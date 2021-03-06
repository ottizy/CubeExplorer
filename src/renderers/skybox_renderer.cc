#include "renderers/skybox_renderer.h"

SkyboxRenderer::SkyboxRenderer() {

}

void SkyboxRenderer::render(const std::vector<std::shared_ptr<SkyboxModel>>& models, Camera& camera, const std::shared_ptr<Light>&) {

	if (models.empty()) {
		return;
	}

	m_shader->bind();
	m_shader->upload_tex_unit(0);
	
	auto view_matrix = camera.get_view_matrix();
	view_matrix[3][0] = 0.0f;
	view_matrix[3][1] = 0.0f;
	view_matrix[3][2] = 0.0f;

	m_shader->upload_view_projection_matrix(camera.get_projection_matrix() * view_matrix);

	GLC(glDisable(GL_DEPTH_TEST));
	GLC(glEnable(GL_CULL_FACE));

	for (const auto& model : models) {
		model->bind();
		model->bind_texture(GL_TEXTURE0);
		m_shader->upload_model_matrix(model->get_model_matrix());
		DRAW_CALL(GLC(glDrawElements(GL_TRIANGLES, model->get_indices_count(), GL_UNSIGNED_INT, nullptr)));
	}

	GLC(glDisable(GL_CULL_FACE));
}