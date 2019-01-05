#ifndef BINARY_NODE_TREE_
#define BINARY_NODE_TREE_

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "PrecondViolatedExcept.h"
#include "NotFoundException.h"

using namespace std;

template<class ItemType>
class BinaryNodeTree : public BinaryTreeInterface<ItemType>
{
private:
	NodeUnit rootPtr;

protected:
	//------------------------------------------------------------
	// Protected Utility Methods Section:
	// Recursive helper methods for the public methods.
	//------------------------------------------------------------
	static int getHeightHelper(NodeUnit subTreePtr);
	static int getNumberOfNodesHelper(NodeUnit subTreePtr);

	// Recursively adds a new node to the tree in a left/right fashion to keep tree balanced.
	static NodeUnit balancedAdd(NodeUnit subTreePtr, NodeUnit newNodePtr);

	// Removes the target value from the tree.
	virtual NodeUnit removeValue(NodeUnit &subTreePtr, const ItemType target, bool& isSuccessful);

	// Recursively searches for target value.
	virtual NodeUnit findNode(NodeUnit treePtr, const ItemType& target, bool& isSuccessful) const;

	// Copies the tree rooted at treePtr and returns a pointer to the root of the copy.
	NodeUnit copyTree(const NodeUnit oldTreeRootPtr);

	// Recursively deletes all nodes from the tree.
	static void destroyTree(NodeUnit &subTreePtr);
	static void getNodeCollection(const NodeUnit root_ptr, vector<ItemType> &collection);

	NodeUnit getRoot() const { return rootPtr; }

	static bool accessUncompletedNode(NodeUnit root_ptr, NodeUnit &result_ptr, int height, int current_height, ItemType newItem);
	static bool accessBalancedUncompletedNode(NodeUnit root_ptr, int height, int current_height, NodeUnit& result_ptr);
	static bool accessBalancedUncompletedNodeHelper(NodeUnit root_ptr, int height, int target_height, int current_height, NodeUnit& result_ptr);
	static bool accessLeftBalancedNode(NodeUnit root_ptr, int height, int current_height, NodeUnit& result_ptr);

	static int countNumNode(NodeUnit root_ptr);
	static int determineNodeCount(int height);

	static NodeUnit copyTreeHelper(NodeUnit &root_ptr, const NodeUnit oldTreeRootPtr);

	// Recursive traversal helper methods:
	static void preorder(void visit(ItemType&), NodeUnit treePtr);
	static void inorder(void visit(ItemType&), NodeUnit treePtr);
	static void postorder(void visit(ItemType&), NodeUnit treePtr);
	static void generalOrder(void visit(ItemType&), NodeUnit treePtr, int height, int current_height);
	static void linearOrder(void visit(ItemType&), NodeUnit treePtr, int height, int current_height);

	static void collectNodeHeight(NodeUnit treePtr, vector<ItemType> &collection, int height, int target_height, int current_height);

public:
	//------------------------------------------------------------
	// Constructor and Destructor Section.
	//------------------------------------------------------------
	BinaryNodeTree();
	BinaryNodeTree(const ItemType& rootItem);
	BinaryNodeTree(const ItemType& rootItem, const NodeUnit leftTreePtr, const NodeUnit rightTreePtr);
	BinaryNodeTree(const NodeUnit& tree);
	virtual ~BinaryNodeTree();

	//------------------------------------------------------------
	// Public BinaryTreeInterface Methods Section.
	//------------------------------------------------------------
	bool isEmpty() const;
	int getHeight() const;
	int getNumberOfNodes() const;

	ItemType getRootData() const throw(PrecondViolatedExcept);
	void setRootData(const ItemType& newData) throw(PrecondViolatedExcept);

	bool add(const ItemType& newData); // Adds an item to the tree
	bool remove(const ItemType& data); // Removes specified item from the tree
	void clear();

	ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException);
	bool contains(const ItemType& anEntry) const;

	//------------------------------------------------------------
	// Public Traversals Section.
	//------------------------------------------------------------
	void preorderTraverse(void visit(ItemType&)) const;
	void inorderTraverse(void visit(ItemType&)) const;
	void postorderTraverse(void visit(ItemType&)) const;
	void generalOrderTraverse(void visit(ItemType&)) const; // The original order of the data
	void linearOrderTraverse(void visit(ItemType&)) const;    // Another way of displaying data

															  //------------------------------------------------------------
															  // Overloaded Operator Section.
															  //------------------------------------------------------------
	BinaryNodeTree& operator=(const BinaryNodeTree& rightHandSide);

}; // end BinaryNodeTree

   // -------------------Definitons----------------------------
template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree() {}

template<class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree() {}

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem)
{
	add(rootItem);
}

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem, const NodeUnit leftTreePtr, const NodeUnit rightTreePtr)
{
	add(rootItem);
	copyTree(rootPtr->getLeftChildPtrReference());
	copyTree(rootPtr->getRightChildPtrReference());
}

template<class ItemType>
BinaryNodeTree<ItemType>& BinaryNodeTree<ItemType>::operator = (const BinaryNodeTree<ItemType>& rightHandSide)
{
	if (&rightHandSide != this)
	{
		copyTree(rootPtr, rightHandSide.getRoot());
	}

	return (*this);
}

template<class ItemType>
void BinaryNodeTree<ItemType>::collectNodeHeight(NodeUnit treePtr, vector<ItemType> &collection, int height, int target_height, int current_height)
{
	if (treePtr.get() == nullptr)
	{return;}

	NodeUnit leftPtr = treePtr->getLeftChildPtr();
	NodeUnit rightPtr = treePtr->getRightChildPtr();

	if (target_height == current_height)
	{
		if (leftPtr.get() != nullptr)
		{
			collection.push_back(leftPtr->getItem());
		}

		if (rightPtr.get() != nullptr)
		{
			collection.push_back(rightPtr->getItem());
		}
		return;
	}
	else
	{
		collectNodeHeight(leftPtr, collection, height, target_height, current_height + 1);
		collectNodeHeight(rightPtr, collection, height, target_height, current_height + 1);
	}
}


// Recursively searches for target value.
template<class ItemType>
NodeUnit BinaryNodeTree<ItemType>::findNode(NodeUnit treePtr, const ItemType& target, bool& isSuccessful) const
{
	isSuccessful = false;
	if (treePtr.get() == nullptr)
	{
		return treePtr;
	}

	if (treePtr->getItem() == target)
	{
		isSuccessful = true;
		return treePtr;
	}

	NodeUnit leftPtr = treePtr->getLeftChildPtr();
	NodeUnit rightPtr = treePtr->getRightChildPtr();

	if (findNode(leftPtr, target, isSuccessful).get() != nullptr) return leftPtr;
	return findNode(rightPtr, target, isSuccessful);
}

template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getEntry(const ItemType& anEntry) const throw(NotFoundException)
{
	bool isSuccessful;
	findNode(rootPtr, anEntry, isSuccessful);

	if (isSuccessful) return anEntry;
	throw NotFoundException("BinaryNodeTree::getEntry : Entry not found");
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::contains(const ItemType& anEntry) const
{
	bool isSuccessful;
	findNode(rootPtr, anEntry, isSuccessful);

	if (isSuccessful) 
		return true; 
	else 
		return false;
}

template<class ItemType>
void BinaryNodeTree<ItemType>::linearOrder(void visit(ItemType&), NodeUnit treePtr, int height, int current_height)
{
	int i;
	if (treePtr.get() == nullptr)
	{
		cout << "BinaryNodeTree::linearOrder()\n+ Fatal error : The treePtr argument cannot be null\n";
		system("pause");
		terminate();
	}

	vector<ItemType> itemCollection;

	for (i = 2; i <= height; i++)
		collectNodeHeight(treePtr, itemCollection, height, i, 2);

	ItemType myItem = treePtr->getItem(); visit(myItem);

	for (i = 0; i < (int)itemCollection.size(); i++)
	{
		visit(itemCollection[i]);
	}
}

template<class ItemType>
void BinaryNodeTree<ItemType>::getNodeCollection(const NodeUnit root_ptr, vector<ItemType> &collection)
{
	int i;
	if (root_ptr.get() == nullptr)
	{
		cout << "BinaryNodeTree::getNodeCollection()\n+ Fatal error : The root_ptr argument cannot be null\n";
		system("pause");
		terminate();
	}

	int height = getHeightHelper(root_ptr);

	collection.clear();
	vector<ItemType> leftNodeCollection;
	vector<ItemType> rightNodeCollection;

	NodeUnit leftPtr = root_ptr->getLeftChildPtr();
	NodeUnit rightPtr = root_ptr->getRightChildPtr();

	if (leftPtr.get() != nullptr)
	{
		leftNodeCollection.push_back(leftPtr->getItem());

		for (i = 3; i <= height; i++)
			collectNodeHeight(leftPtr, leftNodeCollection, height, i, 3);
	}

	if (rightPtr.get() != nullptr)
	{
		rightNodeCollection.push_back(rightPtr->getItem());

		for (i = 3; i <= height; i++)
			collectNodeHeight(rightPtr, rightNodeCollection, height, i, 3);
	}

	int len_max = max(leftNodeCollection.size(), rightNodeCollection.size());

	collection.push_back(root_ptr->getItem());

	for (i = 0; i < len_max; i++)
	{
		if (i < leftNodeCollection.size()) collection.push_back(leftNodeCollection[i]);
		if (i < rightNodeCollection.size()) collection.push_back(rightNodeCollection[i]);
	}
}

template<class ItemType>
void BinaryNodeTree<ItemType>::generalOrder(void visit(ItemType&), NodeUnit treePtr, int height, int current_height)
{
	if (treePtr.get() == nullptr)
	{
		cout << "BinaryNodeTree::generalOrder()\n+ Fatal error : The treePtr argument cannot be null\n";
		system("pause"); 
		terminate();
	}

	// Traversing though a search binary tree
	// Example : 
	//                                                                 [1]                                                                         // Height : 5 (1)
	//                                                         [2]            [3]                                                                 // Height : 4 (2)
	//                    [4]                         [6]                                [5]                            [7]                     // Height : 3 (3)
	//            [8]           [10]        [12]           [14]             [9]             [11]         [13]               [15]        // Height : 2 (4)
	//        [16][18]    [20][22]   [24][26]     [28][30]        [17][19]       [21][23]    [25][27]        [29][31]     // Height : 1 (5)

	// Use the regular recursion method - two vectors for two parts
	// Root : 1
	// Even : 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30
	// Odd : 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31
	// Calculate height in advance too 

	int i;
	vector<ItemType> leftNodeCollection;
	vector<ItemType> rightNodeCollection;

	NodeUnit leftPtr = treePtr->getLeftChildPtr();
	NodeUnit rightPtr = treePtr->getRightChildPtr();

	if (leftPtr.get() != nullptr)
	{
		leftNodeCollection.push_back(leftPtr->getItem());

		for (i = 3; i <= height; i++)
			collectNodeHeight(leftPtr, leftNodeCollection, height, i, 3);
	}

	if (rightPtr.get() != nullptr)
	{
		rightNodeCollection.push_back(rightPtr->getItem());

		for (i = 3; i <= height; i++)
			collectNodeHeight(rightPtr, rightNodeCollection, height, i, 3);
	}

	int len_max = max(leftNodeCollection.size(), rightNodeCollection.size());

	ItemType myItem = treePtr->getItem();
	visit(myItem);

	for (i = 0; i < len_max; i++)
	{
		if (i < leftNodeCollection.size()) visit(leftNodeCollection[i]);
		if (i < rightNodeCollection.size()) visit(rightNodeCollection[i]);
	}

} // End generalOrder()


template<class ItemType>
int BinaryNodeTree<ItemType>::determineNodeCount(int height)
{
	int i;
	int totalNodeCount = 0;
	for (i = 0; i < height; i++)
	{
		totalNodeCount += pow(2, i);
	}

	return totalNodeCount;
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(NodeUnit subTreePtr)
{
	return countNumNode(subTreePtr);
}

template<class ItemType>
int BinaryNodeTree<ItemType>::countNumNode(NodeUnit root_ptr)
{
	int totalCount;

	if (root_ptr.get() == nullptr)
	{
		totalCount = 0;
	}
	else
	{
		totalCount = 1;

		NodeUnit leftPtr = root_ptr->getLeftChildPtr();
		NodeUnit rightPtr = root_ptr->getRightChildPtr();

		totalCount += countNumNode(leftPtr);
		totalCount += countNumNode(rightPtr);
	}

	return totalCount;
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::accessBalancedUncompletedNodeHelper(NodeUnit root_ptr, int height, int target_height, int current_height, NodeUnit& result_ptr)
{
	if (root_ptr.get() == nullptr)
	{
		cout << "BinaryNodeTree::accessBalancedUncompletedNodeHelper()\n+ Fatal error : The root_ptr argument cannot be null\n";
		system("pause");
		terminate();
	}

	NodeUnit leftPtr = root_ptr->getLeftChildPtr();
	NodeUnit rightPtr = root_ptr->getRightChildPtr();

	if (target_height == current_height)
	{
		if (leftPtr.get() == nullptr)
		{
			result_ptr = root_ptr;
			return true;
		}

		if (rightPtr.get() == nullptr)
		{
			result_ptr = root_ptr;
			return true;
		}

		return false;
	}

	if (leftPtr.get() != nullptr)
		if (accessBalancedUncompletedNodeHelper(leftPtr, height, target_height, current_height - 1, result_ptr)) return true;

	if (rightPtr.get() != nullptr)
		if (accessBalancedUncompletedNodeHelper(rightPtr, height, target_height, current_height - 1, result_ptr)) return true;

	return false;
}


template<class ItemType>
bool BinaryNodeTree<ItemType>::accessBalancedUncompletedNode(NodeUnit root_ptr, int height, int current_height, NodeUnit& result_ptr)
{
	int i;
	if (root_ptr.get() == nullptr)
	{
		cout << "BinaryNodeTree::accessBalancedUncompletedNode()\n+ Fatal error : The root_ptr argument cannot be null\n";
		system("pause"); 
		terminate();
	}

	NodeUnit leftPtr = root_ptr->getLeftChildPtr();
	NodeUnit rightPtr = root_ptr->getRightChildPtr();

	if (leftPtr.get() == nullptr || rightPtr.get() == nullptr)
	{
		result_ptr = root_ptr;
		return true;
	}

	for (i = current_height - 1; i >= 2; i--)
	{
		if (leftPtr.get() != nullptr)
			if (accessBalancedUncompletedNodeHelper(leftPtr, height, i, current_height - 1, result_ptr)) return true;

		if (rightPtr.get() != nullptr)
			if (accessBalancedUncompletedNodeHelper(rightPtr, height, i, current_height - 1, result_ptr)) return true;
	}

	return false;
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::accessLeftBalancedNode(NodeUnit root_ptr, int height, int current_height, NodeUnit& result_ptr)
{
	if (root_ptr.get() == nullptr)
	{
		cout << "BinaryNodeTree::accessLeftBalancedNode()\n+ Fatal error : The root_ptr argument cannot be null\n";
		system("pause");
		terminate();
	}

	NodeUnit leftPtr = root_ptr->getLeftChildPtr();

	if (leftPtr.get() == nullptr)
	{
		result_ptr = root_ptr;
		return true;
	}

	if (leftPtr.get() != nullptr)
		return accessLeftBalancedNode(leftPtr, height, current_height - 1, result_ptr);

	return false;
}


// You may use a pointer the catch the return value
template<class ItemType>
bool BinaryNodeTree<ItemType>::accessUncompletedNode(NodeUnit root_ptr, NodeUnit &result_ptr, int height, int current_height, ItemType newItem)
{
	// To determine which node is the right successor

	if (height == 0)
	{
		cout << "BinaryNodeTree::accessUncompletedNode()\n+ Fatal error : The height argument cannot be 0\n";
		system("pause"); 
		terminate();
	}

	if (root_ptr.get() == nullptr)
	{
		cout << "BinaryNodeTree::accessUncompletedNode()\n+ Fatal error : The root_ptr argument cannot be null\n";
		system("pause");
		terminate();
	}

	int halfCount = (determineNodeCount(current_height) - 1) / 2;

	NodeUnit leftPtr = root_ptr->getLeftChildPtr();
	int nodeLeftCount = countNumNode(leftPtr);

	NodeUnit rightPtr = root_ptr->getRightChildPtr();
	int nodeRightCount = countNumNode(rightPtr);

	if (height == 1)
	{
		result_ptr = root_ptr;
		return true;
	}

	// Algorithm : When detecting that there is a difference between nodeLeftCount and nodeRightCount
	// if(nodeLeftCount < nodeRightCount) - Add an element to the left side (from left order) to balance the left side
	// if(nodeRightCount < nodeLeftCount) - Add an element to the left side (from left order) to balance the right side
	// if(nodeRightCount == nodeLeftCount) - Add an element to the left side (from left order)

	if (nodeLeftCount == nodeRightCount && nodeLeftCount == 0)
	{
		result_ptr = root_ptr;
		return true;
	}

	if (nodeLeftCount < nodeRightCount)
	{
		if (leftPtr.get() == nullptr)
		{
			result_ptr = root_ptr;
			return true;
		}

		bool result = accessBalancedUncompletedNode(leftPtr, height, current_height - 1, result_ptr);
		if (!result) { cout << "Abort A1F4\n"; abort(); }

		return true;
	}
	else if (nodeRightCount < nodeLeftCount)
	{
		if (rightPtr.get() == nullptr)
		{
			result_ptr = root_ptr;
			return true;
		}

		bool result = accessBalancedUncompletedNode(rightPtr, height, current_height - 1, result_ptr);
		if (!result) result = accessLeftBalancedNode(rightPtr, height, current_height - 1, result_ptr);
		if (!result) { cout << "Abort C2A6\n"; abort(); }

		return true;
	}
	else if (nodeRightCount == nodeLeftCount)
	{
		bool result;

		if (nodeRightCount != halfCount)
			result = accessBalancedUncompletedNode(leftPtr, height, current_height - 1, result_ptr);
		else
			result = accessLeftBalancedNode(leftPtr, height, current_height - 1, result_ptr);

		if (!result) { cout << "Abort D38A\n"; abort(); }

		return true;
	}

	return false;
} // End accessUncompletedNode()



template<class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData)
{
	NodeUnit newNodePtr = std::make_shared<BinaryUnit>(newData);

	if (rootPtr.get() == nullptr)
	{
		rootPtr = newNodePtr;
	}
	else
	{
		int max_height = getHeightHelper(rootPtr);

		NodeUnit targetPtr;
		accessUncompletedNode(rootPtr, targetPtr, max_height, max_height, newData);

		balancedAdd(targetPtr, newNodePtr);
	}

	return true;
} // end add

template<class ItemType>
NodeUnit BinaryNodeTree<ItemType>::balancedAdd(NodeUnit subTreePtr, NodeUnit newNodePtr)
{
	if (subTreePtr.get() == nullptr)
	{
		cout << "BinaryNodeTree::balancedAdd()\n+ Fatal error : The subTreePtr argument cannot be null\n";
		system("pause");
		terminate();
	}

	NodeUnit leftPtr = subTreePtr->getLeftChildPtr();
	NodeUnit rightPtr = subTreePtr->getRightChildPtr();

	if (leftPtr.get() == nullptr)
	{
		subTreePtr->setLeftChildPtr(newNodePtr);
	}
	else if (rightPtr.get() == nullptr)
	{
		subTreePtr->setRightChildPtr(newNodePtr);
	}

	return subTreePtr;
} // End balancedAdd()


template<class ItemType>
int BinaryNodeTree<ItemType>::getHeightHelper(NodeUnit subTreePtr)
{
	if (subTreePtr == nullptr)
		return 0;
	else
		return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr()));

} // end getHeightHelper


template<class ItemType>
void BinaryNodeTree<ItemType>::postorder(void visit(ItemType&), NodeUnit treePtr)
{
	if (treePtr != nullptr)
	{
		postorder(visit, treePtr->getLeftChildPtr());
		postorder(visit, treePtr->getRightChildPtr());
		ItemType theItem = treePtr->getItem();
		visit(theItem);
	} // End If-statement
} // End postorder()


template<class ItemType>
void BinaryNodeTree<ItemType>::preorder(void visit(ItemType&), NodeUnit treePtr)
{
	if (treePtr != nullptr)
	{
		ItemType theItem = treePtr->getItem();
		visit(theItem);
		preorder(visit, treePtr->getLeftChildPtr());
		preorder(visit, treePtr->getRightChildPtr());
	} // End If-statement
} // End preorder()


template<class ItemType>
void BinaryNodeTree<ItemType>::inorder(void visit(ItemType&), NodeUnit treePtr)
{
	if (treePtr != nullptr)
	{
		inorder(visit, treePtr->getLeftChildPtr());
		ItemType theItem = treePtr->getItem();
		visit(theItem);
		inorder(visit, treePtr->getRightChildPtr());
	} // End If-statement
} // End inorder()

template<class ItemType>
NodeUnit BinaryNodeTree<ItemType>::removeValue(NodeUnit &subTreePtr, const ItemType target, bool& isSuccessful)
{
	int i;
	if (subTreePtr.get() == nullptr)
	{
		isSuccessful = false;
		return subTreePtr;
	}

	vector<ItemType> itemCollection;
	getNodeCollection(subTreePtr, itemCollection);

	for (i = 0; i < (int)itemCollection.size(); i++)
	{
		if (itemCollection[i] == target)
		{
			isSuccessful = true;
			itemCollection.erase(itemCollection.begin() + i);
			break;
		}
	}

	if (i == itemCollection.size()) isSuccessful = false;

	NodeUnit newNodePtr;
	NodeUnit targetPtr;

	if (isSuccessful)
	{
		subTreePtr = nullptr;
		for (i = 0; i < (int)itemCollection.size(); i++)
		{
			newNodePtr = std::make_shared<BinaryUnit >(itemCollection[i]);

			if (subTreePtr.get() == nullptr)
			{
				subTreePtr = newNodePtr;
			}
			else
			{
				int max_height = getHeightHelper(subTreePtr);

				NodeUnit targetPtr;
				accessUncompletedNode(subTreePtr, targetPtr, max_height, max_height, itemCollection[i]);

				balancedAdd(targetPtr, newNodePtr);
			}
		}
	}

	return subTreePtr;
}

template<class ItemType>
void BinaryNodeTree<ItemType>::destroyTree(NodeUnit &subTreePtr)
{
	subTreePtr = nullptr;
}

template<class ItemType>
void BinaryNodeTree<ItemType>::clear()
{
	destroyTree(rootPtr);
}

template<class ItemType>
NodeUnit BinaryNodeTree<ItemType>::copyTree(const NodeUnit oldTreeRootPtr)
{
	return copyTreeHelper(rootPtr, oldTreeRootPtr);
}

template<class ItemType>
NodeUnit BinaryNodeTree<ItemType>::copyTreeHelper(NodeUnit &root_ptr, const NodeUnit oldTreeRootPtr)
{
	int i;
	destroyTree(root_ptr);

	if (oldTreeRootPtr.get() == nullptr)
	{
		return root_ptr;
	}

	int max_height = getHeightHelper(oldTreeRootPtr);

	vector<ItemType> itemCollection;
	getNodeCollection(oldTreeRootPtr, itemCollection);

	NodeUnit newNodePtr;
	NodeUnit targetPtr;
	for (i = 0; i < (int)itemCollection.size(); i++)
	{
		newNodePtr = std::make_shared<BinaryUnit >(itemCollection[i]);

		if (root_ptr.get() == nullptr)
		{
			root_ptr = newNodePtr;
		}
		else
		{
			int max_height = getHeightHelper(root_ptr);

			NodeUnit targetPtr;
			accessUncompletedNode(root_ptr, targetPtr, max_height, max_height, itemCollection[i]);

			balancedAdd(targetPtr, newNodePtr);
		}
	}

	return root_ptr;
}

template<class ItemType>
void BinaryNodeTree<ItemType>::generalOrderTraverse(void visit(ItemType&)) const
{
	if (rootPtr.get() == nullptr) return;

	int max_height = getHeightHelper(rootPtr);
	generalOrder(visit, rootPtr, max_height, 1);
} // End generalOrderTraverse()

template<class ItemType>
void BinaryNodeTree<ItemType>::linearOrderTraverse(void visit(ItemType&)) const
{
	if (rootPtr.get() == nullptr) return;

	int max_height = getHeightHelper(rootPtr);
	linearOrder(visit, rootPtr, max_height, 1);
} // End linearOrderTraverse()

template<class ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType&)) const
{
	preorder(visit, rootPtr);
}

template<class ItemType>
void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType&)) const
{
	postorder(visit, rootPtr);
}

template<class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
	inorder(visit, rootPtr);
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const
{
	return (rootPtr.get() == nullptr);
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeight() const
{
	return getHeightHelper(rootPtr);
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes() const
{
	return countNumNode(rootPtr);
}

template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getRootData() const throw(PrecondViolatedExcept)
{
	if (rootPtr.get() != nullptr)
	{
		return rootPtr->getItem();
	}

	throw PrecondViolatedExcept("BinaryNodeTree::getRootData() : The rootPtr is null");
}

template<class ItemType>
void BinaryNodeTree<ItemType>::setRootData(const ItemType& newData) throw(PrecondViolatedExcept)
{
	if (rootPtr.get() != nullptr)
	{
		rootPtr->setItem(newData);
	}

	throw PrecondViolatedExcept("BinaryNodeTree::setRootData() : The rootPtr is null");
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::remove(const ItemType& data)
{
	bool isSuccessful;
	removeValue(rootPtr, data, isSuccessful);

	return isSuccessful;
}

#endif

