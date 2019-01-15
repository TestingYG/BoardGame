#include "player.h"
#include <iostream>
#include <string>
using namespace std;

player :: player()
{	
	string n;

    cin >> n;
	name = n;
	
    location = 0;
}

string player :: getname()
{
    return name;
}

void player :: playerswap(player &player)
{
	string temp;
	
	temp = name;
	name = player.name;
	player.name = temp;
	
	return;
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
	
	if(location > numbs)// checks if player is over poistion 21
	{
		subtraction = location - numbs;
		location = numbs - subtraction;
	}
	
	if(location < 0)
		locationzero();
	
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
    
    if(location < 0)
    	locationzero();
    
    return;
}

void player :: locationzero()
{
    location = 0;
    
    return;
}





