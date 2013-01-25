#ifndef _ACTOR_H_
#define _ACTOR_H_

class Actor
{
public:
	Actor();
	virtual ~Actor();

	virtual void		Think(float dt);
	virtual void		DoAction();

protected:
	virtual void		MoveChess(int from_x, int from_y, int to_x, int to_y);
	virtual void		TurnChess(int target_x, int target_y);
};

#endif

