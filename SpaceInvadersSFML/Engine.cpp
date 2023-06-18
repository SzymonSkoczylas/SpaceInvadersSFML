#include "Headers\Engine.h"


void Engine::Game::CreateWindow()
{
	window.create(sf::VideoMode(SCREEN_WIDTH * SCREEN_RESIZE, SCREEN_HEIGHT * SCREEN_RESIZE), "Space Invaders", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(144);
	window.setVerticalSyncEnabled(true);
}


std::mutex enemiesMutex;
void LoadEnemy(std::vector<Enemy>* enemies, float x, float y, int dir)
{
	char direction = 0;
	if (dir == 0 || dir == 2)
		direction = 1;
	if (dir == 1)
		direction = -1;
	auto enemy = Enemy(x, y, direction);
	std::lock_guard<std::mutex> lock(enemiesMutex);
	enemies->push_back(enemy);
}

void Engine::Game::InitGameMenu()
{
	menu[0].SetText("Play",TEXT_SIZE,sf::Color::Magenta,SCREEN_WIDTH*SCREEN_RESIZE/2 - BASE_SIZE - TEXT_OFFSET_X,SCREEN_HEIGHT*SCREEN_RESIZE/2 - TEXT_OFFSET_Y);
	menu[1].SetText("Scoreboard", TEXT_SIZE, sf::Color::Magenta, SCREEN_WIDTH * SCREEN_RESIZE / 2 - BASE_SIZE - TEXT_OFFSET_X, SCREEN_HEIGHT * SCREEN_RESIZE / 2 + BASE_SIZE * 2 - TEXT_OFFSET_Y);
	menu[2].SetText("Exit", TEXT_SIZE, sf::Color::Magenta, SCREEN_WIDTH * SCREEN_RESIZE / 2 - BASE_SIZE - TEXT_OFFSET_X, SCREEN_HEIGHT * SCREEN_RESIZE / 2 + BASE_SIZE * 4 - TEXT_OFFSET_Y);
}

void Engine::Game::InitLoginMenu()
{
	login_menu[0].SetText("Log in", TEXT_SIZE, sf::Color::Magenta, SCREEN_WIDTH * SCREEN_RESIZE / 2 - BASE_SIZE - TEXT_OFFSET_X, SCREEN_HEIGHT * SCREEN_RESIZE / 2 - TEXT_OFFSET_Y);
	login_menu[1].SetText("Register", TEXT_SIZE, sf::Color::Magenta, SCREEN_WIDTH * SCREEN_RESIZE / 2 - BASE_SIZE - TEXT_OFFSET_X, SCREEN_HEIGHT * SCREEN_RESIZE / 2 + BASE_SIZE * 2 - TEXT_OFFSET_Y);
	login_boxes[0].SetText("Login:", TEXT_SIZE, sf::Color::Magenta, SCREEN_WIDTH * SCREEN_RESIZE / 2 - BASE_SIZE - TEXT_OFFSET_X*3, SCREEN_HEIGHT * SCREEN_RESIZE / 2 - TEXT_OFFSET_Y);
	login_boxes[1].SetText("Password:", TEXT_SIZE, sf::Color::Magenta, SCREEN_WIDTH * SCREEN_RESIZE / 2 - BASE_SIZE - TEXT_OFFSET_X*3, SCREEN_HEIGHT * SCREEN_RESIZE / 2 + BASE_SIZE * 2 - TEXT_OFFSET_Y);
	login_boxes[2].SetText("", TEXT_SIZE, sf::Color::Magenta, SCREEN_WIDTH * SCREEN_RESIZE / 2 - BASE_SIZE - TEXT_OFFSET_X * 1.5, SCREEN_HEIGHT * SCREEN_RESIZE / 2 - TEXT_OFFSET_Y);
	login_boxes[3].SetText("", TEXT_SIZE, sf::Color::Magenta, SCREEN_WIDTH * SCREEN_RESIZE / 2 - BASE_SIZE - TEXT_OFFSET_X * 0.6 , SCREEN_HEIGHT * SCREEN_RESIZE / 2 + BASE_SIZE * 2 - TEXT_OFFSET_Y);
}

void Engine::Game::InitScoreboard()
{
	std::ifstream score_file("Data/scoreboard.txt");
	std::string line, name;
	int score;
	while (std::getline(score_file, line))
	{
		std::stringstream ss;
		ss << line;
		ss >> name >> score;
		scoreboard.AddToScoreboard(name,score);
	}
}

void Engine::Game::InitTextes()
{

	score1.setContent("Score: ");
	score2.setContent(std::to_string(current_score));
	score2.SetText(score2.getContent(), TEXT_SIZE / 2, sf::Color::Magenta,
		SCREEN_WIDTH * SCREEN_RESIZE / 3 - BASE_SIZE + TEXT_OFFSET_X * 1.5, 20);
	life1.setContent("Life: ");
	life2.setContent(std::to_string(player.getLife()));
	life2.SetText(life2.getContent(), TEXT_SIZE / 2, sf::Color::Magenta,
		SCREEN_WIDTH * SCREEN_RESIZE / 2 + TEXT_OFFSET_X, 20);
	score1.SetText(score1.getContent(), TEXT_SIZE / 2, sf::Color::Magenta,
		SCREEN_WIDTH * SCREEN_RESIZE / 3, 20);
	life1.SetText(life1.getContent(), TEXT_SIZE / 2, sf::Color::Magenta,
		SCREEN_WIDTH * SCREEN_RESIZE / 2, 20);


	error.SetText("Something went wrong!\nTry Again", TEXT_SIZE, sf::Color::Magenta,
		SCREEN_WIDTH * SCREEN_RESIZE / 2 - BASE_SIZE - TEXT_OFFSET_X, SCREEN_HEIGHT * SCREEN_RESIZE / 2 - TEXT_OFFSET_Y);


	losetext.setContent("\t\tGame Over!\n Press space or enter to continue");
	losetext.SetText(losetext.getContent(), TEXT_SIZE, sf::Color::Magenta,
		SCREEN_WIDTH * SCREEN_RESIZE / 3 - BASE_SIZE - TEXT_OFFSET_X, SCREEN_HEIGHT * SCREEN_RESIZE / 2 - TEXT_OFFSET_Y);

}

void Engine::Game::UpdateBackground()
{
	if (background2.background_sprite.getPosition().y < 720)
		background2.background_sprite.move(0, 1.f);
	else
		background2.background_sprite.setPosition(0, -720);

	if (background1.background_sprite.getPosition().y < 720)
		background1.background_sprite.move(0, 1.f);
	else
		background1.background_sprite.setPosition(0, -720);
}

void Engine::Game::GameOver()
{
	status = LOSEBOARD;
	scoreboard.AddToScoreboard(username, current_score);
	scoreboard.SaveScoreboard();
	for (auto& enemy : enemies)
		enemy.dead = true;
	stage = 0;
	player.setLife(3);
}

void Engine::Game::GameFinished()
{
	using namespace std::chrono_literals;
	status = WINBOARD;
	current_score += player.getLife() * BONUS_SCORE_PER_LIFE;
	scoreboard.AddToScoreboard(username, current_score);
	scoreboard.SaveScoreboard();
	for (auto& enemy : enemies)
		enemy.dead = true;
	stage = 0;
	player.setLife(3);
	std::this_thread::sleep_for(0.5s);
}

void Engine::Game::Login()
{
	status = LOGGING;
}

void Engine::Game::Register()
{
	status = REGISTERING;
}

bool Engine::Game::CheckRegister()
{
	std::regex regLogin(".{5}");
	std::regex regPassword("^(?=.*[a-z])(?=.*[A-Z])(?=.*[^a-zA-Z0-9]).{8,}$");
	std::string login = login_boxes[2].getContent();
	std::string password = login_boxes[3].getContent();
	if (std::regex_match(login, regLogin) && std::regex_match(password, regPassword))
	{
		bool isUserInDatabase = false;
		std::ifstream file("Data/users.txt");
		std::string line;
		while (std::getline(file, line))
		{
			std::stringstream ss;
			ss << line;
			ss >> username;
			if (username == login)
				return false;
		}
		username = login;
		std::ofstream user_file("Data/users.txt", std::ios_base::app | std::ios_base::out);
		user_file << login << " " << password << "\n";
		return true;
	}
	else
		return false;
}

bool Engine::Game::CheckLogin()
{
	std::string login = login_boxes[2].getContent();
	std::string password = login_boxes[3].getContent();
	std::ifstream file("Data/users.txt");
	std::string line;
	std::string passwordS{};
	while (std::getline(file, line))
	{
		std::stringstream ss;
		ss << line;
		ss >> username >> passwordS;
		if (username == login && password == passwordS)
		{
			username = login;
			return true;
		}
	}
	return false;
}

void Engine::Game::ClearUsernameAndPassword()
{
	login_boxes[2].setContent("");
	login_boxes[3].setContent("");
	login_boxes[2].UpdateText();
	login_boxes[3].UpdateText();
}

void Engine::Game::MoveToNextStage()
{
	stage++;
	end_of_stage = true;
}

void Engine::Game::EnterUsername(char input)
{
	if (input > 32 && input < 128)
	{
		std::string temp = login_boxes[2].getContent();
		temp += input;
		login_boxes[2].setContent(temp);
		login_boxes[2].UpdateText();
	}
	else if(input == 0x08)
	{
		if (login_boxes[2].getContent().size() != 0)
		{
			login_boxes[2].setContent(login_boxes[2].getContent().substr(0, login_boxes[2].getContent().size()-1));
			login_boxes[2].UpdateText();
		}
	}
}

void Engine::Game::EnterPassword(char input)
{
	if (input > 32 && input < 128)
	{
		std::string temp = login_boxes[3].getContent();
		temp += input;
		login_boxes[3].setContent(temp);
		login_boxes[3].UpdateText();
	}
	else if (input == 0x08)
	{
		if (login_boxes[3].getContent().size() != 0)
		{
			login_boxes[3].setContent(login_boxes[3].getContent().substr(0, login_boxes[3].getContent().size() - 1));
			login_boxes[3].UpdateText();
		}
	}
}

void Engine::Game::EnemyShooting()
{
	if (Enemy::reload == 0.0)
	{
		Enemy::reload = ENEMY_RELOAD_SPEED;
		Enemy::start_reloading = std::chrono::high_resolution_clock::now();
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist(0, enemies.size()-1);
		enemies[dist(rng)].Shoot();
	}
	else
	{
		Enemy::stop_reloading = std::chrono::high_resolution_clock::now();
		Enemy::time_of_reloading = Enemy::stop_reloading - Enemy::start_reloading;
		if (Enemy::time_of_reloading.count() > Enemy::reload)
			Enemy::reload = 0.0;
	}
}

void Engine::Game::BossShooting()
{
	if (Boss::reload == 0.0)
	{	
		Boss::reload = BOSS_RELOAD_SPEED;
		Boss::start_reloading = std::chrono::high_resolution_clock::now();
		boss[0].Shoot(boss[0].x, boss[0].y+BOSS_HEIGHT,0.f);
		boss[0].Shoot(boss[0].x + BOSS_WIDTH * SCREEN_RESIZE / 2, boss[0].y + BOSS_HEIGHT, 0.f);
		boss[0].Shoot(boss[0].x + BOSS_WIDTH * SCREEN_RESIZE - BASE_SIZE, boss[0].y + BOSS_HEIGHT, 0.f);
	}
	else
	{
		Boss::stop_reloading = std::chrono::high_resolution_clock::now();
		Boss::time_of_reloading = Boss::stop_reloading - Boss::start_reloading;
		if (Boss::time_of_reloading.count() > Boss::reload)
			Boss::reload = 0.0;
	}
}

void Engine::Game::ClearDeadEnemies()
{
	enemies.erase(remove_if(enemies.begin(), enemies.end(), [](const Enemy& enemy) { return enemy.dead; }), enemies.end());
}

void Engine::Game::LoadEnemies(short current_stage)
{
	end_of_stage = false;
	futures.clear();
	if (stage < 4)
	{
		for (int j = 0; j < current_stage; j++)
			for (int i = 0; i < ENEMIES_IN_ROW; i++)
				futures.push_back(std::async(std::launch::async, LoadEnemy, &enemies, ENEMY_SPACING_X * i, ENEMY_SPACING_Y * j + BASE_SIZE,j));

		for (auto& future : futures)
			future.get();
	}
	if (stage == 4)
	{
		boss_phase = true;
	}
}



void Engine::Game::Render()
{
	using namespace std::string_literals;

	window.clear();
	window.draw(background1.background_sprite); // zaladowanie tla
	window.draw(background2.background_sprite); // zaladowanie tla
	if (status == WINBOARD)
	{
		wintext.setContent("\t\t\t\tYou made it!\n\t\tYour score : " + std::to_string(current_score) +
			"\nPress space or enter to continue");
		wintext.SetText(wintext.getContent(), TEXT_SIZE, sf::Color::Magenta,
			SCREEN_WIDTH * SCREEN_RESIZE / 3 - BASE_SIZE - TEXT_OFFSET_X, SCREEN_HEIGHT * SCREEN_RESIZE / 2 - TEXT_OFFSET_Y);
		window.draw(wintext.getText());
	}
	if (status == LOSEBOARD)
	{
		window.draw(losetext.getText());
	}
	if (status == SCOREBOARD)
	{
		std::vector<Score> scores;
		for (auto& score : scoreboard.scores)
			scores.push_back(score);
		short loop_range = MAX_SCOREBOARD_ENTRIES * (scoreboard_page + 1);
		if (loop_range > scores.size())
			loop_range = scores.size();
		for (int i = scoreboard_page; i < loop_range; i++)
		{
			UI::MyText score;
			std::string entry = std::to_string(i + 1) + '.' + scores[i].username +
				" .......................................... " + std::to_string(scores[i].score);
			score.SetText(entry, TEXT_SIZE, sf::Color::Magenta,
				20, 20 + SCORES_SPACING * i - SCORES_SPACING * MAX_SCOREBOARD_ENTRIES * scoreboard_page);
			window.draw(score.getText());
		}
	}
	if (status == NOT_LOGGED)
	{
		window.draw(error.getText());
	}
	if (status == REGISTERING)
	{
		for (auto& item : login_boxes)
			window.draw(item.getText());
	}
	if (status == LOGGING)
	{
		for (auto& item : login_boxes)
			window.draw(item.getText());
	}
	if (status == LOGIN_REGISTER)
	{
		for (auto& item : login_menu)
			window.draw(item.getText());
	}
	if (status == GAME_MENU)
	{
		for (auto& item : menu)
			window.draw(item.getText());
	}
	if (status == PLAYING)
	{
		window.draw(score1.getText());
		window.draw(score2.getText());
		window.draw(life1.getText());
		window.draw(life2.getText());
		player.Draw(window);

		if (!boss_phase)
		{
			for (auto& enemy : enemies)
			{
				enemy.Draw(window);
				for (auto& e_bullet : enemy.bullets)
					e_bullet.Draw(window);
			}
		}
		if (boss_phase)
		{
			boss[0].Draw(window);
			for (auto& bullet : boss[0].bullets)
				bullet.Draw(window);
		}
		for (auto& bullet : player.bullets)
			bullet.Draw(window);

	}

	window.display();
}

void Engine::Game::Update()
{
	UpdateBackground();
	if (status == REGISTERING)
	{
		for (int i = 0; i < login_boxes.size(); i++)
		{
			if (i == current_login_boxes_item)
				login_boxes[i].Underline();
			else
				login_boxes[i].Default();
		}
	}
	if (status == LOGGING)
	{
		for (int i = 0; i < login_boxes.size(); i++)
		{
			if (i == current_login_boxes_item)
				login_boxes[i].Underline();
			else
				login_boxes[i].Default();
		}
	}
	if (status == LOGIN_REGISTER)
	{
		for (int i = 0; i < login_menu.size(); i++)
		{
			if (i == current_login_menu_item)
				login_menu[i].Underline();
			else
				login_menu[i].Default();
		}
	}
	if (status == GAME_MENU)
	{
		for (int i = 0; i < menu.size(); i++)
		{
			if (i == current_menu_item)
				menu[i].Underline();
			else
				menu[i].Default();
		}

	}
	if (status == PLAYING)
	{
		player.Update();

		for (auto& bullet : player.bullets)
			bullet.Update();
		if (!boss_phase)
		{
			for (auto& enemy : enemies)
			{
				enemy.Update();
				if (enemy.GetHitbox().intersects(player.GetHitbox()))
					GameOver();
				for (auto& bullet : player.bullets)
					if (enemy.BulletCollision(bullet.GetHitbox()))
					{
						if (enemy.LoseLife())
						{
							current_score += enemy.GetScoreValue();
							score2.setContent(std::to_string(current_score));
							score2.SetText(score2.getContent(), TEXT_SIZE / 2, sf::Color::Magenta,
								SCREEN_WIDTH * SCREEN_RESIZE / 3 - BASE_SIZE + TEXT_OFFSET_X * 1.5, 20);
						}
						bullet.dead = true;
					}
				for (auto& bullet : enemy.bullets)
				{
					bullet.Update();
					if (player.BulletCollision(bullet.GetHitbox()))
					{
						bullet.dead = true;
						if (player.LoseLife())
							GameOver();

						life2.setContent(std::to_string(player.getLife()));
						life2.SetText(life2.getContent(), TEXT_SIZE / 2, sf::Color::Magenta,
							SCREEN_WIDTH * SCREEN_RESIZE / 2 + TEXT_OFFSET_X, 20);
					}
				}
			}
		}
		if (boss_phase)
		{
			boss[0].Update();
			for (auto& bullet : player.bullets)
			{
				if (boss[0].BulletCollision(bullet.GetHitbox()))
				{
					if (boss[0].LoseLife())
					{
						current_score += boss[0].GetScoreValue();
						score2.setContent(std::to_string(current_score));
						score2.SetText(score2.getContent(), TEXT_SIZE / 2, sf::Color::Magenta,
							SCREEN_WIDTH * SCREEN_RESIZE / 3 - BASE_SIZE + TEXT_OFFSET_X * 1.5, 20);
					}
					bullet.dead = true;
				}
			}
			for (auto& bullet : boss[0].bullets)
			{
				bullet.Update();
				if(player.BulletCollision(bullet.GetHitbox()))
				{
					bullet.dead = true;
					if (player.LoseLife())
						GameOver();
					life2.setContent(std::to_string(player.getLife()));
					life2.SetText(life2.getContent(), TEXT_SIZE / 2, sf::Color::Magenta,
						SCREEN_WIDTH * SCREEN_RESIZE / 2 + TEXT_OFFSET_X, 20);
				}
			}
		}
	}
}

void Engine::Game::LoadBackground()
{
	background1.background_texture.loadFromFile("Images/space.png");
	background1.background_sprite.setTexture(background1.background_texture);
	background1.background_sprite.setScale(2.5f, 2.f);
	background2.background_texture.loadFromFile("Images/space.png");
	background2.background_sprite.setTexture(background2.background_texture);
	background2.background_sprite.setPosition(0, -720);
	background2.x = 0.0;
	background2.y = -720.0;
	background2.background_sprite.setScale(2.5f, 2.f);
}

void Engine::Game::AppPolling()
{
	using namespace std::literals::chrono_literals;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (status == LOGGING)
			{
				if (event.type == sf::Event::TextEntered)
				{ 
					if (current_login_boxes_item == 0)
					{
						EnterUsername(static_cast<char>(event.text.unicode));
					}
					if (current_login_boxes_item == 1)
					{
						EnterPassword(static_cast<char>(event.text.unicode));
					}
				}
			}
			if (status == REGISTERING)
			{
				if (event.type == sf::Event::TextEntered)
				{
					if (current_login_boxes_item == 0)
						EnterUsername(static_cast<char>(event.text.unicode));
					if (current_login_boxes_item == 1)
						EnterPassword(static_cast<char>(event.text.unicode));
				}
			}
		}

		if (status == PLAYING)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				player.Shoot();

			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				//window.close();


			if (!boss_phase)
			{
				if (end_of_stage)
					LoadEnemies(stage);
				ClearDeadEnemies();
				if (enemies.empty())
					MoveToNextStage();
				if (!enemies.empty())
					EnemyShooting();
			}
			if (boss_phase)
			{
				if (boss[0].dead)
					GameFinished();
				BossShooting();
			}
		}
		else if (status == GAME_MENU)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (current_menu_item > 0)
				{
					current_menu_item--;
					std::this_thread::sleep_for(0.2s);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (current_menu_item < 2)
				{
					current_menu_item++;
					std::this_thread::sleep_for(0.2s);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (current_menu_item == 0)
				{
					status = PLAYING;
					std::this_thread::sleep_for(0.2s);
				}
				if (current_menu_item == 1)
				{
					status = SCOREBOARD;
					std::this_thread::sleep_for(0.2s);
				}
				if (current_menu_item == 2)
					window.close();
			}
		}
		else if (status == LOGIN_REGISTER)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (current_login_menu_item > 0)
				{
					current_login_menu_item--;
					std::this_thread::sleep_for(0.2s);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (current_login_menu_item < 1)
				{
					current_login_menu_item++;
					std::this_thread::sleep_for(0.2s);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (current_login_menu_item == 0)
				{
					Login();
					std::this_thread::sleep_for(0.2s);
				}
				if (current_login_menu_item == 1)
				{
					Register();
					std::this_thread::sleep_for(0.2s);
				}
			}
		}
		else if (status == LOGGING || status == REGISTERING)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (current_login_boxes_item > 0)
				{
					current_login_boxes_item--;
					std::this_thread::sleep_for(0.2s);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (current_login_boxes_item < 1)
				{
					current_login_boxes_item++;
					std::this_thread::sleep_for(0.2s);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				if(status == REGISTERING)
				{ 
					if (CheckRegister())
					{
						status = GAME_MENU;
						std::this_thread::sleep_for(0.2s);
					}
					else
					{
						status = NOT_LOGGED;
						ClearUsernameAndPassword();
						std::this_thread::sleep_for(0.2s);
					}
				}
				else
				{
					if (CheckLogin())
					{
						status = GAME_MENU;
						username = login_boxes[2].getContent();
						std::this_thread::sleep_for(0.2s);
					}
					else
					{
						status = NOT_LOGGED;
						ClearUsernameAndPassword();
						std::this_thread::sleep_for(0.2s);
					}
				}
			}
		}
		else if (status == NOT_LOGGED)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				status = LOGIN_REGISTER;
				std::this_thread::sleep_for(0.2s);
			}
		}
		else if (status == SCOREBOARD)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				status = GAME_MENU;
				std::this_thread::sleep_for(0.2s);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (scoreboard_page > 0)
				{
					scoreboard_page--;
					std::this_thread::sleep_for(0.2s);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				short max_scoreboard_pages = scoreboard.scores.size() / 9;
				if (scoreboard_page < max_scoreboard_pages)
				{
					scoreboard_page++;
					std::this_thread::sleep_for(0.2s);
				}
			}
		}
		else if (status == LOSEBOARD || status == WINBOARD)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				boss.clear();
				boss.push_back(Boss());
				stage = 0;
				status = GAME_MENU;
				current_score = 0;
				std::this_thread::sleep_for(0.1s);
			}
		}
		
		Update();

		Render();
	}
}

void Engine::Game::InitStage()
{
	LoadBackground();
	status = LOGIN_REGISTER;
	stage = 0;
	current_menu_item = 0;
	current_login_menu_item = 0;
	current_login_boxes_item = 0;
	scoreboard_page = 0;
	current_score = 0;
	boss_phase = false;
	end_of_stage = true;
	boss.push_back(Boss());
}
