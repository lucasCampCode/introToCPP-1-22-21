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
	int screenHeight = 760;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
	m_camera->offset = { (float)screenWidth / 2, (float)screenHeight / 2 };
	m_camera->target = { (float)screenWidth / 2, (float)screenHeight / 2 };
	m_camera->zoom = 1;

	SetTargetFPS(60);
	m_start = new Scene();
	m_screen1 = new Scene();
	m_highScore = new Scene();
	m_load = new Scene();

	m_block1 = new Ground(0, GetScreenHeight() - 100, 500, 100, " ");
	m_player1 = new Player(10, 10, 5, " ", 10, 100, 10);
	m_returnB = new Button();
	setCurrentScene(addScene(m_start));//index 0
	addScene(m_highScore);//index 1
	addScene(m_load);//index 2
	addScene(m_screen1);//index 3

	startMenu();

	m_screen1->addActor(m_player1);
	m_screen1->addActor(m_block1);
}

void Game::startMenu()
{
	//initilizes buttons
	m_startB = new Button(312, 150, 400, 100, GREEN, "Start", 90);
	m_startB->offsetText(MathLibrary::Vector2(100, 0));
	m_HighScoreB = new Button(312, 300, 400, 100, ORANGE, "HighScore", 70);
	m_loadB = new Button(312, 450, 400, 100, DARKBLUE, "Load", 90);
	m_exitB = new Button(312, 600, 400, 100, RED, "Exit", 90);
	//adds buttons to scene
	m_start->addActor(m_startB);
	m_start->addActor(m_HighScoreB);
	m_start->addActor(m_loadB);
	m_start->addActor(m_exitB);
		
}

int Game::highScoreMenu()
{
	int option = 0;
	while (option == 0)
	{
		BeginDrawing();
		ClearBackground(BLACK);
		//Underlay is white boxes
		DrawRectangle(312, 0, 400, 100, RAYWHITE);
		DrawRectangle(312, 110, 400, 625, RAYWHITE);
		DrawRectangle(5, GetScreenHeight() - 105, 300, 80, RAYWHITE);
		DrawRectangle(GetScreenWidth() - 305, GetScreenHeight() - 105, 300, 80, RAYWHITE);
		//Overlay is the black boxes to make the white boxes appear as borders
		DrawRectangle(317, 7, 390, 90, BLACK);
		DrawRectangle(317, 115, 390, 615, BLACK);
		DrawRectangle(10, GetScreenHeight() - 100, 290, 70, BLACK);
		DrawRectangle(GetScreenWidth() - 300, GetScreenHeight() - 100, 290, 70, BLACK);
		//Text is drawn last
		DrawText("HighScores", (GetScreenWidth() / 2) - 190, 20, 68, RAYWHITE);
		DrawText("Return", 15, GetScreenHeight() - 100, 80, RAYWHITE);
		DrawText("ClearSaves", GetScreenWidth() - 292, GetScreenHeight() - 90, 49, RAYWHITE);
		EndDrawing();
		option = (withinBounds(10, GetScreenHeight() - 100, 300, GetScreenHeight() - 30) * 1) //if in box Return, set option to 1
			+ (withinBounds(GetScreenWidth() - 300, GetScreenHeight() - 100, GetScreenWidth() - 10, GetScreenHeight() - 30) * 2); // if in box Clear Saves, set option to 2
	}
	return option;
}

int Game::loadMenu()
{
	int option = 0;
	while (option == 0)
	{
		BeginDrawing();
		ClearBackground(BLACK);

		DrawRectangle(GetScreenWidth() / 2 - 300, 5, 600, 100, RAYWHITE);
		DrawRectangle(GetScreenWidth() / 2 - 300, 145, 600, 100, RAYWHITE);
		DrawRectangle(GetScreenWidth() / 2 - 300, 265, 600, 100, RAYWHITE);
		DrawRectangle(GetScreenWidth() / 2 - 300, 385, 600, 100, RAYWHITE);
		DrawRectangle(GetScreenWidth() / 2 - 300, 505, 600, 100, RAYWHITE);
		DrawRectangle(10, GetScreenHeight() - 110, 400, 100, RAYWHITE);
		DrawRectangle(GetScreenWidth() - 410, GetScreenHeight() - 110, 400, 100, RAYWHITE);

		DrawRectangle(GetScreenWidth() / 2 - 295, 10, 590, 90, BLACK);
		DrawRectangle(GetScreenWidth() / 2 - 295, 150, 590, 90, BLACK);
		DrawRectangle(GetScreenWidth() / 2 - 295, 270, 590, 90, BLACK);
		DrawRectangle(GetScreenWidth() / 2 - 295, 390, 590, 90, BLACK);
		DrawRectangle(GetScreenWidth() / 2 - 295, 510, 590, 90, BLACK);
		DrawRectangle(15, GetScreenHeight() - 105, 390, 90, BLACK);
		DrawRectangle(GetScreenWidth() - 405, GetScreenHeight() - 105, 390, 90, BLACK);

		DrawText("Save Files", GetScreenWidth() / 2 - 245, 20, 90, RAYWHITE);
		DrawText("Return", 45, GetScreenHeight() - 100, 90, RAYWHITE);
		DrawText("Clear SaveSlot", GetScreenWidth() - 390, GetScreenHeight() - 90, 40, RAYWHITE);

		option = (withinBounds(10, GetScreenHeight() - 110, 410, GetScreenHeight() - 10) * 1)
			+ (withinBounds(GetScreenWidth() - 410, GetScreenHeight() - 110, GetScreenWidth() - 10, GetScreenHeight() - 10) * 2);
		EndDrawing();
	}
	return option;
}


void Game::update(float deltaTime)
{
	if (!m_scenes[m_currentSceneIndex]->getStarted())
		m_scenes[m_currentSceneIndex]->start();

	m_scenes[m_currentSceneIndex]->update(deltaTime);

	if (m_returnB->getButtonClicked())
		setCurrentScene(0);
	if (m_HighScoreB->getButtonClicked())
		setCurrentScene(1);
	if (m_loadB->getButtonClicked())
		setCurrentScene(2);
	if (m_startB->getButtonClicked())
		setCurrentScene(3);
	if (m_exitB->getButtonClicked())
		setGameOver(true);
}

void Game::draw()
{
	BeginDrawing();

	BeginMode2D(*m_camera);
	ClearBackground(BLACK);

	m_scenes[m_currentSceneIndex]->draw();

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
