#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

// adds new node at the front of list
void insertAtHead(Node*& head, int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = head;
    head = newNode;
    cout << value << " inserted at head." << endl;
}

// puts new node at 3rd spot in list
void insertAtThird(Node*& head, int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;

    // if less than 2 nodes so we put it at end instead
    if (head == nullptr) {
        cout << "List has fewer than 2 nodes. Inserting at the end instead." << endl;
        head = newNode;
        return;
    }
    if (head->next == nullptr) {
        cout << "List has fewer than 2 nodes. Inserting at the end instead." << endl;
        head->next = newNode;
        return;
    }

    // walk to 2nd node, then insert right after it
    Node* second = head->next;
    newNode->next = second->next;
    second->next = newNode;
    cout << value << " inserted at 3rd position." << endl;
}

// prints out the whole list
void displayList(Node* head) {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

// removes last node in the list
void deleteLast(Node*& head) {
    if (head == nullptr) {
        cout << "List is empty. Nothing to delete." << endl;
        return;
    }
    if (head->next == nullptr) {
        // only one node, so deleting it empties list
        delete head;
        head = nullptr;
        cout << "Only node deleted. List is now empty." << endl;
        return;
    }
    // go until we're one before the last node
    Node* temp = head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
    cout << "Last node deleted." << endl;
}

// counts how many nodes are in the list
int countNodes(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

// flips list around
void reverseList(Node*& head) {
    Node* prev = nullptr;
    Node* curr = head;
    Node* next = nullptr;

    while (curr != nullptr) {
        next = curr->next;   // hold onto next node before we lose it
        curr->next = prev;   // point backwards instead of forwards
        prev = curr;         // shift prev up
        curr = next;         // shift curr up
    }
    head = prev;   // prev ends up being the new head
    cout << "List reversed." << endl;
}

// looks for a value
void searchValue(Node* head, int value) {
    Node* temp = head;
    int position = 0;
    while (temp != nullptr) {
        if (temp->data == value) {
            cout << value << " found at position " << position << "." << endl;
            return;
        }
        temp = temp->next;
        position++;
    }
    cout << value << " not found in the list." << endl;
}

// clears out whatever's left in list before we quit
void destroyList(Node*& head) {
    Node* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* head = nullptr;
    int choice, value;

    do {
        cout << "\n----- Singly Linked List Menu -----" << endl;
        cout << "1. Insert at Head" << endl;
        cout << "2. Insert at 3rd Position" << endl;
        cout << "3. Display List" << endl;
        cout << "4. Delete Last Node" << endl;
        cout << "5. Count Nodes" << endl;
        cout << "6. Reverse List" << endl;
        cout << "7. Search Value" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert at head: ";
                cin >> value;
                insertAtHead(head, value);
                break;
            case 2:
                cout << "Enter value to insert at 3rd position: ";
                cin >> value;
                insertAtThird(head, value);
                break;
            case 3:
                displayList(head);
                break;
            case 4:
                deleteLast(head);
                break;
            case 5:
                cout << "Number of nodes: " << countNodes(head) << endl;
                break;
            case 6:
                reverseList(head);
                displayList(head);
                break;
            case 7:
                cout << "Enter value to search: ";
                cin >> value;
                searchValue(head, value);
                break;
            case 8:
                cout << "Exiting" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 8);

    destroyList(head);   // free everything before we exit
    return 0;
}