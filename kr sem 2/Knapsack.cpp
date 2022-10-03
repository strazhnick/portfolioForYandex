#include "Knapsack.h"

using namespace std;

void traceResult(int **dp, int *w, int *c, int n, int s, LinkedList<int> &ind, LinkedList<int> &away) {
    if (dp[n][s] == 0) {
        return;
    }
    if (dp[n - 1][s] == dp[n][s]) {
        traceResult(dp, w, c, n - 1, s, ind, away);
    } else {
        traceResult(dp, w, c, n - 1, s - w[n-1], ind, away);
        away.add(w[n-1]);
        ind.add(n-1);
    }
}

void calc(int *w, int*c, int n, int s, LinkedList<int> &ind, LinkedList<int> &away) {
    int **dp = new int *[n + 1];
    for (int i = 0; i < n + 1; i++) {
        dp[i] = new int[s + 1];
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= s; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else {
                if (j >= w[i-1]) {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i-1]] + c[i-1]);
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
    }
    traceResult(dp, w, c, n, s, ind, away);
    for (int i = 0; i < n + 1; i++) {
        delete[] dp[i];
    }
    delete[] dp;
    //return dp[n][s];
}