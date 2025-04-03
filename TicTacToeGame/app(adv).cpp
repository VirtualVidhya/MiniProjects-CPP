#include <iostream>
#include <vector>
#include <string>

// Class representing the game board
class Board
{
private:
    std::vector<std::vector<char>> grid;

public:
    Board() : grid(3, std::vector<char>(3))
    {
        // Initialize board with numbers '1' to '9'
        char mark = '1';
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                grid[i][j] = mark++;
    }

    // Display the board
    void display() const
    {
        std::cout << "\nCurrent Board Status:\n";
        for (int i = 0; i < 3; ++i)
        {
            std::cout << "\t";
            for (int j = 0; j < 3; ++j)
            {
                std::cout << grid[i][j];
                if (j < 2)
                    std::cout << " | ";
            }
            std::cout << "\n";
            if (i < 2)
                std::cout << "\t---------\n";
        }
        std::cout << "\n";
    }

    // Mark a cell with the player's symbol if it is not already taken.
    // Returns true if successful, false otherwise.
    bool markCell(int move, char symbol)
    {
        int row, col;
        if (!convertMove(move, row, col))
            return false;
        if (grid[row][col] == 'X' || grid[row][col] == 'O')
            return false;
        grid[row][col] = symbol;
        return true;
    }

    // Convert move (1-9) into board indices.
    bool convertMove(int move, int &row, int &col) const
    {
        if (move < 1 || move > 9)
            return false;
        row = (move - 1) / 3;
        col = (move - 1) % 3;
        return true;
    }

    // Check if the board has a winning combination for the given symbol.
    bool checkWin(char symbol) const
    {
        // Check rows and columns
        for (int i = 0; i < 3; ++i)
        {
            if (grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol)
                return true;
            if (grid[0][i] == symbol && grid[1][i] == symbol && grid[2][i] == symbol)
                return true;
        }
        // Check diagonals
        if (grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol)
            return true;
        if (grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol)
            return true;
        return false;
    }

    // Check if the board is completely filled.
    bool isDraw() const
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (grid[i][j] != 'X' && grid[i][j] != 'O')
                    return false;
        return true;
    }
};

// Class representing a player
class Player
{
private:
    std::string name;
    char symbol;

public:
    Player(const std::string &name, char symbol)
        : name(name), symbol(symbol) {}

    char getSymbol() const { return symbol; }
    std::string getName() const { return name; }
};

// Class to manage the overall game logic
class TicTacToe
{
private:
    Board board;
    Player player1;
    Player player2;
    Player *currentPlayer;

public:
    TicTacToe(const std::string &name1, const std::string &name2)
        : player1(name1, 'X'), player2(name2, 'O'), currentPlayer(&player1) {}

    // Switch the current player pointer
    void switchPlayer()
    {
        if (currentPlayer == &player1)
            currentPlayer = &player2;
        else
            currentPlayer = &player1;
    }

    // Main game loop
    void play()
    {
        while (true)
        {
            board.display();
            int move;
            std::cout << currentPlayer->getName() << " (" << currentPlayer->getSymbol()
                      << "), enter your move (1-9): ";
            std::cin >> move;

            if (!board.markCell(move, currentPlayer->getSymbol()))
            {
                std::cout << "Invalid move. Try again.\n";
                continue;
            }

            // Check for win
            if (board.checkWin(currentPlayer->getSymbol()))
            {
                board.display();
                std::cout << currentPlayer->getName() << " wins!\n";
                break;
            }
            // Check for draw
            if (board.isDraw())
            {
                board.display();
                std::cout << "The game is a draw!\n";
                break;
            }
            // Switch turn
            switchPlayer();
        }
    }
};

int main()
{
    std::string name1, name2;
    std::cout << "Enter name for Player 1 (X): ";
    std::getline(std::cin, name1);
    std::cout << "Enter name for Player 2 (O): ";
    std::getline(std::cin, name2);

    TicTacToe game(name1, name2);
    game.play();

    return 0;
}
