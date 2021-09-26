#include "basicAI.h"
#include "board.h"
#include <iostream>
#include <limits.h>
#include <algorithm>
#include <math.h>

BasicAI::BasicAI(Board * b, int depth, int alpha, int beta): board{b}, depth{depth}, alpha{alpha}, beta{beta} {}

int BasicAI::getBoardScore(Board * currBoard) {
	//if (currBoard->isCornerHighestTile()) {
	//	return currBoard->getScore()*3;
	//}
	//std::cout << "currBoard->getScore(): " << currBoard->getScore() << std::endl;
	//std::cout << "currBoard->maxCornerTileSum(): " << currBoard->maxCornerTileSum() << std::endl;
	return alpha * currBoard->maxCornerTileSum() + beta * currBoard->getNumOfEmptyBlocks(); //currBoard->getScore() + 
}

float BasicAI::iterate(Board * currBoard, int cmd, int currDepth) {
	// Basecase: we have reached the end of our allowed depth and must return a board evaluation.
        if (!currDepth) {
                return getBoardScore(currBoard);
        }
	
	currBoard = new Board{currBoard};
	bool isShifted = currBoard->shift(cmd);
	
	// If there is no shift, return sentinal value.
	if (!isShifted) {
		return -1;
        }

	if (!currBoard->isCornerHighestTile()) {
		return INT_MIN;
	}
	
	// Note: must be at least one empty block otherwise there could not be a shift.
	std::vector<int> emptyBlocks = currBoard->getEmptyBlocks();
	std::vector<float> maxScores;
	float avgScore = 0;

//	std::cout << "DEPTH: " << currDepth << std::endl;
//	std::cout << "getBoardScore(currBoard): " << getBoardScore(currBoard) << std::endl;

	for (int emptyBlock : emptyBlocks) {
		currBoard->setBlock(emptyBlock,2);

		float nextMaxScore = INT_MIN;
		//avgScore = 0;
		for (char nextCmd : cmds) {
			float nextScore = iterate(currBoard, nextCmd, currDepth-1);
			if (nextScore > nextMaxScore) {
				nextMaxScore = nextScore;
			}
		}

		if (nextMaxScore == INT_MIN) return INT_MIN;

//		std::cout << "nextMaxScore for 2 block: " << nextMaxScore << std::endl;
//		std::cout << "score for currBoard: " << getBoardScore(currBoard) << std::endl;

		avgScore += 0.9*nextMaxScore;
			
		currBoard->setBlock(emptyBlock,4);

		nextMaxScore = INT_MIN;

                for (char nextCmd : cmds) {
                        float nextScore = iterate(currBoard, nextCmd, currDepth-1);
                        if (nextScore > nextMaxScore) {
                                nextMaxScore = nextScore;
                        }
                }

		if (nextMaxScore == INT_MIN) return INT_MIN;

                avgScore += 0.1*nextMaxScore;

		maxScores.emplace_back(avgScore);
//		std::cout << "nextMaxScore for 4 block: " << nextMaxScore << std::endl;


		currBoard->setBlock(emptyBlock,0);
	}

	avgScore /= emptyBlocks.size();

	return avgScore;
	

}

void BasicAI::play() {
	char testDevice;
	bool isShifted = true;
	while (/*std::cin >> testDevice &&*/ (!isShifted || !board->isGameOver())) {
		std::cout << "board: " << std::endl << *board << std::endl;
		float bestScore = INT_MIN;
		char bestCmd = 'a';
		for (char cmd : cmds) {
			int numEmptyBlocks = board->getNumOfEmptyBlocks(); 
			float currScore;

			if (numEmptyBlocks < 6) {
				currScore = iterate(board, cmd, depth+1);
			}
			if (numEmptyBlocks < 12) {
				currScore = iterate(board, cmd, depth);
			} else {
				currScore = iterate(board, cmd, depth-1);
			}

			//float currScore = iterate(board, cmd, depth);
			std::cout << "cmd: " << cmd << ", currScore: " << currScore << std::endl;
			if (currScore >= bestScore && currScore != -1) {
				bestScore = currScore;
				bestCmd = cmd;
			}
		}

		isShifted = board->shift(bestCmd);

		if (isShifted) {
			board->addRandomBlock();
		}
	}	
	std::cout << "END OF GAME" << std::endl;
	while (std::cin >> testDevice) {}
}

