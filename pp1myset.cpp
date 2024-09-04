

#include <iostream>
using namespace std;

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
    bool IsEmpty() {
        return head == nullptr;
    }

    // Check if an object is a member of the set
    bool IsMember(void* o) {
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

    // Perform union with another set
    Myset Union(Myset& a) {
        Myset unionSet;

        // Add all elements from the current set to the union set
        Node* current = this->head;
        while (current != nullptr) {
            unionSet.Insert(current->data);
            current = current->next;
        }

        // Add elements from set a that are not already in the union set
        current = a.head;
        while (current != nullptr) {
            unionSet.Insert(current->data);
            current = current->next;
        }

        return unionSet;
    }

    // Perform intersection with another set
    Myset Intersection(Myset& a) {
        Myset intersectionSet;

        Node* current = this->head;
        while (current != nullptr) {
            if (a.IsMember(current->data)) {
                intersectionSet.Insert(current->data);
            }
            current = current->next;
        }

        return intersectionSet;
    }

    // For testing purposes - print the set
    void PrintSet() {
        Node* current = head;
        cout << "{ ";
        while (current != nullptr) {
            cout << *(int*)(current->data) << " ";  // Assuming data is of type int
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

// Main function to test the Myset class
int main() {
    
        Myset set1;
        Myset set2;
    
        int a = 1, b = 2, c = 3, d = 4;

        set1.Insert(&a);
        set1.Insert(&b);
        set1.Insert(&c);

        set2.Insert(&b);
        set2.Insert(&c);
        set2.Insert(&d);

        cout << "Set 1: ";
        set1.PrintSet();

        cout << "Set 2: ";
        set2.PrintSet();
        
  
        Myset unionSet = set1.Union(set2);
        cout << "Union: ";
        unionSet.PrintSet();

        Myset intersectionSet = set1.Intersection(set2);
        cout << "Intersection: ";
        intersectionSet.PrintSet();

        set1.Delete(&a);
        cout << "Set 1 after deleting 1: ";
        set1.PrintSet();


    return 0;
}

































// #include <iostream>
// #include <memory>

// class Node {
// public:
//     std::shared_ptr<void> data;
//     std::shared_ptr<Node> next;

//     Node(std::shared_ptr<void> d, std::shared_ptr<Node> n = nullptr) : data(d), next(n) {}
// };

// class LL {
// public:
//     std::shared_ptr<Node> head;
//     int size;

//     LL() : head(nullptr), size(0) {}

//     bool isEmpty() const {
//         return size == 0;
//     }

//     std::shared_ptr<void> headData() const {
//         if (isEmpty()) return nullptr;
//         return head->data;
//     }

//     void add(std::shared_ptr<void> d) {
//         head = std::make_shared<Node>(d, head);
//         size++;
//     }

//     std::shared_ptr<void> removeFirst() {
//         if (isEmpty()) return nullptr;
//         auto temp = head->data;
//         head = head->next;
//         size--;
//         return temp;
//     }
// };

// class Myset {
// public:
//     LL set;

//     bool IsEmpty() const {
//         return set.isEmpty();
//     }

//     bool IsMember(std::shared_ptr<void> o) const {
//         auto temp = set.head;
//         while (temp != nullptr) {
//             if (temp->data == o) return true;
//             temp = temp->next;
//         }
//         return false;
//     }

//     void Insert(std::shared_ptr<void> o) {
//         if (!IsMember(o)) set.add(o);
//     }

//     Myset Union(const Myset& a) {
//         Myset temp;
//         LL temp2 = this->set;
//         LL templ = a.set;
//         std::shared_ptr<void> tempo;

//         while (!templ.isEmpty()) {
//             tempo = templ.head->data;
//             if (!IsMember(tempo)) {
//                 temp2.add(tempo);
//             }
//             templ.removeFirst();
//         }
//         temp.set = temp2;
//         return temp;
//     }

//     Myset Intersection(const Myset& a) {
//         Myset temp;
//         LL temp2;
//         LL templ = a.set;
//         std::shared_ptr<void> tempo;

//         while (!templ.isEmpty()) {
//             tempo = templ.head->data;
//             if (IsMember(tempo)) {
//                 temp2.add(tempo);
//             }
//             templ.removeFirst();
//         }
//         temp.set = temp2;
//         return temp;
//     }

//     void Delete(std::shared_ptr<void> o) {
//         if (IsMember(o)) {
//             LL tset = this->set;
//             LL temp;
//             std::shared_ptr<void> first = tset.head->data;

//             while (first != o) {
//                 temp.add(tset.removeFirst());
//                 first = tset.head->data;
//             }
//             tset.removeFirst();

//             Myset a;
//             Myset b;
//             a.set = temp;
//             b.set = tset;

//             Myset c = a.Union(b);
//             this->set = c.set;
//         } else {
//             std::cout << "Error!" << std::endl;
//         }
//     }
// };

// int main() {
//     Myset myset;

//     auto item1 = std::make_shared<int>(1);
//     auto item2 = std::make_shared<int>(2);

//     myset.Insert(item1);
//     myset.Insert(item2);

//     std::cout << "Is item1 a member: " << myset.IsMember(item1) << std::endl;
//     std::cout << "Is item2 a member: " << myset.IsMember(item2) << std::endl;

//     Myset unionSet = myset.Union(myset);
//     std::cout << "Union set size: " << unionSet.set.size << std::endl;

//     Myset intersectionSet = myset.Intersection(myset);
//     std::cout << "Intersection set size: " << intersectionSet.set.size << std::endl;

//     myset.Delete(item1);
//     std::cout << "Is item1 a member after deletion: " << myset.IsMember(item1) << std::endl;

//     return 0;
// }



