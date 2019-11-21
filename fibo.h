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

    /** Overload addition assignment
     * Set value to sum of this and another Fibo number
     * @param[in] fibo - another Fibo number
     * @return Reference to current Fibo number
     */
    Fibo &operator+=(const Fibo &fibo);

    /** Overload "fi-bitwise AND" assignment
     * Set value to "fi-bitwise AND" of this and another Fibo number
     * @param[in] fibo - another Fibo number
     * @return Reference to current Fibo number
     */
    Fibo &operator&=(const Fibo &fibo);

    /** Overload "fi-bitwise OR" assignment
     * Set value to "fi-bitwise OR" of this and another Fibo number
     * @param[in] fibo - another Fibo number
     * @return Reference to current Fibo number
     */
    Fibo &operator|=(const Fibo &fibo);

    /** Overload "fi-bitwise XOR" assignment
     * Set value to "fi-bitwise XOR" of this and another Fibo number
     * @param[in] fibo - another Fibo number
     * @return Reference to current Fibo number
     */
    Fibo &operator^=(const Fibo &fibo);

    /** Overload "fi-bitwise left shift" assignment
     * Set value to "fi-bitwise left shift" of this and another Fibo number
     * @param[in] n - number of places to shift
     * @return Reference to current Fibo number
     */
    Fibo &operator<<=(unsigned int n);

    /** Less than Fibo numbers operator
     * Checks if fibo1 < fibo2
     * @param[in] fibo1 - Fibo number
     * @param[in] fibo2 - Fibo number
     * @return @p true - fibo1 < fibo2, @p false - otherwise
     */
    friend bool operator<(const Fibo &fibo1, const Fibo &fibo2);

    /** Equal Fibo numbers operator
     * Checks if two Fibo numbers are equal
     * @param[in] fibo1 - Fibo number
     * @param[in] fibo2 - Fibo number
     * @return @p true - fibo1 == fibo2, @p false - otherwise
     */
    friend bool operator==(const Fibo &fibo1, const Fibo &fibo2);

    /** Output operator for Fibo numbers
     * Print Fibo number through stream
     * @param[out] os - output stream
     * @param[in] fibo - Fibo number to print
     * @return Reference to output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Fibo &fibo);
};

/** Reference to immutable Fibo(0)
 * @return Reference to const Fibo(0)
 */
const Fibo &Zero();

/** Reference to immutable Fibo(1)
 * @return Reference to const Fibo(1)
 */
const Fibo &One();

#endif //FIBO_H
