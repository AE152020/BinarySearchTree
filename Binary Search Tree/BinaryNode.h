#ifndef BINARY_NODE_
#define BINARY_NODE_
#include "General.h"

// Should be "using NodeUnit = std::shared_ptr<BinaryNode<ItemType> >;"
#define BinaryUnit BinaryNode<ItemType>
#define NodeUnit std::shared_ptr<BinaryUnit>

template<class ItemType>
class BinaryNode
{
private:
	ItemType item;          // Data portion
	NodeUnit leftChildPtr;  // Pointer to left child
	NodeUnit rightChildPtr; // Pointer to right child

public:
	BinaryNode();
	BinaryNode(const ItemType& anItem);
	BinaryNode(const ItemType& anItem, NodeUnit leftPtr, NodeUnit rightPtr);

	void setItem(const ItemType& anItem);
	ItemType getItem() const;

	bool isLeaf() const;

	NodeUnit getLeftChildPtr() const;
	NodeUnit getRightChildPtr() const;

	NodeUnit& getLeftChildPtrReference();
	NodeUnit& getRightChildPtrReference();

	void setLeftChildPtr(NodeUnit leftPtr);
	void setRightChildPtr(NodeUnit rightPtr);
}; // end BinaryNode

template<class ItemType>
BinaryNode<ItemType>::BinaryNode() {}

template<class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem) : item(anItem) {}

template<class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem, NodeUnit leftPtr, NodeUnit rightPtr) :
	item(anItem),
	leftChildPtr(leftPtr),
	rightChildPtr(rightPtr)
{}

template<class ItemType>
void BinaryNode<ItemType>::setItem(const ItemType& anItem)
{
	item = anItem;
}

template<class ItemType>
ItemType BinaryNode<ItemType>::getItem() const
{
	return item;
}

template<class ItemType>
void BinaryNode<ItemType>::setLeftChildPtr(NodeUnit leftPtr)
{
	leftChildPtr = leftPtr;
}

template<class ItemType>
void BinaryNode<ItemType>::setRightChildPtr(NodeUnit rightPtr)
{
	rightChildPtr = rightPtr;
}

template<class ItemType>
NodeUnit BinaryNode<ItemType>::getLeftChildPtr() const
{
	return leftChildPtr;
}

template<class ItemType>
NodeUnit BinaryNode<ItemType>::getRightChildPtr() const
{
	return rightChildPtr;
}

template<class ItemType>
NodeUnit& BinaryNode<ItemType>::getLeftChildPtrReference()
{
	return leftChildPtr;
}

template<class ItemType>
NodeUnit& BinaryNode<ItemType>::getRightChildPtrReference()
{
	return rightChildPtr;
}

template<class ItemType>
bool BinaryNode<ItemType>::isLeaf() const
{
	if (rightChildPtr == nullptr && leftChildPtr == nullptr)
		return true;
	else
		return false;
}

#endif 

