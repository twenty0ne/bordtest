#ifndef _MOVE_GENERATOR_H_
#define _MOVE_GENERATOR_H_

#include "define.h"

class MoveGenerator
{
public:
	MoveGenerator();
	~MoveGenerator();

	static bool 	IsValidMove(byte position[CHESSBOARD_WIDTH][CHESSBOARD_WIDTH], int from_x, int from_y, int to_x, int to_y);
	int				CreatePossibleMove(byte position[CHESSBOARD_WIDTH][CHESSBOARD_WIDTH], int play_layer, int side);

public:
	ChessMove	m_moveList[10][255];

private:
	int				AddMove(int from_x, int from_y, int to_x, int to_y, int play_layer);

private:
	int		m_moveCount;
};

#endif