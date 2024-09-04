#include <iostream>
using namespace std;

// Exchange class representing a base station
class Exchange {
private:
    int id; // Unique identifier for the exchange

public:
    // Constructor to create an exchange with a unique id
    Exchange(int id) : id(id) {}

    // Getter for the exchange id
    int getId() const {
        return id;
    }

    // For printing the exchange information
    void print() const {
        cout << "Exchange ID: " << id << endl;
    }
};

// Node class representing each element in the linked list
class Node {
public:
    Exchange* data;
    Node* next;

    // Constructor for the Node class
    Node(Exchange* exchange) {
        data = exchange;
        next = nullptr;
    }
};

// ExchangeList class implementing the linked list of exchanges
class ExchangeList {
private:
    Node* head;

public:
    // Constructor for the ExchangeList class
    ExchangeList() {
        head = nullptr;
    }

    // Check if the list is empty
    bool isEmpty() const {
        return head == nullptr;
    }

    // Insert an Exchange at the beginning of the list
    void insert(Exchange* exchange) {
        Node* newNode = new Node(exchange);
        newNode->next = head;
        head = newNode;
    }

    // Search for an Exchange by its ID
    Exchange* findExchangeById(int id) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data->getId() == id) {
                return current->data;
            }
            current = current->next;
        }
        return nullptr; // Not found
    }

    // Delete an Exchange by its ID
    void deleteExchangeById(int id) {
        if (isEmpty()) {
            cout << "List is empty, cannot delete." << endl;
            return;
        }

        // Special case: Deleting the head node
        if (head->data->getId() == id) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        // General case: Deleting a non-head node
        Node* current = head;
        while (current->next != nullptr) {
            if (current->next->data->getId() == id) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
                return;
            }
            current = current->next;
        }

        cout << "Exchange with ID " << id << " not found in the list." << endl;
    }

    // Print all Exchanges in the list
    void printList() const {
        Node* current = head;
        while (current != nullptr) {
            current->data->print();
            current = current->next;
        }
    }

    // Destructor to free memory
    ~ExchangeList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

// Main function to test the ExchangeList class
int main() {
    ExchangeList list;

    // Creating some Exchange objects
    Exchange* exchange1 = new Exchange(101);
    Exchange* exchange2 = new Exchange(102);
    Exchange* exchange3 = new Exchange(103);

    // Inserting Exchanges into the list
    list.insert(exchange1);
    list.insert(exchange2);
    list.insert(exchange3);

    // Printing the list
    cout << "Exchange List:" << endl;
    list.printList();

    // Finding an Exchange by ID
    Exchange* found = list.findExchangeById(102);
    if (found) {
        cout << "Found Exchange with ID 102:" << endl;
        found->print();
    } else {
        cout << "Exchange with ID 102 not found." << endl;
    }

    // Deleting an Exchange by ID
    list.deleteExchangeById(102);
    cout << "After deleting Exchange with ID 102:" << endl;
    list.printList();

    // Clean up allocated memory
    delete exchange1;
    delete exchange2;
    delete exchange3;

    return 0;
}
