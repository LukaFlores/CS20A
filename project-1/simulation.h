#ifndef SIMULATION_H
#define SIMULATION_H

#include "life.h"
#include "world.h"

class Simulation {
    public:
        Simulation(Life **life, int numLife);
        ~Simulation(); 
        void simulate(); 
        void report();
        int two(int u);
        int three(int x);
        void one(int t);
    private:
        void delay(int ms) const; 
        int watchme;
        World * m_world;
        int m_steps;
        bool m_automate;
};

#endif //SIMULATION_H
