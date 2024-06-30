/*
Name : Mohamed Aziz Zaghdoudi
Project Two
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Course {
public:
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;

    Course(string number, string title) : courseNumber(number), courseTitle(title) {}

    void addPrerequisite(string prerequisite) {
        prerequisites.push_back(prerequisite);
    }
};

vector<Course> loadCourses(const string& fileName) {
    vector<Course> courses;
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return courses;
    }

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string number, title, prereq;
        getline(ss, number, ',');
        getline(ss, title, ',');

        Course course(number, title);

        while (getline(ss, prereq, ',')) {
            course.addPrerequisite(prereq);
        }

        courses.push_back(course);
    }

    file.close();
    return courses;
}

void printCourses(const vector<Course>& courses) {
    vector<string> courseNumbers;
    for (const auto& course : courses) {
        courseNumbers.push_back(course.courseNumber);
    }

    sort(courseNumbers.begin(), courseNumbers.end());

    cout << "Here is a sample schedule:" << endl;
    for (const auto& number : courseNumbers) {
        for (const auto& course : courses) {
            if (course.courseNumber == number) {
                cout << course.courseNumber << ", " << course.courseTitle << endl;
                break;
            }
        }
    }
}

void printCourseInfo(const vector<Course>& courses, const string& courseNumber) {
    for (const auto& course : courses) {
        if (course.courseNumber == courseNumber) {
            cout << course.courseNumber << ", " << course.courseTitle << endl;
            cout << "Prerequisites: ";
            for (const auto& prereq : course.prerequisites) {
                cout << prereq;
                if (&prereq != &course.prerequisites.back()) {
                    cout << ", ";
                }
            }
            cout << endl;
            return;
        }
    }
    cout << "Course not found." << endl;
}

void displayMenu() {
    cout << "Welcome to the course planner." << endl;
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do? ";
}

int main() {
    vector<Course> courses;
    string fileName = "CS 300 ABCU_Advising_Program_Input.csv"; // default file name
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            courses = loadCourses(fileName);// Load the file
            if (!courses.empty()) {
                cout << "Courses loaded successfully." << endl;
            }
            break;
        case 2:
            if (courses.empty()) {
                cout << "No courses loaded. Please load the data structure first." << endl;
            }
            else {
                printCourses(courses);// Print the course list
            }
            break;
        case 3:
            if (courses.empty()) {
                cout << "No courses loaded. Please load the data structure first." << endl;
            }
            else {
                cout << "What course do you want to know about? ";
                cin >> fileName;
                transform(fileName.begin(), fileName.end(), fileName.begin(), ::toupper);
                printCourseInfo(courses, fileName); // Print specific course info
            }
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            return 0;
        default:
            cout << choice << " is not a valid option." << endl;
        }
    }
}
