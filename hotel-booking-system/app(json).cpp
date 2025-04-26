#include <iostream>
#include <fstream>
#include <vector>
#include "../libs/single_include/nlohmann/json.hpp"
using json = nlohmann::json;

const std::string DATA_FILE = "hotel_data.json";

class Room
{
private:
    int m_number;
    std::string m_type;
    int m_price;
    std::string m_occupant_name; // Empty if available

public:
    Room(int num, std::string type, int cost, std::string occupant = "")
        : m_number(num), m_type(type), m_price(cost), m_occupant_name(occupant) {}

    bool isAvailable() const
    {
        return m_occupant_name.empty();
    }

    void bookRoom(std::string name)
    {
        m_occupant_name = name;
    }

    void cancelBooking()
    {
        m_occupant_name = "";
    }

    json toJSON() const
    {
        return {{"number", m_number}, {"roomType", m_type}, {"price", m_price}, {"occupantName", m_occupant_name}};
    }

    static Room fromJSON(const json &data)
    {
        return Room(data["number"], data["roomType"], data["price"], data["occupantName"]);
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
        loadData();
    }

    void loadData()
    {
        std::ifstream file(DATA_FILE);

        if (file)
        {
            json data;
            file >> data;

            for (const auto &roomData : data)
            {
                rooms.push_back(Room::fromJSON(roomData));
            }
        }
        else
        {
            initializeRooms(); // If no data, initialize with default rooms
        }
    }

    void saveData() const
    {
        std::ofstream file(DATA_FILE);
        json data;

        for (const auto &room : rooms)
        {
            data.push_back(room.toJSON());
        }

        file << data.dump(4); // Indented JSON for readability
    }

    void initializeRooms()
    {
        rooms = {
            Room(101, "Single", 2000),
            Room(102, "Double", 3500),
            Room(103, "Suite", 5000)};

        saveData();
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

        int roomNumber;
        while (true)
        {
            std::cout << "Enter room number to book: ";
            std::cin >> roomNumber;

            for (auto &room : rooms)
            {
                if (room.getNumber() == roomNumber)
                {
                    if (room.isAvailable())
                    {
                        room.bookRoom(name);
                        saveData();
                        std::cout << "Booking successful! Room " << roomNumber << " is now occupied.\n";

                        return;
                    }
                    else
                    {
                        std::cout << "Error! Room " << roomNumber << " is already occupied. Please choose another room.\n";
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
