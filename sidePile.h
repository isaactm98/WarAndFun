#ifndef SIDEPILE_H
#define SIDEPILE_H


static int const MAX_CARDS = 5;

class SidePile 
{
private:	
	int m_topSpotAvailable;//keeps track of next open spot
	int m_stackOfCards[MAX_CARDS];

public:
	SidePile(void);
	~SidePile(void) = default;

	// Mutators
	void push(int card); // Puts a card on the stack
	int pop(void);			 // Removes the last card from the stack and returns it to the caller
	int peek(void);			 // Shows the top card without removing it.

	// Accessors
	int length(void);		 // Shows the number of cards in the stack
	bool isEmpty(void);		 // Checks to see if stack is empty
	bool isFull(void);		 // Checks to see if stack is full
	int getCapacity(void);   // Shows max num of cards possible in stack	
};

#endif SIDEPILE_H