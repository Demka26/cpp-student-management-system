#include "Grade.hpp"

#include <iomanip>
#include <stdexcept>

namespace grading {

constexpr double GRADE_A = 90.0;
constexpr double GRADE_B = 80.0;
constexpr double GRADE_C = 70.0;

int Grade::totalGradesCreated = 0;

double Grade::clamp(double value){
    if(value<0.0){
        return 0.0;
    }
    if(value>100.0){
        return 100.0;
    } 

    return value;
}

Grade::Grade() : score(0.0) {
    ++totalGradesCreated;
}

Grade::Grade(double score) : score(clamp(score)) {
    ++totalGradesCreated;
}

Grade::Grade(const Grade& other) : score(other.score) {
    ++totalGradesCreated;
}

double Grade::getScore() const {
    return score;
}

void Grade::setScore(double newScore) {
    score = clamp(newScore);
}

bool Grade::isPassing() const {
    return score >= passingGrade;
}

std::string Grade::getLetterGrade() const {
    if (score >= GRADE_A) {
        return "A";
    }

    if (score >= GRADE_B) {
        return "B";
    }

    if (score >= GRADE_C) {
        return "C";
    }

    if (score >= passingGrade) {
        return "D";
    }

    return "F";
}

int Grade::getTotalGradesCreated() {
    return totalGradesCreated;
}

double Grade::getPassingGrade() {
    return passingGrade;
}

Grade Grade::operator+(const Grade& other) const {
    return Grade(score + other.score);
}

Grade Grade::operator+(double value) const {
    return Grade(score + value);
}

Grade Grade::operator-(const Grade& other) const {
    return Grade(score - other.score);
}

Grade Grade::operator-(double value) const {
    return Grade(score - value);
}

Grade Grade::operator*(double factor) const {
    return Grade(score * factor);
}

Grade Grade::operator/(double divisor) const {
    if (divisor == 0.0) {
        throw std::invalid_argument("Division by zero");
    }

    return Grade(score / divisor);
}

Grade& Grade::operator+=(const Grade& other) {
    score = clamp(score + other.score);
    return *this;
}

Grade& Grade::operator+=(double value) {
    score = clamp(score + value);
    return *this;
}

Grade& Grade::operator-=(const Grade& other) {
    score = clamp(score - other.score);
    return *this;
}

Grade& Grade::operator-=(double value) {
    score = clamp(score - value);
    return *this;
}

Grade& Grade::operator*=(double factor) {
    score = clamp(score * factor);
    return *this;
}

Grade& Grade::operator++() {
    score = clamp(score + 1.0);
    return *this;
}

Grade Grade::operator++(int) {
    Grade old(*this);
    ++(*this);
    return old;
}

Grade& Grade::operator--() {
    score = clamp(score - 1.0);
    return *this;
}

Grade Grade::operator--(int) {
    Grade old(*this);
    --(*this);
    return old;
}

bool Grade::operator==(const Grade& other) const {
    return score == other.score;
}

bool Grade::operator!=(const Grade& other) const {
    return !(*this == other);
}

bool Grade::operator<(const Grade& other) const {
    return score < other.score;
}

bool Grade::operator>(const Grade& other) const {
    return score > other.score;
}

bool Grade::operator<=(const Grade& other) const {
    return score <= other.score;
}

bool Grade::operator>=(const Grade& other) const {
    return score >= other.score;
}

Grade::operator int() const {
    return static_cast<int>(score);
}

Grade::operator double() const {
    return score;
}

Grade::operator std::string() const {
    return getLetterGrade();
}

Grade operator+(double value, const Grade& grade) {
    return Grade(value + grade.score);
}

Grade operator*(double factor, const Grade& grade) {
    return Grade(factor * grade.score);
}

std::ostream& operator<<(std::ostream& ost, const Grade& grade) {
    ost << std::fixed << std::setprecision(2)
       << grade.score << " (" << grade.getLetterGrade() << ")";
    return ost;
}

}