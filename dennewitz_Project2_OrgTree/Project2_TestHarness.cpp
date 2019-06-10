/*
When using this test harness:
	1. Drag this .cpp file onto the Source Files folder in your project folder
	2. Comment out the main() function in your project.
	3. The test.txt file must be in the same location as your .vcxproject files
	(This folder contains all .h and .cpp files)

NOTE:
	This TestHarness assumes you have the following classes:
	1. OrgTree.h
	2. TreeNode.h

YOUR PROJECT MUST HAVE OrgTree.h

TreeNode.h may be implemented within OrgTree.h
*/

#include "stdafx.h"
#include "OrgTree.h"
//#include "TreeNode.h"
#include <iostream>
#include <string>
using namespace std;

bool testAddRoot(OrgTree testTree) {
	try {
		for (int i = 0; i < 1000; i++) {
			testTree.addRoot("t1", "n1");
		}
	}
	catch (exception e) {
		return false;
	}
	return true;
}

bool testHire(OrgTree &testTree) {
	try {
		testTree.hire(testTree.find("VP Sales"), "Director of Marketing", "George Lucas");
		testTree.hire(testTree.find("VP Sales"), "Director of Public Relations", "Kurt Vonnnegut");
	}
	catch (exception e) {
		return false;
	}
	return true;
}

void printTest(OrgTree t) {
	cout << "\tNode added within loop:" << endl;
	t.hire(t.getRoot(), "T2", "Bob");
	t.printSubTree(t.getRoot());
}

int main() {

	OrgTree testTree;
	int testNum = 1;

	cout << "Test " << testNum << ": addRoot ";
	if (!testAddRoot(testTree)) { cout << "failed.\n\n"; }
	else { cout << "passed.\n\n"; }
	testNum++;

	// Add two roots
	testTree.addRoot("VP Sales", "Mark Zuckerberg");
	testTree.addRoot("President", "George Orwell");
	
	cout << "Test " << testNum << ": getSize ";
	if (testTree.getSize() != 2) { 
		cout << "failed." << endl;
		cout << "\tExpected 2. Value was: " << testTree.getSize() << endl << endl;
	}
	else { cout << "passed.\n\n"; }
	testNum++;

	cout << "Test " << testNum << ": getRoot ";
	if (testTree.getRoot()== TREENULLPTR) { cout << "failed.\n\n"; }
	else { cout << "passed.\n\n"; }

	cout << "Test " << testNum << ": hire ";
	if (!testHire(testTree)) { cout << "failed.\n\n"; }
	else { cout << "passed.\n\n"; }
	testNum++;

	cout << "Test " << testNum << ": getSize ";
	if (testTree.getSize() != 4) {
		cout << "failed." << endl;
		cout << "\tExpected 4. Value was: " << testTree.getSize() << endl << endl;
	}
	else { cout << "passed.\n\n"; }
	testNum++;

	int count = 0;
	while (count < 3) {
		cout << "Test " << testNum << ": fire ";
		try {
			if (count == 0) {				
				if (testTree.fire("VP Sales")) { cout << "passed.\n\n";	}
			}
			else if (count == 1) {
				if (!testTree.fire("President")) { cout << "passed.\n\n"; }
			}
			else if (count == 2){ 
				if (!testTree.fire("Taco Salesman")) { cout << "passed.\n\n"; }
			}
			else {
				cout << "failed.\n\n";
			}
		}
		catch (exception e) {
			cout << "failed.\n\n";
		}
		testNum++;
		count++;
	}

	cout << "Test " << testNum << ": getSize ";
	if (testTree.getSize() != 3) {
		cout << "failed." << endl;
		cout << "\tExpected 3. Value was: " << testTree.getSize() << endl << endl;
	}
	else { cout << "passed.\n\n"; }
	testNum++;

	cout << "Test " << testNum << ": read file ";
	//if (!testTree.read("test.txt")) { cout << "failed.\n\n"; }
	//else { cout << "passed.\n\n"; }
	testNum++;
	
	cout << "Test " << testNum << ": getSize ";
	if (testTree.getSize() != 12) {
		cout << "failed." << endl;
		cout << "\tExpected 12. Value was: " << testTree.getSize() << endl << endl;
	}
	else { cout << "passed.\n\n"; }
	testNum++;

	count = 0;
	while (count < 3) {
		cout << "Test " << testNum << ": find ";
		try {
			if (count == 0) {
				if (testTree.find("President")) { cout << "passed.\n\n"; }
			}
			else if (count == 1) {
				if (testTree.find("MagicBag Team Leader")) { cout << "passed.\n\n"; }
			}
			else if (count == 2) {
				if (!testTree.find("Taco Salesman")) { cout << "passed.\n\n"; }
			}
			else {
				cout << "failed.\n\n";
			}
		}
		catch (exception e) {
			cout << "failed.\n\n";
		}
		testNum++;
		count++;
	}

	cout << "Test " << testNum << ": print test ";
	printTest(testTree);
	cout << "\tprintSubTree should not contain the added node." << endl;
	testTree.printSubTree(testTree.getRoot());
	cout << endl;

	system("pause");
	return 0;
}