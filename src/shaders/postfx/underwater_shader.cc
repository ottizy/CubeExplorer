#include "shaders/postfx/underwater_shader.h"

UnderwaterShader::UnderwaterShader() : Shader({ "postfx/underwatershader.comp" }), MultiTexShader(this) {
	bind();
	get_uniform_locations();
}

void UnderwaterShader::upload_time(float time) const {
	upload_uniform(m_time_location, time);
}

void UnderwaterShader::upload_depth(float depth) const {
	upload_uniform(m_depth_location, depth);
}

void UnderwaterShader::get_uniform_locations() {
	MultiTexShader::get_uniform_locations();

	m_time_location = get_uniform_location("time");
	m_depth_location = get_uniform_location("depth");
}
