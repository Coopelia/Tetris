#pragma once
#include"Square.h"

class Tetris
{
public:
	RenderWindow* app;
	Vector2i mCorePoint, nextCorePoint;
	Square nowSquare, nextSquare;
	Texture *tTiles;
	Sprite sTiles;
	int role;
	int b7Int;
	int b7array[7];
	int score;
	int Field[STAGE_WIDTH][STAGE_HEIGHT];
	bool isRotate, isHardDrop;
	float timer, delay;
	void Initial(RenderWindow* app, Texture* tex);
	void Input(Event& e);
	void Start();
	void Update();
	void Draw();
	bool isHit();
	int Bag7();
	void Move_x(int dx);
	void Move_y();
	void HardDrop();//Ó²½µ
	void Rotate();
	void checkLine();
};

