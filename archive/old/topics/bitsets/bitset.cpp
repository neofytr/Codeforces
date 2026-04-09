#include <iostream>
#include <bitset>
#include <string>

int main() {
    // create bitsets
    std::bitset<8> a; // default initialized to 00000000
    std::bitset<8> b("10101010"); // initialized with binary string
    std::bitset<8> c(42); // initialized with integer (decimal 42 = 00101010)

    // display bitsets
    std::cout << "bitsets:\n";
    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
    std::cout << "c = " << c << "\n\n";

    // bitwise operations
    std::cout << "bitwise operations:\n";
    std::cout << "b & c = " << (b & c) << "\n"; // and
    std::cout << "b | c = " << (b | c) << "\n"; // or
    std::cout << "b ^ c = " << (b ^ c) << "\n"; // xor
    std::cout << "~b    = " << (~b) << "\n"; // not
    std::cout << "b << 2 = " << (b << 2) << "\n"; // left shift
    std::cout << "b >> 2 = " << (b >> 2) << "\n\n"; // right shift

    // setting and resetting bits
    std::cout << "bit modification:\n";
    a.set(); // set all bits to 1
    std::cout << "a.set() -> " << a << "\n";
    a.reset(); // reset all bits to 0
    std::cout << "a.reset() -> " << a << "\n";
    a.set(2); // set the bit at position 2
    std::cout << "a.set(2) -> " << a << "\n";
    a.reset(2); // reset the bit at position 2
    std::cout << "a.reset(2) -> " << a << "\n";
    a.flip(); // flip all bits
    std::cout << "a.flip() -> " << a << "\n";
    a.flip(0); // flip bit at position 0
    std::cout << "a.flip(0) -> " << a << "\n\n";

    // testing bits
    std::cout << "bit testing:\n";
    std::cout << "a.test(0) = " << a.test(0) << "\n";
    std::cout << "a.any() = " << a.any() << "\n"; // check if any bit it turned on
    std::cout << "a.none() = " << a.none() << "\n"; // check if all the bits are off
    std::cout << "a.all() = " << a.all() << "\n\n"; // check if all the bits are turned on

    // count and size
    std::cout << "count and size:\n";
    std::cout << "b.count() = " << b.count() << "\n"; // number of bits set
    std::cout << "b.size() = " << b.size() << "\n\n"; // number of bits total

    // accessing individual bits
    std::cout << "accessing bits:\n";
    std::cout << "b[0] = " << b[0] << "\n";
    std::cout << "b[1] = " << b[1] << "\n\n";

    // string and number conversion
    std::cout << "conversion:\n";
    std::string str = b.to_string(); // to string
    std::cout << "b.to_string() = " << str << "\n";
    std::cout << "b.to_ulong() = " << b.to_ulong() << "\n"; // to unsigned long
    std::cout << "b.to_ullong() = " << b.to_ullong() << "\n"; // to unsigned long long
    // std::cout << std::bitset<70>("111...").to_ulong(); would throw std::overflow_error

    return 0;
}
