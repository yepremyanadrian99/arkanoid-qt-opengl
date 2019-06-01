#include "board.h"

Board::Board() {
}

Board::~Board() {
    if(instance) {
        delete instance;
    }
}

Board* Board::instance = nullptr;

Board* Board::getInstance() {
    if(!instance) {
        instance = new Board();
    }
    return instance;
}