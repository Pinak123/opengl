#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window(unsigned int width, unsigned int height, const std::string& title);
    ~Window();

    bool shouldClose() const;
    void swapBuffers() const;
    void pollEvents() const;
    void clear() const;
    static void processInput(GLFWwindow* window);
    GLFWwindow* getWindow() const;

private:
    GLFWwindow* window;
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    
};

#endif // WINDOW_H


