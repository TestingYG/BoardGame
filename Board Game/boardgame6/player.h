#ifndef Player_h
#define Player_h

#include <string>
using namespace std;

class player{
	private:
		string name;
		int location;
	public:
		player();
		string getname();
		int getlocation();
        void playerswap(player&);
        void playerforward(int);
        void playerbackward(int, int);
        void locationswap(player&);
        void obstacle(int);
        void locationzero();
};

#endif
