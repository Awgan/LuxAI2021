
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
/*
 *Chek if Unit survive the night
 */
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

/*
 *Check if City survive the night
 */
bool lib::nightSurvive( const int & turn, lux::City & cit)
{
	float citFuel = cit.fuel;
	float needFuel = 23 * (10 - turn % 31);
	if ( needFuel < citFuel )
		return true;
	else
		return false;
}

/*
 * Check if Tree can be meining
 */

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

/*
 * Find empty CityTile
 */

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


int lib::mapTrees::amount = 0;

/*
 * Find best Tree for mining
 */

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

	std::vector<lib::mapTrees> treeMap(20);

	lib::mapTrees tree;
		tree.tile = closestTree;
		tree.dist = closestDist;
		tree.value = 1;
		tree.amount += 1;

	treeMap.push_back( tree );



	lib::exploreForest( gameMap, treeMap, *(treeMap.end()-1), unit );



	int higherValue = -1;
	int shorterDist = 999;
	lux::CityTile * isInCity = gameMap.getCellByPos(unit.pos)->citytile;
	bool hasResource = gameMap.getCellByPos(unit.pos)->hasResource();

	for ( unsigned int k = 0; k < treeMap.size(); ++k )
	{
		if ( hasResource && treeMap[k].dist == 0 )
		{
			//Unit is at Tree Tile
			higherValue = treeMap[k].value;
			closestTree = treeMap[k].tile;
			break;
		}
		else if ( isInCity != nullptr && treeMap[k].dist == 1 )
		{
			//Unit is at City Tile
			if ( treeMap[k].value > higherValue  )
			{
				higherValue = treeMap[k].value;
				closestTree = treeMap[k].tile;
				shorterDist = treeMap[k].dist;
			}
		}
		else
		{
			if ( treeMap[k].dist < shorterDist )
			{
				shorterDist = treeMap[k].dist;
				higherValue = treeMap[k].value;
				closestTree = treeMap[k].tile;
			}

			//TODO: Need to build new city when dist is much more than 1 !!
			//return nullptr;
		}
	}



	lux::Annotate::sidetext( "Best Tree: " + std::to_string(closestTree->pos.x) + "," + std::to_string(closestTree->pos.x) );

	return closestTree;
}

/*
 * Check if Cell is recorded in vector
 */

bool lib::isRecorded( std::vector<lib::mapTrees> & vmt, const lux::Cell * cl )
	{
		for ( unsigned int j = 0; j < vmt.size(); ++j )
		{
			if ( vmt[j].tile == cl )
				return true;
		}

		return false;
	}

/*
 * Go through each TreeTill and count possible trees for mining for each TreeTile
 */

void lib::exploreForest( const lux::GameMap & gm, std::vector<lib::mapTrees> & vmt, lib::mapTrees & mt, const lux::Unit & un )
{
	lux::Position tPos = mt.tile->pos;

	for ( int i = 0; i < 4; ++i )
	{
		tPos = mt.tile->pos;

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

						//lib::exploreForest( gm, vmt, (vmt.back()), un );

						lib::exploreForest( gm, vmt, *(vmt.end()-1), un );
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

						lib::exploreForest( gm, vmt, *(vmt.end()-1), un );
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

						lib::exploreForest( gm, vmt, *(vmt.end()-1), un );
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

						lib::exploreForest( gm, vmt, *(vmt.end()-1), un );
					}
				}
			}
			break;

			default:
			break;
		}
	}
	return;
}

/*
* Do research points
* player - player object
*/
void lib::research( const lux::Player & player, std::vector<std::string> & act )
{
	lux::Annotate comm;
	lux::Annotate::sidetext("#Function Research: ENTERED");
	// Iterator for  std::map<string, City> cities
	for ( auto cit : player.cities )
	{
		comm.sidetext("#Function Research: FIRST FOR");
		// Iterator for std::vector<CityTile> citytiles
		for ( auto citT : cit.second.citytiles )
		{
			comm.sidetext("#Function Research: SECOND FOR");
			//Check if it is possible to do research points
			if ( citT.canAct() && player.researchPoints < 200 /*(int)lux::GAME_CONSTANTS["PARAMETERS"]["RESEARCH_REQUIREMENTS"]["URANIUM"]*/ )
			{
				act.push_back( citT.research() );
				lux::Annotate::sidetext("#Function Research: RESEARCHED DONE");
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
void lib::createUnit( lux::Player & player, std::vector<std::string> & act, const char ch, int limit )
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
					act.push_back( iv[i].buildWorker() );
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
					act.push_back( iv[i].buildCart() );
					++created;
				}
			}
		}
	}
}

void lib::buildCity( lux::GameMap & map, lux::Player & player, std::vector<std::string> & act, lux::Unit & unit)
{
	int citiesNu = player.cityTileCount;
	int unitNu = player.units.size();

	if ( unitNu >= citiesNu )
		return;

	if ( unit.canBuild( map ) )
	{
		act.push_back( unit.buildCity() );
	}
}

void lib::move( lux::Unit & uni, lux::DIRECTIONS & dir, std::vector<std::string> & act, lib::TileOccuppied & til )
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
			//stay
		}
		break;
		default:
		break;
	}

	if ( til.empty( target ) )
	{
		//go
		til.push( uni );
		act.push_back( uni.move(dir) );
	}
	else
	{
		//wait
		til.push( uni );
		act.push_back( uni.move( lux::DIRECTIONS::CENTER ) );
	}
}

lux::Cell * lib::buildCitySurroundForest( lux::Player & pla, std::vector<lib::mapTrees *> & vMapTrees, lux::Unit & uni )
{
	//czy moze budować

	//jeżeli nie może budować, to idzie do nowego miejsca
	//jeżeli może to też idzie, wazne żeby zszedł z miasta

	//znajdź następne miejsce
	lux::Position uPos = uni.pos;

	lux::DIRECTIONS forestDir = lux::DIRECTIONS::CENTER;

	//oblicz zwrot w którym rozbudowuje się las
	for ( int i = 0; i < vMapTrees.size(); ++i )
	{

	}

	//return komorkę, którą zapiszemy w zbiorze misji

}
