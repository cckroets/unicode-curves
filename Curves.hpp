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
#include <fstream>
#include <iostream>

typedef std::string filename;

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


/* ------ Ouput the Curves to unicode files --------- */

#define TEMP_EXT ".temp"

inline void to_temp_file(const filename& temp_file, const LSystem& Curve) {
    
    std::ofstream out(temp_file.c_str());
    
    std::vector<uint> walk = Curve.unicode_values();
    
    // Print out the int value of each unicode character
    std::vector<uint>::iterator car;
    for (car = walk.begin(); car != walk.end(); car++)
        out << *car << " ";
    
    // Flush
    out.close();
}

inline void to_file(const filename& file, const LSystem& Curve) {
    
    filename temp_name = file + TEMP_EXT;
    
    std::string racket_pwd = "/Applications/Racket\\ v5.3.1/bin/racket ";
    std::string executable = "unicode.ss";
    
    // Write the values of each char to a temporary file
    to_temp_file(temp_name, Curve);
    
    std::string command = racket_pwd + executable + " < " + temp_name + " > " + file;
    
    // Use the unicode converter to convert the values to unicode
    system(command.c_str());
    
    // Delete temp file
    std::remove(temp_name.c_str());
    
}



#endif /* defined(____Curves__) */
