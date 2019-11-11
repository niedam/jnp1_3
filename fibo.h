#ifndef FIBO_H
#define FIBO_H

#include <string>
#include "boost/dynamic_bitset.hpp"

class Fibo {
public:
    boost::dynamic_bitset<> mask;
public:
    Fibo();

    explicit Fibo(const std::string &str);

    Fibo(const Fibo &fibo);

    size_t length() const;

    void operator+=(const Fibo &fibo);

    void operator&=(const Fibo &fibo);

    void operator=(const Fibo &fibo);
};

Fibo operator+(const Fibo &fibo1, const Fibo &fibo2);

Fibo operator&(const Fibo &fibo1, const Fibo &fibo2);

std::ostream &operator<<(std::ostream &os, const Fibo &fibo);

const Fibo &Zero();

#endif //FIBO_H
