#include "life.h"


int Life::getCol() const {
    return m_col;
}
int Life::getRow() const {
    return m_row;
}
int Life::getHeight() const {
    return m_height;
}
int Life::getWidth() const {
    return m_width;
}
char Life::getFigure(int r, int c) const {
    return m_pattern[r][c];
}
void Life::inWorld(World *w) {
    m_world = w;
}
void Life::inSimulation(Simulation *s) {
    m_simulation = s;
}
bool Life::areWeInASimulation() {
    return m_simulation != nullptr;
}
