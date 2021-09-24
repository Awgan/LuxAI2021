
#include "lib.hpp"

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
	
	const lux::CityTile * closestcitytile;
	
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

void TileOccupy::push( const lux::Unit & uni)
{
	spaceOccupy.insert( {uni.id, uni.pos} );
}

bool TileOccupy::empty( lux::Position & pos )
{
	for ( auto it = spaceOccupy.begin(); it != spaceOccupy.end(); ++it )
	{
		if (pos == it->second)
			return false;
	}
	
	return true;
	
}

const lux::Cell * lib::bestTreeMining( const lux::GameMap & gameMap, const std::vector<lux::Cell *> & trees, const lux::Unit & unit)
{
	const lux::Cell * closestTree;
	float closestDist = 9999999;
	
	for (auto it = trees.begin(); it != trees.end(); it++)
	{
		auto cell = *it;
		float dist = cell->pos.distanceTo(unit.pos);
		if (dist < closestDist)
		{
			closestDist = dist;
			closestTree = cell;
		}
	}
	
	std::vector<lib::mapTrees> treeMap;
	
	lib::mapTrees tree;
		tree.tile = closestTree;
		tree.dist = closestDist;
		tree.value = 1;
		tree.amount = 1;
	
	treeMap.push_back( tree );
	
	lib::exploreForest( gameMap, treeMap, tree, unit );
	
	int higherValue = -1;
	for ( unsigned int k = 0; k < treeMap.size(); ++k )
	{
		if ( treeMap[k].value > higherValue )
		{
			higherValue = treeMap[k].value;
			closestTree = treeMap[k].tile;
		}
	}

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
	
	for ( int i = 0; i < 4; ++i )
	{
		lux::Position tPos = mt.tile->pos;
		const lux::Cell * tCell;
		switch (i)
		{
			case 0:
			
				tPos.y -= 1;
				
				tCell = gm.getCellByPos( tPos );
				
				if ( tCell->resource.type == lux::ResourceType::wood && isRecorded( vmt, tCell ) == false )
				{
					lib::mapTrees tree;
						tree.tile = tCell;
						tree.dist = tCell->pos.distanceTo(un.pos);
						tree.value = 1;
						tree.amount += 1;
						
					vmt.push_back(tree);
					
					mt.value += 1;
					
					
					lib::exploreForest( gm, vmt, *(vmt.end()-1), un );
				}
			
			break;
			
			case 1:
			
				tPos.y += 1;
				
				tCell = gm.getCellByPos( tPos );
				
				if ( tCell->resource.type == lux::ResourceType::wood && isRecorded( vmt, tCell ) == false )
				{
					lib::mapTrees tree;
						tree.tile = tCell;
						tree.dist = tCell->pos.distanceTo(un.pos);
						tree.value = 1;
						tree.amount += 1;
						
					vmt.push_back(tree);
					
					mt.value += 1;
					
					exploreForest( gm, vmt, *(vmt.end() - 1), un );
				}
				
			break;
			
			case 2:
			
				tPos.x -= 1;
				
				tCell = gm.getCellByPos( tPos );
				
				if ( tCell->resource.type == lux::ResourceType::wood && isRecorded( vmt, tCell ) == false )
				{
					lib::mapTrees tree;
						tree.tile = tCell;
						tree.dist = tCell->pos.distanceTo(un.pos);
						tree.value = 1;
						tree.amount += 1;
						
					vmt.push_back(tree);
					
					mt.value += 1;
					
					exploreForest( gm, vmt, *(vmt.end() - 1), un );
				}
				
			break;
			
			case 3:
			
				tPos.x += 1;
				
				tCell = gm.getCellByPos( tPos );
				
				if ( tCell->resource.type == lux::ResourceType::wood && isRecorded( vmt, tCell ) == false )
				{
					lib::mapTrees tree;
						tree.tile = tCell;
						tree.dist = tCell->pos.distanceTo(un.pos);
						tree.value = 1;
						tree.amount += 1;
						
					vmt.push_back(tree);
					
					mt.value += 1;
					
					exploreForest( gm, vmt, *(vmt.end() - 1), un );
				}
				
			break;
			
			default:
			break;
			
		}
	}
}

