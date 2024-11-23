//Lab 10
//Exercice 4

#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

class Student {
public:
    string studentID;
    map<string, int> subjects; 

    Student(const string& id) : studentID(id) {}

    void updateScore(const string& subject, int score) {
        subjects[subject] = score;
    }

    int getScore(const string& subject) const {
        auto it = subjects.find(subject);
        if (it != subjects.end()) {
            return it->second;
        }
        return -1;
    }

    void display() const {
        cout << "Student ID: " << studentID << endl;
        for (const auto& subject : subjects) {
            cout << "  " << subject.first << ": " << subject.second << endl;
        }
    }
};

void addStudent(set<Student*>& students, const string& studentID) {
    for (const auto& student : students) {
        if (student->studentID == studentID) {
            cout << "Student with ID " << studentID << " already exists." << endl;
            return;
        }
    }

    students.insert(new Student(studentID));
    cout << "Student with ID " << studentID << " added." << endl;
}

Student* findStudent(set<Student*>& students, const string& studentID) {
    for (auto& student : students) {
        if (student->studentID == studentID) {
            return student;
        }
    }
    return nullptr;
}

// Main function
int main() {
    set<Student*> students;
    bool exit = false;
    int choice;

    while (!exit) {
        cout << "1. Add Student\n2. Update Student Score\n3. Display Student Record\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string studentID;
        string subject;
        int score;

        switch (choice) {
            case 1: {
                cout << "Enter student ID: ";
                cin >> studentID;
                addStudent(students, studentID);
                break;
            }
            case 2: {
                cout << "Enter student ID: ";
                cin >> studentID;
                Student* student = findStudent(students, studentID);
                if (student) {
                    cout << "Enter subject name: ";
                    cin >> subject;
                    cout << "Enter score: ";
                    cin >> score;
                    student->updateScore(subject, score);
                    cout << "Score updated." << endl;
                } else {
                    cout << "Student not found." << endl;
                }
                break;
            }
            case 3: {
                cout << "Enter student ID: ";
                cin >> studentID;
                Student* student = findStudent(students, studentID);
                if (student) {
                    student->display();
                } else {
                    cout << "Student not found." << endl;
                }
                break;
            }
            case 4: {
                exit = true;
                break;
            }
        }
    }

    for (auto student : students) {
        delete student;
    }

    return 0;
}
