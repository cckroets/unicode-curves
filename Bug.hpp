//
//  Bug.hpp
//
//
//  Created by Curtis Kroetsch on 2013-06-30.
//
//

#ifndef _BUG_hpp
#define _BUG_hpp

#include <vector>
#include <deque>
#include <string>
#include <utility>
#include <algorithm>
#include <iostream> 

typedef unsigned int uint;


// Flags: UP|LEFT|DOWN|RIGHT
enum BDC { NEWLN=16, BLANK=0, EW=5, SE=3, SW=6, NWE=13, NE=9, NW=12, SWE=7, NS=10, NSW=14, NSE=11, NSEW=15 };

enum Compass { NORTH = 8, WEST = 4, SOUTH = 2, EAST = 1 };

// Hard-code of the Unicode values
inline uint unicode_value(BDC c) {
 
    switch (c) {
        case BLANK: return 0x20;    case NS:   return 0x2551;
        case EW:   return 0x2550;   case SE:    return 0x2554;
        case SW:    return 0x2557;  case NE:    return 0x255A;
        case NW:    return 0x255D;  case NSW:  return 0x2563;
        case NSE:  return 0x2560;   case SWE:  return 0x2566;
        case NWE:  return 0x2569;   case NSEW: return 0x256C;
        case NORTH: return 0x2551;  case SOUTH: return 0x2551;
        case EAST:  return 0x2550;  case WEST:  return 0x2550;
        case NEWLN: return 0x0A;
    }
}

// A grid is a 2D vector of box drawing characters
typedef std::deque<BDC> Row;
typedef std::deque<Row> Grid;

// A point somewhere in 2D space
struct point {
    int x;
    int y;
    point(int x, int y) : x(x), y(y) {};
};

// A bug that draws a curve
class Bug {
    
private:
    
    Grid _grid;     // The grid of characters representing the curve
    point _bug;     // Bug coordinates
    point _orig;    // Bug starting coordinates
    Compass _dir;   // The direction the bug is facing: [0,4)
    
    void x_buffer(); // Buffer each row with a blank space
    void y_buffer(); // Buffer the grid with a blank row
    void x_push();   // Push a blank space onto each row
    void y_push();   // Push a blank row onto the grid
    
    int grid_x() { return _bug.x + _orig.x; };
    int grid_y() { return _bug.y + _orig.y; };
    
    void insert(BDC sym); // Insert a BDC at the bug's position
    
public:
    
    // Move in the direction specified
    enum Direction { LEFT, RIGHT, FORWARD };
    void move(Direction);

    std::vector<uint> walk(); // Return the grid that the Bug did as a vector of BDC
    
    // Create a bug with direction d
    Bug(Compass d=NORTH) : _dir(d), _bug(0,0), _orig(0,0) {
        Row blank(1,BLANK);
        _grid.push_back(blank);
    }
};

inline size_t height(Grid& g) { return g.size(); }
inline size_t width(Grid& g) { return g.front().size(); }

// Insert a blank space at the front of a Row
inline void buff_blank(Row& R) { R.push_front(BLANK); }

// Push a blank space onto all Rows in the grid
inline void Bug::x_buffer() {
    std::for_each(_grid.begin(),_grid.end(),buff_blank);
    _orig.x++;
}

// Push a blank space onto the end of a Row
inline void push_blank(Row& R) { R.push_back(BLANK); }

// Push a blank space onto the end of each row
inline void Bug::x_push() {
    std::for_each(_grid.begin(),_grid.end(),push_blank);
}

// Insert a blank row at the first row of the grid
inline void Bug::y_buffer() {
    _grid.push_front(Row(width(_grid),BLANK));
    _orig.y++;
}

// Push a blank row onto the the end of the grid
inline void Bug::y_push() {
    _grid.push_back(Row(width(_grid),BLANK));
}

// Get the new coordinates of the bug after moving
inline void new_coords(Compass new_dir, point& p) {
    // Changes the references to each coordinate
    switch (new_dir) {
        case NORTH: p.y--; break;
        case EAST : p.x++; break;
        case SOUTH: p.y++; break;
        case WEST : p.x--;
    }
}

// Get the opposite direction on the compass
inline Compass opposite(Compass dir) {
    switch (dir) {
        case NORTH: return SOUTH;   case SOUTH: return NORTH;
        case WEST:  return EAST;    case EAST:  return WEST;
    }
}

// Move the bug either left, right or forward
inline void Bug::move(Direction way) {
    
    // Determine which way the bug will face after moving
    Compass new_dir;
    switch (way) {
        case LEFT  : new_dir = (_dir == EAST) ? NORTH : Compass(_dir >> 1); break;
        case RIGHT : new_dir = (_dir == NORTH) ? EAST : Compass(_dir << 1); break;
        case FORWARD : new_dir = _dir;
    }

    BDC next = BDC(opposite(_dir) | new_dir);    // Get the next box-drawing character
 
    insert(next);                        // Insert the next symbol at the bug's spot
    new_coords(new_dir, _bug);           // Get the new coordinates of the bug
    _dir = new_dir;                      // Update the direction after turning
}

// Insert a symbol at the bug's position
inline void Bug::insert(BDC sym) {

    // Modify the grid so that the new position fits on it
    if (grid_x() < 0) x_buffer();
    else if (grid_y() < 0) y_buffer();
    else if (grid_x() >= width(_grid)) x_push();
    else if (grid_y() >= height(_grid)) y_push();
    
    // Finally, insert the symbol at its location
    BDC& prev = _grid.at(grid_y()).at(grid_x());
    prev = (BDC)(prev | sym);
}


// Return an instance of the bug's walk
inline std::vector<uint> Bug::walk() {
    
    Row bug_walk;
    
    // For each row, copy its contents and add a newline character
    for (Grid::iterator row = _grid.begin(); row != _grid.end(); row++) {
        // Add newline char
        row->push_back(NEWLN);
        bug_walk.insert(bug_walk.end(),row->begin(),row->end());
    }
    
    std::vector<uint> chars(bug_walk.size());
    std::transform(bug_walk.begin(),bug_walk.end(),chars.begin(),unicode_value);
    
    return chars;
}



#endif

