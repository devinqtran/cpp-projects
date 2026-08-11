#pragma once

template <typename T>
class LinkedList
{
public:
    // Define the node structure
    struct Node
    {
        T data;
        Node *next;

        Node(const T &data) : data(data), next(nullptr) {}
    };

private:
    Node *head;
    Node *tail;
    int count;

public:
    // Constructor
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}

    // Destructor to ensure proper memory management
    ~LinkedList()
    {
        clear();
    }

    // Add a new element to the end of the list
    void append(const T &value)
    {
        Node *newNode = new Node(value);
        if (!head)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    // Method to insert
    // Add a new element to the end of the list
    void Insert(const T &value)
    {
        Node *newNode = new Node(value);
        if (!head)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    // Free all nodes to prevent memory leaks
    void clear()
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
        count = 0;
    }

    // Returns the size of the list
    int size() const
    {
        return count;
    }

    // --- Iteration Methods ---

    // Option 1: Manual traversal
    Node *getHead() const
    {
        return head;
    }

    // Option 2: Custom Iterator for range-based for loops
    class Iterator
    {
    private:
        Node *current;

    public:
        Iterator(Node *node) : current(node) {}

        // Overload dereference to return the data
        T &operator*() { return current->data; }

        // Overload pre-increment to move to the next node
        Iterator &operator++()
        {
            if (current)
                current = current->next;
            return *this;
        }

        // Overload inequality to check for the end of the list
        bool operator!=(const Iterator &other) const
        {
            return current != other.current;
        }
    };

    // Begin and end methods required for range-based loops
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};