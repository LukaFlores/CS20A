#include <iostream>
#include <string>

std::string decode(int digits) {
    const std::string lut[] = { 
        {101,118,98,32,99},
        {32,110,101,118,101},
        {116,32,117,32,100},
        {103,105,118,101,32},
        {111,119,110,32,32},
        {110,97,32,108,101},
        {110,97,32,103,105},
        {117,32,117,112,32},
        {114,32,103,111,110},
        {118,101,32,117,32} 
    };
    
    std::string val = "";

    while (digits != 0) {
        int lsb = digits % 10;
        digits /= 10;
        val += lut[lsb];
    }
    return val;
}

int main() {
    int watchme_digits = 42581;
    std::cout<<decode(watchme_digits)<<std::endl;
}
