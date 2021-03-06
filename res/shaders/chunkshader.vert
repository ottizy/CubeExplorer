#include "ext/shadows_vert.glsl"

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 tex_coords;
layout(location = 2) in vec3 normal;

out vec2 tex_coords_fs;
out vec3 normal_fs;
out vec4 world_position;

uniform mat4 model_matrix;
uniform mat4 view_projection_matrix;

uniform vec4 clip_plane;

void main(void){

	world_position = model_matrix * vec4(position, 1.0);

	gl_ClipDistance[0] = dot(world_position, clip_plane);

	gl_Position = view_projection_matrix * world_position;

	transform_shadow_coords(world_position, gl_Position.z);

	tex_coords_fs = tex_coords;
	normal_fs = normalize(mat3(model_matrix) * normal);
}