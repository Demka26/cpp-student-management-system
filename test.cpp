/**
 * @file test.cpp
 * @brief Unit tests for Student Grade Management System using doctest
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <fstream>
#include "Grade.hpp"
#include "Student.hpp"

using namespace grading;

// ==================== GRADE CLASS TESTS ====================

TEST_CASE("Grade - Constructors") {
    Grade g1;
    CHECK(g1.getScore() == 0.0);
    
    Grade g2(85.5);
    CHECK(g2.getScore() == 85.5);
    
    Grade g3(g2);
    CHECK(g3.getScore() == 85.5);
}

TEST_CASE("Grade - Clamping") {
    Grade g1(150.0);  // Over 100
    CHECK(g1.getScore() == 100.0);
    
    Grade g2(-50.0);  // Below 0
    CHECK(g2.getScore() == 0.0);
}

TEST_CASE("Grade - Arithmetic Operators") {
    Grade g1(80.0);
    Grade g2(15.0);
    
    // Addition
    Grade g3 = g1 + g2;
    CHECK(g3.getScore() == 95.0);
    
    Grade g4 = g1 + 10.0;
    CHECK(g4.getScore() == 90.0);
    
    Grade g5 = 5.0 + g1;
    CHECK(g5.getScore() == 85.0);
    
    // Subtraction
    Grade g6 = g1 - g2;
    CHECK(g6.getScore() == 65.0);
    
    Grade g7 = g1 - 20.0;
    CHECK(g7.getScore() == 60.0);
    
    // Multiplication
    Grade g8 = g1 * 1.2;
    CHECK(g8.getScore() == 96.0);
    
    Grade g9 = 1.5 * g2;
    CHECK(g9.getScore() == 22.5);
    
    // Division
    Grade g10 = g1 / 2.0;
    CHECK(g10.getScore() == 40.0);
}

TEST_CASE("Grade - Compound Assignment Operators") {
    Grade g1(70.0);
    
    g1 += 10.0;
    CHECK(g1.getScore() == 80.0);
    
    g1 += Grade(15.0);
    CHECK(g1.getScore() == 95.0);
    
    g1 -= 5.0;
    CHECK(g1.getScore() == 90.0);

    g1 *= 0.5;
    CHECK(g1.getScore() == doctest::Approx(45.0));

    Grade g2(80.0);
    g2 *= 1.5;
    CHECK(g2.getScore() == 100.0);  // Clamped to 100
}

TEST_CASE("Grade - Increment/Decrement Operators (Prefix & Postfix)") {
    Grade g1(80.0);
    
    // Postfix increment
    Grade g2 = g1++;
    CHECK(g2.getScore() == 80.0);  // Returns old value
    CHECK(g1.getScore() == 81.0);  // Incremented
    
    // Prefix increment
    Grade g3 = ++g1;
    CHECK(g3.getScore() == 82.0);  // Returns new value
    CHECK(g1.getScore() == 82.0);  // Incremented
    
    // Postfix decrement
    Grade g4 = g1--;
    CHECK(g4.getScore() == 82.0);  // Returns old value
    CHECK(g1.getScore() == 81.0);  // Decremented
    
    // Prefix decrement
    Grade g5 = --g1;
    CHECK(g5.getScore() == 80.0);  // Returns new value
    CHECK(g1.getScore() == 80.0);  // Decremented
}

TEST_CASE("Grade - Comparison Operators") {
    Grade g1(90.0);
    Grade g2(80.0);
    Grade g3(90.0);
    
    CHECK(g1 == g3);
    CHECK_FALSE(g1 == g2);
    
    CHECK(g1 != g2);
    CHECK_FALSE(g1 != g3);
    
    CHECK(g1 > g2);
    CHECK_FALSE(g2 > g1);
    
    CHECK(g2 < g1);
    CHECK_FALSE(g1 < g2);
    
    CHECK(g1 >= g3);
    CHECK(g1 >= g2);
    
    CHECK(g2 <= g1);
    CHECK(g1 <= g3);
}

TEST_CASE("Grade - Conversion Operators") {
    Grade g(87.6);
    
    int intVal = (int)g;
    CHECK(intVal == 87);
    
    double doubleVal = (double)g;
    CHECK(doubleVal == doctest::Approx(87.6));
    
    std::string strVal = (std::string)g;
    CHECK(strVal == "B");
}

TEST_CASE("Grade - Letter Grades") {
    CHECK(Grade(95.0).getLetterGrade() == "A");
    CHECK(Grade(85.0).getLetterGrade() == "B");
    CHECK(Grade(75.0).getLetterGrade() == "C");
    CHECK(Grade(65.0).getLetterGrade() == "D");
    CHECK(Grade(55.0).getLetterGrade() == "F");
}

TEST_CASE("Grade - Passing Status") {
    CHECK(Grade(70.0).isPassing() == true);
    CHECK(Grade(60.0).isPassing() == true);
    CHECK(Grade(59.0).isPassing() == false);
}

TEST_CASE("Grade - Static Members") {
    int initial = Grade::getTotalGradesCreated();
    
    Grade g1(80.0);
    Grade g2(90.0);
    
    CHECK(Grade::getTotalGradesCreated() == initial + 2);
    CHECK(Grade::getPassingGrade() == 60.0);
}

// ==================== STUDENT CLASS TESTS ====================

TEST_CASE("Student - Constructors") {
    Student s1;
    CHECK(s1.getName() == "Unknown");
    CHECK(s1.getGradeCount() == 0);
    
    Student s2("Alice", "S001", 5);
    CHECK(s2.getName() == "Alice");
    CHECK(s2.getStudentID() == "S001");
    CHECK(s2.getCapacity() == 5);
}

TEST_CASE("Student - Add Grades (Composition)") {
    Student s("Bob", "S002");
    Course math("Math", "M101", 4);
    Course physics("Physics", "P101", 4);
    
    s.addGrade(Grade(90.0), math);
    s.addGrade(Grade(85.0), physics);
    
    CHECK(s.getGradeCount() == 2);
}

TEST_CASE("Student - Bracket Operator [] by Index") {
    Student s("Charlie", "S003");
    s. addGrade(Grade(80.0), "Math");
    s.addGrade(Grade(90.0), "Physics");
    s.addGrade(Grade(85.0), "Chemistry");
    
    CHECK(s[0]. getScore() == 80.0);
    CHECK(s[1].getScore() == 90.0);
    CHECK(s[2]. getScore() == 85.0);
    
    // Modify through bracket operator
    s[1] = Grade(95.0);
    CHECK(s[1].getScore() == 95.0);
}

TEST_CASE("Student - Bracket Operator [] by Course Name") {
    Student s("Dave", "S004");
    Course math("Mathematics", "M101", 4);
    s.addGrade(Grade(88.0), math);
    
    CHECK(s["Mathematics"].getScore() == 88.0);
    
    // Modify through bracket operator
    s["Mathematics"] = Grade(92.0);
    CHECK(s["Mathematics"].getScore() == 92.0);
}

TEST_CASE("Student - Parentheses Operator () - No Parameters") {
    Student s("Eve", "S005");
    s.addGrade(Grade(80.0), "Course1");
    s.addGrade(Grade(90.0), "Course2");
    s.addGrade(Grade(85.0), "Course3");
    
    double avg = s();
    CHECK(avg == doctest::Approx(85.0));  // (80+90+85)/3
}

TEST_CASE("Student - Parentheses Operator () - One Parameter") {
    Student s("Frank", "S006");
    s.addGrade(Grade(80.0), "C1");
    s.addGrade(Grade(90.0), "C2");
    s.addGrade(Grade(70.0), "C3");
    
    double avg = s(2);  // Average of first 2
    CHECK(avg == doctest:: Approx(85.0));  // (80+90)/2
}

TEST_CASE("Student - Parentheses Operator () - Two Parameters (Range)") {
    Student s("Grace", "S007");
    s.addGrade(Grade(80.0), "C1");
    s.addGrade(Grade(90.0), "C2");
    s.addGrade(Grade(70.0), "C3");
    
    double avg = s(1, 3);  // Average from index 1 to 2
    CHECK(avg == doctest::Approx(80.0));  // (90+70)/2
}

TEST_CASE("Student - Arithmetic Operators") {
    Student s("Henry", "S008");
    s.addGrade(Grade(80.0), "Math");
    s.addGrade(Grade(70.0), "Physics");
    
    // Add bonus
    Student s2 = s + 10.0;
    CHECK(s2[0].getScore() == 90.0);
    CHECK(s2[1].getScore() == 80.0);
    
    // Multiply (curve)
    Student s3 = s * 1.1;
    CHECK(s3[0].getScore() == doctest::Approx(88.0));
    CHECK(s3[1].getScore() == doctest::Approx(77.0));
    
    // Compound assignment
    s += 5.0;
    CHECK(s[0].getScore() == 85.0);
    CHECK(s[1].getScore() == 75.0);
}

TEST_CASE("Student - Calculate Average") {
    Student s("Iris", "S009");
    s.addGrade(Grade(80.0), "C1");
    s.addGrade(Grade(90.0), "C2");
    s.addGrade(Grade(85.0), "C3");
    
    CHECK(s.calculateAverage() == doctest::Approx(85.0));
}

TEST_CASE("Student - Calculate GPA") {
    Student s("Jack", "S010");
    s.addGrade(Grade(90.0), "C1");  // A = 4.0
    s.addGrade(Grade(80.0), "C2");  // B = 3.0
    s.addGrade(Grade(70.0), "C3");  // C = 2.0
    
    double gpa = s.calculateGPA();
    CHECK(gpa == doctest::Approx(3.0));  // (4.0+3.0+2.0)/3
}

TEST_CASE("Student - Highest and Lowest Grade") {
    Student s("Kate", "S011");
    s.addGrade(Grade(80.0), "C1");
    s.addGrade(Grade(95.0), "C2");
    s.addGrade(Grade(70.0), "C3");
    
    CHECK(s.getHighestGrade().getScore() == 95.0);
    CHECK(s.getLowestGrade().getScore() == 70.0);
}

TEST_CASE("Student - Count Passing Grades") {
    Student s("Leo", "S012");
    s.addGrade(Grade(70.0), "C1");  // Pass
    s.addGrade(Grade(50.0), "C2");  // Fail
    s.addGrade(Grade(80.0), "C3");  // Pass
    s.addGrade(Grade(55.0), "C4");  // Fail
    
    CHECK(s.countPassingGrades() == 2);
}

TEST_CASE("Student - Comparison Operators") {
    Student s1("Mary", "S013");
    s1.addGrade(Grade(90.0), "C1");
    s1.addGrade(Grade(90.0), "C2");
    
    Student s2("Nick", "S014");
    s2.addGrade(Grade(80.0), "C1");
    s2.addGrade(Grade(80.0), "C2");
    
    CHECK(s1 > s2);   // Higher GPA
    CHECK_FALSE(s1 < s2);
    CHECK(s1 != s2);
    CHECK_FALSE(s1 == s2);
}

TEST_CASE("Student - Copy Constructor (Deep Copy)") {
    Student s1("Oliver", "S015");
    s1.addGrade(Grade(85.0), "Math");
    s1.addGrade(Grade(90.0), "Physics");
    
    Student s2(s1);  // Copy constructor
    s2.setName("Oliver's Copy");
    s2[0] = Grade(100.0);
    
    CHECK(s1[0].getScore() == 85.0);   // Original unchanged
    CHECK(s2[0].getScore() == 100.0);  // Copy modified
}

TEST_CASE("Student - Remove Grade") {
    Student s("Paul", "S016");
    s.addGrade(Grade(80.0), "C1");
    s.addGrade(Grade(90.0), "C2");
    s.addGrade(Grade(70.0), "C3");
    
    s.removeGrade(1);
    CHECK(s.getGradeCount() == 2);
    CHECK(s[0].getScore() == 80.0);
    CHECK(s[1].getScore() == 70.0);  // Shifted down
}

TEST_CASE("Student - Resize (Dynamic Array Growth)") {
    Student s("Quinn", "S017", 2);  // Initial capacity 2
    
    s.addGrade(Grade(80.0), "C1");
    s.addGrade(Grade(85.0), "C2");
    CHECK(s.getCapacity() == 2);
    
    s.addGrade(Grade(90.0), "C3");  // Triggers resize
    CHECK(s.getCapacity() == 4);
    CHECK(s.getGradeCount() == 3);
}

TEST_CASE("Student - Friend Functions") {
    Student s1("Rachel", "S018");
    s1.addGrade(Grade(95.0), "C1");
    s1.addGrade(Grade(90.0), "C2");
    
    Student s2("Sam", "S019");
    s2.addGrade(Grade(80.0), "C1");
    s2.addGrade(Grade(85.0), "C2");
    
    CHECK(compareByAverage(s1, s2) == true);
    CHECK(haveSameGPA(s1, s2) == false);
}

TEST_CASE("Student - Static Members") {
    int initial = Student::getTotalStudentsCreated();
    int initialCurrent = Student::getCurrentStudentCount();
    
    {
        Student s1("Temp1", "T001");
        Student s2("Temp2", "T002");
        
        CHECK(Student:: getTotalStudentsCreated() == initial + 2);
        CHECK(Student::getCurrentStudentCount() == initialCurrent + 2);
    }
    
    CHECK(Student::getCurrentStudentCount() == initialCurrent);
}

TEST_CASE("Student - Copy Assignment Operator (Deep Copy)") {
    Student s1("Oliver", "S020");
    s1.addGrade(Grade(85.0), "Math");
    s1.addGrade(Grade(90.0), "Physics");
    
    Student s2("Empty", "S021");
    s2 = s1;  // Copy assignment operator
    s2.setName("Oliver's Copy");
    s2[0] = Grade(100.0);
    
    CHECK(s1[0].getScore() == 85.0);   // Original unchanged
    CHECK(s2[0].getScore() == 100.0);  // Copy modified
    CHECK(s2.getGradeCount() == 2);
}

TEST_CASE("Student - Self Assignment") {
    Student s1("Self", "S022");
    s1.addGrade(Grade(85.0), "Math");
    
    s1 = s1;  // Self assignment - should not crash
    
    CHECK(s1[0].getScore() == 85.0);
    CHECK(s1.getName() == "Self");
}

// ==================== INTEGRATION TESTS ====================

TEST_CASE("Integration - Complete Workflow") {
    Student student("Test Student", "T100", 3);
    
    // Add grades
    student.addGrade(Grade(85.0), Course("Math", "M101", 4));
    student.addGrade(Grade(90.0), Course("Physics", "P101", 4));
    student.addGrade(Grade(88.0), Course("Chemistry", "C101", 3));
    
    // Test bracket operator
    CHECK(student[0].getScore() == 85.0);
    CHECK(student["Physics"].getScore() == 90.0);
    
    // Test parentheses operator
    CHECK(student() == doctest::Approx(87.666667).epsilon(0.001));
    
    // Test arithmetic
    Student curved = student * 1.05;
    CHECK(curved[0].getScore() == doctest::Approx(89.25));
    
    // Test statistics
    CHECK(student.calculateAverage() == doctest::Approx(87.666667).epsilon(0.001));
    CHECK(student.getHighestGrade().getScore() == 90.0);
    CHECK(student.getLowestGrade().getScore() == 85.0);
    CHECK(student.countPassingGrades() == 3);
}

TEST_CASE("Student custom tests file exists") {
    std::ifstream f("StudentTest.cpp");
    CHECK_MESSAGE(f.good(), "StudentTest.cpp file must be created by the student");
}
