//Yinghao Guo 2/9/17
//Assignment 2 board game
//two players play the game untill they reach the home, which in terms they win the game. the only inputs are players
//names and answering yes or no to questions. 

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

int random ();
int play(string[], int&);
int obstacle(int[], int&);
int samepos(int [],int, int&);
int taketurns(int[], int&, int&);
void switchpos(int[], int&, int&);
void showpos(string[], int[], int&);
void rules ();   

// all i's are used for count only.

int main()
{
	int winner, n, playercount = 1;
	string players[6];
	rules();
	
	cout <<"How many players will be playing (at most 6)? ";
	cin >> n; 
	
	for(int i = 0; i < n ; i++)
	{
		cout << "Enter The Player " << playercount <<"'s Name: ";
		cin >> players[i];
		playercount ++;
	}
	
	cout << endl;
	
	winner = play(players, n);
	cout << "THE WINNIER IS " << players[winner];
	
	return 0;

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
	cout << "6. If the player lands on a space with a number, the player moves back that number of spaces." << endl;
	cout << "7. If you land on a spot where another player is, the one that just landed moves back to home." << endl;
	cout << "8. If your poistion is over 21, move back how many spaces you are over 21 by." << endl<<endl;
	
	return;
}

int play(string players[], int& n) //this functions plays the game.
{
	int playerpos[6]= {0,0,0,0,0,0};
	int winner = -1, store = 0, whosturn = 0, subtraction;
	string tempstr;
	char answer;
	
	for(int i = 0; i < n; i++)// determines whos going first. 
		for (int j = 0; j < n; j++)
			if (players[i].length() < players[j].length() )
			{
				tempstr = players[i];
				players[i] = players[j];
				players[j] = tempstr;
			}
	
	cout <<"The current players are:" <<endl;// tells whos turn it is
	for(int i = 0; i < n; i++)
		cout << "Player " << i+1 << " is: " << players[i] <<endl;
	
	cout <<endl;
	
	while(winner < 0)
	{
		for (int i = 0; i < n; i++)
		{
			if(whosturn == n)//turn counter
				whosturn = 0;
				
			cout<<"Do You want to see the position of all the players? Y(for yes N for no): ";
			cin >> answer;
			
			if(answer == 'y')
				showpos(players, playerpos, n);
			else 
				cout<<endl;
			
			cout << "It's " <<players[i]<< " / Player " << i+1 <<"'s turn"<<endl; 
			playerpos[i] = taketurns(playerpos, n, whosturn);
			
			if(playerpos[i] == 21)// checkes who wins
			{
            	winner = 10;
                store = i; 
				break;  
			}
            else if(playerpos[i] > 21)// checks if player is over poistion 21
            {
                subtraction = playerpos[i] - 21;
          		playerpos[i] = 21 - subtraction;
          		playerpos[i] = obstacle(playerpos, whosturn);  
          	}
			
			playerpos[i] = obstacle(playerpos, whosturn);
			playerpos[i] = samepos(playerpos, whosturn, n);
			
			whosturn ++;
		        
            }
		}
	
	return store; 	
}

int taketurns(int playerpos[], int& n, int& whosturn)//this function simulates one turn for a player
{
	int cards[10] = {1,1,2,2,3,3,4,4,5,6}; //1 -4 are numbers of tiles that the user can move. 5 - Lose a turn, 6 - switch places with another player. 
	int choice, randompic,temp;
	
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
		switchpos(playerpos, n, whosturn);
		cout << "You Pick the card and it Switch Postions with the furthest player!" <<endl;
	}
		else if (cards[choice] == 5)
		{
			cout << "You Pick the card and it says Lose A Turn!" <<endl;
			return playerpos[whosturn]; 
		}
			else
			{
				cout << "You are moving " << cards[choice] <<" spaces" <<endl;
				playerpos[whosturn] = playerpos[whosturn] + cards[choice];
			}

	return playerpos[whosturn];				
}

void switchpos(int playerpos[] , int& n, int& whosturn)//swithces poistion with the furthest player
{
	int furtestsofar = playerpos[0], arraypos = 0, temp;
	
	for(int i = 1; i < n; i++)
	{
		if (furtestsofar < playerpos[i])
		{
			furtestsofar = playerpos[i];
			arraypos = i;
		}
	}
	
	temp = playerpos[whosturn];
	playerpos[whosturn] = playerpos[arraypos];
	playerpos[arraypos] = temp;
	
	return;
}

int random()//picks cards at random and return it to the play function
{
	int pick;
    
    srand(time(0));
    pick = rand()% 10; 
					
	return pick;
}

int obstacle(int playerpos[], int& whosturn)//function shows where the obsticals are on the board.
{
	int obstacle[21] = {0,0,2,0,0,1,0,3,0,0,0,0,0,2,0,0,0,2,0,1,0};
	int position = playerpos[whosturn] - 1;
	
	if(obstacle[position] != 0)
	{
		cout<<"You Hit A CONE!. You are moving back " << obstacle[position] << " spaces!" <<endl<<endl;
		playerpos[whosturn] = playerpos[whosturn] - obstacle[position];
	}
	
	return playerpos[whosturn];
}

void showpos(string players[], int playerpos[], int& n)//shows all the players position, if user says yes.
{
	for(int i = 0; i < n; i++)
		cout << players[i] <<" is in postion " << playerpos[i] <<endl;
	cout <<endl;
	
	return;
}

int samepos(int playerpos[], int whosturn, int& n)//moves the most recent player back to home if 2 people are in the same position.
{
	int count = 0;
	
	while (count < n && playerpos[whosturn] != 0)
	{
		if (whosturn == count)//this is to skip reading the currents players turn position.
			count ++;
		else if(playerpos[whosturn] == playerpos[count])
		{
			cout <<"YOU ARE IN THE SAME POSITION AS ANOTHER PLAYER, YOU GO HOME!" <<endl<<endl;
			playerpos[whosturn] = 0;	
			break;
		}
		else
			count ++;	
	}	

	return playerpos[whosturn];
}


 
		

