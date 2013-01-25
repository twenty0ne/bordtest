#ifndef _ACTOR_HUMAN_H_
#define _ACTOR_HUMAN_H_

#include "Actor"

class ActorHuman : public Actor
{
public:
	ActorHuman();
	~ActorHuman();

	void		Think(float dt);
	void		DoAction();

protected:
	void		MoveChess();
	void		TurnChess();
};

#endif