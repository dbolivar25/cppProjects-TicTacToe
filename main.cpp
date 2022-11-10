#include <iostream>
#include <sstream>
#include <random>
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

class TicTacToeBoard {
    private:
        char cell[9] = {'1', '2', '3', '4', '5', '6', '7', '8',
                        '9'};

        char * lanes[8][3] = {&cell[0], &cell[1], &cell[2],
                          &cell[3], &cell[4], &cell[5],
                          &cell[6], &cell[7], &cell[8],
                          &cell[0], &cell[3], &cell[6],
                          &cell[1], &cell[4], &cell[7],
                          &cell[2], &cell[5], &cell[8],
                          &cell[0], &cell[4], &cell[8],
                          &cell[2], &cell[4], &cell[6],
        };

        int turnNumber = 0;

        int win = 0;

        void checkWin() {
            for (auto & lane : lanes) {
                int numXInLane = 0;
                int numOInLane = 0;
                for (char * j : lane) {
                    if (*j == 'X') ++numXInLane;
                    if (*j == 'O') ++numOInLane;
                }
                if (numXInLane == 3) win = 1;
                else if (numOInLane == 3) win = 2;
            }
        }

        static bool isNumber(const std::string &s) {
            return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
        }

        static int verifyInt() {
            std::string inputLine;
            std::string input;
            int playerSelection = 0;

            do {
                do {
                    std::cout << "Enter your move (1 - 9): ";
                    getline(std::cin, inputLine);
                    std::stringstream inputStream(inputLine);
                    inputStream >> input;
                } while (!isNumber(input));

                std::stringstream inputStream(input);
                inputStream >> playerSelection;
            } while (!(playerSelection >= 1 && playerSelection <= 9));

            return playerSelection;
        }

        bool alreadySelected(int playerMove) {
            return (this->cell[playerMove - 1] == 'X' || this->cell[playerMove - 1] == 'O');
        }

        static void printColor(char character) {
            if (character == 'X') std::cout << ANSI_GREEN << character << ANSI_RESET;
            else if (character == 'O') std::cout << ANSI_RED << character << ANSI_RESET;
            else std::cout << character;
        }

    public:
        void displayBoard() {
            std::cout << "\n";
            std::cout << "  "; printColor(cell[0]); std::cout << "  "; std::cout << "|";
            std::cout << "  "; printColor(cell[1]); std::cout << "  "; std::cout << "|";
            std::cout << "  "; printColor(cell[2]); std::cout << "  \n";
            std::cout << "------------------" << "\n";
            std::cout << "  "; printColor(cell[3]); std::cout << "  "; std::cout << "|";
            std::cout << "  "; printColor(cell[4]); std::cout << "  "; std::cout << "|";
            std::cout << "  "; printColor(cell[5]); std::cout << "  \n";
            std::cout << "------------------" << "\n";
            std::cout << "  "; printColor(cell[6]); std::cout << "  "; std::cout << "|";
            std::cout << "  "; printColor(cell[7]); std::cout << "  "; std::cout << "|";
            std::cout << "  "; printColor(cell[8]); std::cout << "  \n";
            std::cout << "\n";
        }

        void setPlayerMove() {
            int playerMove = verifyInt();
            while (alreadySelected(playerMove)) {
                std::cout << "That square is already selected" << "\n";
                playerMove = verifyInt();
            }

            cell[playerMove - 1] = 'X';

            ++turnNumber;
        }

        void setComputerMove() {
            int randomMove;
            int playerMove;

            std::random_device rd; // obtain a random number from hardware
            std::mt19937 gen(rd()); // seed the generator
            std::uniform_int_distribution<> distribution(1, 9); // define the range

            // todo: make so that computer scans through all possible lanes and makes decision based on if it is about
            //       to win or lose

            do {
                randomMove = distribution(gen);
            } while (alreadySelected(randomMove));

            playerMove = randomMove;

            std::cout << "Computer move: " << playerMove << "\n";

            cell[playerMove - 1] = 'O';

            ++turnNumber;
        }

        [[nodiscard]] bool checkEndOfGame() {
            checkWin();
            if (turnNumber == 9 || win == 1 || win == 2) return true;
            else return false;
        }

        [[nodiscard]] int getWinner() const {
            return win;
        }
};

bool userDecision() {
    std::string userInput;
    std::string inputLine;
    std::string prompt = "Press enter to play again ('q' to quit): ";
    std::string quitKey = "q";

    do {
        userInput = "c";
        std::cout << "\n";
        std::cout << prompt;
        getline(std::cin, inputLine);

        if (inputLine.length() != 0) {
            userInput = inputLine.substr(0, inputLine.find(' '));
        }
    } while (!(userInput == "c" || userInput == quitKey));

    return (userInput == "c");
}

int main() {

    do {
        TicTacToeBoard ticTacToeBoard;

        ticTacToeBoard.displayBoard();

        while (true) {
            ticTacToeBoard.setPlayerMove();
            ticTacToeBoard.displayBoard();
            if (ticTacToeBoard.checkEndOfGame()) break;

            ticTacToeBoard.setComputerMove();
            ticTacToeBoard.displayBoard();
            if (ticTacToeBoard.checkEndOfGame()) break;
        }

        switch (ticTacToeBoard.getWinner()) {
            case 1:
                std::cout << "You Win!" << "\n";
                break;
            case 2:
                std::cout << "You Lose." << "\n";
                break;
            default:
                std::cout << "Draw." << "\n";
                break;
        }
    } while (userDecision());

    // todo: add thanks for playing message, scoreboards after games end, and final summary after quitting.

    return 0;
}
