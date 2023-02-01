#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <sstream>
// The string header provides std::string
#include <string>
// cstring provides methods for dealing with arrays of characters as strings
// you should always prefer std::string but we need strcmp from here
// for a cool demo
#include <cstring>
#include <bitset>
#include <cctype>

int main() {
	// Redirecting output to files
	ofstream fp_out;
	fp_out.open("../output.txt", ios::out);
	streambuf *coutbuf = cout.rdbuf();
	cout.rdbuf(fp_out.rdbuf());	

	// ---------------------------------
	// char
	// ---------------------------------

	// ASCII is a simple and widely used format for storing character data
	// it's an encoding that maps bit-patterns of 8 bits to characters of the
	// English alphabet, along with some other special characters
	//
	// The character 'a' in ASCII is represented as 0b0110'0001 (97 in decimal, conveniently 61 in hex);
	// A full list of character mappings is on Wikipedia:
	// https://en.wikpedia.org/wiki/ASCII
	//
	// Because ASCII uses 8 bits to encode characters it can only represent 256
	// different symbols, which is clearly not going to work on an international
	// scale. To solve this problem the Unicode standard was created.
	//
	// In C++ we can declare an 8 bit character variable by specifying its
	// type as 'char'
	char a = 'a';
	// We can print out special characters like quotes " by escaping
	// them using a backslash. These are known as escape sequences, \n is also an
	// escape sequence allowing us to print out the newline character.
	cout << "a = \"" << a << "\"\n";
	


	// Close Files and reset to standard I/O
	fp_out.close();
	cout.rdbuf(coutbuf);

	return 0;
}