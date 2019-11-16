#ifndef FIBO_H
#define FIBO_H

#include <string>
#include "boost/dynamic_bitset.hpp"

class Fibo {
    boost::dynamic_bitset<> mask;
public:
    Fibo();

    explicit Fibo(const std::string &str);

    explicit Fibo(unsigned int n);

    Fibo(const Fibo &fibo);

    [[nodiscard]] size_t length() const;

    Fibo &operator+=(const Fibo &fibo);

    Fibo &operator&=(const Fibo &fibo);

    Fibo &operator|=(const Fibo &fibo);

    Fibo &operator^=(const Fibo &fibo);

    Fibo &operator<<=(unsigned int n);

    // Implicit declaration
    //void operator=(const Fibo &fibo);

    friend std::ostream &operator<<(std::ostream &os, const Fibo &fibo);
};

const Fibo operator+(const Fibo &fibo1, const Fibo &fibo2);

const Fibo operator&(const Fibo &fibo1, const Fibo &fibo2);

const Fibo operator|(const Fibo &fibo1, const Fibo &fibo2);

const Fibo operator^(const Fibo &fibo1, const Fibo &fibo2);

const Fibo operator<<(const Fibo &fibo, unsigned int n);

std::ostream &operator<<(std::ostream &os, const Fibo &fibo);


const Fibo &Zero();

const Fibo &One();

#endif //FIBO_H
