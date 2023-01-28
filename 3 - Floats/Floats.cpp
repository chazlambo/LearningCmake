#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

int main() {
	// Redirecting output to files
	ofstream fp_out;
	fp_out.open("../output.txt", ios::out);
	streambuf *coutbuf = cout.rdbuf();
	cout.rdbuf(fp_out.rdbuf());	

	// ----------------------------------------------------
	// Loss of Accuracy when adding big and small numbers
	// ----------------------------------------------------

	const float big_float = 1e8;
	const float med_float = 1e3;
	const float lil_float = 1.0;
	cout << fixed;

	cout << "1e3 + 1.0 = " << med_float + lil_float << "\n"; // Works Fine
	cout << "1e8 + 1.0 = " << big_float + lil_float << "\n"; // Does not work, only gives 1e8

	// What about this case?

	cout << "1e8 + 4.0 = " << big_float + 4.0f << "\n"; // Still 1e8
	cout << "1e8 + 5.0 = " << big_float + 5.0f << "\n"; // Now 1e8+8
	// This means that it can't store integers 1e8 through 1e8+7 and has to estimate the closest value

	double big_double = 1e8;
	const double lil_double = 1.0;
	cout << "double: 1e8 + 1.0 = " << big_double + lil_double << "\n"; // Double has more bits and can handle this
	big_double = 1e16;
	cout << "double: 1e16 + 1.0 = " << big_double + lil_double << "\n"; // Has the same problem but just at higher values

	// ----------------------------------------------------
	// Innacuracy of floating point representation
	// ----------------------------------------------------

	// Does this work?
	float x = 2.0f;
	float x_clone = 8.0f - 6.0f;
	cout << setprecision(32);
	cout << "x = " << x << "\nx_clone = " << x_clone << "\n\n";
	// All is good :)

	// What about this?
	x = 0.25f;
	float x_wannabe = 0.75f - 0.50f;
	cout << setprecision(16);
	cout << "x = " << x << "\nx_wannabe = " << x_wannabe << "\n";
	cout << setprecision(32);
	cout << "x = " << x << "\nx_wannabe = " << x_wannabe << "\n\n";
	// Still good...

	// What about this?
	x = 0.2f;
	x_wannabe = 0.8f - 0.6f;
	cout << setprecision(16);
	cout << "x = " << x << "\nx_wannabe = " << x_wannabe << "\n";	// Note that x itself isn't even equal to 0.2, neither is x_wannabe but in a different way
	cout << setprecision(32);
	cout << "x = " << x << "\nx_wannabe = " << x_wannabe << "\n\n";	// Note that it's only accurate up to 7 decimal digits
	if (x == x_wannabe){
		cout << "x == x_wannabe!\n\n";
	}
	else {
		cout << "Don't use == to compare floats!\n\n";
	}
	// If you want to compare floats then don't use ==, take the difference and check if the difference is greater than some threshold

	// ----------------------------------------------------
	// Associativity
	// ----------------------------------------------------

	float a = 1e8f;
	float b = 1.83450e5f;
	float c = 5e1f;

	cout << "(a + b) + c = " << (a + b) + c << "\n";
	cout << "a + (b + c) = " << a + (b + c) << "\n\n";
	// Note that the associative property does not hold when dealing with floats and large numbers
	// Associative property can hold with small numbers or powers of 2 but it's not always true

	// ----------------------------------------------------
	// Number of Significant Decimal Digits
	// ----------------------------------------------------

	// A float "on average" has 7 decimal digits of accuracy, due ot the fact that
	// it has 23 bits of mantissa, and roughly every 3 bits make up a decimal digit
	// so 23 / 3 ~= 7

	cout << 0.123456789f << "\n";
	cout << 0.1234567890123456789f << "\n\n";
	// Note that the printed value is only accurate to 7 digits

	// The number of significant decimal digits for a double is between 16 and 17
	cout << 0.123456789 << "\n";
	cout << 0.1234567890123456789 << "\n\n";

	// ----------------------------------------------------
	// Numeric Limits
	// ----------------------------------------------------

	// The numeric limits of floats and doubles are also a bit different than
	// we've seen with signed integers. numeric_limits<float>::min() is
	// actually the smallest number > 0 that can be represented in normalized 
	// form, not the smallest number representable by a float, which would be
	// -std::numeric_limits<float>::max();

	// Note: float can represent positive numbers smaller than numeric_limits<float>::min(), just not in normalized form

	cout << scientific;
	cout << "Range for floats:"
		<< "\nMax float = " << numeric_limits<float>::max()
		<< "\nMin float = " << -numeric_limits<float>::max()
		<< "\nLowest float = " << numeric_limits<float>::lowest()	// Lowest value that can be represented using 32-bit single precision float
		<< "\nMin normalized float = " << numeric_limits<float>::min() << "\n\n";	// Smallest positive number that can be represented using 32-bit single precision float
	// Any value over max will overflow
	// Any value that is less than the smallest positive number that can be represented will cause an underflow

	cout << scientific;
	cout << "Range for doubles:"
		<< "\nMax double = " << numeric_limits<double>::max()
		<< "\nMin double = " << -numeric_limits<double>::max()
		<< "\nLowest double = " << numeric_limits<double>::lowest()	// Lowest value that can be represented using 32-bit single precision float
		<< "\nMin normalized double = " << numeric_limits<double>::min() << "\n\n";	// Smallest positive number that can be represented using 32-bit single precision float

	// ----------------------------------------------------
	// Casting
	// ----------------------------------------------------

	float f = 12.614156f;
	int i = static_cast<int>(f);

	// Any decimal numbers in the float are simply chopped off and discarded
	// No rounding is performed
	cout << "f = " << f << ", i = " << i << "\n";

	// Any decimal numbers in float are simply chopped off and discarded
	// Truncation is performed
	// Compiler will usually issue a warning
	i = f + 0.5f;
	cout << "f = " << f << ", i = " << i << "\n";

	// Going the other way is okay, as long as the number is in the range of the float
	i = 15;
	f = static_cast<float>(i);
	cout << "f = " << f << ", i = " << i << "\n";

	// What happens when we cast a bigger int to a float?
	i = 987654321;
	f = static_cast<float>(i);
	cout << "f = " << f << ", i = " << i << "\n"; // f is only accurate to 7 digits
	int j = static_cast<int>(f);
	cout << "f = " << f << ", j = " << j << "\n\n"; // We don't get int we originally started with

	// Casting a double to a flaot can have the same issues as casting a long long
	// to an int. Sinc ethe float has less space to store the number and can't 
	// represent as large a range the number will be rounded, in the case of too
	// large a number it gets rounded to infinity. This example will be ok,
	// float has enough prevision to represent this number

	double d = 2e10;
	f = static_cast<float>(d);
	cout << "d = " << d << ", f = " << f << "\n";

	// But there are some numbers that are larger than float can store, for
	// this value a float doesn't have enough bits to store the exponent
	// and it gets clamped to the max value float can store, infinity

	d = 2e145;
	f = static_cast<float>(d);
	cout << "d = " << d << ", f = " << f << "\n\n";
	// Double can't accurately represent number and float gets rounded to infinity

	// ----------------------------------------------------
	// Special Numbers
	// ----------------------------------------------------
	double zero = 0;
	cout << 1.0 / zero << "\n";
	cout << -1.0 / zero << "\n";
	cout << 0.0 / zero << "\n";
	cout << asin(-2) / zero << "\n"; // sin^-1 only has values between -1 and 1 so what happens when we take asin of 2?
	// Returns +/- infinity and NaN
	// +/- infinity is represented with an exponent of 255 (0xFF) and a mantissa of zero
	// NaN is represented with an exponent of 255 and a non-zero mantissa
	cout << "+infinity = " << numeric_limits<double>::infinity()
		 << "\n-infinity = " << -numeric_limits<double>::infinity()
		 << "\nNaN = " << numeric_limits<double>::quiet_NaN() << "\n";

	// Any computations involving NaN will also return NaN
	cout << "10 * 0.5 + 3 + NaN = " << 10.0 * 0.5 * 3.0 + numeric_limits<double>::quiet_NaN() << "\n";

	// NaN != NaN; use std::isnan(x) instead of (x != x)
	cout << "NaN == NaN: " << boolalpha << (numeric_limits<double>::quiet_NaN() == numeric_limits<double>::quiet_NaN()) << "\n";
	cout << "isnan(NaN): " << boolalpha << isnan(numeric_limits<double>::quiet_NaN()) << "\n\n";

	// Close Files and reset to standard I/O
	fp_out.close();
	cout.rdbuf(coutbuf);

	return 0;
}