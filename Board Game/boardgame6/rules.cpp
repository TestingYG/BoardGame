#include "rules.h"
#include <iostream>
using namespace std;

rules :: rules()
{
	cout << "Object: Reach the last space on the board, which is labeled Home." << endl;
	cout << "Players: 2 - 6 players" <<endl<<endl;
	cout << "Rules:" << endl; 
	cout << "1. PLayer with the shortes first name goes first." << endl;
	cout << "2. Players take turns in order until one player wins." << endl;
	cout << "3. A turn consists of picking a card. If the card has a number, the player moves that number of spaces." << endl; 
	cout << "4. If the card says 'lose turn,' the player does nothing, and the game continues with the next player." << endl;
	cout << "5. If the card says 'switch places,' the player must switch places with another player." << endl;
	cout << "6. If the player lands on an obstacle, the player moves back 0-4 spaces." << endl;
	cout << "7. If you land on a spot where another player is, the one that just landed moves back to home." << endl;
	cout << "8. If your poistion is over 21, move back how many spaces you are over 21 by." << endl;
	cout << "9. When you land on Go again, you get to go again. "<<endl;
	cout << "10. If you land on and obstcle and you move back spaces and land on Go Again, You cannot go again." <<endl<<endl;
}

