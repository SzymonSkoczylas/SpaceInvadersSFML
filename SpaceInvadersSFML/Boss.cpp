#include "Headers/Boss.h"
#include "Headers/Global.h"
#include <iostream>
Boss::Boss()
	: x(SCREEN_WIDTH), y(0),life(BOSS_LIFE), direction(1), dead(false), speed(BOSS_BASE_SPEED)
{
}

void Boss::Update()
{
	Movement();
	ClearingDeadBullets();
}

void Boss::Draw(sf::RenderWindow& window)
{
	this->texture.loadFromFile("Images/boss.png");
	this->sprite.setTexture(texture);
	this->sprite.setPosition(x, y);
	window.draw(sprite);
}

void Boss::Shoot(float xpos, float ypos, float angle)
{
	Bullet bullet(xpos, ypos, false);
	bullet.ChangeAngle(angle);
	this->bullets.push_back(bullet);
}

sf::FloatRect Boss::GetHitbox()
{
	return sf::FloatRect(this->x + BOSS_LEFT_SPACE,this->y - BOSS_TOP_SPACE,BOSS_WIDTH *SCREEN_RESIZE,BOSS_HEIGHT*SCREEN_RESIZE);
}

bool Boss::BulletCollision(const sf::FloatRect& other)
{
	return this->GetHitbox().intersects(other);
}

bool Boss::LoseLife()
{
	if (this->life == 1)
	{
		this->dead = true;
		return true;
	}

	if (this->life > 1)
	{
		this->life--;
		return false;
	}
	return false;
}

int Boss::GetScoreValue()
{
	return 10'000;
}

void Boss::ClearingDeadBullets()
{
	this->bullets.erase(remove_if(bullets.begin(), bullets.end(), [](const Bullet& bullet) { return bullet.dead; }), bullets.end());
}

void Boss::Movement()
{
	if (this->direction == 1)
	{
		if (this->x < SCREEN_WIDTH * SCREEN_RESIZE - BOSS_WIDTH * SCREEN_RESIZE * 1.2)
			this->x += BOSS_BASE_SPEED;
		else
			this->direction = -1;
	}
	if (this->direction == -1)
	{
		if (this->x >= 0)
			this->x -= BOSS_BASE_SPEED;
		else
			this->direction = 1;
	}
}
