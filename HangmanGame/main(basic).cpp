#include <iostream>
#include <vector>
using namespace std;

void greet()
{
    cout << "=====================\n";
    cout << "Hangman: The Game\n";
    cout << "=====================\n";
    cout << "Instructions: Save your friend from being hanged by guessing the letters in the codeword.\n";
}

void displayMisses(int misses)
{
    if (misses == 0)
    {
        cout << "  +---+ \n";
        cout << "  |   | \n";
        cout << "      | \n";
        cout << "      | \n";
        cout << "      | \n";
        cout << "      | \n";
        cout << " ========= \n";
    }
    else if (misses == 1)
    {
        cout << "  +---+ \n";
        cout << "  |   | \n";
        cout << "  O   | \n";
        cout << "      | \n";
        cout << "      | \n";
        cout << "      | \n";
        cout << " ========= \n";
    }
    else if (misses == 2)
    {
        cout << "  +---+ \n";
        cout << "  |   | \n";
        cout << "  O   | \n";
        cout << "  |   | \n";
        cout << "      | \n";
        cout << "      | \n";
        cout << " ========= \n";
    }
    else if (misses == 3)
    {
        cout << "  +---+ \n";
        cout << "  |   | \n";
        cout << "  O   | \n";
        cout << " /|   | \n";
        cout << "      | \n";
        cout << "      | \n";
        cout << " ========= \n";
    }
    else if (misses == 4)
    {
        cout << "  +---+ \n";
        cout << "  |   | \n";
        cout << "  O   | \n";
        cout << " /|\\  | \n";
        cout << "      | \n";
        cout << "      | \n";
        cout << " ========= \n";
    }
    else if (misses == 5)
    {
        cout << "  +---+ \n";
        cout << "  |   | \n";
        cout << "  O   | \n";
        cout << " /|\\  | \n";
        cout << " /    | \n";
        cout << "      | \n";
        cout << " ========= \n";
    }
    else if (misses == 6)
    {
        cout << "  +---+ \n";
        cout << "  |   | \n";
        cout << "  O   | \n";
        cout << " /|\\  | \n";
        cout << " / \\  | \n";
        cout << "      | \n";
        cout << " ========= \n";
    }
}

void displayStatus(vector<char> incorrect, string answer)
{
    cout << "Incorrect Guesses: ";

    for (int i = 0; i < incorrect.size(); i++)
    {
        cout << incorrect[i] << " ";
    }

    cout << "\nCodeword:\n";

    for (int i = 0; i < answer.length(); i++)
    {
        cout << answer[i] << " ";
    }
}

void endGame(string answer, string codeword)
{
    if (answer == codeword)
    {
        cout << "Hooray! You saved the person from being hanged and earned a medal "
                "of honor!\n";
        cout << "Congratulations!\n";
    }
    else
    {
        cout << "On no! The man is hanged!\n";
    }
}

int main()
{
    greet();

    string codeword = "forum";
    string answer = "_____";
    int misses = 0;
    int allowedMisses = 7;
    vector<char> incorrect;
    bool guess = false;
    char letter;

    while (answer != codeword && misses < allowedMisses)
    {
        displayMisses(misses);
        displayStatus(incorrect, answer);

        cout << "\n\nPlease enter your guess: ";
        cin >> letter;

        for (int i = 0; i < codeword.length(); i++)
        {
            if (letter == codeword[i])
            {
                answer[i] = letter;
                guess = true;
            }
        }

        if (guess)
        {
            cout << "\nCorrect!\n";
        }
        else
        {
            cout << "\nIncorrect! Another portion of the person has been drawn.\n";
            incorrect.push_back(letter);
            misses++;
        }

        guess = false;
    }

    endGame(answer, codeword);

    return 0;
}