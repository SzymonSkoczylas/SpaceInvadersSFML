#ifndef BOSS_H
#define BOSS_H

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Network.hpp>
#include <SFML\Audio.hpp>

#include <vector>
#include <algorithm>
#include <chrono>
#include <future>
#include "Headers/Bullet.h"
#include "Bullet.h"
#include "Global.h"


class Boss {
public:
	Boss();
	void Update();
	void Draw(sf::RenderWindow& window);
	void Shoot(float xpos, float ypos, float angle);
	sf::FloatRect GetHitbox();
	bool BulletCollision(const sf::FloatRect& other);
	bool LoseLife();
	int GetScoreValue();
	void Revive() { this->life = BOSS_LIFE; }
public:
	static inline float reload;
	static inline float series_reload;
	static inline std::chrono::time_point<std::chrono::steady_clock> start_reloading, stop_reloading;
	static inline std::chrono::duration<double> time_of_reloading;
	static inline std::chrono::time_point<std::chrono::steady_clock> series_start_reloading, series_stop_reloading;
	static inline std::chrono::duration<double> series_time_of_reloading;
	std::vector<Bullet> bullets;
	bool dead; // zmienna informujaca o tym, czy gracz umarl
	char direction;
	float x; // koordynat x
	float y; // koordynat y
private:
	void ClearingDeadBullets();
	void Movement();
private:
	short life;
	int score_value;
	sf::Sprite sprite; //sprite dla modelu
	sf::Texture texture; // tekstura modelu
	unsigned char speed; // predkosc gracza
};

#endif