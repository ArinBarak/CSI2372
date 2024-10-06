//student name: Arin Barak
//student number: 300280812
//LAB 4

#include <iostream>
#include <vector>
using namespace std;

//Exercice 1.A
class Course{
    int code;
    int hours;
public:
    Course(int c, int h): code(c), hours(h) {};
    int getNum() const {return code;};
    int getHours() const {return hours;};
};

//1.B
class Student{
    int id;
    int max_course_num;
    int taken_course_num;
    Course** courses;
    int* grades;
public:
    Student(const int s_id, int max)
        : id(s_id), max_course_num(max), taken_course_num(0) {
            courses = new Course*[max_course_num];
            grades = new int[max_course_num];
        };

    ~Student() {
        for (int i=0; i<taken_course_num; i++){
            delete courses[i];
        }
        delete[] courses;
        delete[] grades;
    };

    float average() {
        int sum =0;
        for (int i=0; i<taken_course_num; ++i){
            sum += grades[i];
        }
        return sum/taken_course_num;
    };

    int totalHours() {
        int total =0;
        for (int i=0; i<taken_course_num; ++i){
            total += courses[i]->getHours();
        }
        return total;
    };
    
    bool addCourse(Course* course, int grade){
        if (taken_course_num >= max_course_num){
            cout << "Can not add more courses.";
            return false;
        }
        else{
            courses[taken_course_num] = course;
            grades[taken_course_num] = grade;
            taken_course_num++;
            cout<< "Course added.";
            return true;
        }
    };
};

//Exercice 2
class SetInt{
private:
    int *elem;
    int size;
    bool containsAux (int n, int &p){
        for (int i = 0; i < size; ++i) {
            if (elem[i] == n) {
                p = i;
                return true;
            }
        }
        p = -1;
        return false;
    };
public:
    SetInt(): elem(NULL), size(0) {};
    
    SetInt(int arr[], int a_size): elem(nullptr), size(0){
        for (int i=0; i<a_size; i++){
            add(arr[i]);
        }
    };
    
    ~ SetInt(){
        delete[] elem;
    };
    
    SetInt (const SetInt &other): size(other.size), elem(nullptr){
        if (size>0){
            elem = new int[size];
            for (int i=0; i<size; ++i){
                elem[i] = other.elem[i];
            }
        }
    }; // copy constructor
    
    void add(int val){
        if (!contains(val)) {
            int* n_elem = new int[size + 1];
            for (int i = 0; i < size; ++i) {
                n_elem[i] = elem[i];
            }
            n_elem[size] = val;
            delete[] elem;
            elem = n_elem; 
            size++; 
        }
    };
    
    void remove(int val){
        for (int i = 0; i < size; ++i) {
            if (elem[i] == val) {
                int* n_elem = new int[size - 1];
                for (int j = 0; j < i; ++j) {
                    n_elem[j] = elem[j];
                }
                for (int j = i + 1; j < size; ++j) {
                    n_elem[j - 1] = elem[j];
                }
                delete[] elem; // Free old memory
                elem = n_elem; // Update the pointer
                size--; // Decrease the size
                return;
            }
        }
    };
    
    bool contains(int val){
        for (int i = 0; i < size; ++i) {
            if (elem[i] == val) {
                return true;
            }
        }
        return false;
    };
    
    int nbElem(){
        return size;
    };
    
    int *tabElem(){
        if (size == 0) return nullptr;
        int* lst = new int[size];
        for (int i = 0; i < size; ++i) {
            lst[i] = elem[i];
        }
        return lst;
    };
};


//Exercice 3
int rain(vector<int>& r_map){
    int total = 0;

    for (int i=1; i<r_map.size(); i++){
        int left= r_map[i];
        for(int k=0; k<i; k++){
            if (r_map[k]>left){
                left =r_map[k];
            }
        }
        int right = r_map[i];
        for (int n=i+1; n<r_map.size(); n++){
            if (r_map[n]> right){
                right = r_map[n];
            }
        }

        if (left < right){
            total+= left - r_map[i];
        }else{
            total += right - r_map[i];
        }
    }

    return total;
}

//Exercice 4
int factorial(int x){
    if (x == 0){
        return 1;
    }
    else{
        return x*(factorial (x-1));
    }
}

int unique_path(int m, int n){
    int fact_m = factorial(m-1);
    int fact_n = factorial(n-1);
    int fact_mn = factorial(m+n-2);

    return (fact_mn)/((fact_m)*(fact_n));
}




void main(){
    vector<int> water{3,0,1,0,4,0,3}; //should return 11
    int water_num = rain(water);
    cout<< "total water is: "<< water_num;
}