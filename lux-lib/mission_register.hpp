#ifndef MISSION_REG_HPP
#define MISSION_REG_HPP

#include <vector>

#include "../lux/kit.hpp"

class MissionRegister
	{
		public:
			std::vector<std::string> unitID;
			std::vector<lux::Position> target;
			std::vector<char> mission;

			MissionRegister() : unitID(20), target(20), mission(20)
			{}

			MissionRegister( std::string &, lux::Position &, char );

			MissionRegister(const MissionRegister &)
			{}

			~MissionRegister()
			{}

			bool pushBack( std::string &, lux::Position &, char );

			bool isRegistered( std::string & );

			char getMission( std::string & );

			lux::Position getTarget( std::string & );

			MissionRegister operator[](int);

	};

#endif
