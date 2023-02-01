#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <sstream>

// The string header provides std::string
#include <string>

using namespace std;

int main() {
	// Redirecting input and output to files
	ifstream fp_in;							// Create I/O file streams
	ofstream fp_out;
	fp_in.open("../input.txt", ios::in);	// Open I/O file streams
	fp_out.open("../output.txt", ios::out);
	streambuf *cinbuf = cin.rdbuf();		// Save old buf
	streambuf *coutbuf = cout.rdbuf();
	cin.rdbuf(fp_in.rdbuf());				// Redirect cin and cout to file streams
	cout.rdbuf(fp_out.rdbuf());	


	// ----------------------------------
	// Line Based Input
	// ----------------------------------

	// Instead of taking whitespace-delimited input like cin >> name
	// we can read entire lines of text using std::getline
	// this will instead read '\n' delimited input

	// This is useful if say we wanted to count the number of lines in a file
	string line;
	cout << "Enter a line: ";

	while (getline(cin, line)) {
		if (line == "quit") {
			break;	// Note, it's case sensitive
		}
		cout << "Entered: " << line << "\n";
		cout << "Enter a line: ";
	}

	string name;
	int age;
	cout << "\n\nEnter your name: ";
	cin >> name;
	cout << "\nEnter your age: ";
	cin >> age;
	cout << "\n Where do you live?";

	// Last entered input ended with a newline character so we need to 'clean' the input
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, line);
	cout << "\n\nYour name is " << name << " and you're " << age << " years old.\n";
	cout << "You live at '" << line << "'\n";

	// There's a small issue mixing whitesapce-delimited input (cin >> age for example)
	// with line delimited input like getline. When we read using std::cin >> age the
	// newline character is left in the stream by cin which getline will read as an
	// empty line. Instead we need to ignore any remaining newlines with ignore, which
	// will keep reading characters and discarding them until it finds and discards the
	// desired character. It also takes a max number of characters to ignore
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	// NOTE THE USE OF WHITE SPACE INSTEAD OF NEW LINE IN THE INPUT FILE
	// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

	// Close Files and reset to standard I/O
	fp_in.close();
	fp_out.close();
	cin.rdbuf(cinbuf);
	cout.rdbuf(coutbuf);

	return 0;
}
	