#ifndef SQUARE_H
#define SQUARE_H

#include "life.h"
#include "constants.h"

class Square : public Life {
    public:
        Square(int r, int c);
        ~Square();
};

#endif //SQUARE_H

