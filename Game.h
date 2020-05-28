#pragma once
#include"Button.h"
#include "Tetris.h"

class Game
{
public:
	Game();
	~Game();
	RenderWindow* app;
	Tetris player1, player2;
	Clock clock;
	bool gameOver, gameQuit, gameBegin, gamePause;
	int imgSetNo;
	Texture tBackground, tTiles, tFrame, tCover;
	Sprite	sBackground, sTiles, sFrame, sCover;
	Font font;
	Text text;
	Button bt_start, bt_pause;
	void Initial();
	void LoadMediaData();
	void ShowText();
	void Input();
	void Start();
	void Update();
	void Draw();
	void Run();
};

