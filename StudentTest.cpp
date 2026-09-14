#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "Grade.hpp"
#include "Student.hpp"

#include <sstream>
#include <stdexcept>
#include <string>

using namespace grading;

// ==================== GRADE CLASS TESTS ====================


TEST_CASE("Removing last grade keeps earlier grades") {
    Student s("Demi", "S1");
    s.addGrade(Grade(60.0), "Math");
    s.addGrade(Grade(70.0), "Algebra");
    s.addGrade(Grade(80.0), "CPP");

    s.removeGrade(2);

    CHECK(s.getGradeCount() == 2);
    CHECK(s[0].getScore() == 60.0);
    CHECK(s[1].getScore() == 70.0);
}
TEST_CASE("Weighted average with zero weight ignores selected grade") {
    Student s("Demi", "S1");
    s.addGrade(Grade(100.0), "Math");
    s.addGrade(Grade(60.0), "Algebra");
    s.addGrade(Grade(80.0), "CPP");

    CHECK(s(0, 0.0) == doctest::Approx(70.0)); //It’s used for comparing doubles safely
    
    
    /*
        grade at index 0 (100) gets weight 0
        all others get weight 1
            (100 * 0 + 60 * 1 + 80 * 1) / (0 + 1 + 1)
            = (0 + 60 + 80) / 2
            = 140 / 2
            = 70
    
    */
}

TEST_CASE("Prefix and postfix changes affect letter grade") {
    Grade g(89.0);

    ++g;
    CHECK(g.getLetterGrade() == "A");

    g--;
    CHECK(g.getLetterGrade() == "B");
}
TEST_CASE("Student plus bonus does not modify original") {
    Student original("Demi", "S1");
    original.addGrade(Grade(80.0), "Math");

    Student boosted = original + 10.0;

    CHECK(original[0].getScore() == 80.0);
    CHECK(boosted[0].getScore() == 90.0);
}
TEST_CASE("Student multiply curve does not modify original") {
    Student original("Dana", "S1");
    original.addGrade(Grade(80.0), "Math");

    Student curved = original * 1.5;

    CHECK(original[0].getScore() == 80.0);
    CHECK(curved[0].getScore() == 100.0);
}

TEST_CASE("Plus equals clamps every grade") {
    Student s("Demi", "S1");
    s.addGrade(Grade(95.0), "Math");
    s.addGrade(Grade(99.0), "Physics");

    s += 10.0;

    CHECK(s[0].getScore() == 100.0);
    CHECK(s[1].getScore() == 100.0);
}
TEST_CASE("StudentTest - Count passing after score modifications") {
    Student s("Dana", "S1");
    s.addGrade(Grade(59.0), "Math");
    s.addGrade(Grade(61.0), "Physics");

    CHECK(s.countPassingGrades() == 1);

    s[0].setScore(60.0);

    CHECK(s.countPassingGrades() == 2);
}
TEST_CASE("Lowest grade after modification by course name") {
    Student s("Demi", "S1");
    s.addGrade(Grade(85.0), "Math");
    s.addGrade(Grade(75.0), "Physics");

    s["Math"] = Grade(40.0);

    CHECK(s.getLowestGrade().getScore() == 40.0);
}
TEST_CASE("GPA with only failing grades is zero") {
    Student s("Dana", "S1");
    s.addGrade(Grade(10.0), "Math");
    s.addGrade(Grade(55.0), "Physics");

    CHECK(s.calculateGPA() == doctest::Approx(0.0));
}
TEST_CASE("Grade addition with clamp overflow") {
    Grade g1(95.0);
    Grade g2(10.0);

    Grade result = g1 + g2;

    CHECK(result.getScore() == 100.0);
}
TEST_CASE("Grade subtraction resulting in zero") {
    Grade g1(20.0);
    Grade g2(50.0);

    Grade result = g1 - g2;

    CHECK(result.getScore() == 0.0);
}
TEST_CASE("Grade multiplication overflow clamps") {
    Grade g(80.0);

    Grade result = g * 2.0;

    CHECK(result.getScore() == 100.0);
}
TEST_CASE("Grade addition with double on left") {
    Grade g(40.0);

    Grade result = 10.0 + g;

    CHECK(result.getScore() == 50.0);
}

TEST_CASE("Grade compound += with double") {
    Grade g(70.0);

    g += 15.0;

    CHECK(g.getScore() == 85.0);
}
TEST_CASE("Grade multiplication with double on left") {
    Grade g(30.0);

    Grade result = 3.0 * g;

    CHECK(result.getScore() == 90.0);
}
TEST_CASE("Arithmetic preserves grade order") {
    Student s("Demi", "S1");
    s.addGrade(Grade(60.0), "A");
    s.addGrade(Grade(70.0), "B");
    s.addGrade(Grade(80.0), "C");

    Student result = s + 10.0;

    CHECK(result[0].getScore() == 70.0);
    CHECK(result[1].getScore() == 80.0);
    CHECK(result[2].getScore() == 90.0);
}
TEST_CASE("Student arithmetic does not affect original") {
    Student s("Demi", "S1");
    s.addGrade(Grade(70.0), "Math");

    Student result = s + 20.0;

    CHECK(s[0].getScore() == 70.0);
    CHECK(result[0].getScore() == 90.0);
}
TEST_CASE("Chained student operations") {
    Student s("Demi", "S1");
    s.addGrade(Grade(50.0), "Math");
    s.addGrade(Grade(60.0), "Physics");

    Student result = (s + 10.0) * 2.0;

    CHECK(result[0].getScore() == 100.0);
    CHECK(result[1].getScore() == 100.0);
}
TEST_CASE("Grade - Letter Grades") {
    CHECK(Grade(96.0).getLetterGrade() == "A");
    CHECK(Grade(84.0).getLetterGrade() == "B");
    CHECK(Grade(73.0).getLetterGrade() == "C");
    CHECK(Grade(61.0).getLetterGrade() == "D");
    CHECK(Grade(54.0).getLetterGrade() == "F");
}
TEST_CASE("Grade - Passing Status") {
    CHECK(Grade(77.0).isPassing() == true);
    CHECK(Grade(60.0).isPassing() == true);
    CHECK(Grade(59.0).isPassing() == false);
}
