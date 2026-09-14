#pragma once

#include "Grade.hpp"

#include <iostream>
#include <string>

namespace grading {

struct Course {
    std::string name;
    std::string code;
    int credits;

    Course();
    Course(const std::string& name, const std::string& code, int credits);
};

class Student {
private:
    std::string name;
    std::string studentID;
    Grade* grades;
    Course* courses;
    int gradeCount;
    int capacity;

    static int totalStudentsCreated;
    static int currentStudentCount;

    void resize();
    int findCourseIndex(const std::string& courseName) const;

public:
    Student();
    Student(const std::string& name, const std::string& studentID, int capacity = 2);
    Student(const Student& other);
    Student& operator=(const Student& other);
    ~Student();

    std::string getName() const;
    void setName(const std::string& newName);

    std::string getStudentID() const;
    int getGradeCount() const;
    int getCapacity() const;
    std::string getCourseName(int index) const;
    std::string getCourseCode(int index) const;
    int getCourseCredits(int index) const;

    void addGrade(const Grade& grade, const Course& course);
    void addGrade(const Grade& grade, const std::string& courseName);
    void removeGrade(int index);

    Grade& operator[](int index);
    const Grade& operator[](int index) const;

    Grade& operator[](const std::string& courseName);
    const Grade& operator[](const std::string& courseName) const;

    double operator()() const;
    double operator()(int count) const;
    double operator()(int start, int end) const;
    double operator()(int index, double weight) const;

    Student operator+(double bonus) const;
    Student operator*(double factor) const;

    Student& operator+=(double bonus);
    Student& operator*=(double factor);

    bool operator==(const Student& other) const;
    bool operator!=(const Student& other) const;
    bool operator<(const Student& other) const;
    bool operator>(const Student& other) const;
    bool operator<=(const Student& other) const;
    bool operator>=(const Student& other) const;

    double calculateAverage() const;
    double calculateGPA() const;

    const Grade& getHighestGrade() const;
    const Grade& getLowestGrade() const;

    int countPassingGrades() const;
    void printGrades() const;

    static int getTotalStudentsCreated();
    static int getCurrentStudentCount();

    friend bool compareByAverage(const Student& first, const Student& second);
    friend bool haveSameGPA(const Student& first, const Student& second);
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
};

bool compareByAverage(const Student& first, const Student& second);
bool haveSameGPA(const Student& first, const Student& second);

}