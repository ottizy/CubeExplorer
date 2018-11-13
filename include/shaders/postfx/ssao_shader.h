#pragma once

#include <vector>

#include "../shader.h"
#include "../multi_tex_shader.h"

class SSAOShader : public Shader, public MultiTexShader<3>{
public:
	SSAOShader();

	SSAOShader(const SSAOShader&) = delete;
	SSAOShader(const SSAOShader&&) = delete;

	void upload_kernel(const std::vector<glm::vec3>& kernel) const;
	void upload_resolution(const glm::vec2& res) const;
	void upload_projection_matrix(const glm::mat4& projection) const;

private:
	void get_uniform_locations() override;

	int m_kernel_location;
	int m_resolution_location;
	int m_projection_matrix_location;
};