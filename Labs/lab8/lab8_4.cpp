//Lab 8
//Exercice 4

#include <iostream>

class Complex{
private:
    double real;
    double imaginary;
public:
    Complex(double r= 0, double i=0) : real(r), imaginary(i){};

    Complex operator+(Complex& other) const {
        return Complex((this->real+other.real), (this->imaginary + other.imaginary));
    }

    Complex operator-(Complex& other) const {
        return Complex((this->real-other.real), (this->imaginary - other.imaginary));
    }

    Complex operator*(Complex& other){
        return Complex((this->real*other.real - this->imaginary*other.imaginary), (this->real*other.imaginary+ this->imaginary* other.real));
    }

    Complex operator/(Complex& other){
        double denominator = other.real * other.real + other.imaginary * other.imaginary;
        if (denominator == 0) { 
            throw std::runtime_error("Division by zero");
        }
        return Complex(((this->real * other.real + this->imaginary * other.imaginary) / denominator), ((this->imaginary * other.real - this->real * other.imaginary) / denominator));
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c){
        os << c.real << " + " << c.imaginary<<"i";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Complex& c){
        std::cout << "Enter real part: ";
        is >> c.real;
        std::cout << "Enter imaginary part: ";
        is >> c.imaginary;
        return is;
    }
};


void main(){
    Complex c1, c2, result;

    std::cout <<"Enter first complex number:\n";
    std::cin >> c1;
    std::cout <<"Enter second complex number:\n";
    std::cin >> c2;

    result = c1 + c2;
    std::cout <<"Sum: "<< result<<std::endl;
    result = c1 - c2;
    std::cout <<"Difference: "<< result<<std::endl;
    result = c1*c2;
    std::cout <<"Multiplication: "<< result<<std::endl;
    result = c1/c2;
    std::cout <<"Quotient: "<< result<<std::endl;

}
