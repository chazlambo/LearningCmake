#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// Function Declarations
void factorial_example(unsigned long long n);
int fibonnaci_normal(unsigned long long n);
int fibonnaci_recursive(unsigned long long n);
int fib(unsigned long long x);
int factorial(long long n);

// Main Function
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

	unsigned long long n;
	//Input n value
	cin >> n;
	factorial_example(n);
	cin >> n;
	fibonnaci_normal(n);
	std::cout << "\n";
	fibonnaci_recursive(n);


	// Close Files and reset to standard I/O
	fp_in.close();
	fp_out.close();
	cin.rdbuf(cinbuf);
	cout.rdbuf(coutbuf);
	
	return 0;
}

// User defined functions


void factorial_example(unsigned long long n) {
	unsigned long long fac = 1;
	//Calculation with for statement
	for (int i = 1; i <= n; ++i) {
		fac = fac * i;
	}
	cout << "(Normal) Factorial of " << n << " = " << fac << "\n";

	//Calculation with recursive function
	cout << "(Recursive) Factorial of " << n << " = " << factorial(n) << "\n";
}

int factorial(long long n)
{
	if (n > 1)
		return n * factorial(n - 1); //Function calls itself
	else
		return 1;
}

int fibonnaci_normal(unsigned long long n) {
	int t1 = 0, t2 = 1, nextTerm = t1 + t2, nextTermIndex = 1;
	cout << "(Normal) Fibonnacci Series: " << t1 << ", ";
	if (n == 0) return 0;
	cout << t2 << ", ";
	if (n == 1) return 0;

	while (nextTermIndex < n) {
		nextTermIndex = nextTermIndex + 1;
		cout << nextTerm << ", ";
		t1 = t2;
		t2 = nextTerm;
		nextTerm = t1 + t2;
	}
	return 0;
}

int fibonnaci_recursive(unsigned long long n) {
	int t1 = 0, t2 = 1, nextTerm = t1 + t2, nextTermIndex = 1;
	cout << "(Recursive) Fibonnacci Series: " << t1 << ", ";
	if (n == 0) return 0;
	cout << t2 << ", ";
	if (n == 1) return 0;

	while (nextTermIndex < n) {
		nextTermIndex = nextTermIndex + 1;
		cout << fib(int(nextTermIndex)) << ", ";
	}
	return 0;
}

int fib(unsigned long long x) {
	if ((x == 1) || (x == 0)) {
		return(x);
	}
	else {
		return(fib(x - 1) + fib(x - 2));
	}
}