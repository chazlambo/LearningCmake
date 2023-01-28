#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

int main() {
	// Redirecting output to files
	ofstream fp_out;
	fp_out.open("../output.txt", ios::out);
	streambuf *coutbuf = cout.rdbuf();
	cout.rdbuf(fp_out.rdbuf());	

	// Max values of types
	cout << "Max 32-bit int = " << 2147483647 << "\n"; // Decimal
	cout << "Max 32-bit int = " << 0b0111'1111'1111'1111'1111'1111'1111'1111 << "\n"; // Binary
	cout << "Max 32-bit int = " << 0x7FFFFFFF << "\n"; // Hexadecimal (replaces 4 bits with each digit!)
	cout << "Max 32-bit int = " << numeric_limits<int>::max() << "\n";
	cout << "Max 32-bit uint = " << numeric_limits<unsigned int>::max() << "\n";
	cout << "Min 32-bit int = " << numeric_limits<int>::lowest() << "\n";
	cout << "Min 32-bit uint = " << numeric_limits<unsigned int>::lowest() << "\n\n";

	// Boss Fight Example
	short boss_health = 32000;
	cout << "Initial Boss Health: " << boss_health << "\n";
	boss_health += 400;	// Make a mistake by healing instead of damaging
	cout << "Increase Health by " << 400 << "\n";
	cout << "Boss Health After Healing: " << boss_health << "\n\n";

	cout << "Initial Boss Health: " << boss_health << "\n";
	boss_health += 400;	// Make a mistake by healing instead of damaging
	cout << "Increase Health by " << 400 << "\n";
	cout << "Boss Health After Healing: " << boss_health << "\n\n";
	cout << "Note the overflow\n\n";

	// What is the minimum value a short can hold?
	short n = -32768;
	cout << "n = " << n << "\n";
	n /= -2;
	cout << "n / -2 = " << n << "\n";
	n = -32768;
	n /= -1;
	cout << "n / -1 = " << n << "\n";
	cout << "Note that even division can cause overflow";

	// Averaging Example
	cout << "(2000'000'000 + 2000'000'000) / 2 = " << (2000'000'000 + 2000'000'000) / 2 << "\n";
	cout << "Note that both are signed int which can hold 2 billion but not 4 billion so overflow occurs before division\n";
	cout << "(2000'000'0000 + 2000'000'000) / 2 =" << (2000'000'0000 + 2000'000'000) / 2 << "\n";
	cout << "(2000'000'000 + 2000'000'0000) / 2 =" << (2000'000'000 + 2000'000'0000) / 2 << "\n";
	cout << "Automatically picks number type based on largest operator, in 2nd two averages the largest value couldn't fit so it went up a size";


	// Overflow before assigning
	long long my_money = 2000'000'000 + 2000'000'000;	// Right hand side is an int
	cout << "my_money = " << my_money << "\n";			// Overflow still occured even before value is assigned to variable
	my_money = static_cast<long long>(2000'000'000) + (2000'000'000);	// Avoid overflow by casting int to long long
	cout << "my_money = " << my_money << "\n\n";

	// Assigning negative to uint
	unsigned int f = -3;
	cout << "f(-3) = " << f << "\n";	// Overflow!

	// Overflow can happen because of implicit conversion as well
	// If conversions is what we really want we can use explicit cast to get rid of warning
	f = static_cast<unsigned int>(-3);
	cout << "f(-3) = " << f << "\n";	// Still overflows but doesn't throw error

	unsigned long long my_password = 1234567890;	// 64-bit
	cout << "my_password (1234567890) = " << static_cast<long long>(my_password) << "\n"; // This is fine
	unsigned long long safer_password = 12345678901234567890;
	cout << "my safer password (12345678901234567890) = " << static_cast<long long>(safer_password) << "\n\n";	// Garbage
	// Safer password > 2^63-1 <-- long long max
	// Safer psasword is too big to store in assigned long long


	// Truncation
	// Type is too small to hold a value, in case value is truncated (significant bits chopped off)
	cout << "9 / 4 = " << 9 / 4 << "\n";
	int zero = 0;
	//cout << "2 / 0 = " << 2 / zero << "\n"
	// Division by zero really messes things up.

	// Close Files and reset to standard I/O
	fp_out.close();
	cout.rdbuf(coutbuf);

	return 0;
}