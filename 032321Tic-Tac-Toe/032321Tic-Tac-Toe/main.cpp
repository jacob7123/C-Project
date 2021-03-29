#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const char X      = 'X';
const char O      = 'O';
const char EMPTY  = ' ';
const char Tie    = 'T';
const char NO_ONE = 'N';

void instructtion();
char askYesNo(string question);
int askNum(string question, int high, int low = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(const vector<char>& board);
char winner(const vector<char>& board);
bool isLegal(const vector<char>& board, int move);
int humanMove(const vector<char>& board, char human);
int computerMove(vector<char>& board, char computer);
void announceWinner(char winner, char computer, char human);
int main(void) {
	int move;
	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES, EMPTY);

	instructtion();
	char human    = humanPiece();
	char computer = opponent(human); 
	char turn     = X;
	displayBoard(board);
	while (winner(board) == NO_ONE) {
		if (turn == human) {
			move        = humanMove(board, human);
			board[move] = human;
		}
		else {
			move        = computerMove(board, computer);
			board[move] = computer;
		}
		displayBoard(board);
		turn = opponent(turn);
	}
	announceWinner(winner(board), computer, human);
	system("pause");
	return 0;
}

void instructtion() {
	cout << "Welcome to play Tic-Tac-Toe by Chingyen Huang" << endl;
	cout << "You can enter 0 to 8 number, and the board will show." << endl;
	cout << "0 | 1 | 2 " << endl;
	cout << "3 | 4 | 5 " << endl;
	cout << "6 | 7 | 8 " << endl;
}
//Limit user enter
char askYesNo(string question) {
	char response;
	do {
		cout << question << "(y/n)";
		cin >> response;
	} while (tolower(response) != 'y' && tolower(response) != 'n');
	return response;
}
//Limit user enter
int askNum(string question, int high, int low) {
	int number;
	do {
		cout << question << "(" << low << "-" << high << "):";
		//cout << "low is " << low << endl;
		//cout << "high is " << high << endl;
		cin >> number;
	} while (number < low || number > high);
	return number;
}
char humanPiece() {
	char go_first = askYesNo("You want to first?");
	if (go_first == 'y') {
		cout << "The game will start. You will be first. Enjoy~~" << endl;
		return X;
	}
	else {
		cout << "The game will start. System will be first. Enjoy~~" << endl;
		return O;
	}
}
char opponent(char piece) {
	if (piece == X)
		return O;
	else
		return X;
}
void displayBoard(const vector<char>& board) {
	cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
	cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
	cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
	cout << endl;
}
char winner(const vector<char>& board) {
	const int WIN_LINE[8][3] = {
		{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, 
		{0, 3, 6}, {1, 4, 7}, {2, 5, 8},
		{0, 4, 8}, {2, 4, 6}
	};
	const int TOTAL_LINE = 8;
	for (int line = 0; line < TOTAL_LINE; ++line) {
		if (board[WIN_LINE[line][0]] != EMPTY &&
			board[WIN_LINE[line][0]] == board[WIN_LINE[line][1]] &&
			board[WIN_LINE[line][1]] == board[WIN_LINE[line][2]])
			return board[WIN_LINE[line][0]];
	}
	if (count(board.begin(), board.end(), EMPTY) == 0)
		return Tie;
	return NO_ONE; 
}
bool isLegal(const vector<char>& board, int move) {
	return (board[move] == EMPTY);
}
int humanMove(const vector<char>& board, char human) {
	int move = askNum("Where place you want to mark?", board.size() - 1);
	while (!isLegal(board, move)) {
		cout << "\n" << "You cannot mark this place since there is mark by someone." << endl;
		displayBoard(board);
		int move = askNum("Lets try again, Where place you want to mark?", board.size() - 1);
	}
	return move;
}
int computerMove(vector<char>& board, char computer) {
	int move = 0;
	bool found = false;

	//The system will find whether it can win
	while (!found && move < board.size()) {
		if (isLegal(board, move)) {//Chaeck whether computer can win or not
			board[move] = computer;
			found = winner(board) == computer;
			board[move] = EMPTY;
		}
		if (!found)
			++move;
	}

	//Whether player will win. If player will win, stop it.
	if (!found) {
		move = 0;
		char human = opponent(computer);
		while (!found && move < board.size()) {
			if (isLegal(board, move)) {
				board[move] = human;
				found = winner(board) == human;
				board[move] = EMPTY;
			}
			if (!found) {
				++move;
			}
		}
	}

	if (!found) {
		move = 0;
		int i = 0;
		const int BEST_STRATEGY[] = { 4,0,2,6,8,1,3,5,7 };
		while (!found && move < board.size()) {
			move = BEST_STRATEGY[i];
			if (isLegal(board, move))
				found = true;
			++i;
		}
	}
	cout << "I will put mark on " << move << endl;
	return move;
}
void announceWinner(char winner, char computer, char human) {
	if (winner == computer) {
		cout << "Computer win" << endl;
	}
	else if(winner == human){
		cout << "Player win" << endl;
	}
	else {
		cout << "Tie" << endl;
	}
}
