#include "binary_tree.h"

namespace r_DataStructure
{
	r_BinaryTree::r_BinaryTree()
	{
		data = 0;
		left = 0;
		right = 0;
	}
	r_BinaryTree::r_BinaryTree(int received_data, r_BinaryTree *received_left, r_BinaryTree *received_right)
	{
		data = received_data;
		left = received_left;
		right = received_right;
	}

}