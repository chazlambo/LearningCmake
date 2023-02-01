#include <iostream>
#include <vector>
#include <string>
#include <cassert>	// Gives assert command for debugging
#include <tuple>	// Allows functions to return multiple vals

#include <fstream>
#include <iomanip>

using namespace std;

// Default Parameters
double clamp_angle(double angle_in_degrees, double min_angle = 0, double max_angle = 360) {
	// This function can be called with one, two or three parameters.
	// If some parameters are not provided, the default values will be used.
	// Expression to be evaluated.
	// If this expression evaluaties to 0, this causes an assertion failure that terminates the program.

	assert(max_angle >= min_angle);

	if(angle_in_degrees > max_angle)
		return max_angle;
	if (angle_in_degrees < min_angle)
		return min_angle;
	return angle_in_degrees;
}

// Function Overloading
	// Functions can have the same name but diffferent parameter types
	// The function being called will be chosen based on the types being passed by the caller
	// At least one of the function inputs must be different

int my_max(int a, int b) {
	cout << "max_int\n";
	if (a > b) {
		return a;
	}
	return b;
}

double my_max(double a, double b) {
	cout << "max_double\n";
	if (a > b) {
		return a;
	}
	return b;
}

// Pass Parameters by References
// By declaring the parameter as "int& a" instead of "int a", the variable a
// inside the function is basically the same as whatever variable is used in 
// that slot when the function is called. Inside the function, "a" is called
// a reference to an int (i.e. it "refers" to another variable). This also
// means the function can modify "a" and change the value of not only "a" but
// that of the corresponding variable outside of the function as well.

int sum (const vector<int>& numbers) {
	// const: input is constant because we only want to read rather than write
	// &: would reference initial variable rather than create a new one
	// Not using & uses more memory and is slower
	int sum = 0;

	for (size_t i = 0; i < numbers.size(); ++i){
		sum += numbers[i];
	}

	return sum;
}

void introduce_vectors() {
	// A vector is a high-level concept that is similar to a C array.
	vector<int> numbers = { 1, 4, 16, 24, 91};
	cout << "Size of vector: " << numbers.size() << "\n";
	numbers.push_back(23);	// This pushes 23 to the back of the vector
	numbers.push_back(32);	// This vector now has 7 elements
	cout << "Size of vector after pushback: " << numbers.size() << "\n";

	cout << "Using ++i: \t\t";
	for (size_t i = 0; i < numbers.size(); ++i) {
		cout << numbers[i] << " ";
	}

	cout << "\n Using auto&&: \t\t";
	for (auto&& value : numbers) { // Auto doesn't care type of value and will iterate through each element
		cout << value << " ";
	}

	cout << "\n";
	cout << "The sum is " << sum(numbers) << "\n\n";
}

// Swap Two Values using References
void swap(int& a1, int& b1) {
	int temp = a1;
	a1 = b1;
	b1 = temp;
}

// Returning Multiple Values
// We can use std::tuple to return multiple values from a function
tuple<string, int, string> return_multiple_vals() {
	return make_tuple("Windows ", 10, " is not awesome.");
}

int main() {
	// Redirecting output to files
	ofstream fp_out;
	fp_out.open("../output.txt", ios::out);
	streambuf *coutbuf = cout.rdbuf();
	cout.rdbuf(fp_out.rdbuf());	

	// Default Parameters
	double angle = 90;

	// Check if angle is clamped for multiple cases
	cout << "Clamped Angle = " << clamp_angle(angle) << "\n";	// Default values
	cout << "Clamped Angle (30, 60) = " << clamp_angle(angle, 30, 60) << "\n";	// Set min and max to 30 and 60 respectively
	cout << "Clamped Angle (120, __ ) = " << clamp_angle(angle, 120) << "\n";	// Set min to 120 and max to default

	// Trying with invalid inputs gives an error thanks to assert
	// cout << "Clamped Angle (0, -10) = " << clamp_angle(angle, 0, -10) << "\n";

	// Function Overloading
	cout << "max of 10 and 20		= " << my_max(10, 20) << "\n";
	cout << "max of 10.0 and 20.0 	= " << my_max(10.0, 20.0) << "\n";
	cout << "max of 10.1 and 10.0 	= " << my_max(10.1, 10.0) << "\n";

	// Can't mix function parameter types
	// cout << "max of 10.1 and 10 	= " << my_max(10.1, 10) << "\n";

	// std::vector
	introduce_vectors();

	// Swap Two Values
	int a = 5;
	int b = 10;
	cout << "Using Hard Code in Main: \nBefore a = " << a << ", b = " << b << "\n";

	// Can't swap two values without a temporary variable
	int temp = a;
	a = b;
	b = temp;
	cout << "After a = " << a << ", b = " << b << "\n\n";

	// Make this into a function
	cout << "Using Function With References: \n Before a = " << a << ", b = " << b << "\n";
	swap(a,b);
	cout << "After a = " << a << ", b = " << b << "\n";

	// Multiple Return Values
	// Use std::tie to get the multiple returned values from a function
	string str1;
	int num;
	string str2;
	tie(str1, num, str2) = return_multiple_vals();
	cout << str1 << num << str2 << "\n";

	// Close Files and reset to standard I/O
	fp_out.close();
	cout.rdbuf(coutbuf);

	return 0;
}