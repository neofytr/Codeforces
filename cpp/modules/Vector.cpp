module Vector;

Vector::Vector(const std::size_t sz) {
    if (sz >= Vector::maxVectorSize)
        throw std::length_error("The given size exceeds the maximum vector size!");
    elements = new double[sz];
    this->sz = sz;
}

double &Vector::operator[](std::size_t index) const {
    return elements[index];
}

std::size_t Vector::size() const {
    return sz;
}

bool operator==(const Vector &vecOne, const Vector &vecTwo) {
    if (vecOne.size() != vecTwo.size())
        return false;

    for (std::size_t i = 0; i < vecOne.size(); i++)
        if (vecOne[i] != vecTwo[i])
            return false;

    return true;
}
