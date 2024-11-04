//lab 6
//Exercice 2

#include <iostream>
using namespace std;

template <typename T, int N>
class IterativeSquare {
public:
    static T apply(T value){
        return IterativeSquare<T, N-1>::apply(value*value);
    }
};

template<typename T>
class IterativeSquare<T, 1>{
public: 
    static T apply(T value){
        return value*value;
    }
};

void main(){
    //Exercice 2
    cout<<"Exercice 2:" <<endl;

    int result = IterativeSquare<int, 2>::apply(2);
    cout<< "Result: "<< result << endl;

    int result2 = IterativeSquare<int, 3>::apply(2);
    cout<< "Result: "<< result2<< endl;

}