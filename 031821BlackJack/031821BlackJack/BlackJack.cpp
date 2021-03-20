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
Card::Card(rank r, suit s, bool ifu):m_Rank(r), m_Suit(s), m_IsFaceUp(ifu){

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
	int GetTotal() const;//Calculate value
protected:
	vector<Card*> m_Cards;
};
Hand::Hand() {
	m_Cards.reserve(7);
}
Hand::~Hand(){
	Clear();
}
void Hand::Add(Card* pCard) {
	m_Cards.push_back(pCard);
}
void Hand::Clear() {
	vector<Card*>::iterator iter;
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
		delete *iter;
		*iter = nullptr;
	}
	m_Cards.clear();
}
int Hand::GetTotal()const {
	if (m_Cards.empty())
		return 0;
	if (m_Cards[0]->GetValue() == 0)
		return 0;
	//If Ace = 1
	int total = 0;
	vector<Card*>::const_iterator iter;
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
		total += (*iter)->GetValue();
	}

	bool containAce = false;
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter){
		if ((*iter)->GetValue() == Card::ACE)
			containAce = true;
	}

	//If have ACE, and value is small, Ace = 11
	if (containAce && total <= 11)
		total += 10;
	return total;
}

class GenericPlayer : public Hand {
	friend ostream& operator<<(ostream& os, const GenericPlayer& aGeneticPlayer);
public:
	GenericPlayer(const string& name = "");
	virtual ~GenericPlayer(){}
	virtual bool IsHitting() const = 0;
	bool IsBusted() const {
		return (GetTotal() > 21);
	}
	void Bust()const {
		cout << m_Name << ", Your value large than 21" << endl;
	}
protected:
	string m_Name;
};
GenericPlayer::GenericPlayer(const string& name):m_Name(name) {}

class Player : public GenericPlayer {
public:
	Player(const string& name = "");
	virtual ~Player() {

	}
	virtual bool IsHitting()const;
	void Win() const;
	void Lose() const;
	void Push() const;
};
Player::Player(const string& name) : GenericPlayer(name) {}
void Player::Win()const {
	cout << m_Name << " win" << endl;
}
void Player::Lose()const {
	cout << m_Name << " lose" << endl;
}
void Player::Push()const {
	cout << m_Name << " tie" << endl;
}
bool Player::IsHitting() const {
	cout << m_Name << ", you want more card?(Y/N)" << endl;
	char response;
	cin >> response;
	while (toupper(response) != 'Y' && toupper(response) != 'N') {
		cout << "Please enter Y/y or N/n." << endl;
		cin >> response;
	}
	return (toupper(response) == 'Y');
}

class House : public GenericPlayer {
public:
	House(const string& name = "House") :GenericPlayer(name) {}
	virtual ~House(){}
	virtual bool IsHitting()const {
		return (GetTotal() <= 16);
	}
	inline void FilpFirstCard() {
		if (!(m_Cards.empty())) {
			m_Cards[0]->Flip();
		}
		else {
			cout << "No card is hidding." << endl;
		}
	}
};

class Deck : Hand {
public:
	Deck();
	virtual ~Deck(){}
	void Populate();//create 52 cards
	void Shuffle();
	void Deal(Hand& hand);//Give card
	void AdditionalCards(GenericPlayer& aGeneticPlayer);
};
Deck::Deck() {
	m_Cards.reserve(52);
	Populate();
}
void Deck::Populate() {
	Clear();
	for (int s = Card::SPADES; s <= Card::CLUBS; ++s) {
		for (int r = Card::ACE; r <= Card::KING; ++r) {
			Add(new Card(static_cast<Card::rank>(r), static_cast<Card::suit>(s)));
		}
	}
}
void Deck::Shuffle() {
	random_shuffle(m_Cards.begin(), m_Cards.end());
}
void Deck::Deal(Hand& hand) {
	if (!m_Cards.empty()) {
		hand.Add(m_Cards.back());
		m_Cards.pop_back();
	}
	else {
		cout << "There are no any card can given." << endl;
	}
}
void Deck::AdditionalCards(GenericPlayer& aGen) {
	cout << endl;
	while (!(aGen.IsBusted()) && aGen.IsHitting()) {
		Deal(aGen);
		cout << aGen << endl;
		if (aGen.IsBusted()) {
			aGen.Bust();
		}
	}
}

class Game {
public:
	Game(const vector<string>& names);
	void Play();
private:
	Deck m_Deck;
	House m_House;
	vector<Player> m_Player;
};
Game::Game(const vector<string>& names) {
	vector<string>::const_iterator p_Name;
	for (p_Name = names.begin(); p_Name != names.end(); ++p_Name) {
		m_Player.push_back(Player(*p_Name));
	}

	srand(static_cast<unsigned int>(time(0)));
	m_Deck.Populate();
	m_Deck.Shuffle();
}
void Game::Play() {
	vector<Player>::iterator p_Player;
	for (int i = 0; i < 2; ++i) {
		for (p_Player = m_Player.begin(); p_Player != m_Player.end(); ++p_Player) {
			m_Deck.Deal(*p_Player);
		}
		m_Deck.Deal(m_House);
	}
	m_House.FilpFirstCard();
	for (p_Player = m_Player.begin(); p_Player != m_Player.end(); ++p_Player) {
		cout << *p_Player << endl;
	}
	cout << m_House << endl;
	for (p_Player = m_Player.begin(); p_Player != m_Player.end(); ++p_Player) {
		m_Deck.AdditionalCards(*p_Player);
	}

	m_House.FilpFirstCard();
	cout << endl << m_House << endl;
	m_Deck.AdditionalCards(m_House);
	if (m_House.IsBusted()) {
		for (p_Player = m_Player.begin(); p_Player != m_Player.end(); ++p_Player) {
			if (!p_Player->IsBusted()) {
				p_Player->Win();
			}
		}
	}
	else {
		for (p_Player = m_Player.begin(); p_Player != m_Player.end(); ++p_Player) {
			if (!p_Player->IsBusted()) {
				if (p_Player->GetTotal() > m_House.GetTotal())
					p_Player->Win();
				else if (p_Player->GetTotal() < m_House.GetTotal())
					p_Player->Lose();
				else
					p_Player->Push();
			}
			else
				p_Player->Lose();
		}
	}

	for (p_Player = m_Player.begin(); p_Player != m_Player.end(); ++p_Player) {
		p_Player->Clear();
	}
	m_House.Clear();
}

ostream& operator <<(ostream&, const Card& aCard);
ostream& operator <<(ostream&, const GenericPlayer& aGenericPlater);

int main(void) {
	cout << "Welcome to play BlacJack by Chingyen Huang" << endl;
	int num_Player = 0;
	while (num_Player < 1 || num_Player > 7) {
		cout << "Please enter number of players:";
		cin >> num_Player;
		cout << endl;
	}
	vector<string> names;
	string name;
	for (int i = 0; i < num_Player; ++i) {
		cout << "Please enter player name:";
		cin >> name;
		names.push_back(name);
	}
	cout << endl;
	Game aGame(names);
	char ans = 'y';
	while (toupper(ans) != 'N') {
		aGame.Play();
		cout << "Do you want to play again?(y/n):";
		cin >> ans;
		cout << endl;
	}
	cout << "Thank you for your time!! Have good day. Bye~~" << endl;
	system("pause");
	return 0;
}
ostream& operator <<(ostream& os, const Card& aCard) {
	const string RANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	//SPADES, HEARTS, DIAMONDS, CLUBS
	const string SUITS[] = { "SPADES", "HEARTS", "DIAMONDS", "CLUBS" };
	if (aCard.m_IsFaceUp) {
		os << SUITS[aCard.m_Suit] << " " << RANKS[aCard.m_Rank];
	}
	else {
		os << "XX";
	}
	return os;
}
ostream& operator <<(ostream& os, const GenericPlayer& aGenericPlayer) {
	os << aGenericPlayer.m_Name << ":\t";
	vector<Card*>::const_iterator p_Card;
	if (!aGenericPlayer.m_Cards.empty()) {
		for (p_Card = aGenericPlayer.m_Cards.begin(); p_Card != aGenericPlayer.m_Cards.end(); ++p_Card) {
			os << *(*p_Card) << "\t";
		}
		if (aGenericPlayer.GetTotal() != 0)
			cout << "(" << aGenericPlayer.GetTotal() << ")";
	}
	else
		cout << "<empty>";
	return os;
}
