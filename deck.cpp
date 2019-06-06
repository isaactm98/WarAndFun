#include "deck.h"
#include <iostream>

void Deck::enqueue(int card)
{
	m_deckOfCards[m_backOfQueue] = card; 
	m_backOfQueue++;//increment back to keep track of next item position	
}

int Deck::dequeue(void)
{
	//get top deck card
	int returnVal = m_deckOfCards[0];
	//decrement the amount of cards
	m_backOfQueue--;

	//shift everything up
	for (int i = 0; i < m_backOfQueue; i++) 
	{
		m_deckOfCards[i] = m_deckOfCards[i + 1];
	}

	return returnVal;
}

int Deck::peek(void)
{
	return m_deckOfCards[0];
}

int Deck::length(void)
{
	return m_backOfQueue;
}

bool Deck::isEmpty(void)
{
	return m_backOfQueue==0;
}

bool Deck::isFull(void)
{
	return m_backOfQueue==(MAX_NUM_CARDS);
}

void Deck::makeEmpty(void)
{
	m_backOfQueue = 0;
}

Deck::Deck(void)
{
	m_backOfQueue = 0;
}