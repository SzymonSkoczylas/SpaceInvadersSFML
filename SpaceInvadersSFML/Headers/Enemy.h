#ifndef ENEMY_H
#define ENEMY_H

#include <chrono>
#include <vector>
#include <random>
#include "Bullet.h"

class Enemy{
public:	
	Enemy(float X, float Y, char dir);//funkcja odpowiadajaca za rysowanie modelu statku gracza
	void Update();
	void Draw(sf::RenderWindow& window);
	void Shoot();
	sf::FloatRect GetHitbox();
	bool BulletCollision(const sf::FloatRect& other);
	bool LoseLife();
	int GetScoreValue();
public:
	static inline float reload;
	static inline float move_reload;
	static inline std::chrono::time_point<std::chrono::steady_clock> start_reloading, stop_reloading;
	static inline std::chrono::duration<double> time_of_reloading;
	std::vector<Bullet> bullets;
	bool dead; // zmienna informujaca o tym, czy gracz umarl
	char direction;
private:
	void ClearingDeadBullets();
	void Movement();
	void RandomizeBody();
private:
	float next_row;
	short life;
	int score_value;
	sf::Sprite sprite; //sprite dla modelu
	sf::Texture texture; // tekstura modelu
	float x; // koordynat x
	float y; // koordynat y
	unsigned char speed; // predkosc gracza
	std::string body;
};

#endif 