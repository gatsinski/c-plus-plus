#include <iostream>
using namespace std;

class Person {
    protected:
        char* name;
        char* id;
    public:
        Person(char* name, char* id) {
            this->name = name;
            this->id = id;
        }
        ~Person() {
            cout << "The person died" << endl;
        }
        // Some GET methods:
        char* get_name() { return this->name; }
        char* get_id() { return this->id; }
};

class Student:Person {
    protected:
        unsigned long int faculty_number;
        double grade;
    public:
        Student(char* name, char* id, unsigned long int faculty_number, double grade):Person(name, id) {
            this->faculty_number = faculty_number;
            this->grade = grade;
        }
        ~Student() {
            cout << "The student has graduated or left university" << endl;
        }
        void show() {
            cout << "This is a student called " << this->name << endl;
            cout << "His personal id is " << this->id << endl;
            cout << "His faculty number is " << this->faculty_number << endl;
            cout << "His average grade is " << this->grade << endl;
            if(this->grade > 4.5) {
                cout << "He is receiving scollarship" << endl;
            } else {
                cout << "He is not receiving scollarshiip" << endl;
            }
        }
        unsigned long int get_faculty_number() { return this->faculty_number; }
        double get_grade() { return this->grade; }
};

class PStudent:Student {
    public:
        PStudent(char* name, char* id, unsigned long int faculty_number, double grade):Student(name, id, faculty_number, grade){

        }
};

int main() {
    Person danny("Danny", "4285048650");
    cout << danny.get_name() << endl;
    Student chris("Chris", "5436326776", 121214024, 5.85);
    chris.show();
    return 0;
}

