#include "sidePile.h"

void SidePile::push(int card)
{
	m_stackOfCards[m_topSpotAvailable] = card;
	m_topSpotAvailable++;
}

int SidePile::pop(void)
{
	m_topSpotAvailable--;
	return m_stackOfCards[m_topSpotAvailable];
}

int SidePile::peek(void)
{
	
	return m_stackOfCards[m_topSpotAvailable-1];
}

int SidePile::length(void)
{
	return m_topSpotAvailable;
}

bool SidePile::isEmpty(void)
{
	return m_topSpotAvailable==0;
}

bool SidePile::isFull(void)
{
	return m_topSpotAvailable==MAX_CARDS;
}

int SidePile::getCapacity(void)
{
	return MAX_CARDS;
}

SidePile::SidePile(void)
{
	m_topSpotAvailable = 0;
}