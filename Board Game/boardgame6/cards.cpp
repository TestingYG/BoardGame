#include "cards.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std; 

int cards::getcards()
{
	int pick, randompic, temp,choice;
	
	srand(time(0)); //this code shuffles the array
    for(int i = 0; i < 10; i++)
    {
        randompic = rand()% 10;
        temp = deck[i];
        deck[i] = deck[randompic];
        deck[randompic] = temp;
    }
    
    choice = random();
    pick = deck[choice];
    
    return pick;
}

int cards::random()
{
	int randompic;
    
    srand(time(0));
    randompic = rand()% 10; 
					
	return randompic;
}
