#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <random>
#include <algorithm>

enum class Category
{
    Animals,
    Countries,
    Fruits,
    Count
};

class Hangman
{
private:
    static constexpr int MAX_WRONG = 6;
    std::string m_word;
    std::string m_display;
    std::vector<char> m_guessed;
    int m_wrong_cnt = 0;

    const std::array<std::array<std::string, 5>, static_cast<size_t>(Category::Count)> word_lists{{{"elephant", "giraffe", "kangaroo", "dolphin", "alligator"},
                                                                                                 {"canada", "brazil", "japan", "australia", "india"},
                                                                                                 {"banana", "strawberry", "pineapple", "mango", "orange"}}};

    const std::array<std::array<std::string, 7>, MAX_WRONG + 1> hangman_stages{{{// 0 wrong
                                                                              "  +---+",
                                                                              "  |   |",
                                                                              "      |",
                                                                              "      |",
                                                                              "      |",
                                                                              "      |",
                                                                              "========="},
                                                                             {// 1 wrong
                                                                              "  +---+",
                                                                              "  |   |",
                                                                              "  O   |",
                                                                              "      |",
                                                                              "      |",
                                                                              "      |",
                                                                              "========="},
                                                                             {// 2 wrong
                                                                              "  +---+",
                                                                              "  |   |",
                                                                              "  O   |",
                                                                              "  |   |",
                                                                              "      |",
                                                                              "      |",
                                                                              "========="},
                                                                             {// 3 wrong
                                                                              "  +---+",
                                                                              "  |   |",
                                                                              "  O   |",
                                                                              " /|   |",
                                                                              "      |",
                                                                              "      |",
                                                                              "========="},
                                                                             {// 4 wrong
                                                                              "  +---+",
                                                                              "  |   |",
                                                                              "  O   |",
                                                                              " /|\\  |",
                                                                              "      |",
                                                                              "      |",
                                                                              "========="},
                                                                             {// 5 wrong
                                                                              "  +---+",
                                                                              "  |   |",
                                                                              "  O   |",
                                                                              " /|\\  |",
                                                                              " /    |",
                                                                              "      |",
                                                                              "========="},
                                                                             {// 6 wrong
                                                                              "  +---+",
                                                                              "  |   |",
                                                                              "  O   |",
                                                                              " /|\\  |",
                                                                              " / \\  |",
                                                                              "      |",
                                                                              "========="}}};

    static Category chooseCategory()
    {
        std::cout << "Choose a category:\n";
        std::cout << " 1. Animals\n";
        std::cout << " 2. Countries\n";
        std::cout << " 3. Fruits\n";

        int choice = 0;

        std::cout << "Enter your choice (1-3): ";
        std::cin >> choice;

        return static_cast<Category>(std::clamp(choice - 1, 0, static_cast<int>(Category::Count) - 1));
    }

    void pickRandomWord(Category cat)
    {
        const auto &list = word_lists[static_cast<size_t>(cat)];
        static std::mt19937 rng{std::random_device{}()};
        std::uniform_int_distribution<size_t> dist(0, list.size() - 1);
        m_word = list[dist(rng)];
        m_display.assign(m_word.size(), '_');
    }

    void showState() const
    {
        for (const auto &line : hangman_stages[m_wrong_cnt])
            std::cout << line << "\n";

        std::cout << "\nWord: ";

        for (char c : m_display)
            std::cout << c << ' ';

        std::cout << "\nGuessed: ";

        for (char c : m_guessed)
            std::cout << c << ' ';

        std::cout << "\n\n";
    }

    bool processGuess(char guess)
    {
        m_guessed.push_back(guess);
        bool found = false;

        for (size_t i = 0; i < m_word.size(); ++i)
        {
            if (m_word[i] == guess)
            {
                m_display[i] = guess;
                found = true;
            }
        }

        if (!found)
            ++m_wrong_cnt;

        return found;
    }

public:
    void play()
    {
        Category cat = chooseCategory();
        pickRandomWord(cat);

        while (m_wrong_cnt < MAX_WRONG && m_display.find('_') != std::string::npos)
        {
            showState();
            std::cout << "Enter a letter: ";
            char guess;
            std::cin >> guess;
            guess = std::tolower(guess);

            // Skip if already guessed
            if (std::find(m_guessed.begin(), m_guessed.end(), guess) != m_guessed.end())
                continue;

            processGuess(guess);
        }

        showState();

        if (m_display.find('_') == std::string::npos)
            std::cout << "Congratulations! You guessed the word: " << m_word << "\n";
        else
            std::cout << "Game Over. The word was: " << m_word << "\n";
    }
};

int main()
{
    Hangman game;
    game.play();

    return 0;
}
