#include "Game.h"
#include "raylib.h"

bool Game::m_gameOver = false;
Scene** Game::m_scenes = new Scene*;
int Game::m_sceneCount = 0;
int Game::m_currentSceneIndex = 0;


Game::Game()
{
	m_gameOver = false;
	m_scenes = new Scene*;
	m_camera = new Camera2D();
	m_currentSceneIndex = 0;
	m_sceneCount = 0;
}

bool Game::withinBounds(int Lp, int Tp, int Rp, int Bp)
{
	float mouseposx = GetMouseX();
	float mouseposy = GetMouseY();
	if (mouseposx >= Lp && mouseposx <= Rp && mouseposy >= Tp && mouseposy <= Bp)
		return true;
	return false;
}

void Game::start()
{
	int screenWidth = 1024;
	int screenHeight = 760;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
	m_camera->offset = { (float)screenWidth / 2, (float)screenHeight / 2 };
	m_camera->target = { (float)screenWidth / 2, (float)screenHeight / 2 };
	m_camera->zoom = 1;

	SetTargetFPS(60);
	startMenu();
}

void Game::startMenu()
{
	char start[] = "Start";
	char* startPtr = start;
	char highScore[] = "HighScores";
	char* highScorePtr = highScore;
	char load[] = "Load";
	char* loadPtr = load;
	char exit[] = "Exit";
	char* exitPtr = exit;
	//draws start window loop
	while (!IsMouseButtonDown(MOUSE_LEFT_BUTTON) || !withinBounds(GetScreenWidth() / 2 - 200, 150, GetScreenWidth() / 2 + 200, 250)) {
		BeginDrawing();
		ClearBackground(BLACK);
		DrawRectangle(GetScreenWidth() / 2 - 200, 150, 400, 100, GREEN);
		DrawRectangle(GetScreenWidth() / 2 - 200, 300, 400, 100, ORANGE);
		DrawRectangle(GetScreenWidth() / 2 - 200, 450, 400, 100, DARKBLUE);
		DrawRectangle(GetScreenWidth() / 2 - 200, 600, 400, 100, RED);
		DrawText(startPtr, GetScreenWidth() / 2 - 115, 160, 90, RAYWHITE);
		DrawText(highScorePtr, GetScreenWidth() / 2 - 190, 315, 68, RAYWHITE);
		DrawText(loadPtr, GetScreenWidth() / 2 - 105, 460, 90, RAYWHITE);
		DrawText(exitPtr, GetScreenWidth() / 2 - 90, 610, 90, RAYWHITE);
		/*DrawRectanglePro(Rectangle{ 16,16,16,16 }, Vector2{ 8,8 }, 45.0f, GREEN);*/
		EndDrawing();
	}
}

void Game::update(float deltaTime)
{
	for (int i = 0; i < m_sceneCount; i++)
	{
		m_scenes[i]->update(deltaTime);
	}
}

void Game::draw()
{
	BeginDrawing();

	BeginMode2D(*m_camera);
	ClearBackground(RAYWHITE);

	for (int i = 0; i < m_sceneCount; i++)
	{
		m_scenes[i]->draw();
	}

	EndMode2D();
	EndDrawing();
}

void Game::end()
{
	CloseWindow();
}

MathLibrary::Matrix3* Game::getWorld()
{
	return getCurrentScene()->getWorld();
}

void Game::run()
{
	start();

	while (!m_gameOver && !RAYLIB_H::WindowShouldClose())
	{
		float deltaTime = RAYLIB_H::GetFrameTime();
		update(deltaTime);
		draw();
	}

	end();
}

Scene* Game::getScene(int index)
{
	if (index < 0 || index >= m_sceneCount)
		return nullptr;

	return m_scenes[index];
}

Scene* Game::getCurrentScene()
{
	return m_scenes[m_currentSceneIndex];
}

int Game::getCurrentSceneIndex()
{
	return m_currentSceneIndex;
}

int Game::addScene(Scene* scene)
{
	//If the scene is null then return before running any other logic
	if (!scene)
		return -1;

	//Create a new temporary array that one size larger than the original
	Scene** tempArray = new Scene*[m_sceneCount + 1];

	//Copy values from old array into new array
	for (int i = 0; i < m_sceneCount; i++)
	{
		tempArray[i] = m_scenes[i];
	}

	//Store the current index
	int index = m_sceneCount;

	//Sets the scene at the new index to be the scene passed in
	tempArray[index] = scene;

	//Set the old array to the tmeporary array
	m_scenes = tempArray;
	m_sceneCount++;

	return index;
}

bool Game::removeScene(Scene* scene)
{
	//If the scene is null then return before running any other logic
	if (!scene)
		return false;

	bool sceneRemoved = false;

	//Create a new temporary array that is one less than our original array
	Scene** tempArray = new Scene*[m_sceneCount - 1];

	//Copy all scenes except the scene we don't want into the new array
	int j = 0;
	for (int i = 0; i < m_sceneCount; i++)
	{
		if (tempArray[i] != scene)
		{
			tempArray[j] = m_scenes[i];
			j++;
		}
		else
		{
			sceneRemoved = true;
		}
	}

	//If the scene was successfully removed set the old array to be the new array
	if (sceneRemoved)
	{
		m_scenes = tempArray;
		m_sceneCount--;
	}
		

	return sceneRemoved;
}

void Game::setCurrentScene(int index)
{
	//If the index is not within the range of the the array return
	if (index < 0 || index >= m_sceneCount)
		return;

	//Call end for the previous scene before changing to the new one
	if (m_scenes[m_currentSceneIndex]->getStarted())
		m_scenes[m_currentSceneIndex]->end();

	//Update the current scene index
	m_currentSceneIndex = index;
}

bool Game::getKeyDown(int key)
{
	return RAYLIB_H::IsKeyDown((KeyboardKey)key);
}

bool Game::getKeyPressed(int key)
{
	return RAYLIB_H::IsKeyPressed((KeyboardKey)key);
}

void Game::destroy(Actor* actor)
{
	getCurrentScene()->removeActor(actor);
	if (actor->getParent())
		actor->getParent()->removeChild(actor);
	actor->end();
	delete actor;
}

void Game::setGameOver(bool value)
{
	Game::m_gameOver = value;
}
