/*
Ethan Dennewitz
CS 3100-02
Project 2 Managing a Hierarchy using a General Tree

For creating my general tree implementation I decided to go with a leftchild/rightsibling linked list build. Each node 
in the list has three pointers to determine there location in the tree based on their parent, left child, and right sibling.
Notable this about this project: TreeNode.h doesnt exist and is implemented within OrgTree.h, also I didn't quite implement 
my read method properly. In read I am having a issue of the root pointing to a nullptr when it tries to hire the first person 
in the file. The read test is currentlty commented out in order for the program to not crash.
*/

#pragma once

#define TREENODEPTR TreeNode*
#define TREENULLPTR NULL
#include <string>
#include <fstream>
#include <iostream>

using namespace std;


/*The TreeNode is a node structure that is used to store the information about the employee and also maintains three 
pointers to determine where in the general tree the employee should be placed.
*/
class TreeNode {
public:
	string title;
	string name;
	TreeNode * parent;
	TreeNode * leftChild;
	TreeNode * rightSibling;
	
	//constructor
	TreeNode(string Title, string Name) {
		title = Title;
		name = Name;
		parent = TREENULLPTR;
		leftChild = TREENULLPTR;
		rightSibling = TREENULLPTR;
	}

};


/*The OrgTree class that I created for this general uses a left child/right sibling linked list structure. 
*/
class OrgTree
{
public:

	TreeNode * head;
	int size;
	/*Constructor method for creating an empty OrgTree
	*/
	OrgTree() {
		head = TREENULLPTR;
		size = 0;
	}
	/*The addRoot method is used to create a root node for the tree.If there is no current head node the added root becomes the 
	head node. If there already is a head node the current head becomes the left child of the new root.
	Time Complexity: Θ(n)
	*/
	void addRoot(string title, string name) {
		if (!head) {
			head = new TreeNode(title, name);
		}
		else {
			head->parent = new TreeNode(title, name);
			head->parent->leftChild = head;
			head = head->parent;
		}
		size++;
	}
	/*The getSize method simply returns the current size of the tree.
	Time Complexity: Θ(1)
	*/
	unsigned int getSize() {
		return size;
	}
	/*The getRoot method is used to return whatever is the current root node or head node.
	Time Complexity: Θ(n)
	*/
	TREENODEPTR getRoot() {
		if (!head) {
			return TREENULLPTR;
		}
		return head;

	}

	/*The leftMostChild method is used to return the left most child of whatever node the method is called on.
	Time Complexity: Θ(1)
	*/
	TREENODEPTR leftMostChild(TREENODEPTR node) {
		if (!node || !node->leftChild) {
			return TREENULLPTR;
		}
		else {
			return node->leftChild;
		}
	}
	/*The rightSibling method is used to return the right sibling of whatever node the method is called on.
	Time Complexity: Θ(1)
	*/
	TREENODEPTR rightSibling(TREENODEPTR node) {
		if (!node || !node->rightSibling) {
			return TREENULLPTR;
		}
		else {
			return node->rightSibling;
		}
	}
	/*The printSubTree method calls my recurisve printing helper method in order to print the current contents of the given tree pointer.
	Time Complexity: Θ(n)
	*/
	void printSubTree(TREENODEPTR subTreeRoot) {
		if (subTreeRoot) {
			cout << subTreeRoot->title << ": " << subTreeRoot->name << endl;
			int count = 1;
			recursivePrint(subTreeRoot->leftChild, count);
		}
	}
	/*This recursivePrint method is used to recusively traverse the tree in order to print out all of the nodes in the given tree.
	*/
	void recursivePrint(TREENODEPTR root, int count) {
		if (!root) {
			return;
		}
		else {
			for (int i = 0; i < count; i++) {
				cout << "\t";
			}

			cout << root->title << ": " << root->name << endl;
			count++;
			recursivePrint(root->leftChild, count);
			count--;
			recursivePrint(root->rightSibling, count);
		}
	}
	/*The find method first checks of the title of the employee is the current head node if not it call my recursive helper method to traverse the tree and 
	find the node based on the title that is provided.
	Time Complexity: Θ(n)
	*/
	TREENODEPTR find(string title) {
		if (head->title == title) {
			return head;
		}

		return	recursiveFind(head, title);
	}
	/*The recursive method is very similar to my recursivePrint helper method but instead of print the contents of node as it is traversing the tree it
	returns the node that contains the title that is being searched for.
	*/
	TREENODEPTR recursiveFind(TREENODEPTR currentNode, string titleToFind) {
		if (!currentNode) {
			return TREENULLPTR; 
		}
		if (currentNode->title == titleToFind) {
			return currentNode;
		}
		else {
			TREENODEPTR temp = recursiveFind(currentNode->leftChild, titleToFind);
			if (temp) {
				return temp;
			}
			return recursiveFind(currentNode->rightSibling, titleToFind);
		}

	}

	/*The read method is used to open up a file that is provided, reads the contents and converts the information into 
	an OrgTree. Currently the method isn't working as intended it opens the file and reads but it is assigning the root 
	to a nullptr causing an error with the hire method.
	Time Complexity: Θ(n)
	*/
	bool read(string filename) {
		string title;
		string name;
		string extra;

		ifstream file(filename);
		file.open(filename);

		if (!file.is_open()) {
			return false;
		}

		OrgTree orgTree;
		TREENODEPTR treeNode;

		getline(file, title, ',');
		getline(file, name);
		orgTree.addRoot(title, name);
		treeNode = find(title);

		while (!file.eof()) {
			if (file.peek() == ')') {
				getline(file, extra);
				treeNode = treeNode->parent;
			}
			else {
				getline(file, title, ',');
				getline(file, name);
				orgTree.hire(treeNode, title, name);
				treeNode = find(title);
			}

		}

		return true;

	}
	/*The write method is used to take the current contents of the OrgTree and write them into a .txt file. This method
	utilises a recursive helper method inorder to traverse the tree and write the contents.
	Time Complexity: Θ(n)
	*/
	void write(string filename) {
		ofstream file;
		file.open(filename);
		file << head->title << ", " << head->name << endl;
		recursiveWriting(file, head->leftChild);
		file << ")";
		file.close();
	}
	/*The recursiveWriting method is used to recursively traverse the OrgTree and write the contents of the current tree into
	a .txt file that is being created within the write method.
	*/
	void recursiveWriting(ofstream &file, TREENODEPTR head) {
		if (!head) {
			return;
		}
		else {
			file << head->title << ", " << head->name << endl;
			recursiveWriting(file, head->leftChild);
			file << ")" << endl;
			recursiveWriting(file, head->rightSibling);
		}
	}

	/*The hire method is used to add nodes to the OrgTree it does this add the node as the left child of the node that is being
	pointed to within the method call.
	Time Complexity: Θ(n)
	*/
	void hire(TREENODEPTR root, string newTitle, string newName) {
		TreeNode * currentNode = root->leftChild;
		if (!currentNode) {
			currentNode = new TreeNode(newTitle, newName);
			currentNode->parent = root;
			root->leftChild = currentNode;
		}
		else {
			TreeNode * currentRightSibling = currentNode->rightSibling;
			while (currentRightSibling) {
				currentNode = currentRightSibling;
				currentRightSibling = currentRightSibling->rightSibling;
			}
			currentRightSibling = new TreeNode(newTitle, newName);
			currentNode->rightSibling = currentRightSibling;
			currentRightSibling->parent = root;
		}
		size++;
	}
	/*The fire method is used to delete the "employee" from the tree and then assign any children that were associated with that 
	employee to parent of the fired employee. 
	Time Complexity: Θ(n)
	*/
	bool fire(string formerTitle) {
		if (head->title == formerTitle) {
			return false;
		}

		TREENODEPTR firedEmployee = find(formerTitle);
		if (!firedEmployee) {
			return false;
		}
		if (firedEmployee) {
			size--;
			return true;
		}
		delete firedEmployee;
		size--;
		return true;

	}

};


