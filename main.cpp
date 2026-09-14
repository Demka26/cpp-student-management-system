/**
 * @file main.cpp
 * @brief Demo for Student Grade Management System
 */

#include <iostream>
#include <iomanip>
#include "Grade.hpp"
#include "Student.hpp"

using namespace std;
using namespace grading;

void printSeparator(const string& title = "") {
    cout << "\n========================================" << endl;
    if (!title.empty()) {
        cout << "  " << title << endl;
        cout << "========================================" << endl;
    }
}

int main() {
    cout << fixed << setprecision(2);
    
    printSeparator("Student Grade Management System Demo");
    
    // ============ PART 1: GRADE CLASS DEMO ============
    
    printSeparator("PART 1: GRADE CLASS");
    
    // --- 1. CONSTRUCTORS ---
    cout << "\n=== 1. CONSTRUCTORS ===" << endl;
    Grade g1;                    // Default constructor
    Grade g2(85.5);             // Parameterized constructor
    Grade g3(g2);               // Copy constructor
    
    cout << "g1 (default): " << g1 << endl;          // Expected: 0.00 (F)
    cout << "g2 (85.5): " << g2 << endl;             // Expected: 85.50 (B)
    cout << "g3 (copy of g2): " << g3 << endl;       // Expected: 85.50 (B)
    
    // --- 2. ARITHMETIC OPERATORS ---
    cout << "\n=== 2. ARITHMETIC OPERATORS (+, -, *, /) ===" << endl;
    
    Grade g4 = g2 + 10.0;
    cout << "g2 + 10.0 = " << g4 << endl;            // Expected: 95.50 (A)
    
    Grade g5 = g2 - 20.0;
    cout << "g2 - 20.0 = " << g5 << endl;            // Expected: 65.50 (D)
    
    Grade g6 = g2 * 1.1;
    cout << "g2 * 1.1 = " << g6 << endl;             // Expected: 94.05 (A)
    
    Grade g7 = g2 / 2.0;
    cout << "g2 / 2.0 = " << g7 << endl;             // Expected: 42.75 (F)
    
    Grade g8 = g2 + g3;
    cout << "g2 + g3 = " << g8 << endl;              // Expected: 100.00 (A) - clamped
    
    Grade g9 = 5.0 + g2;
    cout << "5.0 + g2 = " << g9 << endl;             // Expected: 90.50 (A)
    
    Grade g10 = 1.2 * g2;
    cout << "1.2 * g2 = " << g10 << endl;            // Expected: 100.00 (A) - clamped
    
    Grade g11(70.0);
    g11 += 15.0;
    cout << "g11 after += 15.0: " << g11 << endl;    // Expected: 85.00 (B)
    
    g11 -= 10.0;
    cout << "g11 after -= 10.0: " << g11 << endl;    // Expected: 75.00 (C)
    
    // --- 3. PREFIX & POSTFIX OPERATORS (++, --) ---
    cout << "\n=== 3. INCREMENT/DECREMENT (Prefix & Postfix) OPERATORS ===" << endl;
    
    Grade g12(80.0);
    cout << "g12 initial: " << g12 << endl;          // Expected: 80.00 (B)
    
    Grade g13 = g12++;
    cout << "After g12++: g12 = " << g12 << ", returned value = " << g13 << endl;
    // Expected: g12 = 81.00 (B), returned = 80.00 (B)
    
    Grade g14 = ++g12;
    cout << "After ++g12: g12 = " << g12 << ", returned value = " << g14 << endl;
    // Expected: g12 = 82.00 (B), returned = 82.00 (B)
    
    Grade g15 = g12--;
    cout << "After g12--: g12 = " << g12 << ", returned value = " << g15 << endl;
    // Expected: g12 = 81.00 (B), returned = 82.00 (B)
    
    Grade g16 = --g12;
    cout << "After --g12: g12 = " << g12 << ", returned value = " << g16 << endl;
    // Expected: g12 = 80.00 (B), returned = 80.00 (B)
    
    // --- 4. COMPARISON OPERATORS ---
    cout << "\n=== 4. COMPARISON OPERATORS ===" << endl;
    
    Grade gA(90.0), gB(80.0), gC(90.0);
    
    cout << "gA (90) == gB (80): " << (gA == gB ?  "true" : "false") << endl;  // Expected: false
    cout << "gA (90) == gC (90): " << (gA == gC ? "true" : "false") << endl;  // Expected: true
    cout << "gA (90) != gB (80): " << (gA != gB ? "true" : "false") << endl;  // Expected:  true
    cout << "gA (90) > gB (80): " << (gA > gB ? "true" : "false") << endl;    // Expected: true
    cout << "gA (90) < gB (80): " << (gA < gB ? "true" : "false") << endl;    // Expected: false
    cout << "gA (90) >= gC (90): " << (gA >= gC ? "true" :  "false") << endl;  // Expected: true
    cout << "gB (80) <= gA (90): " << (gB <= gA ? "true" :  "false") << endl;  // Expected: true
    
    // --- 5. CONVERSION OPERATORS (int, double, string) ---
    cout << "\n=== 5. CONVERSION OPERATORS (int-string-operators) ===" << endl;
    
    Grade g17(87.6);
    
    int intScore = (int)g17;              // Convert to int
    double doubleScore = (double)g17;     // Convert to double
    string letterGrade = (string)g17;     // Convert to string (letter grade)
    
    cout << "g17 = " << g17 << endl;                           // Expected: 87.60 (B)
    cout << "As int: " << intScore << endl;                    // Expected: 87
    cout << "As double: " << doubleScore << endl;              // Expected: 87.60
    cout << "As string (letter): " << letterGrade << endl;     // Expected: B
    
    // Using in expressions
    int total = 100;
    int remaining = total - (int)g17;
    cout << "100 - (int)g17 = " << remaining << endl;          // Expected: 13
    
    // --- 6. STREAM OPERATOR (Output) ---
    cout << "\n=== 6. STREAM OPERATOR (<<) ===" << endl;
    
    Grade g18(92.5);
    cout << "Output using <<: " << g18 << endl;                // Expected: 92.50 (A)
    
    Grade g19(78.5);
    cout << "Another grade using <<: " << g19 << endl;         // Expected: 78.50 (C)
    
    // --- 7. CONST METHODS & STATIC ---
    cout << "\n=== 7. CONST METHODS & STATIC MEMBERS ===" << endl;
    
    const Grade constGrade(75.0);
    cout << "Const grade score: " << constGrade. getScore() << endl;        // Expected: 75.00
    cout << "Is passing?  " << (constGrade.isPassing() ? "Yes" : "No") << endl;  // Expected: Yes
    cout << "Letter grade: " << constGrade. getLetterGrade() << endl;       // Expected: C
    
    cout << "Total grades created: " << Grade::getTotalGradesCreated() << endl;
    cout << "Passing grade threshold: " << Grade::getPassingGrade() << endl;  // Expected: 60.00
    
    // ============ PART 2: STUDENT CLASS DEMO ============
    
    printSeparator("PART 2: STUDENT CLASS");
    
    // --- 8. COMPOSITION (Student HAS-A Grades array) ---
    cout << "\n=== 8. COMPOSITION (Student HAS-A Grades & Courses) ===" << endl;
    
    Student student1("Alice Johnson", "S001", 3);
    cout << "Created student:  " << student1.getName() << " (ID: " << student1.getStudentID() << ")" << endl;
    // Expected: Alice Johnson (ID: S001)
    
    // Add grades with courses (demonstrates composition and reference parameters)
    Course math("Calculus I", "MATH101", 4);
    Course physics("Physics I", "PHYS101", 4);
    Course english("English Composition", "ENG101", 3);
    
    student1.addGrade(Grade(92.0), math);
    student1.addGrade(Grade(87.5), physics);
    student1.addGrade(Grade(95.0), english);
    
    cout << "Added 3 grades with courses (composition demonstrated)" << endl;
    cout << "Number of grades:  " << student1.getGradeCount() << endl;  // Expected: 3
    
    // --- 9. BRACKET OPERATOR [] ---
    cout << "\n=== 9. BRACKET OPERATOR [] ===" << endl;
    
    cout << "student1[0] = " << student1[0] << endl;          // Expected: 92.00 (A)
    cout << "student1[1] = " << student1[1] << endl;          // Expected: 87.50 (B)
    cout << "student1[2] = " << student1[2] << endl;          // Expected: 95.00 (A)
    
    student1[1] = Grade(90.0);
    cout << "After student1[1] = Grade(90.0): " << student1[1] << endl;  // Expected: 90.00 (A)
    
    Grade& mathGrade = student1["Calculus I"];
    cout << "student1[\"Calculus I\"] = " << mathGrade << endl;          // Expected: 92.00 (A)
    
    student1["English Composition"] = Grade(98.0);
    cout << "After student1[\"English Composition\"] = Grade(98.0): " 
         << student1["English Composition"] << endl;                     // Expected: 98.00 (A)
    
    // --- 10. PARENTHESES OPERATOR () ---
    cout << "\n=== 10. PARENTHESES OPERATOR () ===" << endl;
    
    double avg1 = student1();
    cout << "student1() [average of all grades]: " << avg1 << endl;
    // Expected: (92.0 + 90.0 + 98.0) / 3 = 93.33
    
    double avg2 = student1(2);
    cout << "student1(2) [average of first 2 grades]: " << avg2 << endl;
    // Expected: (92.0 + 90.0) / 2 = 91.00
    
    double avg3 = student1(1, 3);
    cout << "student1(1, 3) [average from index 1 to 2]: " << avg3 << endl;
    // Expected: (90.0 + 98.0) / 2 = 94.00
    
    double avg4 = student1(0, 2.0);
    cout << "student1(0, 2.0) [weighted average, grade 0 weighted 2x]: " << avg4 << endl;
    // Expected: (92.0*2 + 90.0 + 98.0) / 4 = 93.00
    
    // --- 11. ARITHMETIC OPERATORS ON STUDENT ---
    cout << "\n=== 11. ARITHMETIC OPERATORS (on Student) ===" << endl;
    
    Student student2 = student1 + 5.0;
    cout << "student1 + 5.0 bonus:" << endl;
    student2.printGrades();
    // Expected: All grades increased by 5
    
    Student student3 = student1 * 1.05;
    cout << "\nstudent1 * 1.05 (5% curve):" << endl;
    student3.printGrades();
    // Expected: All grades multiplied by 1.05
    
    Student student4("Bob Smith", "S002");
    student4.addGrade(Grade(80.0), "History");
    student4.addGrade(Grade(75.0), "Art");
    
    student4 += 10.0;
    cout << "\nstudent4 after += 10.0:" << endl;
    student4.printGrades();
    // Expected: 80->90, 75->85
    
    student4 *= 1.1;
    cout << "\nstudent4 after *= 1.1:" << endl;
    student4.printGrades();
    // Expected: 90->99, 85->93. 5
    
    // --- 12. COMPARISON OPERATORS (on Student) ---
    cout << "\n=== 12. COMPARISON OPERATORS (comparing Students by GPA) ===" << endl;
    
    double gpa1 = student1.calculateGPA();
    double gpa4 = student4.calculateGPA();
    
    cout << "student1 GPA: " << gpa1 << endl;
    cout << "student4 GPA: " << gpa4 << endl;
    
    cout << "student1 == student4: " << (student1 == student4 ? "true" :  "false") << endl;
    cout << "student1 != student4: " << (student1 != student4 ? "true" : "false") << endl;
    cout << "student1 > student4: " << (student1 > student4 ? "true" : "false") << endl;
    cout << "student1 < student4: " << (student1 < student4 ?  "true" : "false") << endl;
    
    // --- 13. FRIEND FUNCTIONS ---
    cout << "\n=== 13. FRIEND FUNCTIONS ===" << endl;
    
    cout << "compareByAverage(student1, student4): " 
         << (compareByAverage(student1, student4) ? "student1 higher" : "student4 higher") << endl;
    
    cout << "haveSameGPA(student1, student4): " 
         << (haveSameGPA(student1, student4) ? "Yes" : "No") << endl;
    
    // --- 14. STREAM OPERATOR (on Student) ---
    cout << "\n=== 14. STREAM OPERATOR (Student <<) ===" << endl;
    
    cout << "Output using <<:" << endl;
    cout << student1 << endl;
    // Expected: Full student info with all grades
    
    // --- 15. CONST METHODS ---
    cout << "\n=== 15. CONST METHODS (on Student) ===" << endl;
    
    const Student constStudent = student1;
    cout << "Const student name: " << constStudent.getName() << endl;
    cout << "Const student GPA: " << constStudent.calculateGPA() << endl;
    cout << "Const student average: " << constStudent.calculateAverage() << endl;
    cout << "Const student passing grades: " << constStudent.countPassingGrades() << endl;
    cout << "Highest grade: " << constStudent.getHighestGrade() << endl;
    cout << "Lowest grade: " << constStudent.getLowestGrade() << endl;
    
    // Const bracket operator
    cout << "Const student[0]:  " << constStudent[0] << endl;
    
    // Const parentheses operator
    cout << "Const student(): " << constStudent() << endl;
    
    // --- 16. COPY CONSTRUCTOR & DESTRUCT-ARRAYS ---
    cout << "\n=== 16. COPY CONSTRUCTOR (Deep Copy) & DESTRUCT-ARRAYS ===" << endl;
    
    {
        Student copy1(student1);  // Copy constructor
        copy1.setName("Alice's Copy");
        copy1[0] = Grade(100.0);  // Modify copy
        
        cout << "Original student1 first grade: " << student1[0] << endl;  // Expected: 92.00
        cout << "Copied student first grade: " << copy1[0] << endl;        // Expected:  100.00
        cout << "Deep copy verified - arrays are independent" << endl;
        
        cout << "\nExiting scope - copy1 will be destroyed (destruct-arrays)..." << endl;
    } // copy1 destroyed here - destructor deletes Grade[] and Course[] arrays
    
    cout << "Scope exited - destructor called, arrays deleted" << endl;
    
    // --- 17. STATIC MEMBERS ---
    cout << "\n=== 17. STATIC MEMBERS ===" << endl;
    
    cout << "Total students created: " << Student::getTotalStudentsCreated() << endl;
    cout << "Current students in memory: " << Student::getCurrentStudentCount() << endl;
    
    // --- 18. REFERENCE & REFERENCE-RETURN ---
    cout << "\n=== 18. REFERENCE & REFERENCE-RETURN ===" << endl;
    
    Grade& gradeRef = student1[0];
    cout << "Grade reference before modification: " << gradeRef << endl;
    gradeRef. setScore(95.0);
    cout << "Grade reference after modification: " << student1[0] << endl;
    // Expected: Changed from 92 to 95
    
    const Grade& constGradeRef = student1.getHighestGrade();
    cout << "Highest grade (const ref): " << constGradeRef << endl;
    
    // --- 19. INLINE vs OUTLINE ---
    cout << "\n=== 19. INLINE vs OUTLINE IMPLEMENTATIONS ===" << endl;
    cout << "getName() is INLINE: " << student1.getName() << endl;
    cout << "calculateGPA() is OUTLINE: " << student1.calculateGPA() << endl;
    cout << "getGradeCount() is INLINE: " << student1.getGradeCount() << endl;
    cout << "calculateAverage() is OUTLINE: " << student1.calculateAverage() << endl;
    
    // --- 20. FUNCTION OVERLOADING (not operators) ---
    cout << "\n=== 20. FUNCTION OVERLOADING (addGrade) ===" << endl;
    
    Student student5("Charlie", "S005");
    
    Course biology("Biology", "BIO101", 4);
    student5.addGrade(Grade(88.0), biology);
    cout << "Added grade with Course object" << endl;
    
    student5.addGrade(Grade(92.0), "Chemistry");
    cout << "Added grade with course name string" << endl;
    
    student5.printGrades();
    
    cout << "\n=== Statistics ===" << endl;
    cout << "Total grades created: " << Grade::getTotalGradesCreated() << endl;
    cout << "Total students created: " << Student::getTotalStudentsCreated() << endl;
    cout << "Current students in memory: " << Student:: getCurrentStudentCount() << endl;
    
    printSeparator("Demo Complete!");
    
    return 0;
}