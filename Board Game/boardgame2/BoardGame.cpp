//Yinghao Guo 2/9/17
//Assignment 2 board game
//two players play the game untill they reach the home, which in terms they win the game. the only inputs are players
//names and answering yes or no to questions. 

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

int random (int[]);
int play(string[], int&);
int obstacle(int);
int taketurns(int[], int&, int&);
void switchpos(int[], int&, int&);
void showpos(string[], int[], int&);
void rules ();   

// all i's are used for count only.

int main()
{
	int winner, n, playercount = 0; 
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
	
	cout <<endl;
	
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
	cout << "6. If the player lands on a space with a number, the player moves back that number of spaces." << endl << endl;
	
	return;
}

int play(string players[], int& n) //this functions plays the game.
{
	int playerpos[6]= {0,0,0,0,0,0};
	int winner = -1, store = 0, whosturn = 0; 
	string tempstr;
	char answer;
	
	for(int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (players[i].length() < players[j].length() )
			{
				tempstr = players[i];
				players[i] = players[j];
				players[j] = tempstr;
			}
	
	cout <<"The current players are:" <<endl;
	for(int i = 0; i < n; i++)
		cout << "Player " << i+1 << " is: " << players[i] <<endl;
	
	cout <<endl;
	while(winner < 0)
	{
		for (int i = 0; i < n; i++)
		{
			cout << "It's " <<players[i]<< " / Player " << i+1 <<"'s turn"<<endl; 
			playerpos[i] = taketurns(playerpos, n, whosturn);
			
			if(whosturn == 6)
				whosturn = 0;
				
			whosturn ++;
			
			cout<<"Do You want to see the poistion of all the players? Y(for yes N for no): ";
			cin >> answer;
			
			if(answer == 'y')
				showpos(players, playerpos, n);
			else 
				cout<<endl;
		}
		
		for (int i = 0; i < n; i++)
		{
			if(playerpos[i] == 21)
			{
				winner = 1;
				store = i;
			}
		}
	}
	
	return store; 
	
}

int taketurns(int playerpos[], int& n, int& whosturn)
{
	int cards[10] = {1,1,2,2,3,3,4,4,5,6}; //1 -4 are numbers of tiles that the user can move. 5 - Lose a turn, 6 - switch places with another player. 
	int choice = 0;
	
	choice = random(cards);
	
	if (whosturn == 6)
		whosturn == 0;
	
	if (cards[choice] == 6)
		switchpos(playerpos, n, whosturn);
		else if (cards[choice] == 5)
			{
				whosturn = whosturn + 1;
				return playerpos[whosturn];
			}
				else
					playerpos[whosturn] = playerpos[whosturn] + cards[choice];
	
	
	return playerpos[whosturn];				
}

void switchpos(int playerpos[] , int& n, int& whosturn)
{
	int furtestsofar = playerpos[0], arraypos = 0, temp;
	
	for(int i = 1; i < n; i++)
	{
		if (furtestsofar < playerpos[i])
		{
			furtestsofar = playerpos[i];
			arraypos = i;
			cout<< furtestsofar <<endl;
		}
	}
	
	temp = playerpos[whosturn];
	playerpos[whosturn] = playerpos[arraypos];
	playerpos[arraypos] = temp;
	
	return;
}

int random(int cards[])//picks cards at random and return it to the play function
{
	int pick;
	
	pick = rand()% 10;
	
	if(cards[pick] == 5)
		cout << "You Pick the card and it says Lose A Turn!" <<endl;
		else if (cards[pick] == 6)
			cout << "You Pick the card and it Switch Postions with the other player!" <<endl;
				else
					cout << "You are moving " << cards[pick] <<" spaces" <<endl;
					
	return pick;
}

void showpos(string players[], int playerpos[], int& n)
{
	for(int i = 0; i < n; i++)
		cout << players[i] <<" is in postion " << playerpos[i] <<endl;
	cout <<endl;
	
	return;
}



 
		

