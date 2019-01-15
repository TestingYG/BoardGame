#include "game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <new>
using namespace std;

game :: game()
{
	
	int obstaclescount = 0, gocount = 0, goagainallowed = 2 , biggest = 0, biggestallowed = 3; 
	int pick, x =0;
	
    cout <<"How many players will be playing (at most 6)? ";
    cin >> nump;
    cout << endl;

    cout <<"How many spaces you want on the board? ";
    cin >> numbs;
    cout << endl;
    
    cout <<"How many obstacles do you want on the board? ";
    cin >> numobs;
    cout << endl;
    
    cout <<"Whats the biggest obstacle you want? ";
    cin >> bigobs;
    cout << endl;
    
    cout << "Enter All the Player's. Press Enter After Each Name " <<endl;
	player players[nump];
	
	int boardspace[numbs] = {0};
	
	while(x <= 25)	
	{
		for (int i = 1; i < numbs; i++)
		{
			pick = rand() % 30;
			
			if ( boardspace[i] == 0 && pick == 6 && obstaclescount < numobs )//obstacles
			{
				boardspace[i] = 1;
				obstaclescount ++;
			}
				else if (boardspace[i] == 0 && gocount < goagainallowed   && pick == 15 )//go again
				{
					boardspace[i] = 2;
					gocount ++;
				}
					else if ( boardspace[i] == 1 && biggest < biggestallowed && pick == 25)// biggest obstacle
					{
						boardspace[i] = 3;
						biggest ++;
					}
		}
		
		x ++;
	}

	cout <<endl;
	cout << "The Following is your game board." <<endl<<endl;
	cout <<	"Number Zero represent regular board space." <<endl;
	cout << "Number One represent and obstacle space."<<endl;
	cout << "Number two represent the 'Go Again' spaces."<<endl;
	cout << "Number Three represent the biggest obsticle."<<endl<<endl;
	
	for (int i = 0; i < numbs; i ++ )// prints the board.
		cout << boardspace[i] << " ";
		
	cout <<endl<<endl;
	
	play(boardspace, players, numbs, numobs, nump);
    
}

void game :: play(int boardspace[], player players[], int numbs, int numobs, int nump)
{
	int store = 0, whosturn = 0, winner = -1;
    char answer;
    
	nameswap(players);
	
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
            
            if(players[i].getlocation() == numbs)// checkes who wins
            {
                winner = 1;
                store = i;
                break;
            }
            
         	checkboard(players, boardspace, whosturn, bigobs, nump, numbs);
        	samepos(players, whosturn, nump);
            
            whosturn ++;
            
        }
        
    }
    
    cout << "THE WINNIER IS " << players[store].getname();
    
    return; 
}


void game :: nameswap(player players[])
{
	for(int i = 0; i < nump; i++)// determines whos going first. 
		for (int j = 0; j < nump; j++)
			if ( players[i].getname().length() < players[j].getname().length() )
 				players[i].playerswap(players[j]);
	
	cout <<"The current players are:" <<endl;// tells whos turn it is
    for(int i = 0; i < nump; i++)
        cout << "Player " << i+1 << " is: " << players[i].getname() <<endl;
        
    cout <<endl; 
 				
	return;
}

void game :: taketurns(player players[], int nump, int whosturn, int numbs)
{
	int choice, subtraction;
	cards random;
	
	choice = random.getcards();
	
	if (choice == 6)//makes one turn for the player
    {
        cout << "You Pick the card and it Switch Postions with the furthest player!" <<endl;
        switchpos(players, nump, whosturn);
    }
    else if (choice == 5)
        cout << "You Pick the card and it says Lose A Turn!" <<endl;
    else
    {
        cout << "You are moving " << choice <<" spaces" <<endl;
        players[whosturn].playerforward(choice);
    }
    
    players[whosturn].playerbackward(subtraction, numbs);
        
    return;
}

void game :: checkboard(player players[], int boardspace[], int whosturn, int bigobs, int nump, int numbs)
{
	int pick, location;
	
	location = players[whosturn].getlocation();
	
	if (boardspace[location] == 1)// checks to see if you are on an obstacle
	{
		pick = rand() % 4;
		
		cout << "You hit a cone. You are Moving Back " << pick << " spaces!" <<endl;
		players[whosturn].obstacle(pick);
	}
	else if (boardspace[location] == 2)// checks if you are on go again
	{
		cout << "You get to go again !!!!!"<<endl;
			taketurns(players, nump, whosturn, numbs);
	}
		else if (boardspace[location] == 3) //checks if you are on the biggest obsticle position
		{
			cout << " You Just hit the biggest Obsticle in the game!" <<endl;
			players[whosturn].obstacle(bigobs);;
			
		}
	return;
}

void game :: switchpos(player players[] , int nump, int whosturn)//swithces poistion with the furthest player
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

void game :: samepos(player players[], int whosturn, int nump)//moves the most recent player back to home if 2 people are in the same position.
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




