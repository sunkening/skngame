#include "base.h"
#include <string>
#include <iostream>
using namespace  std;
#include "SException.h"
#include "base.h"
#include "List.h"
#include "tree.h"

namespace skn
{
Tree::Tree(void)
{
}


Tree::~Tree(void)
{
}
STreeNode::STreeNode(void)
{
	father=null;
}


STreeNode::~STreeNode(void)
{
}

void STreeNode::addChild(STreeNode* child)
{
	children.add(child);
}
STreeNode2X::STreeNode2X(void)
{
}


STreeNode2X::~STreeNode2X(void)
{
}
}






