#ifndef LIB_LUX_HPP
#define LIB_LUX_HPP

#include "../lux/kit.hpp"
#include "tile_occu.hpp"


namespace lib
{

	bool isCityNearResources( lux::CityTile & CiTi, std::vector<lux::Cell *> & vect);

	const lux::CityTile * whereNearestCityTile( const lux::Unit & un, const std::map<std::string, lux::City> & cit );

	bool nightSurvive( const int & turn, lux::Unit & uni);

	bool nightSurvive( const int & turn, lux::City & cit);

	bool checkTreeResource( lux::Cell * cell, int limit = 100 );

	void bestCityTileAction();

	lux::Position emptyCityTile( lux::City & cit, lux::Position & pos );

	struct mapTrees
	{
		const lux::Cell * tile;	//pointer to Cell
		int dist;				//distance to Unit
		int value;				//how many trees can be mined by Unit
		static int amount;		//how many trees is there in the forest
	};

	bool isRecorded( std::vector<lib::mapTrees> &, const lux::Cell * );

	void exploreForest( const lux::GameMap &, std::vector<lib::mapTrees> &, lib::mapTrees &, const lux::Unit & );

	/*
	//Find the best and the closest tree tile for mining
	*/
	const lux::Cell * bestTreeMining( const lux::GameMap &, const std::vector<lux::Cell *> &, const lux::Unit & );

	class BestResourceTile
	{



	};


	void research( const lux::Player & player, std::vector<std::string> & );

	void createUnit( lux::Player &, std::vector<std::string> &, const char, int );

	void buildCity( lux::GameMap &, lux::Player &, std::vector<std::string> &, lux::Unit & );

	void move( lux::Unit &, lux::DIRECTIONS &, std::vector<std::string> &, lib::TileOccuppied & );

	lux::Cell * findCellForCityForest( lux::GameMap &, std::vector<lib::mapTrees *> & );

};


#endif
