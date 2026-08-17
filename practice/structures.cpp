#include <iostream>

struct address {
    char* name;
    long number;
    char* street;
    char* town;
    char state[2]; // "MD"
    int zip;
};

void printAddress(address* p) {
    std::cout << p->name << "\n"
         << p->number << "\n";
}

int main () {
    address dt;
    dt.name = "Devin Tran";
    dt.number = 301;
    dt.street = "255 S University Ave";
    
    address mp = {
        "Marieanne Paniagua", 255, "South University Ave"
    };

    printAddress(&dt); // use the & to access the address at dt
    printAddress(&mp);



    return 0;
}