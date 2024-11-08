//Lab 8
//Exercice 1

#include <iostream>

class Date{
private:
    int year;
    int month;
    int day;

public:
    Date(int d, int m, int y): day(d), month(m), year(y) {}

    void operator+(int n){
        day += n;
    }

    void operator-(int n){
        day -= n;
    }

    bool operator==(Date& other){
        return year==other.year && month==other.month && day==other.day;
    }

    bool operator<(Date& other){
        return year < other.year
            || (year==other.year && month<other.month)
            || (year==other.year && month>other.month && day<other.day);
    }

    bool operator>(Date& other){
        return year > other.year
            || (year==other.year && month>other.month)
            || (year==other.year && month==other.month && day>other.day);
    }

    void print(){
        std::cout<<day<<"/"<<month<<"/"<<year<<std::endl;
    }
};

void main(){
    Date date1(15, 5, 2023);
    Date date2(20, 6, 2024);
    Date date3(30, 5, 2023);
    Date date4(30, 5, 2023);

    date1.print();
    date2.print();
    date3.print();
    date4.print();

    date1+5;
    date2-2;

    date1.print();
    date2.print();

    std::cout<< "Is Date1 earlier than Date2? "<< std::boolalpha << (date1<date2) <<std::endl;
    std::cout<< "Is Date2 later than than Date3? "<< std::boolalpha << (date2>date4) <<std::endl;
    std::cout<< "Is Date3 same as Date4? "<< std::boolalpha << (date3==date4) <<std::endl;
}
