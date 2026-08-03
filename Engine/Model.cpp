#include "pch.h"
#include "Model.h"

namespace nu {
	void Model::calculateRadius() {
		m_radius = 0.0f;

		// check for mech radius
		for (const auto& mesh : m_meshes) {
			float radius = mesh.GetRadius();

			if (radius > m_radius) {
				m_radius = radius;
			}
		}
	}
}