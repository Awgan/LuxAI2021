
#include "tile_occu.hpp"


bool TileOccuppied::push( const lux::Unit & uni)
{
	if ( empty( uni.pos ) )
	{
		spaceOccuppied.insert( {uni.id, uni.pos} );
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
