

#include "mission_register.hpp"

MissionRegister::MissionRegister( std::string & uID, lux::Position & tar, char miss) : unitID(20), target(20), mission(20)
{
	unitID.push_back( uID );
	target.push_back( tar );
	mission.push_back( miss );
}

bool MissionRegister::pushBack( std::string & uID, lux::Position & tar, char miss )
{
	for ( int g = 0; g < unitID.size(); ++g )
	{
		if ( uID == unitID[g] )
		{
			return false;
		}
	}

	unitID.push_back( uID );
	target.push_back( tar );
	mission.push_back( miss );

	return true;
}

bool MissionRegister::isRegistered( std::string & uID)
{
	for ( uint g = 0; g < unitID.size(); ++g )
	{
		if ( uID == unitID[g] )
		{
			return true;
		}
	}
	return false;
}

char MissionRegister::getMission( std::string & uID )
{
	for ( uint g = 0; g < unitID.size(); ++g )
	{
		if ( uID == unitID[g] )
		{
			return mission[g];
		}
	}
	return '!';
}

lux::Position MissionRegister::getTarget( std::string & uID )
{
	for ( uint g = 0; g < unitID.size(); ++g )
	{
		if ( uID == unitID[g] )
		{
			return target[g];
		}
	}
	return lux::Position(-1, -1);
}

MissionRegister MissionRegister::operator[](int index)
{
	int size = unitID.size();
	if ( index > size && index <= size )
	{
		return MissionRegister( unitID[index], target[index], mission[index] );
	}
	return MissionRegister();
}
