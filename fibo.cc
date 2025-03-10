#include "fibo.h"
#include <cassert>

using boost::dynamic_bitset;
using std::min;
using std::max;

namespace {
    /** @brief Erases leading zeros from Fibonacci number.
     * @param mask[in,out]          - given Fibonacci number.
     */
    void eraseLeadingZeros(dynamic_bitset<> &mask) {
        size_t length = mask.size();
        assert(length > 0); // mask is proper Fibonacci number (not normalized) so length > 0.

        size_t mostSignificantBitPos = length - 1;
        while (mostSignificantBitPos > 0 && !mask[mostSignificantBitPos]) {
            mostSignificantBitPos--;
        }

        if (mostSignificantBitPos + 1 < length) {
            mask.resize(mostSignificantBitPos + 1);
        }
    }

    /** @brief Normalizes Fibonacci number but only on indexes >= @p position - 1.
     * Assumes that given Fibonacci number is normalized on indexes >= @p position, @p mask[position + 1] = @p false,
     * @p mask[position] = @p true and @p mask[position - 1] = @p true (if @p position = 0, then we treat @p mask
     * Fibonacci number as it has mask[-1] = @p true despite -1 is invalid index number).
     * @param mask[in,out]          - given Fibonacci number;
     * @param position[in]          - position described above.
     */
    void normalizeOnPosition(dynamic_bitset<> &mask, size_t position) {
        size_t length = mask.size();
        assert(position < length);
        assert(!mask[position + 1]);
        assert(mask[position]);
        assert(position == 0 || mask[position - 1]);

        mask[position] = false;
        if (position > 0) {
            mask[position - 1] = false;
        }

        size_t addBitPos = position + 1;
        while (addBitPos < length) {
            assert(!mask[position]);
            if (addBitPos + 1 < length && mask[addBitPos + 1]) {
                mask[addBitPos + 1] = false;
                addBitPos += 2;
            } else {
                mask[addBitPos] = true;
                return;
            }
        }
        mask.push_back(true);
    }

    /** @brief Normalizes and erases leading zeros in Fibonacci number.
     * Assumes that @p mask is proper Fibonacci number (mask.size() > 0).
     * @param mask[in,out]          - given Fibonacci number.
     */
    void normalize(dynamic_bitset<> &mask) {
        size_t length = mask.size();
        assert(length > 0); // mask is proper Fibonacci number (not normalized) so length > 0.

        for (size_t i = length - 1; i > 0; i--) {
            if (mask[i] && mask[i - 1]) {
                normalizeOnPosition(mask, i);
            }
        }

        eraseLeadingZeros(mask);
    }

    /** @brief Adds f(@p position + 2) Fibonacci number to @p mask Fibonacci number.
     * @param mask[in,out]          - given Fibonacci number;
     * @param position[in]          - position described above.
     */
    void addSingleBit(dynamic_bitset<> &mask, size_t position) {
        size_t length = mask.size();
        if (length <= position) {
            mask.resize(position + 1);
            length = position + 1;
        }

        if (!mask[position]) {
            mask[position] = true;
            if (position + 1 < length && mask[position + 1]) {
                normalizeOnPosition(mask, position + 1);
            } else if (position > 0 && mask[position - 1]) {
                normalizeOnPosition(mask, position);
            }
            return;
        }

        // mask[position] = true, so we have situation "...020x.." and we will change it to "...100(x+1)..."
        mask[position] = false;
        if (position + 1 == length) {
            mask.push_back(true);
            length++;
        } else {
            assert(!mask[position + 1]);
            mask[position + 1] = true;
            if (position + 2 < length && mask[position + 2]) {
                normalizeOnPosition(mask, position + 2);
            }
        }

        // Now is the part when we change x to (x+1) (x is described in the comment above).
        // If (x+1) == 2, then we recursively change "...00(x+1)0y..." = "...0020y..." to "...0100(y+1)...".
        // If (x+1) == 1, then we have situation "...0(x+1)y..." = "...01y..." where y = {0, 1}, so we just change
        // x to (x+1) and we normalize if necessary.
        while (position >= 2) {
            position -= 2;
            assert(!mask[position + 1]);
            if (!mask[position]) {
                mask[position] = true;
                if (position > 0 && mask[position - 1]) {
                    normalizeOnPosition(mask, position);
                }
                return;
            }

            mask[position + 1] = true;
            mask[position] = false;
        }

        // Now we would like to add bit (change x to (x+1)) on position - 2 but position < 2, so we need to add
        // f(position - 2 + 2) = f(position) Fibonacci number (index of number in mask is shifted by 2).

        // f0 Fibonacci is equal to 0, so we need to add nothing.
        if (position == 0) {
            return;
        }

        // f1 Fibonacci is equal to 1, so we need to add 1.
        // It is guaranteed that mask[1] = false.
        assert(length > 0 || !mask[1]);
        if (!mask[0]) {
            mask[0] = true;
        } else {
            normalizeOnPosition(mask, 0);
        }
    }
}

Fibo::Fibo() : mask(1, false) {}

Fibo::Fibo(const std::string &str) : mask(str) { // Asserts if str contains other character than '0' or '1'.
    size_t length = mask.size();
    assert(length > 0); // Proper Fibonacci number has size at least 1.
    assert(length == 1 || mask[length - 1]); // Proper Fibonacci number does not have leading zeros.
    normalize(mask);
}

Fibo::Fibo(const char *str) : Fibo((std::string) str) {}

// Asserts if any signed type gets a negative value.

Fibo::Fibo(short int n) : Fibo((unsigned long long) n) {
    assert(n >= 0); // The negative numbers do not have representation in Fibonacci code.
}

Fibo::Fibo(unsigned short int n) : Fibo((unsigned long long) n) {}

Fibo::Fibo(int n) : Fibo((unsigned long long) n) {
    assert(n >= 0); // The negative numbers do not have representation in Fibonacci code.
}

Fibo::Fibo(unsigned int n) : Fibo((unsigned long long) n) {}

Fibo::Fibo(long int n) : Fibo((unsigned long long) n) {
    assert(n >= 0); // The negative numbers do not have representation in Fibonacci code.
}

Fibo::Fibo(unsigned long int n) : Fibo((unsigned long long) n) {}

Fibo::Fibo(long long n) : Fibo((unsigned long long) n) {
    assert(n >= 0); // The negative numbers do not have representation in Fibonacci code.
}

Fibo::Fibo(unsigned long long n) : mask(1, false) {
    unsigned long long x = 1, y = 1, z;
    int id_x = 0;
    while (x <= y && y < n) {
        z = x + y;
        x = y;
        y = z;
        id_x++;
    }
    if (y == n) {
        mask.resize(id_x + 1);
        mask[id_x] = true;
    } else if (n != 0) {
        mask.resize(id_x);
        while (n > 0) {
            mask[id_x - 1] = true;
            n -= x;
            while (x > n) {
                z = y - x;
                y = x;
                x = z;
                id_x--;
            }
        }
    }
}

[[nodiscard]] size_t Fibo::length() const {
    return mask.size();
}

Fibo &Fibo::operator+=(const Fibo &fibo) {
    if (&fibo != this) {
        size_t length = fibo.mask.size();
        for (size_t i = 0; i < length; i++) {
            if (fibo.mask[i]) {
                addSingleBit(mask, i);
            }
        }
        return *this;
    }

    // Now we have Fibonacci number consisting only of 0's and 2's. No two 2's are directly next to each other.
    // We will change this into proper Fibonacci number (not yet normalized).
    // We will recursively change situation "...020x..." into "...100(x+1)...", "...030x..." into "...110(x+1)..."
    // and "...0120x..." into "...1010x...". One can prove that making these changes we will encounter only
    // situations that will require those changes.
    mask.push_back(false);
    bool addAdditionalBit = false; // Variable that tells that we should add bit on current position ((x+1) described above).
    long long position;
    for (position = (long long) mask.size() - 2; position >= 0; position--) {
        if (mask[position]) {
            if (mask[position + 1]) {
                assert(!mask[position + 2]);
                mask[position + 2] = true;
                mask[position + 1] = false;
            } else {
                mask[position + 1] = true;
                mask[position] = addAdditionalBit;
                addAdditionalBit = true;
            }

            // We are guaranteed that there is no '2' on position - 1, so we can decrease variable position.
            // We have to decrease variable position here because we set
            // variable addAdditionalBit to true above which would be wrong without this.
            assert(position < 1 || !mask[position - 1]);
            position--;
        } else {
            mask[position] = addAdditionalBit;
            addAdditionalBit = false;
        }
    }

    normalize(mask);

    // If we have leftover (addAdditionalBit == true) from for above we are adding this here.
    // mask[-1] would be Fibonacci number F(1) = 1 and mask[-2] would be F(0) = 0.
    if (addAdditionalBit && position == -1) {
        addSingleBit(mask, 0);
    }

    return *this;
}

Fibo &Fibo::operator|=(const Fibo &fibo) {
    size_t lengthFibo = fibo.mask.size();
    size_t lengthMax = max(mask.size(), lengthFibo);
    mask.resize(lengthMax);
    for (size_t i = 0; i < lengthFibo; i++) {
        mask[i] |= fibo.mask[i];
    }
    normalize(mask);
    return *this;
}

Fibo &Fibo::operator&=(const Fibo &fibo) {
    size_t lengthMin = min(mask.size(), fibo.mask.size());
    for (size_t i = 0; i < lengthMin; i++) {
        mask[i] &= fibo.mask[i];
    }
    mask.resize(lengthMin);
    eraseLeadingZeros(mask);

    return *this;
}

Fibo &Fibo::operator^=(const Fibo &fibo) {
    size_t lengthFibo = fibo.mask.size();
    size_t lengthMax = max(mask.size(), lengthFibo);
    mask.resize(lengthMax);
    for (size_t i = 0; i < lengthFibo; i++) {
        mask[i] ^= fibo.mask[i];
    }
    normalize(mask);
    return *this;
}

Fibo &Fibo::operator<<=(unsigned int n) {
    mask.resize(mask.size() + n);
    mask <<= n;
    return *this;
}

bool operator<(const Fibo &fibo1, const Fibo &fibo2) {
    size_t length1 = fibo1.mask.size();
    size_t length2 = fibo2.mask.size();

    if (length1 == length2) {
        return (fibo1.mask < fibo2.mask);
    }
    return length1 < length2;
}

bool operator==(const Fibo &fibo1, const Fibo &fibo2) {
    return fibo1.mask == fibo2.mask;
}

std::ostream &operator<<(std::ostream &os, const Fibo &fibo) {
    os << fibo.mask;
    return os;
}

const Fibo &Zero() {
    static const Fibo fibo;
    return fibo;
}

const Fibo &One() {
    static const Fibo fibo(1ULL);
    return fibo;
}
