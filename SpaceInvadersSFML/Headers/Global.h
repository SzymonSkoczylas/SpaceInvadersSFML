#ifndef GLOBAL_H
#define GLOBAL_H
//Tutaj przechowywane sa zmienne stale 

//Bazowa wielkosc pomocna do ustawiania obiektow
constexpr unsigned char BASE_SIZE = 60;

//Player
constexpr unsigned char PLAYER_BASE_SPEED = 8;
constexpr unsigned char PLAYER_BULLET_BASE_SPEED = 6;
constexpr double		PLAYER_RELOAD_SPEED = 0.5;
constexpr unsigned char PLAYER_WIDTH = 90;
constexpr unsigned char PLAYER_HEIGHT = 80;
constexpr unsigned int  BONUS_SCORE_PER_LIFE = 5000;

//Boss
constexpr float			BOSS_BASE_SPEED = 2.5f;
constexpr double		BOSS_RELOAD_SPEED = 0.5f;
constexpr unsigned char BOSS_BULLET_BASE_SPEED = 5;
constexpr unsigned char BOSS_WIDTH = 630;
constexpr unsigned char BOSS_HEIGHT = 330;
constexpr unsigned char BOSS_LEFT_SPACE = 20;
constexpr unsigned char BOSS_TOP_SPACE = 30;
constexpr unsigned char BOSS_LIFE = 10;
//Enemy
constexpr float			ENEMY_BASE_SPEED = 0.5f;
constexpr double		ENEMY_RELOAD_SPEED = 1.0;
constexpr unsigned char ENEMY_SPACING_X = 100;
constexpr unsigned char ENEMY_SPACING_Y = 80;
constexpr unsigned char ENEMY_BULLET_BASE_SPEED = 4;
constexpr unsigned char ENEMY_WIDTH = 80;
constexpr unsigned char ENEMY_HEIGHT = 60;
constexpr unsigned char ENEMIES_IN_ROW = 12;

//Bullet
constexpr unsigned char BULLET_WIDTH  = 5;
constexpr unsigned char BULLET_HEIGHT = 60;

//Text
constexpr unsigned char TEXT_SIZE = 60;
constexpr unsigned char TEXT_OFFSET_Y = 140;
constexpr unsigned char TEXT_OFFSET_X = 100;
constexpr unsigned char SCORES_SPACING = 80;
constexpr unsigned char MAX_SCOREBOARD_ENTRIES = 9;
//Screen
constexpr unsigned short SCREEN_HEIGHT = 180;
constexpr unsigned short SCREEN_WIDTH = 320;
constexpr unsigned char  SCREEN_RESIZE = 4;

#endif 