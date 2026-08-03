#include "Assets.h"
#include "Random.h"

using namespace nu;

namespace assets {
	Mesh playerMesh{ { Vector2{ 1, 0}, Vector2{-1, 1}, Vector2{-0.5f, 0}, Vector2{-1, -1}, Vector2{1, 0} }, Color{ RandomFloat(), RandomFloat(), RandomFloat()}};
	Model playerModel = { std::vector<Mesh>{ playerMesh } };

	Mesh enemyMesh{ { Vector2{ 1, 0}, Vector2{-1, 1}, Vector2{-0.5f, 0}, Vector2{-1, -1}, Vector2{1, 0} }, Color{ 1.0f, 0.0f, 0.0f} };
	Model enemyModel = { std::vector<Mesh>{ enemyMesh } };

	Mesh tripleShotMesh{ { Vector2{ 1.0f, -1.0f}, Vector2{0.0f, 0.0f}, Vector2{0.0f, -1.0f}, Vector2{0.0f, 0.0f}, Vector2{-1.0f, -1.0f} }, Color{ 1.0f, 1.0f, 1.0f} };
	Model tripleShotModel = { std::vector<Mesh>{ tripleShotMesh } };

	Mesh circleShotMesh{ { Vector2{ 1.0f, -1.0f}, Vector2{0.0f, 0.0f}, Vector2{0.0f, -1.0f}, Vector2{0.0f, 0.0f}, Vector2{-1.0f, -1.0f}, Vector2{0.0f, 0.0f}, Vector2{-1.0, 0.0f}, Vector2{0.0f, 0.0f}, Vector2{-1.0f, 1.0f}, Vector2{0.0f, 0.0f}, Vector2{0.0f, 1.0f}, Vector2{0.0f, 0.0f}, Vector2{1.0f, 1.0f}, Vector2{0.0f, 0.0f}, Vector2{1.0f, 0.0f}}, Color{1.0f, 1.0f, 1.0f} };
	Model circleShotModel = { std::vector<Mesh>{ circleShotMesh } };

	Mesh sizeMesh{ { Vector2{ 1, 0}, Vector2{-1, 1}, Vector2{-0.5f, 0}, Vector2{-1, -1}, Vector2{1, 0} }, Color{ 1.0f, 1.0f, 1.0f} };
	Model sizeModel = { std::vector<Mesh>{ sizeMesh } };

	Mesh bulletMesh{
	{
	  Vector2{ -1, -1 },
	  Vector2{ 1, 0 },
	  Vector2{ -1, 1 },
	  Vector2{ -1, -1 },
	},
	Color{ 1.0f, 0.0f, 0.0f }
	};
	Model bulletModel = { std::vector<Mesh>{ bulletMesh } };
}