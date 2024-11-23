//Lab 10
//Exercice 1

#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Patient{
    string name;
    int severity;
    int order_of_arrival;

    Patient(string n, int s, int ooa) : name(n), severity(s), order_of_arrival(ooa) {}
};

bool operator<(const Patient& p1, const Patient& p2){
    if (p1.severity == p2.severity){
        return p1.order_of_arrival > p2.order_of_arrival;
    }

    return p1.severity<p2.severity;
}

int main(){
    std::priority_queue<Patient> patients;
    bool exit = false;
    int option = 0;
    int arrival = 0;

    while (!exit){
        cout<< "1. Add Patient\n2. Serve Patient\n3. Exit" << endl;
        cout<< "Enter your choice: ";
        cin >> option;

        switch (option){
            case 1:
                {string nam;
                int severity;
                cout << "Enter patient's name: ";
                cin >> nam;
                cout << "Enter patient's condition severity (1-10, with 10 beign most severe): ";
                cin >> severity;
                arrival++;
                Patient pat(nam, severity, arrival);
                patients.push(pat);
                cout << "Patient added: " << pat.name << " with severity "<< pat.severity<<endl;;
                break;
                }case 2:{
                while (!patients.empty()) {
                    const Patient& cp = patients.top();
                    cout << "Serving: " << cp.name << " with severity: " << cp.severity << endl;
                    patients.pop();
                }
                break;
                }case 3:{
                exit = true;
                break;
                }
        }
    }

    return 0;
}
