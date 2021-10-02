#ifndef TILE_OCCU_HPP
#define TILE_OCCU_HPP

#include <map>

#include "../lux/kit.hpp"

/*
 * Save occuppied cells, check if there is free cell
 * It is for avoiding collision between Units.
 * */

class TileOccuppied
{
	private:
		std::map<std::string, lux::Position> spaceOccuppied;
		std::map<std::string, lux::Position> spaceOccuppiedNext;

	public:

		TileOccuppied()
		{}

		~TileOccuppied()
		{}

		bool push( const lux::Unit & uni );

		bool empty( const lux::Position & pos );

		void update();
};

#endif
