#include<iostream>
#include <fstream>	// File I/O
#include <iomanip>	// Format Manipulation
#include<string>

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

	// Basic Input/Output
	int count;
	cout << "Hello World\n";
	cin >> count;

	cout << count << "\n";
	string test_string;
	cout << "Enter test string: \n";
	cin >> test_string;
	cout << "You entered: " << test_string << "\n";

	// If Statement
	bool statement = true;
	if (statement) {
		cout << "TRUE\n";
	}
	else {
		cout << "FALSE\n";
	}
	cout << "\n";

	// For Loop
	int numloop;
	cin >> numloop;
	cout << "Loops: " << numloop << "\n";
	for (int iterator = 0; iterator < numloop; iterator++) {
		cout << iterator << " ";
	}
	cout << "\n\n";

	// Combining Everything
	int numcases;
	int val;

	cin >> numcases;
	for (int i = 0; i < numcases; i++) {
		cout << "Case: " << i << "\n";
		cin >> val;
		cout << "Values entered is: " << val << "\n";
		if (val > 0) {
			cout << "Value is positive\n";
		}
		else if (val < 0) {
			cout << "Value is negative\n";
		}
		else {
			cout << "Value is zero\n";
		}
		if (abs(val) > 5) {
			cout << "Value has magnitude greater than 5\n";
		}
		cout << "\n";
	}

	bool running = true;
	int x = 1;
	cin >> count;
	cout << "Will now count to " << count << ":\n";
	while (running) {
		cout << x << " ";
		if (x >= count) {
			running = false;
		}
		else {
			x++;
		}
	}
	cout << endl;


	// Close Files and reset to standard I/O
	fp_in.close();
	fp_out.close();
	cin.rdbuf(cinbuf);
	cout.rdbuf(coutbuf);

	return 0;
}