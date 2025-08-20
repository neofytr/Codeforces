module;
export module Complex;

/*
 * Functions defined in a class are inlined by default
 * Copy assignment and copy initialization are implicitly defined
 */

export class Complex {
  private:
    double re, im;

  public:
    Complex(const double real, const double img) : re{real}, im{img} {}
    Complex() : re{0}, im{0} {} // default constructor
    [[nodiscard]] double getReal() const { return re; }
    [[nodiscard]] double getImg() const { return im; }
    void setReal(const double r) { re = r; }
    void setImg(const double i) { im = i; }

    inline constexpr Complex &operator+=(const Complex &z) {
        re += z.getReal();
        im += z.getImg();
        return *this;
    }

    inline constexpr Complex &operator-=(const Complex &z) {
        re -= z.getReal();
        im -= z.getImg();
        return *this;
    }

    inline constexpr Complex &operator*=(const double scl) {
        re *= scl;
        im *= scl;
        return *this;
    }

    inline constexpr Complex &operator/=(const double scl) {
        *this *= 1 / scl;
        return *this;
    }

    inline constexpr Complex &operator*=(const Complex &b) {
        // a = a * b
        // a = (x + yi)(m + ni) = (xm - yn + i(xn + my))
        re = re * b.getReal() - im * b.getImg();
        im = re * b.getImg() + im * b.getReal();
        return *this;
    }
};

inline Complex operator+(Complex a, const Complex b) {
    return a += b;
}

inline Complex operator-(Complex a, const Complex b) {
    return a -= b;
}

inline Complex operator-(Complex a) {
    return a *= -1;
}

inline Complex operator*(Complex a, const Complex b) {
    return a *= b;
}

inline bool operator==(const Complex &a, const Complex &b) {
    return a.getReal() == b.getReal() && a.getImg() == b.getImg();
}

inline bool operator!=(const Complex &a, const Complex &b) {
    return !(a == b);
}