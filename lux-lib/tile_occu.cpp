
#include "tile_occu.hpp"


bool TileOccuppied::push( const lux::Unit & uni, const lux::DIRECTIONS & dir )
{
	if ( empty( uni.pos ) )
	{
		lux::Position target = uni.pos;
		switch(dir)
		{
			case lux::DIRECTIONS::NORTH:
			{
				target.y -= 1;
			}
			break;
			case lux::DIRECTIONS::EAST:
			{
				target.x += 1;
			}
			break;
			case lux::DIRECTIONS::SOUTH:
			{
				target.y += 1;
			}
			break;
			case lux::DIRECTIONS::WEST:
			{
				target.x -= 1;
			}
			break;
			case lux::DIRECTIONS::CENTER˙:
			{
				//nothing
			}
			break;
			default:
			break;
		}

		spaceOccuppied.insert( {uni.id, target} );
		return true;
	}
	return false;
}

bool TileOccuppied::empty( const lux::Position & pos )
{
	for ( auto it = spaceOccuppied.begin(); it != spaceOccuppied.end(); ++it )
	{
		if ( it->second == pos )
			return false;
	}

/*
	for ( auto it = spaceOccuppiedNext.begin(); it != spaceOccuppiedNext.end(); ++it )
	{
		if ( it->second == pos )
			return false;
	}
*/

	return true;
}

void TileOccuppied::update()
{
	spaceOccuppiedNext.clear();
	spaceOccuppiedNext = spaceOccuppied;
	spaceOccuppied.clear();
}
