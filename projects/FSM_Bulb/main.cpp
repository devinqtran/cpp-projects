#include <iostream>
#include "Bulb.h"
#include "FSM.h"
#include "stdafx.h"
#include "LinkedList.h"
#include "Transition.h"
#include "State.h"

using namespace std;

int main()
{
    cout << "====== State Machines ======\n";
    cout << "====== Example ======\n";

    Bulb *bulb = new Bulb();
    bulb->Update();
    bulb->voltage = 0;
    bulb->Update();
    bulb->voltage = 240;
    bulb->Update();
    bulb->voltage = 500;
    bulb->Update();
    system("pause");
}