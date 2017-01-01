/*
#######################
Author: Hristo Gatsinski
Date: 18.12.2016
Notes: To compile the source code via `g++` use -std=c++0x or -std=c++11
#######################
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include "custom_validators.h"

using namespace std;


class Student {
    private:
        string name;
        unsigned int faculty_number;
        unsigned short int group;
        unsigned short int course;
    public:
        Student();
        Student(string name, unsigned int faculty_number, unsigned short int group, unsigned short int course);
        ~Student();
        string getName();
        unsigned int getFacultyNumber();
        unsigned short int getGroup();
        unsigned short int getCourse();
        void setName(string name);
        void setFacultyNumber(unsigned int faculty_number);
        void setGroup(unsigned short int group);
        void setCrourse(unsigned short int course);
};


Student::Student() {
    do {
        cout << "Enter name:" << endl;
        cin >> name;

        if (validateName(name)) { break; }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid input" << endl;
    } while (true);

    do {
        cout << "Enter faculty number:" << endl;
        cin >> faculty_number;

        if (cin.good()) { break; }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid input" << endl;
    } while (true);

    do {
        cout << "Enter group:" << endl;
        cin >> group;

        if (cin.good()) { break; }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid input" << endl;
    } while (true);

    do {
        cout << "Enter course:" << endl;
        cin >> course;

        if (cin.good()) { break; }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid input" << endl;
    } while (true);

}


Student::Student(string name, unsigned int faculty_number, unsigned short int group, unsigned short int course) {
    this->name = name; this->faculty_number = faculty_number; this->group = group; this->course = course;
}


Student::~Student() {
   cout << "The student has been removed." << endl;
}

// Some GET and SET methods
string Student::getName() { return this->name; }
unsigned int Student::getFacultyNumber() { return this->faculty_number; }
unsigned short int Student::getGroup() { return this->group; }
unsigned short int Student::getCourse() { return this->course; }
void Student::setName(string name) { this->name=name; }
void Student::setFacultyNumber(unsigned int faculty_number) { this->faculty_number=faculty_number; }
void Student::setGroup(unsigned short int group) { this->group=group; }
void Student::setCrourse(unsigned short int course) { this->course=course; }


/**
    Grade class that inherits Student
*/
class Grade: public Student {
    private:
        double* grades;
    public:
        Grade();
        Grade(double* grades, string name, unsigned int faculty_number, unsigned short int group, unsigned short int course);
        ~Grade();
        double* getGrades();
        double getAverageGrade();
        void save();
        friend std::ostream& operator<< (std::ostream &out, const Grade &grade);
};

Grade::Grade() {
    unsigned short int course = getCourse();
    unsigned short int number_of_grades = course * 5;
    grades = new double[number_of_grades];
    for(unsigned short int i = 0, k=1; i < number_of_grades; i++, k++) {
        do {
            cout << "Enter grade " << k << ":" << endl;
            cin >> grades[i];

            if (cin.good()) {
                if (validateGrade(grades[i])) { break; }
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Invalid input" << endl;
        } while (true);
    }
}

Grade::Grade(double* grades, string name, unsigned int faculty_number, unsigned short int group, unsigned short int course)
:Student(name, faculty_number, group, course) { this->grades = grades; }

Grade::~Grade() {
   cout << "The grade object has been removed." << endl;
}

double* Grade::getGrades() { return this->grades; }

/**
    Calculates the average grade of the student
*/
double Grade::getAverageGrade() {
    unsigned short int course = getCourse();
    unsigned short int number_of_grades = course * 5;
    double sum = 0;
    for(unsigned short int i = 0; i < number_of_grades; i++) {
        sum += this->grades[i];
    }
    return sum/number_of_grades;
}

/**
    Saves the grade object into the 'grades.dat' file
*/
void Grade::save() {
    // open a file in write mode.
    fstream outfile;
    outfile.open("grades.dat", fstream::out | fstream::app);

    string name = this->getName();
    unsigned int faculty_number = this->getFacultyNumber();
    unsigned short int group = this->getGroup();
    unsigned short int course = this->getCourse();
    double* grades = this->getGrades();
    unsigned short int number_of_grades = course * 5;

    outfile << endl << name << endl;
    outfile  << faculty_number << endl;
    outfile << group << endl;
    outfile << course << endl;
    for(unsigned short int i = 0; i < number_of_grades; i++) {
        if(i!=(number_of_grades-1)) {
            outfile << grades[i] << ";";
        } else {
            outfile << grades[i];
        }
    }
    outfile.close();
}

/**
    Overloading << operator to be able to print Grades
*/
std::ostream& operator<< (std::ostream &out, Grade &grade)
{
    string name = grade.getName();
    unsigned int faculty_number = grade.getFacultyNumber();
    unsigned short int group = grade.getGroup();
    unsigned short int course = grade.getCourse();
    double* grades = grade.getGrades();
    unsigned short int number_of_grades = course * 5;

    out << name << endl;
    out << faculty_number << endl;
    out << group << endl;
    out << course << endl << endl;

    for(unsigned short int i = 0; i < number_of_grades; i++) {
        if(i!=(number_of_grades-1)) {
            out << "[" << grades[i] << "], ";
        } else {
            out << "[" << grades[i] << "];" ;
        }
    }
	out << endl;
    return out;
}

/**
    Loads the grades from the file 'grades.dat'

    @return list of Grade objects
*/
list<Grade> loadGrades() {
    ifstream infile;
    infile.open("grades.dat"); 

    string name;
    unsigned int faculty_number;
    unsigned short int group, course, counter=0;
    double* grades;
	list<Grade> listOfItems;
	int size_counter = 0;

    while(!infile.eof()) {
        infile >> name;
        infile >> faculty_number;
        infile >> group;
        infile >> course;
        string grade_string;
        infile >> grade_string;

		grades = new double[course * 5];
        string delimiter = ";";

        size_t pos = 0;
        int i = 0;
        string token;
        while ((pos = grade_string.find(delimiter)) != string::npos) {
            token = grade_string.substr(0, pos);
            grade_string.erase(0, pos + delimiter.length());
            grades[i] = stod(token);
            i++;
        }
        try {
            grades[i] = stod(grade_string);
        } catch (const invalid_argument& e) {
            cout << "Invalid argument" << endl;
        }
		Grade single_grade_object(grades, name, faculty_number, group, course);
		listOfItems.push_back(single_grade_object);
    }
    infile.close();
	return listOfItems;
}

/**
    Prints all avalibale data about the student with highest average grade
    in the selected group and course
*/
void getGroupHighestAverage(list<Grade>& grades, unsigned short int group, unsigned short int course){
    list<Grade>::iterator it;
    double highest = 0, current;
    string name;
    unsigned int faculty_number;

    for (it = grades.begin(); it!=grades.end();) {
        if (it->getGroup() == group && it->getCourse() == course) {
            current = it->getAverageGrade();
            if (current > highest) {
                highest = current;
                name = it->getName();
                faculty_number = it->getFacultyNumber();
            }
        }
        it++;
    }
    cout << "The student with the highest average grade in group " << group << " course " << course;
    cout << " is " << name << " with a faculty number " << faculty_number << "." << endl;
    cout << "His average grade is " << highest << "." << endl;
}

/**
    Prints all avaliable data about a student or about all students if faculty_number is 0
*/
void getStudentData(list<Grade>& grades, unsigned int faculty_number){
	list<Grade>::iterator it;
    if(faculty_number != 0)
	    cout << "Data for the student:" << endl;
    else
        cout << "Full list of sudents:" << endl;

    for (it = grades.begin(); it!=grades.end();) {
        if(faculty_number == 0) {
            cout<<*it;
        }
		else if(it->getFacultyNumber() == faculty_number){
			cout<<*it;
		}
        it++;
    }
    cout << endl << endl;
}

// Main function for the program
int main( ) {

    Grade new_grade;

    new_grade.save();

	list<Grade> listOfItems = loadGrades();

    getGroupHighestAverage(listOfItems, 34, 2);
    getStudentData(listOfItems, 3410682058);
    getStudentData(listOfItems, 0);

   return 0;
}