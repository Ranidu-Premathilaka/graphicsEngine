#include "renderThreadPool.h"
#include "../renderer.h"

// PRIVATE METHODS
void RenderThreadPool::workerLoop(int workerId) {
    while (true) {
        // Lock until the master thread signals to re-render
        {
            std::unique_lock<std::mutex> lock(this->mtx);
            this->unfinishedWorkers++; 
            this->cv.wait(lock, [this]{ return this->reRender == true || this->destroyed == true; });
        } 
        if(this->destroyed){break;}
        // Unlocks the mutex. EVERY thread is in parallel now

        this->renderer->workerTask(workerId, this->numOfWorkers);


        // Wait until all workers have finished their tasks
        {
            std::unique_lock<std::mutex> lock(this->mtx);
            this->unfinishedWorkers--; 
            this->checkIfAllWorkersFinished(); 
            this->cv.wait(lock, [this]{ return this->reRender == false; });
        } 
    }


}


void RenderThreadPool::checkIfAllWorkersFinished() {
    if(this->unfinishedWorkers == 0){
        this->cv.notify_all();
    }
}

//PUBLIC METHODS
RenderThreadPool::RenderThreadPool(Renderer* renderer) {
    this->numOfWorkers = std::thread::hardware_concurrency(); 
    this->renderer = renderer;


    for (int i = 0; i < this->numOfWorkers; ++i) {
        this->threads.emplace_back([this, i]() {
                this->workerLoop(i); // Or just workerLoop(i);
            });
    }
}

RenderThreadPool::~RenderThreadPool() {
    while(1){
        if(this->unfinishedWorkers == this->numOfWorkers){
            break;
        }
    }

    this->destroyed = true;
    cv.notify_all(); 

    for (auto& thread : this->threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void RenderThreadPool::startWorkers() {
    
    // To prevent the main thread from proceeding before all workers are ready and waiting
    while(1){
        if(this->unfinishedWorkers == this->numOfWorkers){
            break;
        }
    }


    {
        std::unique_lock<std::mutex> lock(this->mtx);
        this->reRender = true;

        // This is inside a lock to ensure that no other thread 
        //would rush to process and finish before the main thread
        // has a chance to wait and finish
        this->cv.notify_all(); 

        this->cv.wait(lock, [this]{ return this->unfinishedWorkers == 0; });
    }

    this->reRender = false; 
    this->cv.notify_all(); 
}