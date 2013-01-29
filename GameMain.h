#ifndef _GAME_MAIN_H_
#define _GAME_MAIN_H_

#include "define.h"

// game main logic
class GameMain
{
public:
	GameMain();
	~GameMain();

	void		Update(float dt);

	void		MoveChess(int side, int from_x, int from_y, int to_x, int to_y);
	void		TurnChess(int side, int target_x, int target_y);

private:
	void		InitChessBoard();
	bool		IsValidMove(int side, int from_x, int from_y, int to_x, int to_y);
	bool		IsValidTurn(int side, int target_x, int target_y);

	void		PrintBoard();
	void		PrintInput();

private:
	int			m_curSide;
	Actor*		m_actorWhite;
	Actor*		m_actorBlack;

	int			m_boardChess[CHESSBOARD_WIDTH][CHESSBOARD_WIDTH];
	int 		m_boardState[CHESSBOARD_WIDTH][CHESSBOARD_WIDTH];
};

#endif