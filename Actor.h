#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "define.h"

class Actor
{
public:
								Actor() {}
	virtual						~Actor() {}

	virtual void				Think(float dt) {}
	virtual void				DoAction() {}
	// make a action
	// ActorAction: ACTOR_ACT_MOVE fx = from_x, fy = from_y, tx = to_x, ty = to_y
	// ActorAction: ACTOR_ACT_TURN fx = -1, fy = -1, tx = target_x, ty = target_y
	virtual ActorAction			MakeAction(int fx, int fy, int tx, int ty) { return ACTOR_ACT_NONE; }

protected:
	virtual void				MoveChess(int from_x, int from_y, int to_x, int to_y) {}
	virtual void				TurnChess(int target_x, int target_y) {}
};

#endif

