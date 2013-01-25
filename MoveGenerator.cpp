##include "MoveGenerator.h"

MoveGenerator::MoveGenerator()
{

}

MoveGenerator::~MoveGenerator()
{

}

bool MoveGenerator::IsValidMove(byte position[CHESSBOARD_WIDTH][CHESSBOARD_WIDTH], int from_x, int from_y, int to_x, int to_y)
{
	if (to_x < 0 || to_x >= CHESSBOARD_WIDTH || to_y < 0 || to_y >= CHESSBOARD_WIDTH)
		return false;

	if (from_x == to_x && from_y == to_y)
		return false;

	// only can move one grid per step
	if (abs(from_x - to_x) > 1 || abs(from_y - to_y) > 1 || (from_x != to_x && from_y != to_y))
		return false;

	move_chessid = position[from_x][from_y]
	target_chessid = position[to_x][to_y]
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

int MoveGenerator::CreatePossibleMove(byte position[GRID_NUM][GRID_NUM], int play_layer, int side)
{
	m_moveCount = 0;
	for (int i = 0; i < GRID_NUM; ++i)
	{
		for (int j = 0; j < GRID_NUM; ++i)
		{
			if (position[i][j] != CHESS_NONE)
			{
				chess_id = position[i][j];
				if (side == CHESSSIDE_WHITE && IsBlack(chess_id))
					continue;
				if (side == CHESSSIDE_BLACK && IsWhite(chess_id))
					continue;

				// four dir
				for (int dir = 0; dir < 4; ++dir)
				{
					to_x = i + MOVE_DIR[dir][0];
					to_y = j + MOVE_DIR[dir][1];

					if (IsValidMove(position, i, j, to_x, to_y))
						AddMove(i, j, to_x, to_y, play_layer)
				}
			}
		}
	}

	return m_moveCount;
}

int MoveGenerator::AddMove(int from_x, int from_y, int to_x, int to_y, int play_layer)
{
	m_moveList[play_layer][m_moveCount].fromPos.x = to_x;
	m_moveList[play_layer][m_moveCount].fromPos.y = to_y;
	m_moveList[play_layer][m_moveCount].toPos.x = 
	m_moveList[play_layer][m_moveCount].toPos.y = PosValue[to_x][to_y];
	++m_moveCount;

	return m_moveCount;
}