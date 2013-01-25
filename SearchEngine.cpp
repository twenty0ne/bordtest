#include "SearchEngine.h"

SearchEngine::SearchEngine()
{

}

SearchEngine::~SearchEngine()
{

}

int SearchEngine::MakeMove(ChessMove* move)
{
	int chess_id;
	chess_id = m_curPosition[move->toPos.x][move->toPos.y];
	m_curPosition[move->toPos.x][move->toPos.y] = m_curPosition[move->fromPos.x][move->fromPos.y];
	// clear last pos
	m_curPosition[move->fromPos.x][move->fromPos.y] = CHESS_NONE;

	// return chess id by eated
	return chess_id;
}

void SearchEngine::UnMakeMove(ChessMove* move, int chess_id)
{
	m_curPosition[move->fromPos.x][move->fromPos.y] = m_curPosition[move->toPos.x][move->toPos.y];
	// recover
	m_curPosition[move->toPos.x][move->toPos.y] = chess_id;
}

// TODO:@xudong
int SearchEngine::IsGameOver(int position[CHESSBOARD_WIDTH][CHESSBOARD_WIDTH], int depth)
{
	return 0;
}