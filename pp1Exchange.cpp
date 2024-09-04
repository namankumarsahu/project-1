#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

// Forward declarations
class RoutingMapTree;
class MobilePhoneSet;

// Stub of MobilePhoneSet (Assume it is similar to your previous set implementation)
class MobilePhoneSet {
    // Implementation would manage a set of MobilePhones.
    // This is just a placeholder.
public:
    void displayPhones() {
        cout << "Displaying mobile phones in this exchange." << endl;
    }
};

// Exchange class representing a node in the routing map tree
class Exchange {
private:
    int id;  // Unique identifier for the exchange
    Exchange* parentExchange;  // Pointer to the parent exchange
    vector<Exchange*> children;  // List of children exchanges
    MobilePhoneSet residentPhones;  // Resident set of mobile phones

public:
    // Constructor to create an exchange with a unique ID
    Exchange(int number) : id(number), parentExchange(nullptr) {}

    // Returns the unique identifier for the exchange
    int getId() const {
        return id;
    }

    // Returns the parent exchange, or nullptr if it's the root
    Exchange* parent() const {
        return parentExchange;
    }

    // Adds a child exchange to this exchange
    void addChild(Exchange* child) {
        child->parentExchange = this;
        children.push_back(child);
    }

    // Returns the number of children of this exchange
    int numChildren() const {
        return children.size();
    }

    // Returns the ith child of the exchange (0-based index)
    Exchange* child(int i) const {
        if (i < 0 || i >= children.size()) {
            throw out_of_range("Child index is out of range");
        }
        return children[i];
    }

    // Checks if this exchange is the root
    bool isRoot() const {
        return parentExchange == nullptr;
    }

    // Returns the ith subtree (which is the ith child exchange wrapped in a RoutingMapTree)
    RoutingMapTree* subtree(int i) const;

    // Returns the resident set of mobile phones for this exchange
    MobilePhoneSet residentSet() const {
        return residentPhones;
    }

    // Display all child exchanges (for debugging)
    void displayChildren() const {
        cout << "Exchange ID: " << id << " has " << children.size() << " children." << endl;
        for (int i = 0; i < children.size(); i++) {
            cout << "  Child " << i << ": Exchange ID " << children[i]->getId() << endl;
        }
    }
};

// Stub of RoutingMapTree (which represents the entire tree structure of exchanges)
class RoutingMapTree {
private:
    Exchange* root;

public:
    // Constructor to create a routing map tree with a root exchange
    RoutingMapTree(Exchange* rootExchange) : root(rootExchange) {}

    // Returns the root exchange of the routing map tree
    Exchange* getRoot() const {
        return root;
    }
};

// Implementation of the subtree method (returns a new RoutingMapTree starting from the ith child)
RoutingMapTree* Exchange::subtree(int i) const {
    return new RoutingMapTree(child(i));
}

// Main function to demonstrate the use of the Exchange class
int main() {
    // Create root exchange
    Exchange* rootExchange = new Exchange(1);

    // Create child exchanges
    Exchange* child1 = new Exchange(2);
    Exchange* child2 = new Exchange(3);

    // Add children to root
    rootExchange->addChild(child1);
    rootExchange->addChild(child2);

    // Display the children of the root
    rootExchange->displayChildren();

    // Check if root is a root exchange
    cout << "Is root a root exchange? " << (rootExchange->isRoot() ? "Yes" : "No") << endl;

    // Display resident set of root exchange (stub functionality)
    rootExchange->residentSet().displayPhones();

    // Access and display the child exchange (example: first child)
    Exchange* firstChild = rootExchange->child(0);
    cout << "First child of root has Exchange ID: " << firstChild->getId() << endl;

    // Create a subtree from the first child
    RoutingMapTree* subtree1 = rootExchange->subtree(0);

    // Clean up allocated memory
    delete rootExchange;
    delete child1;
    delete child2;
    delete subtree1;

    return 0;
}




































// #include <iostream>
// #include <vector>

// class Exchange;  // Forward declaration

// class ExchangeList {
// public:
//     std::vector<Exchange*> list;
    
//     Exchange* ithChild(int i) {
        
//         // Implement the logic to get the ith child
//         return list[list.size() - i - 1];
//     }

//     size_t size() const {
//         return list.size();
//     }
// };

// class MobilePhoneSet {
//     // Implement MobilePhoneSet class according to your requirements
// };

// class RoutingMapTree {
// public:
//     Exchange* root;
// };

// class Exchange {
// public:
//     int eId;
//     Exchange* parent;
//     ExchangeList cList;
//     MobilePhoneSet mpSet;

//     Exchange(int number) : eId(number), parent(nullptr) {}

//     Exchange* getParent() const {
//         return parent;
//     }

//     size_t numChildren() const {
//         return cList.size();
//     }

//     Exchange* child(int i) {
//         std::cout << "childstart1 " << cList.size() << std::endl;
//         Exchange* temp = cList.ithChild(cList.size() - i - 1);
//         std::cout << "childend1 " << cList.size() << std::endl;
//         return temp;
//     }

//     bool isRoot() const {
//         return eId == 0;
//     }

//     RoutingMapTree subtree(int i) {
//         RoutingMapTree sub;
//         sub.root = child(i);
//         return sub;
//     }

//     MobilePhoneSet& residentSet() {
//         return mpSet;
//     }
// };

// int main() {
//     // Example usage
//     Exchange root(0);
//     Exchange child1(1);
//     Exchange child2(2);

//     root.cList.list.push_back(&child1);
//     root.cList.list.push_back(&child2);

//     root.child(1);

//     return 0;
// }
