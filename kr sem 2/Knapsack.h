#pragma once
#include <iostream>
#include "LinkedList.h"
#include <fstream>

void traceResult(int **dp, int *w, int *c, int n, int s, LinkedList<int> &ind, LinkedList<int> &away);

void calc(int *w, int *c, int n, int s, LinkedList<int> &ind, LinkedList<int> &away);