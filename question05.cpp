// Question 5
//
//	we want to implement a logic class named MyBool to use in our logic
//	we would like to be able to use the logical and (&&) with instances of this class 
//  i.e. to be able to write in the form of myBool1 && myBool2
//	we have also implemented some function using this class
//	"notNull" checks if a pointer is null and return a corresponding MyBool
//  "greaterThanZero" checks if an int pointer points to a positive int and return a corresponding MyBool
//
//	1. Implement this addition in the MyBool class
//  2. Did it compile successfully?
//	3. Did it run successfully?
//	4. Explain the result, explain what happened and why
//
// useful links:
// https://en.cppreference.com/w/cpp/language/operators
// https://cplusplus.com/doc/tutorial/operators/
// https://isocpp.org/wiki/faq/operator-overloading

#include <iostream>

class MyBool
{
public:
	MyBool(bool b) : m_val(b) {};

	//TODO: Your code here
	//  1. 
	bool operator&&(const MyBool& other) const { return m_val && other.m_val; }

private:
	bool m_val;
};

MyBool notNull(int* intPtr)
{
	return intPtr != nullptr;
}

MyBool greaterThanZero(int* intPtr)
{
	return *intPtr > 0;
}

int main(int argc, char* argv[])
{
	int* a = nullptr;
	int val = 5;
	int* b = &val;


	// the long way to check
	if (a != nullptr && *a > 0)
	{
		++* a;
		std::cout << "*a is " << *a << std::endl;
	}

	// using our functions
	if (notNull(b) && greaterThanZero(b))
	{
		++* b;
		std::cout << "*b is " << *b << std::endl;
	}

	// using our functions again
	if (notNull(a) && greaterThanZero(a))
	{
		++* a;
		std::cout << "*a is " << *a << std::endl;
	}

	return 0;
}

//  2. Yes, it compiled successfully. 
//	3. It ran and printed a correct result for b - pointer to val = 5, but a runtime error was thrown when 
// used code for a - is pointer to nullptr and the greaterThanZero function attempted to access its contents (*intPtr > 0). 
//	4. A runtime error was thrown:
//Exception thrown : read access violation.
//intPtr was nullptr.
//In a normal IF question, when 2 conditions appear and &&between them - the code is read from left to right,
//First the part is called - the left condition, and if it returns true - the right side will be called.
//In the existing code, there is a check whether a pointer contains an address, and whether its content is a pointer greater than 0, if so - a promotion operation is performed for the content of the pointer.
//If the pointer contains nullptr - you will throw an error because its contents cannot be accessed.[because it contains nullptr and not an address].
//In the usual and lengthy way, the test is indeed carried out - first the left part of the preliminary condition is called, which asks if the pointer is not equal to nullptr, and only if this condition returns true -
//The second part will be called where we will access the content and make sure it is greater than 0.
//Therefore this code is correct and does not throw an error,
// However, the code we implemented using the operator&& function in the MyBool class,
// Returns true or false on both conditions as one unit - that is, executes both parts of the codeand returns true if both conditions returned true, and false if both returned false, but executes both in any case
// Even in the case that the first condition returns false - unlike when using the normal&& operator and not like in the function we loaded.
// As a result : no check is made to see if the pointer contains an address before accessing the address it points to, so this error is thrown.
