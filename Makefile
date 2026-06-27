CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# macOS Frameworks for OpenGL and GLUT
LDFLAGS  := -framework GLUT -framework OpenGL

# Output executable name
TARGET   := rayTracing

# Source files
SRCS     := main.cpp \
            src/utils/logging.cpp \
            src/intensity/intensity.cpp \
            src/math/vector3D.cpp \
            src/objects/sphere.cpp \
            src/lightSource/lightSource.cpp \
            src/scene/scene.cpp \
            src/camera/camera.cpp \
            src/renderer/renderer.cpp

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

compile: $(TARGET)

time: $(TARGET)
	zsh -c "time ./$(TARGET) test"

clean:
	rm -f $(TARGET)

.PHONY: run compile clean