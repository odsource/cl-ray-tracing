#version 330 core
in vec2 frag_tex_coord;

out vec4 color;

uniform sampler2D tex;

void main()
{
        color = texture(tex, frag_tex_coord);
}
