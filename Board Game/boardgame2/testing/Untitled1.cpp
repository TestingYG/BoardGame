#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

int main()
{
	int cards[10] = {1,1,2,2,3,3,4,4,5,6}; //1 -4 are numbers of tiles that the user can move. 5 - Lose a turn, 6 - switch places with another player.
	int cardlimit = 10, temp, random;
	
	srand(time(0));
    for(int i = 0; i < cardlimit; i++)
    {
        random = rand()% cardlimit;
        temp = cards[i];
        cards[i] = cards[random];
        cards[random] = temp;
	}
	
	for(int i = 0; i < cardlimit; i++)
		cout << cards[i]<<endl;
}
