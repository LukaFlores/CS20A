#ifndef WORLD_H
#define WORLD_H

#include "life.h"
#include "constants.h"
 

class World {
    public:
        World(); 
        ~World(); 
        void render() const; 
        void computeNextState(); 
        bool initState(Life *life);
    private:
        void clearScreen() const; 
        char nextState(char state, char row, char col, bool toggle) const; 

        // The rules of Conway's Simulation of Life requires each cell to
        // examine it's neighbors. So, we have to check the entire world
        // first before we change it. We can use two copies of the world,
        // one to check the current state (current day) then another to generate
        // the next state(for the next day). We can toggle between them each
        // step, to avoid having to copy between worlds each step (day) of the game.
        char **m_grid_1;
        char **m_grid_2;
        bool m_toggle;
};

#endif //WORLD_H
