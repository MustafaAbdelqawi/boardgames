#include <iostream>
#include <stdlib.h> 
#include <vector>
#include <string>
#include <limits>
using namespace std;

const int rows = 3;
const int columns = 3;

void displayCell(char cell){
	if (cell == 'X') {
		std::cout << "\033[31m●\033[0m";
	} else if (cell == 'O') {
		std::cout << "\033[33m●\033[0m";
	} else {
		std::cout << cell;
	}
}

void displayBoard(char** arr){

	for(int i = 0; i < rows; ++i){
		std::cout << "*---*---*---*\n";
		std::cout << "* ";
		displayCell(arr[i][0]);
		std::cout << " | ";
		displayCell(arr[i][1]);
		std::cout << " | ";
		displayCell(arr[i][2]);
		std::cout << " *\n";
	}
	std::cout << "*---*---*---*\n";
}

bool askPosition(char** array, string player, char value){
	while(true){
		std::cout << player << ", Please choose your play index...";
		int pos;
		if(!(std::cin >> pos)){
			if(std::cin.eof())
				return false;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter a number from 0 to 8.\n";
			continue;
		}
		if(pos < 0 || pos > 8 || array[pos/columns][pos%columns] == 'X' || array[pos/columns][pos%columns] == 'O'){
			std::cout << "Invalid position please select a free number from the board...\n";
			continue;
		}

		array[pos/columns][pos%columns] = value;
		return true;
	}
}

bool iSGameOn(char** array){
	for(int i=0;i<rows;++i){
		for(int j=0; j<columns; ++j){
			if(array[i][j] != 'X' && array[i][j] != 'O'){
				return true;
			}
		}
	}
	std::cout << "Game Draw!!" << std::endl;
	return false;
}

bool checkWin(char ** array, string player, char letter){
	//check rows and columns
		for(int i = 0; i<rows; ++i){
			if(array[i][0] == letter && array[i][0] == array[i][1] && array[i][0] == array[i][2]){
				std::cout << player << " Congrates, You won by completeing row...\n";
				return true;
			}
			else if(array[0][i] == letter && array[0][i] == array[1][i] && array[0][i] == array[2][i]){
				std::cout << player << " Congrates, You won by completeing Columns...\n";
				return true;
			}
		}
	//check left diagonal
	bool left = false;
	for(int i = 0; i < columns; ++i){
		if(array[i][i] == letter)
			left = true;
		else{
			left = false;
			break;
		}
	}

	//check right diagonal
	bool right = false;
	int j = columns-1;
	for(int i = 0; i < rows; ++i){
		if(array[i][j] == letter){
			right = true;
		}
		else{
			right = false;
			break;
		}
		j--;
	}

	if(right || left){
		std::cout << player << " Congrates, You won by completeing diagonally...\n";
		return true;
	}

	return false;
}

int main(){
	char **gameBoard = new char*[rows];
	std::cout << "Welcome to Tic-Tac-Toe game.\n";
	std::cout << "The game is a board game type consists of a matrix of 9 position (3*3) that can be played by two players.\n";
	std::cout << "Each player will be assign a letter 'X' or 'O'\n";
	std::cout << "The Player with letter 'X' shall start the game followed by the player with letter 'O'\n";
	std::cout << "The player who can comblete a row, column or diagonal shape (left or right) will win the game.\n";
	for(int i = 0; i <rows; i++)
		gameBoard[i] = new char[columns];

	for(int i = 0; i < rows; ++i){
		for(int j=0; j<columns; ++j){
			std::string s = std::to_string(i*rows+j);
			gameBoard[i][j] = *s.c_str();
		}
	}

	displayBoard(gameBoard);

	char Player_1{'X'};
	char Player_2{'O'};
	std::string name1;
	std::string name2;
	std::cout << "Please enter the name of first player (X): ";
	std::cin >> name1;
	std::cout << "Please enter the name of second player (O): ";
	std::cin >> name2;
	int moves = 0;
	while(true)
	{
		if(!askPosition(gameBoard, name1, 'X'))
			break;
		displayBoard(gameBoard);
		if(checkWin(gameBoard, name1, 'X') || !iSGameOn(gameBoard))
			break;
		if(!askPosition(gameBoard, name2, 'O'))
			break;
		displayBoard(gameBoard);
		if(checkWin(gameBoard, name2, 'O') || !iSGameOn(gameBoard))
			break;
	}


	//Free each sub-array
	for(int i = 0; i < 3; ++i) {
		delete[] gameBoard[i];   
	}
	delete []gameBoard;

	return 0;
}
