#pragma once

#include "rational.h"
#include "pow.h"

#include <string>
#include <optional>
#include <cmath>

using Error = std::string;

template<typename Number>
class Calculator {
public:

    void Set(Number number_set) {
        number_ = number_set;
    }


    Number GetNumber() const {
        return number_;
    }


    std::optional<Error> Add(Number number_add) {
        number_ += number_add;
        return std::nullopt;
    }


    std::optional<Error> Sub(Number number_sub) {
        number_ -=number_sub;
        return std::nullopt;
    }


    std::optional<Error> Div(Number number_div) {
        if constexpr (std::is_floating_point_v<Number>) {
            number_ /= number_div;
            return std::nullopt;
        }
        else if constexpr (std::is_same_v<Number, Rational>) {
            if (number_div == Rational(0)) return "Division by zero";
            number_ /= number_div;
            return std::nullopt;
        }
        else {
            if (number_div == 0) return "Division by zero";
            number_ /= number_div;
            return std::nullopt;
        }
    }


    std::optional<Error> Mul(Number number_mul) {
        number_ *= number_mul;
        return std::nullopt;
    }


    template <class P>
    std::optional<Error> Pow(P number_pow) {
        if constexpr(std::is_floating_point_v<Number>) {
            number_ = std::pow(number_ , number_pow);
            return std::nullopt;
        }
        else if constexpr (std::is_integral_v<Number>) {
            if (number_pow <0) {
                return "Integer negative power";
            }
            else if(number_pow == 0 && number_ ==0) {
                return "Zero power to zero";
            }
            number_ = ::IntegerPow(number_,static_cast<Number>(number_pow));
            return std::nullopt;
        }
        else {
            Rational pow_rational = number_pow;
            if(pow_rational == Rational(0) && number_ == Rational(0)) {
                return "Zero power to zero";
            }
            if (pow_rational.GetDenominator() != 1) {
                return "Fractional power is not supported";
            }
            number_ = ::Pow(number_,pow_rational);
            return std::nullopt;
        }
    }


    bool GetHasMem() const {
        return mem_.has_value();
    }


    void Save() {
        mem_ = number_;
    }


    std::optional<Number> Load() {
        if (mem_.has_value()) {
            number_ = mem_.value();
            return number_;
        }
        return std::nullopt;
    }

private:
    Number number_;
    std::optional<Number> mem_;
};
