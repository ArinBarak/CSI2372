/*
Arin Barak
300280812
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//QUESTION 1
class Student {
    string name;
    int id;
public: 
    Student(string sname, int sid) : name(sname), id(sid) {}
    void Student_info();
};

void Student::Student_info() {
    string info = "Student name: " + name + "\nStudent ID: " + to_string(id);
    cout << info << endl;
}

void list_of_students() {
    vector<Student> student_list;

    student_list.emplace_back("John", 145);
    student_list.emplace_back("Emma", 944);
    student_list.emplace_back("Greg", 685);

    for (Student& student : student_list) {
        student.Student_info();
    }
}


//QUESTION 2
class Digital_Product {
public:
    int id;
    string content;
public:
    Digital_Product(int d_id, string d_content) : id(d_id), content(d_content) {}
};

class Digital_Diary {
    vector<Digital_Product*> diary;
public:
    ~Digital_Diary() {
        for (auto entry : diary) {
            delete entry;
        }
    }
    void addEntry(int e_id, string e_content);
    void deleteEntry(int e_id);
    void print_diary();
};

void Digital_Diary::addEntry(int e_id, string e_content) {
    Digital_Product* entry = new Digital_Product(e_id, e_content);
    diary.push_back(entry);
}

void Digital_Diary::deleteEntry(int e_id) {
    int n = 0;
    for (Digital_Product* product : diary) {
        if (product-> id == e_id) {
            delete product;
            diary.erase(diary.begin()+n);
            break;
        }
        n++;
    }
}

void Digital_Diary::print_diary() {
    for (Digital_Product* product : diary) {
        cout << "Product ID: " << product->id << ", Product content: " << product->content << endl;
    }
}


//QUESTION 3
class Animal {
public:
    string name;
    string type;
public:
    Animal(string a_name, string a_type) : name(a_name), type(a_type) {}
};

class Shelter {
    vector<Animal*> shelter_animals;
    vector<Animal*> housed_animals;
public:
    void addAnimal(string n, string t);
    void removeAnimal(string n);
    void displayHousedAnimals();
    void displayShelterAnimals();
};

void Shelter::addAnimal(string n, string t) {
    Animal* ani = new Animal(n, t);
    shelter_animals.push_back(ani);
}

void Shelter::removeAnimal(string n) {
    for (vector<Animal*>::iterator it = shelter_animals.begin(); it != shelter_animals.end(); ++it) {
        if ((*it)->name == n) {
            Animal* animal = new Animal((*it)->name, (*it)->type);
            housed_animals.push_back(animal);
            delete* it;
            shelter_animals.erase(it);
            break;
        }
    }
}

void Shelter::displayHousedAnimals() {
    cout << "Housed Animals" << endl;
    for (Animal* animal : housed_animals) {
        cout << "Animal name: " << animal->name << ", Animal type: " << animal->type << endl;
    }
}
void Shelter::displayShelterAnimals() {
    cout << "Shelter Animals" << endl;
    for (Animal* animal : shelter_animals) {
        cout << "Animal name: " << animal->name << ", Animal type: " << animal->type << endl;
    }
}

//QUESTION 4
int minCandies(vector<int> ratings) {
    const int len = ratings.size();
    vector<int> candies (len, 1);

    for (int i = 1; i < len; i++) {
        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }

    for (int i = len - 1; i > 0; i--) {
        if (ratings[i - 1] > ratings[i]) {
            candies[i - 1] = candies[i] + 1;
        }
    }

    int totalCandies = 0;
    for (int candy : candies) {
        totalCandies += candy;
    }

    cout << totalCandies;
    return totalCandies;
}

//QUESTION 5
class Color {
public:
    struct RGB {
        int r;
        int g;
        int b;
    };

    using rgb_values = struct RGB;

    Color(int r, int g, int b) : rgb{r, g, b} {}

    static Color blend(Color c1, Color c2) {
        int b_red = (c1.rgb.r + c2.rgb.r) / 2;
        int b_green = (c1.rgb.g + c2.rgb.g) / 2;
        int b_blue = (c1.rgb.b + c2.rgb.b) / 2;
        return Color(b_red, b_green, b_blue);
    }

    void displayColor() {
        cout << "R:" << rgb.r << " G:" << rgb.g << " B:" << rgb.b << endl;
    }

private:
    rgb_values rgb;
};

int main()
{
    //Q1 test
    //list_of_students();
    
    //Q2 test
    /*
    Digital_Diary diary;
    diary.addEntry(1, "a");
    diary.addEntry(2, "b");
    diary.addEntry(3, "c");
    diary.print_diary();
    diary.deleteEntry(3);
    diary.print_diary();
    */

    //Q3 test
    /*
    Shelter shelter;
    shelter.addAnimal("Plum", "dog");
    shelter.addAnimal("Daisy", "cat");
    shelter.addAnimal("Sun", "bird");
    shelter.displayShelterAnimals();
    shelter.removeAnimal("Plum");
    shelter.displayHousedAnimals();
    */
    
    //Q4 test
    /*
    vector<int> arr = {1,3,4,2,1,5,6 };
    minCandies(arr);
    */

    //Q5 test
    /*
    Color color1(100, 0, 0); 
    Color color2(0, 0, 100); 
    Color color3 = Color::blend(color1, color2);
    color3.displayColor();
    */
    return 0;
}
