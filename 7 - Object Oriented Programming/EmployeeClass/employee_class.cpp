#include <iostream>
#include <vector>
#include <string>

// ----------------------------------------
//	Classes - Motivation Written
// ----------------------------------------
// Lets define an Employee class to hold all the information we care about
// for a single employee

class Employee {
	// We want these to be private, once these are set other code shouldn't
	// be able to freely change them
private:
	std::string name;
	std::string position;
	std::string location;
	int payrate;

public:
	// Our constructor takes a name, position, location and payrate to
	// setup our employee. Notice that names of parameters and
	// those in the member initializer list can be the same, but be careful
	// if you use these parameters in the constructor due to the name shadowing
	// It's far safer to just use different names
	
	Employee(const std::string &employee_name, const std::string &employee_position,
		const std::string &employee_location, const int employee_payrate)
		: name(employee_name)
		, position(employee_position)
		, location(employee_location)
		, payrate(employee_payrate)
	{
		std::cout << "Parameterized C'tor called \n";
	}

	// If we provide a constructor no default one is provided for us so we must also
	// add a default empty constructor
	// Employee e;
	Employee() 
	{
		std::cout << "Default C'tor called \n";
	}

	//Copy constructor
	//Employee e1 = e;
	Employee(const Employee& other):
		name(other.name),
		position(other.position),
		location(other.location),
		payrate(other.payrate)
	{
		std::cout << "Copy C'tor called \n";
	}

	// Copy assignment
	//e1 = e; other is alias to e and this will point to e1
	Employee& operator=(const Employee& other)
	{
		std::cout << "Copy assignment called \n";
		// avoid self assignment
		if (this != &other)
		{
			name = other.name;
			position = other.position;
			location = other.location;
			payrate = other.payrate;
		}
		return *this;
	}

	//Destructor
	~Employee() {
		std::cout << "D'tor called \n";
	}

	// We can provide read-only access to the members by providing getters.
	// A getter simply returns the member variable but can also do some
	// other setup or whatever else must be done to return the data
	// We also mark these functions as const to indicate that the object
	// that they are called on is not changed internally by calling the
	// function. For example we could not change the member variables in these
	// functions because the object is a const variable
	std::string get_name() const { return this->name; }
	// Dangerous - returns refernce to private data member
	std::string& get_name2() { return name; }
	std::string get_position() const;
	std::string get_location() const;
	int get_payrate() const;
	void set_name(const std::string& new_name) { name = new_name; }
	
	void set_payrate(int new_payrate)  { payrate = new_payrate; }
	// Can we declare the following function? YES/NO
	//Answer: NO
	//void set_payrate(int new_payrate) const { payrate = new_payrate; }

};

std::string Employee::get_position() const { return position; }

std::string Employee::get_location() const { return location; }

int Employee::get_payrate() const { return payrate; }

// std::cout << Employee() << Employee() << "\n";
std::ostream& operator<<(std::ostream& os, const Employee& emp)
{
	os << "Employee: " << emp.get_name()
		<< "\n    Position: " << emp.get_position()
		<< "\n    Payrate: $" << emp.get_payrate()
		<< "\n    Location: " << emp.get_location()
		<< "\n";
	return os;
}

// Now we just operate on a vector of employees!
//void print_employees(const std::vector<Employee> &employees)
//{
//	for (const auto& employee: employees) 
//	{
//		std::cout << "Employee: " << employee.get_name()
//			<< "\n    Position: " << employee.get_position()
//			<< "\n    Payrate: $" << employee.get_payrate()
//			<< "\n    Location: " << employee.get_location()
//			<< std::endl;
//	}
//	std::cout << "-----------------------------\n";
//}

void print_employees(const std::vector<Employee> &employees)
{
	for (const auto& employee : employees) {
		std::cout << employee << std::endl;
	}
	std::cout << "-----------------------------\n";
}


void add_employee(const Employee& employee, std::vector<Employee> &employees)
{
	employees.push_back(employee);
}

// Find an employee by name and return their info in position, payrate,
// location. returns false if we couldn't find them
bool find_employee(const std::string &name, const std::vector<Employee>& employees,
	Employee &employee)
{
	for (const auto& _employee : employees) 
	{
		if (name == _employee.get_name()) 
		{
			employee = _employee;
			return true;
		}
	}
	return false;
}

void pass_by_value(Employee emp)
{
	std::cout << "pass_by_value: " << emp.get_name() << "\n";
}

void pass_by_ref(const Employee& emp)
{
	std::cout << "pass_by_ref: " << emp.get_name() << "\n";
}

int main()
{
	Employee e{ "Rick", "Chief Scientist", "Space", 500000 };
	// What does the following line print?
	//std::cout << e.name << std::endl;
	// A: Rick
	// B: crash
	// C: does not compile
	// D: random

	e = Employee(); // default c'tor
	// What does the following line print?
	std::cout << e.get_name() << std::endl;
	std::cout << std::endl;
	// A: Rick
	// B: crash
	// C: does not compile
	// D: empty string
	// E: random

	Employee e1{ "Bob", "Burger Chef", "Wonder Wharf", 45000 };
	e = e1; // Copy assignment
	e1.set_name("Tina");
	// What does the following line print?
	std::cout << e.get_name() << std::endl;
	// A: Rick
	// B: Bob
	// C: Tina
	// D: random
	std::cout << std::endl;

	Employee e2("Tina", "Teaching Assistant", "New York City", 50000);
	std::string& name = e2.get_name2();
	name = "Bob";
	// What does the following line print?
	std::cout << e2.get_name() << std::endl;
	// A: Gina
	// B: Bob
	// C: Tina
	std::cout << std::endl;

	Employee e3 = e2; //Copy c'tor
	pass_by_value(e3); //Copy c'tor
	pass_by_ref(e3);

	Employee e4(e3); //Copy c'tor

	// What will the following line do
	std::cout << Employee{"Morty", "Intern", "San Francisco", 40000} << std::endl;

	// A: Print Morty
	// B: Print { "Morty", "Intern", "San Francisco", 40000 }
	// C: crash
	// D: print random things
	// E: not compile
	
	// What function is called, assuming the above line compile?


	// It's now really clear what data goes with each employee
	std::vector<Employee> employees{
		Employee{ "Rick", "Chief Scientist", "Space", 500000 },
		Employee{ "Bob", "Burger Chef", "Wonder Wharf", 45000 },
		Employee{ "Tina", "Teaching Assistant", "New York City", 50000 },
		Employee{ "Morty", "Intern", "San Francisco", 40000 },
		Employee{ "James", "Manager", "London", 120000 }
	};
	
	print_employees(employees);
	
	// Hiring someone new is a hassle as well
	add_employee(Employee{ "Dave", "Programmer", "Los Angeles", 90000 }, employees);
	add_employee(Employee{ "Brad", "Actor", "Los Angeles", 900000 }, employees);
	add_employee(Employee{ "Ryan", "Vice President", "China", 1000000 }, employees);
	std::cout << "Employee list after hiring Dave:" << std::endl;
	print_employees(employees);

	// better way to create a vector of employees
	// avoids frequent resize, copy c'tor and d'tor calls
	{
		std::vector<Employee> employees;
		employees.reserve(100);
		employees.emplace_back("Rick", "Chief Scientist", "Space", 500000);
		employees.emplace_back("Bob", "Burger Chef", "Wonder Wharf", 45000);
		employees.emplace_back("Tina", "Teaching Assistant", "New York City", 50000);
		employees.emplace_back("Morty", "Intern", "San Francisco", 40000);
		employees.emplace_back("James", "Manager", "London", 120000);

		print_employees(employees);

		// Hiring someone new is a hassle as well
		add_employee(Employee{ "Dave", "Programmer", "Los Angeles", 90000 }, employees);
		add_employee(Employee{ "Brad", "Actor", "Los Angeles", 900000 }, employees);
		add_employee(Employee{ "Ryan", "Vice President", "China", 1000000 }, employees);
		std::cout << "\n";
	}

	// Find an employee
	Employee employee;
	if (!find_employee("Rick", employees, employee)) {
		std::cout << "Employee Rick not found\n";
	}
	else {
		std::cout << "Found Rick, employee info:"
			<< "\n    Position: " << employee.get_position()
			<< "\n    Payrate: $" << employee.get_payrate()
			<< "\n    Location: " << employee.get_location()
			<< std::endl;
	}

	if (!find_employee("Jim-bob", employees, employee)) {
		std::cout << "Employee Jim-bob not found" << std::endl;
	}
	else {
		std::cout << "Found Jim-bob, employee info:"
			<< "\n    Position: " << employee.get_position()
			<< "\n    Payrate: $" << employee.get_payrate()
			<< "\n    Location: " << employee.get_location()
			<< std::endl;
	}
	return 0;
}
