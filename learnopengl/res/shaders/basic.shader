#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 tex_coord;
layout(location = 3) in float a_tex_index;

uniform mat4 u_mvps[2];

out vec2 v_tex_coord;
out vec4 v_color;
out float f_tex_index;

void main() {
  if (a_tex_index == 0.0f)
    gl_Position = u_mvps[0] * position;
  else
    gl_Position = u_mvps[1] * position;

  v_color = color;
  v_tex_coord = tex_coord;
  f_tex_index = a_tex_index;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_tex_coord;
in vec4 v_color;
in float f_tex_index;

uniform sampler2D u_textures[2];

void main() {
  int texture_index = int(f_tex_index);
  vec4 tex_color = texture(u_textures[texture_index], v_tex_coord);
  color = tex_color;
};