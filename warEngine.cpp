#include "warEngine.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <array>
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::to_string;

bool WarEngine::canGameEnd(void)
{
	//while the player and computer both have at least 1 card
	return (!(m_player.m_deck.isEmpty()) || !(m_player.m_sidePile.isEmpty())) &&
		(!(m_computer.m_deck.isEmpty()) || !(m_computer.m_sidePile.isEmpty()));
}

void WarEngine::beginHand(void)
{
	//draws card from deck if a card is in deck. otherwise, draw card from side pile
	//checks to see if choice is equivalent to PEEK_AT_NEXT_CARD_IN_DECK, CHECK_YOUR_NUM_CARDS,
	//CHECK_OPP_NUM_CARDS because if it is a card should not be drawn
	// If hand has not been played, do not draw another card
	if (m_player.m_deck.isEmpty() && (m_currentChoice != 5 && m_currentChoice != 6 && m_currentChoice != 3) && m_player.m_validHandPlayed)
	{
		m_player.m_currentCard = m_player.m_sidePile.pop();
	}
	else if ((m_currentChoice != 5 && m_currentChoice != 6 && m_currentChoice != 3) && m_player.m_validHandPlayed)
	{
		m_player.m_currentCard = m_player.m_deck.dequeue();
	}
	if (m_computer.m_deck.isEmpty() && (m_currentChoice != 5 && m_currentChoice != 6 && m_currentChoice != 3) && m_player.m_validHandPlayed)
	{
		m_computer.m_currentCard = m_computer.m_sidePile.pop();
	}
	else if ((m_currentChoice != 5 && m_currentChoice != 6 && m_currentChoice != 3) && m_player.m_validHandPlayed)
	{
		m_computer.m_currentCard = m_computer.m_deck.dequeue();
	}
	//tell user what the card is in their hand
	cout << "The card in your hand is a " << cardType(m_player.m_currentCard) << endl;
}

void WarEngine::shuffleCardsIntoDecks(void)
{
	// Created this way so shuffle command could be used
	std::array <int, MAX_NUM_CARDS> cards;

	//goes through and fills cards with the values 1-13 4 times
	//each integer represents a card
	//4 suits*13 cards
	int j = 0;
	for (int i = 0; i < MAX_NUM_CARDS; i++)
	{
		if ((i % 4) == 0)
		{
			j++;
		}
		cards[i] = j;
	}

	// Shuffle Cards
	unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
	std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
	//split the deck and give half to the player, half to the computer
	for (int m = 0; m < MAX_NUM_CARDS; m++)
	{
		m_player.m_deck.enqueue(cards[m]);
		m++;//goes to next card
		m_computer.m_deck.enqueue(cards[m]);
	}
}

void WarEngine::getUserInput(void)
{
	int choice = 0;
	//choice and input validation
	cout << "What would you like to do?\n1.Put card in side pile and play next card in deck\n2." <<
		"Play card against computer\n3.Peek at next card in deck\n4.Draw from side pile and play both\n" <<
		"5.Look at how many cards you have\n6.Look at how many cards the computer has\n";
	cin >> choice;
	while (choice >= LENGTH_OF_CHOICES || choice == NOTHING)
	{
		cout << "What would you like to do?\n1.Put card in side pile and play next card in deck\n" <<
			"2.Play card against computer\n3.Peek at next card in deck\n4.Draw from side pile and" <<
			" play both\n5.Look at how many cards you have\n6.Look at how many cards the computer has\n";
		cin >> choice;
	}

	m_currentChoice = static_cast<PlayerChoices>(choice);
}

void WarEngine::processDecision(void)
{
	switch (m_currentChoice)
	{
	case PUT_CARD_IN_SIDE_PILE: {//error checks before, if passes sees what computer does and plays
		if (m_player.m_sidePile.isFull()) 
		{
			cout << "Cannot add card to pile. Pile is full. What would you like to do?\n";
			m_player.m_validHandPlayed = false;
		}
		else if (m_player.m_deck.isEmpty())
		{
			cout << "Cannot add card to pile. Your deck is empty. Can only add to pile if you can draw from your deck.\n";
			m_player.m_validHandPlayed = false;
		}
		else 
		{
			m_player.m_sidePile.push(m_player.m_currentCard);
			m_player.m_currentCard = m_player.m_deck.dequeue();
			//computer decides what to do based on conditions of deck, pile, and current card
			if (m_computer.m_currentCard < 5 && !(m_computer.m_sidePile.isFull()) && !(m_computer.m_deck.isEmpty())) 
			{
				m_computer.m_sidePile.push(m_computer.m_currentCard);
				m_computer.m_currentCard = m_computer.m_deck.dequeue();
				processCardsPlayed();
			}
			else if (m_computer.m_currentCard >= 5 && m_computer.m_currentCard << 11 && !(m_computer.m_sidePile.isFull())) 
			{
				m_computer.m_sideCard = m_computer.m_sidePile.pop();
				processCardsPlayed();
			}
			else
			{
				processCardsPlayed();
			}

		}
		break;
	}

	case PLAY_CARD_IN_HAND: 
	{
		//computer decides what to do based on conditions of deck, pile, and current card
		if (m_computer.m_currentCard < 5 && !(m_computer.m_sidePile.isFull()) && !(m_computer.m_deck.isEmpty())) 
		{
			m_computer.m_sidePile.push(m_computer.m_currentCard);
			m_computer.m_currentCard = m_computer.m_deck.dequeue();
			processCardsPlayed();
		}
		else if (m_computer.m_currentCard >= 5 && m_computer.m_currentCard << 11 && !(m_computer.m_sidePile.isFull())) 
		{
			m_computer.m_sideCard = m_computer.m_sidePile.pop();
			processCardsPlayed();
		}
		else 
		{
			processCardsPlayed();
		}
		break;
	}


	case PEEK_AT_NEXT_CARD_IN_DECK: {//shows card at top of deck
		if (!(m_player.m_deck.isEmpty())) 
		{
			cout << "The card at the top of your deck is a " << cardType(m_player.m_deck.peek()) << endl;
		}
		else 
		{
			cout << "Deck is empty. Cannot peek.\n";
		}

		break;
	}


	case DRAW_FROM_SIDE_PILE_PLAY_BOTH:
	{
		if (m_player.m_sidePile.isEmpty())
		{
			cout << "Cannot draw from pile. Pile is empty. \n";
			m_player.m_validHandPlayed = false;
		}
		else
		{
			m_player.m_sideCard = m_player.m_sidePile.pop();
			//computer decides what to do based on conditions of deck, pile, and current card
			if (m_computer.m_currentCard < 5 && !(m_computer.m_sidePile.isFull()) && !(m_computer.m_deck.isEmpty()))
			{
				m_computer.m_sidePile.push(m_computer.m_currentCard);
				m_computer.m_currentCard = m_computer.m_deck.dequeue();
				processCardsPlayed();
			}
			else if (m_computer.m_currentCard >= 5 && m_computer.m_currentCard << 11 && !(m_computer.m_sidePile.isFull()))
			{
				m_computer.m_sideCard = m_computer.m_sidePile.pop();
				processCardsPlayed();
			}
			else 
			{
				processCardsPlayed();
			}
		}
		break;
	}
	case CHECK_YOUR_NUM_CARDS://sums cards each player has
	{
		cout << "You have " << m_player.m_deck.length() + m_player.m_sidePile.length() + 1 << " cards.\n";
		m_player.m_validHandPlayed = false;
		break;
	}
		
	case CHECK_OPP_NUM_CARDS:
	{
		cout << "The computer has " << m_computer.m_deck.length() + m_computer.m_sidePile.length() + 1 << " cards.\n";
		m_player.m_validHandPlayed = false;
		break;
	}
		
	default:
		cout << "Something has gone wrong. Game may be invalid.\n";
		break;
	}
}

void WarEngine::processCardsPlayed(void)
{	
	// Computer wins ties.. it needs some help
	if (m_player.m_currentCard + m_player.m_sideCard > m_computer.m_currentCard + m_computer.m_sideCard)
	{
		cout << "You win! You receive " << cardType(m_player.m_currentCard) << ", " << cardType(m_computer.m_currentCard);
		
		if (m_player.m_sideCard != 0)
		{
			cout << ", " << cardType(m_player.m_sideCard);
		}
		if (m_computer.m_sideCard != 0)
		{
			cout << ", " << cardType(m_computer.m_sideCard);
		}

		cout << endl;
			
		m_player.m_deck.enqueue(m_player.m_currentCard);
		m_player.m_deck.enqueue(m_player.m_sideCard);
		m_player.m_deck.enqueue(m_computer.m_currentCard);
		m_player.m_deck.enqueue(m_computer.m_sideCard);
	}
	else 
	{
		cout << "You lost! Computer receives " << cardType(m_player.m_currentCard) << ", " << cardType(m_computer.m_currentCard);

		if (m_player.m_sideCard != 0)
		{
			cout << ", " << cardType(m_player.m_sideCard);
		}
		if (m_computer.m_sideCard != 0)
		{
			cout << ", " << cardType(m_computer.m_sideCard);
		}

		cout << endl;
		
		m_computer.m_deck.enqueue(m_player.m_currentCard);
		m_computer.m_deck.enqueue(m_player.m_sideCard);
		m_computer.m_deck.enqueue(m_computer.m_currentCard);
		m_computer.m_deck.enqueue(m_computer.m_sideCard);
	}

	// Clear cards used
	m_player.m_currentCard = 0;
	m_player.m_sideCard = 0;
	m_computer.m_currentCard = 0;
	m_computer.m_sideCard = 0;
	m_player.m_validHandPlayed = true; // need to set this to true to continue game
}

string WarEngine::cardType(int card)
{
	string returnCard = "";
	if (card >= 2 && card <= 10)
	{
		returnCard = to_string(card);
	}
	else if (card == 11)
	{
		returnCard = "Jack";
	}
	else if (card == 12)
	{
		returnCard = "Queen";
	}
	else if (card == 13)
	{
		returnCard = "King";
	}
	else
	{
		returnCard = "Ace";
	}
	return returnCard;
}

WarEngine::WarEngine(void)
{
	shuffleCardsIntoDecks();
	// Init players variables
	m_player.m_currentCard = 0;
	m_player.m_sideCard = 0;
	m_player.m_validHandPlayed = true;
	m_computer.m_currentCard = 0;
	m_computer.m_sideCard = 0;
	m_computer.m_validHandPlayed = true;
}

void WarEngine::start(void)
{		
	while(canGameEnd())
	{
		// Only begin hand if the last hand was valid and went through
		if (m_player.m_validHandPlayed == true)
		{
			beginHand();
		}		
		getUserInput();
		processDecision();				
	}


	//end game message
	if (m_player.m_deck.isEmpty())
	{
		cout << "\nYou Lose!\n";
	}
	else
	{
		cout << "\nYou Win!\n";
	}
}
