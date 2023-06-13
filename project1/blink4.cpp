#include "blink4.h"

Blink4::Blink4(int r, int c) {
    m_col = c;
    m_row = r;
    m_height = BLINK4_SIZE;
    m_width = BLINK4_SIZE;
    //Allocate space for figure
    m_pattern = new char*[m_height];
    for (int i = 0; i < m_height; i++) {
        m_pattern[i] = new char[m_width];
    }
    //Initialize figure
    for (int i = 0; i < m_height; i++) {
        for (int j = 0; j < m_width; j++) {
            m_pattern[i][j] = DEAD;
        }
    }
    m_pattern[0][4] = ALIVE;
    m_pattern[1][4] = ALIVE;
    m_pattern[2][4] = ALIVE;
    m_pattern[6][4] = ALIVE;
    m_pattern[7][4] = ALIVE;
    m_pattern[8][4] = ALIVE;
    m_pattern[4][0] = ALIVE;
    m_pattern[4][1] = ALIVE;
    m_pattern[4][2] = ALIVE;
    m_pattern[4][6] = ALIVE;
    m_pattern[4][7] = ALIVE;
    m_pattern[4][8] = ALIVE;
}
Blink4::~Blink4() {
    for (int i = 0; i < m_height; i++) {
        delete[] m_pattern[i];
    }
    delete[] m_pattern;
}
