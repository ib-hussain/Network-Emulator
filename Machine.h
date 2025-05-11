#ifndef MACHINE_H
#define MACHINE_H
#include "BaseLibrariesFile.h"

struct Machine{
    const String name;
    const long long int ID;
    Machine(const String& namei = NULLstring):name(namei), ID(++global_ID_declare){}
    // needs to be made better
};

#endif