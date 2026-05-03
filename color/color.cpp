#include "color.h"

using namespace std;

void TestColor_window() {
	cout << Color::Normal << "start test output with color" << endl;
    
	cout << Color::Red << "this is Red" << endl;
	cout << Color::HighLight << "this is highlight" << endl;
	cout << Color::Normal << Color::Red << "this is Red" << endl;
	cout << Color::Green << "this is Green" << endl;
	cout << Color::Blue << "this is Blue" << endl;
	cout << Color::Magenta << "this is Magenta" << endl;
	cout << Color::White << "this is White" << endl;

	cout << Color::Normal << "end test output with color" << endl;
}
