#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include <stdexcept>

using namespace std;

class Exchange;
class MobilePhone;
class Node;
class MobilePhoneSet;
class Myset;
class LL;
class RoutingMapTree;

class Node {
public:
    void* data;
    Node* next;

    Node(void* d, Node* n) : data(d), next(n) {}
};

class LL {
public:
    Node* head;
    int size;

    LL() : head(nullptr), size(0) {}

    bool isEmpty() { return size == 0; }

    void* headData() {
        if (isEmpty()) return nullptr;
        return head->data;
    }

    void add(void* d) {
        head = new Node(d, head);
        size++;
    }

    void* removeFirst() {
        if (isEmpty()) return nullptr;
        void* temp = head->data;
        head = head->next;
        size--;
        return temp;
    }
};

class Myset {
public:
    LL set;

    bool IsEmpty() { return set.isEmpty(); }

    bool IsMember(void* o) {
        Node* temp = set.head;
        while (temp != nullptr) {
            if (temp->data == o) return true;
            temp = temp->next;
        }
        return false;
    }

    void Insert(void* o) {
        if (!IsMember(o)) set.add(o);
    }

    Myset Union(Myset a) {
        Myset temp;
        LL temp2 = this->set;
        LL templ = a.set;
        void* tempo;

        while (!templ.isEmpty()) {
            tempo = templ.head->data;
            if (!IsMember(tempo)) {
                temp2.add(tempo);
            }
            templ.removeFirst();
        }
        temp.set = temp2;
        return temp;
    }

    Myset Intersection(Myset a) {
        Myset temp;
        LL temp2;
        LL templ = a.set;
        void* tempo;

        while (!templ.isEmpty()) {
            tempo = templ.head->data;
            if (IsMember(tempo)) {
                temp2.add(tempo);
            }
            templ.removeFirst();
        }
        temp.set = temp2;
        return temp;
    }

    void Delete(void* o) {
        if (IsMember(o)) {
            LL tset = this->set;
            LL temp;
            void* first = tset.head->data;

            while (first != o) {
                temp.add(tset.removeFirst());
                first = tset.head->data;
            }
            tset.removeFirst();
            Myset a, b;
            a.set = temp;
            b.set = tset;
            Myset c = a.Union(b);
            this->set = c.set;
        } else {
            cout << "Error!" << endl;
        }
    }
};

class MobilePhone {
public:
    int id;
    bool status;
    Exchange* base;

    MobilePhone(int number) : id(number), status(false), base(nullptr) {}

    bool getStatus() { return status; }

    void switchOn() { status = true; }

    void switchOff() { status = false; }

    Exchange* location() { return base; }
};

class MobilePhoneSet : public Myset {
public:
    bool IsMember2(int i) {
        Node* temp = set.head;
        while (temp != nullptr) {
            MobilePhone* x = static_cast<MobilePhone*>(temp->data);
            if (x->id == i) return true;
            temp = temp->next;
        }
        return false;
    }

    MobilePhone* id2mp(int i) {
        Node* temp = set.head;
        while (temp != nullptr) {
            MobilePhone* x = static_cast<MobilePhone*>(temp->data);
            if (x->id == i) return x;
            temp = temp->next;
        }
        return nullptr;
    }

    MobilePhone* removeFirst2() {
        if (IsEmpty()) return nullptr;
        return static_cast<MobilePhone*>(set.removeFirst());
    }
};

class ExchangeList : public LL {
public:
    Exchange* ithChild(int i) {
        Node* temp = head;
        while (i > 0) {
            temp = temp->next;
            i--;
        }
        return static_cast<Exchange*>(temp->data);
    }
};

class Exchange {
public:
    int eId;
    Exchange* parent;
    ExchangeList cList;
    MobilePhoneSet mpSet;

    Exchange(int number) : eId(number), parent(nullptr) {}

    int numChildren() { return cList.size; }

    Exchange* child(int i) { return cList.ithChild(i); }

    bool isRoot() { return eId == 0; }

    RoutingMapTree subtree(int i);
};

class RoutingMapTree {
public:
    Exchange* root;

    RoutingMapTree() { root = new Exchange(0); }

    bool containsNode(Exchange* a) {
        if (root != a && root->numChildren() == 0) return false;
        if (root == a) return true;
        for (int j = 0; j < root->numChildren(); j++) {
            if (containsNode((root->subtree(j)).root)) return true;
        }
        return false;
    }

    void switchOn(MobilePhone* a, Exchange* b) {
        if (!a->getStatus() && b->numChildren() == 0) {
            a->switchOn();
            a->base = b;
            b->mpSet.Insert(a);

            while (b->parent != nullptr) {
                b = b->parent;
                b->mpSet.Insert(a);
            }
        }
    }

    void switchOff(MobilePhone* a) {
        root->mpSet.Delete(a);

        for (int j = 0; j < root->numChildren(); j++) {
            RoutingMapTree temp;
            temp.root = root->child(j);

            if (temp.root->mpSet.IsMember(a)) {
                temp.switchOff(a);
                break;
            }
        }
    }

    void performAction(const string& actionMessage) {
        cout << actionMessage << endl;

        if (actionMessage[0] == 'a') {
            int i = 12;
            while (actionMessage[i] != ' ') i++;

            int a = stoi(actionMessage.substr(12, i - 12));
            int b = stoi(actionMessage.substr(i + 1));
            addExchange(a, b);
        } else if (actionMessage[7] == 'n') {
            int i = 15;
            while (actionMessage[i] != ' ') i++;

            int a = stoi(actionMessage.substr(15, i - 15));
            int b = stoi(actionMessage.substr(i + 1));
            switchOnMobile(a, b);
        } else if (actionMessage[7] == 'f') {
            int a = stoi(actionMessage.substr(16));
            switchOffMobile(a);
        } else if (actionMessage[5] == 'N') {
            int i = 14;
            while (actionMessage[i] != ' ') i++;

            int a = stoi(actionMessage.substr(14, i - 14));
            int b = stoi(actionMessage.substr(i + 1));
            queryNthChild(a, b);
        } else if (actionMessage[5] == 'M') {
            int a = stoi(actionMessage.substr(20));
            queryMobilePhoneSet(a);
        }
    }

    Exchange* id2ex(int a, Exchange* p) {
        if (p->eId == a) return p;

        if (p->numChildren() != 0) {
            for (int i = 0; i < p->numChildren(); i++) {
                Exchange* temp = id2ex(a, p->child(i));
                if (temp != nullptr) return temp;
            }
        }

        return nullptr;
    }

    void addExchange(int a, int b) {
        Exchange* A = id2ex(a, root);
        if (A == nullptr) return;

        Exchange* B = new Exchange(b);
        A->cList.add(B);
    }

    void switchOnMobile(int a, int b) {
        Exchange* B = id2ex(b, root);
        MobilePhone* A = new MobilePhone(a);
        switchOn(A, B);
    }

    void switchOffMobile(int a) {
        MobilePhone* A;
        if (root->mpSet.IsMember2(a)) {
            A = root->mpSet.id2mp(a);
        } else {
            A = new MobilePhone(a);
        }
        switchOff(A);
    }

    void queryNthChild(int a, int b) {
        Exchange* A = id2ex(a, root);
        if (A != nullptr) {
            cout << A->child(b)->eId << endl;
        }
    }

    void queryMobilePhoneSet(int a) {
        Exchange* A = id2ex(a, root);
        if (A != nullptr) {
            MobilePhoneSet& mps = A->mpSet;
            while (!mps.IsEmpty()) {
                cout << static_cast<MobilePhone*>(mps.removeFirst2())->id << endl;
            }
        }
    }
};

// Implementing subtree method outside to avoid circular dependency.
RoutingMapTree Exchange::subtree(int i) {
    RoutingMapTree sub;
    sub.root = child(i);
    return sub;
}

int main() {
    RoutingMapTree rmt;
    rmt.performAction("addExchange 0 1");
    rmt.performAction("addExchange 1 2");
    rmt.performAction("switchOnMobile 1 2");
    rmt.performAction("queryNthChild 1 0");

    return 0;
}








































































// // #include <iostream>
// // #include <unordered_map>
// // #include <vector>
// // #include <stdexcept>
// // using namespace std;

// // class MobilePhone;
// // class MobilePhoneSet;
// // class Exchange;

// // class MobilePhone {
// // private:
// //     int id;
// //     bool on;
// //     Exchange* location;

// // public:
// //     MobilePhone(int id) : id(id), on(false), location(nullptr) {}

// //     int getId() const {
// //         return id;
// //     }

// //     bool isOn() const {
// //         return on;
// //     }

// //     void switchOn() {
// //         on = true;
// //     }

// //     void switchOff() {
// //         on = false;
// //     }

// //     Exchange* getLocation() const {
// //         return location;
// //     }

// //     void setLocation(Exchange* location) {
// //         this->location = location;
// //     }
// // };

// // class MobilePhoneSet {
// // private:
// //     vector<MobilePhone*> phones;

// // public:
// //     void addPhone(MobilePhone* phone) {
// //         phones.push_back(phone);
// //     }

// //     void removePhone(MobilePhone* phone) {
// //         for (auto it = phones.begin(); it != phones.end(); ++it) {
// //             if (*it == phone) {
// //                 phones.erase(it);
// //                 break;
// //             }
// //         }
// //     }

// //     void printPhones() const {
// //         for (MobilePhone* phone : phones) {
// //             cout << phone->getId() << " ";
// //         }
// //         cout << endl;
// //     }
// // };

// // class Exchange {
// // private:
// //     int id;
// //     Exchange* parent;
// //     vector<Exchange*> children;
// //     MobilePhoneSet mobilePhoneSet;

// // public:
// //     Exchange(int id) : id(id), parent(nullptr) {}

// //     int getId() const {
// //         return id;
// //     }

// //     Exchange* getParent() const {
// //         return parent;
// //     }

// //     void setParent(Exchange* parent) {
// //         this->parent = parent;
// //     }

// //     void addChild(Exchange* child) {
// //         children.push_back(child);
// //         child->setParent(this);
// //     }

// //     vector<Exchange*>& getChildren() {
// //         return children;
// //     }

// //     MobilePhoneSet& getMobilePhoneSet() {
// //         return mobilePhoneSet;
// //     }

// //     Exchange* getNthChild(int n) {
// //         if (n < 0 || n >= children.size()) {
// //             throw out_of_range("Child index out of range");
// //         }
// //         return children[n];
// //     }

// //     bool containsExchange(Exchange* exchange) {
// //         if (this == exchange) return true;
// //         for (Exchange* child : children) {
// //             if (child->containsExchange(exchange)) return true;
// //         }
// //         return false;
// //     }
// // };

// // class RoutingMapTree {
// // private:
// //     Exchange* root;
// //     unordered_map<int, MobilePhone*> phoneMap;

// // public:
// //     RoutingMapTree() {
// //         root = new Exchange(0);
// //     }

// //     bool containsNode(Exchange* exchange) {
// //         return root->containsExchange(exchange);
// //     }

// //     void switchOn(MobilePhone* phone, Exchange* exchange) {
// //         if (!phone->isOn()) {
// //             phone->switchOn();
// //             phone->setLocation(exchange);
// //             exchange->getMobilePhoneSet().addPhone(phone);
// //             phoneMap[phone->getId()] = phone;
// //         } else {
// //             cout << "Phone is already on." << endl;
// //         }
// //     }

// //     void switchOff(MobilePhone* phone) {
// //         if (phone->isOn()) {
// //             phone->getLocation()->getMobilePhoneSet().removePhone(phone);
// //             phone->switchOff();
// //         } else {
// //             cout << "Phone is already off." << endl;
// //         }
// //     }

// //     void addExchange(int a, int b) {
// //         Exchange* exchangeA = findExchange(root, a);
// //         if (!exchangeA) {
// //             throw invalid_argument("Exchange with ID " + to_string(a) + " does not exist.");
// //         }
// //         Exchange* newExchangeB = new Exchange(b);
// //         exchangeA->addChild(newExchangeB);
// //     }

// //     void queryNthChild(int a, int b) {
// //         Exchange* exchangeA = findExchange(root, a);
// //         if (!exchangeA) {
// //             throw invalid_argument("Exchange with ID " + to_string(a) + " does not exist.");
// //         }
// //         try {
// //             Exchange* nthChild = exchangeA->getNthChild(b);
// //             cout << nthChild->getId() << endl;
// //         } catch (const out_of_range& e) {
// //             cout << e.what() << endl;
// //         }
// //     }

// //     void queryMobilePhoneSet(int a) {
// //         Exchange* exchangeA = findExchange(root, a);
// //         if (!exchangeA) {
// //             throw invalid_argument("Exchange with ID " + to_string(a) + " does not exist.");
// //         }
// //         exchangeA->getMobilePhoneSet().printPhones();
// //     }

// //     void performAction(string actionMessage) {
// //         vector<string> parts = split(actionMessage, ' ');
// //         string action = parts[0];

// //         try {
// //             if (action == "addExchange") {
// //                 int a = stoi(parts[1]);
// //                 int b = stoi(parts[2]);
// //                 addExchange(a, b);
// //             } else if (action == "switchOnMobile") {
// //                 int mobileId = stoi(parts[1]);
// //                 int exchangeId = stoi(parts[2]);
// //                 MobilePhone* phone = phoneMap.count(mobileId) ? phoneMap[mobileId] : new MobilePhone(mobileId);
// //                 Exchange* exchange = findExchange(root, exchangeId);
// //                 if (!exchange) {
// //                     throw invalid_argument("Exchange with ID " + to_string(exchangeId) + " does not exist.");
// //                 }
// //                 switchOn(phone, exchange);
// //             } else if (action == "switchOffMobile") {
// //                 int switchOffMobileId = stoi(parts[1]);
// //                 if (!phoneMap.count(switchOffMobileId)) {
// //                     throw invalid_argument("MobilePhone with ID " + to_string(switchOffMobileId) + " does not exist.");
// //                 }
// //                 switchOff(phoneMap[switchOffMobileId]);
// //             } else if (action == "queryNthChild") {
// //                 int a = stoi(parts[1]);
// //                 int b = stoi(parts[2]);
// //                 queryNthChild(a, b);
// //             } else if (action == "queryMobilePhoneSet") {
// //                 int a = stoi(parts[1]);
// //                 queryMobilePhoneSet(a);
// //             } else {
// //                 cout << "Invalid action." << endl;
// //             }
// //         } catch (const exception& e) {
// //             cout << e.what() << endl;
// //         }
// //     }

// // private:
// //     Exchange* findExchange(Exchange* root, int id) {
// //         if (root->getId() == id) {
// //             return root;
// //         }
// //         for (Exchange* child : root->getChildren()) {
// //             Exchange* result = findExchange(child, id);
// //             if (result) {
// //                 return result;
// //             }
// //         }
// //         return nullptr;
// //     }

// //     vector<string> split(const string& str, char delimiter) {
// //         vector<string> tokens;
// //         size_t start = 0;
// //         size_t end = str.find(delimiter);
// //         while (end != string::npos) {
// //             tokens.push_back(str.substr(start, end - start));
// //             start = end + 1;
// //             end = str.find(delimiter, start);
// //         }
// //         tokens.push_back(str.substr(start));
// //         return tokens;
// //     }
// // };

// // int main() {
// //     RoutingMapTree tree;
// //     tree.performAction("addExchange 0 1");
// //     tree.performAction("addExchange 0 2");
// //     tree.performAction("switchOnMobile 123 1");
// //     tree.performAction("switchOffMobile 123");
// //     tree.performAction("queryNthChild 0 1");
// //     tree.performAction("queryMobilePhoneSet 0");

// //     return 0;
// // }









// #include <iostream>
// #include <string>
// #include <unordered_map>
// #include <list>
// #include <stdexcept>

// using namespace std;

// class Exchange;
// class MobilePhoneSet;
// class MobilePhone;

// class Node {
// public:
//     void* data;
//     Node* next;

//     Node(void* d, Node* n) : data(d), next(n) {}
// };

// class LL {
// public:
//     Node* head;
//     int size;

//     LL() : head(nullptr), size(0) {}

//     bool isEmpty() { return size == 0; }

//     void* headData() {
//         if (isEmpty()) return nullptr;
//         return head->data;
//     }

//     void add(void* d) {
//         head = new Node(d, head);
//         size++;
//     }

//     void* removeFirst() {
//         if (isEmpty()) return nullptr;
//         void* temp = head->data;
//         head = head->next;
//         size--;
//         return temp;
//     }
// };

// class Myset {
// public:
//     LL set;

//     bool IsEmpty() { return set.isEmpty(); }

//     bool IsMember(void* o) {
//         Node* temp = set.head;
//         while (temp != nullptr) {
//             if (temp->data == o) return true;
//             temp = temp->next;
//         }
//         return false;
//     }

//     void Insert(void* o) {
//         if (!IsMember(o)) set.add(o);
//     }

//     Myset Union(Myset a) {
//         Myset temp;
//         LL temp2 = this->set;
//         LL templ = a.set;
//         void* tempo;

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

//     Myset Intersection(Myset a) {
//         Myset temp;
//         LL temp2;
//         LL templ = a.set;
//         void* tempo;

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

//     void Delete(void* o) {
//         if (IsMember(o)) {
//             LL tset = this->set;
//             LL temp;
//             void* first = tset.head->data;

//             while (first != o) {
//                 temp.add(tset.removeFirst());
//                 first = tset.head->data;
//             }
//             tset.removeFirst();
//             Myset a, b;
//             a.set = temp;
//             b.set = tset;
//             Myset c = a.Union(b);
//             this->set = c.set;
//         } else {
//             cout << "Error!" << endl;
//         }
//     }
// };

// class MobilePhone {
// public:
//     int id;
//     bool status;
//     Exchange* base;

//     MobilePhone(int number) : id(number), status(false), base(nullptr) {}

//     bool getStatus() { return status; }

//     void switchOn() { status = true; }

//     void switchOff() { status = false; }

//     Exchange* location() { return base; }
// };

// class ExchangeList : public LL {
// public:
//     Exchange* ithChild(int i) {
//         Node* temp = head;
//         while (i > 0) {
//             temp = temp->next;
//             i--;
//         }
//         return static_cast<Exchange*>(temp->data);
//     }
// };

// class MobilePhoneSet : public Myset {
// public:
//     bool IsMember2(int i) {
//         Node* temp = set.head;
//         while (temp != nullptr) {
//             MobilePhone* x = static_cast<MobilePhone*>(temp->data);
//             if (x->id == i) return true;
//             temp = temp->next;
//         }
//         return false;
//     }

//     MobilePhone* id2mp(int i) {
//         Node* temp = set.head;
//         while (temp != nullptr) {
//             MobilePhone* x = static_cast<MobilePhone*>(temp->data);
//             if (x->id == i) return x;
//             temp = temp->next;
//         }
//         return nullptr;
//     }

//     MobilePhone* removeFirst2() {
//         if (IsEmpty()) return nullptr;
//         return static_cast<MobilePhone*>(set.removeFirst());
//     }
// };

// class Exchange {
// public:
//     int eId;
//     Exchange* parent;
//     ExchangeList cList;
//     MobilePhoneSet mpSet;

//     Exchange(int number) : eId(number), parent(nullptr) {}

//     int numChildren() { return cList.size; }

//     Exchange* child(int i) { return cList.ithChild(cList.size - i - 1); }

//     bool isRoot() { return eId == 0; }

//     RoutingMapTree subtree(int i);

//     MobilePhoneSet residentSet() { return mpSet; }
// };

// class RoutingMapTree {
// public:
//     Exchange* root;

//     RoutingMapTree() {
//         root = new Exchange(0);
//     }

//     bool containsNode(Exchange* a) {
//         if (root != a && root->numChildren() == 0) return false;
//         if (root == a) return true;

//         for (int j = 0; j < root->numChildren(); j++) {
//             if (containsNode(root->child(j))) return true;
//         }
//         return false;
//     }

//     void switchOn(MobilePhone* a, Exchange* b) {
//         if (!a->getStatus() && b->numChildren() == 0) {
//             a->switchOn();
//             a->base = b;
//             b->mpSet.Insert(a);

//             while (b->parent != nullptr) {
//                 b = b->parent;
//                 b->mpSet.Insert(a);
//             }
//         }
//     }

//     void switchOff(MobilePhone* a) {
//         root->mpSet.Delete(a);

//         for (int j = 0; j < root->numChildren(); j++) {
//             RoutingMapTree temp;
//             temp.root = root->child(j);

//             if (temp.root->mpSet.IsMember(a)) {
//                 temp.switchOff(a);
//                 break;
//             }
//         }
//     }

//     void performAction(const string& actionMessage) {
//         cout << actionMessage << endl;

//         if (actionMessage[0] == 'a') {
//             int i = 12;
//             while (actionMessage[i] != ' ') i++;

//             int a = stoi(actionMessage.substr(12, i - 12));
//             int b = stoi(actionMessage.substr(i + 1));
//             addExchange(a, b);
//         } else if (actionMessage[7] == 'n') {
//             int i = 15;
//             while (actionMessage[i] != ' ') i++;

//             int a = stoi(actionMessage.substr(15, i - 15));
//             int b = stoi(actionMessage.substr(i + 1));
//             switchOnMobile(a, b);
//         } else if (actionMessage[7] == 'f') {
//             int a = stoi(actionMessage.substr(16));
//             switchOffMobile(a);
//         } else if (actionMessage[5] == 'N') {
//             int i = 14;
//             while (actionMessage[i] != ' ') i++;

//             int a = stoi(actionMessage.substr(14, i - 14));
//             int b = stoi(actionMessage.substr(i + 1));
//             queryNthChild(a, b);
//         } else if (actionMessage[5] == 'M') {
//             int a = stoi(actionMessage.substr(20));
//             queryMobilePhoneSet(a);
//         }
//     }

//     Exchange* id2ex(int a, Exchange* p) {
//         if (p->eId == a) return p;

//         if (p->numChildren() != 0) {
//             for (int i = 0; i < p->numChildren(); i++) {
//                 Exchange* temp = id2ex(a, p->child(i));
//                 if (temp != nullptr) return temp;
//             }
//         }

//         return nullptr;
//     }

//     void addExchange(int a, int b) {
//         Exchange* A = id2ex(a, root);
//         if (A == nullptr) return;

//         Exchange* B = new Exchange(b);
//         A->cList.add(B);
//     }

//     void switchOnMobile(int a, int b) {
//         Exchange* B = id2ex(b, root);
//         MobilePhone* A = new MobilePhone(a);
//         switchOn(A, B);
//     }

//     void switchOffMobile(int a) {
//         MobilePhone* A;
//         if (root->mpSet.IsMember2(a)) {
//             A = root->mpSet.id2mp(a);
//         } else {
//             A = new MobilePhone(a);
//         }
//         switchOff(A);
//     }

//     void queryNthChild(int a, int b) {
//         Exchange* A = id2ex(a, root);
//         if (A != nullptr) {
//             cout << A->child(b)->eId << endl;
//         }
//     }

//     void queryMobilePhoneSet(int a) {
//         Exchange* A = id2ex(a, root);
//         if (A != nullptr) {
//             MobilePhoneSet& mps = A->mpSet;
//             while (!mps.IsEmpty()) {
//                 cout << static_cast<MobilePhone*>(mps.removeFirst2())->id << endl;
//             }
//         }
//     }
// };

// // Implementing subtree method outside to avoid circular dependency.
// RoutingMapTree Exchange::subtree(int i) {
//     RoutingMapTree sub;
//     sub.root = child(i);
//     return sub;
// }

// int main() {
//     RoutingMapTree rmt;
//     rmt.performAction("addExchange 0 1");
//     rmt.performAction("addExchange 1 2");
//     rmt.performAction("switchOnMobile 1 2");
//     rmt.performAction("queryNthChild 1 0");
//     return 0;
// }
