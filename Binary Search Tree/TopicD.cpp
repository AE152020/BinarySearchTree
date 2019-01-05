#include "General.h"
#include "Soundtrack.h"
#include "BinaryNodeTree.h"
#include "BinarySearchTree.h"

// Two additional traversal helper methods like generalOrderTraverse() and linearOrderTraverse(), in order to check the correctness of the binary search tree structure.

// The "Binary seach tree" idea: 

// + Example (1) : 
//                                                    [1]                                                                    // Height : 2
//                                   [2]                               [3]                                                 // Height : 1

// + Example (2) : 
//                                                           [1]                                                           // Height : 3
//                                   [2]                                               [3]                                // Height : 2
//                [4]                              [6]               [5]                             [7]                // Height : 1

// + Example (3) : 
//                                                    [1]                                                                   // Height : 4
//                                            [2]            [3]                                                           // Height : 3
//          [4]                     [6]                                [5]                         [7]                   // Height : 2
//  [8]           [10]     [12]           [14]             [9]           [11]      [13]               [15]      // Height : 1

// + Example (4) : 
//                                                                 [1]                                                                         // Height : 5 (1)
//                                                         [2]            [3]                                                                 // Height : 4 (2)
//                    [4]                         [6]                                [5]                            [7]                     // Height : 3 (3)
//            [8]           [10]        [12]           [14]             [9]             [11]         [13]               [15]        // Height : 2 (4)
//        [16][18]    [20][22]   [24][26]     [28][30]        [17][19]       [21][23]    [25][27]        [29][31]     // Height : 1 (5)

// The values are inserted from left to right, in a perfectly balanced mode.
// + If the left side gets a value, the right side gets a value in the next turn, so that in order to ensure that the number of nodes for the left side and the number of nodes for the left side are equal.
// + If there is no slot remaining, the program attempts to create a new height level.

// generalOrderTraverse() and linearOrderTraverse() are helper methods to check the correctness of the "Binary search tree" structure.
// + Here is an example of generalOrderTraverse() for example (3) : 
//   1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
// generalOrderTraverse() represents exactly the order inserted into the "Binary search tree"

// + Here is an example of linearOrderTraverse() for example (3) : 
//   1 2 3 4 6 5 7 8 10 12 14 9 11 13 15
// As you can see, linearOrderTraverse() represents exactly the structure of "Binary search tree"

// For example, given 38 entries :  
//		-20, 0, -10, 10, 15, 2, 1, 
//		1989, 1993, 1991, 1990, 1985, 1997, 1999, 2002, 1998, 2003, 2003, 
//		2003, 1995, 2004, 2004, 2004, 2006, 2009, 2007, 2005, 2005, 2004, 
//		2010, 2010, 2010, 2004, 2011, 2014, 2013, 2012, 2011

// The height of this "Binary search tree" is only 6.
// 1 + 2 + 4 + 8 + 16 + (32) (Level 6)

// While the height of the original "Binary search tree" is 8. 

template<class T>
void outputPost(T &t);

template<class T>
void outputPost2(T &t);

void test();

int main()
{
	int i;
	test();

	int data_postOrder1[] =
	{
		-20, 0, -10, 10, 15, 2, 1,
		1989, 1993, 1991, 1990, 1985, 1997, 1999, 2002, 1998, 2003, 2003,
		2003, 1995, 2004, 2004, 2004, 2006, 2009, 2007, 2005, 2005, 2004,
		2010, 2010, 2010, 2004, 2011, 2014, 2013, 2012, 2011
	};
	vector<int> postOrder1(data_postOrder1, data_postOrder1 + sizeof(data_postOrder1) / sizeof(int));

	BinarySearchTree<int> bst2;

	for (i = 0; i < (int)postOrder1.size(); i++)
	{
		bst2.add(postOrder1[i]);
	}

	cout << "bst2 General order : \n";
	bst2.generalOrderTraverse(&outputPost<int>);

	cout << "Height of bst2 is " << bst2.getHeight() << endl << endl;

	cout << "Number of nodes in bst2 is " << bst2.getNumberOfNodes() << endl << endl;

	cout << "Delete 2014 from bst2" << endl << endl;

	if (bst2.remove(2014))
	{
		cout << "2014 deleted from bst2" << endl << endl;
	}
	else
	{
		cout << "2014 NOT deleted from bst2" << endl << endl;
	}

	cout << "Delete 2014 from bst2" << endl << endl;

	if (bst2.remove(2014))
	{
		cout << "2014 deleted from bst2" << endl << endl;
	}
	else
	{
		cout << "2014 NOT deleted from bst2" << endl << endl;
	}

	cout << "Display bst2 : \n";
	cout << "Pre order : \n";
	bst2.preorderTraverse(&outputPost<int>);

	cout << endl;
	cout << "General order : \n";
	bst2.generalOrderTraverse(&outputPost<int>);

	cout << endl;
	cout << "Post order : \n";
	bst2.postorderTraverse(&outputPost<int>);

	cout << endl;
	cout << "In order : \n";
	bst2.inorderTraverse(&outputPost<int>);

	cout << endl;

	cout << "Height of bst2 is " << bst2.getHeight() << endl << endl;

	cout << "Number of nodes in bst2 is " << bst2.getNumberOfNodes() << endl << endl;

	cout << "Create bst3 then assign bst2 to bst3" << endl << endl;

	BinarySearchTree<int> bst3;
	bst3 = bst2;

	cout << "Display bst3" << endl << endl;

	cout << "Pre order : \n";
	bst3.preorderTraverse(&outputPost<int>);

	cout << endl;
	cout << "General order : \n";
	bst3.generalOrderTraverse(&outputPost<int>);

	cout << endl;
	cout << "Post order : \n";
	bst3.postorderTraverse(&outputPost<int>);

	cout << endl;
	cout << "In order : \n";
	bst3.inorderTraverse(&outputPost<int>);

	cout << endl;

	cout << "Height of bst3 is " << bst3.getHeight() << endl << endl;

	cout << "Number of nodes in bst3 is " << bst3.getNumberOfNodes() << endl << endl;

	std::ifstream inFile("TopicD_Soundtrack.txt");

	if (!inFile.is_open())
	{
		std::cerr << "Cannot locate the file 'TopicD_Soundtrack.txt' Program cannot continue..." << std::endl;
		return 0;

	} // End if-statement

	std::vector<soundtrack> soundtrack_data;

	while (inFile)
	{
		// Appends an empty soundtrack element
		soundtrack_data.push_back(soundtrack());

		// Attempt to load data from the file. If the operation fails, remove the element
		if (!(inFile >> soundtrack_data.back())) soundtrack_data.pop_back();

	} // End while-statement
	inFile.close();
	BinarySearchTree<soundtrack> bstST1;

	for (i = 0; i < (int)soundtrack_data.size(); i++)
	{
		bstST1.add(soundtrack_data[i]);
	}

	cout << "Display bstST1" << endl << endl;

	cout << "General order : \n";
	bstST1.generalOrderTraverse(&outputPost<soundtrack>);

	cout << "Height of bstST1 is " << bstST1.getHeight() << endl << endl;

	cout << "Number of nodes in bstST1 is " << bstST1.getNumberOfNodes() << endl << endl;

	cout << "Create bstST2 from bstST1" << endl << endl;

	BinarySearchTree<soundtrack> bstST2(bstST1);

	cout << "Display bstST2" << endl << endl;

	cout << "General order : \n";
	bstST2.generalOrderTraverse(&outputPost<soundtrack>);

	cout << "Height of bstST2 is " << bstST2.getHeight() << endl << endl;

	cout << "Number of nodes in bstST2 is " << bstST2.getNumberOfNodes() << endl << endl;

	cout << "***************************************************************" << endl << endl;

	return 0;
}

template<class T>
void outputPost(T &t)
{
	cout << t << endl;
}


template<class T>
void outputPost2(T &t)
{
	cout << t << " ";
}

void test()
{
	int i;
	int data_test[] =
	{
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
		//		, 
		//		16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
	};

	vector<int> postData(data_test, data_test + sizeof(data_test) / sizeof(int));

	BinarySearchTree<int> bst1;

	for (i = 0; i < postData.size(); i++)
	{
		bst1.add(postData[i]);
	}

	cout << "Display bst1 (General order) : " << endl;
	bst1.generalOrderTraverse(&outputPost2<int>);

	cout << endl << endl;

	cout << "Display bst1 (Linear order) : " << endl;
	bst1.linearOrderTraverse(&outputPost2<int>);

	cout << endl << endl;

	cout << "Display bst1 (Pre order) : " << endl;
	bst1.preorderTraverse(&outputPost2<int>);

	cout << endl << endl;

	cout << "Display bst1 (Post order) : " << endl;
	bst1.postorderTraverse(&outputPost2<int>);

	cout << endl << endl;

	cout << "Display bst1 (In order) : " << endl;
	bst1.inorderTraverse(&outputPost2<int>);

	cout << endl << endl;

}
