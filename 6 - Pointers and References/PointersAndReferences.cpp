// Pointers and memory allocations

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstddef>
#include <vector>
#include <string>
#include <cstdint>
#include <cassert>
#include <cstring>

using namespace std;


int main(int argc, char* argv[])
{
    // Redirecting input and output to files
    ifstream fp_in;                         // Create I/O file streams
    ofstream fp_out;
    fp_in.open("../input.txt", ios::in);    // Open I/O file streams
    fp_out.open("../output.txt", ios::out);
    streambuf *cinbuf = cin.rdbuf();        // Save old buf
    streambuf *coutbuf = cout.rdbuf();
    cin.rdbuf(fp_in.rdbuf());               // Redirect cin and cout to file streams
    cout.rdbuf(fp_out.rdbuf());     

    //--------------------------------
    // Memory addresses, & operator, * operator
    //--------------------------------

    // Every variable has a unique address in memory associated with it. To get
    // this address, use the & operator. In Visual Studio, we can look at the
    // contents of every address in memory using the Memory debugging window
    // (Debug -> Windows -> Memory)    
    int a = 10;
    int* address_of_a = &a;	// the type of the address of an int is int* (called
                            // pointer-to-int)
                            // The variable address_of_a stores the address
                            // of the variable a (in bytes).
    std::cout << "address of a = " << address_of_a << "\n";

    // Open the memory debugger to see 'a' and its address in memory

    // To access the original variable from a pointer, use the * operator (called
    // de-reference operator)
    *address_of_a = 20;
    // QUESTION: Will a = 10 here? Yes/No
    std::cout << "a = " << a << "\n";

    // In fact, since the type of *address_of_a is an int, *address_of_a can
    // occur in any context that an int could
    *address_of_a = *address_of_a * 10; //same as a = a * 10
    // QUESTION: Will 'address_of_a' be 10x its value here? Yes/No
    std::cout << "address of a = " << address_of_a << "\n";
    // QUESTION: Will 'a' be 10x its value here? Yes/No
    std::cout << "a = " << a << "\n";





    // Unlike a reference, which "sticks" to the variable that it refers to,
    // a pointer can be re-assigned to point to other variables.
    int a2 = 30;
    int& a_ref = a;
    std::cout << "address of a_ref = " << &a_ref << " address of a = " << address_of_a << "\n";
    a_ref = a2; // This statement assigns a2 to a (equivalent to a = a2), but does not make a_ref
                // "points" to a2
    // QUESTION: Will 'a' be 30 here? Yes/No
    std::cout << "a = " << a << "\n";
    std::cout << "address of a_ref = " << &a_ref << "\n";

    // But we can reassign a pointer
    address_of_a = &a2;
    std::cout << "address of a2 = " << address_of_a << "\n";
    std::cout << "a2 = " << *address_of_a << "\n";






    // QUESTION: Can we define a pointer without initializing it? Yes/No
    int* address; // this pointer will hold some random address

    // QUESTION: Can we use pointer without initializing it? Yes/No
    //std::cout << "address = " << address << "\n";
    //NEGATIVE: THIS WILL GIVE US AN ERROR IF WE UNCOMMENT

    // But a pointer can be assigned a special value, nullptr, to mean that the
    // pointer points to nothing.
    address = nullptr; // if you come from a C background, DO NOT use NULL, or 0

    // You can't dereference a nullptr, so unless you know for sure your pointer
    // is not nullptr, always check for that possibility.
    address = address_of_a;
    if (address != nullptr)
        std::cout << "valued pointed to by address = " << *address << "\n";

    // You can't also just assign any integer to a pointer
    // address = 123; // will not compile

    // Although a pointer stores a number (an address), pointer types are
    // different from regular integer types (int, unsigned int, etc). You can't
    // use, say an int, to store addresses:
    // int address = &a; // will not compile

    // QUESTION: How can we convert between integers and pointers?



    //--------------------------------
    // Pointer arithmetics
    //--------------------------------

    // It's illegal to have expressions combining pointers of different types
    double b = 3.14;
    double* address_of_b = &b;
    // The following assignment is illegal
    //address_of_a = address_of_b;

    // But we can compare and subtract (but not add/multiply/etc) pointers of
    // the same type
    double c = 5.0;
    double* address_of_c = &c;

    // QUESTION: What will get printed?
    // A) true
    // B) false
    // C) undefined
    std::cout << std::boolalpha << "are b and c the same variable? " << (address_of_c == address_of_b) << "\n";
    // ptrdiff_t is a type to store differences in addresses (it's basically a
    // signed integer)
    std::ptrdiff_t address_diff_b_c = address_of_b - address_of_c;
    std::cout << "&c - &b = " << address_diff_b_c << "\n";

    // We can also add/subtract an int from a pointer to get another pointer
    int array_of_ints[] = { 0, 1, 2, 3, 4 };
    // QUESTION: Are these same? Yes/No
    // ANSWER: NO

    int* ptr_int = &array_of_ints[0];   // pointer that goes to specified element
    int* ptr_int_ = array_of_ints;      // pointer defaults to first element of array

    std::cout << (ptr_int == ptr_int_) << std::endl;



    // QUESTION: What value is printed here?
    // A: 0
    // B: 1
    // C: 2
    // D: 3
    // E: 4

    // ANSWER: D
    std::cout << *(ptr_int + 3) << "\n"; //Note that we aren't adding 3 to current value, we're adding 3 bytes which is a value of 12
    std::cout << "Using Pointer Arithmetic: " << * (ptr_int + 3) << "\nUsing Array Indexing: " << array_of_ints[3] << "\n";  // These are the same things!
    //Both ways print the 4th element of the array!
    

    // Note that although a pointer stores a byte address, when you add a number
    // N to a pointer, the pointer is not moved by N bytes, but N * sizeof(type)
    // bytes, with "type" being the type of the variable being pointed to.
    std::string array_of_strings[] = { "time", "waits", "for", "no", "one" };
    std::string* str_ptr = &array_of_strings[3];


    // QUESTION: What string is printed here?
    // A: time
    // B: waits
    // C: for
    // D: no
    // E: one

    //ANSWER: waits

    std::cout << *(str_ptr - 2) << "\n";


    // Close Files and reset to standard I/O
    fp_in.close();
    fp_out.close();
    cin.rdbuf(cinbuf);
    cout.rdbuf(coutbuf);

    return 0;
}
