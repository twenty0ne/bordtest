#ifndef _GAME_MAIN_H_
#define _GAME_MAIN_H_

#include "define.h"
#include "Macro.h"

class Actor;

#define theGameApp		GameMain::GetInstance()

// game main logic
class GameMain
{	
	// game status
	enum {
		GAME_STATUS_NONE,
		GAME_STATUS_RUN,
		GAME_STATUS_STOP,
		GAME_STATUS_END,
	};

public:
	static GameMain&				GetInstance();

public:
	bool 							Init();
	void							Update(float dt);

	void							MoveChess(int side, int from_x, int from_y, int to_x, int to_y);
	void							TurnChess(int side, int target_x, int target_y);

private:
									GameMain();
									~GameMain();

	void							InitChessBoard();
	bool							IsValidMove(int side, int from_x, int from_y, int to_x, int to_y);
	bool							IsValidTurn(int side, int target_x, int target_y);

	void							SwapTurn();
	void							HandleInput();

	void							PrintBoard();

private:
	static GameMain*				m_pInstance;

	int 							m_status;
	int								m_curSide;
	//Actor*						m_actorWhite;
	//Actor*						m_actorBlack;
	bool							m_actorThinking;

	int								m_curFocusX;
	int								m_curFocusY;
	int								m_curTargetX;
	int								m_curTargetY;

	int								m_boardChess[CHESSBOARD_WIDTH][CHESSBOARD_WIDTH];
	int 							m_boardState[CHESSBOARD_WIDTH][CHESSBOARD_WIDTH];

	// Actor
	Actor*							m_actor[ACTOR_COUNT];
};

#endif