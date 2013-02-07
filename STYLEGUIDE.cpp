#include <iostream>
#include <string>

using namespace std;

class TestClass {
  // this is private
  int value;

  // note the line between private variables and the next section, "public"
public:
  TestClass();
  TestClass(int);
  ~TestClass();
  int accessor();
  void modifier(int value);

  // and the line here between public methods and variables
  string this_is_public = "Private vars are not necessary for our code; try not to use them.";
};

// note the space before the bracket and before the comment after "//"
TestClass::TestClass() {
  // constructor
  // note that class functions are defined
  // outside of the main class definition
  this.value = 10;
}

TestClass::TestClass(int a) {
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
