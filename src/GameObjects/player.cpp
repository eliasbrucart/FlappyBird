#include "player.h"

#include "raylib.h"

#include "gameobjects/pipes.h"
#include "screens/game.h"
#include "screens/gameplay.h"

namespace Game
{
	Player player;
	Sound pointSFX;
	Sound wingSFX;

	void InitPlayer() 
	{
		player.rec.x = 100.0f;
		player.rec.y = 250.0f;
		player.rec.width = 50.0f;
		player.rec.height = 50.0f;
		player.lifes = 3;
		player.points = 0;
		player.speed = 600.0f;
		player.gravity = 300.0f;
		player.isAlive = true;
		player.sprite = LoadTexture("assets/sprites/bird-atlas.png");
		frameRec = { 0.0f, 0.0f, static_cast<float>(player.sprite.height / 2), static_cast<float>(player.sprite.width / 2) };
		pointSFX = LoadSound("assets/sounds/sfx_point.wav");
		wingSFX = LoadSound("assets/sounds/sfx_wing.wav");
	}

	void MovePlayer() 
	{
		if (IsKeyDown(KEY_SPACE))
		{
			if (player.isAlive == true)
			{
				player.rec.y -= player.speed * GetFrameTime();
				PlaySound(wingSFX);
			}
		}
		else 
		{
			player.rec.y += player.gravity * GetFrameTime();
		}
	}
	
	void DrawPlayer() 
	{
		if (player.isAlive == true)
		{
			framesCounter += GetFrameTime();

			if (framesCounter >= (maxCounter))
			{
				framesCounter = 0;

				currentFrame++;
				if (currentFrame > 1)
				{
					currentFrame = 0;
				}

				frameRec.x = static_cast<float>(currentFrame*(player.sprite.width / 2));
				frameRec.y = static_cast<float>(currentFrame*(player.sprite.height / 2));
			}
			playerPosition = { player.rec.x, player.rec.y };

			DrawTextureRec(player.sprite, frameRec, playerPosition, WHITE);
		}
	}

	void LimitWithScreen()
	{
		if ((player.rec.y) <= minScreenHeight)
		{
			player.rec.y = static_cast<float>(minScreenHeight);
		}
		if ((player.rec.y + player.rec.height) >= screenHeight)
		{
			player.rec.y = static_cast<float>(screenHeight) - player.rec.height;
			player.isAlive = false;
		}
	}

	void CollisionPlayerWithPipes() 
	{
		for (int i = 0; i < sizePipes; i++)
		{
			if (player.isAlive == true)
			{
				if (CheckCollisionRecs(player.rec, tube[i].rec))
				{
					player.isAlive = false;
				}
			}
		}
	}

	void CheckPlayerIsAlive()
	{
		if (player.isAlive == false)
		{
			gameState = GameState::FinalMenu;
		}
	}

}