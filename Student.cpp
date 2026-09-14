#include "Student.hpp"

#include <iomanip>
#include <stdexcept>
#include <span>
#include <algorithm>
#include <iterator>



namespace grading {

constexpr double GPA_A = 4.0;
constexpr double GPA_B = 3.0;
constexpr double GPA_C = 2.0;
constexpr double GPA_D = 1.0;
constexpr double GPA_F = 0.0;



int Student::totalStudentsCreated = 0;
int Student::currentStudentCount = 0;

Course::Course() : credits(0) {}

Course::Course(const std::string& name, const std::string& code, int credits)
    : name(name), code(code), credits(credits) {}

Student::Student()
    : name("Unknown"),
      //studentID(""),
      grades(new Grade[2]),
      courses(new Course[2]),
      gradeCount(0),
      capacity(2) {
    ++totalStudentsCreated;
    ++currentStudentCount;
}

Student::Student(const std::string& name, const std::string& studentID, int capacity)
    : name(name),
      studentID(studentID),
      grades(nullptr),
      courses(nullptr),
      gradeCount(0),
      capacity(capacity > 0 ? capacity : 2) {
    grades = new Grade[static_cast<size_t>(this->capacity)]; // NOLINT(cppcoreguidelines-owning-memory)
    courses = new Course[static_cast<size_t>(this->capacity)]; // NOLINT(cppcoreguidelines-owning-memory)

    ++totalStudentsCreated;
    ++currentStudentCount;
}

Student::Student(const Student& other)
    : name(other.name),
      studentID(other.studentID),
      grades(new Grade[static_cast<size_t>(other.capacity)]),
      courses(new Course[static_cast<size_t>(other.capacity)]),
      gradeCount(other.gradeCount),
      capacity(other.capacity) {
      std::copy_n(other.grades, static_cast<size_t>(gradeCount), grades);
      std::copy_n(other.courses, static_cast<size_t>(gradeCount), courses);

    ++totalStudentsCreated;
    ++currentStudentCount;
}

Student& Student::operator=(const Student& other) {
    if (this == &other) {
        return *this;
    }

    Grade* newGrades = new Grade[static_cast<size_t>(other.capacity)]; // NOLINT(cppcoreguidelines-owning-memory)
    Course* newCourses = new Course[static_cast<size_t>(other.capacity)]; // NOLINT(cppcoreguidelines-owning-memory)

    // for (int i = 0; i < other.gradeCount; ++i) {
    //     newGrades[i] = other.grades[i];
    //     newCourses[i] = other.courses[i];
    // }
    std::copy_n(other.grades, static_cast<size_t>(other.gradeCount), newGrades);
    std::copy_n(other.courses, static_cast<size_t>(other.gradeCount), newCourses);

    delete[] grades;
    delete[] courses;

    name = other.name;
    studentID = other.studentID;
    grades = newGrades;
    courses = newCourses;
    gradeCount = other.gradeCount;
    capacity = other.capacity;

    return *this;
}

Student::~Student() {
    delete[] grades;
    delete[] courses;
    --currentStudentCount;
}

void Student::resize() {
    const int newCapacity = capacity * 2;

    Grade* newGrades = new Grade[static_cast<size_t>(newCapacity)]; // NOLINT(cppcoreguidelines-owning-memory)
    Course* newCourses = new Course[static_cast<size_t>(newCapacity)]; // NOLINT(cppcoreguidelines-owning-memory)

    std::copy_n(grades, static_cast<size_t>(gradeCount), newGrades);
    std::copy_n(courses, static_cast<size_t>(gradeCount), newCourses);

    delete[] grades;
    delete[] courses;

    grades = newGrades;
    courses = newCourses;
    capacity = newCapacity;
}

int Student::findCourseIndex(const std::string& courseName) const {
    for (int i = 0; i < gradeCount; ++i) {
        // if (courses[i].name == courseName) 
        if (std::next(courses, i)->name == courseName)
        {
            return i;
        }
    }

    throw std::out_of_range("Course not found");
}

std::string Student::getName() const {
    return name;
}

void Student::setName(const std::string& newName) {
    name = newName;
}

std::string Student::getStudentID() const {
    return studentID;
}

int Student::getGradeCount() const {
    return gradeCount;
}

int Student::getCapacity() const {
    return capacity;
}

void Student::addGrade(const Grade& grade, const Course& course) {
    if (gradeCount == capacity) {
        resize();
    }

    // grades[gradeCount] = grade;
    // courses[gradeCount] = course;
    *std::next(grades, gradeCount) = grade;
    *std::next(courses, gradeCount) = course;
    ++gradeCount;
}

void Student::addGrade(const Grade& grade, const std::string& courseName) {
    addGrade(grade, Course(courseName, courseName, 0));
}

void Student::removeGrade(int index) {
    if (index < 0 || index >= gradeCount) {
        throw std::out_of_range("Grade index out of range");
    }
    //grades[i] = grades[i + 1];
    std::move(
        std::next(grades, index + 1),
        std::next(grades, gradeCount),
        std::next(grades, index)
    );
    //courses[i] = courses[i + 1];
    std::move(
        std::next(courses, index + 1),
        std::next(courses, gradeCount),
        std::next(courses, index)
    );

    --gradeCount;
}

Grade& Student::operator[](int index) {
    if (index < 0 || index >= gradeCount) {
        throw std::out_of_range("Grade index out of range");
    }

    return *std::next(grades, index);
}

const Grade& Student::operator[](int index) const {
    if (index < 0 || index >= gradeCount) {
        throw std::out_of_range("Grade index out of range");
    }

    return *std::next(grades, index);
}

Grade& Student::operator[](const std::string& courseName) {
    return (*this)[findCourseIndex(courseName)];
}

const Grade& Student::operator[](const std::string& courseName) const {
    return (*this)[findCourseIndex(courseName)];
}

double Student::operator()() const {
    return calculateAverage();
}

double Student::operator()(int count) const {
    if (count <= 0 || count > gradeCount) {
        throw std::out_of_range("Invalid grade count");
    }

    double sum = 0.0;

    for (int i = 0; i < count; ++i) {
        sum += (*this)[i].getScore();
    }

    return sum / count;
}

double Student::operator()(int start, int end) const {
    if (start < 0 || end > gradeCount || start >= end) {
        throw std::out_of_range("Invalid range");
    }

    double sum = 0.0;

    for (int i = start; i < end; ++i) {
        sum += (*this)[i].getScore();
    }

    return sum / (end - start);
}

double Student::operator()(int index, double weight) const {
    if (index < 0 || index >= gradeCount) {
        throw std::out_of_range("Grade index out of range");
    }

    if (weight < 0.0) {
        throw std::invalid_argument("Weight cannot be negative");
    }

    double weightedSum = 0.0;
    double totalWeight = 0.0;

    for (int i = 0; i < gradeCount; ++i) {
        const double currentWeight = (i == index) ? weight : 1.0;
        weightedSum += (*this)[i].getScore() * currentWeight;
        totalWeight += currentWeight;
    }

    if (totalWeight == 0.0) {
        throw std::invalid_argument("Total weight cannot be zero");
    }

    return weightedSum / totalWeight;
}

Student Student::operator+(double bonus) const {
    Student result(*this);
    result += bonus;
    return result;
}

Student Student::operator*(double factor) const {
    Student result(*this);
    result *= factor;
    return result;
}

Student& Student::operator+=(double bonus) {
    for (int i = 0; i < gradeCount; ++i) {
        (*this)[i] += bonus;
    }

    return *this;
}

Student& Student::operator*=(double factor) {
    for (int i = 0; i < gradeCount; ++i) {
        (*this)[i] *= factor;
    }

    return *this;
}

bool Student::operator==(const Student& other) const {
    return calculateGPA() == other.calculateGPA();
}

bool Student::operator!=(const Student& other) const {
    return !(*this == other);
}

bool Student::operator<(const Student& other) const {
    return calculateGPA() < other.calculateGPA();
}

bool Student::operator>(const Student& other) const {
    return calculateGPA() > other.calculateGPA();
}

bool Student::operator<=(const Student& other) const {
    return calculateGPA() <= other.calculateGPA();
}

bool Student::operator>=(const Student& other) const {
    return calculateGPA() >= other.calculateGPA();
}

double Student::calculateAverage() const {
    if (gradeCount == 0) {
        return 0.0;
    }

    double sum = 0.0;

    for (int i = 0; i < gradeCount; ++i) {
        sum += (*this)[i].getScore();
    }

    return sum / gradeCount;
}

double Student::calculateGPA() const {
    if (gradeCount == 0) {
        return 0.0;
    }

    double sum = 0.0;

    for (int i = 0; i < gradeCount; ++i) {
        const std::string letter = (*this)[i].getLetterGrade();

         if (letter == "A") {
             sum += GPA_A;
        } else if (letter == "B") {
            sum += GPA_B;
        } else if (letter == "C") {
            sum += GPA_C;
        } else if (letter == "D") {
            sum += GPA_D;
        } else {
            sum += GPA_F;
        }
    }

    return sum / gradeCount;
}

const Grade& Student::getHighestGrade() const {
    if (gradeCount == 0) {
        throw std::out_of_range("No grades available");
    }

    int highestIndex = 0;

    for (int i = 1; i < gradeCount; ++i) {
        if ((*this)[i] > (*this)[highestIndex]) {
            highestIndex = i;
        }
    }

    return (*this)[highestIndex];
}

const Grade& Student::getLowestGrade() const {
    if (gradeCount == 0) {
        throw std::out_of_range("No grades available");
    }

    int lowestIndex = 0;

    for (int i = 1; i < gradeCount; ++i) {
        if ((*this)[i] < (*this)[lowestIndex]) {
            lowestIndex = i;
        }
    }

    return (*this)[lowestIndex];
}

int Student::countPassingGrades() const {
    int count = 0;

    for (int i = 0; i < gradeCount; ++i) {
        if ((*this)[i].isPassing()) {
            ++count;
        }
    }

    return count;
}

std::string Student::getCourseName(int index) const {
    if (index < 0 || index >= gradeCount) {
        throw std::out_of_range("Course index out of range");
    }

    return std::next(courses, index)->name;
}

std::string Student::getCourseCode(int index) const {
    if (index < 0 || index >= gradeCount) {
        throw std::out_of_range("Course index out of range");
    }

    return std::next(courses, index)->code;
}

int Student::getCourseCredits(int index) const {
    if (index < 0 || index >= gradeCount) {
        throw std::out_of_range("Course index out of range");
    }

    return std::next(courses, index)->credits;
}

void Student::printGrades() const {
    for (int i = 0; i < gradeCount; ++i) {
        std::cout << getCourseName(i) << ": " << (*this)[i] << '\n';
    }
}

int Student::getTotalStudentsCreated() {
    return totalStudentsCreated;
}

int Student::getCurrentStudentCount() {
    return currentStudentCount;
}

bool compareByAverage(const Student& first, const Student& second) {
    return first.calculateAverage() > second.calculateAverage();
}

bool haveSameGPA(const Student& first, const Student& second) {
    return first.calculateGPA() == second.calculateGPA();
}

std::ostream& operator<<(std::ostream& ost, const Student& student) {
    ost << "Student: " << student.name << '\n';
    ost << "ID: " << student.studentID << '\n';
    ost << "Grades:\n";

    for (int i = 0; i < student.gradeCount; ++i) {
        ost << student.getCourseName(i)
            << " [" << student.getCourseCode(i) << "]"
            << " (" << student.getCourseCredits(i) << " credits): "
            << student[i] << '\n';
    }

    return ost;
}

}