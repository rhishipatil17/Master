#include "binary_tree.h"

namespace DataStructure
{
	BinaryTree::BinaryTree()
	{
		data = 0;
		left = 0;
		right = 0;
	}
	BinaryTree::BinaryTree(int received_data, BinaryTree *received_left, BinaryTree *received_right)
	{
		data = received_data;
		left = received_left;
		right = received_right;
	}

	int BinaryTree::getData()
	{
		return data;
	}

	BinaryTree* BinaryTree::getLeft()
	{
		return left;
	}

	BinaryTree* BinaryTree::getRight()
	{
		return right;
	}
}