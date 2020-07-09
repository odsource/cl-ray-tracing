#include "engine.h"

void engine_init_opengl(struct engine *e)
{
        create_shader(GL_VERTEX_SHADER, "/home/me/GitHub/cl-ray-tracing/shader/vertex_shader.glsl");
        create_shader(GL_FRAGMENT_SHADER, "/home/me/GitHub/cl-ray-tracing/shader/fragment_shader.glsl");
}

void engine_set_viewport(struct engine *e, const uint w, const uint h)
{
        CALL_GL(glViewport(0, 0, w, h));

        e->w = w;
        e->h = h;

        LOG_INFO_F("Viewport set to %d:%d", w, h);
}

void engine_set_delta_time(struct engine *e, const double dt)
{
        e->dt = dt;
}

void engine_move_cam(struct engine *e, enum cam_move  dir)
{

}

void engine_look_cam(struct engine *e, const double x, const double y)
{

}

int create_shader(const uint type, const char *path)
{
        const uint id = glCreateShader(type);
        
        LOG_DEBUG_F("Reading shader source code from file %s", path);
        char *src;
        read_src_from_file(path, &src);
}
