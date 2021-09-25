#ifndef MAP_TERMINAL
#define MAP_TERMINAL

#include <fstream>
#include <iostream>

#include "../lux/map.hpp"
#include "../lux/position.hpp"
#include "lib.hpp"

class Map_Terminal
{
	private:
		
		
		
	public:
		
		Map_Terminal(){};
		
		void draw( const lux::GameMap & map ) const;
		
		void draw( const std::vector<lib::mapTrees> & ) const;
	
};

#endif