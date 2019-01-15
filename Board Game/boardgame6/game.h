#ifndef game_h
#define game_h

#include "player.h"
#include "player.cpp"
#include "rules.cpp"
#include "cards.cpp"

class game{
	private:
		int numbs;  //number of boardspace
		int nump;   //number of players
		int numobs; // number of obstacles
		int bigobs; //biggest obstacle
	public:
		game();
		void play(int [], player[], int, int,int);
		void nameswap(player[]);
		void taketurns(player[], int, int, int);
		void checkboard(player[], int[], int, int, int, int);
		void switchpos(player[], int, int);
		void samepos(player[], int, int);
};


#endif
