/* This is a multi-line
   comment.
   */
// This is a single line comment.
/* This is also a single line comment. */

#include <iostream>
#include <string>

using namespace std;

/* Tabs starting a line should be a <Tab> character, not any other amount of spaces.
   If you have a preference on tab widths, change your editor settings
   (or get a better editor if you can't change your editor settings).
   For adding whitespace in the middle of a line, spaces are ok.
   */
/* Also, please remove trailing whitespace before committing. */
/* Finally, DON'T USE DOS LINE ENDINGS! */

class TestClass {
	private:
		int x; // this is a private variable
		int y;
		int value;

	public: // blank line between public and private sections
		TestClass();
		TestClass(int);
		~TestClass();
		int accessor();
		void modifier(int value);

		// and the blank line here between public methods and variables
		string this_is_public = "Use private vars but note that they can only be accessed by class methods.";
};

TestClass::TestClass() : // space before ":" to start initializer list
	x(1), // comma at end of each entry
	y(2)
{ // opening bracket gets a newline after multiline initializer lists
	/* Constructor:
	   Note that class functions are defined
	   outside of the main class definition.
	*/
	this.value = 10;
}

// this is an overloaded constructor that takes an int as an argument
TestClass::TestClass(int a) { // Space before opening bracket
	// a non-default constructor will initialize
	// the variables of the class to the ones
	// provided as arguments
	this.value = a;
}

TestClass::~TestClass() {
	delete this.private_vars;
	delete this.value;
}

int TestClass::accessor() {
	return this.value;
}

void TestClass::modifier(int a) {
	this.value = a;
}

// Class functions are defined before generic functions

// This is what a line comment looks like.
// Do not use /* and put text between that and */
/* Block comments are on several lines
   and are aligned like so */

int main(int argc, char *argv[]) {
	// note the spaces before and after all operators
	cout << "We might want to print things for like debugging purpose" << endl;
	cout << "We will use stream operators" << endl;

	// note the space between "while" and "(true)" and the space before the bracket
	while (true) {
		break;
	}

	// same as with "while"
	if (true == true) {
		cout << "One line if statements should have brackets" << endl;
	}

	TestClass test_class;
	cout << test_class.accessor(); << endl;

	delete test_class;
	return 0;
}
