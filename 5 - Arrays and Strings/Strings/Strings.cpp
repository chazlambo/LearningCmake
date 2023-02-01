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

using namespace std;

int main() {
	// Redirecting output to files
	ofstream fp_out;
	fp_out.open("../output.txt", ios::out);
	streambuf *coutbuf = cout.rdbuf();
	cout.rdbuf(fp_out.rdbuf());	

	// --------------------------------
	// char
	// --------------------------------

	// ASCII is a simple and widely used format for storing character data,
	// it's an encoding that maps bit-patterns of 8 bits to characters of the
	// English alphabet, along with some other special characters.
	//
	// The character 'a' in ASCII is represented as 0b0110'0001 (97 in decimal, conveniently 61 in hex).
	// A full list of character mappings is on Wikipedia:
	// https://en.wikipedia.org/wiki/ASCII
	//
	// Because ASCII uses 8 bits to encode characters it can only represent 256
	// different symbols, which is clearly not going to work on an international
	// scale. To solve this problem the Unicode standard was created.

	// In C++ we can declare an 8 bit character variable by specifying its
	// type as 'char'
	char a = 'a';
	// We can print out special characters like quotes "  by escaping
	// them using a backslash. These are known as escape sequences, \n is also an
	// escape sequence allowing us to print out the newline character.
	std::cout << "a = \"" << a << "\"\n";
	// But it's really just bits (or a number depending on how you squint) that
	// the ASCII standard says should appear in our console as the letter 'a'
	std::cout << "a = " << std::bitset<8>(a) << "\n"
		<< "a = " << static_cast<int>(a) << "\n";
	a = 8; // this is fine, you don't always have to assign a "character" to a
		   // variable of type char. Think of it as yet another integer type.

		   // QUESTION: What will get printed?
		   // A) 0
		   // B) 1
		   // C) 48
		   // ANSWER: C), '8' == 56
	std::cout << '8' - 8 << '\n';

	// QUESTION: What will get printed?
	// A) 2 and 196
	// B) 2 and 195
	// C) 2 and 20
	// D) none of the above
	// ANSWER:  A)
	std::cout << "c - a = " << 'c' - 'a' << "\n";
	std::cout << "c + a = " << 'c' + 'a' << "\n";
	std::cout << "\n";

	// We can use the set of functions defined in <cctype> to check if a given
	// character is alphabetic/numeric/space/punctuation
	// QUESTION: Vote on the results. True/False
	std::cout << std::boolalpha; // print true/false instead of 1/0
	std::cout << static_cast<bool>(std::isalpha('1')) << "\n"; // false
	std::cout << static_cast<bool>(std::isalpha('a')) << "\n"; // true
	std::cout << static_cast<bool>(std::ispunct('\'')) << "\n"; // true
	std::cout << static_cast<bool>(std::ispunct(';')) << "\n"; // true
	std::cout << static_cast<bool>(std::isdigit('2')) << "\n"; // true
	std::cout << static_cast<bool>(std::isdigit('1')) << "\n"; // true
	std::cout << static_cast<bool>(std::isdigit('O')) << "\n"; // false
	std::cout << static_cast<bool>(std::isspace('_')) << "\n"; // false
	std::cout << static_cast<bool>(std::isspace('\t')) << "\n"; // true
	std::cout << "\n";
	// --------------------------------
	// Strings
	// --------------------------------
	// The C++ standard library provides the std::string type, which gives us
	// methods for easily working with sequences of characters
	//
	// Internally the std::string has a container it resizes to store the
	// characters in the string, previously we've encountered char[] which are
	// arrays of characters of a fixed size.
	const std::string university = "University of ";
	const std::string state = "Utah";
	// We can add strings to compose them:
	std::cout << "We're at " << university + state << "\n";
	// Strings can also tell us how many characters are in them
	std::cout << "Utah is " << state.size() << " characters long\n";

	// Example: determine if a string is a cyclic permutation of another
	const std::string str1 = "in Soviet Union television watches you ";
	const std::string str2 = "television watches you in Soviet Union ";
	const std::string str3 = "in Soviet Union you watch   television ";
	std::string tmp = str1 + str1;

	// find str2 in str1, return the position of str2 if found\
	            // Is this True? Yes/No
	if (str1.size() == str2.size() && tmp.find(str2) != std::string::npos)
		std::cout << "str1 and str2 are cyclic permutations\n";
	else
		std::cout << "str1 and str2 are NOT cyclic permutations\n";

	// Is this True? Yes/No
	if (str1.size() == str3.size() && tmp.find(str3) != std::string::npos)
		std::cout << "str1 and str3 are cyclic permutations\n";
	else
		std::cout << "str1 and str3 are NOT cyclic permutations\n";
	std::cout << "\n";
	// Compare two strings
	// 0 Equal, != 0 Unequal

	std::string str_1("green apple");
	std::string str_2("red apple");

	if (str_1.compare(str_2) != 0) // Compare if strings are the same
		std::cout << str_1 << " is not " << str_2 << '\n';

	if (str_1.compare(6, 5, "apple") == 0) //Compare beginning from 6th position for next 5 characters
		std::cout << "still, " << str_1 << " is an apple\n";

	if (str_2.compare(str_2.size() - 5, 5, "apple") == 0)
		std::cout << "and " << str_2 << " is also an apple\n";

	std::string apple = str_2.substr(4, 5);
	if (str_1.compare(6, 5, apple) == 0)
		std::cout << "therefore, both are apples\n";
	std::cout << "\n";

	// --------------------------------
	// Standard Input (std::cin)
	// --------------------------------
	// The counterpart of std::cout is std::cin, which we use to get inputs
	// from users. cin reads input separated by whitespace, see what
	// happens if we enter: 'jimmy-bob 32' instead of waiting for the prompt
	// to enter our age? Will it still read things properly?

	std::string name;
	int age;
	std::cout << "Enter your name: ";
	std::cin >> name;
	std::cout << "Enter your age: ";
	// similar to strings we can also read into ints, floats, doubles, etc.
	// and the actual number value will be parsed from the string
	// If we assign "bob" for the age below, will this code compile?
	std::cin >> age;

	while (true) {
		int x = 0;
		std::cin >> x;
		// hello world the X

		// Handle case where reading input failed (e.g. they didn't enter a number)
		if (std::cin.fail()) {
			std::cout << "Your age must be an integer! Making you a newborn...\n";
			// Unset failed read bit
			std::cin.clear();
			// Ignore remaining bad input using ignore. ignore will read and
			// discard characters until it finds and discards the one was pass
			// (a newline here) or has discarded some number of characters
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		std::cout << x << '\n';
	}
	


	// Close Files and reset to standard I/O
	fp_out.close();
	cout.rdbuf(coutbuf);

	return 0;
}
