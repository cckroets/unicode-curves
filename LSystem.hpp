//
//  LSystem.hpp
//  
//
//  Created by Curtis Kroetsch on 2013-07-01.
//
//

#ifndef _L_SYSTEM_hpp
#define _L_SYSTEM_hpp


#include <utility>
#include <string>
#include <map>
#include "Bug.hpp"  

// Rules for a grammar
typedef std::pair<char,std::string> Rule;
typedef std::map<char,std::string>  Rules;


// A Lindenmayer system or parallel string-rewrite systems
class LSystem {
    
private:
    // The Lindenmayer System representation of the Hilbert curve
    Rules _rules;
    
    // The aiom symbol in the L-System
    const std::string _axiom;
    
    std::string _nonTerminals;
    
    // The order of the Hilbert Curve
    const uint _order;
    
    // The production of the L-System after 'order' iterations
    std::string _production;
    std::vector<uint> _pattern;
    
    // Substitute the rule at position pos into the string
    int substitute(std::string& str, size_t pos);
    
    void rewrite(std::string&);
    
public:
    std::string production(); // Get a curve as a string of order k
    
    std::vector<uint> unicode_values() const;
    
    LSystem(Rules, std::string, uint k); // Create an L-Sytem of order k
};






#endif
