#pragma once
#include"Square.h"

class Tetris
{
public:
	RenderWindow* app;
	Vector2i mCorePoint, nextCorePoint;
	Square nowSquare, nextSquare, shadowSquare;
	Texture *tTiles;
	Sprite sTiles;
	int role;
	int b7Int;
	int b7array[7];
	int score;
	int Field[STAGE_WIDTH][STAGE_HEIGHT];
	std::vector<int> animationRow;
	float animationCtrValue;
	Clock m_clock;
	float elapsedTime;
	bool isRotate, isHardDrop, isHold;
	bool isOver;
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
	void animatieFunc();
	void shadowFunc();
	void slowLoading();//�ײ�����
	void HardDrop();//Ӳ��
	void Rotate();
	void nextFunc();
	void holdFunc();
	void checkLine();
};

static Square holdSquare;