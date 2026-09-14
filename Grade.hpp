#pragma once

#include <iostream>
#include <string>

namespace grading {

class Grade {
private:
    double score;

    static int totalGradesCreated;
    static constexpr double passingGrade = 60.0;

    static double clamp(double value); // legal grade

public:
    Grade();
    explicit Grade(double score);
    Grade(const Grade& other);

    double getScore() const;
    void setScore(double newScore);

    bool isPassing() const;
    std::string getLetterGrade() const;

    static int getTotalGradesCreated();
    static double getPassingGrade();

    Grade operator+(const Grade& other) const;
    Grade operator+(double value) const;
    Grade operator-(const Grade& other) const;
    Grade operator-(double value) const;
    Grade operator*(double factor) const;
    Grade operator/(double divisor) const;

    Grade& operator+=(const Grade& other);
    Grade& operator+=(double value);
    Grade& operator-=(const Grade& other);
    Grade& operator-=(double value);
    Grade& operator*=(double factor);

    Grade& operator++();
    Grade operator++(int);
    Grade& operator--();
    Grade operator--(int);

    bool operator==(const Grade& other) const;
    bool operator!=(const Grade& other) const;
    bool operator<(const Grade& other) const;
    bool operator>(const Grade& other) const;
    bool operator<=(const Grade& other) const;
    bool operator>=(const Grade& other) const;

    explicit operator int() const;
    explicit operator double() const;
    explicit operator std::string() const;

    friend Grade operator+(double value, const Grade& grade);
    friend Grade operator*(double factor, const Grade& grade);
    friend std::ostream& operator<<(std::ostream& os, const Grade& grade);
};

} 