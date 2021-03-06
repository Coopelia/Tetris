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
	animationRow.clear();
	isRotate = false;
	isHardDrop = false;
	isHold = false;
	isOver = false;
	timer = 0;
	animationCtrValue = 1.0;
	elapsedTime = 0.0;
	delay = DELAYTIME;
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
	if (!animationRow.size())
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
					delay = DELAYTIME;
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
					delay = DELAYTIME;
				if (e.key.code == Keyboard::RShift)
					isHold = true;
			}
		}
	}
}

void Tetris::Update()
{
	if (!animationRow.size())
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
		slowLoading();
		if (timer > delay)
		{
			delay = DELAYTIME;
			Move_y();
			timer = 0;
		}
		shadowFunc();
		checkLine();
	}
}

void Tetris::Draw()
{
	sTiles.setColor(Color(100, 100, 100, 100));
	for (int i = 0; i < STAGE_WIDTH; i++)
	{
		if (i >= nowSquare.getSquarePosition(nowSquare.getLeft()).x && i < nowSquare.getSquarePosition(nowSquare.getLeft()).x + nowSquare.getWidth())
		{
			for (int j = 0; j < STAGE_HEIGHT; j++)
			{
				sTiles.setTextureRect(IntRect(nowSquare.getColor() * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
				sTiles.setPosition(i * GRIDSIZE, j * GRIDSIZE);
				sTiles.move(mCorePoint.x, mCorePoint.y);
				app->draw(sTiles);
			}
		}
	}
	sTiles.setColor(Color(255, 255, 255, 255));

	for (int j = 0; j < STAGE_HEIGHT; j++)
	{
		bool flag = false;
		for (int jj = 0; jj < animationRow.size(); jj++)
		{
			if (j == animationRow[jj])
			{
				flag = true;
				break;
			}
		}
		if (flag)
			continue;
		for (int i = 0; i < STAGE_WIDTH; i++)
		{
			if (Field[i][j] == 0)
				continue;
			sTiles.setTextureRect(IntRect(Field[i][j] * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
			sTiles.setPosition(i * GRIDSIZE, j * GRIDSIZE);
			sTiles.move(mCorePoint.x, mCorePoint.y);
			app->draw(sTiles);
		}
	}

	sTiles.setColor(Color(155, 155, 155, 225));
	for (int i = 0; i < 4; i++)
	{
		sTiles.setTextureRect(IntRect(shadowSquare.getColor() * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
		sTiles.setPosition(shadowSquare.getSquarePosition(i).x * GRIDSIZE, shadowSquare.getSquarePosition(i).y * GRIDSIZE);
		sTiles.move(mCorePoint.x, mCorePoint.y);
		app->draw(sTiles);
	}
	sTiles.setColor(Color(255, 255, 255, 255));

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

	if (animationRow.size())
		animatieFunc();
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

//��̬����
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

void Tetris::slowLoading()
{
	Square	tempSquare = nowSquare;
	nowSquare.setPosition(nowSquare.getPosition().x, nowSquare.getPosition().y + 1);

	if (isHit())
		delay = 2 * DELAYTIME;
	nowSquare = tempSquare;
}

void Tetris::shadowFunc()
{
	Square	tempSquare = nowSquare;
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		nowSquare.setPosition(nowSquare.getPosition().x, nowSquare.getPosition().y + 1);
		if (isHit())
		{
			nowSquare.setPosition(nowSquare.getPosition().x, nowSquare.getPosition().y - 1);
			shadowSquare = nowSquare;
			nowSquare = tempSquare;
			break;
		}
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
	if (isHit())
		isOver = true;
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
	int xCount;
	for (int j = STAGE_HEIGHT - 1; j > 0; j--)
	{
		xCount = 0;
		for (int i = 0; i < STAGE_WIDTH; i++)
			if (Field[i][j])
				xCount++;
		if (xCount == STAGE_WIDTH)
			animationRow.push_back(j);
	}
}

void Tetris::animatieFunc()
{
	elapsedTime += m_clock.restart().asMilliseconds();
	if (elapsedTime >= 100)
	{
		elapsedTime = 0;
		Vector2f po = sTiles.getOrigin();
		Vector2f ps = sTiles.getScale();
		float pr = sTiles.getRotation();
		sTiles.setOrigin(GRIDSIZE / 2, GRIDSIZE / 2);
		sTiles.setScale(animationCtrValue, animationCtrValue);
		sTiles.rotate(360 * animationCtrValue);
		for (int i = 0; i < animationRow.size(); i++)
		{
			for (int j = 0; j < STAGE_WIDTH; j++)
			{
				sTiles.setTextureRect(IntRect(Field[j][animationRow[i]] * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
				sTiles.setPosition((j + 0.5) * GRIDSIZE, (animationRow[i] + 0.5) * GRIDSIZE);
				sTiles.move(mCorePoint.x, mCorePoint.y);
				app->draw(sTiles);
			}
		}
		sTiles.setOrigin(po);
		sTiles.setScale(ps);
		sTiles.setRotation(pr);
		animationCtrValue -= 0.2;
		if (animationCtrValue < 0.1)
		{
			animationCtrValue=1.0;
			int k = STAGE_HEIGHT - 1;
			int xCount;
			for (int j = STAGE_HEIGHT - 1; j > 0; j--)
			{
				xCount = 0;
				for (int i = 0; i < STAGE_WIDTH; i++)
				{
					if (Field[i][j])
						xCount++;
					Field[i][k] = Field[i][j];
				}
				if (xCount < STAGE_WIDTH)
					k--;
			}
			animationRow.clear();
		}
	}
}