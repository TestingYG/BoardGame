//Yinghao Guo 3/14/17
//Assignment 2 board game
//two players or more players  play the game untill they reach the home, which in terms they win the game.

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <new>
#include "player.cpp"
using namespace std;

int random ();
int play(player[], int*, int, int, int);
void checkboard(player [],int*, int, int, int, int);
void samepos(player[] ,int, int);
void taketurns(player [], int, int, int);
void switchpos(player[], int , int);
void rules (); 
void zeroout(int *, int &);
void setboard(int*, const int, const int);

int main()
{
    int nump, numbs, numobstacles, biggestobstacles, winner, *boardspace;
    string n;
    
    rules();
    
    cout <<"How many players will be playing (at most 6)? ";
    cin >> nump;
    cout << endl;
    
    cout <<"How many spaces you want on the board? ";
    cin >> numbs;
    cout << endl;
    
    cout <<"How many obstacles do you want on the board? ";
    cin >> numobstacles;
    cout << endl;
    
    cout <<"Whats the biggest obstacle you want? ";
    cin >> biggestobstacles;
    cout << endl;
    
    for(int playercount = 0; playercount < nump ; playercount++)
    {
        cout << "Enter Player " << playercount + 1 <<"'s Name: ";
        cin >> n;
        players[playercount].setname(n);
    }
    
    boardspace = new int[numbs];
    
    cout << endl;
    
    setboard(boardspace, numobstacles, numbs); // sets the gameboard with obstacles, go again.
    
    winner = play(players, boardspace, biggestobstacles, nump, numbs);
    cout << "THE WINNIER IS " << players[winner].getname();
    
    delete[] boardspace;
    
    return 0;
}

int play(player players[], int *boardspace, int biggestobstacles, int nump, int numbs) //this functions plays the game.
{
    int winner = -1, store = 0, whosturn = 0;
    char answer;
    
	for(int i = 0; i < nump; i++)// determines whos going first. 
		for (int j = 0; j < nump; j++)
			if ( players[i].getname().length() < players[j].getname().length() )
 				players[i].playerswap(players, i, j);
    
    cout <<"The current players are:" <<endl;// tells whos turn it is
    for(int i = 0; i < nump; i++)
        cout << "Player " << i+1 << " is: " << players[i].getname() <<endl;
    
    cout <<endl;
    
    while(winner < 0) //main controler of the game
    {
        for (int i = 0; i < nump; i++)
        {
            if(whosturn == nump)//turn counter
                whosturn = 0;
            
            cout << "Do You Want to see the Poistion of the players? ";
            cin >> answer;
            cout << endl;
            
            if (answer = 'y')
                for (int i = 0; i < nump; i++)
                {
                    cout << players[i].getname() << " is in poistion " << players[i].getlocation() <<endl;
                }	
            
			cout <<endl;    
            
            cout << "It's " << players[i].getname() << " / Player " << i+1 <<"'s turn"<<endl;
            taketurns(players, nump, whosturn, numbs);
            
            if( players[i].getlocation() == numbs)// checkes who wins
            {
                winner = 10;
                store = i;
                break;
            }
            
           	checkboard(players, boardspace,whosturn,biggestobstacles, nump, numbs);
        	samepos(players, whosturn, nump);
            
            whosturn ++;
            
        }
    }
    return store;
}

    
void taketurns(player players[] , int nump, int whosturn, int numbs)//this function simulates one turn for a player
{
    int cards[10] = {1,1,2,2,3,3,4,4,5,6};  //1 -4 are numbers of tiles that the user can move. 5 - Lose a turn, 6 - switch places with another player.
    int choice, randompic,temp,subtraction;
    
    choice = random();
        
    srand(time(0)); //this code shuffles the array
    for(int i = 0; i < 10; i++)
    {
        randompic = rand()% 10;
        temp = cards[i];
        cards[i] = cards[randompic];
        cards[randompic] = temp;
    }
    
    if (cards[choice] == 6)//makes one turn for the player
    {
        cout << "You Pick the card and it Switch Postions with the furthest player!" <<endl;
        switchpos(players, nump, whosturn);
    }
    else if (cards[choice] == 5)
        cout << "You Pick the card and it says Lose A Turn!" <<endl;
    else
    {
        cout << "You are moving " << cards[choice] <<" spaces" <<endl;
        players[whosturn].playerforward(cards[choice]);
    }
    
    if(players[whosturn].getlocation() > numbs)// checks if player is over poistion 21
        players[whosturn].playerbackward(subtraction, numbs);
        
    return;
}

void switchpos(player players[] , int nump, int whosturn)//swithces poistion with the furthest player
{
	int furtestsofar = players[0].getlocation(), arraypos = 0, temp;
	
	for(int i = 1; i < nump ; i++)
	{
		if (furtestsofar < players[i].getlocation())
		{
			furtestsofar = players[i].getlocation();
			arraypos = i;
		}
	}
	
    players[whosturn].locationswap(players[arraypos]);
	
	return;
} 

int random()//picks cards at random and return it to the play function
{
	int pick;
    
    srand(time(0));
    pick = rand()% 10; 
					
	return pick;
}

void checkboard(player players[], int* boardspace, int whosturn, int biggestobsticle, int nump, int numbs)
//function checks the poistion of the player and see if they hit obsticle or go again.
{
	int pick, location;
	
	location = players[whosturn].getlocation();
	
	if (*(boardspace + (location)) == 1)// checks to see if you are on an obstacle
	{
		pick = rand() % 4;
		cout << "You hit a cone. You are Moving Back " << pick << " spaces!" <<endl;
		players[whosturn].obstacle(pick);
	}
	else if (*(boardspace + (location)) == 2)// checks if you are on go again
	{
		cout << "You get to go again !!!!!"<<endl;
			taketurns(players, nump, whosturn, numbs);
	}
		else if (*(boardspace + (location)) == 3) //checks if you are on the biggest obsticle position
		{
			cout << " You Just hit the biggest Obsticle in the game!" <<endl;
			players[whosturn].obstacle(biggestobsticle);;
			
		}
	return;
}

void samepos(player players[], int whosturn, int nump)//moves the most recent player back to home if 2 people are in the same position.
{
	int count = 0;
	
	while (count < nump && players[whosturn].getlocation() != 0)
	{
		if (whosturn == count)//this is to skip reading the currents players turn position.
			count ++;
        else if(players[whosturn].getlocation() == players[count].getlocation())
		{
			cout <<"YOU ARE IN THE SAME POSITION AS ANOTHER PLAYER, YOU GO HOME!" <<endl<<endl;
				players[whosturn].locationzero();
			break;
		}
		else
			count ++;	
	}	

	return;
}

void rules() //displays the rules of the game
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
	
	return;
}
 
void setboard(int* boardspace, const int obstacle,const int numbs)//fucntion puts the obstacles and go again in place. 
{
	
	int obstaclescount = 0, gocount = 0, goagainallowed = 2 , biggest = 0, biggestallowed = 3; 
	int pick, x =0;
	
	while(x <= 25)	
	{
		for (int i = 1; i < numbs; i++)
		{
			pick = rand() % 30;
			
			if ( *(boardspace + i) == 0 && pick == 6 && obstaclescount < obstacle )//obstacles
			{
				*(boardspace + i) = 1;
				obstaclescount ++;
			}
				else if (*(boardspace + i) == 0 && gocount < goagainallowed   && pick == 15 )//go again
				{
					*(boardspace + i) = 2;
					gocount ++;
				}
					else if ( *(boardspace + i) == 1 && biggest < biggestallowed && pick == 25)// biggest obstacle
					{
						*(boardspace + i) = 3;
						biggest ++;
					}
		}
		
		x ++;
	}

	cout << "This is Your following game board." <<endl;
	cout <<	"Number Zero represent regular board space." <<endl;
	cout << "Number One represent and obstacle space."<<endl;
	cout << "Number two represent the 'Go Again' spaces."<<endl;
	cout << "Number Three represent the biggest obsticle."<<endl;
	
	for (int i = 0; i < numbs; i ++ )// prints the board.
		cout << *(boardspace +i) << " ";
		
	cout <<endl<<endl;
	
	return; 
}
		

