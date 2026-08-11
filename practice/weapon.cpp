#include <iostream>
#include <string>

// Enumerate the possible states
enum States
{
    inactive,
    loaded,
    firing,
    reload
};

// Set current state to inactive
States currentState = inactive;

class Gun
{
private:
    int ammo;
    float caliber;
    bool mounted;
    std::string category;
    States state;

public:
    Gun() : ammo(0), caliber(0.0f), mounted(false), category(""), state(inactive) {};
    Gun(int a, float cal, bool m, std::string cat, States s) : ammo(a), caliber(cal), mounted(m), category(cat), state(s) {};

    // If statements to check the current state and implement transitions
    void updateState()
    {
        if (state == inactive && mounted)
            state = loaded;
        else if (state == loaded && ammo > 0)
            state = firing;
        else if (state == loaded && !mounted)
            state = inactive;
        else if (state == firing && ammo == 0)
            state = reload;
        else if (state == reload && ammo > 0)
            state = loaded;
    }

    void onFire()
    {
        ammo--;
    }

    // Getter for state
    States getState() const
    {
        return state;
    }

    int getAmmo() const
    {
        return ammo;
    }
};

int main()
{
    Gun glock17(17, .9, true, "handgun", loaded);
    std::cout << glock17.getState() << "\n";
    std::cout << glock17.getAmmo() << "\n";
    glock17.onFire();
    std::cout << glock17.getAmmo() << "\n";

    return 0;
}
