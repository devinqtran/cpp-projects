#pragma once
#include <iostream>
#include "LinkedList.h"
#include "stdafx.h"
#include "FSM.h"
#include "Transition.h"

class Bulb
{
public:
    // pointer to fsm and int voltage
    FSM *fsm;
    int voltage;

    Bulb()
    {
        voltage = 240;
        fsm = new FSM();
        fsm->AddState(new State(On, &Bulb::OnOn, this));
        fsm->AddState(new State(Off, &Bulb::OnOff, this));
        fsm->AddState(new State(Broken, &Bulb::OnBroken, this));

        fsm->AddTransition(On, Off, &Bulb::GuardOnToOff, this);
        fsm->AddTransition(On, Broken, &Bulb::GuardOnToBroken, this);
        fsm->AddTransition(Off, Broken, &Bulb::GuardOffToBroken, this);
        fsm->AddTransition(Off, On, &Bulb::GuardOffToOn, this);
    }

    // Destructor
    ~Bulb()
    {
        delete fsm;
    }

    // Methods for printing state
    void OnOn()
    {
        std::cout << "OnOn\n";
    }

    void OnOff()
    {
        std::cout << "OnOff\n";
    }

    void OnBroken()
    {
        std::cout << "OnBroken\n";
    }

    // Guards to check voltage values
    bool GuardOnToOff()
    {
        return voltage == 0;
    }

    bool GuardOnToBroken()
    {
        return voltage > 300;
    }

    bool GuardOffToBroken()
    {
        return voltage > 300;
    }

    bool GuardOffToOn()
    {
        return voltage >= 240;
    }

    // Call to update fsm
    void Update()
    {
        fsm->Check();
    }
};