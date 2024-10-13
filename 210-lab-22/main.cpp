// 210 | lab 22 | Neil Orton
// IDE used: Xcode
#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;    // Return if empty list
        
        Node* temp = head;
        while (temp && temp->data != value)    // Moves to position based on val
            temp = temp->next;
    
        if (!temp) {    // Value not found
            cout << "Value not found" << endl;
            return;
        }

        if (temp->prev) {
            temp->prev->next = temp->next;    // adjusts list to isolate node to be deleted
        } else {
            head = temp->next;    // deletes head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;    // adjusts list to isolate node to be deleted
        } else {
            tail = temp->prev; // deletes tail
        }
        
        delete temp;    // node deleted
    }

    void delete_pos(int pos) {
        if (!head) return;    // return if empty list

        Node* temp = head;
        
        for (int i = 0; i < pos - 1; i++) {    // Moves to location based on pos
            temp = temp->next;
            if (!temp) {
                cout << "Position not found" << endl;
                return; // Value not found
            }
        }

        if (temp->prev) {
            temp->prev->next = temp->next;    // adjusts list to isolate node to be deleted
        } else {
            head = temp->next;    // sets head to one position ahead
            head->prev = nullptr;    // assigns head prev to nullptr
        }

        if (temp->next) {
            temp->next->prev = temp->prev;    // adjusts list to isolate node to be deleted
        } else {
            tail = temp->prev;    // sets tail to one position previous
            tail->next = nullptr;   // assigns head next to nullptr
        }
        
        delete temp;    // deletes node
    }

    void pop_front() {
        if (!head) return;    // return if empty list

        Node* temp = head;
        
        head = temp->next;    // sets head to one position ahead
        head->prev = nullptr;    // assigns head prev to nullptr
        
        delete temp;    // deletes node
    }

    void pop_back() {
        if (!head) return;    // return if empty list

        Node* temp = tail;
        
        tail = temp->prev;    // sets tail to one position previous
        tail->next = nullptr;   // assigns head next to nullptr
        
        delete temp;    // deletes node
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    int pos;
    int val;
    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();
    
    cout << "Which value should be deleted?: ";    //user prompted to enter which value they want to remove
    cin >> val;
    list.delete_val(val);
    cout << "Updated List: ";
    list.print();
    
    //user prompted to enter which position they want to remove
    cout << "Which position should be deleted? Enter a whole number no less than 1: ";
    cin >> pos;
    while(pos < 1 || cin.fail()) {
        cout << "Enter a whole number no less than 1: ";
        cin.clear();
        cin.ignore(50, '\n');
        cin >> pos;
    }
    list.delete_pos(pos);
    
    cout << "Popping the back..." << endl;    // pop back function call
    list.pop_back();
    cout << "Popping the front..." << endl;    // pop front function call
    list.pop_front();
    
    cout << "Updated List: ";
    list.print();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();
    

    return 0;
}
