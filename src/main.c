#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "common.h"

void on_glfw_error(int code, const char* desc);
int init_glfw_window(GLFWwindow** win, uint w, uint h);

int main(int argc, char** argv)
{
        GLFWwindow* win;
        init_glfw_window(&win, 1280, 720);

        while (!glfwWindowShouldClose(win)) {
                glfwSwapBuffers(win);
                glfwPollEvents();
        }

        return EXIT_SUCCESS;
}

void on_glfw_error(int code, const char* desc)
{
        LOG_ERROR(desc);
}

int init_glfw_window(GLFWwindow** win, uint w, uint h)
{
        if (!glfwInit()) {
                LOG_ACTION_ERROR("GLFW", "INIT");
                return ERROR_GLFW;
        } else {
                LOG_ACTION_SUCCESS("GLFW", "INIT");
        }

        glfwSetErrorCallback(on_glfw_error);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        *win = glfwCreateWindow(w, h, PROGRAM_NAME, NULL, NULL);
        if (!*win) {
                LOG_ACTION_ERROR("GLFW WINDOW", "CREATE");
                return ERROR_GLFW;
        } else {
                LOG_ACTION_SUCCESS("GLFW WINDOW", "CREATE");
        }

        glfwMakeContextCurrent(*win);

        glfwSetInputMode(*win, GLFW_STICKY_KEYS, GLFW_TRUE);
        glfwSetInputMode(*win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        const GLenum err = glewInit();
        if (err != GLEW_OK) {
                LOG_ACTION_ERROR("GLEW", "INIT");
                return ERROR_GLEW;
        }

        if (!GLEW_VERSION_3_3) {
                LOG_ERROR("OpenGL 3.3 is not supported");
                return OPENGL_WRONG_VERSION;
        } else {
                LOG_INFO("OpenGL 3.3 is supported");
        }

        return SUCCESS;
}
