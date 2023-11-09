#include <iostream>
#include <string>
#include <iomanip>

enum GameState {
    Tie = 0,
    Win = 1,
    Incomplete = 2
};

class Game {

private:
    char turn = 'X';
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    void drawBoard() {
        std::cout << ' ' << board[0][0] << ' ' << '|' << ' ' << board[0][1] << ' ' << '|' << ' ' << board[0][2] << ' ' << std::endl;
        std::cout << "---|---|---" << std::endl;
        std::cout << ' ' << board[1][0] << ' ' << '|' << ' ' << board[1][1] << ' ' << '|' << ' ' << board[1][2] << ' ' << std::endl;
        std::cout << "---|---|---" << std::endl;
        std::cout << ' ' << board[2][0] << ' ' << '|' << ' ' << board[2][1] << ' ' << '|' << ' ' << board[2][2] << ' ' << std::endl;
    }
    GameState getGameState() {
        bool gameIsWin = isWin();
        bool canMakeMoreMoves = !boardIsFull();
        if (gameIsWin) {
            return Win;
        }
        else if (!canMakeMoreMoves) {
            return Tie;
        }
        else {
            return Incomplete;
        }
    }

    bool isWin() {
        for (int i = 0; i < 3; i++) {
            if (checkRow(i))
                return true;
            if (checkColumn(i))
                return true;
        }
        if (checkDiagonals())
            return true;

        return false;
    }

    bool checkRow(int index) {
        return (board[index][0] == turn && board[index][1] == turn && board[index][2] == turn);
    }

    bool checkColumn(int index) {
        return (board[0][index] == turn && board[1][index] == turn && board[2][index] == turn);
    }

    bool checkDiagonals() {
        return (board[0][0] == turn && board[1][1] == turn && board[2][2] == turn)
            || (board[2][0] == turn && board[1][1] == turn && board[0][2] == turn);
    }

    bool boardIsFull() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    void changeTurn() {
        turn = turn == 'X' ? 'O' : 'X';
    }

    bool validateMove(std::string move) {
        try {
            int row = stoi(move.substr(0, 1)) - 1;
            int col = stoi(move.substr(2, 3)) - 1;

            if (row < 0 || row > 2 || col < 0 || col > 2) {
                return false;
            }

            if (board[row][col] != ' ') {
                return  false;
            }

            return true;
        }
        catch (...) {
            return false;
        }

    }

    void makeMove(std::string move) {
        int row = stoi(move.substr(0, 1)) - 1;
        int col = stoi(move.substr(2, 3)) - 1;

        board[row][col] = turn;
    }

    void printResult(GameState gameState) {
        if (gameState == Win) {
            std::cout << "Congratulations! Player " << turn << " has won the game!" << std::endl;
        }
        else if (gameState == Tie) {
            std::cout << "The game has resulted in a tie." << std::endl;
        }
    }

public:
    void play() {
        GameState gameResult = Incomplete;
        std::string playerInput;

        std::cout << "Welcome to Tic Tac Toe. First player to get three in a row wins." << std::endl;
        drawBoard();

        while (gameResult == Incomplete) {
            changeTurn();
            bool moveIsValid = false;

            while (!moveIsValid) {
                std::cout << "Player " << turn << ": please ";
                std::cin >> playerInput;
                moveIsValid = validateMove(playerInput);
            }

            makeMove(playerInput);

            drawBoard();
            gameResult = getGameState();
        }

        printResult(gameResult);
    }
};

int main()
{
    Game game;
    game.play();
    return 0;
}


