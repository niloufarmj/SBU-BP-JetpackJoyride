#ifndef ZAPPER_H
#define ZAPPER_H

#include "SBDL.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "stdafx.h"


enum ZapperState {
    ZAPPER_FIRST,
    ZAPPER_SECOND,
    ZAPPER_THIRD,
    ZAPPER_FOURTH
};

class Zapper {
public:
    Zapper();
    // Add constructor(s) and any other member functions as needed
    
    void update();
    void draw();

    Texture first;
    Texture second;
    Texture third;
    Texture fourth;
    int x;
    int y;
    int counter;
    int velocity;
    int currentState;
    int currentIndex;
    SDL_Rect rect;
};

#endif // ZAPPER_H