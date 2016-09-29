#pragma once

namespace skn
{
	class STreeNode;
	class Tree
	{
	public:
		Tree(void);
		virtual ~Tree(void);
		STreeNode* root;
	};
	class STreeNode :
		public SObject
	{
	private:
		STreeNode *father;
	public:
		List children;

	public:
		STreeNode(void);
		virtual ~STreeNode(void);
		void addChild(STreeNode* child);
	};
	class STreeNode2X:
		public SObject
	{
	private:
		STreeNode *father;
		STreeNode *childLeft;
		STreeNode *childRight;
	public:
		STreeNode2X(void);
		~STreeNode2X(void);
	};
}






