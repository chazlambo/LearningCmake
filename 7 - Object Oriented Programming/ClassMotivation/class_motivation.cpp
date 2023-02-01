#include <iostream>
#include <vector>
#include <string>

// ----------------------------------------
//  Classes - Motiviation
// ----------------------------------------
// Why would we want to use classes to organize our code?
// Suppose we have some kind of employee management system where
// we store information (names, position, payrates, locations) 
// about our employees in vectors

// All our employee data is split up in these different arrays,
// any function to operate on them must take all of them
void print_employees(const std::vector<std::string>& names,
	const std::vector<std::string>& positions,
	const std::vector<int>& payrates,
	const std::vector<std::string>& locations)
{
	// What if somehow the arrays got out of sync and were different
	// lengths or the employee data got shuffled around some?
	for (size_t i = 0; i < names.size(); ++i)
	{
		std::cout << "Employee: " << names[i]
			<< "\n    Position: " << positions[i]
			<< "\n    Payrate: $" << payrates[i]
			<< "\n    Location: " << locations[i]
			<< "\n";
	}
	std::cout << "-----------------------------\n";
}

void add_employee(const std::string& name, const std::string& position,
	const int payrate, const std::string& location,
	std::vector<std::string>& names,
	std::vector<std::string>& positions,
	std::vector<int>& payrates,
	std::vector<std::string>& locations)
{
	names.push_back(name);
	positions.push_back(position);
	payrates.push_back(payrate);
	locations.push_back(location);
}

// Find an employee by name and return their info in position, payrate,
// location. returns false if we couldn't find them
bool find_employee(const std::string& name, std::string& position,
	int& payrate, std::string& location,
	std::vector<std::string>& names,
	std::vector<std::string>& positions,
	std::vector<int>& payrates,
	std::vector<std::string>& locations)
{
	for (size_t i = 0; i < names.size(); ++i)
	{
		if (name == names[i])
		{
			position = positions[i];
			payrate = payrates[i];
			location = locations[i];
			return true;
		}
	}
	return false;
}

int main() {
	// Names of our employees
	std::vector<std::string> employee_names{ "Rick", "Bob", "Tina", "Morty", "James" };
	// Position of each employee
	std::vector<std::string> employee_positions{ "Chief Scientist",
												 "Burger Chef", "Teaching Assistant",
												 "Intern","Manager" };
	// How much each employee makes anually
	std::vector<int> employee_payrates{ 500000, 45000, 50000, 40000, 120000 };
	// Which office each employee works in
	std::vector<std::string> employee_locations{ "Space", "Wonder Wharf",
												 "New York City", "San Francisco",
												 "London" };

	// Dealing with our employee data is kind of a pain!
	std::cout << "Initial employee list:\n";
	print_employees(employee_names, employee_positions, employee_payrates, employee_locations);

	// Hiring someone new is a hassle as well
	add_employee("Dave", "Programmer", 90000, "Los Angeles",
		employee_names, employee_positions, employee_payrates,
		employee_locations
	);
	std::cout << "Employee list after hiring Dave:\n";
	print_employees(employee_names, employee_positions, employee_payrates, employee_locations);

	// Finding someone is annoying too!
	std::string position;
	std::string location;
	int payrate = 0;
	if (!find_employee("Rick", position, payrate, location, employee_names,
		employee_positions, employee_payrates, employee_locations))
	{
		std::cout << "Employee Rick not found\n";
	}
	else {
		std::cout << "Found Rick, employee info:"
			<< "\n    Position: " << position
			<< "\n    Payrate: $" << payrate
			<< "\n    Location: " << location
			<< "\n";
	}

	if (!find_employee("Jim-bob", position, payrate, location, employee_names,
		employee_positions, employee_payrates, employee_locations))
	{
		std::cout << "Employee Jim-bob not found\n";
	}
	else {
		std::cout << "Found Jim-bob, employee info:"
			<< "\n    Position: " << position
			<< "\n    Payrate: $" << payrate
			<< "\n    Location: " << location
			<< "\n";
	}

	// This system is horrible! What if we mixed up the names, positions
	// or locations vectors? They're all just std::vector<std::string> so
	// we could easily mix up the order and have a bug. Not to mention
	// potential issues with the vector lengths getting out of sync or the
	// order of things being mixed up and people getting the wrong position
	// or payrate and so on. Also, it's a huge pain to type all this!

	// Instead, we can use classes to make life better for us

	return 0;
}
