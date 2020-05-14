#pragma once
#include"Def.h"

class Square
{
public:
	Square();
	Square(const Square& e);
	void setColor(int color);
	void setShape(int shape);
	void setPosition(int x, int y);
	void Rotate();
	int getColor();
	int getShape();
	int getMid();
	int getWidth();
	int getHeight();
	Vector2i getSquarePosition(int i);
	Vector2i getPosition();
protected:
	int color;
	int shape;
	int mid;
	int width, height;
	Vector2i Pos;
	Vector2i squarePos[4];
private:
	Vector2i squareShape[4];
	void updata();
};