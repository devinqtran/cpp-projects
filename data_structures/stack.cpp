#include <iostream>
#include <queue>

class MyStack
{
private:
    std::queue<int> q;

public:
    MyStack()
    {
    }

    // push element to the front (usually queue push puts at back)
    void push(int x)
    {
        q.push(x); // push x to the front
        for (int i = 0; i < q.size() - 1; i++)
        {                      // iterate through entire queue
            q.push(q.front()); // push the value at the front to the back
            q.pop();           // remove the front value
        }
    }

    // remove element on top of stack
    int pop()
    {
        int t = q.front();
        q.pop();
        return t;
    }

    int top()
    {
        int f = q.front();
        return f;
    }

    bool empty()
    {
        if (!q.empty())
            return false;
        return true;
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */