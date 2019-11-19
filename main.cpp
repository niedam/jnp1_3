#include "fibo.h"

#include <cassert>
#include <iostream>

using  namespace std;

int main() {
    Fibo f;

    assert(f == Zero());
    assert(Fibo(f) == Zero());
    //assert(Zero() < One());
    assert(Fibo("11") == Fibo("100"));
    assert((Fibo("1001") + Fibo("10")) == Fibo("1011"));
    assert((Fibo("1001") & Fibo("1100")) == Zero()); // 1100 == 10000
    assert((Fibo("1100") | Fibo("11")) == Fibo("10100")); // 1100 == 10000, 11 == 100
    assert((Fibo("1001") ^ Fibo("1010")) == Fibo("11"));
    assert((Fibo("101") << 3) == Fibo("101000"));

    f = One();
    f <<= 3;
    assert(f == Fibo("1000"));

    f = One();

    f = 2;

    assert(f + Fibo("1") == Fibo("10"));
    assert(f == One());
    assert(Fibo(2) != One());

    Fibo f1("101");
    Fibo f2 = Fibo("101");
    assert(f1 == f2);

    assert(Fibo("11").length() == 3); // 11 == 100

    Fibo f_big(18446744073709551615ULL);
    cout << f_big << '\n';
    Fibo f_big2(8 * 1000 * 1000 * 1000LL);
    cout << f_big2 << '\n';

    //f1 += 2;
    f2 = Fibo("1001");

    Fibo f0(0);
    cout << f0.length() << ' ' << f0 << '\n';

    //NIE POWINNO SIĘ KOMPILOWAĆ
    /*Fibo f_char;
    f_char = Fibo((char)'a');
    f_char = Fibo((char16_t)'a');
    f_char = Fibo((char32_t)'a');
    f_char = Fibo((wchar_t)'a');
    f_char = Fibo((signed char)'a');
    f_char = Fibo((unsigned char)'a');*/


    std::cout << Fibo("11") << std::endl; // prints 100
}