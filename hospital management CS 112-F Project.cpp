#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>

using namespace std;
//class for room and room services
class Room
{
private:
    int roomNumber;
    bool booked;
    bool clean;

public:
    Room(int number) : roomNumber(number), booked(false), clean(true) {}

    int getRoomNumber() const
    {
        return roomNumber;
    }

    bool isBooked() const
    {
        return booked;
    }

    bool isClean() const
    {
        return clean;
    }

    void bookRoom()
    {
        booked = true;
    }

    void releaseRoom()
    {
        booked = false;
        clean = true;
    }

    void setClean(bool status)
    {
        clean = status;
    }
};
//class for customer info
class Customer
{
private:
    string name;
    string phoneNumber;

public:
    Customer(const string &name, const string &phoneNumber) : name(name), phoneNumber(phoneNumber) {}

    string getName() const
    {
        return name;
    }

    string getPhoneNumber() const
    {
        return phoneNumber;
    }
};
// class for hotel info
class Hotel
{
private:
    vector<Room> rooms;
    vector<Customer> customers;
    map<string, double> foodMenu;
    map<string, double> roomServiceMenu;
    const double roomPrice = 300.0;

public:
    Hotel(int numRooms)
    {
        for (int i = 0; i < numRooms; ++i)
        {
            rooms.push_back(Room(i + 1));
        }
        // Initialize food menu
        foodMenu["Pizza"] = 10.0;
        foodMenu["Burger"] = 8.0;
        foodMenu["Salad"] = 6.0;
        foodMenu["Coffee"] = 2.5;
        // Initialize room service menu
        roomServiceMenu["Laundry"] = 15.0;
        roomServiceMenu["Room Cleaning"] = 20.0;
        roomServiceMenu["Wake-up Call"] = 5.0;
    }

    bool bookRoom(int roomNumber, const Customer &customer)
    {
        for (Room &room : rooms)
        {
            if (room.getRoomNumber() == roomNumber)
            {
                if (!room.isBooked())
                {
                    room.bookRoom();
                    customers.push_back(customer);
                    return true;
                }
                return false; // Room already booked
            }
        }
        return false; // Invalid room number
    }

    void releaseRoom(int roomNumber)
    {
        for (Room &room : rooms)
        {
            if (room.getRoomNumber() == roomNumber)
            {
                room.releaseRoom();// Leave the room
                break;
            }
        }
    }

    void setRoomClean(int roomNumber, bool status)
    {
        for (Room &room : rooms)
        {
            if (room.getRoomNumber() == roomNumber)
            {
                room.setClean(status);//cleaning status update
                break;
            }
        }
    }

    double calculateRoomBill() const
    {
        return roomPrice;// Bill of room only
    }

    double calculateRoomServiceBill(const Customer &customer) const
    {
        double totalBill = 0.0;
        for (const auto &item : roomServiceMenu)
        {
            totalBill += item.second;
        }
        return totalBill;// Bill of room  services
    }

    double calculateFoodBill(const Customer &customer) const
    {
        double totalBill = 0.0;
        for (const auto &item : foodMenu)
        {        totalBill += item.second;// Bill of food ordered
    }
    return totalBill;
}

void printBill(const Customer &customer) const
{
    for (const Customer &cust : customers)
    {
        if (cust.getName() == customer.getName() && cust.getPhoneNumber() == customer.getPhoneNumber())
        {
            cout << "------------------------" << endl;
            cout << "Bill for customer: " << customer.getName() << endl;
            cout << "------------------------" << endl;

            double roomBill = calculateRoomBill();
            double roomServiceBill = calculateRoomServiceBill(customer);
            double foodBill = calculateFoodBill(customer);
            double totalBill = roomBill + roomServiceBill + foodBill;// Total bill of room with room services

            cout << "Room Charge: $" << fixed << setprecision(2) << roomBill << endl;
            cout << "Room Service Charge: $" << fixed << setprecision(2) << roomServiceBill << endl;
            cout << "Food Charge: $" << fixed << setprecision(2) << foodBill << endl;
            cout << "------------------------" << endl;
            cout << "Total Amount Due: $" << fixed << setprecision(2) << totalBill << endl;
            cout << "------------------------" << endl;
            return;
        }
    }
    cout << "Customer not found." << endl;
}

void printFoodMenu() const
{
    cout << "------------------------" << endl;
    cout << "Food Menu:" << endl;
    cout << "------------------------" << endl;
    for (const auto &item : foodMenu)
    {
        cout << item.first << " - $" << fixed << setprecision(2) << item.second << endl;// Printing total bill
    }
    cout << "------------------------" << endl;
}

void addCustomer(const Customer &customer)
{
    customers.push_back(customer);
}

void orderFood(const Customer &customer, const vector<string> &foodItems)
{
    addCustomer(customer);
    cout << "Order placed for customer: " << customer.getName() << endl;
    cout << "------------------------" << endl;
    cout << "Food items ordered:" << endl;
    cout << "------------------------" << endl;
    double foodBill = 0.0;
    for (const string &item : foodItems)
    {
        if (foodMenu.count(item) > 0)
        {
            cout << item << " - $" << fixed << setprecision(2) << foodMenu[item] << endl;
            foodBill += foodMenu[item];
        }
    }
    cout << "------------------------" << endl;
    cout << "Food Bill: $" << fixed << setprecision(2) << foodBill << endl;
    cout << "------------------------" << endl;
    cout << "Thank you for your order!" << endl;
    cout << "------------------------" << endl;
}
};
// A class for complaint
class HelpDesk
{
public:
    void handleComplaint(const string &complaint)
    {
        cout << "------------------------" << endl;
        cout << "Complaint received: " << complaint << endl;
        cout << "Complaint is being processed." << endl;
        cout << "------------------------" << endl;
    }

};

int main()
{
    Hotel hotel(100); // Create a hotel with 100 rooms
    HelpDesk helpDesk;

    while (true)
    {
    	cout<<endl;
    	cout<<"WELL COME TO _____ BRING IN HOTEL _____"<<endl;
    	cout<<endl;
        cout << "------------------------" << endl;
       
        cout << "1. Book a room" << endl;
        cout << "2. Check out" << endl;
        cout << "3. Room service" << endl;
        cout << "4. Print customer bill" << endl;
        cout << "5. Order food" << endl;
        cout << "6. Register complaint" << endl;
        cout << "7. Quit" << endl;
        
        cout << "------------------------" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                int roomNumber;
                string customerName, phoneNumber;
                cout << "Enter room number: ";
                cin >> roomNumber;
                cout << "Enter customer name: ";
                cin.ignore();
                getline(cin, customerName);
                cout << "Enter customer phone number: ";
                cin >> phoneNumber;

                Customer customer(customerName, phoneNumber);
                bool success = hotel.bookRoom(roomNumber, customer);
                if (success)
                {
                    cout << "Room " << roomNumber << " booked successfully for customer: " << customer.getName() << endl;
                }
                else
                {
                    cout << "Failed to book room. Room " << roomNumber << " is already booked." << endl;
                }
                break;
            }

            case 2:
            {
                int roomNumber;
                cout << "Enter room number: ";
                cin >> roomNumber;
                hotel.releaseRoom(roomNumber);
                cout << "Room " << roomNumber << " checked out successfully." << endl;
                break;
            }

            case 3:
            {
                int roomNumber;
                bool status;
                cout << "Enter room number: ";
                cin >> roomNumber;
                cout << "Enter room service status (0 for unclean, 1 for clean): ";
                cin >> status;
                hotel.setRoomClean(roomNumber, status);
                cout << "Room cleanliness status updated successfully." << endl;
                break;
            }

            case 4:
            {
                string customerName, phoneNumber;
                cout << "Enter customer name: ";
                cin.ignore();
                getline(cin, customerName);
                cout << "Enter customer phone number: ";
                cin >> phoneNumber;

                Customer customer(customerName, phoneNumber);
                hotel.printBill(customer);
                break;
            }

            case 5:
            {
                string customerName, phoneNumber;
                cout << "Enter customer name: ";
                cin.ignore();
                getline(cin, customerName);
                cout << "Enter customer phone number: ";
                cin >> phoneNumber;

                Customer customer(customerName, phoneNumber);

                int numItems;
                cout << "Enter the number of food items to order: ";
                cin >> numItems;
                vector<string> foodItems(numItems);
                cout << "Enter food items (one per line):" << endl;
                cin.ignore();
                for (int i = 0; i < numItems; ++i)
                {
                    getline(cin, foodItems[i]);
                }

                hotel.orderFood(customer, foodItems);
                break;
            }

            case 6:
            {
                string complaint;
                cout << "Enter your complaint: ";
                cin.ignore();
                getline(cin, complaint);
                helpDesk.handleComplaint(complaint);
                break;
            }

            case 7:
            {
                cout << "Exiting the program. Goodbye!" << endl;
                return 0;
            }

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}
