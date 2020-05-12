#pragma once
#include<SFML/Graphics.hpp>
#include<SFML./Audio.hpp>
#include<sstream>
#include<vector>

#define GRIDSIZE 35
#define WINDOW_WIDTH 1350
#define WINDOW_HEIGHT 1000 
#define  STAGE_WIDTH	10
#define  STAGE_HEIGHT	20
#define  P1_STAGE_CORNER_X		156
#define  P1_STAGE_CORNER_Y		174
#define  P2_STAGE_CORNER_X		844
#define  P2_STAGE_CORNER_Y		174
#define  P1_NXET_CORNER_X		587
#define  P1_NXET_CORNER_Y		125
#define  P2_NXET_CORNER_X		702
#define  P2_NXET_CORNER_Y		125
#define  P1_SCORE_CORNER_X		366
#define  P1_SCORE_CORNER_Y		110
#define  P2_SCORE_CORNER_X		1195
#define  P2_SCORE_CORNER_Y		110

using namespace sf;

extern class Game;
extern class Tetris;
extern Vector2i holdSquare[4];