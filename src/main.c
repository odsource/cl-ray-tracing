#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "common.h"
#include "engine.h"

void on_glfw_error(int code, const char *desc);
int init_glfw_window(GLFWwindow **win, const uint w, const uint h);
int init_opengl_context(GLFWwindow *win);
void process_key_input(GLFWwindow *win, struct engine *e);
void process_mouse_input(GLFWwindow *win, struct engine *e);

int main(int argc, char** argv)
{
        const uint w = 1280;
        const uint h = 720;
        GLFWwindow* win;

        if (init_glfw_window(&win, w, h))
                return EXIT_FAILURE;

        if (init_opengl_context(win))
                return EXIT_FAILURE;

        glfwSetInputMode(win, GLFW_STICKY_KEYS, GLFW_TRUE);
        glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        struct engine e;
        engine_init_opengl(&e);
        engine_set_viewport(&e, w, h);

        double last_frame = 0;

        while (!glfwWindowShouldClose(win)) {
                double curr_frame = glfwGetTime();
                last_frame = curr_frame;

                process_key_input(win, &e);
                process_mouse_input(win, &e);

                glfwSwapBuffers(win);
                glfwPollEvents();
        }
                
        glfwTerminate();

        return EXIT_SUCCESS;
}

void on_glfw_error(int code, const char *desc)
{
        LOG_ERROR_F("GLFW error code %d, %s", code, desc);
}

int init_glfw_window(GLFWwindow **win, const uint w, const uint h)
{
        if (!glfwInit()) {
                LOG_ACTION_ERROR("GLFW", "INIT");
                return FAILURE;
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
                return FAILURE;
        } else {
                LOG_ACTION_SUCCESS("GLFW WINDOW", "CREATE");
        }

        return SUCCESS;
}

int init_opengl_context(GLFWwindow *win)
{
        glfwMakeContextCurrent(win);

        if (glewInit()) {
                LOG_ACTION_ERROR("GLEW", "INIT");
                return FAILURE;
        } else {
                LOG_ACTION_SUCCESS("GLEW", "INIT");
        }

        if (!GLEW_VERSION_3_3) {
                LOG_ERROR("OpenGL 3.3 is not supported");
                return FAILURE;
        } else {
                LOG_INFO("OpenGL 3.3 is supported");
        }

        return SUCCESS;
}

void process_key_input(GLFWwindow *win, struct engine *e)
{
        if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(win, GL_TRUE);

        if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
                engine_move_cam(e, front);

        if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
                engine_move_cam(e, left);

        if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
                engine_move_cam(e, back);

        if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
                engine_move_cam(e, right);
}

void process_mouse_input(GLFWwindow *win, struct engine *e)
{
        double x, y;
        glfwGetCursorPos(win, &x, &y);

        engine_look_cam(e, x, y);
}
