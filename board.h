#ifndef _BOARD_
#define _BOARD_

#include <vector>
#include <string>
#include <ostream>

class Xwindow;

class Board {
	const int dim = 4;
	const int size = 100;
	int score;
	int numOfEmptyBlocks;
	int highestTile;
	std::vector<int> blocks;
	Xwindow * window;
	int tileSumByRow(int, int);
	int tileSumByCol(int, int);
	public:
	Board();
	~Board();
	Board(Board *);
	void initializeDisplay(bool = false);
	bool isGameOver();
	bool isCornerHighestTile();
	bool shift(char = 'a');
	int getScore();
	int getNumOfEmptyBlocks();
	int maxCornerTileSum();
	std::vector<int> getEmptyBlocks();
	int addRandomBlock();
	void setBlock(int, int);
	void draw(int, int);
	friend std::ostream& operator<<(std::ostream&, Board&);
	friend class BasicAI;
};

#endif

