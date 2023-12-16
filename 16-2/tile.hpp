#ifndef TILE
#define TILE

class tile {
    private:
        bool left;
        bool right;
        bool up;
        bool down;

    public:
        tile();
        bool leftEnergized();
        bool rightEnergized();
        bool upEnergized();
        bool downEnergized();
        bool energized(int direction);

        void setLeft();
        void setRight();
        void setUp();
        void setDown();
        void setEnergized(int direction);

        bool anyEnergized();
};

#endif