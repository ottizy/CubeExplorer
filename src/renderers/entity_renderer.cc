#include "renderers/entity_renderer.h"

EntityRenderer::EntityRenderer() {
	m_depth_shader = std::make_unique<EntityShader>(true);
}

void EntityRenderer::render(const std::vector<std::shared_ptr<ChunkModel>>& models, Camera& camera, const std::shared_ptr<Light>& light) {
	if (models.empty()) {
		return;
	}

	m_shader->bind();

	m_shader->upload_tex_units({ 0, 1 });
	m_shader->upload_view_matrix(camera.get_view_matrix());
	m_shader->upload_projection_matrix(camera.get_projection_matrix());
	m_shader->upload_light_source(light);
	m_shader->upload_shadow_transform(light->get_transform_matrix());
	m_shader->upload_clip_plane(m_clip_plane);

	if (m_shadow_map)
		m_shadow_map->bind(GL_TEXTURE1);

	GLC(glEnable(GL_DEPTH_TEST));
	GLC(glEnable(GL_CULL_FACE));
	GLC(glFrontFace(GL_CCW));
	GLC(glEnable(GL_CLIP_DISTANCE0));
	GLC(glEnable(GL_BLEND));
	GLC(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


	for (const auto& model : models) {
		if (model->get_indices_count() > 0) {

			if (!intersects_frustum(model, camera)) {
				continue;
			}

			model->bind();
			model->bind_texture(GL_TEXTURE0);
			m_shader->upload_model_matrix(model->get_model_matrix());
			DRAW_CALL(GLC(glDrawElements(GL_TRIANGLES, model->get_indices_count(), GL_UNSIGNED_INT, nullptr)));
		}
	}

	GLC(glDisable(GL_CULL_FACE));
	GLC(glDisable(GL_DEPTH_TEST))
	GLC(glDisable(GL_BLEND));
	GLC(glDisable(GL_CLIP_DISTANCE0));
}

void EntityRenderer::render_depth(const std::vector<std::shared_ptr<ChunkModel>>& models, Camera& camera, const std::shared_ptr<Light>& light) {
	if (models.empty()) {
		return;
	}

	m_depth_shader->bind();

	m_depth_shader->upload_view_matrix(light->get_view_matrix());
	m_depth_shader->upload_projection_matrix(light->get_projection_matrix());
	m_depth_shader->upload_clip_plane(m_clip_plane);


	GLC(glEnable(GL_DEPTH_TEST));
	GLC(glEnable(GL_CULL_FACE));
	GLC(glFrontFace(GL_CCW));
	GLC(glEnable(GL_CLIP_DISTANCE0));

	for (const auto& model : models) {
		if (model->get_indices_count() > 0) {

			model->bind();
			m_depth_shader->upload_model_matrix(model->get_model_matrix());
			DRAW_CALL(GLC(glDrawElements(GL_TRIANGLES, model->get_indices_count(), GL_UNSIGNED_INT, nullptr)));
		}
	}

	GLC(glDisable(GL_CULL_FACE));
	GLC(glDisable(GL_DEPTH_TEST));
	GLC(glDisable(GL_CLIP_DISTANCE0));
}