//
//  main.cpp
//  test
//
//  Created by Curtis Kroetsch on 2013-07-04.
//  Copyright (c) 2013 Curtis Kroetsch. All rights reserved.
//

#include "Curves.hpp"
#include "LSystem.hpp"
#include "Bug.hpp"



int main(int argc, const char * argv[]) {
    
    // Specify the order of the curves below
    const uint order = 8;
    
    // Create a Hilbert, Koch, and Dragon Curve
    LSystem H = Hilbert(order);
    LSystem K = Koch(order);
    LSystem D = Dragon(order);
    
    
    // Write the curves to files
    to_file("Hilbert.curve", H);
    to_file("Koch.curve", K);
    to_file("Dragon.curve", D);

    return 0;
}


