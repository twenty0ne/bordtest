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

	chess_id = m_board[from_x][from_y];
	m_board[to_x][to_y] = chess_id;
	m_board[from_x][from_y] = CHESS_NONE;
}

void GameMain::TurnChess(int side, int target_x, int target_y)
{
	if ()
}

void GameMain::InitChessBoard()
{
#define CHESS_BLACK_PAWN		1	// 8
#define CHESS_BLACK_DOOM		2	// 4
#define CHESS_BLACK_KNIGHT		3	// 2
#define CHESS_BLACK_BISHOP		4	// 2
#define CHESS_BLACK_QUEEN		5	// 1
#define CHESS_BLACK_KING		6	// 1
#define CHESS_BLACK_BEGIN		CHESS_BLACK_PAWN
#define CHESS_BLACK_END			CHESS_BLACK_KING
#define CHESS_WHITE_PAWN		7	// 8
#define CHESS_WHITE_DOOM		8	// 4
#define CHESS_WHITE_KNIGHT		9	// 2
#define CHESS_WHITE_BISHOP		10	// 2
#define CHESS_WHITE_QUEEN		11	// 1
#define CHESS_WHITE_KING		12	// 1

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

	// input m_board
	for (int i = 0; i < count; ++i)
	{
		/* code */
	}
}

bool GameMain::IsValidMove(int side, int from_x, int from_y, int to_x, int to_y)
{
	if (to_x < 0 || to_x >= CHESSBOARD_WIDTH || to_y < 0 || to_y >= CHESSBOARD_WIDTH)
		return false;

	if (from_x == to_x && from_y == to_y)
		return false;

	// only can move one grid per step
	if (abs(from_x - to_x) > 1 || abs(from_y - to_y) > 1 || (from_x != to_x && from_y != to_y))
		return false;

	move_chessid = m_board[from_x][from_y]
	target_chessid = m_board[to_x][to_y]
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