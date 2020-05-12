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
	int CharacterSize = 24;
	text.setCharacterSize(CharacterSize);
	text.setFillColor(Color(255, 255, 255, 255));
	text.setStyle(Text::Bold);
	text.setFillColor(Color(255, 0, 0, 255));
	text.setPosition(P1_SCORE_CORNER_X, P1_SCORE_CORNER_Y);
	CharacterSize = 48;
	text.setCharacterSize(CharacterSize);
	std::stringstream ss;
	ss << player1.score;
	text.setString(ss.str()); 
	app->draw(text);
	text.setPosition(P2_SCORE_CORNER_X - CharacterSize*3, P2_SCORE_CORNER_Y);
	ss.str("");
	ss << player2.score;
	text.setString(ss.str());
	app->draw(text);
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
	player1.Input(e);
	player2.Input(e);
	e.type = Event::Count;
}

void Game::Update()
{
	float time = clock.getElapsedTime().asSeconds();
	clock.restart();
	player1.timer += time;
	player2.timer += time;
	player1.Update();
	player2.Update();
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
	app->display();
}

void Game::Run()
{
	do {
		Initial();
		Start();
		while (app->isOpen() && gameOver == false)
		{
			Input();
			Update();
			Draw();
		}
	} while (!gameQuit);
}