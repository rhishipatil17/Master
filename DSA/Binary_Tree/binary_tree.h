#ifndef BINARYTREE_H
#define BINARYTREE_H

namespace DataStructure
{
	class BinaryTree
	{
		public:
			BinaryTree();
			BinaryTree(int received_data, BinaryTree *received_left, BinaryTree *received_right);

			//tree specific

			//node specific
			int getData();
			BinaryTree* getLeft();
			BinaryTree* getRight();

		private:
			int data;
			BinaryTree *left;
			BinaryTree *right;
	};
}

#endif