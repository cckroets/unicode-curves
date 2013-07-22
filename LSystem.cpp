//
//  LSystem.cpp
//
//
//  Created by Curtis Kroetsch on 2013-07-01.
//
//

#include "LSystem.hpp"
#include "Bug.hpp"
#include <iostream>

/*
 
L-System (Lindenmayer system) is a rewrite system. See more at
 http://en.wikipedia.org/wiki/L-system
 
 Meaning:
    'F' -> "draw forward"
    '-' -> "turn left 90°"
    '+' -> "turn right 90°"
*/


// Find and remove 'toFind' from 'str'
bool findAndRemove(std::string& str, const std::string& toFind) {
    std::size_t f = str.find(toFind);
    if (f == std::string::npos) return false;
    
    str.erase(f,toFind.length());
    return true;
}

// Find and replace 'toFind' with 'repl' inside of 'str'
bool findAndReplace(std::string& str, const std::string& toFind, const std::string& repl) {
    std::size_t f = str.find(toFind);
    if (f == std::string::npos) return false;
    
    str.replace(f,toFind.length(),repl);
    return true;
}

// Construct the H-Curve of order k
LSystem::LSystem(Rules rules, std::string ax, uint k) : _order(k), _rules(rules), _axiom(ax) {
    
    // The production string begins as the axiom
    _production = _axiom;
    
    // For each Rule append the LHS to the nonTerminals String
    for (Rules::iterator R = rules.begin(); R != rules.end(); R++) {
        // (duplicates don't matter)
        _nonTerminals.append(1,R->first);
    }
    
    // Do exactly 'k' rewrites of the L-System
    for (int rewrites = 0; rewrites < _order; rewrites++) {
        rewrite(_production);
    }

    // Remove all occurrences of bad commands 
    while (findAndRemove(_production, "+-"));
    while (findAndRemove(_production, "-+"));
    while (findAndRemove(_production, "A"));
    while (findAndRemove(_production, "B"));
    
    // Slightly modify the user's L-System to work with a DawBug
    while (findAndReplace(_production, "F", "W$"));
    while (findAndReplace(_production, "$+", "+"));
    while (findAndReplace(_production, "$-", "-"));
}

// Rewrite each occurence of each non-terminal string with its rule
void LSystem::rewrite(std::string& production) {
    
    uint offset = 0;
    
    do { // Do until all occurences have been sustituted
        // Find the first occurence of LHS
        std::size_t first = production.find_first_of(_nonTerminals,offset);
        if (first == std::string::npos) break;      // Break if there are no more occurences of LHS
        int len = substitute(production,first);     // otherwise substitute the rule
        offset = first + len;                       // and update the offset after
    
    } while (offset < production.length());
}
    
// Substitute a rule at pos
int LSystem::substitute(std::string& str, std::size_t pos) {
    // Find the rule to rewrite
    std::string rewrite = (_rules.find(str.at(pos)))->second;
    // Replace the instance of the key with the production string
    str.replace(pos,1,rewrite,0,rewrite.length());
    
    return rewrite.length();
}

// Return the produced string
std::string LSystem::production() { return _production; }

// Print the produced walk (list of BDC)
std::vector<uint> LSystem::unicode_values() const{
    

    // Tell the Bug what to do at each command
    Bug DrawBug;
    for (int i = 0; i < _production.length(); i++) {
        char command = _production[i];
        
        switch (command) {
            case 'W' : DrawBug.move(Bug::FORWARD); break;
            case '$' : DrawBug.move(Bug::FORWARD); break;
            case '+' : DrawBug.move(Bug::RIGHT); break;
            case '-' : DrawBug.move(Bug::LEFT); break;
            default: break;
        }
    }
    
    std::vector<uint> walk = DrawBug.walk();
    
    return DrawBug.walk();
    

    std::cout << std::endl;
}


    
