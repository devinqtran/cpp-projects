#include <stack>

class MyQueue
{
private:
    std::stack<int> s;
    std::stack<int> t; // temporary stack

public:
    MyQueue()
    {
    }

    void push(int x)
    {
        // Move everything from s to t
        while (!s.empty())
        {
            t.push(s.top()); // push top element of s to t
            s.pop();         // remove top element
        }

        // push the new element to the back of s now that s is empty
        s.push(x);

        // copy back to s
        while (!t.empty())
        {
            s.push(t.top());
            t.pop();
        }
    }

    int pop()
    {
        int f = s.top();
        s.pop();
        return f;
    }

    int peek()
    {
        int f = s.top();
        return f;
    }

    bool empty()
    {
        if (!s.empty())
            return false;
        return true;
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */