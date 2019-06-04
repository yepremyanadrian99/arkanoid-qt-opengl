#include "board.h"

Board::Board() {
}

Board& Board::getInstance() {
    static Board instance;
    return instance;
}