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
	memset(list, 0, sizeof(list));
	isRotate = false;
	isHardDrop = false;
	timer = 0;
	delay = 0.5;
	list_num = 0;

	if (role == 1)
	{
		mCornPoint = { P1_STAGE_CORNER_X,	P1_STAGE_CORNER_Y };
		nextSquareCornPoint = { P1_NXET_CORNER_X, P1_NXET_CORNER_Y };
	}
	if (role == 2)
	{
		mCornPoint = { P2_STAGE_CORNER_X,	P2_STAGE_CORNER_Y };
		nextSquareCornPoint = { P2_NXET_CORNER_X, P2_NXET_CORNER_Y };
	}

	colorNum = 1 + rand() % 7;
	currentShapeNum = rand() % 7;

	nextcolorNum = 1 + rand() % 7;
	nextShapeNum = rand() % 7;

	for (int i = 0; i < 4; i++)
	{
		currentSquare[i].x = Figures[currentShapeNum][i] % 2 + STAGE_WIDTH / 2;
		currentSquare[i].y = Figures[currentShapeNum][i] / 2;
		nextSquare[i].x = Figures[nextShapeNum][i] % 2;
		nextSquare[i].y = Figures[nextShapeNum][i] / 2;
	}
}

void Tetris::Input(Event& e)
{
	if (role == 1)
	{
		if (e.type == Event::KeyPressed)
		{
			if (e.key.code == Keyboard::W)
				if (currentShapeNum != 6)
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
		}
	}
	if (role == 2)
	{
		if (e.type == Event::KeyPressed)
		{
			if (e.key.code == Keyboard::Up)
				if (currentShapeNum != 6)
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
	if (timer > delay)
	{
		Move_y();
		timer = 0;
	}
	slowLoading();
	checkLine();
}

void Tetris::Draw()
{
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			if (Field[i][j] == 0)
				continue;
			sTiles.setTextureRect(IntRect(Field[i][j] * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
			sTiles.setPosition(j * GRIDSIZE, i * GRIDSIZE);
			sTiles.move(mCornPoint.x, mCornPoint.y);
			app->draw(sTiles);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		sTiles.setTextureRect(IntRect(colorNum * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
		sTiles.setPosition(currentSquare[i].x * GRIDSIZE, currentSquare[i].y * GRIDSIZE);
		sTiles.move(mCornPoint.x, mCornPoint.y);
		app->draw(sTiles);
	}

	for (int i = 0; i < 4; i++)
	{
		sTiles.setTextureRect(IntRect(nextcolorNum * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
		sTiles.setPosition(nextSquare[i].x * GRIDSIZE, nextSquare[i].y * GRIDSIZE);
		sTiles.move(nextSquareCornPoint.x, nextSquareCornPoint.y);
		app->draw(sTiles);
	}
}

bool Tetris::hitTest()
{
	for (int i = 0; i < 4; i++)
	{
		if (currentSquare[i].x < 0 || currentSquare[i].x >= STAGE_WIDTH || currentSquare[i].y >= STAGE_HEIGHT)
			return false;
		else if (Field[currentSquare[i].y][currentSquare[i].x])
			return false;
	}
	return true;
}

int Tetris::List()
{
	if (list_num == 0)
	{
		for (int i = 0; i < 7; i++)
			list[i] = i;
		list_num = 7;
	}
	int k, num;
	srand(time(0));
	while (true)
	{
		k = rand() % 7;
		if (list[k] != -1)
		{
			num = list[k];
			list[k] = -1;
			list_num--;
			break;
		}
	}
	return num;
}

void Tetris::Move_x(int dx)
{
	for (int i = 0; i < 4; i++)
	{
		tempSquare[i] = currentSquare[i];
		currentSquare[i].x += dx;
	}
	if (!hitTest())
	{
		for (int i = 0; i < 4; i++)
			currentSquare[i] = tempSquare[i];
	}
}

void Tetris::Move_y()
{
	for (int i = 0; i < 4; i++)
	{
		tempSquare[i] = currentSquare[i];
		currentSquare[i].y += 1;
	}

	if (!hitTest())
	{
		for (int i = 0; i < 4; i++)
			Field[tempSquare[i].y][tempSquare[i].x] = colorNum;
		colorNum = nextcolorNum;
		currentShapeNum = nextShapeNum;
		nextcolorNum = 1 + rand() % 7;
		nextShapeNum = List();
		for (int i = 0; i < 4; i++)
		{
			currentSquare[i] = nextSquare[i];
			currentSquare[i].x = currentSquare[i].x + STAGE_WIDTH / 2;
			nextSquare[i].x = Figures[nextShapeNum][i] % 2;
			nextSquare[i].y = Figures[nextShapeNum][i] / 2;
		}
	}
}

void Tetris::slowLoading()
{
	for (int i = 0; i < 4; i++)
	{
		tempSquare[i] = currentSquare[i];
		currentSquare[i].y += 1;
	}

	if (!hitTest())
		delay = 1;
	for (int i = 0; i < 4; i++)
		currentSquare[i] = tempSquare[i];
}

void Tetris::HardDrop()
{
	for (int j = 0; j < STAGE_HEIGHT; j++)
	{
		for (int i = 0; i < 4; i++)
			currentSquare[i].y += 1;
		if (!hitTest())
		{
			for (int i = 0; i < 4; i++)
				currentSquare[i].y -= 1;
			break;
		}
	}
}

void Tetris::Rotate()
{
	int mid = 0;
	for (int i = 0; i < 4; i++)
	{
		if (Figures[currentShapeNum][i] == 5)
		{
			mid = i;
			break;
		}
	}
	Vector2i p = currentSquare[mid];
	for (int i = 0; i < 4; i++)
	{
		int x = currentSquare[i].y - p.y;
		int y = currentSquare[i].x - p.x;
		currentSquare[i].x = p.x - x;
		currentSquare[i].y = p.y + y;
	}
	if (!hitTest())
	{
		for (int i = 0; i < 4; i++)
			currentSquare[i] = tempSquare[i];
	}
}

void Tetris::checkLine()
{
	int k = STAGE_HEIGHT - 1;
	int yCount = 0;
	for (int i = STAGE_HEIGHT - 1; i > 0; i--)
	{
		int xCount = 0;
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			if (Field[i][j])
				xCount++;
			Field[k][j] = Field[i][j];
		}
		if (xCount < STAGE_WIDTH)
			k--;
		else
			score += 10;
	}
}