#version 330 core

uniform mat4 projection_matrix;
uniform mat4 model_matrix;
uniform mat4 view_matrix;

uniform vec3 color;

in vec3 vtx_position;

out vec3 v_color;
out vec3 v_position;

void main()
{
    v_position = (view_matrix * model_matrix * vec4(vtx_position, 1.)).xyz;
    v_color = color;
    gl_Position = projection_matrix * vec4(v_position, 1.);
}
