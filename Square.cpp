#include"Square.h"

Square::Square()
{
	this->color = 0;
	this->shape = 0;
	this->mid = 0;
	this->Pos = { 0,0 };
	this->width = 0;
	this->height = 0;
	memset(this->squareShape, 0, sizeof(squareShape));
	memset(this->squarePos, 0, sizeof(squarePos));
}

Square::Square(const Square& e)
{
	this->color = e.color;
	this->shape = e.shape;
	this->mid = e.mid;
	this->Pos = e.Pos;
	this->width = e.width;
	this->height = e.height;
	for (int i = 0; i < 4; i++)
	{
		this->squarePos[i] = e.squarePos[i];
		this->squareShape[i] = e.squareShape[i];
	}
}

int Square::getColor()
{
	return this->color;
}

int Square::getShape()
{
	return this->shape;
}

int Square::getMid()
{
	return this->mid;
}

int Square::getWidth()
{
	return this->width;
}

int Square::getHeight()
{
	return this->height;
}

Vector2i Square::getSquarePosition(int i)
{
	return this->squarePos[i];
}

Vector2i Square::getPosition()
{
	return this->Pos;
}

void Square::setColor(int color)
{
	this->color = color;
}

void Square::setShape(int shape)
{
	this->shape = shape;
	for (int i = 0; i < 4; i++)
	{
		squareShape[i].x = Figures[shape][i] % 2;
		squareShape[i].y = Figures[shape][i] / 2;
		if (Figures[shape][i] == 5)
			mid = i;
	}
	updata();
}

void Square::setPosition(int x, int y)
{
	this->Pos = { x,y };
	updata();
}

void Square::Rotate()
{
	Vector2i p = squareShape[mid];
	for (int i = 0; i < 4; i++)
	{
		int x = squareShape[i].y - p.y;
		int y = squareShape[i].x - p.x;
		squareShape[i].x = p.x - x;
		squareShape[i].y = p.y + y;
	}
	updata();
}

void Square::updata()
{
	int min_x = 3, min_y = 3, max_x = 0, max_y = 0;
	for (int i = 0; i < 4; i++)
	{
		min_x = squareShape[i].x < min_x ? squareShape[i].x : min_x;
		min_y = squareShape[i].y < min_y ? squareShape[i].y : min_y;
		max_x = squareShape[i].x > max_x ? squareShape[i].x : max_x;
		max_y = squareShape[i].y > max_y ? squareShape[i].y : max_y;
	}
	this->width = max_x - min_x + 1;
	this->height = max_y - min_y + 1;
	for (int i = 0; i < 4; i++)
	{
		squarePos[i].x = Pos.x + squareShape[i].x - min_x;
		squarePos[i].y = Pos.y + squareShape[i].y - min_y;
	}
}