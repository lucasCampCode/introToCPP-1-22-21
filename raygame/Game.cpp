#include "Game.h"
#include "raylib.h"

bool Game::m_gameOver = false;
bool Game::m_gameStarted = false;
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
	if (mouseposx >= Lp && mouseposx <= Rp && mouseposy >= Tp && mouseposy <= Bp && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		return true;
	return false;
}

void Game::start()
{
	int screenWidth = 1024;
	int screenHeight = 768;
	initRecs();
	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
	m_camera->offset = { (float)screenWidth / 2, (float)screenHeight / 2 };
	m_camera->target = { (float)screenWidth / 2, (float)screenHeight / 2 };
	m_camera->zoom = 1;

	SetTargetFPS(60);
	m_start = new Scene();
	m_playerDeath = new Scene();
	//first scene and background
	m_screen1 = new Scene();
	m_world1 = new Actor(16, 12, 0, "images/firstMap.png", 0);
	m_world1->scale(MathLibrary::Vector2(32, 24));
	for (int i = 0; i < 20; i++)
	{
		m_enemies[i] = new Enemy(rand() % 30 + 1, rand() % 22 + 1, 0.8f, "images/PizzaGuyWalkRight(2).png", 10, 4, 1);
		m_enemies[i]->scale(MathLibrary::Vector2(1.5f, 1.5f));
	}
	m_highScore = new Scene();
	m_load = new Scene();
	//player initilization
	m_player1 = new Player(16, 12,0.8f, "images/PizzaGuyWalkRight(2).png", 10, 10, 2);
	m_player1->scale(MathLibrary::Vector2(1.5f,1.5f));

	//m_wall1 = new Wall(6,4,12,8);
	//m_wall2 = new Wall(26,4,12,8);
	//m_wall3 = new Wall(6,19,12,7);
	//m_wall4 = new Wall(26,19,12,7);
	//addes scenes and actors to those scenes
	setCurrentScene(addScene(m_start));//index 0
	addScene(m_highScore);//index 1
	addScene(m_load);//index 2
	addScene(m_screen1);//index 3
	addScene(m_playerDeath);//index 4
	m_screen1->addActor(m_world1);
	m_screen1->addActor(m_player1);

	//m_screen1->addActor(m_wall1);
	//m_screen1->addActor(m_wall2);
	//m_screen1->addActor(m_wall3);
	//m_screen1->addActor(m_wall4);
}

void Game::initRecs()
{
	m_startB.x = 312;
	m_startB.y = 150;
	m_startB.width = 325;
	m_startB.height = 80;

	m_highScoreB.x = 312;
	m_highScoreB.y = 300;
	m_highScoreB.width = 325;
	m_highScoreB.height = 80;

	m_loadB.x = 312;
	m_loadB.y = 450;
	m_loadB.width = 325;
	m_loadB.height = 80;

	m_exitB.x = 312;
	m_exitB.y = 600;
	m_exitB.width = 325;
	m_exitB.height = 80;

	m_returnB.x = 0;
	m_returnB.y = 660;
	m_returnB.width = 325;
	m_returnB.height = 80;

	m_tableB.x = 430;
	m_tableB.y = 5;
	m_tableB.width = 500;
	m_tableB.height = 750;
}

void Game::updateSceneButtons()
{
	
	switch (m_currentSceneIndex)
	{
	case 0:
		if(CheckCollisionPointRec(GetMousePosition(),m_startB) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			setCurrentScene(3);
		if (CheckCollisionPointRec(GetMousePosition(), m_highScoreB) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			setCurrentScene(1);
		if (CheckCollisionPointRec(GetMousePosition(), m_loadB) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			setCurrentScene(2);
		if (CheckCollisionPointRec(GetMousePosition(), m_exitB) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			setGameOver(true);
		break;
	case 1:
		if (CheckCollisionPointRec(GetMousePosition(), m_returnB) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			setCurrentScene(0);
		break;
	case 2:
		if (CheckCollisionPointRec(GetMousePosition(), m_returnB) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			setCurrentScene(0);
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}
}

void Game::startWave(float deltaTime)
{
	if ((m_timer+=deltaTime) > 5) 
	{
		if(m_enemyCount < 20)
			m_screen1->addActor(m_enemies[m_enemyCount]);
		m_enemyCount++;
		m_timer = 0;
	}
}

void Game::drawScreenButtons()
{
	switch (m_currentSceneIndex)
	{
	case 0:
		DrawRectangleRec(m_startB, GREEN);
		DrawText("start", m_startB.x + 50, m_startB.y + 0, 80, WHITE);
		DrawRectangleRec(m_highScoreB, ORANGE);
		DrawText("HighScore", m_highScoreB.x + 0, m_highScoreB.y + 10, 63, WHITE);
		DrawRectangleRec(m_loadB, DARKBLUE);
		DrawText("Load", m_loadB.x + 55, m_loadB.y + 0, 80, WHITE);
		DrawRectangleRec(m_exitB, RED);
		DrawText("exit", m_exitB.x + 60, m_exitB.y + 0, 80, WHITE);
		break;
	case 1:
		DrawRectangleLinesEx(m_returnB, 4, WHITE);
		DrawText("return", m_returnB.x + 20, m_returnB.y + 0, 80, WHITE);
		DrawRectangleLinesEx(m_tableB, 4, WHITE);
		break;
	case 2:
		DrawRectangleLinesEx(m_returnB, 4, WHITE);
		DrawText("return", m_returnB.x + 20, m_returnB.y + 0, 80, WHITE);
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}
}

void Game::update(float deltaTime)
{
	if (!m_scenes[m_currentSceneIndex]->getStarted())
		m_scenes[m_currentSceneIndex]->start();

	m_scenes[m_currentSceneIndex]->update(deltaTime);
	if (getCurrentSceneIndex() == 3) {
		startWave(deltaTime);
	}
	updateSceneButtons();
}

void Game::draw()
{
	BeginDrawing();

	BeginMode2D(*m_camera);
	ClearBackground(BLACK);

	m_scenes[m_currentSceneIndex]->draw();
	drawScreenButtons();
	
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
