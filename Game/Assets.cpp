#include "Assets.h"
#include "Core/Random.h"

using namespace nu;

namespace assets {
	Mesh playerMesh{ { Vector2{ 1, 0}, Vector2{-1, 1}, Vector2{-0.5f, 0}, Vector2{-1, -1}, Vector2{1, 0} }, Color{ RandomFloat(), RandomFloat(), RandomFloat()}};
	std::shared_ptr<Model> playerModel = std::make_shared<Model>( std::vector<Mesh>{ playerMesh } );

	Mesh enemyMesh{ { Vector2{ 1, 0}, Vector2{-1, 1}, Vector2{-0.5f, 0}, Vector2{-1, -1}, Vector2{1, 0} }, Color{ 1.0f, 0.0f, 0.0f} };
	std::shared_ptr<Model> enemyModel = std::make_shared<Model>( std::vector<Mesh>{ enemyMesh } );

	Mesh tripleShotMesh{ { Vector2{ 1.0f, -1.0f}, Vector2{0.0f, 0.0f}, Vector2{0.0f, -1.0f}, Vector2{0.0f, 0.0f}, Vector2{-1.0f, -1.0f} }, Color{ 1.0f, 1.0f, 1.0f} };
	std::shared_ptr<Model> tripleShotModel = std::make_shared<Model>( std::vector<Mesh>{ tripleShotMesh } );

	Mesh circleShotMesh{ { Vector2{ 1.0f, -1.0f}, Vector2{0.0f, 0.0f}, Vector2{0.0f, -1.0f}, Vector2{0.0f, 0.0f}, Vector2{-1.0f, -1.0f}, Vector2{0.0f, 0.0f}, Vector2{-1.0, 0.0f}, Vector2{0.0f, 0.0f}, Vector2{-1.0f, 1.0f}, Vector2{0.0f, 0.0f}, Vector2{0.0f, 1.0f}, Vector2{0.0f, 0.0f}, Vector2{1.0f, 1.0f}, Vector2{0.0f, 0.0f}, Vector2{1.0f, 0.0f}}, Color{1.0f, 1.0f, 1.0f} };
	std::shared_ptr<Model> circleShotModel = std::make_shared<Model>( std::vector<Mesh>{ circleShotMesh } );

	Mesh sizeMesh{ { Vector2{ 1, 0}, Vector2{-1, 1}, Vector2{-0.5f, 0}, Vector2{-1, -1}, Vector2{1, 0} }, Color{ 1.0f, 1.0f, 1.0f} };
	std::shared_ptr<Model> sizeModel = std::make_shared<Model>( std::vector<Mesh>{ sizeMesh } );

	Mesh bulletMesh{
	{
	  Vector2{ -1, -1 },
	  Vector2{ 1, 0 },
	  Vector2{ -1, 1 },
	  Vector2{ -1, -1 },
	},
	Color{ 1.0f, 0.0f, 0.0f }
	};
	std::shared_ptr<Model> bulletModel = std::make_shared<Model>( std::vector<Mesh>{ bulletMesh } );
}