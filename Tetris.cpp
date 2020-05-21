#include "Tetris.h"

void Tetris::Initial(RenderWindow* app, Texture* tex)
{
	this->app = app;
	this->tTiles = tex;
	sTiles.setTexture(*tTiles);
}

void Tetris::Start()
{
	score = 0;
	memset(Field, 0, sizeof(Field));
	memset(b7array, 0, sizeof(b7array));
	memset(Field, 0, sizeof(Field));
	isRotate = false;
	isHardDrop = false;
	isHold = false;
	timer = 0;
	delay = 0.5;
	b7Int = 0;

	if (role == 1)
	{
		mCorePoint = { P1_STAGE_CORNER_X,	P1_STAGE_CORNER_Y };
		nextCorePoint = { P1_NXET_CORNER_X, P1_NXET_CORNER_Y };
	}
	if (role == 2)
	{
		mCorePoint = { P2_STAGE_CORNER_X,	P2_STAGE_CORNER_Y };
		nextCorePoint = { P2_NXET_CORNER_X, P2_NXET_CORNER_Y };
	}

	nowSquare.setColor(1 + rand() % 7);
	nowSquare.setShape(rand() % 7);
	nowSquare.setPosition(STAGE_WIDTH / 2 - nowSquare.getWidth() / 2, 0);

	nextSquare.setColor(1 + rand() % 7);
	nextSquare.setShape(rand() % 7);
	nextSquare.setPosition(0, 0);

	holdSquare.setColor(0);
}

void Tetris::Input(Event& e)
{
	if (role == 1)
	{
		if (e.type == Event::KeyPressed)
		{
			if (e.key.code == Keyboard::W)
				if (nowSquare.getShape() != 6)
					isRotate = true;
			if (e.key.code == Keyboard::A)
				Move_x(-1);
			else if (e.key.code == Keyboard::D)
				Move_x(1);
			if (e.key.code == Keyboard::S)
				delay /= 10;
		}
		if (e.type == Event::KeyReleased)
		{
			if (e.key.code == Keyboard::LControl)
				isHardDrop = true;
			if (e.key.code == Keyboard::S)
				delay = 0.5;
			if (e.key.code == Keyboard::LShift)
				isHold = true;
		}
	}
	if (role == 2)
	{
		if (e.type == Event::KeyPressed)
		{
			if (e.key.code == Keyboard::Up)
				if (nowSquare.getShape() != 6)
					isRotate = true;
			if (e.key.code == Keyboard::Left)
				Move_x(-1);
			else if (e.key.code == Keyboard::Right)
				Move_x(1);
			if (e.key.code == Keyboard::Down)
				delay /= 10;
		}
		if (e.type == Event::KeyReleased)
		{
			if (e.key.code == Keyboard::RControl)
				isHardDrop = true;
			if (e.key.code == Keyboard::Down)
				delay = 0.5;
			if (e.key.code == Keyboard::RShift)
				isHold = true;
		}
	}
}

void Tetris::Update()
{
	if (isRotate)
	{
		Rotate();
		isRotate = false;
	}
	if (isHardDrop)
	{
		HardDrop();
		isHardDrop = false;
	}
	if (isHold)
	{
		holdFunc();
		isHold = false;
	}
	if (timer > delay)
	{
		Move_y();
		timer = 0;
	}
	checkLine();
}

void Tetris::Draw()
{
	for (int i = 0; i < STAGE_WIDTH; i++)
	{
		for (int j = 0; j < STAGE_HEIGHT; j++)
		{
			if (Field[i][j] == 0)
				continue;
			sTiles.setTextureRect(IntRect(Field[i][j] * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
			sTiles.setPosition(i * GRIDSIZE, j * GRIDSIZE);
			sTiles.move(mCorePoint.x, mCorePoint.y);
			app->draw(sTiles);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		sTiles.setTextureRect(IntRect(nowSquare.getColor() * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
		sTiles.setPosition(nowSquare.getSquarePosition(i).x * GRIDSIZE, nowSquare.getSquarePosition(i).y * GRIDSIZE);
		sTiles.move(mCorePoint.x, mCorePoint.y);
		app->draw(sTiles);
	}

	for (int i = 0; i < 4; i++)
	{
		sTiles.setTextureRect(IntRect(nextSquare.getColor() * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
		sTiles.setPosition(nextSquare.getSquarePosition(i).x * GRIDSIZE, nextSquare.getSquarePosition(i).y * GRIDSIZE);
		sTiles.move(nextCorePoint.x, nextCorePoint.y);
		app->draw(sTiles);
	}

	if (holdSquare.getColor())
	{
		for (int i = 0; i < 4; i++)
		{
			sTiles.setTextureRect(IntRect(holdSquare.getColor() * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
			sTiles.setPosition(holdSquare.getSquarePosition(i).x * GRIDSIZE, holdSquare.getSquarePosition(i).y * GRIDSIZE);
			sTiles.move(HOLD_CORNER_X, HOLD_CORNER_Y);
			app->draw(sTiles);
		}
	}
}

bool Tetris::isHit()
{
	if (nowSquare.getPosition().x<0 || nowSquare.getPosition().x + nowSquare.getWidth()>STAGE_WIDTH || nowSquare.getPosition().y + nowSquare.getHeight() > STAGE_HEIGHT)
		return true;
	for (int i = 0; i < 4; i++)
	{
		if (Field[nowSquare.getSquarePosition(i).x][nowSquare.getSquarePosition(i).y])
			return true;
	}
	return false;
}

//¾²Ì¬·ÖÅä
int Tetris::Bag7()
{
	srand(time(0));
	if (b7Int == 0)
	{
		int temp[7];
		for (int i = 0; i < 7; i++)
			temp[i] = i;
		int k;
		while (b7Int < 7)
		{
			k = rand() % 7;
			if (temp[k] != -1)
			{
				b7array[b7Int++] = temp[k];
				temp[k] = -1;
			}
		}
	}
	return b7array[(7 - b7Int--)];
}

void Tetris::Move_x(int dx)
{
	Square	tempSquare = nowSquare;
	nowSquare.setPosition(nowSquare.getPosition().x + dx, nowSquare.getPosition().y);

	if (isHit())
		nowSquare = tempSquare;
}

void Tetris::Move_y()
{
	Square	tempSquare = nowSquare;
	nowSquare.setPosition(nowSquare.getPosition().x, nowSquare.getPosition().y + 1);

	if (isHit())
	{
		for (int i = 0; i < 4; i++)
			Field[tempSquare.getSquarePosition(i).x][tempSquare.getSquarePosition(i).y] = tempSquare.getColor();
		nextFunc();
	}
}

void Tetris::HardDrop()
{
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		nowSquare.setPosition(nowSquare.getPosition().x, nowSquare.getPosition().y + 1);
		if (isHit())
		{
			nowSquare.setPosition(nowSquare.getPosition().x, nowSquare.getPosition().y - 1);
			break;
		}
	}
}

void Tetris::Rotate()
{
	Square	tempSquare = nowSquare;
	nowSquare.Rotate();
	Square rtSquare = nowSquare;
	for (int i = 0; i < rtSquare.getWidth(); i++)
	{
		nowSquare.setPosition(nowSquare.getPosition().x + i, nowSquare.getPosition().y);
		if (isHit())
		{
			nowSquare = rtSquare;
			nowSquare.setPosition(nowSquare.getPosition().x - i, nowSquare.getPosition().y);
			if (isHit())
				nowSquare = rtSquare;
			else
				return;
		}
		else
			return;
	}
	nowSquare = tempSquare;
}

void Tetris::nextFunc()
{
	nowSquare = nextSquare;
	nowSquare.setPosition(STAGE_WIDTH / 2 - nowSquare.getWidth() / 2, 0);

	nextSquare.setColor(1 + rand() % 7);
	nextSquare.setShape(rand() % 7);
}

void Tetris::holdFunc()
{
	if (!holdSquare.getColor())
	{
		holdSquare.setColor(nowSquare.getColor());
		holdSquare.setShape(nowSquare.getShape());
		nextFunc();
		return;
	}
	Square tempSquare = nowSquare;
	nowSquare.setColor(holdSquare.getColor());
	nowSquare.setShape(holdSquare.getShape());
	if (isHit())
		nowSquare = tempSquare;
	else
	{
		holdSquare.setColor(nextSquare.getColor());
		holdSquare.setShape(nextSquare.getShape());
		nextFunc();
	}
}

void Tetris::checkLine()
{
	int k = STAGE_HEIGHT - 1;
	int yCount = 0;
	for (int j = STAGE_HEIGHT - 1; j > 0; j--)
	{
		int xCount = 0;
		for (int i = 0; i < STAGE_WIDTH; i++)
		{
			if (Field[i][j])
				xCount++;
			Field[i][k] = Field[i][j];
		}
		if (xCount < STAGE_WIDTH)
			k--;
		else
			score += 10;
	}
}