#pragma once
#include "stdafx.h"

class State;
class Bulb;

class Transition {
public:
    // pointers to the from state, to state, and guard location
    State* fromState;
    GP guardFunction;
    Bulb* guardLocation;
    Transition* next;
    State* toState;

    // Non-default constructor, initializes pointers
    Transition(State* from, State* to, GP guardFunction, Bulb *guardLocation) {
        this->fromState = from;
        this->toState = to;
        this->guardFunction = guardFunction;
        this->guardLocation = guardLocation;
        this->next = nullptr;
    }

    // InvokeGuard checks for function pointer and calls that function
    bool InvokeGuard() {
        if(guardFunction != 0 && guardLocation != 0) {
            return (guardLocation->*guardFunction)();
        }
        return false;
    }

    // Getter for toState
    State* GetToState() {
        return toState;
    }


};