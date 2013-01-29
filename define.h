#ifndef _DEFINE_H_
#define _DEFINE_H_

#define CHESSBOARD_WIDTH		6

#define CHESS_STATE_BACK 		0
#define CHESS_STATE_FRONT		1

#define CHESS_NONE				0
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
#define CHESS_WHITE_BEGIN		CHESS_WHITE_PAWN
#define CHESS_WHITE_END			CHESS_WHITE_KING

#define IsBlack(x) ( x >= CHESS_BLACK_BEGIN && x <= CHESS_BLACK_END )
#define IsWhite(x) ( x >= CHESS_WHITE_BEGIN && x <= CHESS_WHITE_END )
#define IsSameSide(x, y) ( (IsBlack(x) && IsBlack(y)) || (IsWhite(x) && IsWhite(y)) ) 

#define CHESSSIDE_WHITE		1
#define CHESSSIDE_BLACK		2

int MOVE_DIR[4][2] =
{
	{0, -1},	// up
	{0,  1},	// down
	{-1, 0},	// left
	{ 1, 0},	// right
}

typedef struct{
	byte	x;
	byte	y;
}ChessPos;

typedef struct{
	int			chessId;
	ChessPos	fromPos;
	ChessPos	toPos;
	int			score;
}ChessMove;

#endif