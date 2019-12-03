#include "gameplay.h"

#include "raylib.h"

#include "game.h"
#include "gameobjects/player.h"
#include "gameobjects/pipes.h"

namespace Game
{
	const int screenWidth = 800;
	const int screenHeight = 450;
	int minScreenWidth = 0;
	int minScreenHeight = 0;

	Texture2D background;

	Vector2 playerPosition;
	Rectangle frameRec;
	float currentFrame = 0.0f;
	float framesCounter = 0.0f;

	float maxCounter = 0.5f;

	void InitWindowGame() 
	{
		InitWindow(screenWidth, screenHeight, "Happy Flappy -V0.1");
		InitAudioDevice();
		InitGame();
	}

	void InitGame() 
	{
		InitPlayer();
		InitPipes();
		gameState = GameState::StartMenu;
		player.points = 0;
		background = LoadTexture("assets/sprites/bg-large-1.png");
	}

	void GamePlayScreen()
	{
		Update();
		Draw();
	}

	void Update() 
	{
		MovePlayer();
		LimitWithScreen();
		MovePipes();
		PipesOutOfScreen();
		CollisionPlayerWithPipes();
	}

	void Draw() 
	{
		ClearBackground(BLACK);
		DrawTexture(background, minScreenWidth, minScreenHeight, WHITE);
		DrawPlayer();
		DrawPipes();
		DrawText(TextFormat("Points: %i", player.points), 100, 50, 20, WHITE);
	}
}