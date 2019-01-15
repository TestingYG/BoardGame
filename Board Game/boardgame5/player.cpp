#include "player.h"
#include <iostream>
#include <string>
using namespace std;

player :: player ()
{
    location = 0;
}

void player :: setname(string n)
{
    name = n;
    
    return;
}

string player :: getname()
{
    return name;
}

int player :: getlocation()
{
    return location;
}

void player :: playerforward (int card)
{
	location = location + card;
	
	return;
}

void player :: playerbackward(int subtraction, int numbs)
{
	subtraction = location - numbs;
	location = numbs - subtraction;
	
	return;
}

void player :: locationswap(player &player)
{
    int temp;
    
    temp = location;
    location = player.location;
    player.location = temp;

    return;
}


void player :: obstacle(int pick)
{
    location = location - pick;
    
    return;
}

void player :: locationzero()
{
    location = 0;
    
    return;
}





