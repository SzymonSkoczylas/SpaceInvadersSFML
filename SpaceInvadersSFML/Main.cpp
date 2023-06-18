#include "Headers\Engine.h"

using namespace Engine;

int main()
{
	Game::InitTextes();
	Game::InitStage();
	Game::InitLoginMenu();
	Game::InitGameMenu();
	Game::InitScoreboard();
	Game::CreateWindow();
	Game::AppPolling();
}