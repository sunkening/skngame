

#include "graph.h"
namespace skn
{

Graph::Graph(void)
{
}


Graph::~Graph(void)
{
}


GraphNode::GraphNode(void)
{
	mark=GRAPH_NODE_UNMARKED;
}


GraphNode::~GraphNode(void)
{
}
//**************************************
 
GraphStatic ::GraphStatic( )
{
}

 
GraphStatic ::~GraphStatic( )
{
}

 
 
void GraphStatic ::addNode(GraphNode*node)
{
	nodes.push_back(node);
}
 
void GraphStatic ::addEdge(GraphEdge*edge,int index_v1, int index_v2,int direction )
{
	edge->index_v1=index_v1;
	edge->index_v2=index_v2;
	GraphNode *v1=nodes[index_v1];
	GraphNode *v2=nodes[index_v2];
/*
	edge->v1=v1;
	edge->v2=v2;*/
	v1->edgeList.push_back( edge);
	if (direction==GRAPH_EDGE_UNDIRECTED)
	{
		v2->edgeList.push_back( edge);
	}
	edges.push_back(edge);
}
 
void GraphStatic ::deepFirstSearch(int node_index)
{
	GraphNode *node=nodes[node_index];
	node->mark=GRAPH_NODE_MARKED;
	node->preWork();
	list<GraphEdge*>::iterator iter;
	for (iter=node->edgeList.begin();iter!=node->edgeList.end();iter++)
	{
		GraphEdge* edge=(*iter);
		if (!edge->mark)
		{
			edge->mark=GRAPH_EDGE_MARKED;
		}
		int other_node_index=edge->index_v2;
		if (edge->index_v2==node_index)
		{
			other_node_index=edge->index_v1;
		}
		GraphNode *v2=nodes[other_node_index];
		if (!v2->mark)
		{
			deepFirstSearch( other_node_index);
			edge->postWork();
		}
	}
}
//****************************************************
GraphEdge::GraphEdge(void)
{
	index_v1=0;
	index_v2=0;
	mark=GRAPH_EDGE_UNDIRECTED;
}


GraphEdge::~GraphEdge(void)
{
}







 

}





