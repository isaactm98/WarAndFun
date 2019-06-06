#ifndef	DECK_H
#define DECK_H

static int const MAX_NUM_CARDS = 52; // Max number of cards a deck can hold

class Deck 
{
private: 			
	int m_backOfQueue; // Keeps track of next available open space
	int m_deckOfCards[MAX_NUM_CARDS] = { 0 }; // Array to hold 
public:
	Deck(void);
	~Deck(void) = default;

	// Mutators
	void enqueue(int card);// Adds item to deck
	int dequeue(void);// Removes item from deck
	void makeEmpty(void);// Makes the deck empty

	// Accessors
	int peek(void);// Looks at top item of deck
	int length(void);// Looks at length of deck
	bool isEmpty(void);// Checks to see if deck is empty
	bool isFull(void); // Checks to see if deck is full		
};
#endif DECK_H
