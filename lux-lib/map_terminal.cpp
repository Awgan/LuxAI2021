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
	std::string fileName = "drzewMapka" + std::to_string(no) + ".txt";
	
	std::ofstream Mapka(fileName, std::ofstream::app);
	if( !Mapka.is_open() )
		Mapka.open(fileName, std::ofstream::app);
	
	Mapka << "vector size: " << std::to_string(vmt.size()) << '\n';
	
	for( auto it : vmt )
	{
		lux::Position pos = it.tile->pos;
		Mapka << "(" << std::to_string(pos.x) << ";" << std::to_string(pos.y) << ")" << '\t';
		Mapka << "v:" << std::to_string(it.value) << '\t';
		Mapka << "d:" << std::to_string(it.dist) << '\t';
		Mapka << "a:" << std::to_string(it.amount) << '\n';
		
	}
	Mapka.close();
	/**/
	++no;
}



