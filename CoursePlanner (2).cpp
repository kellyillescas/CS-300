// CoursePlanner.cpp
// Author: Kelly Illescas
// October 13, 2021

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

//Creating course info structure
struct Course {
    string courseNumber;
    string courseName;
    string p1; //course prerequisite 1
    string p2; //course prerequisite 2
    string p3; //course prerequisite 3
    string p4; //course prerequisite 4

    //Default Constructor
    Course() {
        courseNumber = "";
        courseName = "";
        p1 = "";
        p2 = "";
        p3 = "";
        p4 = "";
    }
};

//Code for reading course file
//Creating vector to store courses
vector<Course> readFile(string filePath) {
    ifstream inFS;
    vector<string> fileLines;
    vector<Course> courses;
    vector<Course> errorCourse;
    string tempStr;

    cout << "Opening file " << filePath << endl;
    inFS.open(filePath); //opening file

    if (!(inFS.is_open())) {
        cout << "Could not open file. Please try again. " << filePath << endl;
        return errorCourse;
    }
    else {
        cout << filePath << "File opened successfully." << endl;
    }

    //While loop to store courses in vector
    while (!inFS.eof()) {
        getline(inFS, tempStr);
        fileLines.push_back(tempStr);
    }

    //Iterating over each line
    for (int i = 0; i < fileLines.size(); i++) {
        char currChar = 0;
        int location = 0;
        Course course; //Creating new course object

        //Iterating over each character in a line
        for (int j = 0; j < fileLines.at(i).size(); j++) {
            currChar = fileLines.at(i).at(j);
            if (currChar == ',') {
                location++;
                continue;
            }

            //Coding for cases to append characters to correct course (using location)
            switch (location) {
            case 0:
                course.courseNumber = course.courseNumber + currChar;
                break;

            case 1:
                course.courseName = course.courseName + currChar;
                break;

            case 2:
                course.p1 = course.p1 + currChar;
                break;

            case 3:
                course.p2 = course.p2 + currChar;
                break;

            case 4:
                course.p3 = course.p3 + currChar;
                break;

            case 5:
                course.p4 = course.p4 + currChar;
                break;
            }
        }
        courses.push_back(course); //Appending course to vector
    }
    return courses; //Returning vector
}

//Sorting courses in alphabetical order
void sortCourses(vector<Course> &courses) {
    int min = 0;

    //Loop for iterating through items, swapping courseNum for minimum courseNum
    for (int pos = 0; pos < courses.size(); pos++) {
        min = pos;

        for (int i = pos; i < courses.size(); i++) {
            if (courses.at(i).courseNumber < courses.at(min).courseNumber) {
                min = i;
            }
        }
        swap(courses.at(pos), courses.at(min));
    }
}

int main() {
    string filePath = "ABCU_Advising_Program_Input.txt";
    vector<Course> courses;
    int menuChoice = 0;

    //Creating menu
    while (menuChoice != 9) {
        cout << "Welcome to the course planner. Be sure to select number 1 to load the course list first. Please make a selection." << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do?" << endl;
        cin >> menuChoice;

        switch (menuChoice) {
        //Reading the file
        case 1: 
            courses = readFile(filePath);
            sortCourses(courses);
            cout << endl;
            break;

        //Outputting courses
        case 2:
            cout << endl << "Here is a sample schedule: " << endl << endl;
            for (int i = 0; i < courses.size(); i++) {
                cout << courses.at(i).courseNumber << ", " << courses.at(i).courseName << endl;
            }
            cout << endl;
            break;

        //Outputting specific course info
        case 3:
            string userCourse;
            
            bool found = false;
            cout << endl << "What course do you want to know about? " << endl;
            cin >> userCourse;

            for (int i = 0; i < courses.size(); i++) {
                if (userCourse.compare(courses.at(i).courseNumber) == 0) {
                    cout << endl << courses.at(i).courseNumber << ", " << courses.at(i).courseName << endl;
                    cout << "Prerequisite 1: " << courses.at(i).p1 << endl;
                    cout << "Prerequisite 2: " << courses.at(i).p2 << endl;
                    cout << "Prerequisite 3: " << courses.at(i).p3 << endl;
                    cout << "Prerequisite 4: " << courses.at(i).p4 << endl << endl;
                    found = true;
                    break;
                }
            }
            if (found == false) {
                cout << "That is not a valid course. Be sure to capitalize all letters in course. Please try again." << endl;
            }
            break;
        }
    }
    cout << endl << "Thank you for using the course planner!" << endl;
    return 0;
}

