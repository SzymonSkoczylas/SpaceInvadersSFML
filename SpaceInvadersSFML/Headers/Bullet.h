#ifndef BULLET_H
#define BULLET_H

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Network.hpp>
#include <SFML\Audio.hpp>

class Bullet {
public:
	void Draw(sf::RenderWindow& window);
	void Update();
	Bullet(unsigned int xx, unsigned int yy, bool cond = true);
	Bullet() = delete;
	sf::FloatRect GetHitbox();
	void ChangeAngle(float angle);
public:
	bool dead;
private:
	bool isPlayer;
	sf::Sprite sprite; //sprite dla modelu
	sf::Texture texture; // tekstura modelu
	unsigned int x; // koordynat x
	unsigned int y; // koordynat y
	unsigned char speed; // predkosc pocisku
};

#endif 