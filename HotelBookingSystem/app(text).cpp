#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

const std::string DATA_FILE = "hotel_data.txt";

class Room
{
private:
    int m_number;
    std::string m_type;
    int m_price;
    std::string m_occupant_name;

public:
    Room(int num, std::string type, int cost, std::string occupant = "")
        : m_number(num), m_type(type), m_price(cost), m_occupant_name(occupant) {}

    void bookRoom(std::string name)
    {
        m_occupant_name = name;
    }

    void cancelBooking()
    {
        m_occupant_name = "";
    }

    bool isAvailable() const
    {
        return m_occupant_name.empty();
    }

    int getNumber()
    {
        return m_number;
    }

    void setNumber(int n)
    {
        m_number = n;
    }

    std::string getRoomType()
    {
        return m_type;
    }

    void setRoomType(const std::string &r)
    {
        m_type = r;
    }

    int getPrice()
    {
        return m_price;
    }

    void setPrice(int p)
    {
        m_price = p;
    }

    std::string getOccupantName()
    {
        return m_occupant_name;
    }

    void setOccupantName(const std::string &o)
    {
        m_occupant_name = o;
    }
};

class Hotel
{
private:
    std::vector<Room> rooms;

public:
    Hotel()
    {
        initializeRooms();

        loadData();
    }

    void loadData()
    {
        std::ifstream file("bookings.txt");

        if (file.is_open())
        {
            int room_no;
            int price;
            std::string type;
            std::string occupant_name;

            // while (file >> room_no >> price >> type >> occupant_name)
            // {
            //     file.ignore();
            //     // getline(file, price);
            //     getline(file, type);
            //     getline(file, occupant_name);

            //     for (auto &room : rooms)
            //     {
            //         if (room.getNumber() == room_no)
            //         {
            //             room.setOccupantName(occupant_name);
            //         }
            //     }
            // }

            while (file >> room_no >> type)
            {
                std::getline(file, price); // Read the remaining line after price
                std::stringstream ss(price);
                std::getline(ss, price, ' ');    // Extract the room type
                std::getline(ss, occupant_name); // Extract the occupant name

                // Remove leading whitespace from type and occupant_name
                type.erase(0, type.find_first_not_of(' '));
                occupant_name.erase(0, occupant_name.find_first_not_of(' '));

                for (auto &room : rooms)
                {
                    if (room.getNumber() == room_no)
                    {
                        room.setRoomType(type);
                        room.setPrice(price);
                        room.setOccupantName(occupant_name);
                    }
                }
            }

            file.close();
        }
        else
        {
            // initializeRooms();
            saveData();
        }
    }

    void saveData()
    {
        std::ofstream file("bookings.txt");

        if (file.is_open())
        {
            for (auto &room : rooms)
            {
                // file << room.roomNumber << " " << room.isOccupied << " " << room.guestName << " " << room.contactNumber << "\n";
                file << room.getNumber() << " - " << room.getRoomType() << " - " << room.getPrice() << " - " << room.getOccupantName() << "\n";
            }

            file.close();

            std::cout << "Booking data saved.\n";
        }
    }

    void initializeRooms()
    {
        rooms = {
            Room(101, "Single", 2000),
            Room(102, "Double", 3500),
            Room(103, "Suite", 5000)};
    }

    void displayRooms()
    {
        std::cout << "\nRoom Details:\n";

        for (auto &room : rooms)
        {
            std::cout << "Room " << room.getNumber() << " - " << room.getRoomType() << " - Rs." << room.getPrice()
                      << "/night - " << (room.isAvailable() ? "Available" : "Occupied by " + room.getOccupantName()) << "\n";
        }
    }

    void bookRoom()
    {
        std::string name;
        std::cout << "Enter your name: ";
        std::cin.ignore();
        getline(std::cin, name);

        int room_no;

        while (true)
        {
            std::cout << "Enter room number to book: ";
            std::cin >> room_no;

            for (auto &room : rooms)
            {
                if (room.getNumber() == room_no)
                {
                    if (room.isAvailable())
                    {
                        room.bookRoom(name);
                        saveData();
                        std::cout << "Booking successful! Room " << room_no << " is now occupied.\n";

                        return;
                    }
                    else
                    {
                        std::cout << "Error! Room " << room_no << " is already occupied. Please choose another room.\n";
                    }
                }
            }

            std::cout << "Invalid room number. Please enter a valid room.\n";
        }
    }

    void cancelBooking()
    {
        std::string name;
        std::cout << "Enter your name: ";
        std::cin.ignore();
        getline(std::cin, name);

        int roomNumber;

        while (true)
        {
            std::cout << "Enter room number to cancel: ";
            std::cin >> roomNumber;

            for (auto &room : rooms)
            {
                if (room.getNumber() == roomNumber && room.getOccupantName() == name)
                {
                    room.cancelBooking();
                    saveData();
                    std::cout << "Cancellation successful! Room " << roomNumber << " is now available.\n";
                    return;
                }
            }

            std::cout << "No booking found under your name for this room. Please enter a valid room number.\n";
        }
    }

    void mainMenu()
    {
        while (true)
        {
            std::cout << "\nWelcome to the Hotel Booking System!\n";
            std::cout << "1. View Available Rooms\n";
            std::cout << "2. Book a Room\n";
            std::cout << "3. Cancel a Booking\n";
            std::cout << "4. Exit\n";
            std::cout << "Enter your choice: ";

            int choice;
            std::cin >> choice;

            switch (choice)
            {
            case 1:
                displayRooms();
                break;
            case 2:
                bookRoom();
                break;
            case 3:
                cancelBooking();
                break;
            case 4:
                std::cout << "\nExiting...\nBooking data saved.\nSystem shutting down. Goodbye!\n";
                return;
            default:
                std::cout << "Invalid choice! Please enter a valid option.\n";
            }
        }
    }

    ~Hotel()
    {
        saveData();
        std::cout << "System shutting down. Goodbye!\n";
    }
};

int main()
{
    Hotel hotel;
    hotel.mainMenu();

    return 0;
}
