
#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcept.h"

template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType>
{
private:
	NodeUnit rootPtr;

protected:
	//------------------------------------------------------------
	//    Protected Utility Methods Section:
	//    Recursive helper methods for the public methods.
	//------------------------------------------------------------
	// Places a given new node at its proper position in this binary search tree.
	NodeUnit placeNode(NodeUnit subTreePtr, NodeUnit newNode);

	// Removes the given target value from the tree while maintaining a binary search tree.
	NodeUnit removeValue(NodeUnit &subTreePtr, const ItemType target, bool& isSuccessful) override;

	// Removes a given node from a tree while maintaining a binary search tree.
	NodeUnit removeNode(NodeUnit nodePtr);

	// Removes the (last) node in the left subtree of the node pointed to by nodePtr.
	// Sets inorderSuccessor to the value in this node.
	// Returns a pointer to the (last) node (not the node that was removed)
	NodeUnit removeLeftmostNode(NodeUnit &subTreePtr, ItemType& inorderSuccessor);

	// Returns a pointer to the node containing the given value, or nullptr if not found.
	NodeUnit findNode(NodeUnit treePtr, const ItemType& target) const;

public:
	//------------------------------------------------------------
	// Constructor and Destructor Section.
	//------------------------------------------------------------
	BinarySearchTree();
	BinarySearchTree(const ItemType& rootItem);
	BinarySearchTree(const BinarySearchTree<ItemType>& tree);
	virtual ~BinarySearchTree();

	//------------------------------------------------------------
	// Public Methods Section.
	//------------------------------------------------------------
	bool isEmpty() const;
	int getHeight() const;
	int getNumberOfNodes() const;

	ItemType getRootData() const throw(PrecondViolatedExcept);
	void setRootData(const ItemType& newData);

	bool add(const ItemType& newEntry);
	bool remove(const ItemType& target);
	void clear();

	ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException);
	bool contains(const ItemType& anEntry) const;

	//------------------------------------------------------------
	// Public Traversals Section.
	//------------------------------------------------------------
	void preorderTraverse(void visit(ItemType&)) const;
	void inorderTraverse(void visit(ItemType&)) const;
	void postorderTraverse(void visit(ItemType&)) const;
	void generalOrderTraverse(void visit(ItemType&)) const;
	void linearOrderTraverse(void visit(ItemType&)) const;

	//------------------------------------------------------------
	// Overloaded Operator Section.
	//------------------------------------------------------------
	BinarySearchTree<ItemType>&
		operator=(const BinarySearchTree<ItemType>& rightHandSide);
}; // end BinarySearchTree

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree()
{
}

template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree()
{
}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem) : BinaryNodeTree<ItemType>(rootItem)
{
}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& tree)
{
	BinaryNodeTree<ItemType>::copyTree(tree.getRoot());
}

template<class ItemType>
BinarySearchTree<ItemType>& BinarySearchTree<ItemType>::operator = (const BinarySearchTree<ItemType>& rightHandSide)
{
	if (&rightHandSide != this)
	{
		BinaryNodeTree<ItemType>::copyTree(rightHandSide.getRoot());
	}

	return (*this);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const
{
	return BinaryNodeTree<ItemType>::isEmpty();
}

template<class ItemType>
int BinarySearchTree<ItemType>::getHeight() const
{
	return BinaryNodeTree<ItemType>::getHeight();
}

template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const
{
	return BinaryNodeTree<ItemType>::getNumberOfNodes();
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getRootData() const throw(PrecondViolatedExcept)
{
	return BinaryNodeTree<ItemType>::getRootData();
}

template<class ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType& newData) throw(PrecondViolatedExcept)
{
	BinaryNodeTree<ItemType>::setRootData(newData);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newData)
{
	return BinaryNodeTree<ItemType>::add(newData);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& data)
{
	return BinaryNodeTree<ItemType>::remove(data);
}

template<class ItemType>
void BinarySearchTree<ItemType>::clear()
{
	BinaryNodeTree<ItemType>::clear();
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry) const throw(NotFoundException)
{
	return BinaryNodeTree<ItemType>::getEntry(anEntry);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType& anEntry) const
{
	return BinaryNodeTree<ItemType>::contains(anEntry);
}

template<class ItemType>
void BinarySearchTree<ItemType>::preorderTraverse(void visit(ItemType&)) const
{
	BinaryNodeTree<ItemType>::preorderTraverse(visit);
}

template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
	BinaryNodeTree<ItemType>::inorderTraverse(visit);
}

template<class ItemType>
void BinarySearchTree<ItemType>::postorderTraverse(void visit(ItemType&)) const
{
	BinaryNodeTree<ItemType>::postorderTraverse(visit);
}

template<class ItemType>
void BinarySearchTree<ItemType>::generalOrderTraverse(void visit(ItemType&)) const
{
	BinaryNodeTree<ItemType>::generalOrderTraverse(visit);
}

template<class ItemType>
void BinarySearchTree<ItemType>::linearOrderTraverse(void visit(ItemType&)) const
{
	BinaryNodeTree<ItemType>::linearOrderTraverse(visit);
}

template<class ItemType>
NodeUnit BinarySearchTree<ItemType>::placeNode(NodeUnit subTreePtr, NodeUnit newNodePtr)
{
	return BinaryNodeTree<ItemType>::balancedAdd(subTreePtr, newNodePtr);
}

template<class ItemType>
NodeUnit BinarySearchTree<ItemType>::removeValue(NodeUnit &subTreePtr, const ItemType target, bool& isSuccessful)
{
	return BinaryNodeTree<ItemType>::removeValue(subTreePtr, target, isSuccessful);
}

template<class ItemType>
NodeUnit BinarySearchTree<ItemType>::removeNode(NodeUnit nodePtr)
{
	if (nodePtr.get() == nullptr)
	{
		return nodePtr;
	}

	bool isSuccessful;
	ItemType myItem = nodePtr.getItem();
	return BinaryNodeTree<ItemType>::removeValue(nodePtr.getRoot(), myItem, isSuccessful);
}

template<class ItemType>
NodeUnit BinarySearchTree<ItemType>::removeLeftmostNode(NodeUnit &subTreePtr, ItemType& inorderSuccessor)
{
	int i;
	if (subTreePtr.get() == nullptr)
	{
		return subTreePtr;
	}

	vector<ItemType> itemCollection;
	getNodeCollection(subTreePtr, itemCollection);

	inorderSuccessor = itemCollection.back();
	itemCollection.erase(itemCollection.end() - 1);

	NodeUnit newNodePtr;
	NodeUnit targetPtr;

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

template<class ItemType>
NodeUnit BinarySearchTree<ItemType>::findNode(NodeUnit treePtr, const ItemType& target) const
{
	bool isSuccessful;
	return BinaryNodeTree<ItemType>::findNode(treePtr, target, isSuccessful);
}

#endif
