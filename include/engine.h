#ifndef ENGINE_H
#define ENGINE_H

#include <string.h>
#include <GL/glew.h>
#include "types.h"
#include "log.h"
#include "util.h"

enum cam_move {
        front,
        back,
        left,
        right
};

struct engine {
        uint w;
        uint h;
        double dt;
};

void engine_init_opengl(struct engine *e);
void engine_set_viewport(struct engine *e, const uint w, const uint h);
void engine_set_delta(struct engine *e, const double dt);
void engine_move_cam(struct engine *e, enum cam_move dir);
void engine_look_cam(struct engine *e, const double x, const double y);
int create_shader(const uint type, const char *path);

#endif /* ENGINE_H */
