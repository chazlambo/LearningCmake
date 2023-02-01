#include<iostream>
#include <cassert>
#include <fstream>
#include <iomanip>

using namespace std;

void useless() {
	// Any code for the function to execute, in this case nothing
}

void say_hello() {
	std::cout << "Hello there!\n\n";
}

double final_grade(const double midterm,
	const double final_exam,
	const double homework)
{
	//-----------------------------------
	// Parameter Validation
	//-----------------------------------
	// A student's grade should be within 0 to 100 for each test, we can have
	// our function requrie that these values are within range by testing with
	// asster. Calling assert(false) will result in our program aborting so
	// we can use this to error out if the caller gives us invalid values
	// Assert only works in debug mode
	// Each score must be within [0, 100]
	assert(midterm >= 0.0 && midterm <= 100.0);
	assert(final_exam >= 0.0 && final_exam <= 100.0);
	assert(homework >= 0.0 && homework <= 100.0);

	// Just like in main where we return an integer to the caller (the runtime)
	// our functions can return values to their callers using return.
	return 0.2 * midterm + 0.4 * final_exam + 0.4 * homework;
}

// A function must be declared before it can be called so that its name
// is in scope, however we can wait to define it until later.

void print_student_score(std::string name, const double midterm, const double final_exam, const double homework);

//-----------------------------------
// Global Scope
//-----------------------------------
const double MAX_STUDENT_GRADE = 100.0;
const double MIN_STUDENT_GRADE = 0.0;

int main() {
	// Redirecting output to files
	ofstream fp_out;
	fp_out.open("../output.txt", ios::out);
	streambuf *coutbuf = cout.rdbuf();
	cout.rdbuf(fp_out.rdbuf());	

	double local = 10.0;
	//-----------------------------------
	// Scope and Shadowing
	//-----------------------------------
	// A variable is only accessible while it's in scope. We can introduce
	// a new scope while in any function with a pair of {}
	{ // new scope begins here
		int a = 10;
		std::cout << "a = " << a << "\n";
	} // new scope ends here
	//std::cout << "a = " << a << "\n" <-- variable doesn't exist and can't be accessed outside the scope

	// Let's count how many times this for loop executes
	int counter = 0;
	for (int counter = 0; counter < 4; ++counter) { //Only valid because the two counter variable exist in a different scope
		std::cout << "In Loop Counter = " << counter << "\n";
	}
	std::cout << "Out of Loop Counter = " << counter << "\n\n";

	// It's legal to declare a variable with the same name as one in an 
	// enclosing scope. This can easily lead to confusion and bugs tough,
	// and isn't recommended
	// When accessing a variable we pick the innermsot one if there are
	// name conflicts. This is known as shadowing, as the inner variable
	// shadows the outer one. Most compilers should emit a warning about
	// this if you set the warning level properly

	int shadowed = 10;
	{
		int shadowed = 20;
		shadowed = 30; // shadowed here refers to the one declared on the previous line and initialized to 30
		std::cout << "shadowed = " << shadowed << "\n";
	}
	//shadowed here refers to the one declared above the block and initialized to 10
	std::cout << "shadowed = " << shadowed << "\n\n";

	//-----------------------------------
	// Calling Functions
	//-----------------------------------

	//Call our simple functions
	useless();
	say_hello();

	print_student_score("Lisa Simpson", 100.00, 100.00, 100.00);
	print_student_score("Morty", 70.0, 95.0, 60.0);

	// Close Files and reset to standard I/O
	fp_out.close();
	cout.rdbuf(coutbuf);
}

void print_student_score(std::string name, const double midterm, const double final_exam, const double homework) {
	// Functions can call other functions as well. We can use the final_grade
	// function to compute the total score in a function that prints out a
	// summary of a student's grades in the course
	std::cout << "Student: " << name
		<< "\n\tMidterm: " << midterm
		<< "\n\tFinal: " << final_exam
		<< "\n\tHomework: " << homework
		<< "\n\tOverall: " << final_grade(midterm, final_exam, homework)
		<< "\n";
}