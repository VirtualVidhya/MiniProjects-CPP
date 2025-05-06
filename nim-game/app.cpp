#include <iostream>

int main()
{
    int stones = 20;
    int curr_player_index = 1;

    std::cout << "Welcome to Nimm (take 1 or 2 stones; last to take loses)!\n\n";

    while (stones > 0)
    {
        std::cout << "Stones remaining: " << stones << "\n";
        std::cout << "Player " << curr_player_index
                  << ", how many stones will you take? (1 or 2): ";

        int take;
        std::cin >> take;

        // Validate input
        while (std::cin.fail() || (take < 1 || take > 2) || take > stones)
        {
            std::cin.clear();            // clear error flags
            std::cin.ignore(1000, '\n'); // discard bad input
            std::cout << "Invalid choice. You may take only 1 or 2 stones at a time, and no more than that. Please try again: ";
                    //   << stones << ". Try again: ";
            std::cin >> take;
        }

        stones -= take;

        // If this move emptied the pile, current player loses
        if (stones == 0)
        {
            int winner = (curr_player_index == 1 ? 2 : 1);

            std::cout << "\nPlayer " << curr_player_index
                      << " took the last stone and loses!\n";
            std::cout << "Player " << winner << " wins the game. Congratulations!\n";
            
            break;
        }

        // Switch player
        curr_player_index = (curr_player_index == 1 ? 2 : 1);
        std::cout << "\n";
    }

    return 0;
}
