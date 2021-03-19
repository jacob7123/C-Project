#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
//If using standard C++, use these.
#include <ctime>
#include <cctype> //A standard Library, use to distinguish char

//using namespace std; //Not necessary
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
int main(void) {
	//Create Game
	const int MAX_WRONG = 8;//You can guess 8 times;

	//Possible words
	vector<string> words{ "GUESS" , "CPLUSPLUS", "HARD"};

	//Using random
	srand(static_cast<unsigned int>(time(0)));
	std::random_shuffle(words.begin(), words.end());

	const string THE_ONE = words[0];//Answer
	//init times of guess wrong
	int wrong = 0;

	string soFar(THE_ONE.size(), '-');
	string used = "";
	cout << "Welcome to play the game" << endl;
	cout << "System will choose one English word to be the answer from list, and the word will be hide." << endl;
	cout << "If answer is apple, it will show -----" << endl;
	cout << "The rule is that you can enter one letter in each try." << endl;
	cout << "System will check whether you guess right" << endl;
	cout << "If you guess right, system will show the letter on the right side in the word." << endl;
	cout << "You have 8 chances to guess." << endl;
	while ((wrong < MAX_WRONG) && (soFar != THE_ONE)) {
		cout << "You have " << (MAX_WRONG - wrong) << " chance." << endl;
		cout << "Used letters :\n" << used << endl;
		cout << "The situatiuon is : " << soFar << endl;

		char guess;
		cin >> guess;
		guess = toupper(guess);
		
		//if user enter the letter which is entered, let use enter again.
		while (used.find(guess) != string::npos) {
			cout << "The letter you guess is " << guess << endl;
			cout << "You already guess it." << endl;
			cout << "enter the letter you want to guess" << endl;
			cin >> guess;
			guess = toupper(guess);
		}
		used += guess;
		if (THE_ONE.find(guess) != string::npos) {
			cout << "Letter " << guess << " is in this word" << endl;
			for (int i = 0; i < THE_ONE.length(); ++i) {
				if (THE_ONE[i] == guess)
					soFar[i] = guess;
			}
		}
		else {
			cout << "The letter " << guess << "you guess is not in the word" << endl;
			++wrong;
		}
	}

	if (wrong == MAX_WRONG) {
		cout << "You cannot guess because you already guess eight times." << endl;
	}
	else {
		cout << "You get the right answer" << endl;
	}
	cout << "The answer is " << THE_ONE << endl;


	//cout << "Game over" << endl;
	system("pause");
	//cin.get();
	return 0;
}