#pragma once
#include "Bulb.h"
#include "stdafx.h"
#include "Transition.h"
#include "LinkedList.h"

class State {
public:
    CBP callBack;
    Bulb* callBackLocation;
    State* next; // Pointer of type State named next
    TStates state;
    LinkedList<Transition>* transitions;

    // Two non-default constructors
    State(TStates state) {
        this->state = state;
    }

    State(TStates state, CBP callBack, Bulb * callBackLocation) {
        this->state = state;
        this->callBack = callBack;
        this->callBackLocation = callBackLocation;
        transitions = new LinkedList<Transition>();
        next = 0;
    }

    // Two overloaded operators
    bool operator != (State& rhd) {
        return (this->state != rhd.state);
    }

    bool operator == (State& rhd) {
        return (this->state == rhd.state);
    }

    // Method for adding transition into state
    void AddTransition(State* from, State* to, GP guard, Bulb * guardLocation) {
        transitions->Insert(new Transition(from, to, guard, guardLocation));
    }

    void InvokeCallBack() {
        (callBackLocation->*callBack)();
    }

    // CheckGuards takes a boolean pointer named changed (checks t/f) if there has been change
    State* CheckGuards(bool* changed) {
        for (int n = 0; n < transitions->size(); n++) {
            if((*transitions)[n]->InvokeGuard()) {
                *changed = true;
                return (*transitions)[n]->GetToState();
            }
        }
        return 0;
    }

};