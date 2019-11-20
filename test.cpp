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

    srand(1231);
    for (int i = 0; i < 1000000; i++) {
        long long a = rand(), b = rand();

        Fibo aa = a;
        if (aa + Fibo(b) != Fibo(a + b)) {
            cout << "zle randy: " << a << " + " << b << endl;
            return 1;
        }
        aa += aa;
        if (aa != Fibo(a + a)) {
            cout << "zle randy: " << a << " += " << a << endl;
            return 1;
        }
    }
}