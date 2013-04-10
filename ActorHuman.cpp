#include "ActorHuman.h"
#include <stdio.h>

ActorHuman::ActorHuman()
{

}

ActorHuman::~ActorHuman()
{

}

void ActorHuman::Think(float dt)
{
	// if human, listen input
	HandleInput();
}

void ActorHuman::DoAction()
{
	
}

ActorAction ActorHuman::MakeAction(int fx, int fy, int tx, int ty)
{
	

	return ACTOR_ACT_NONE;
}

void ActorHuman::MoveChess()
{

}

void ActorHuman::TurnChess()
{

}

void ActorHuman::HandleInput()
{
	int ix, iy;
	printf("------------please input you choose-----------\n");
	scanf("%d %d", &ix, &iy);
	// check is it back
	if (ix < 0 || ix >= CHESSBOARD_WIDTH || iy < 0 || iy >= CHESSBOARD_WIDTH)
	{
		printf("out of the board, rechoose \n");
		HandleInput();
		return;
	}

	if (m_boardState[ix][iy] == CHESSBOARD_STATE_BACK)
	{
		TurnChess(m_curSide, ix, iy);
		SwapTurn();
	}
	else
	{
		int chess_id = m_boardChess[ix][iy];
		if (chess_id != CHESS_NONE)
		{
			// choose self chess
			if ((m_curSide == CHESS_SIDE_WHITE && IsWhite(chess_id)) ||
				(m_curSide == CHESS_SIDE_BLACK && IsBlack(chess_id)))
			{
				m_curFocusX = ix;
				m_curFocusY = iy;

				printf("Next Step: please choose target \n");
				HandleInput();
				return;	
			}
			// opposite side chess
			else
			{
				// check choose test
				if (m_curFocusX != -1 && m_curFocusY != -1)
				{
					if (IsValidMove(m_curSide, m_curFocusX, m_curFocusY, ix, iy))
					{
						MoveChess(m_curSide, m_curFocusX, m_curFocusY, ix, iy);
						SwapTurn();
						PrintBoard();
						return;
					}
					else
					{
						printf("cant move to target, rechoose \n");
						HandleInput();
						return;	
					}
				}
				else
				{
					printf("cant choose op chess, rechoose \n");
					HandleInput();
					return;	
				}
			}
		}
		else
		{
			printf("there no chess, rechoose \n");
			HandleInput();
			return;
		}
	}
}