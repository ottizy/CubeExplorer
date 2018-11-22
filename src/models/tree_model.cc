#include <array>

#include "models/tree_model.h"


TreeModel::TreeModel(const std::shared_ptr<ITexture>& texture, const glm::vec3& position) 
	: ChunkModel(texture, position){
	generate_geometry();
}

void TreeModel::generate_geometry() {
	
}

void TreeModel::generate_trunk(int x, int y, int z) {
	
	generate_face(x, y, z, POSITIVE, right_face);
	generate_face_texture(ChunkModel::TREE_TRUNK);
	generate_normals(right_normal);

	generate_face(x, y, z, NEGATIVE, left_face);
	generate_face_texture(ChunkModel::TREE_TRUNK);
	generate_normals(left_normal);

	generate_face(x, y, z, POSITIVE, top_face);
	generate_face_texture(ChunkModel::TREE_TRUNK_INSIDE);
	generate_normals(top_normal);

	generate_face(x, y, z, POSITIVE, front_face);
	generate_face_texture(ChunkModel::TREE_TRUNK);
	generate_normals(front_normal);

	generate_face(x, y, z, NEGATIVE, back_face);
	generate_face_texture(ChunkModel::TREE_TRUNK);
	generate_normals(back_normal);

	generate_face(x, y, z, NEGATIVE, bottom_face);
	generate_face_texture(ChunkModel::TREE_TRUNK_INSIDE);
	generate_normals(bottom_normal);
}

void TreeModel::generate_branch(int x, int y, int z) {
	generate_face(x, y, z, POSITIVE, right_face);
	generate_face_texture(ChunkModel::TREE_BRANCH);
	generate_normals(right_normal);

	generate_face(x, y, z, NEGATIVE, left_face);
	generate_face_texture(ChunkModel::TREE_BRANCH);
	generate_normals(left_normal);

	generate_face(x, y, z, POSITIVE, top_face);
	generate_face_texture(ChunkModel::TREE_BRANCH);
	generate_normals(top_normal);

	generate_face(x, y, z, POSITIVE, front_face);
	generate_face_texture(ChunkModel::TREE_BRANCH);
	generate_normals(front_normal);

	generate_face(x, y, z, NEGATIVE, back_face);
	generate_face_texture(ChunkModel::TREE_BRANCH);
	generate_normals(back_normal);

	generate_face(x, y, z, NEGATIVE, bottom_face);
	generate_face_texture(ChunkModel::TREE_BRANCH);
	generate_normals(bottom_normal);
}