#include "fibo.h"

#include <bits/stdc++.h>

using namespace std;

int main() {
    for (int i = 0; i <= 2000; i++) {
        cout << "licze " << i;
        cout.flush();
        Fibo f(i);
        f += f;
        assert(f == Fibo(i + i));
        for (int j = 0; j <= 2000; j++) {
            assert(Fibo(i) + Fibo(j) == Fibo(i + j));
        }
        cout << " skonczylem" << endl;
    }
}