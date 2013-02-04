##include "GameMain.h"

GameMain::GameMain()
{

}

GameMain::~GameMain()
{

}

void GameMain::MoveChess(int side, int from_x, int from_y, int to_x, int to_y)
{
	if (!IsValidMove(side, from_x, from_y, to_x, to_y))
		return;

	chess_id = m_boardChess[from_x][from_y];
	m_boardChess[to_x][to_y] = chess_id;
	m_boardChess[from_x][from_y] = CHESS_NONE;
}

void GameMain::TurnChess(int side, int target_x, int target_y)
{
	if (!IsValidTurn(side, target_x, target_y))
		return;

	m_boardState[target_x][target_y] == CHESS_STATE_FRONT;

#if TEST_PRINT_LOG
	printf("side: %d turn (%d, %d) chess: %d \n", side, target_x, target_y, m_boardChess[target_x][target_y]);
#endif
}

void GameMain::InitChessBoard()
{
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
	random_shuffle(vec_chess.begin(), vec_chess.end());

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
	if (m_boardState[to_x][to_y] != CHESS_STATE_FRONT)
		return false;

	// only can move one grid per step
	if (abs(from_x - to_x) > 1 || abs(from_y - to_y) > 1 || (from_x != to_x && from_y != to_y))
		return false;

	move_chessid = m_boardChess[from_x][from_y]
	target_chessid = m_boardChess[to_x][to_y]
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
	if (m_boardState[target_x][target_y] == CHESS_STATE_BACK)
	{
		return true;
	}

	return false;
}

void GameMain::PrintBoard()
{
	printf("--------------print board------------")
	for (int i = 0; i < CHESSBOARD_WIDTH; ++i)
	{
		for (int j = 0; j < CHESSBOARD_WIDTH; ++j)
		{
			printf("%d ", m_boardChess[i][j]);
		}
		printf("\n");
	}
}

void GameMain::HandleInput(int stage)
{
	int ix, iy;
	printf("------------please input you choose-----------")
	scanf("%d, %d", &ix, &iy);
	// check is it back
	if (ix < 0 || ix >= CHESSBOARD_WIDTH || iy < 0 || iy >= CHESSBOARD_WIDTH)
		printf("out of the board\n");
	if (m_boardState[ix][iy] == CHESS_STATE_BACK)
	{
		TurnChess(m_curSide, ix, iy);

		SwapTurn();
	}
	else
	{
		chess_id = m_boardChess[ix][iy];
		if (chess_id != CHESS_NONE)
		{
			// choose self chess
			if ((m_curSide == CHESS_SIDE_WHITE && IsWhite(chess_id)) ||
				(m_curSide == CHESS_SIDE_BLACK && IsBlack(chess_id)))
			{
				printf()
			}
		}
	}
}

void GameMain::SwapTurn()
{
	if (m_curSide == CHESS_SIDE_WHITE)
	{
		m_curSide = CHESS_SIDE_BLACK;
	}
	else if (m_curSide == CHESS_SIDE_BLACK)
	{
		m_curSide = CHESS_SIDE_WHITE;
	}

#if TEST_PRINT_LOG
	printf("----------swap turn--------------");
	printf("Now: %d \n", m_curSide);
#endif
}
