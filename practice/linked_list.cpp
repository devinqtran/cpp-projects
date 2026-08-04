#include <iostream>

// Definition of a Node
struct Node
{
    int data;
    Node *next;

    // Constructor to initialize data and next pointer
    Node(int val) : data(val), next(nullptr) {}
};

// LinkedList Class encapsulating operations
class LinkedList
{
private:
    Node *head; // Points to the first node

public:
    LinkedList() : head(nullptr) {}

    // 1. Insert a new node at the front
    void insertAtFront(int val)
    {
        Node *newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    // 2. Insert a new node at the end
    void insertAtEnd(int val)
    {
        Node *newNode = new Node(val);
        if (head == nullptr)
        {
            head = newNode;
            return;
        }
        Node *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // 3. Delete a node by value
    void deleteValue(int val)
    {
        if (head == nullptr)
            return;

        // If head node holds the value
        if (head->data == val)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node *temp = head;
        while (temp->next != nullptr && temp->next->data != val)
        {
            temp = temp->next;
        }

        // Value found, reconnect pointers and free memory
        if (temp->next != nullptr)
        {
            Node *toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
        }
    }

    // 4. Traverse and print the list
    void printList()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "NULL\n";
    }

    // Destructor to clean up memory
    ~LinkedList()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            Node *nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
};

int main()
{
    LinkedList list;

    list.insertAtEnd(40);
    list.insertAtEnd(30);
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtFront(5); // List: 5 -> 10 -> 20 -> NULL

    std::cout << "Original List: ";
    list.printList();

    list.deleteValue(10); // List: 5 -> 20 -> NULL
    std::cout << "After Deleting 10: ";
    list.printList();

    return 0;
}