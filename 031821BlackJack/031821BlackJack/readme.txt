Simple Black Jack:
	System gives Poker card to players. Every player should collect card and the value should be close
21, but the value cannot over 21. The value of each card is the number on the card; however, A can be 
1 or 11 by player, and J, Q, and K value are 10.
	System is banker. There is/are 1 to 7 players. When the game start, banker will give 2 card to each
player. Everyone can see their card and value, but banker has one card every player cannot know the value.
	Each player can claim more if they want. However, if their value larger than 21, they fail. After 
everyone stop claiming card, banker will show the hiding card. If the banker's value less than 16, bnaker
should claim card. If banker's value large than 21, the players whose value less than 21 win. If banker's
value is not over 21, each player will compare value with banker. If their value large than banker, player
win. If not, banker win.

Class			Base Class		Description
---------------------------------------------------
Game			None			Main class
Player			GenericPlayer	Player
House			GenericPlayer	System
GenericPlayer	Hand			Abstract game player
Card			None			Poker card
Hand			None			Card in player's hand
Deck			Hand			None