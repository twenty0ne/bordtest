#ifndef _EVELUATION_ENGINE_H_
#define _EVELUATION_ENGINE_H_

// PAWN 100, DOOM 200, KNIGHT 200, BISHOP 300 QUEEN 500 KING 1000
#define BASEVALUE_PAWN		100
#define BASEVALUE_DOOM		200
#define BASEVALUE_KNIGHT	200
#define BASEVALUE_BISHOP	300
#define BASEVALUE_QUEEN		500
#define BASEVALUE_KING		1000

// 
#define FLEXIBILITY_PAWN	15
#define FLEXIBILITY_DOOM	1
#define FLEXIBILITY_KNIGHT	1
#define FLEXIBILITY_BISHOP	6
#define FLEXIBILITY_QUEEN	12
#define FLEXIBILITY_KING	0

class EveluationEngine
{
public:
	EveluationEngine();
	~EveluationEngine();

	virtual int			Eveluate(int position[CHESSBOARD_WIDTH][CHESSBOARD_WIDTH], bool bIsRedTurn);


};

#endif