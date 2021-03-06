﻿#include <iomanip>
#include <iostream>
#include <windows.h>

using namespace std; 
int board[4][4];
int dirLine[] = { 1, 0, -1, 0 };
int dirColumn[] = { 0, 1, 0, -1 };

pair<int, int> generateUnoccupiedPosition() {
	int occupied = 1, line, column;
	while (occupied) {
		line = rand() % 4;
		column = rand() % 4;
		if (board[line][column] == 0)
		occupied = 0;
	}
	return make_pair(line, column);
}

void addPiece() {
	pair<int, int> pos = generateUnoccupiedPosition();
	board[pos.first][pos.second] = 2; //создание 2 
}

bool check() {
	int count = 0;
	bool gameOver = false;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (board[i][j] == 0) {
				++count;
			}
			if (i != 3 and board[i][j] == board[i + 1][j]) {
				++count;
			}

			if (j != 3 and board[i][j] == board[i][j + 1]) {
				++count;
			}
			if (board[i][j] == 2048) {
				cout << "You achieved 2048!" << endl;
			}
		}
	}
	if (count == 0){ 
		gameOver = true;
		return gameOver;
	}
	return gameOver;
}

void newGame() {
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			board[i][j] = 0;
	addPiece();
}

void printUI() {
	system("cls");
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) 
			if (board[i][j] == 0)
				cout << setw(4) << ".";
			else
				cout << setw(4) << board[i][j];
			cout << "\n";
		}
	cout << "n:new game, w: up, s: down, d: right, a: left, q: quit\n";
}

bool canDoMove(int line, int column, int nextLine, int nextColumn) { 
	if (nextLine < 0 || nextColumn < 0 || nextLine >= 4 || nextColumn >= 4
		|| (board[line][column] != board[nextLine][nextColumn] && board[nextLine][nextColumn] != 0))
		return false;
	return true;
}

void applyMove(int direction) {
	int startLine = 0, startColumn = 0, lineStep = 1, columnStep = 1;
	if (direction == 0) {
		startLine = 3;
		lineStep = -1;
	}
	if (direction == 1) {
		startColumn = 3;
		columnStep = -1; 
	}
	int movePossible = 0, canAddPiece = 0;
	do {
		movePossible = 0;
		for (int i = startLine; i >= 0 && i < 4; i += lineStep)
			for (int j = startColumn; j >= 0 && j < 4; j += columnStep) {
				int nextI = i + dirLine[direction], nextJ = j + dirColumn[direction];
				if (board[i][j] && canDoMove(i, j, nextI, nextJ)) {
					board[nextI][nextJ] += board[i][j];
					board[i][j] = 0;
					movePossible = canAddPiece = 1;
				}
			}
		printUI();
	} while (movePossible);
	if (canAddPiece)
		addPiece();
}

int main()
{
	char commandToDir[128];
	commandToDir['s'] = 0;
	commandToDir['d'] = 1;
	commandToDir['w'] = 2;
	commandToDir['a'] = 3;
	newGame();
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

			applyMove(currentDirection);
		}
		if (check() == true) {
		cout << "GAME OVER";
		}
	} 
	return 0;
}