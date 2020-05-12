#pragma once
#include"Def.h"

class Tetris
{
public:
	RenderWindow* app;
	Vector2i mCornPoint, nextSquareCornPoint;
	Vector2i currentSquare[4], nextSquare[4], tempSquare[4];
	Texture *tTiles;
	Sprite sTiles;
	int role;
	int list_num;
	int list[7];
	int score;
	int colorNum, nextcolorNum, tempcolorNum;
	int currentShapeNum, nextShapeNum, tempShapeNum;
	int Field[STAGE_HEIGHT][STAGE_WIDTH];
	bool isRotate, isHardDrop;
	float timer, delay;
	int Figures[7][4] =
	{
		3,5,1,7, // I
		4,5,2,7, // S
		4,5,3,6, // Z
		5,3,4,7, // T
		3,5,2,7, // L
		7,5,3,6, // J
		2,3,4,5, // O
	};
	void Initial(RenderWindow* app, Texture* tex);
	void Input(Event& e);
	void Start();
	void Update();
	void Draw();
	bool hitTest();
	int List();
	void Move_x(int dx);
	void Move_y();
	void slowLoading();
	void HardDrop();
	void Rotate();
	void checkLine();
};

