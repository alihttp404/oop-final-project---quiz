#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <conio.h>
using namespace std;
#include "header.h"
#include "menu.h"

int main()
{
	vector<string> options = 
	{
		"Option 1",
		"Option 2",
		"Option 3"
	};

	Menu<string> start(options);
	start.start();
}