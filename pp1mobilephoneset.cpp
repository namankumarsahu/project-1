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
    int number() const {
        return id;
    }

    // Returns the status of the phone: true if switched on, false if switched off
    bool isOn() const {
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
    Exchange* getLocation() const {
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
    int getId() const {
        return id;
    }
};

// Node class representing the elements of the set
class Node {
public:
    void* data;
    Node* next;

    Node(void* data) {
        this->data = data;
        this->next = nullptr;
    }
};

// Myset class implementing the set using a linked list
class Myset {
private:
    Node* head;

public:
    // Constructor for Myset
    Myset() {
        head = nullptr;
    }

    // Check if the set is empty
    bool IsEmpty() const {
        return head == nullptr;
    }

    // Check if an object is a member of the set
    bool IsMember(void* o) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == o) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Insert an object into the set
    void Insert(void* o) {
        if (!IsMember(o)) {  // Only insert if it's not already a member
            Node* newNode = new Node(o);
            newNode->next = head;
            head = newNode;
        }
    }

    // Delete an object from the set
    void Delete(void* o) {
        if (IsEmpty()) {
            throw runtime_error("Set is empty");
        }

        // Special case: Deleting the head node
        if (head->data == o) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        // General case: Deleting a non-head node
        Node* current = head;
        while (current->next != nullptr) {
            if (current->next->data == o) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
                return;
            }
            current = current->next;
        }

        throw runtime_error("Object not found in the set");
    }

    // For testing purposes - print the set
    void PrintSet() const {
        Node* current = head;
        cout << "{ ";
        while (current != nullptr) {
            cout << ((MobilePhone*)current->data)->number() << " ";  // Assuming data is MobilePhone pointer
            current = current->next;
        }
        cout << "}" << endl;
    }

    // Destructor to free memory
    ~Myset() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

// MobilePhoneSet class definition
class MobilePhoneSet {
private:
    Myset phoneSet;

public:
    // Insert a mobile phone into the set
    void InsertPhone(MobilePhone* phone) {
        phoneSet.Insert((void*)phone);
    }

    // Delete a mobile phone from the set
    void DeletePhone(MobilePhone* phone) {
        phoneSet.Delete((void*)phone);
    }

    // Check if a mobile phone is in the set
    bool IsMemberPhone(MobilePhone* phone) const {
        return phoneSet.IsMember((void*)phone);
    }

    // Display all mobile phones in the set
    void DisplayPhones() const {
        phoneSet.PrintSet();
    }
};

// Main function to test the MobilePhoneSet class
int main() {
    // Create some MobilePhone objects
    MobilePhone phone1(101);
    MobilePhone phone2(102);
    MobilePhone phone3(103);
// MobilePhone phone4(105);
    // Create a MobilePhoneSet
    MobilePhoneSet mobilePhoneSet;

    // Insert phones into the set
    mobilePhoneSet.InsertPhone(&phone1);
    mobilePhoneSet.InsertPhone(&phone2);
    mobilePhoneSet.InsertPhone(&phone3);

    // Display the phones in the set
    cout << "Phones in the set: ";
    mobilePhoneSet.DisplayPhones();

    // Check if a phone is a member of the set
    cout << "Is phone 102 in the set? " << (mobilePhoneSet.IsMemberPhone(&phone2) ? "Yes" : "No") << endl;

    // Delete a phone from the set
    mobilePhoneSet.DeletePhone(&phone2);
        // mobilePhoneSet.DeletePhone(&phone4);
    cout << "Phones in the set after deleting phone 102: ";
    mobilePhoneSet.DisplayPhones();

    return 0;
}
