
#include "lib.hpp"
#include "map_terminal.hpp"

using namespace lib;


bool lib::isCityNearResources( lux::CityTile & CiTi, std::vector<lux::Cell *> & vect)
{
	for ( uint i = 0; i < vect.size(); ++i )
	{
		if ( CiTi.pos.isAdjacent( vect[ i ]->pos ) )
			return true;
	}
	return false;
}

const lux::CityTile * lib::whereNearestCityTile( const lux::Unit & un, const std::map<std::string, lux::City> & cit )
{
	lux::Position unpos = un.pos;

	auto citi_iter = cit.begin();
	auto &citi = citi_iter->second;

	float closestdist = 999999;

	const lux::CityTile * closestcitytile = nullptr;

	for ( auto &citytile : citi.citytiles )
	{
		float dist = citytile.pos.distanceTo(unpos);

		if ( dist < closestdist )
		{
			closestdist = dist;
			closestcitytile = &citytile;
		}
	}

	return closestcitytile;

}

// Does unit survive the night
bool lib::nightSurvive( const int & turn, lux::Unit & uni )
{
	if ( uni.isWorker() )
	{
		int needFuel = 4 * ( 10 - turn % 31 );
		int cargo = 100 - uni.getCargoSpaceLeft();
		if ( needFuel < cargo )
			return true;
		else
			return false;
	}
	else if( uni.isCart() )
	{
		int needFuel = 10 * ( 10 - turn % 31 );
		int cargo = 2000 - uni.getCargoSpaceLeft();
		if ( needFuel < cargo )
			return true;
		else
			return false;
	}
	return false;
}

bool lib::nightSurvive( const int & turn, lux::City & cit)
{
	float citFuel = cit.fuel;
	float needFuel = 23 * (10 - turn % 31);
	if ( needFuel < citFuel )
		return true;
	else
		return false;
}

bool lib::checkTreeResource( lux::Cell * cell, int limit )
{
	if ( cell->resource.type == lux::ResourceType::wood )
	{
		int cellResource = cell->resource.amount;

		if ( cellResource > limit )
			return true;
	}
	return false;
}

lux::Position lib::emptyCityTile( lux::City & cit, lux::Position & pos )
{
	for ( auto itm = cit.citytiles.begin(); itm != cit.citytiles.end(); ++itm )
	{
		lux::Position cityPos = itm->pos;

		if ( cityPos != pos )
		{
		return cityPos;
		}
	}
	return lux::Position();
}

/*
 * Class TileOccuppied
 *
 * */

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

	for ( auto it = spaceOccuppiedNext.begin(); it != spaceOccuppiedNext.end(); ++it )
	{
		if ( it->second == pos )
			return false;
	}

	return true;

}

void TileOccuppied::update()
{
	spaceOccuppiedNext = spaceOccuppied;
}

/*
 * Class TileOccuppied END
 * */


int lib::mapTrees::amount = 0;

const lux::Cell * lib::bestTreeMining( const lux::GameMap & gameMap, const std::vector<lux::Cell *> & trees, const lux::Unit & unit)
{
	const lux::Cell * closestTree = nullptr;
	float closestDist = 9999999;

	for (auto it = trees.begin(); it != trees.end(); ++it)
	{
		auto cell = *it;
		float dist = cell->pos.distanceTo(unit.pos);
		if (dist < closestDist)
		{
			closestDist = dist;
			closestTree = cell;
		}
	}
<<<<<<< HEAD

	std::vector<lib::mapTrees> treeMap;

=======
	
	std::vector<lib::mapTrees> treeMap(2);
	
>>>>>>> SaveEachStep
	lib::mapTrees tree;
		tree.tile = closestTree;
		tree.dist = closestDist;
		tree.value = 1;
		tree.amount += 1;

	treeMap.push_back( tree );
<<<<<<< HEAD

	lib::exploreForest( gameMap, treeMap, *(treeMap.begin()), unit );

=======
	
	lib::exploreForest( gameMap, treeMap, *(treeMap.end()-1), unit );
	
>>>>>>> SaveEachStep
	int higherValue = -1;
	for ( unsigned int k = 0; k < treeMap.size(); ++k )
	{
		if ( treeMap[k].value > higherValue )
		{
			higherValue = treeMap[k].value;
			closestTree = treeMap[k].tile;
		}
	}

	Map_Terminal mapa;
	mapa.draw( treeMap );


	return closestTree;

}

bool lib::isRecorded( std::vector<lib::mapTrees> & vmt, const lux::Cell * cl )
	{
		for ( unsigned int j = 0; j < vmt.size(); ++j )
		{
			if ( vmt[j].tile == cl )
				return true;
		}

		return false;
	}

void lib::exploreForest( const lux::GameMap & gm, std::vector<lib::mapTrees> & vmt, lib::mapTrees & mt, const lux::Unit & un )
{
	static int mmm = 0;
	
	
	static std::ofstream Mapka("xxxco.txt", std::ofstream::app);
	
	if ( !Mapka.is_open() )
		Mapka.open("xxxco.txt", std::ofstream::app);
	
	/*
	for( int i = 0; i < mmm; ++i )
	{
		Mapka << '\t';
	}*/
	
	++mmm;
	
	Mapka << "Rekurencja: " << mmm << '\n';
	
	lux::Position tPos = mt.tile->pos;
	
	for ( int i = 0; i < 4; ++i )
	{

		if ( !Mapka.is_open() )
		Mapka.open("xxxco.txt", std::ofstream::app);
		
		Mapka << "(R=" << std::to_string(mmm) << "C=" << std::to_string(i) << ") ";
		
		tPos = mt.tile->pos;
		Mapka << mt.tile << "=(" << tPos.x << ',' << tPos.y << ") ";

		const lux::Cell * tCell = nullptr;
		switch (i)
		{
			case 0:
			{
				tPos.y -= 1;

				tCell = gm.getCellByPos( tPos );

				if ( tCell->resource.type == lux::ResourceType::wood )
				{
					mt.value += 1;

					if ( isRecorded( vmt, tCell ) == false )
					{
						lib::mapTrees tree;
							tree.tile = tCell;
							tree.dist = tCell->pos.distanceTo(un.pos);
							tree.value = 1;
							tree.amount += 1;

						vmt.push_back(tree);


						lib::exploreForest( gm, vmt, (vmt.back()), un );
						Mapka << "i after case 0=" + std::to_string(i) << " ";

						Mapka << " CASE: " << i << " uruchamia następną rekurencję\n";
						lib::exploreForest( gm, vmt, *(vmt.end()-1), un );
						if ( !Mapka.is_open() )
							Mapka.open("xxxco.txt", std::ofstream::app);
						Mapka << " CASE: " << i << " koniec R=" << std::to_string( mmm );
						--mmm;
						Mapka << " (R=" << std::to_string(mmm) << "C=" << std::to_string(i) << ')' << '\n';
						Mapka.close();

					}
				}
			}
			break;

			case 1:
			{
				tPos.y += 1;

				tCell = gm.getCellByPos( tPos );

				if ( tCell->resource.type == lux::ResourceType::wood )
				{
					mt.value += 1;

					if ( isRecorded( vmt, tCell ) == false )
					{
						lib::mapTrees tree;
							tree.tile = tCell;
							tree.dist = tCell->pos.distanceTo(un.pos);
							tree.value = 1;
							tree.amount += 1;

						vmt.push_back(tree);


						lib::exploreForest( gm, vmt, (vmt.back()), un );
						Mapka << "i after case 1=" + std::to_string(i) << " ";

						Mapka << " CASE: " << i << " uruchamia następną rekurencję\n";
						lib::exploreForest( gm, vmt, *(vmt.end()-1), un );
						if ( !Mapka.is_open() )
							Mapka.open("xxxco.txt", std::ofstream::app);
						Mapka << " CASE: " << i << " koniec R=" << std::to_string( mmm );
						--mmm;
						Mapka << " (R=" << std::to_string(mmm) << "C=" << std::to_string(i) << ')' << '\n';
						Mapka.close();
p
					}
				}
			}
			break;

			case 2:
			{
				tPos.x -= 1;

				tCell = gm.getCellByPos( tPos );

				if ( tCell->resource.type == lux::ResourceType::wood )
				{
					mt.value += 1;

					if ( isRecorded( vmt, tCell ) == false )
					{
						lib::mapTrees tree;
							tree.tile = tCell;
							tree.dist = tCell->pos.distanceTo(un.pos);
							tree.value = 1;
							tree.amount += 1;

						vmt.push_back(tree);


						lib::exploreForest( gm, vmt, (vmt.back()), un );
						Mapka << "i after case 2=" + std::to_string(i) << " ";

						Mapka << " CASE: " << i << " uruchamia następną rekurencję\n";
						lib::exploreForest( gm, vmt, *(vmt.end()-1), un );
						if ( !Mapka.is_open() )
							Mapka.open("xxxco.txt", std::ofstream::app);
						Mapka << " CASE: " << i << " koniec R=" << std::to_string( mmm );
						--mmm;
						Mapka << " (R=" << std::to_string(mmm) << "C=" << std::to_string(i) << ')' << '\n';
						Mapka.close();

					}
				}
			}
			break;

			case 3:
			{
				tPos.x += 1;

				tCell = gm.getCellByPos( tPos );

				if ( tCell->resource.type == lux::ResourceType::wood )
				{
					mt.value += 1;

					if ( isRecorded( vmt, tCell ) == false )
					{
						lib::mapTrees tree;
							tree.tile = tCell;
							tree.dist = tCell->pos.distanceTo(un.pos);
							tree.value = 1;
							tree.amount += 1;

						vmt.push_back(tree);


						lib::exploreForest( gm, vmt, (vmt.back()), un );
						Mapka << "i after case 3=" + std::to_string(i) << " ";

						Mapka << " CASE: " << i << " uruchamia następną rekurencję\n";
						lib::exploreForest( gm, vmt, *(vmt.end()-1), un );
						if ( !Mapka.is_open() )
							Mapka.open("xxxco.txt", std::ofstream::app);
						Mapka << " CASE: " << i << " koniec R=" << std::to_string( mmm );
						--mmm;
						Mapka << " (R=" << std::to_string(mmm) << "C=" << std::to_string(i) << ')' << '\n';
						Mapka.close();

					}
				}
			}
			break;

			default:
			break;

		}

	}
	if ( !Mapka.is_open() )
		Mapka.open("xxxco.txt", std::ofstream::app);
	Mapka << "\nKONIEC R=" << std::to_string( mmm ) << '\n';
	Mapka.close();
	return;
}

/*
* Do research points
* player - player object
*/	
void research( const lux::Player & player )
{
	// Iterator for  std::map<string, City> cities
	for ( auto cit : player.cities )
	{
		// Iterator for std::vector<CityTile> citytiles
		for ( auto citT : cit.second.citytiles )
		{
			//Check if it is possible to do research points
			if ( citT.canAct() && player.researchPoints < (int)lux::GAME_CONSTANTS["PARAMETERS"]["RESEARCH_REQUIREMENTS"]["URANIUM"] )
			{
				citT.research();
			}
		}
	}
}

/*
 * Create unit function
 * player - 
 * ch - indicate what unit type.
 * 			'w' -> worker
 * 			'c'	-> cart 
 * limit - indicate how many units build
 */
void createUnit( lux::Player & player, const char ch, int limit )
{
	int unitNu = player.units.size();
	int cityNu = player.cityTileCount;

	//Exit if there is more Units than citytiles
	if ( unitNu >= cityNu )
		return;

	//How many units can be build
	int newUnits = cityNu - unitNu;

	//Choose what to build: Workers or Carts
	if ( ch == 'w' )
	{
		//Create Unit
		int created = 0;

		for ( auto it = player.cities.begin(); it != player.cities.end() || created < newUnits || created < limit; ++it )
		{
			auto iv = it->second.citytiles;
			for ( uint i = 0 ; i < iv.size() && created < newUnits; ++i)
			{
				if ( iv[i].canAct() )
				{
					iv[i].buildWorker();
					++created;
				}
			}
		}
	}
	else if ( ch == 'c' )
	{
		//create cart
		int created = 0;

		for ( auto it = player.cities.begin(); it != player.cities.end() || created < newUnits || created < limit; ++it )
		{
			auto iv = it->second.citytiles;
			for ( uint i = 0 ; i < iv.size() && created < newUnits; ++i)
			{
				if ( iv[i].canAct() )
				{
					iv[i].buildCart();
					++created;
				}
			}
		}
	}
}

