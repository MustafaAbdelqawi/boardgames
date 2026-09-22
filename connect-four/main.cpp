#include <iostream>
#include <string>
#include <array>
#include <algorithm>
//#include <cctype>
#include <limits>

constexpr int BoardRows = 6;
constexpr int BoardColumns = 7;
constexpr int ConnectLength = 4;
constexpr char EmptyCell = '-';
constexpr char PlayerOneSymbol = 'X';
constexpr char PlayerTwoSymbol = 'O';
constexpr int DirectionCount = 4;

using Board = std::array<std::array<char, BoardColumns>, BoardRows>;

bool hasNonWhitespace(const std::string& text){
	return std::any_of(text.begin(), text.end(), [](unsigned char character){
		return !std::isspace(character);
	});
}

void displayBoard(const Board& board){
	for (int column = 1; column <= BoardColumns; ++column) {
		std::cout << column << "\t";
	}
	std::cout << '\n';
	for (int rowIndex = 0; rowIndex < BoardRows; ++rowIndex) {
		for (int columnIndex = 0; columnIndex < BoardColumns; ++columnIndex) {
			std::cout << board[rowIndex][columnIndex] << "\t";
		}
		std::cout << '\n';
	}
}

bool checkWin(const Board& board, int rowPosition, int columnPosition, const char playerSymbol){
	const std::array<std::array<int, 2>, DirectionCount> directions = {
		{{0, 1}, {1, 0}, {1, 1}, {1, -1}}
	};

	for (const auto& direction : directions) {
		int connected = 1;
		for (int side : {-1, 1}) {
			for (int step = 1; step < ConnectLength; ++step) {
				int row = rowPosition + side * step * direction[0];
				int column = columnPosition + side * step * direction[1];

				if (row < 0 || row >= BoardRows || column < 0 || column >= BoardColumns ||
					board[row][column] != playerSymbol) {
					break;
				}
				++connected;
			}
		}
		if (connected >= ConnectLength) return true;
	}

	return false;
}

bool assignValue(Board& board, int columnChoice, const std::pair<std::string, char>& player, bool& won){
	if (columnChoice < 0 || columnChoice >= BoardColumns) return false;

	for(int rowIndex = BoardRows - 1; rowIndex >= 0; --rowIndex){
		if(board[rowIndex][columnChoice] == EmptyCell)
		{
			board[rowIndex][columnChoice] = player.second;
			displayBoard(board);
			won = checkWin(board, rowIndex, columnChoice, player.second);
			if(won) std::cout << "\' " << player.first << " \' Won the game!\n";
			return true;
		}
	}
	return false;
}

bool askInput(Board& board, const std::pair<std::string, char>& player, bool& inputEnded){
	int choice;
	bool won = false;
	bool validMove = false;
	inputEnded = false;
	do{
		std::cout << "\' " << player.first << " \' Please select your column 1 ---> "
			      << BoardColumns << ": ";
		if (!(std::cin >> choice)) {
			if (std::cin.eof()) {
				inputEnded = true;
				return false;
			}
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		validMove = assignValue(board, choice - 1, player, won);
		if (!validMove) std::cout << "That column is invalid or full. Try again.\n";
	}while(!validMove);
	return won;
}

int main(){

	for(auto x : {-1,1}){
		std::cout << x << "\n";
	}

	std::cout << "Welcome to my connect-four game board.\n Please enter the names of the two players...\n";
	std::pair<std::string, char> player1;
	std::pair<std::string, char> player2;
	std::cout << "Player 1 name: ";
	if (!std::getline(std::cin, player1.first)) {
		std::cout << "Input ended. Exiting the game.\n";
		return 0;
	}
	while (!hasNonWhitespace(player1.first)) {
		std::cout << "Please enter a name for Player 1: ";
		if (!std::getline(std::cin, player1.first)) {
			std::cout << "Input ended. Exiting the game.\n";
			return 0;
		}
	}
	std::cout << "Player 2 name: ";
	if (!std::getline(std::cin, player2.first)) {
		std::cout << "Input ended. Exiting the game.\n";
		return 0;
	}
	while (!hasNonWhitespace(player2.first)) {
		std::cout << "Please enter a name for Player 2: ";
		if (!std::getline(std::cin, player2.first)) {
			std::cout << "Input ended. Exiting the game.\n";
			return 0;
		}
	}
	player1.second = PlayerOneSymbol;
	player2.second = PlayerTwoSymbol;

	std::cout << "Welcome, " << player1.first << " (" << player1.second << ") and "
		      << player2.first << " (" << player2.second << ").\n"
		      << "Choose a column from 1 to " << BoardColumns << " to make your move.\n"
		      << "The first player to connect four pieces horizontally, vertically, or diagonally wins.\n";
	Board board;
	for(auto& row : board){
		row.fill(EmptyCell);
	}
	displayBoard(board);
	int numberOfMoves = 0;
	bool won = false;
	bool inputEnded = false;
	do{
		won = askInput(board, player1, inputEnded);
		if (won || inputEnded) break;
		numberOfMoves++;

		won = askInput(board, player2, inputEnded);
		if (won || inputEnded) break;
		numberOfMoves++;
	}while(numberOfMoves < BoardRows * BoardColumns);
	if (inputEnded) std::cout << "Input ended. Exiting the game.\n";
	else if (!won) std::cout << "The game ended in a draw.\n";
	return 0;
}
