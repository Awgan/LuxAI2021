#include "map_terminal.hpp"

void Map_Terminal::draw( const lux::GameMap & map ) const
{
	static int p = 0;
	if(p == 0)
	{
		++p;
		std::ofstream Mapka("mapka.txt");
		Mapka << "p=" << p << '\n';
		Mapka << "width=" << map.width << '\n';
		Mapka << "height=" << map.height << "\n\n";
		Mapka << '@';
		
		for( int j = 0; j < map.width; ++j )
			Mapka << j % 10;
		
		Mapka << '\n';
		
		for( int i = 0; i < map.height; ++i )
		{
			Mapka << i % 10;
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
					Mapka << '*';
				}
			}
			Mapka << '\n';
		}
		
		Mapka.close();
	}
}


void Map_Terminal::draw( const std::vector<lib::mapTrees> & vmt ) const
{
	static int no = 0;
	std::string fileName = "mapkaDrzew" + std::to_string(no) + ".txt";
	
	std::ofstream Mapka(fileName);
	
	for( auto it : vmt )
	{
		lux::Position pos = it.tile->pos;
		Mapka << "(" << pos.x << ";" << pos.y << ")" << '\t';
		Mapka << "v:" << it.value << '\t';
		Mapka << "d:" << it.dist << '\t';
		Mapka << "a:" << it.amount << '\n';
		
	}
	Mapka.close();
	++no;
}


