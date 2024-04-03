#ifndef BINARYTREE_H
#define BINARYTREE_H

namespace r_DataStructure
{
	class r_BinaryTree
	{
		public:
			r_BinaryTree();
			r_BinaryTree(int received_data, r_BinaryTree *received_left, r_BinaryTree *received_right);

		private:
			int data;
			r_BinaryTree *left;
			r_BinaryTree *right;
	};
}

#endif