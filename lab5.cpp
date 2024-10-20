//LAB 5
//Arin Barak
//300280812

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

//Exercice 1
class MathLib{
public:
    static inline string square_root(double num){
        try{
            if (num < 0){
                throw invalid_argument("Negative input provided.");
            }
            double res = sqrt(num);
            return "Square root of "+to_string(num)+" is "+to_string(res)+".";
        }
        catch (const invalid_argument& e){
            return "Error: "+ string(e.what());
        }
    }

    static inline string logarithm(double num){
        try{
            if (num < 0){
                throw invalid_argument("Negative input provided.");
            }
            double res = log10(num);
            return "Logarithm of "+to_string(num)+" is "+to_string(round(res*100) / 100.0)+".";

        }
        catch (exception& e){
            cout<< "Error: Negative input provided.";
        }
    }
};

//Exercice 2
class User{
    string username;
    string id;
    string access;
    static int counter;
public: 
    User(){counter = 0;}

    User(const string& name, const string& s_id, const string& level): username(name), id(s_id), access(level){
        counter++;
    }

    ~User(){
        counter--;
    }

    static int getUserNum(){
        return counter;
    }

    friend bool compare(const User& user1, const User& user2);
};

int User::counter = 0;

bool compare(const User& user1, const User& user2){
    cout<< "Comparing users: ";
    cout<< "Username: "<< user1.username << ", ID: "<<user1.id<<", Access Level: "<< user1.access<<endl;
    cout<< "Username: "<< user2.username << ", ID: "<<user2.id<<", Access Level: "<< user2.access<<endl;
    return user1.access == user2.access;
}

//Exercice 3
class SportsTeam {
private:
    string name;
    int win; 
    int loss;
    int draw;
    static int totalTeams;

public:
    SportsTeam(string n, int w, int l, int d) : name(move(n)), win(w), loss(l), draw(d) {
        totalTeams++;
    }

    ~SportsTeam() {
        totalTeams--;
    }

    static int getTotalTeams() {
        return totalTeams;
    }

    double getWinPercentage() const {
        int totalGames = win + loss + draw;
        return totalGames > 0 ? static_cast<double>(win) / totalGames * 100 : 0.0;
    }

    friend bool operator<(const SportsTeam& a, const SportsTeam& b);
    friend bool operator>(const SportsTeam& a, const SportsTeam& b);

    void display() const {
        cout << name << ": Wins: " << win << ", Losses: " << loss << ", Draws: " << draw << ", Win%: " << getWinPercentage() <<endl;
    }
};

int SportsTeam::totalTeams = 0;

bool operator<(const SportsTeam& a, const SportsTeam& b) {
    return a.getWinPercentage() < b.getWinPercentage();
}

bool operator>(const SportsTeam& a, const SportsTeam& b) {
    return a.getWinPercentage() > b.getWinPercentage();
}

//Exercice 4
class Shape {
public:
    virtual void draw() const = 0;
    virtual double area() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
    double radius;
public:
    Circle(double radius) : radius(radius) {}

    void draw() const override {
        cout << "Drawing a circle." << endl;
    }

    double area() const override {
        return 3.14* radius * radius;
    }

    void setRadius(double newRadius) {
        radius = newRadius;
    }
};

class Rectangle : public Shape {
    double width, height;
public:
    Rectangle(double width, double height) : width(width), height(height) {}

    void draw() const override {
        cout << "Drawing a rectangle." <<endl;
    }

    double area() const override {
        return width * height;
    }
};

void modifyRadius(Shape* shape, double newRadius) {
    Circle* circle = dynamic_cast<Circle*>(shape);
    if (circle) {
        circle->setRadius(newRadius);
    } else {
        cout << "Shape is not a circle." <<endl;
    }
}

void main(){
    //Exercice 1 Example
    cout<< "Exercice 1 Example\n\n";
    cout<< MathLib::square_root(16)<<endl;
    cout<< MathLib::square_root(-1)<<endl;
    cout<< MathLib::logarithm(10)<<endl;

    //Exercice 2 Example
    cout<< "\n Exercice 2 Example";
    int n;
    cout<< "How many user would you like to enter? ";
    cin >> n;

    User* users = new User[n];

    string name, id, level;
    for (int i=0; i<n; i++){
        cout<< "Enter details for user "<<i+1<<":"<<endl;
        cout<< "Username: ";
        cin>> name;
        cout<< "ID:";
        cin>> id;
        cout<< "Access Level:";
        cin>> level;

        users[i] = User(name, id, level);
    }

    cout << "Total users: "<< User::getUserNum()<< endl;

    string ans;
    cout <<"Would you like to compare access levels between two users? (y/n): ";
    cin >> ans;
    if (ans == "y"){
        cout << "Enter the indices of the two users to compare (1-"<<n<<") : "<<endl;
        int a,b;
        cout << "First user index: ";
        cin>> a;
        cout<< "Second user index: ";
        cin>> b;
        bool res = compare(users[a-1], users[b-1]);
        cout<<"Do they have the same access level? ";
        if (res){
            cout<<"Yes";
        }else{
            cout<< "No";
        }
    }

    delete[] users;

    //Exercice 3 Example
    cout<< "Exercice 3 Example\n\n";
    vector<SportsTeam> teams;
    string name;
    int w, l, d;
    int num;
    cout << "Enter the number of teams: ";
    cin >> num;

    for (int i = 0; i < num; i++) {
        cout << "Enter team " << i + 1 << " name: ";
        cin >> name;
        cout << "Enter wins: ";
        cin >> w;
        cout << "Enter losses: ";
        cin >> l;
        cout << "Enter draws: ";
        cin >> d;

        teams.emplace_back(name, w, l, d);
    }

    sort(teams.begin(), teams.end(), greater<SportsTeam>());
    cout << "\nTeams sorted by winning percentage:" << endl;
    for (const auto& team : teams) {
        team.display();
    }

    //Exercice 4 Example
    cout<< "Exercice 4 Example\n\n";
    int type;
    cout << "Choose a shape to create:\n 1. Circle\n 2. Rectangle \nEnter your choice (1 or 2): ";
    cin >> type;
    Shape* shape = nullptr;
    if (type == 1) {
        double radius;
        cout << "Enter the radius of the circle: ";
        cin >> radius;
        shape = new Circle(radius);
    } else if (type == 2) {
        double width, height;
        cout << "Enter the width and height of the rectangle: ";
        cin >> width >> height;
        shape = new Rectangle(width, height);
    } else {
        cout << "Invalid choice." <<endl;
        return;
    }

    shape->draw();
    cout << "Area of the shape: " << shape->area() << endl;
    if (Circle* circle = dynamic_cast<Circle*>(shape)) {
        double newRadius;
        cout << "Enter a new radius for the circle: ";
        cin >> newRadius;
        modifyRadius(shape, newRadius);
        circle->draw();
        cout << "Updated area of circle: " << circle->area() <<endl;
    } else {
        cout << "The shape is a rectangle. No radius modification needed." << endl;
    }
    delete shape;
}