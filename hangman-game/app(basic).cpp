#include <iostream>
#include <vector>

void greet()
{
    std::cout << "=====================\n";
    std::cout << "Hangman: The Game\n";
    std::cout << "=====================\n";
    std::cout << "Instructions: Save your friend from being hanged by guessing the letters in the codeword.\n";
}

void displayMisses(int misses)
{
    switch (misses)
    {
    case 0:
        std::cout << "  +---+ \n";
        std::cout << "  |   | \n";
        std::cout << "      | \n";
        std::cout << "      | \n";
        std::cout << "      | \n";
        std::cout << "      | \n";
        std::cout << " ========= \n";
        break;
    case 1:
        std::cout << "  +---+ \n";
        std::cout << "  |   | \n";
        std::cout << "  O   | \n";
        std::cout << "      | \n";
        std::cout << "      | \n";
        std::cout << "      | \n";
        std::cout << " ========= \n";
        break;
    case 2:
        std::cout << "  +---+ \n";
        std::cout << "  |   | \n";
        std::cout << "  O   | \n";
        std::cout << "  |   | \n";
        std::cout << "      | \n";
        std::cout << "      | \n";
        std::cout << " ========= \n";
        break;
    case 3:
        std::cout << "  +---+ \n";
        std::cout << "  |   | \n";
        std::cout << "  O   | \n";
        std::cout << " /|   | \n";
        std::cout << "      | \n";
        std::cout << "      | \n";
        std::cout << " ========= \n";
        break;
    case 4:
        std::cout << "  +---+ \n";
        std::cout << "  |   | \n";
        std::cout << "  O   | \n";
        std::cout << " /|\\  | \n";
        std::cout << "      | \n";
        std::cout << "      | \n";
        std::cout << " ========= \n";
        break;
    case 5:
        std::cout << "  +---+ \n";
        std::cout << "  |   | \n";
        std::cout << "  O   | \n";
        std::cout << " /|\\  | \n";
        std::cout << " /    | \n";
        std::cout << "      | \n";
        std::cout << " ========= \n";
        break;
    case 6:
        std::cout << "  +---+ \n";
        std::cout << "  |   | \n";
        std::cout << "  O   | \n";
        std::cout << " /|\\  | \n";
        std::cout << " / \\  | \n";
        std::cout << "      | \n";
        std::cout << " ========= \n";
        break;
    default:
        break;
    }
}

void displayStatus(std::vector<char> incorrect, std::string answer)
{
    std::cout << "Incorrect Guesses: ";

    for (int i = 0; i < incorrect.size(); i++)
    {
        std::cout << incorrect[i] << " ";
    }

    std::cout << "\nCodeword:\n";

    for (int i = 0; i < answer.length(); i++)
    {
        std::cout << answer[i] << " ";
    }
}

void endGame(std::string answer, std::string codeword)
{
    if (answer == codeword)
    {
        std::cout << "Hooray! You saved the person from being hanged and earned a medal "
                     "of honor!\n";
        std::cout << "Congratulations!\n";
    }
    else
    {
        std::cout << "On no! The man is hanged!\n";
    }
}

int main()
{
    greet();

    std::string codeword = "forum";
    std::string answer = "_____";
    int misses = 0;
    int allowedMisses = 7;
    std::vector<char> incorrect;
    bool guess = false;
    char letter;

    while (answer != codeword && misses < allowedMisses)
    {
        displayMisses(misses);
        displayStatus(incorrect, answer);

        std::cout << "\n\nPlease enter your guess: ";
        std::cin >> letter;

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
            std::cout << "\nCorrect!\n";
        }
        else
        {
            std::cout << "\nIncorrect! Another portion of the person has been drawn.\n";
            incorrect.push_back(letter);
            misses++;
        }

        guess = false;
    }

    endGame(answer, codeword);

    return 0;
}