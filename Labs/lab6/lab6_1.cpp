//lab 6, Exercice 1

#include <iostream>
using namespace std;

//Exercice 1
class Employee{
    string name;
public:
    virtual double calculateBonus() const = 0;
    virtual void print() const;
};

class Manager : public Employee{
public:
    string name;
    int num_of_projects;

    Manager(string n) : name(n){};
    Manager(string n, int p) : name(n), num_of_projects(p) {};
    double calculateBonus() const override {
        return 500*num_of_projects;
    }
    void print() const override{
        cout<<"Manager " << name<< " has a bnous of $"<< calculateBonus();
    }

};

class Developer : public Employee{
public:
    string name;
    int num_of_codelines;

    Developer(string n) : name(n) {};
    Developer(string n, int lines) : name(n), num_of_codelines(lines) {};
    double calculateBonus() const override{
        return (0.05)*num_of_codelines;
    }
    void print() const override{
        cout<<"Developer " << name<< " has a bnous of $"<< calculateBonus();
    }
};


void main(){
    //Exercice 1
    cout<<"Exercice 1\n"<<endl;
    string name;
    int projects;
    cout<<"Enter Manager's Name: ";
    cin>> name;
    cout<<"Enter number of projects managed: ";
    cin>> projects;
    Manager employee1 = Manager(name, projects);

    string name2;
    int lines;
    cout<<"Enter Developer's Name: ";
    cin>> name2;
    cout<<"Enter number of lines of code written: ";
    cin>> projects;
    Developer employee2 = Developer(name2, lines);
    
    employee1.print();
    employee2.print();

    
}
