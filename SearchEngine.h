#ifndef _SEARCH_ENGINE_H_
#define _SEARCH_ENGINE_H_

class EveluationEngine;
class MoveGenerator;

class SearchEngine
{
public:
	SearchEngine();
	virtual ~SearchEngine();

	virtual			SearchOneGoodMove(byte position[CHESSBOARD_WIDHT][CHESSBOARD_WIDHT]) = 0;
	void			SetSearchDeepth(int depth) { m_searchDepth = depth; }
	void			SetEveluatorEngine(EveluationEngine* pEval) { m_pEval = pEval; }
	void			SetMoveGenerator(MoveGenerator* pMg) { m_pMg = pMg; }

protected:
	// make chessboard after moving on step
	int				MakeMove(ChessMove* move);
	// recover
	void			UnMakeMove(ChessMove* move, int chess_id);
	// is over
	int				IsGameOver(int position[CHESSBOARD_WIDTH][CHESSBOARD_WIDTH], int depth);

protected:
	int				m_curPosition[CHESSBOARD_WIDTH][CHESSBOARD_WIDTH];
	ChessMove		m_bestMove;

	MoveGenerator*	m_pMg;
	EveluationEngine*	m_pEval;

	int				m_searchDepth;
	int				m_curMaxDepth;
};

#endif