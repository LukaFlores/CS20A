#include <iostream>
#include "world.h"

World::World() {
    m_toggle = true;
    m_grid_1 = new char*[CANVAS_ROW];
    m_grid_2 = new char*[CANVAS_ROW];
    for (char i = 0; i < CANVAS_ROW; i++) {
        m_grid_1[i] = new char[CANVAS_COL];
        m_grid_2[i] = new char[CANVAS_COL];
    }
    for (char i = 0; i < CANVAS_ROW; i++) {
        for (char j = 0; j < CANVAS_COL; j++) {
            m_grid_1[i][j] = DEAD;
        }
    }
}
World::~World() {
    for (char i = 0; i < CANVAS_ROW; i++) {
        delete[] m_grid_1[i];
        delete[] m_grid_2[i];
    }
    delete[] m_grid_1;
    delete[] m_grid_2;
}
void  World::render() const {
    clearScreen();
    if (m_toggle) {
        for (char i = 0; i < CANVAS_ROW; i++) {
            for (char j = 0; j < CANVAS_COL; j++) {
                std::cout << m_grid_1[i][j];
            }
            std::cout << std::endl;
        }
    }
    else {
        for (char i = 0; i < CANVAS_ROW; i++) {
            for (char j = 0; j < CANVAS_COL; j++) {
                std::cout << m_grid_2[i][j];
            }
            std::cout << std::endl;
        }
    }
    for (char i = 0; i < CANVAS_COL; i++) {
        std::cout << '=';
    }
    std::cout << std::endl;
}
void World::computeNextState() {
    if (m_toggle) {
        for (char i = 0; i < CANVAS_ROW; i++) {
            for (char j = 0; j < CANVAS_COL; j++) {
                m_grid_2[i][j] =
                    nextState(m_grid_1[i][j], i, j, m_toggle);
            }
        }
        m_toggle = !m_toggle;
    }
    else {
        for (char i = 0; i < CANVAS_ROW; i++) {
            for (char j = 0; j < CANVAS_COL; j++) {
                m_grid_1[i][j] =
                    nextState(m_grid_2[i][j], i, j, m_toggle);
            }
        }
        m_toggle = !m_toggle;
    }
}
bool World::initState(Life *life) {
    if (life == nullptr) {
        std::cout << "Cannot add nullptr life" << std::endl;
        return false;
    }
    for (char i = life->getRow(); i - life->getRow() < life->getHeight();
            i++) {
        for (char j = life->getCol(); j - life->getCol() < life->getWidth(); j++) {
            if (i < CANVAS_ROW && j < CANVAS_COL) {
                m_grid_1[i][j] =
                    life->getFigure(i - life->getRow(), j - life->getCol());
            }
        }
    }
    return true;
}

void World::clearScreen() const {

#ifdef _MSC_VER // DO NOT BREAK APART THE PREPROCESSOR DIRECTIVES
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(hConsole, &csbi);
            DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
            COORD upperLeft = { 0, 0 };
            DWORD dwCharsWritten;
            FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                    &dwCharsWritten);
            SetConsoleCursorPosition(hConsole, upperLeft);

#else // DO NOT BREAK APART THE PREPROCESSOR DIRECTIVES
            static const char* term = getenv("TERM");// will just write a newline in an Xcode output window
                if (term == nullptr || strcmp(term, "dumb") == 0)
                    std::cout << std::endl;
                else {
                    static const char* ESC_SEQ = "\x1B["; // ANSI Terminal esc seq:ESC [ 
                    std::cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << std::flush;

                }
#endif // DO NOT BREAK APART THE PREPROCESSOR DIRECTIVES
        //
        }


char World::nextState(char state, char row, char col, bool toggle) const {

    int yCoord = row;
    int xCoord = col;
    char neighbors = 0;
    if (toggle) {
        for (char i = yCoord - 1; i <= yCoord + 1; i++) {
            for (char j = xCoord - 1; j <= xCoord + 1; j++) {
                if (i == yCoord && j == xCoord) {
                    continue;
                }
                if (i > -1 && i < CANVAS_ROW && j > -1 && j <
                        CANVAS_COL) {
                    if (m_grid_1[i][j] == ALIVE) {
                        neighbors++;
                    }
                }
            }
        }
    }
    else {
        for (char i = yCoord - 1; i <= yCoord + 1; i++) {
            for (char j = xCoord - 1; j <= xCoord + 1; j++) {
                if (i == yCoord && j == xCoord) {
                    continue;
                }
                if (i > -1 && i < CANVAS_ROW && j > -1 && j <
                        CANVAS_COL) {
                    if (m_grid_2[i][j] == ALIVE) {
                        neighbors++;
                    }
                }
            }
        }
    }
    if (state == ALIVE) {
        return (neighbors > 1 && neighbors < 4) ? ALIVE : DEAD;
    }
    else {
        return (neighbors == 3) ? ALIVE : DEAD;
    }
}

