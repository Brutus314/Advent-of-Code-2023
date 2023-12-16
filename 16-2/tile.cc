#include "tile.hpp"

const int LEFT = 0;
const int RIGHT = 1;
const int UP = 2;
const int DOWN = 3;

tile::tile() {
    left = false;
    right = false;
    down = false;
    up = false;
}

bool tile::leftEnergized() {
    return left;
}
bool tile::rightEnergized(){
    return right;
}
bool tile::upEnergized(){
    return up;
}
bool tile::downEnergized(){
    return down;
}

bool tile::energized(int direction) {
    switch (direction) {
        case LEFT:
            return left;
        case RIGHT:
            return right;
        case UP:
            return up;
        case DOWN:
            return down;
    }
    return false;
}

void tile::setLeft() {
    left = true;
}
void tile::setRight() {
    right = true;
}
void tile::setUp() {
    up = true;
}
void tile::setDown() {
    down = true;
}

void tile::setEnergized(int direction) {
    switch (direction) {
        case LEFT:
            setLeft();
            break;
        case RIGHT:
            setRight();
            break;
        case UP:
            setUp();
            break;
        case DOWN:
            setDown();
            break;
    }
}

bool tile::anyEnergized() {
    return leftEnergized() || rightEnergized() || upEnergized() || downEnergized();
}