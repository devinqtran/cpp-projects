#pragma once
#include <stdio.h>
#include <tchar.h>

class Bulb;

enum TStates
{
    On,
    Off,
    Broken
};

// class Bulb
typedef void (Bulb::*CBP)(); // call-back
typedef bool (Bulb::*GP)();  //

/*
class Weapon;

typedef void(Weapon::*CBP)(); // call-back
typedef bool(Weapon::*GP)(); //

enum TStates { Empty, Reload, Loaded, Firing};
*/