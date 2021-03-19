#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;
class Card {
public:
	enum rank {
		ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT,
		Nine, TEN, JACK, QUEEN, KING
	};
	enum suit {
		SPADES, HEARTS, DIAMONDS, CLUBS
	};
	friend ostream& operator<<(ostream& os, const Card& aCard);
	Card(rank r = ACE, suit = SPADES, bool ifu = true);

	//Get value
	int GetValue() const;
	//Show card
	void Flip();
private:
	rank m_Rank;//Card's value
	suit m_Suit;//Card's suit
	bool m_IsFaceUp;//show or not show
};
Card::Card(rank r = ACE, suit s = SPADES, bool ifu = true):m_Rank(r), m_Suit(s), m_IsFaceUp(ifu){

}
int Card::GetValue() const {
	//If card face down, the value is 0
	int value = 0;
	if (m_IsFaceUp) {
		value = m_Rank;
		if (value > 10) {
			value = 10;
		}
	}
	return value;
}
void Card::Flip() {
	m_IsFaceUp = !(m_IsFaceUp);
}

class Hand {
public:
	Hand();
	virtual ~Hand();
	void Add(Card* pCard);
	void Clear();
	int GetTotal();//Calculate value
protected:
	vector<Card*> m_Cards;
};
Hand::Hand() {
	m_Cards.reserve(7);
}
Hand::~Hand(){
	Clear();
}
void Hand::Clear() {
	vector<Card*>::iterator iter;
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
		delete *iter;
		*iter = nullptr;
	}
	m_Cards.clear();
}
int main(void) {
	system("pause");
	return 0;
}
