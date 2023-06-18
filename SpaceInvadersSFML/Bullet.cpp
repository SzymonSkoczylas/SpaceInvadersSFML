#include "Headers\Bullet.h"
#include "Headers\Global.h"

void Bullet::Draw(sf::RenderWindow& window)
{
	if(isPlayer)
		this->texture.loadFromFile("Images/bulletP.png");
	else
		this->texture.loadFromFile("Images/bulletE.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(0.3f, 0.6f);
	this->sprite.setPosition(x, y);
	window.draw(this->sprite);
}

void Bullet::ChangeAngle(float angle)
{
	this->sprite.setRotation(angle);
}

void Bullet::Update()
{
	if(isPlayer)
	{
		if (this->y < (0 - BASE_SIZE))
			this->y -= this->speed;
		else
			this->dead = true;
	}
	else
	{
		if (this->y < SCREEN_HEIGHT * 4)
			this->y += this->speed;
		else
			this->dead = true;
	}
}

sf::FloatRect Bullet::GetHitbox()
{
	return sf::FloatRect(this->x,this->y, BULLET_WIDTH, BULLET_HEIGHT);
}

Bullet::Bullet(unsigned int xx, unsigned int yy, bool cond) :
	x(xx + BULLET_WIDTH * 4),
	y(yy - BULLET_HEIGHT),
	dead(false),
	isPlayer(cond)
{
	if (isPlayer)
		this->speed = PLAYER_BULLET_BASE_SPEED;
	else
	{
		this->speed = ENEMY_BULLET_BASE_SPEED;
		x += BULLET_WIDTH * 4;
		y += BULLET_HEIGHT * 1.5;
	}
}