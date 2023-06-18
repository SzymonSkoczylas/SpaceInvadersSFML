#include "Headers\Enemy.h"
#include "Headers\Global.h"

#include <string>

const std::string PATH_RED    = "Images/enemy_red.png";
const std::string PATH_YELLOW = "Images/enemy_yellow.png";

void Enemy::Update()
{
	Movement();
	ClearingDeadBullets();
}

void Enemy::Draw(sf::RenderWindow& window)
{
	this->texture.loadFromFile(this->body);
	this->sprite.setTexture(texture);
	this->sprite.setPosition(x, y);
	window.draw(sprite);
}

void Enemy::Shoot()
{
	this->bullets.push_back(Bullet(this->x, this->y, false));
}

sf::FloatRect Enemy::GetHitbox()
{
	return sf::FloatRect(this->x, this->y, ENEMY_WIDTH, ENEMY_HEIGHT);
}

void Enemy::ClearingDeadBullets()
{
	this->bullets.erase(remove_if(bullets.begin(), bullets.end(), [](const Bullet& bullet) { return bullet.dead; }), bullets.end());
}

void Enemy::Movement()
{
	if (this->direction == 1)
	{
		if (this->x < SCREEN_WIDTH * SCREEN_RESIZE - ENEMY_WIDTH - BASE_SIZE)
		{
			next_row = this->y + ENEMY_SPACING_Y;
			this->x += ENEMY_BASE_SPEED;
		}
		else if (this->y < next_row)
			this->y += ENEMY_BASE_SPEED;
		else
			this->direction = -1;
	}
	if (this->direction == -1)
	{
		if (this->x >= 0)
		{
			next_row = this->y + ENEMY_SPACING_Y;
			this->x -= ENEMY_BASE_SPEED;
		}
		else if(this->y < next_row)
			this->y += ENEMY_BASE_SPEED;
		else
			this->direction = 1;
	}
}

void Enemy::RandomizeBody()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 1000);
	if (dist(rng) < 200)
	{
		this->body = PATH_YELLOW;
		life = 2;
		score_value = 400;
	}
	else
	{
		this->body = PATH_RED;
		life = 1;
		score_value = 200;
	}
}

bool Enemy::BulletCollision(const sf::FloatRect& other)
{
	return this->GetHitbox().intersects(other);
}

bool Enemy::LoseLife()
{
	if (this->life == 1)
	{
		this->dead = true;
		return true;
	}

	if (this->life == 2)
	{
		this->body = PATH_RED;
		this->texture.loadFromFile(this->body);
		this->sprite.setTexture(texture);
		this->life = 1;
		return false;
	}
	return false;
}

int Enemy::GetScoreValue()
{
	return this->score_value;
}


Enemy::Enemy(float X, float Y, char dir) :
	x(X), y(Y),direction(dir), dead(false), speed(ENEMY_BASE_SPEED)
{
	RandomizeBody();
}


