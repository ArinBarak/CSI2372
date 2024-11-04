//lab 6
//Exercice 3

#include <iostream>
#include <iomanip>
using namespace std;

template<typename From, typename To>
struct UnitConverter;

template<>
struct UnitConverter<int, double>{
    static double convert(int value) {
        return value / 100.0;
    }
};

template<>
struct UnitConverter<double, double>{
    static double convert(double value) {
        return value * 100;
    }
};

template<>
struct UnitConverter<double, int>{
    static int convert(int value) {
        return static_cast<int>(value * 100.0);
    }
};

template<>
struct UnitConverter<int, int>{
    static int convert(int value) {
        return value * 100.0;
    }
};

void help_convert(){
    double value;
    string from, to;

    cout <<"Enter the value to convert: ";
    cin>> value;
    cout<<"Convert from (cm, m): ";
    cin>>from;
    cout<<"Convert to (cm, m): ";
    cin>>to;

    if (from == "cm" && to=="m"){
        double result = UnitConverter<int,double>::convert(value);
        cout << fixed << setprecision(2) << value << " cm is " << result << " m" << endl;
    } else if (from == "m" && to == "cm") { 
        double result = UnitConverter<double, double>::convert(value);
        cout << fixed << setprecision(2) << value << " m is " << result << " cm" << endl;
    } else {
        cout << "Invalid conversion units provided."<<endl; 
    }
}

void main(){
    help_convert();
}