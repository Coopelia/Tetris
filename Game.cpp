#include "Game.h"

Game::Game()
{
	app = new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris_qjy", Uint32(5));
}

Game::~Game()
{
	delete app;
}

void Game::Initial()
{
	app->setFramerateLimit(15);
	imgSetNo = 1;
	LoadMediaData();
	player1.role = 1;
	player2.role = 2;
	player1.Initial(app, &tTiles);
	player2.Initial(app, &tTiles);
}

void Game::Start()
{
	gameOver = false;
	gameQuit = false;
	gameBegin = false;
	gamePause = false;
	bt_start.app = app;
	bt_pause.app = app;
	bt_start.setPosition(620, 640);
	bt_pause.setPosition(620, 700);
	player1.Start();
	player2.Start();
}

void Game::LoadMediaData()
{
	std::stringstream ss;
	ss << "data/images/bg" << imgSetNo << ".jpg";
	tBackground.loadFromFile(ss.str());
	ss.str("");
	ss << "data/images/tiles" << imgSetNo << ".jpg";
	tTiles.loadFromFile(ss.str());
	tFrame.loadFromFile("data/images/frame.png");
	tCover.loadFromFile("data/images/cover.png");
	sBackground.setTexture(tBackground);
	sFrame.setTexture(tFrame);
	sCover.setTexture(tCover);
	font.loadFromFile("data/fonts/simsun.ttc");
	text.setFont(font);
}

void Game::ShowText()
{
	text.setCharacterSize(42);
	text.setStyle(Text::Bold);
	text.setFillColor(Color(255, 0, 0, 255));
	text.setPosition(P1_SCORE_CORNER_X, P1_SCORE_CORNER_Y);
	std::stringstream ss;
	ss << player1.score;
	text.setString(ss.str()); 
	app->draw(text);
	text.setPosition(P2_SCORE_CORNER_X - 24*3, P2_SCORE_CORNER_Y);
	ss.str("");
	ss << player2.score;
	text.setString(ss.str());
	app->draw(text);
	if(player1.isOver)
	{
	text.setCharacterSize(42);
	text.setFillColor(Color::Red);
	text.setStyle(Text::Bold);
	text.setPosition(P1_STAGE_CORNER_X + 50, P1_STAGE_CORNER_X + 330);
	text.setString(L"Deaded!");
	app->draw(text);
	}
	if(player2.isOver)
	{
		text.setCharacterSize(42);
		text.setFillColor(Color::Red);
		text.setStyle(Text::Bold);
		text.setPosition(P2_STAGE_CORNER_X + 50, P2_STAGE_CORNER_Y + 230);
		text.setString(L"Deaded!");
		app->draw(text);
	}
}

void Game::Input()
{
	Event e;
	app->pollEvent(e);
	if (e.type == Event::Closed)
	{
		app->close();
		gameQuit = true;
	}
	if (bt_start.onClick(e))
		gameBegin = !gameBegin;
	if (bt_pause.onClick(e))
		gamePause = !gamePause;
	if (!player1.isOver)
		player1.Input(e);
	if (!player2.isOver)
		player2.Input(e);
	e.type = Event::Count;
}

void Game::Update()
{
	if (gameBegin)
	{
		bt_start.setTextrue("data/images/结束.png");
		gameOver = false;
	}
	else
	{
		bt_start.setTextrue("data/images/开始.png");
		gameOver = true;
	}
	if (gamePause)
		bt_pause.setTextrue("data/images/继续.png");
	else
	{
		bt_pause.setTextrue("data/images/暂停.png");
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		player1.timer += time;
		player2.timer += time;
		if (!player1.isOver)
			player1.Update();
		if (!player2.isOver)
			player2.Update();
		if (player1.isOver && player2.isOver)
			gameOver = true;
	}
}

void Game::Draw()
{
	app->clear();	
	sBackground.setPosition(0, 0);
	app->draw(sBackground);
	app->draw(sFrame);
	player1.Draw();
	player2.Draw();
	sCover.setPosition(P1_STAGE_CORNER_X, P1_STAGE_CORNER_Y);
	app->draw(sCover);
	sCover.setPosition(P2_STAGE_CORNER_X, P2_STAGE_CORNER_Y);
	app->draw(sCover);
	ShowText();
	bt_start.show();
	bt_pause.show();
	app->display();
}

void Game::Run()
{
	do {
		Initial();
		Start();
		while (app->isOpen() && (gameOver == false||gameBegin==true))
		{
			Update();
			Input();
			Draw();
		}
	} while (!gameQuit);
}