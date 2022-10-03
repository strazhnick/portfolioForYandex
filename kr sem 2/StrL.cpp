#include "StrL.h"

using namespace std;

StrL::StrL(string s) {
    arr = new char[s.length() + 1];
    strcpy(arr, s.c_str());
    len = s.length();
}

StrL::StrL() {

}

int StrL::compareStrl(StrL s) {
    for (int i = 0; i < min(len, s.len); i++) {
        if (arr[i] < s.arr[i]) {
            return -1;
        }
        if (arr[i] > s.arr[i]) {
            return 1;
        }
    }
    if (len < s.len) {
        return -1;
    }
    if (len > s.len) {
        return 1;
    }
    return 0;
}