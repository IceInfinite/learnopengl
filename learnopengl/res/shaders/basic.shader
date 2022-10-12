#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 tex_coord;

uniform mat4 u_mvp;

out vec2 v_tex_coord;
out vec4 v_color;

void main() {
  gl_Position = u_mvp * position;
  v_color = color;
  v_tex_coord = tex_coord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_tex_coord;
in vec4 v_color;

uniform sampler2D u_texture0;

void main() {
  vec4 tex_color = texture(u_texture0, v_tex_coord);
  color = v_color;
};