//Lab 8
//Exercice 3

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Employee {
    int id;
    std::string name;
    std::string department;
public:
    Employee() : id(0), name(""), department("") {}

    Employee(int id, const std::string& name, const std::string& department)
        : id(id), name(name), department(department) {}
    
    std::string toString() const {
        std::ostringstream oss;
        oss << id<<", "<<name << ", " << department;
        return oss.str();
    }

    static Employee fromString(const std::string & str){
        std::istringstream iss(str);
        std::string token;
        int id;
        std::string name,department;

        std::getline(iss,token, ',');
        id = std::stoi(token);
        std::getline(iss, name, ',');
        std::getline(iss, department, ',');

        return Employee(id, name, department);
    }

    friend void updateEmployeeDep(Employee& employee, const std::string& ndepartment);
    
    friend Employee* findEmployeebyID(std::vector<Employee>& employees, int id);
};

void updateEmployeeDep(Employee& employee, const std::string& ndepartment){
        employee.department = ndepartment;
        std::cout << "Department updated successfully."<<std::endl;
    }

void readEmployeesFromFile(const std::string& filename, std::vector<Employee>& employees){
    std::ifstream file(filename);
    if (!file.is_open()){
        throw std::runtime_error("Cannot open file.");
    }

    std::string line;
    while (std::getline(file, line)){
        employees.push_back(Employee::fromString(line));
    }
    file.close();
}

void writeEmployeesToFile(const std::string& filename, const std::vector<Employee>& employees){
    std::ofstream file(filename);
    if (!file.is_open()){
        throw std::runtime_error("Cannot open file.");
    }

    for (const auto& employee : employees){
        file << employee.toString() << std::endl;
    }

    file.close();
}

Employee* findEmployeebyID(std::vector<Employee>& employees, int id){
    for (auto& employee : employees){
        if (employee.id == id){
            return &employee;
        }
    }

    return nullptr;
}

void main(){
    std::vector<Employee> employees;
    try {
        readEmployeesFromFile("employees.txt", employees);
    } catch (const std::exception& e){
        std::cerr << e.what() <<std::endl;
        return;
    }

    int idn;
    std::cout<< "Enter ID to search- ";
    std::cin>> idn; 
    Employee* employee = findEmployeebyID(employees, idn);

    if(employee){
        std::cout<<"Found employee- "<<employee->toString()<<std::endl;
        std::string ndep;
        std::cout<< "Enter new Department for the Employee- ";
        std::cin>>ndep; 
        updateEmployeeDep(*employee, ndep);
        std::cout <<"Updated employee: "<< employee->toString() << std::endl;
    } else {
        std::cout << "Employee with ID "<<idn <<" not found." << std::endl;
    }

    try {
        writeEmployeesToFile("employees.txt", employees);
    } catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
        return;
    }
}
