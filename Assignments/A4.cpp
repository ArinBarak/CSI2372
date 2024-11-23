//Assignment 4

#include <iostream>
#include <math.h>
#include <cmath>

class BigInteger{
private:
    char *digits;
    int size;
    int base;
    bool negative = false;

    char numToChar(int digit) const {
        if (digit < 10) {
            return '0' + digit;
        } else {
            return 'A' + (digit-10);
        }
    }

public:
    BigInteger() : digits(new char[1]{'0'}), base(10), size(1) {}
    
    BigInteger(int d, int b) : base(b) {
        if (b < 2 || b > 36) {
            throw std::out_of_range("Base must be between 2 and 36.");
        }

        if (d == 0) {
            size = 1;
            digits = new char[1];
            digits[0] = numToChar(0);
            return;
        }

        if(d<0){
            negative = true;
            d = -d;
        }

        int temp = d;
        size = 0;
        while (temp > 0) {
            size++;
            temp /= b;
        }

        digits = new char[size];

        temp = d;
        for (int i = 0; i <size; ++i) {
            digits[i] = numToChar(temp % b);
            temp /= b;
        }
    }
    
    BigInteger(const BigInteger &other) : base(other.base), size(other.size) {
        digits = new char[other.size];
        for (int i=0; i<size; ++i){
            digits[i] = other.digits[i];
        }
    }

    ~BigInteger() {
        delete[] digits;
    }

    int num_digits() {
        return size;
    }

    bool add_digit(int n){
        if (n > base){
            throw std::out_of_range("Number should be between 0 and the base.");
        }
        
        char* temp = new char[size+1];
        
        temp[0] = numToChar(n);
        
        for (int i=1; i<size+1; ++i){
            temp[i] = digits[i-1]; 
        }
        
        delete[] digits;
        digits = temp;
        temp = NULL;
        size++;

        return true;
    }

    bool remove_digit() {
        char* temp = new char[size-1];
        for (int i=0; i<size-1; ++i){
            temp[i] = digits[i];
        }
        delete[] digits;
        digits = temp;
        temp = NULL;
        size--;

        return true;
    }

    bool insert_digit(int index, int n) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of range");
        }

        char* temp = new char[size + 1];

        for (int i = 0; i < index; ++i) {
            temp[i] = digits[i];
        }
        temp[index] = numToChar(n);

        for (int i = index; i < size; ++i) {
            temp[i + 1] = digits[i];
        }

        delete[] digits;
        digits = temp;
        size++;

        return true;
    }

    int toDecimal() const {
        int result = 0;
        for (int i=0; i<size; ++i){
            int digitValue = (digits[i] >= '0' && digits[i] <= '9') ? digits[i] - '0' : digits[i] - 'A' + 10;
            result += digitValue*(pow(static_cast<int>(base), i));
        }

        if(negative){
            result = result*(-1);
        }

        return result;
    }

    char operator[](int index) const {
        if (index <0 || index>= size){
            throw std::out_of_range("Index out of range");
        }
        return digits[index];
    }
    char& operator[](int index){
        if (index <0 || index >= size){
            throw std::out_of_range("Index out of range");
        }
        return digits[index];
    }
    
    bool operator==(const BigInteger &b) const {
        return this->toDecimal() == b.toDecimal();
    }
    bool operator>(const BigInteger &b) const {
        return this->toDecimal() > b.toDecimal();
    }
    bool operator<(const BigInteger &b) const {
        return this->toDecimal() < b.toDecimal();
    }
    bool operator>=(const BigInteger &b) const {
        return (this->toDecimal() > b.toDecimal()) || (this->toDecimal() == b.toDecimal());
    }
    bool operator<=(const BigInteger &b) const {
        return (this->toDecimal() < b.toDecimal()) || (this->toDecimal() == b.toDecimal());
    }
    bool operator!=(const BigInteger &b) const {
        return this->toDecimal() != b.toDecimal();
    }
    
    BigInteger& operator=(const BigInteger &b){   
        if (this == &b){
            return *this;
        }

        delete[] digits;
        base = b.base;
        size = b.size;

        digits = new char[size];
        for (int i=0; i< size; ++i){
            digits[i] = b.digits[i];
        }
        negative = b.negative;
        return *this;
    }
    BigInteger operator+(const BigInteger &b) const {
        int result = this->toDecimal() + b.toDecimal();
        return BigInteger(result, this->base);
    }
    BigInteger operator-(const BigInteger &b) const {
        int result = this->toDecimal() - b.toDecimal();
        return BigInteger(result, this->base);
    }
    BigInteger operator*(const BigInteger &b) const {
        int result = this->toDecimal() * b.toDecimal();
        return BigInteger(result, this->base);
    }
    BigInteger operator/(const BigInteger &b) const {
        int d1 = this->toDecimal();
        int d2 = b.toDecimal();

        if (d2 == 0) {
            throw std::runtime_error("Division by zero");
        }
        
        int rest = d1 / d2;

        return BigInteger(rest, this->base);
    }
    BigInteger operator%(const BigInteger &b) const {
        int d1 = this->toDecimal();
        int d2 = b.toDecimal();

        if (d2 == 0) {
            throw std::runtime_error("Division by zero");
        }
        
        int res = d1 % d2;

        return BigInteger(res, this->base);
    }

    BigInteger& operator++(){
        int val = this->toDecimal() + 1;
        *this = BigInteger(val, this->base);
        return *this;
    }
    BigInteger operator++(int){
        BigInteger temp = *this;
        ++(*this);
        return temp;
    }
    BigInteger& operator--(){
        int val = this->toDecimal() - 1;
        *this = BigInteger(val, this->base);
        return *this;
    }
    BigInteger operator--(int){
        BigInteger temp = *this;
        --(*this);
        return temp;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const BigInteger& b) {
        os << "(";

        if (b.negative) {
            os << "-";
        }
    
        for (int i = (b.size-1); i >= 0; --i) {
            os << b.digits[i];
        }
        os << ") with base of "<< static_cast<int>(b.base);
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, BigInteger& b){
        int val;
        int bas;
        is>>val;
        is>>bas;

        if(bas<2 || bas> 36){
            std::cerr <<"Invalid base";
            bas = 2;
        }

        b = BigInteger(val, bas);
        return is;
    }
};



int main(){
    std::cout << "Testing Constructor with Positive and Negative values, and the num_digits function." << std::endl;
    std::cout << "------------------------\n";
    BigInteger val1(12, 2);
    BigInteger val2(-215, 2);
    BigInteger val3(2351, 16);
    
    std::cout << "val1 = " << val1 << " , num_digits = " << val1.num_digits() << std::endl;
    std::cout << "val2 = " << val2 << " , num_digits = " << val2.num_digits() << std::endl;
    std::cout << "val3 = " << val3 << " , num_digits = " << val3.num_digits() << std::endl;

    std::cout << "\nTesting add_digit, remove digit and insert_digit function." << std::endl;
    std::cout << "-----------------------\n";
    std::cout << "add_digit function:\n";
    val1.add_digit(1);
    std::cout << "val1 = " << val1 << " , num_digits = " << val1.num_digits() << std::endl;

    std::cout << "\nremove_digit function:\n";
    val1.remove_digit();
    std::cout << "val1 = " << val1 << " , num_digits = " << val1.num_digits() << std::endl;

    std::cout << "\ninsert_digit function:\n";
    val1.insert_digit(2, 1);
    std::cout << "val1 = " << val1 << " , num_digits = " << val1.num_digits() << std::endl;
    val3.insert_digit(1, 10);
    std::cout << "val3 = " << val3 << " , num_digits = " << val3.num_digits() << std::endl;

    std::cout << "\nTesting operator[]." << std::endl;
    std::cout << "-----------------------\n";
    std::cout << "Number at position 1 in val1 " << val1[1] << std::endl;
    std::cout << "Number at position 2 in val3 " << val3[2] << std::endl;
    val1[1] = '1';
    val3[2] = 'B';
    std::cout << "\nAfter modifications:" << std::endl;
    std::cout << "Number at position 1 in val1 " << val1[1] << std::endl;
    std::cout << "Number at position 2 in val3 " << val3[2] << std::endl;

    std::cout << "\nTesting ==, >, <, >=, <= and != operators." << std::endl;
    std::cout << "-----------------------\n";
    BigInteger val4(25,3);
    BigInteger val5(-26,7);
    BigInteger val6(25, 2);

    std::cout << "val4 = " << val4 << " with decimal value of " << val4.toDecimal() << std::endl;
    std::cout << "val5 = " << val5 << " with decimal value of " << val5.toDecimal() << std::endl;
    std::cout << "val6 = " << val6 << " with decimal value of " << val6.toDecimal() << std::endl;

    std::cout << "val4 == val5: " << (val4 == val5 ? "true" : "false") << std::endl;
    std::cout << "val4 == val6: " << (val4 == val6 ? "true" : "false") << std::endl;
    std::cout << "\n";
    std::cout << "val4 > val5: " << (val4 > val5 ? "true" : "false") << std::endl;
    std::cout << "val5 > val6: " << (val5 > val6 ? "true" : "false") << std::endl;
    std::cout << "\n";
    std::cout << "val4 < val5: " << (val4 < val5 ? "true" : "false") << std::endl;
    std::cout << "val5 < val6: " << (val5 < val6 ? "true" : "false") << std::endl;
    std::cout << "\n";
    std::cout << "val4 >= val5: " << (val4 >= val5 ? "true" : "false") << std::endl;
    std::cout << "val4 >= val6: " << (val4 >= val6 ? "true" : "false") << std::endl;
    std::cout << "\n";
    std::cout << "val4 <= val5: " << (val4 <= val5 ? "true" : "false") << std::endl;
    std::cout << "val4 <= val6: " << (val4 <= val6 ? "true" : "false") << std::endl;
    std::cout << "\n";
    std::cout << "val4 != val5: " << (val4 != val5 ? "true" : "false") << std::endl;
    std::cout << "val4 != val6: " << (val4 != val6 ? "true" : "false") << std::endl;
    
    std::cout << "\nTesting = operator." << std::endl;
    std::cout << "------------------------\n";
    std::cout << "val4 = " << val4 << " with decimal value of " << val4.toDecimal() << std::endl;
    std::cout << "val5 = " << val5 << " with decimal value of " << val5.toDecimal() << std::endl;
    std::cout << "\nAfter modification:" << std::endl;
    val4 = val5;
    std::cout << "val4 = " << val4 << " with decimal value of " << val4.toDecimal() << std::endl;
    std::cout << "val5 = " << val5 << " with decimal value of " << val5.toDecimal() << std::endl;

    std::cout << "\nTesting +, -, *, / and % operators." << std::endl;
    std::cout << "-----------------------\n";
    BigInteger res;
    BigInteger num1(10, 3);
    BigInteger num2(5, 4);
    BigInteger num3(13, 4);
    std::cout << "num1 = " << num1 << " with decimal value of " << num1.toDecimal() << std::endl;
    std::cout << "num2 = " << num2 << " with decimal value of " << num2.toDecimal() << std::endl;
    std::cout << "num3 = " << num3 << " with decimal value of " << num3.toDecimal() << std::endl;
    res = num1+num2;
    std::cout << "num1 + num2 = " << res << ", decimal value of res is " << res.toDecimal() << std::endl;
    res = num1-num2;
    std::cout << "num1 - num2 = " << res << ", decimal value of res is " << res.toDecimal() << std::endl;
    res = num1*num2;
    std::cout << "num1 * num2 = " << res << ", decimal value of res is " << res.toDecimal() << std::endl;
    res = num1/num2;
    std::cout << "num1 / num2 = " << res << ", decimal value of res is " << res.toDecimal() << std::endl;
    res = num3%num2;
    std::cout << "num3 % num2 = " << res << ", decimal value of res is " << res.toDecimal() << std::endl;
    
    std::cout << "\nTesting ++ and -- operators." << std::endl;
    std::cout << "-----------------------\n";
    std::cout << "num1 = " << num1 << " with decimal value of " << num1.toDecimal() << std::endl;
    std::cout << "num2 = " << num2 << " with decimal value of " << num2.toDecimal() << std::endl;
    num1++;
    num2--;
    std::cout << "\nAfter modifications:" << std::endl;
    std::cout << "num1 = " << num1 << " with decimal value of " << num1.toDecimal() << std::endl;
    std::cout << "num2 = " << num2 << " with decimal value of " << num2.toDecimal() << std::endl;
    --num1;
    ++num2;
    std::cout << "\nAfter second modifications:" << std::endl;
    std::cout << "num1 = " << num1 << " with decimal value of " << num1.toDecimal() << std::endl;
    std::cout << "num2 = " << num2 << " with decimal value of " << num2.toDecimal() << std::endl;

    std::cout << "\nTesting >> operator." << std::endl;
    std::cout << "-----------------------\n";
    BigInteger val7;
    std::cout << "Please enter a number followed by a base (base should be between 2 and 36): " << std::endl;
    std::cin >> val7;
    std::cout << "The value you entered is " << val7 << " with decimal value of " << val7.toDecimal() << std::endl;

    return 0;
}
