#ifndef RENDER_THREADPOOL_H
#define RENDER_THREADPOOL_H

#include <atomic>
#include <thread>

class Renderer; // Forward declaration of the Renderer class


class RenderThreadPool {
    private:
        Renderer* renderer;
        int numOfWorkers;
        bool reRender = false;
        int unfinishedWorkers;
        bool destroyed = false;

        std::condition_variable cv;
        std::vector<std::thread> threads;
        std::mutex mtx;

        void workerLoop(int workerId);
        void checkIfAllWorkersFinished();

    public:
        RenderThreadPool(Renderer* renderer);
        ~RenderThreadPool();

        void startWorkers();
};
#endif