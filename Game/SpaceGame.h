#pragma once
#include "Game.h"
#include "Text.h"
#include "Resource.h"

class SpaceGame : public nu::Game {
public:
	enum class GameState {
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver
	};

public:
	SpaceGame() = default;
	SpaceGame(nu::Scene* scene) : Game{ scene } { }

	bool Initialize() override;

	void Update(float dt) override;
	void Draw(class nu::Renderer& renderer) override;

	void OnPlayerDead();
	void AddPoints(int points) { m_score += points; }

private:
	void SpawnPlayer();
	void SpawnEnemy();
	void SpawnPowerUp();

private:
	int m_score{ 0 };
	int m_lives{ 0 };

	float m_stateTimer = 0.0f;
	float m_powerUpTimer = 0.0f;

	float m_spawnTimer = 0.0f;
	float m_spawnTime = 5.0f;
	int m_spawnCount = 0;

	GameState m_gamestate = GameState::Title;

	nu::res_t<nu::Font> titleFont;
	nu::res_t<nu::Font> gameFont;

	//nu::Font* titleFont{ nullptr };
	nu::Text* titleText{ nullptr };

	//nu::Font* gameOverFont{ nullptr };
	nu::Text* gameOverText{ nullptr };

	//nu::Font* gameFont{ nullptr };

	nu::Text* scoreText{ nullptr };
	nu::Text* livesText{ nullptr };
};