module;
export module Complex;

export class Complex {
  private:
    double re, im;

  public:
    Complex(const double real, const double img) : re{real}, im{img} {}
    [[nodiscard]] double getReal() const { return re; }
    [[nodiscard]] double getImg() const { return im; }
    void setReal(const double r) { re = r; }
    void setImg(const double i) { im = i; }

    Complex &operator+=(const Complex &z) {
        re += z.getReal();
        im += z.getImg();
        return *this;
    }

    Complex &operator-(const Complex &z) {
        re -= z.getReal();
        im -= z.getImg();
        return *this;
    }

    Complex &operator*=(const double scl) {
        re *= scl;
        im *= scl;
        return *this;
    }

    Complex &operator/=(const double scl) {
        *this *= 1 / scl;
        return *this;
    }
};