//
//  Curves.h
//  
//
//  Created by Curtis Kroetsch on 2013-07-04.
//
//

#ifndef ____Curves__
#define ____Curves__

#include <iostream>


#include "Curves.hpp"
#include "LSystem.hpp"
#include "Bug.hpp"
#include <string>


/* The Hilbert Curve as a Lindenmayer system,
 http://en.wikipedia.org/wiki/Hilbert_curve
 
 Alphabet : A, B
 Constants : F + -
 Axiom : A
 
 Production rules:
 A → - B F + A F A + F B -
 B → + A F - B F B - F A +
 
 Meaning:
 F → "draw forward"
 - → "turn left 90°"
 + → "turn right 90°"
 */

// Create a Hilbert L-System of a specified order as shown above
inline LSystem Hilbert(uint order = 1) {
    
    Rules prod_rules; // Production Rules
    std::string axiom = "A"; // Axiom
    
    prod_rules.insert(Rule('A', "-BF+AFA+FB-"));
    prod_rules.insert(Rule('B', "+AF-BFB-FA+"));
    
    return LSystem(prod_rules, axiom, order);
}





/* ------ Some other fractals, including Koch and Dragon --------- */

// Create a 90 degree Koch L-System of a specified order
inline LSystem Koch(uint order = 1) {
    
    Rules prod_rules;
    std::string axiom = "F";
    
    prod_rules.insert(Rule('F', "F+F-F-F+F"));
    prod_rules.insert(Rule('B', "+AF-BFB-F"));
    
    return LSystem(prod_rules, axiom, order);
}


// Create a Dragon L-System of a specified order
inline LSystem Dragon(uint order = 1) {
    
    Rules prod_rules;
    std::string axiom = "FX";
    
    prod_rules.insert(Rule('X', "X+YF"));
    prod_rules.insert(Rule('Y', "FX-Y"));
    
    return LSystem(prod_rules, axiom, order);
}



#endif /* defined(____Curves__) */
