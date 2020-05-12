#pragma once
#include "Tetris.h"

class Game
{
public:
	Game();
	~Game();
	RenderWindow* app;
	Tetris player1, player2;
	Clock clock;
	bool gameOver, gameQuit;
	int imgSetNo;
	Texture tBackground, tTiles, tFrame, tCover;
	Sprite	sBackground, sTiles, sFrame, sCover;
	Font font;
	Text text;
	void Initial();
	void LoadMediaData();
	void ShowText();
	void Input();
	void Start();
	void Update();
	void Draw();
	void Run();
};

