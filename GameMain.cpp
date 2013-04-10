#include "GameMain.h"
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <time.h>
#include "Actor.h"
#include "ActorHuman.h"

/*static*/GameMain* GameMain::m_pInstance = NULL;

/*static*/GameMain& GameMain::GetInstance()
{
	if (m_pInstance == NULL)
		m_pInstance = new GameMain;

	return *m_pInstance;
}

GameMain::GameMain()
	:m_status(GAME_STATUS_NONE)
	,m_curSide(CHESS_SIDE_WHITE)
	,m_actorThinking(false)
	,m_curFocusX(-1)
	,m_curFocusY(-1)
	,m_curTargetX(-1)
	,m_curTargetY(-1)
{
}

GameMain::~GameMain()
{

}

bool GameMain::Init()
{
	// init chess board
	InitChessBoard();

	// init actor
	m_actor[ACTOR_WHITE] = new ActorHuman;
	m_actor[ACTOR_BLACK] = new ActorHuman;

#if TEST_PRINT_LOG
	printf("---cur side: %d \n", m_curSide);
#endif

	m_status = GAME_STATUS_RUN;
	m_actorThinking = true;

	return true;
}

void GameMain::Update(float dt)
{
	if (m_status == GAME_STATUS_RUN)
	{
		if (m_actorThinking)
		{
			HandleInput();
		}
	}
}

void GameMain::MoveChess(int side, int from_x, int from_y, int to_x, int to_y)
{
	if (!IsValidMove(side, from_x, from_y, to_x, to_y))
		return;

	int chess_id = m_boardChess[from_x][from_y];
	m_boardChess[to_x][to_y] = chess_id;
	m_boardChess[from_x][from_y] = CHESS_NONE;

	m_boardState[to_x][to_y] = CHESSBOARD_STATE_FRONT;
	m_boardState[from_x][from_y] = CHESSBOARD_STATE_NONE;
}

void GameMain::TurnChess(int side, int target_x, int target_y)
{
	if (!IsValidTurn(side, target_x, target_y))
		return;

	m_boardState[target_x][target_y] = CHESSBOARD_STATE_FRONT;

#if TEST_PRINT_LOG
	printf("side: %d turn (%d, %d) chess: %d \n", side, target_x, target_y, m_boardChess[target_x][target_y]);
	PrintBoard();
#endif
}

void GameMain::InitChessBoard()
{
	srand(static_cast<unsigned int>(time(0)));

	memset(m_boardState, CHESSBOARD_STATE_BACK, sizeof(m_boardState));

	std::vector<int> vec_chess;
	for (int i = 0; i < 2; ++i)
	{
		// 8 pawn
		vec_chess.push_back(CHESS_BLACK_PAWN + CHESS_BLACK_END * i);
		vec_chess.push_back(CHESS_BLACK_PAWN + CHESS_BLACK_END * i);
		vec_chess.push_back(CHESS_BLACK_PAWN + CHESS_BLACK_END * i);
		vec_chess.push_back(CHESS_BLACK_PAWN + CHESS_BLACK_END * i);
		vec_chess.push_back(CHESS_BLACK_PAWN + CHESS_BLACK_END * i);
		vec_chess.push_back(CHESS_BLACK_PAWN + CHESS_BLACK_END * i);
		vec_chess.push_back(CHESS_BLACK_PAWN + CHESS_BLACK_END * i);
		vec_chess.push_back(CHESS_BLACK_PAWN + CHESS_BLACK_END * i);
		// 4 doom
		vec_chess.push_back(CHESS_BLACK_DOOM + CHESS_BLACK_END * i);
		vec_chess.push_back(CHESS_BLACK_DOOM + CHESS_BLACK_END * i);
		vec_chess.push_back(CHESS_BLACK_DOOM + CHESS_BLACK_END * i);
		vec_chess.push_back(CHESS_BLACK_DOOM + CHESS_BLACK_END * i);
		// 2 knight
		vec_chess.push_back(CHESS_BLACK_KNIGHT + CHESS_BLACK_END * i);
		vec_chess.push_back(CHESS_BLACK_KNIGHT + CHESS_BLACK_END * i);
		// 2 bishop
		vec_chess.push_back(CHESS_BLACK_BISHOP + CHESS_BLACK_END * i);
		vec_chess.push_back(CHESS_BLACK_BISHOP + CHESS_BLACK_END * i);
		// 1 queen
		vec_chess.push_back(CHESS_BLACK_QUEEN + CHESS_BLACK_END * i);
		// 1 king
		vec_chess.push_back(CHESS_BLACK_KING + CHESS_BLACK_END * i);
	}
	
	// random
	std::random_shuffle(vec_chess.begin(), vec_chess.end());

	// input m_boardChess
	for (int i = 0; i < vec_chess.size(); ++i)
	{
		int bx = i % CHESSBOARD_WIDTH;
		int by = i / CHESSBOARD_WIDTH;
		m_boardChess[bx][by] = vec_chess.at(i);
	}

	// print board
#if TEST_PRINT_LOG
	PrintBoard();
#endif

}

bool GameMain::IsValidMove(int side, int from_x, int from_y, int to_x, int to_y)
{
	if (to_x < 0 || to_x >= CHESSBOARD_WIDTH || to_y < 0 || to_y >= CHESSBOARD_WIDTH)
		return false;

	if (from_x == to_x && from_y == to_y)
		return false;

	// if state != front, return false
	if (m_boardState[to_x][to_y] != CHESSBOARD_STATE_FRONT)
		return false;

	// only can move one grid per step
	if (abs(from_x - to_x) > 1 || abs(from_y - to_y) > 1 || (from_x != to_x && from_y != to_y))
		return false;

	int move_chessid = m_boardChess[from_x][from_y];
	int target_chessid = m_boardChess[to_x][to_y];
	if (IsSameSide(move_chessid, target_chessid))
		return false;

	if ((move_chessid == CHESS_BLACK_PAWN && target_chessid == CHESS_WHITE_KING) ||
		(move_chessid == CHESS_WHITE_PAWN && target_chessid == CHESS_BLACK_KING))
		return true;
	
	if (IsWhite(move_chessid))
	{
		move_chessid -= CHESS_BLACK_END;
	}
	else // target is black
	{
		target_chessid -= CHESS_BLACK_END;
	}

	if (move_chessid < target_chessid)
		return false;

	return true;
}

bool GameMain::IsValidTurn(int side, int target_x, int target_y)
{
	if (m_boardState[target_x][target_y] == CHESSBOARD_STATE_BACK)
	{
		return true;
	}

	return false;
}

void GameMain::PrintBoard()
{
	printf("--------------print board------------\n");
	for (int i = 0; i < CHESSBOARD_WIDTH; ++i)
	{
		for (int j = 0; j < CHESSBOARD_WIDTH; ++j)
		{
			if (m_boardState[i][j] == CHESSBOARD_STATE_FRONT)
				printf("%2d ", m_boardChess[i][j]);
			else if (m_boardState[i][j] == CHESSBOARD_STATE_BACK)
				printf("[] ");
			else if (m_boardState[i][j] == CHESSBOARD_STATE_NONE)
				printf(" X ");
		}
		printf("\n");
	}
}

void GameMain::HandleInput()
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

void GameMain::SwapTurn()
{
	// reset
	m_curFocusX = -1;
	m_curFocusY = -1;
	m_curTargetX = -1;
	m_curTargetY = -1;

	if (m_curSide == CHESS_SIDE_WHITE)
	{
		m_curSide = CHESS_SIDE_BLACK;

		m_actor[ACTOR_BLACK]->Think(0.0f);
	}
	else if (m_curSide == CHESS_SIDE_BLACK)
	{
		m_curSide = CHESS_SIDE_WHITE;

		m_actor[ACTOR_WHITE]->Think(0.0f);
	}

#if TEST_PRINT_LOG
	printf("----------swap turn--------------\n");
	printf("Now cur turn: %d \n", m_curSide);
#endif

	HandleInput();
}
