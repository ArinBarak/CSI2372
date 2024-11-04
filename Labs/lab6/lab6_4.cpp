//lab 6
//Exercice 4

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Vehicle {
public:
    virtual ~Vehicle() = default;
    virtual void showDetails() const = 0;
};

class Car : public Vehicle {
    string model;
public:
    Car(const string& model): model(model){}

    void showDetails() const override {
        cout<< "Car Model: " << model;
    }
};

class Truck : public Vehicle {
    string model;
    int load;
public:
    Truck(const string& model, int load): model(model), load(load){}

    void showDetails() const override {
        cout<< "Truck Model: "<< model<< ", Load Capacity: "<< load << " tons."<< endl;
    }

    int getLoad() const{
        return load;
    }
};

template <typename T>
class Fleet{
    vector<shared_ptr<T>> vehicles;
public:
    void addVehicle(shared_ptr<T> vehicle){
        vehicles.push_back(vehicle);
    }

    void removeVehicle(shared_ptr<T> veh){
        vehicles.erase(remove(vehicles.begin(), vehicles.end(), vehicle), vehicles.end());
    }

    void showDetails() const {
        for (const auto& vehicle : vehicles){
            vehicle->showDetails();
        }
    }
};

template<>
class Fleet<Truck>{
    vector<shared_ptr<Truck>> vehicles;
public:
    void addVehicle(shared_ptr<Truck> vehicle){
        vehicles.push_back(vehicle);
    }

    void removeVehicle(std::shared_ptr<Truck> vehicle) { 
        vehicles.erase(std::remove(vehicles.begin(), vehicles.end(), vehicle), vehicles.end());
    }
    
    void showDetails() const { 
        for (const auto& vehicle : vehicles) { 
            vehicle->showDetails(); 
            } 
    }

    int calculateTotal() const {
        int total = 0;
        for (const auto& truck : vehicles){
            total += truck->getLoad();
        }
        return total;
    }
};

void main(){
    Fleet<Car> cars;
    Fleet<Truck> trucks;
    int c;
    while(true){
        cout<< "Choose an option: "<<endl;
        cout<< "1. Add Car\n2. Add Truck\n3. Show Fleet Details\n4. Exit"<<endl;
        cin>> c;

        switch (c){
            case 1:{
                string model;
                cout<< "Enter Car Model: ";
                cin>> model;
                cars.addVehicle(make_shared<Car>(model));
                break;
            }
            case 2:{
                string model;
                int load;
                cout<< "Enter Truck Model: ";
                cin>> model;
                cout<<"Enter Load Capacity: ";
                cin>> load;
                trucks.addVehicle(make_shared<Truck>(model, load));
                break;
            }
            case 3:{
                cout<< "Car Fleet Details:"<<endl;
                cars.showDetails();
                cout<<"Truck Fleet Details:"<<endl;
                trucks.showDetails();
                cout<<"Total Truck Load Capacity: "<< trucks.calculateTotal()<< endl;
                break;
            }
            case 4:
                return;
        }
    }
}