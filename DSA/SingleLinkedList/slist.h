#ifndef SLIST_H
#define SLIST_H

namespace DataStructure
{
	class node
	{
		int data;
		node *next;

		node(int p_data, node* ptr) : data(p_data), next(ptr) {}

		public:
			friend class SingleLinkedList;
	};

	class SingleLinkedList
	{
		public:	
			SingleLinkedList();

			unsigned int getLength();

			void addBegin(int p_data);
			void addEnd(int p_data);
			void removeBegin();
			void removeEnd();

			int operator[](unsigned pos);
		
		private:
			node *hptr;
			unsigned int length;
	};
}	

#endif