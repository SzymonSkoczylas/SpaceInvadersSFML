#ifndef ENGINE_H
#define ENGINE_H

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Network.hpp>
#include <SFML\Audio.hpp>


#include <string>
#include <chrono>
#include <future>
#include <array>
#include <sstream>
#include <fstream>
#include <regex>

#include "Scoreboard.h"
#include "Player.h"
#include "Global.h"
#include "UI.h"
#include "Enemy.h"
#include "Boss.h"

struct Background {
	float x, y;
	sf::Sprite  background_sprite;
	sf::Texture background_texture;
};

namespace Engine {
	static class Game {
	public:
		static void CreateWindow();
		static void AppPolling();
		static void InitStage();
		static void InitGameMenu();
		static void InitLoginMenu();
		static void InitScoreboard();
		static void InitTextes();
	private:
		static inline std::string username;
		static inline enum game_status {	
			LOGIN_REGISTER = 0, LOGGING = 1, REGISTERING = 2, GAME_MENU=3,
			PLAYING = 4, NOT_LOGGED = 5, SCOREBOARD =6, LOSEBOARD =7, WINBOARD =8} status;
		static inline UI::MyText score1;
		static inline UI::MyText score2;
		static inline UI::MyText life1;
		static inline UI::MyText life2;
		static inline UI::MyText error;
		static inline UI::MyText losetext;
		static inline UI::MyText wintext;
		static inline std::array<UI::MyText,3> menu;
		static inline std::array<UI::MyText, 2> login_menu;
		static inline std::array<UI::MyText, 4> login_boxes;
		static inline int current_menu_item;
		static inline int current_login_menu_item;
		static inline int current_login_boxes_item;
		static inline sf::Event event;
		static inline sf::RenderWindow window;
		static inline short stage;
		static inline short scoreboard_page;
		static inline int current_score;
		static inline bool end_of_stage;
		static inline bool boss_phase;
		static inline unsigned char rows_of_enemies;
		static inline std::vector<Enemy> enemies;
		static inline std::vector<std::future<void>> futures;
		static inline std::vector<Boss> boss;
		static inline Player player;
		static inline Scoreboard scoreboard;
		static inline Background background1;
		static inline Background background2;
		static inline sf::Sprite  menu_sprite;
		static inline sf::Texture menu_texture;
		static inline sf::Texture font_texture;
	private:
		static void UpdateBackground();
		static void GameOver();
		static void GameFinished();
		static void Login();
		static void Register();
		static bool CheckRegister();
		static bool CheckLogin();
		static void ClearUsernameAndPassword();
		static void MoveToNextStage();
		static void EnterUsername(char input);
		static void EnterPassword(char input);
		static void EnemyShooting();
		static void BossShooting();
		static void ClearDeadEnemies();
		static void LoadEnemies(short current_stage);
		static void Render();
		static void Update();
		static void LoadBackground();
	};
}
#endif