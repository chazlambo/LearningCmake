#include<iostream>
#include<fstream>
#include<iomanip>
#include<vector>
using namespace std;

void test_array_1();
void printarray(int arg[], int length);

#define WIDTH 5
#define HEIGHT 3

void test_array_22();

void test_chars();
void test_vectors();
void printvector(vector<int>myints);

int main() {
	// Redirecting output to files
	ofstream fp_out;
	fp_out.open("../output.txt", ios::out);
	streambuf *coutbuf = cout.rdbuf();
	cout.rdbuf(fp_out.rdbuf());	


	cout << "1D Arrays:\n";
	test_array_1();

	cout << "\n2D Array:\n";
	test_array_22();

	cout << "\nCharacters Test: \n";
	test_chars();

	cout << "\n STL Vector Test: \n";
	test_vectors();


	// Close Files and reset to standard I/O
	fp_out.close();
	cout.rdbuf(coutbuf);

	return 0;
}

void test_array_1() {
	int firstarray[3] = { 5, 10, 15 };
	int secondarray[] = { 2, 4, 6, 8, 10 };
	printarray(firstarray, 3);
	printarray(secondarray, 5);
}

void printarray(int arg[], int length) {
	for (int n = 0; n < length; ++n) {
		cout << arg[n] << " ";
	}
	cout << "\n";
}

void test_array_22() {
	int jimmy[HEIGHT][WIDTH];
	int n, m;
	for (n = 0; n < HEIGHT; n++) {
		for (m = 0; m < WIDTH; m++){
		jimmy[n][m] = (n + 1) * (m + 1);
		}
	}
	for (n = 0; n < HEIGHT; n++) {
		printarray(jimmy[n], WIDTH);
	}
}

void test_chars() {
	// Note: Characters use single quotation marks
	// 'i' = 'i';
	// "i" = {'i','\0'};

	char myword1[] = { 'H', 'e', 'l', 'l', 'o', '\0' }; //Long form, '\0' denotes end of character array.
	char myword2[] = "Hello"; //Same thing

	cout << myword1 << "\n";
	cout << myword2 << "\n";
	cout << "Change one character at a time" << "\n";

	myword2[4] = ' ';
	cout << myword2 << "\n";

	myword2[1] = 'i';
	cout << myword2 << "\n";
	
	myword2[2] = '\0';
	cout << myword2 << "\n";
}

void test_vectors() {
	std::vector<int> myints;
	// push_back appends an element to the sequence
	myints.push_back(5);
	myints.push_back(2);
	myints.push_back(3);
	// The size method can be used to get how many elements are within
	cout << "I have " << myints.size() << " ints\n";
	// We can use [] to get an element at some index
	cout << "The first one is " << myints[0] << "\n";
	cout << "The entire array is: \n";
	printvector(myints);
}

void printvector(vector<int>myints) {
	for (int n = 0; n<int(myints.size()); ++n) {
		cout << myints[n] << ' ';
	}
	cout << '\n';
}