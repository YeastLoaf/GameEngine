#pragma once
#include "Mesh.h"

namespace nu{
	class Model {
	public:
		Model() = default;
		Model(const std::vector<Mesh>& meshes) : m_meshes{ meshes } { calculateRadius(); }

		void AddMesh(const Mesh& mesh) {
			m_meshes.push_back(mesh); 
			calculateRadius();
		}

		void SetMeshes(const std::vector<Mesh>& meshes) {
			m_meshes = meshes;
			calculateRadius();
		}
		const std::vector<Mesh>& GetMeshes() const { return m_meshes; }

		float GetRadius() const { return m_radius; };

		void calculateRadius();

	private:
		float m_radius = 0.0f;
		std::vector<Mesh> m_meshes;
	};
}