// Question 1 - functions
// 
//	you are given the following missing implementation:
//	float applyF(float a, float b, ??????)
//	{
//		return f(a, b);
//	}
//	
//	1) list at least 3 different ways to replace the qustion marks (??????)
//		1. Pointer to any function is called with 2 float arguments. 
//		2. typedef for function... 
//		3. Lambda function std::function<float(float, float)> f. 
//	
//	2) replace the qustion marks in the following implementations with the solutions you listed
//
//	3) using one of those options create an add operation and a multiply operation and implement the following computation:
//		(2 * 3) + (4 * 5) + 6
//
//	you may not change the functions' implementation, only complete the signature

#include <iostream>
#include <functional>

float f(float a, float b);
float add(float a, float b);
float multiply(float a, float b);

float applyF1(float a, float b, float (*f)(float, float))
{
	return f(a, b);
}

typedef std::function<float(float, float)> F;
float applyF2(float a, float b, F f)
{
	return f(a, b);
}

float applyF3(float a, float b, std::function<float(float, float)> f)
{
	return f(a, b);
}

float add(float a, float b) {
	return a + b;
}

float multiply(float a, float b) {
	return a * b;
}

int main(int argc, char* argv[])
{
	float fNum = 0;
	// calculate fNum = (2 * 3) + (4 * 5) + 6

	//Using in pointer to function without using in operators
	fNum = applyF1(applyF1(applyF1(2.0f, 3.0f, multiply), applyF1(4.0f, 5.0f, multiply), add), 6.0f, add);
	std::cout << "(2 * 3) + (4 * 5) + 6 = " << fNum << "\n";

	return 0;
}
