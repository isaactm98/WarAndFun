#ifndef	WAR_ENGINE_H
#define WAR_ENGINE_H

#include "deck.h"
#include "sidePile.h"
#include <string>

enum PlayerChoices
{
	NOTHING,
	PUT_CARD_IN_SIDE_PILE,
	PLAY_CARD_IN_HAND,
	PEEK_AT_NEXT_CARD_IN_DECK,
	DRAW_FROM_SIDE_PILE_PLAY_BOTH,
	CHECK_YOUR_NUM_CARDS,
	CHECK_OPP_NUM_CARDS,
	LENGTH_OF_CHOICES
};

// Holds a player's deck and side pile.
// Could be a class, but we aren't trying
// to abstract information away from the engine.
struct Player
{
	Deck m_deck;
	SidePile m_sidePile;
	int m_currentCard;
	int m_sideCard;
	// Used to not draw new cards if current hand has not been used.
	// Currently, the computer does not make use of this.
	bool m_validHandPlayed;
};

class WarEngine
{
private:
	// Player/Computer data
	Player m_player;
	Player m_computer;
	PlayerChoices m_currentChoice;

	// Game Logic	
	bool canGameEnd(void);
	void beginHand(void);
	void shuffleCardsIntoDecks(void);
	void getUserInput(void);
	void processDecision(void);
	void processCardsPlayed(void);
	// This function takes in the int value that makes up a card and 
	// Returns its value as a card
	std::string cardType(int card);

public:
	WarEngine(void);
	~WarEngine(void) = default;

	// Starts and manages the game
	void start(void);
};
#endif WAR_ENGINE_H
