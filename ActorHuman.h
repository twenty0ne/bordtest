#ifndef _ACTOR_HUMAN_H_
#define _ACTOR_HUMAN_H_

#include "Actor.h"

class ActorHuman : public Actor
{
public:
									ActorHuman();
									~ActorHuman();

	/*virtual*/ void				Think(float dt);
	/*virtual*/ void				DoAction();
	/*virtual*/ ActorAction			MakeAction(int fx, int fy, int tx, int ty);

protected:
	void		MoveChess();
	void		TurnChess();
};

#endif