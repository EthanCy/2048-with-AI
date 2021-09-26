#ifndef _BASICAI_
#define _BASICAI_

class Board;
class Xwindow;

class BasicAI {
	Board * board;
	const int htf = 3;
	int depth;
	int alpha;
	int beta;
	char cmds[4] = {'w', 'a', 's', 'd'};
	float iterate(Board *, int, int);
	int getBoardScore(Board *);
	public:
	BasicAI(Board *, int = 0, int = 100, int = 10);
	void play();
};

#endif
