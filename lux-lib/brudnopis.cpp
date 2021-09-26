#include "lib.hpp"

struct place
{
	int x;
	int y;
	place( int x1, int y1) : x(x1), y(y1){}
	bool operator==(const place &);
	
};

void recur( place [], int, place [], int, place );

bool isRecorded(place [], int, place );

int main (int argc, char * argv[])
{
	
	place arr[]={place(3,5),place(3,6),place(3,7),place(4,5),place(5,5),place(6,5)};
	
	return 0;
}
bool place::operator==(const place &  p)
{
	if(this->x == p.x && this->y == p.y)
		return true;
	else
		return false;	
}
void recur( place [] ar, int maxAr, place [] save, int maxSave, place badan )
{
	{
		for ( int i = 0; i < 4; ++i )
		{
			place temp = badan;
			
			switch (i)
			{
				case 0:
					temp.x += 1;
					if ( isRecorded(save, maxSave, temp) )
					{
						add(temp);
						recur( ar, maxAr, save, maxSave, temp);
					}
				break;
			
				case 1:
					temp.x -= 1;
					if ( isRecorded(save, temp) )
					{
						add(temp);
						recur( ar, save, );
					}
				break;
				
				case 2:
					temp.y += 1;
					if ( isRecorded(save, temp) )
					{
						add(temp);
						recur( ar, save, );
					}
				break;
				
				case 3:
					temp.y -= 1;
					if ( isRecorded(save, temp) )
					{
						add(temp);
						recur( ar, save, );
					}
				break;
				
			}
		}
	}
}
bool isRecorded( place [] save, int maxSave, place badan )
{
	for ( int j = 0; j < maxSave; ++j )
	{
		if ( save[j] == badan )
			return true;
	}
	return false;
}





