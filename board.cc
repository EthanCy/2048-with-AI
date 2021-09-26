#include <stdlib.h>
#include <time.h>
#include <stdexcept>
#include <math.h>
#include "window.h"
#include "board.h"
#include <iostream> // remove later, for testing purposes
Board::Board() {
	score = 0;
	numOfEmptyBlocks = 16;
	
	// Initialize board
	for (int i  = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			// coords are j,i for draw
			blocks.emplace_back(0);
		}
	}
}

Board::~Board() {
	delete window;
}

Board::Board(Board * boardCopy) {
	score = boardCopy->score;
	numOfEmptyBlocks = boardCopy->numOfEmptyBlocks;
	highestTile = boardCopy->highestTile;
	window = nullptr;
	blocks = boardCopy->blocks;
}

void Board::initializeDisplay(bool quiet) {
	// Initialize display
        if (!quiet) {
                window = new Xwindow{450, 550};
                for (int i = 0; i <= dim; i++) {
                        window->fillRectangle(i * (size + 10), 0, 10, dim * (size + 10));
                        window->fillRectangle(0, i * (size + 10), dim * (size + 10), 10);
                }
        } else {
                window = nullptr;
        }

        // Game starts with two blocks
        highestTile = addRandomBlock();
        int nextTileNum = addRandomBlock();

        if (nextTileNum > highestTile) {
                highestTile = nextTileNum;
        }
}

bool Board::shift(char direction) {
	bool isShifted = false;
	
	if (direction == 'a') {
		for (int i = 0; i < dim; i++) {
			int new_index = 0;

			for (int j = new_index; j < dim; j++) {
				if (!blocks[i*dim+j]) {
					continue;
                                }
				int next_j = j+1;
				while (next_j < dim && !blocks[i*dim+next_j]) next_j++;

				if (next_j < dim && blocks[i*dim+j] == blocks[i*dim+next_j]) {
					blocks[i*dim+new_index] = blocks[i*dim+j] * 2;
					draw(i,new_index);

					if (blocks[i*dim+new_index] > highestTile) {
						highestTile = blocks[i*dim+new_index];
					}

					j = next_j;
                                        new_index++;
                                        numOfEmptyBlocks++;
                                        isShifted = true;
					continue;
				}
				
				if (j > new_index) {
					if (blocks[i*dim+new_index] != blocks[i*dim+j]) {
						blocks[i*dim+new_index] = blocks[i*dim+j];
						draw(i, new_index);
					}
					isShifted = true;
				}

				new_index++;
			}

			for (; new_index < dim; new_index++) {
				if (blocks[i*dim+new_index]) {
					blocks[i*dim+new_index] = 0;
					draw(i, new_index);
				}
			}

		}
	} else if (direction == 'd') {
                for (int i = 0; i < dim; i++) {
                        int new_index = dim-1;

                        for (int j = new_index; j >= 0; j--) {
                                if (!blocks[i*dim+j]) {
                                        continue;
                                }
                                int next_j = j-1;
                                while (next_j >= 0 && !blocks[i*dim+next_j]) next_j--;

                                if (next_j >= 0 && blocks[i*dim+j] == blocks[i*dim+next_j]) {
                                        blocks[i*dim+new_index] = blocks[i*dim+j] * 2;
					draw(i, new_index);
					
					if (blocks[i*dim+new_index] > highestTile) {
                                                highestTile = blocks[i*dim+new_index];
                                        }

					j = next_j;
                                        new_index--;
                                        numOfEmptyBlocks++;
                                        isShifted = true;
					continue;
                                }

                                if (j < new_index) {
					if (blocks[i*dim+new_index] != blocks[i*dim+j]) {
						blocks[i*dim+new_index] = blocks[i*dim+j];
						draw(i, new_index);
					}
					isShifted = true;
                                }

                                new_index--;
                        }

                        for (; new_index >= 0; new_index--) {
                                if (blocks[i*dim+new_index]) {
                                        blocks[i*dim+new_index] = 0;
					draw(i, new_index);
                                }
                        }

                }
        } else if (direction == 'w') {
                for (int i = 0; i < dim; i++) {
                        int new_index = 0;

                        for (int j = new_index; j < dim; j++) {
                                if (!blocks[j*dim+i]) {
                                        continue;
                                }
                                int next_j = j+1;
                                while (next_j < dim && !blocks[next_j*dim+i]) next_j++;

                                if (next_j < dim && blocks[j*dim+i] == blocks[next_j*dim+i]) {
                                        blocks[new_index*dim+i] = blocks[j*dim+i] * 2;
                                        draw(new_index,i);
                                        
					if (blocks[new_index*dim+i] > highestTile) {
                                                highestTile = blocks[new_index*dim+i];
                                        }

					j = next_j;
                                        new_index++;
                                        numOfEmptyBlocks++;
                                        isShifted = true;
					continue;
                                }

                                if (j > new_index) {
                                        if (blocks[new_index*dim+i] != blocks[j*dim+i]) {
                                                blocks[new_index*dim+i] = blocks[j*dim+i];
                                                draw(new_index,i);
                                        }
                                        isShifted = true;
                                }

                                new_index++;
                        }

                        for (; new_index < dim; new_index++) {
                                if (blocks[new_index*dim+i]) {
                                        blocks[new_index*dim+i] = 0;
                                        draw(new_index,i);
                                }
                        }

                }
        } else if (direction == 's') {
                for (int i = 0; i < dim; i++) {
                        int new_index = dim-1;

                        for (int j = new_index; j >= 0; j--) {
                                if (!blocks[j*dim+i]) {
                                        continue;
                                }
                                int next_j = j-1;
                                while (next_j >= 0 && !blocks[next_j*dim+i]) next_j--;

                                if (next_j >= 0 && blocks[j*dim+i] == blocks[next_j*dim+i]) {
                                        blocks[new_index*dim+i] = blocks[j*dim+i] * 2;
                                        draw(new_index,i);
					
					if (blocks[new_index*dim+i] > highestTile) {
                                                highestTile = blocks[new_index*dim+i];
                                        }

					j = next_j;
                                        new_index--;
                                        numOfEmptyBlocks++;
                                        isShifted = true;
                                        continue;
                                }

                                if (j < new_index) {
                                        if (blocks[new_index*dim+i] != blocks[j*dim+i]) {
                                                blocks[new_index*dim+i] =blocks[j*dim+i];
                                                draw(new_index,i);
                                        }
                                        isShifted = true;
                                }

                                new_index--;
                        }

                        for (; new_index >= 0; new_index--) {
                                if (blocks[new_index*dim+i]) {
                                        blocks[new_index*dim+i] = 0;
                                        draw(new_index,i);
                                }
                        }

                }
        }

	return isShifted;
}

int Board::getScore() {
	return highestTile;
}

int Board::getNumOfEmptyBlocks() {
	return numOfEmptyBlocks;
}

int Board::tileSumByRow(int row, int col) {
	int tileSum = 0;
        int prevHigh = highestTile;
        bool asc = col ? false : true;

        for (int i = row; i >= 0 && i < dim; i += row ? -1 : 1) {
                for (int j = asc ? 0 : dim-1; j >= 0 and j < dim; j += asc ? 1 : -1) {
                        if (blocks[i*dim+j] < prevHigh/2 || blocks[i*dim+j] > prevHigh) return tileSum;
                        prevHigh = blocks[i*dim+j];
                        tileSum += prevHigh;
                }
                asc = !asc;
        }

	return tileSum;

}

int Board::tileSumByCol(int row, int col) {
	int tileSum = 0;
        int prevHigh = highestTile;
        int asc = row ? false : true;

        for (int j = col; j >= 0 && j < dim; j += col ? -1 : 1) {
                for (int i = asc ? 0 : dim-1; i >= 0 and i < dim; i += asc ? 1 : -1) {
                        if (blocks[i*dim+j] < prevHigh/2 || blocks[i*dim+j] > prevHigh) return tileSum;
                        prevHigh = blocks[i*dim+j];
                        tileSum += prevHigh;
                }
                asc = !asc;
        }

	return tileSum;
}

int Board::maxCornerTileSum() {
	int maxSum = 0;
	if (blocks[0] == highestTile) {
		//int rowSum = tileSumByRow(0,0);
		//int colSum = tileSumByCol(0,0);
		//std::max(rowSum,colSum)-std::min(rowSum,colSum);
		int currSum = std::max(tileSumByRow(0,0),tileSumByCol(0,0));	
		if (currSum > maxSum) maxSum = currSum;
	}
	if (blocks[(dim-1)*dim] == highestTile) {
		//int rowSum = tileSumByRow(dim-1,0);
                //int colSum = tileSumByCol(dim-1,0);
		//std::max(rowSum,colSum)-std::min(rowSum,colSum);
		int currSum = std::max(tileSumByRow(dim-1,0),tileSumByCol(dim-1,0));
                if (currSum > maxSum) maxSum = currSum;
        }
	if (blocks[dim-1] == highestTile) {
		//int rowSum = tileSumByRow(0,dim-1);
                //int colSum = tileSumByCol(0,dim-1);
		int currSum = std::max(tileSumByRow(0,dim-1),tileSumByCol(0,dim-1));
                if (currSum > maxSum) maxSum = currSum;
        }
	if (blocks[dim*dim-1] == highestTile) {
		//int rowSum = tileSumByRow(dim-1,dim-1);
                //int colSum = tileSumByCol(dim-1,dim-1);
		int currSum = std::max(tileSumByRow(dim-1,dim-1),tileSumByCol(dim-1,dim-1));
                if (currSum > maxSum) maxSum = currSum;
        }
	return maxSum;
}

std::vector<int> Board::getEmptyBlocks() {
	std::vector<int> emptyBlocks;

	if (!numOfEmptyBlocks) {
		return emptyBlocks;
	}

	for (int i  = 0; i < dim; i++) {
                for (int j  = 0; j < dim; j++) {
                        if (!blocks[i*dim+j]) {
				emptyBlocks.emplace_back(i*dim+j);
                        }
                }
        }

	return emptyBlocks;
}

int Board::addRandomBlock() {
	srand (time(0));
	int num = rand() % 100 + 1;
	if (num > 90) {
		num = 4;
	} else {
		num = 2;
	}
	int emptyBlockNum = rand() % numOfEmptyBlocks; // 0 to 15, nOEB = 16
	int emptyBlockCount = 0;
	
	for (int i  = 0; i < dim; i++) {
		for (int j  = 0; j < dim; j++) {
			if (!blocks[i*dim+j] && emptyBlockCount == emptyBlockNum) {
				blocks[i*dim+j] = num;
				draw(i,j);
				numOfEmptyBlocks--;
				return num;
			}
			
			if (!blocks[i*dim+j]) {
				emptyBlockCount++;
			}
		}
	}
	return 0;
}

void Board::draw(int i, int j) {
	if (!window) {
                return;
        }

	int num = blocks[i*dim+j];

        if (!num) {
                window->fillRectangle(j + 10 * (j + 1) + size * j, i + 10 * (i + 1) + size * i, size, size, Xwindow::White);
                return;
        }

        double colorNum = log2 (num);
        window->fillRectangle(j + 10 * (j + 1) + size * j, i + 10 * (i + 1) + size * i, size, size, colorNum + 1);
        window->drawString(j + 10 * (j + 1) + size * j + size / 2, i + 10 * (i + 1) + size * i + size / 2, std::to_string(num), 1);

}

void Board::setBlock(int block, int value) {
	blocks[block] = value;
}

bool Board::isGameOver() {
	if (numOfEmptyBlocks > 0) {
		return false;
	}
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			if (i > 0 && blocks[i*dim+j] == blocks[(i - 1)*dim+j]) {
				return false;
			}
			if (j > 0 && blocks[i*dim+j] == blocks[i*dim+j-1]) {
                                return false;
                        }
		}
	}
	return true;
}

bool Board::isCornerHighestTile() {
	if (highestTile <= 4) {
		return true;
	}
	return blocks[0]==highestTile || blocks[dim-1]==highestTile || blocks[(dim-1)*dim]==highestTile || blocks[dim*dim-1]==highestTile;
}

std::ostream& operator<<(std::ostream& out, Board& b) {
	for (int i = 0; i < b.dim; i++) {
		for (int j = 0; j < b.dim; j++) {
			if (!b.blocks[i*b.dim+j]) {
				out << '*';
			} else {
				out << b.blocks[i*b.dim+j];
			}
		}
		out << std::endl;
	}
	return out;
}

