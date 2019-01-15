#ifndef cards_h
#define cards_h

class cards
{
	private:
		int deck[10] = {1,1,2,2,3,3,4,4,5,6};
	public:
		int getcards();
		int random();
};

#endif
