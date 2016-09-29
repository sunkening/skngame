#pragma once

#include <vector>
#include <list>
using namespace std;
#define GRAPH_NODE_MARKED 1
#define GRAPH_NODE_UNMARKED 0
#define GRAPH_EDGE_MARKED 1
#define GRAPH_EDGE_UNMARKED 0
#define  GRAPH_EDGE_DIRECTED 1 //定向边
#define  GRAPH_EDGE_UNDIRECTED 1 //非定向边
namespace skn
{

	class GraphEdge;
	class Graph
	{
	public:
		Graph(void);
		virtual ~Graph(void);
		int v;
		int e;


	};

	class GraphNode
	{
	public:
		GraphNode(void);
		~GraphNode(void);
		int mark;
		list<GraphEdge*> edgeList;
		virtual void preWork(){};
	};
 
	class GraphStatic : public Graph
	{
	private:
		vector<GraphEdge*> edges;
	public:
		GraphStatic( );
		virtual ~GraphStatic( );
		vector<GraphNode*> nodes;
		void init(int v,int e);

		void addNode(GraphNode*node);
		void addEdge(GraphEdge*edge,int index_v1, int index_v2,int direction=GRAPH_EDGE_UNDIRECTED);
		void deepFirstSearch(int node_index);
		void breadthFirstSearch();
	};
	class GraphEdge
	{
	public:
		GraphEdge(void);
		virtual ~GraphEdge(void);
		int mark;
		int index_v1;
		int index_v2;
/*
		GraphNode* v1;
		GraphNode* v2;*/

		virtual void postWork(){};


	};

	 
}




