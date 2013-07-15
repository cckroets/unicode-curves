//
//  main.cpp
//  test
//
//  Created by Curtis Kroetsch on 2013-07-04.
//  Copyright (c) 2013 Curtis Kroetsch. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <cmath>
#include <bitset>
#include "../../Curves.h"
#include "../../LSystem.hpp"
#include "../../Bug.hpp"



int main(int argc, const char * argv[]) {
    
    const uint order = 4;
    
    LSystem H = Hilbert(order);
    LSystem K = Koch(order);
    LSystem D = Dragon(order);
    
    H.print_curve();

    return 0;
}


