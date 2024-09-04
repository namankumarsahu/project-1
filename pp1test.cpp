#include <iostream>

class LL;

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
        Node* oldHead = head;
        head = head->next;
        delete oldHead;
        size--;
        return temp;
    }

    bool contains(void* d) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == d) return true;
            temp = temp->next;
        }
        return false;
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

    Myset Union(const Myset& a) {
        Myset temp;
        LL temp2 = set;
        LL templ = a.set;
        while (!templ.isEmpty()) {
            void* tempo = templ.headData();
            if (!IsMember(tempo)) temp2.add(tempo);
            templ.removeFirst();
        }
        temp.set = temp2;
        return temp;
    }

    Myset Intersection(const Myset& a) {
        Myset temp;
        LL temp2;
        LL templ = a.set;
        while (!templ.isEmpty()) {
            void* tempo = templ.headData();
            if (IsMember(tempo)) temp2.add(tempo);
            templ.removeFirst();
        }
        temp.set = temp2;
        return temp;
    }

    void Delete(void* o) {
        if (IsMember(o)) {
            LL tset = set;
            LL temp;
            void* first = tset.headData();
            while (first != o) {
                temp.add(tset.removeFirst());
                first = tset.headData();
            }
            tset.removeFirst();
            Myset a;
            Myset b;
            a.set = temp;
            b.set = tset;
            Myset c = a.Union(b);
            set = c.set;
        } else {
            std::cout << "Error!" << std::endl;
        }
    }
};

int main() {
    // Testing Myset
    Myset x;
    int val1 = 11, val2 = 12, val3 = 13, val4 = 15, val5 = 17;
    x.Insert(&val1);
    x.Insert(&val2);
    x.Insert(&val3);
    x.Insert(&val4);
    x.Insert(&val5);
    std::cout << "x.size: " << x.set.size << std::endl;
    std::cout << "x.first: " << *(int*)x.set.headData() << std::endl;

    Myset y;
    int val6 = 13, val7 = 14, val8 = 15, val9 = 16;
    y.Insert(&val6);
    y.Insert(&val7);
    y.Insert(&val8);
    y.Insert(&val9);

    Myset z = x.Union(y);
    z.Delete(&val8);
    z.Delete(&val7);
    z.Delete(&val7); // 10 not present, should display "Error!"

    std::cout << "z.size: " << z.set.size << std::endl;
    Node* node = z.set.head;
    for (int i = 0; i < 5 && node != nullptr; i++) {
        std::cout << "z.head.next: " << *(int*)node->data << std::endl;
        node = node->next;
    }

    // Testing LL
    LL ll;
    std::cout << "ll.headData(): " << (ll.headData() ? *(int*)ll.headData() : 0) << std::endl;
    int val10 = 2, val11 = 3, val12 = 4;
    ll.add(&val10);
    std::cout << "ll.headData() after adding 2: " << *(int*)ll.headData() << std::endl;
    ll.add(&val11);
    ll.add(&val12);
    std::cout << "ll.headData() after adding 3 and 4: " << *(int*)ll.headData() << std::endl;
    std::cout << "ll.size: " << ll.size << std::endl;
    ll.removeFirst();
    std::cout << "ll.headData() after removing first: " << (ll.headData() ? *(int*)ll.headData() : 0) << std::endl;
    std::cout << "ll.size after removing first: " << ll.size << std::endl;

    // Print entire list
    Node* temp = ll.head;
    while (temp != nullptr) {
        std::cout << "List item: " << *(int*)temp->data << std::endl;
        temp = temp->next;
    }

    return 0;
}
