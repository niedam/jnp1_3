#include "fibo.h"

using boost::dynamic_bitset;
using std::min;
using std::max;

namespace {
    /** @brief Erases leading zeros from bitset.
     * @param mask[in,out]          - bitset.
     */
    void eraseLeadingZeros(dynamic_bitset<> &mask) {
        size_t size = mask.size();

        // mask is proper Fibonacci number (not normalized) so size > 0.
        size_t mostSignificantBytePos = size - 1;
        while (mostSignificantBytePos > 0 && !mask[mostSignificantBytePos]) {
            mostSignificantBytePos--;
        }

        if (mostSignificantBytePos + 1 < size) {
            mask.resize(mostSignificantBytePos + 1);
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
        size_t size = mask.size();
        assert(position < size);
        assert(!mask[position + 1]);
        assert(mask[position]);
        assert(position == 0 || mask[position - 1]);

        mask[position] = false;
        if (position > 0) {
            mask[position - 1] = false;
        }

        size_t addBytePos = position + 1;
        while (addBytePos < size) {
            if (addBytePos + 1 < size && mask[addBytePos + 1]) {
                mask[addBytePos + 1] = false;
                addBytePos += 2;
            } else {
                mask[addBytePos] = true;
                return;
            }
        }
        if (addBytePos == size) {
            mask.push_back(true);
        }
    }

    /** @brief Normalizes and erases leading zeros in Fibonacci number.
     * Assumes that @p mask is proper Fibonacci number (mask.size() > 0).
     * @param mask[in,out]          - given Fibonacci number.
     */
    void normalize(dynamic_bitset<> &mask) {
        // mask is proper Fibonacci number (not normalized) so size > 0.
        for (size_t i = mask.size() - 1; i > 0; i--) {
            if (mask[i] && mask[i - 1]) {
                normalizeOnPosition(mask, i);
            }
        }

        eraseLeadingZeros(mask);
    }

    /** @brief Adds f(@position + 2) Fibonacci number to @p mask Fibonacci number.
     * @param mask[in,out]          - given Fibonacci number;
     * @param position[in]          - position described above.
     */
    void addSingleByte(dynamic_bitset<> &mask, size_t position) {
        size_t size = mask.size();
        if (size <= position) {
            mask.resize(position + 1);
            size = position + 1;
        }

        if (!mask[position]) {
            mask[position] = true;
            if (position + 1 < size && mask[position + 1]) {
                normalizeOnPosition(mask, position + 1);
            } else if (position > 0 && mask[position - 1]) {
                normalizeOnPosition(mask, position);
            }
            return;
        }

        // mask[position] = true, so we have situation "...020x.." and we will change it to "...100(x+1)..."
        mask[position] = false;
        if (position + 1 == size) {
            mask.push_back(true);
            size++;
        } else {
            mask[position + 1] = true;
            if (position + 2 < size && mask[position + 2]) {
                normalizeOnPosition(mask, position + 2);
            }
        }

        // Now is the part when we change x to (x+1) (x is described in the comment above).
        // If (x+1) == 2, then we recursively change "...00(x+1)0y..." = "...0020y..." to "...0100(y+1)...".
        // If (x+1) == 1, then we have situation "...0(x+1)y..." = "...01y..." where y = {0, 1}, so we just change
        // x to (x+1) and we normalize if necessary.
        while (position >= 2) {
            position -= 2;
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

        // Now we would like to add byte (change x to (x+1)) on position - 2 but position < 2, so we need to add
        // f(position - 2 + 2) = f(position) Fibonacci number (index of number in mask is shifted by 2).

        // f0 Fibonacci is equal to 0, so we need to add nothing.
        if (position == 0) {
            return;
        }

        // f1 Fibonacci is equal to 1, so we need to add 1.
        // It is guaranteed that mask[1] = false.
        if (!mask[0]) {
            mask[0] = true;
        } else {
            normalizeOnPosition(mask, 0);
        }
    }

    //TODO using type dla dynamic_bitset?
    int compare(const dynamic_bitset<> &mask1, const dynamic_bitset<> &mask2) {
        if (mask1.size() > mask2.size()) {
            return 1;
        } else if (mask1.size() < mask2.size()) {
            return -1;
        }
        int length = min(mask1.size(), mask2.size());
        for (size_t i = 0; i < length; i++) {
            if (mask1[i] && !mask2[i])
                return 1;
            else if (mask1[i] && mask2[i]) {
                return -1;
            }
        }
        return 0;
    }

}

Fibo::Fibo() : mask(1, false) {}

Fibo::Fibo(const std::string &str) : mask(str) {
    normalize(mask);
}


// TODO generowane w stalej pamieci, ale za kazdym razem generuje potrzebne liczby Fibonacciego
Fibo::Fibo(unsigned int n) : mask(1, false) {
    int x = 1, y = 1, z;
    int id_x = 0;
    while (y > 0 && y < n) {
        z = x + y;
        x = y;
        y = z;
        id_x++;
    }
    if (n > 0) {
        if (y == n) {
            mask.resize(id_x + 1);
            mask[id_x] = true;
        } else {
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
}

Fibo::Fibo(const Fibo &fibo) : mask(fibo.mask) {}

size_t Fibo::length() const {
    return mask.size();
}

// TODO f += f jeszcze nie działa
Fibo &Fibo::operator+=(const Fibo &fibo) {
    size_t length = fibo.length();
    for (size_t i = 0; i < length; i++) {
        if (fibo.mask[i]) {
            addSingleByte(this->mask, i);
        }
    }

    return *this;
}

Fibo &Fibo::operator|=(const Fibo &fibo) {
    size_t length_fibo = fibo.length();
    size_t length_max = std::max(this->length(), length_fibo);
    this->mask.resize(length_max);
    for (size_t i = 0; i < length_fibo; i++) {
        this->mask[i] |= fibo.mask[i];
    }
    normalize(mask);
    return *this;
}

// TODO upewnić się, że f &= f działa
Fibo &Fibo::operator&=(const Fibo &fibo) {
    size_t length = min(this->length(), fibo.length());
    for (size_t i = 0; i < length; i++) {
        this->mask[i] &= fibo.mask[i];
    }
    this->mask.resize(length);
    eraseLeadingZeros(this->mask);

    return *this;
}

Fibo &Fibo::operator^=(const Fibo &fibo) {
    size_t length_fibo = fibo.length();
    size_t length_max = std::max(this->length(), length_fibo);
    this->mask.resize(length_max);
    for (size_t i = 0; i < length_fibo; i++) {
        this->mask[i] ^= fibo.mask[i];
    }
    normalize(mask);
    return *this;
}

Fibo &Fibo::operator<<=(unsigned int n) {
    this->mask.resize(this->mask.size() + n);
    this->mask <<= n;
    return *this;
}

// TODO ide podpowiada, aby wywalić const ale w czytankach było aby dać consty
const Fibo operator+(const Fibo &fibo1, const Fibo &fibo2) {
    return Fibo(fibo1) += fibo2;
}

//TODO
bool operator<(const Fibo &fibo1, const Fibo &fibo2) {
    return false; //(compare(fibo1.mask, fibo2.mask) == -1?true:false);
}

const Fibo operator&(const Fibo &fibo1, const Fibo &fibo2) {
    return Fibo(fibo1) &= fibo2;
}

const Fibo operator|(const Fibo &fibo1, const Fibo &fibo2) {
    return Fibo(fibo1) |= fibo2;
}

const Fibo operator^(const Fibo &fibo1, const Fibo &fibo2) {
    return Fibo(fibo1) ^= fibo2;
}

const Fibo operator<<(const Fibo &fibo, unsigned int n) {
    return Fibo(fibo) <<= n;
}

std::ostream &operator<<(std::ostream &os, const Fibo &fibo) {
    os << fibo.mask;
    return os;
}

const Fibo &Zero() {
    static Fibo *fibo = new Fibo();
    return *fibo;
}

const Fibo &One() {
    static Fibo *fibo = new Fibo(1);
    return *fibo;
}
