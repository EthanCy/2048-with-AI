#ifndef _CLIENT_
#define _CLIENT_

#include <iostream>
#include <stdexcept>
#include "board.h"
#include "basicAI.h"

class Board;

class Client
{
	int isSingleMode();
	void playAI();
	void playSingle();

	public:
	void play();
};

#endif
