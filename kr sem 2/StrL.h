#pragma once

#include <string>
#include <iostream>

using namespace std;

struct StrL {
    char *arr;
    int len;

    StrL(string s);

    StrL();

    int compareStrl(StrL s);
};

