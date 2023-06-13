#include "simulation.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>

Simulation::Simulation(Life **life, int numLife) {
    watchme = 4;
    m_steps = 0;
    m_automate = false;
    m_world = new World();
    if (life != nullptr) {
        for (int i = 0; i < numLife; i++) {
            if (life[i] != nullptr) {
                bool success = m_world->initState(life[i]);
                if (!success) {
                    std::cout << "Failed to add life to the world"
                        << std::endl;
                }
            }
        }
    }
}
Simulation::~Simulation() {
    delete m_world;
}
void Simulation::simulate() {
    while (true) {
        m_world->render();
        if (!m_automate) {
            std::cout << "command (<space> to step, <a> to automate, <q> to quit): ";
                    std::string action;
                    std::getline(std::cin, action);
                    switch (action[0])
                    {
                        default:
                            std::cout << '\a' << std::endl; // beep
                            continue;
                        case 'q':
                            std::cout << "Quitting Game." << std::endl;
                            return;
                        case 's':
                            continue;
                        case ' ':
                            break;
                        case 'a':
                            m_automate = true;
                            break;
                    }
        }
        else {
            if (m_steps >= MAX_STEPS) {
                std::cout << "Reached max steps, quitting." <<
                    std::endl;
                return;
            }
            delay(300);
        }
        m_steps++;
        m_world->computeNextState();
    }
}
void Simulation::report() {
    std::string msg = "Part 1:\n\n Watch Me Digits: 42581 \n Watch Me Message: 'never gonna let u down' \n\nPart 2:\n\n main.cpp compiled and ran, there was no error as there are file guards on each header file preventing the file from being included twice \n\nPart 3:\n\n main.cpp built sucessfully as simulation.h includes world.h, The instantiation of the World class(w) and main.cpp does not actually require an object as the simulation.h only refers to a pointer. Hence, builds sucessfully as long as the World class is declared"; // Replace Hello World with your answer.
    std::cout << msg << std::endl;
}
int Simulation::two(int u) {
    return u >> 1;
}
int Simulation::three(int x) {
    if (x % 2 == 0)
        return 1;
    else
        return 2;
}
void Simulation::one(int t) {
    int i = 7;
    int k = watchme;
    while (--i > t) {
        if (i == 0)
            k = 7;
        else if (i == 1)
            k = 9;
        else if (i == 4)
            k = 8;
        else if (i == 5)
            k = 5;
        else
            k = two(watchme);
        watchme = k;
    }
    k = three(watchme);
    watchme = k;
}
void Simulation::delay(int ms) const {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
