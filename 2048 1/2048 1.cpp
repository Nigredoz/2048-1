#include <iostream>

using namespace std; 

int board[4][4];
int dirline[] = { 1, 0, -1, 0 };
int dirColumn[] = { 0, 1, 0, -1 };

void newGame() {
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			board[i][j] = 0;
}

void printUI() {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) 
			if (board[i][j] == 0)
				cout << " ";
			else
				cout << board[i][j];
			cout << "\n";
		}
	cout << "n:new game, w: up, s: down, d: right, a: left, q: quit";
}

int main()
{
	char commandToDir[128];
	commandToDir['s'] = 0;
	commandToDir['d'] = 1;
	commandToDir['w'] = 2;
	commandToDir['a'] = 3;
	while (true) {
		printUI();
		char command; 
		cin >> command;
		if (command == 'n')
			newGame();
		else if (command == 'q')
			break;
		else {
			int currentDirection = commandToDir[command];
			cout << currentDirection << "\n";
		}
	}
	return 0;
}