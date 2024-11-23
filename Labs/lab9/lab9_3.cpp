//Lab 9
//Exercice 3

#include <iostream>
#include <vector>
#include <functional>

template <typename T>
class Container {
private:
    std::vector<T> data; 

public:
    Container(std::initializer_list<T> init) : data(init) {}

    class Iterator {
    private:
        typename std::vector<T>::iterator iter; 

    public:
        Iterator(typename std::vector<T>::iterator start) : iter(start) {}

        Iterator& operator++() {
            ++iter;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++iter;
            return temp;
        }

        Iterator& operator--() {
            --iter;
            return *this;
        }

        T& operator*() {
            return *iter;
        }

        bool operator!=(const Iterator& other) const {
            return iter != other.iter;
        }

        bool operator==(const Iterator& other) const {
            return iter == other.iter;
        }
    };

    Iterator begin() {
        return Iterator(data.begin());
    }

    Iterator end() {
        return Iterator(data.end());
    }

    void forEach(std::function<void(T&)> func) {
        for (auto& elem : data) {
            func(elem);
        }
    }

    void display() const {
        for (const auto& elem : data) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
};

int main() {

    Container<int> container = {1, 2, 3, 4, 5};

    std::cout << "Original container: ";
    container.display();

    container.forEach([](int& x) {
        x *= 2;
    });

    std::cout << "After multiplying by 2: ";
    container.display();

    std::cout << "Using custom iterator: ";
    for (auto it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    container.forEach([](int& x) {
        x += 10;
    });

    std::cout << "After adding 10: ";
    container.display();

    return 0;
}
