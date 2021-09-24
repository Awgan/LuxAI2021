#include "map_terminal.hpp"

void Map_Terminal::draw( const lux::GameMap & map )
{
	std::ofstream Mapka("mapka.txt");
	
	for( int i = 0; i < map.height; ++i )
	{
		for( int j = 0; j < map.width; ++j )
		{
			const lux::Cell * cell = map.getCell( j, i );
			if( cell->hasResource() )
			{
				switch( cell->resource.type )
				{
					case 'w':
					Mapka << 'W';
					break;
					case 'c':
					Mapka << 'C';
					break;
					case 'u':
					Mapka << 'U';
					break;
					default:
					break;
				}
			}
			else if( cell->citytile != nullptr )
			{
				Mapka << 'A';
			}
			else
			{
				Mapka << '_';
			}
		}
		Mapka << '\n';
	}
	
	Mapka.close();
}