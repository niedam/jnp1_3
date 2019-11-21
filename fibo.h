#ifndef FIBO_H
#define FIBO_H

#include <string>
#include <boost/dynamic_bitset.hpp>
#include <boost/operators.hpp>

class Fibo : boost::totally_ordered<Fibo>,
        boost::addable<Fibo>,
        boost::bitwise<Fibo>,
        boost::left_shiftable<Fibo, unsigned int> {
    boost::dynamic_bitset<> mask;
public:
    Fibo();

    explicit Fibo(const std::string &str);

    explicit Fibo(const char *str);

    explicit Fibo(short int n);

    explicit Fibo(unsigned short int n);

    explicit Fibo(int n);

    explicit Fibo(unsigned int n);

    explicit Fibo(long int n);

    explicit Fibo(unsigned long int n);

    explicit Fibo(long long n);

    Fibo(unsigned long long n);

    explicit Fibo(char a) = delete;

    explicit Fibo(char16_t a) = delete;

    explicit Fibo(char32_t a) = delete;

    explicit Fibo(wchar_t a) = delete;

    explicit Fibo(signed char a) = delete;

    explicit Fibo(unsigned char a) = delete;

    explicit Fibo(bool b) = delete;

    [[nodiscard]] size_t length() const;

    Fibo &operator+=(const Fibo &fibo);

    Fibo &operator&=(const Fibo &fibo);

    Fibo &operator|=(const Fibo &fibo);

    Fibo &operator^=(const Fibo &fibo);

    Fibo &operator<<=(unsigned int n);

    friend std::ostream &operator<<(std::ostream &os, const Fibo &fibo);

    friend bool operator<(const Fibo &fibo1, const Fibo &fibo2);

    friend bool operator==(const Fibo &fibo1, const Fibo &fibo2);

};

bool operator<(const Fibo &fibo1, const Fibo &fibo2);

bool operator==(const Fibo &fibo1, const Fibo &fibo2);

const Fibo &Zero();

const Fibo &One();

#endif //FIBO_H
