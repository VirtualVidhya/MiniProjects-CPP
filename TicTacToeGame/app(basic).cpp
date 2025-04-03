#include <iostream>
#include <stdlib.h>

// Array for the board
char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

// Variable Declaration
int choice;
int row, column;
char turn = 'X';
bool draw = false;

// Function to show the current status of the gaming board
void displayBoard()
{
    // Rander Game Board LAYOUT
    std::cout << "\nCurrent Status of the board\n";
    std::cout << "\t\t     |     |     \n";
    std::cout << "\t\t  " << board[0][0] << "  |  " << board[0][1] << "  |  "
         << board[0][2] << "\n";
    std::cout << "\t\t_____|_____|_____\n";
    std::cout << "\t\t     |     |     \n";
    std::cout << "\t\t  " << board[1][0] << "  |  " << board[1][1] << "  |  "
         << board[1][2] << "\n";
    std::cout << "\t\t_____|_____|_____\n";
    std::cout << "\t\t     |     |     \n";
    std::cout << "\t\t  " << board[2][0] << "  |  " << board[2][1] << "  |  "
         << board[2][2] << "\n";
    std::cout << "\t\t     |     |    \n";
}

bool isCellOccupied(int r, int c)
{
    if (board[r][c] != 'X' && board[r][c] != 'O')
        return false;
    else
        return true;
}

// Function to get the player input and update the board
void playerTurn()
{
    if (turn == 'X')
        std::cout << "\n\tPlayer - 1 [X] turn : ";
    else if (turn == 'O')
        std::cout << "\n\tPlayer - 2 [O] turn : ";

    // Taking input from user
    // updating the board according to choice and reassigning the turn Start
    std::cin >> choice;

    // switch case to get which row and column will be updated
    switch (choice)
    {
    case 1:
        row = 0;
        column = 0;
        break;
    case 2:
        row = 0;
        column = 1;
        break;
    case 3:
        row = 0;
        column = 2;
        break;
    case 4:
        row = 1;
        column = 0;
        break;
    case 5:
        row = 1;
        column = 1;
        break;
    case 6:
        row = 1;
        column = 2;
        break;
    case 7:
        row = 2;
        column = 0;
        break;
    case 8:
        row = 2;
        column = 1;
        break;
    case 9:
        row = 2;
        column = 2;
        break;
    default:
        std::cout << "Invalid Move";
    }

    if (turn == 'X' && !isCellOccupied(row, column))
    {
        // updating the position for 'X' symbol if it is not already occupied
        board[row][column] = 'X';
        turn = 'O';
    }
    else if (turn == 'O' && !isCellOccupied(row, column))
    {
        // updating the position for 'O' symbol if it is not already occupied
        board[row][column] = 'O';
        turn = 'X';
    }
    else
    {
        // if input position already filled
        std::cout << "Box already filled! Please choose another!!\n\n";

        playerTurn();
    }
}

// Function to get the game status e.g. GAME WON, GAME DRAW, GAME IN CONTINUE MODE
bool isGameOn()
{
    // checking the win for Simple Rows and Simple Column
    for (int i = 0; i < 3; i++)
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] ||
            board[0][i] == board[1][i] && board[0][i] == board[2][i])
            return false;

    // checking the win for both diagonal
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] ||
        board[0][2] == board[1][1] && board[0][2] == board[2][0])
        return false;

    // Checking if the game is in continue mode or not
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return true;

    // Checking if the game is already drawn
    draw = true;

    return false;
}

int main()
{
    std::cout << "\t\t\tT I C -- T A C -- T O E -- G A M E\t\t\t";
    std::cout << "\n\t\t\t\t\tFOR 2 PLAYERS\n\t\t\t";
    displayBoard();

    while (isGameOn())
    {
        playerTurn();
        displayBoard();
        // isGameOn();
    }

    if (turn == 'X' && draw == false)
        std::cout << "\n\nCongratulations! Player with 'O' has won the game";
    else if (turn == 'O' && draw == false)
        std::cout << "\n\nCongratulations! Player with 'X' has won the game";
    else
        std::cout << "\n\nGAME DRAW!!!\n\n";
}