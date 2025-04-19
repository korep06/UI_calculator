#pragma once

#include <iostream>
#include <string>
#include <numeric>
#include <cstdlib>
#include <sstream>

class Rational {
public:
    Rational() : numerator_(0), denominator_(1) {};

    Rational(int numerator) : numerator_(numerator), denominator_(1) {};

    Rational(int numerator, int denominator) {
        if (denominator == 0) {
            std::cerr << "Error" << std::endl;
            std::abort();
        }
        if (denominator < 0) {
            numerator_ = -numerator;
            denominator_ = -denominator;
        }
        else {
            numerator_ = numerator;
            denominator_ = denominator;
        }
        Reduction();
    }

    Rational(const Rational& other) : numerator_(other.numerator_), denominator_(other.denominator_) { Reduction(); };

    friend std::istream& operator>>(std::istream& is, Rational& rational);

    friend std::ostream& operator<<(std::ostream& os, const Rational& rational);

    Rational operator+() const {
        return *this;
    }


    Rational operator-() const {
        return { -numerator_ , denominator_ };
    }


    Rational& operator=(const int value) {
        numerator_ = value;
        denominator_ = 1;
        return *this;
    }


    Rational& operator=(const Rational& r) {
        numerator_ = r.numerator_;
        denominator_ = r.denominator_;
        return *this;
    }


    Rational& operator+=(const Rational& r) {
        numerator_ = numerator_ * r.denominator_ + r.numerator_ * denominator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }


    Rational& operator-=(const Rational& r) {
        numerator_ = numerator_ * r.denominator_ - r.numerator_ * denominator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }


    Rational& operator*=(const Rational& r) {
        numerator_ = numerator_ * r.numerator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }


    Rational& operator/=(const Rational& r) {
        numerator_ = numerator_ * r.denominator_;
        denominator_ *= r.numerator_;
        Reduction();
        return *this;
    }


    explicit operator double() const {
        return static_cast<double>(numerator_) / denominator_;
    }


    Rational operator+(const Rational& r) const {
        Rational result(*this);
        result += r;
        return result;
    }


    Rational operator-(const Rational& r) const {
        Rational result(*this);
        result -= r;
        return result;
    }


    Rational operator*(const Rational& r) const {
        Rational result(*this);
        result *= r;
        return result;
    }


    Rational operator/(const Rational& r) const {
        Rational result(*this);
        result /= r;
        return result;
    }

public:
    int GetNumerator() const {
        return numerator_;
    }


    int GetDenominator() const {
        return denominator_;
    }


    Rational Inv() const {
        return { denominator_ , numerator_ };
    }


    std::string ToString(const Rational& r) {
        std::ostringstream out;
        out << r;
        return out.str();
    }


    Rational FromString(const std::string& str) {
        std::istringstream in(str);
        Rational r;
        in >> r;
        return r;
    }

private:
    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

private:
    int numerator_ = 0 ;
    int denominator_ = 1;

};

inline std::istream& operator>>(std::istream& is, Rational& rational) {
    int numerator, denominator;
    char div;

    if (!(is >> numerator)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    is >> std::ws;

    if (!(is >> div)) {
        is.clear();
        rational.numerator_ = numerator;
        rational.denominator_ = 1;
        return is;
    }

    if (div != '/') {
        is.unget();
        rational.numerator_ = numerator;
        rational.denominator_ = 1;
        return is;
    }

    if (!(is >> denominator) || (denominator == 0)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    rational.numerator_ = numerator;
    rational.denominator_ = denominator;
    rational.Reduction();
    return is;

}

inline std::ostream& operator<<(std::ostream& os, const  Rational& rational) {
    if (rational.denominator_ == 1) {
        os << rational.numerator_;
        return os;
    }
    else {
        os << rational.numerator_ << " / " << rational.denominator_;
        return os;
    }

}

inline auto operator<=>(const Rational& r1, const Rational& r2) {
    return ((static_cast<std::int64_t>(r1.GetNumerator()) * r2.GetDenominator()) <=> (static_cast<std::int64_t>(r1.GetDenominator()) * r2.GetNumerator()));
}

inline auto operator==(const Rational& r1, const Rational& r2) {
    return ((static_cast<std::int64_t>(r1.GetNumerator()) * r2.GetDenominator()) == (static_cast<std::int64_t>(r1.GetDenominator()) * r2.GetNumerator()));
}
