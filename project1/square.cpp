#include "square.h"

Square::Square(int r, int c) {
    m_col = c;
    m_row = r;
    m_height = SQUARE_SIZE;
    m_width = SQUARE_SIZE;
    //Allocate space for figure
    m_pattern = new char*[m_height];
    for (int i = 0; i < m_height; i++) {
        m_pattern[i] = new char[m_width];
    }
    //Initialize figure
    for (int i = 0; i < m_height; i++) {
        for (int j = 0; j < m_width; j++) {
            m_pattern[i][j] = ALIVE;
        }
    }
}

Square::~Square() {
    for (int i = 0; i < m_height; i++) {
        delete[] m_pattern[i];
    }
    delete[] m_pattern;
}
