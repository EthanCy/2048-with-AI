#include "client.h"
#include <fstream>

int Client::isSingleMode() {
	std::cout << "Select playstyle: (1) AI spectator mode (2) Single-player" << std::endl;

        char cmd;

        while (std::cin >> cmd && cmd != '1' and cmd != '2') {
                std::cout << "Please enter valid character: 1 or 2." << std::endl;
        }

	return cmd - '1';
}

void Client::playAI() {
	int alpha, beta;
	std::cin >> alpha;
        std::cin >> beta;	
	Board board{};
	board.initializeDisplay(true);
	BasicAI ai{&board, 4, alpha, beta};
	try {
              ai.play();
        } catch (...) {
              return;
        }
        //std::cout << board << std::endl;
}

void Client::playSingle() {
	Board board{};
	char cmd;
	bool isShifted = true;

	while (std::cin >> cmd && (!isShifted || !board.isGameOver())) {
		if (cmd == 'w' || cmd == 'a' || cmd == 's' || cmd == 'd') {
			isShifted = board.shift(cmd);
			
			if (isShifted) {
				board.addRandomBlock();
			}
                } else {
			std::cout << "Please enter a valid character: w (up), s (down), a (left), d (right)" << std::endl;
		}
		//std::cout << "NEW HIGHEST TILE: " << board.getScore() << std::endl;
	}
	std::cout << "GAME OVER before destroy board" << std::endl;
	std::ofstream scoreFile ("aiScore.txt");
	if (scoreFile.is_open())
	{
		scoreFile << board.maxCornerTileSum() << std::endl;
		scoreFile.close();
	}
	else std::cout << "Unable to open file";
}

void Client::play() {
	if (isSingleMode()) {
		playSingle();
	} else {
		playAI();
	}
	
	std::cout << "Good luck next time!" << std::endl;
}

