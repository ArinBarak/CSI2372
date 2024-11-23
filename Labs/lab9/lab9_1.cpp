//Lab 9
//Exercice 1

#include <iostream>
#include <vector>
#include <algorithm>

class MyString {
private:
    std::vector<char> str;  
    size_t length;

public:
    MyString() : str(1, '\0'), length(0) {}

    MyString(const char* s) {
        if (s == nullptr) {
            str.push_back('\0');
            length = 0;
        } else {
            length = 0;
            while (s[length] != '\0') {
                length++;
            }
            str.resize(length + 1);  
            for (size_t i = 0; i < length; ++i) {
                str[i] = s[i];
            }
            str[length] = '\0';
        }
    }

    MyString(const MyString& other) : str(other.str), length(other.length) {}

    MyString(MyString&& other) noexcept : str(std::move(other.str)), length(other.length) {
        other.length = 0;
    }

    ~MyString() = default;

    MyString operator+(const MyString& other) const {
        MyString result;
        result.length = length + other.length;
        result.str.resize(result.length + 1);

        for (size_t i = 0; i < length; ++i) {
            result.str[i] = str[i];
        }
        for (size_t i = 0; i < other.length; ++i) {
            result.str[length + i] = other.str[i];
        }
        result.str[result.length] = '\0';
        return result;
    }

    bool operator==(const MyString& other) const {
        if (length != other.length) {
            return false;
        }
        for (size_t i = 0; i < length; ++i) {
            if (str[i] != other.str[i]) {
                return false;
            }
        }
        return true;
    }

    friend std::ostream& operator<<(std::ostream& os, const MyString& myStr) {
        os << myStr.str.data(); 
        return os;
    }

    size_t getLength() const {
        return length;
    }
};

struct CompareByLength {
    bool operator()(const MyString& a, const MyString& b) const {
        return a.getLength() < b.getLength();
    }
};

int main() {

    MyString str1("Hello");
    MyString str2("World");
    MyString str3("C++");

    MyString added = str1 + str2;
    std::cout << "Concatenated string: " << added << std::endl;

    if (str1 == str2) {
        std::cout << "str1 and str2 are equal!" << std::endl;
    } else {
        std::cout << "str1 and str2 are not equal!" << std::endl;
    }

    std::vector<MyString> strings = {str1, str2, str3, MyString("Goodbye")};

    std::sort(strings.begin(), strings.end(), CompareByLength());

    std::cout << "Sorted strings by length:" << std::endl;
    for (const auto& str : strings) {
        std::cout << str << " (Length: " << str.getLength() << ")" << std::endl;
    }

    return 0;
}
