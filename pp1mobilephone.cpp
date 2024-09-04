#include <iostream>
#include <stdexcept>
using namespace std;

// Forward declaration of the Exchange class
class Exchange;

// MobilePhone class definition
class MobilePhone {
private:
    int id;            // Unique identifier for the mobile phone
    bool status;       // Status of the phone: true if switched on, false if switched off
    Exchange* location; // Pointer to the base station (Exchange) the phone is registered with

public:
    // Constructor to create a mobile phone with a unique id
    MobilePhone(int number) {
        id = number;
        status = false;  // Initially, the phone is switched off
        location = nullptr;  // Initially, the location is null
    }

    // Returns the unique identifier of the mobile phone
    int number() {
        return id;
    }

    // Returns the status of the phone: true if switched on, false if switched off
    bool isOn() {
        return status;
    }

    // Changes the status to switched on
    void switchOn() {
        status = true;
    }

    // Changes the status to switched off and deregisters from the base station
    void switchOff() {
        status = false;
        location = nullptr;  // Deregister from the base station
    }

    // Returns the base station with which the phone is registered
    Exchange* getLocation() {
        if (!status) {
            throw runtime_error("The phone is switched off");
        }
        return location;
    }

    // Registers the phone with a base station (Exchange)
    void registerLocation(Exchange* exchange) {
        location = exchange;
    }
};

// Exchange class definition (placeholder)
class Exchange {
private:
    int id;  // Unique identifier for the exchange

public:
    // Constructor to create an exchange with a unique id
    Exchange(int id) : id(id) {}

    // Returns the unique identifier of the exchange
    int getId() {
        return id;
    }
};

// Main function for testing the MobilePhone class
int main() {
    try {
        // Create a mobile phone with id 12345
        MobilePhone phone(12345);
        cout << "Phone number: " << phone.number() << endl;
        cout << "Phone status (before switch on): " << phone.isOn() << endl;

        // Switch on the phone
        phone.switchOn();
        cout << "Phone status (after switch on): " << phone.isOn() << endl;

        // Simulate an exchange (base station)
        Exchange exchange(1);  // Assume Exchange class has an id

        // Register the phone to a base station
        phone.registerLocation(&exchange);

        // Get the location (base station)
        cout << "Phone is registered to exchange: " << phone.getLocation()->getId() << endl;

        // Switch off the phone
        phone.switchOff();
        cout << "Phone status (after switch off): " << phone.isOn() << endl;

        // Try to get the location after the phone is switched off
        cout << "Trying to get location when phone is off..." << endl;
        phone.getLocation();  // This will throw an exception

    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}



























// #include <iostream>
// #include <memory>
// #include <vector>

// class Exchange;  // Forward declaration

// class MobilePhone {
// public:
//     int id;
//     bool status;
//     Exchange* base;

//     MobilePhone(int number) : id(number), status(false), base(nullptr) {}

//     bool getStatus() const {
//         return status;
//     }

//     void switchOn() {
//         status = true;
//     }

//     void switchOff() {
//         status = false;
//     }

//     Exchange* getLocation() const {
//         return base;
//     }
// };

// class Node {
// public:
//     std::shared_ptr<void> data;
//     Node* next;

//     Node(std::shared_ptr<void> d) : data(d), next(nullptr) {}
// };

// class Myset {
// public:
//     Node* head;
//     int size;

//     Myset() : head(nullptr), size(0) {}

//     bool isEmpty() const {
//         return size == 0;
//     }
// };

// class MobilePhoneSet : public Myset {
// public:
//     bool IsMember2(int i) {
//         Node* temp = head;
//         while (temp != nullptr) {
//             auto x = std::static_pointer_cast<MobilePhone>(temp->data);
//             if (x->id == i) return true;
//             temp = temp->next;
//         }
//         return false;
//     }

//     std::shared_ptr<MobilePhone> id2mp(int i) {
//         Node* temp = head;
//         std::shared_ptr<MobilePhone> temp2 = std::make_shared<MobilePhone>(-1);
//         while (temp != nullptr) {
//             auto x = std::static_pointer_cast<MobilePhone>(temp->data);
//             if (x->id == i) return temp2 = x;
//             temp = temp->next;
//         }
//         return temp2;
//     }

//     std::shared_ptr<MobilePhone> removeFirst2() {
//         if (isEmpty()) return nullptr;
//         auto temp = std::static_pointer_cast<MobilePhone>(head->data);
//         head = head->next;
//         size--;
//         return temp;
//     }
// };

// int main() {
//     MobilePhoneSet phoneSet;

//     // Example usage
//     auto phone1 = std::make_shared<MobilePhone>(1);
//     auto phone2 = std::make_shared<MobilePhone>(2);

//     phoneSet.head = new Node(phone1);
//     phoneSet.head->next = new Node(phone2);
//     phoneSet.size = 2;

//     std::cout << "Is phone with ID 1 a member: " << phoneSet.IsMember2(1) << std::endl;
//     std::cout << "Is phone with ID 3 a member: " << phoneSet.IsMember2(3) << std::endl;

//     auto phone = phoneSet.id2mp(1);
//     std::cout << "Phone ID: " << phone->id << ", Status: " << phone->getStatus() << std::endl;

//     auto removedPhone = phoneSet.removeFirst2();
//     std::cout << "Removed phone ID: " << removedPhone->id << std::endl;

//     return 0;
// }
