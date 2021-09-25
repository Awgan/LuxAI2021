#include "map_terminal.hpp"

void Map_Terminal::draw( const lux::GameMap & map ) const
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
					Mapka << '?';
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


void Map_Terminal::draw( const std::vector<lib::mapTrees> & vmt ) const
{
	std::ofstream Mapka("mapka_drzew.txt");
	
	for( auto it : vmt )
	{
		lux::Position pos = it.tile->pos;
		Mapka << "(" << pos.x << ";" << pos.y << ")" << '\t';
		Mapka << "v:" << it.value << '\t';
		Mapka << "a:" << it.amount << '\n';
		
	}
	Mapka.close();
}



