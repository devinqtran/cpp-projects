#pragma once
#include "State.h"

class FSM
{
public:
    // Pointer to currentState
    State *currentState;
    LinkedList<State *> *states;

    // Constructor initializes linked list and current state
    FSM(void)
    {
        states = new LinkedList<State *>();
        currentState = 0;
    }

    // Getter for getting currentState
    State *GetCurrentState()
    {
        return currentState;
    }

    // Add a state
    void AddState(State *state)
    {
        if (states->IsEmpty())
        {
            currentState = state;
            currentState->InvokeCallBack();
            states->Insert(state);
        }
        else
        {
            if (!states->Find(state))
            {
                states->Insert(state);
            }
            else
            {
                std::cout << "The state has already been added\n";
            }
        }
    }

    // Helper method to find a state strictly by its TStates enum
    State *FindStateByID(TStates targetEnum)
    {
        // Utilizing the Iterator from the LinkedList
        for (State *s : *states)
        {
            if (s != nullptr && s->state == targetEnum)
            {
                return s;
            }
        }
        return nullptr;
    }

    // Update FSM::AddTransition to use it
    void AddTransition(TStates from, TStates to, GP guardFunction, Bulb* guardLocation) {
        State* foundState = FindStateByID(from);
        State* toState = FindStateByID(to);
        
        if (foundState != nullptr && toState != nullptr) {
            foundState->AddTransition(foundState, toState, guardFunction, guardLocation);
        }
        else {
            std::cout << "ERROR: Could not attach transition. State missing.\n";
        }
    }

    void Check()
    {
        bool changed = false;
        State *toState = currentState->CheckGuards(&changed);
        // If a guard has been met
        if (changed)
        {
            currentState = toState;
            currentState->InvokeCallBack();
        }
    }
};