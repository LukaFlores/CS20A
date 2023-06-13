#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>

#ifdef _MSC_VER // DO NOT BREAK APART THE PREPROCESSOR DIRECTIVES
#include <windows.h>
#else // DO NOT BREAK APART THE PREPROCESSOR DIRECTIVES
      // not Microsoft Visual C++, so assume UNIX interface
#include <iostream>
#include <cstring>
#include <cstdlib>
#endif // DO NOT BREAK APART THE PREPROCESSOR DIRECTIVES



///////////////////////////////////////////////////////////////////////////
// Global Constants
///////////////////////////////////////////////////////////////////////////
#include "constants.h"

///////////////////////////////////////////////////////////////////////////
// Type Definitions
///////////////////////////////////////////////////////////////////////////

#include "life.h"
#include "pent.h"
#include "square.h"
#include "slider.h"
#include "blink4.h"
#include "world.h"
#include "simulation.h"


int main() {
    const int numLife = 4;
    Life **population = new Life*[numLife];
    population[0] = new Slider(8, 4);
    population[1] = new Pent(18, 14);
    population[2] = new Blink4(3, 13);
    population[3] = new Square(14, 10);
    // Create the game
    Simulation s(population, numLife);
    // Debugger Exercise
    s.one('k' - 'h');
    // Run the game
    s.simulate();
    // Report
    s.report();
    // Clean up
    delete population[0];
    delete population[1];
    delete population[2];
    delete population[3];
    delete[] population;
}      

////ANAYLSIS PART 2:
//#include "simulation.h"
//#include "simulation.h"
//#include "world.h"
//#include "world.h"
//#include "life.h"
//#include "life.h"
//#include "square.h"
//#include "square.h"
//#include "pent.h"
//#include "pent.h"
//#include "blink4.h"
//#include "blink4.h"
//#include "slider.h"
//#include "slider.h"
//#include "constants.h"
//#include "constants.h"
//int main(){}


////ANAYLSIS PART 3:
//#include"simulation.h"
//        int main() {
//          World w;
//          Simulation s(nullptr, 0);
//}





