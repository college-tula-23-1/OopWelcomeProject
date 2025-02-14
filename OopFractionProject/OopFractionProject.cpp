#include <iostream>

class Fraction
{
    int numerator;
    int denominator;

    int Nod(int a, int b)
    {
        int r;

        while (a != 0 && b != 0)
        {
            if (a > b)
            {
                r = a % b;
                a = b;
                b = r;
            }
            else
            {
                r = b % a;
                b = r;
            }
        }
        return (a != 0) ? a : b;
    }

    void Shorten()
    {
        int nod = Nod(numerator, denominator);
        numerator /= nod;
        denominator /= nod;
    }

public:
    /*Fraction()
    {
        this->numerator = 0;
        this->denominator = 1;
    }*/

    /*Fraction(int numerator, int denominator)
    {
        this->numerator = numerator;
        this->denominator = denominator;
    }*/

    Fraction() : Fraction(0, 1) {}
        //: numerator{ 0 }, denominator{ 1 } {}

    Fraction(int numerator, int denominator)
        : numerator{ numerator },
        denominator{ denominator } {}
    
    ~Fraction() {}

    int getNumerator() { return numerator; }
    void setNumerator(int value) { numerator = value; }

    int getDenominator() { return denominator; }
    bool setDenominator(int value)
    {
        if (value != 0)
        {
            denominator = value;
            return true;
        }

        return false;
    }

    Fraction Add(Fraction f)
    {
        numerator = numerator * f.denominator + denominator * f.numerator;
        denominator *= f.denominator;
        Shorten();
    }

    Fraction Delete(Fraction f)
    {
        numerator = numerator * f.denominator - denominator * f.numerator;
        denominator *= f.denominator;
        Shorten();
    }

    Fraction Plus(Fraction f)
    {
        Fraction result;
        result.numerator = numerator * f.denominator + denominator * f.numerator;
        result.denominator = denominator * f.denominator;
        result.Shorten();
        return result;
    }

    Fraction Minus(Fraction f)
    {
        Fraction result;
        result.numerator = this->numerator * f.denominator - this->denominator * f.numerator;
        result.denominator = this->denominator * f.denominator;
        result.Shorten();
        return result;
    }

    void Show()
    {
        std::cout << "[" << numerator << "/" << denominator << "]";
    }

    friend Fraction operator+(Fraction f1, Fraction f2)
    {
        Fraction result;
        result.numerator = f1.numerator * f2.denominator 
            + f1.denominator * f2.numerator;

        result.denominator = f1.denominator * f2.denominator;
        result.Shorten();
        return result;
    }

    friend Fraction operator+(Fraction f, int number)
    {
        Fraction fadd(number, 1);
        return f + fadd;
    }

    friend Fraction operator+(int number, Fraction f)
    {
        return f + number;
    }

    Fraction operator-()
    {
        Fraction result = *this;
        result.numerator = -result.numerator;
        return result;
    }

    Fraction operator++()
    {
        *this = *this + 1;
        return *this;
    }

    Fraction operator++(int)
    {
        Fraction result = *this;
        ++(*this);
        return result;
    }

    friend bool operator<(Fraction f1, Fraction f2)
    {
        return f1.numerator * f2.denominator < f1.denominator * f2.numerator;
    }

    friend bool operator>=(Fraction f1, Fraction f2)
    {
        return !(f1 < f2);
    }

    friend std::ostream& operator<<(std::ostream& out, const Fraction& f)
    {
        out << "[" << f.numerator << "/"
            << f.denominator << "]";
        return out;
    }
    
    operator double()
    {
        return (double)numerator / denominator;
    }
};

class Money
{
    int rub;
    int kop;
public:
    Money(int rub, int kop) : rub{ rub }, kop{ kop } {}

    int& Rub() { return rub; }
    int& Kop() { return kop; }

    operator double()
    {
        return rub + (double)kop / 100;
    }

    explicit operator Fraction()
    {
        return Fraction(rub * 100 + kop, 100);
    }

    operator bool()
    {
        return rub != 0 || kop != 0;
    }
};

int main()
{
    Fraction f1(1, 5);
    /*Fraction f2(2, 7);
    
    std::cout << ((double)f1 + 5.6) << "\n";*/

    Money m1(10, 20);
    std::cout << f1 + (Fraction)m1;
}
