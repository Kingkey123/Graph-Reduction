#include "Graph.h"

void Graph::init()
{
	memset(head, -1, sizeof(head));
	vn = 0;
	en = 0;
}

void Graph::addv(int id, int label)
{
	vtx[id] = Vertex(id, label);
	vn++;
}

void Graph::addse(int u, int v, int label)
{
	edge[en] = Edge(u, v, label, head[u]);
	head[u] = en++;
}

void Graph::adde(int u, int v, int label)
{
	addse(u, v, label);
	addse(v, u, label);
}

void Graph::delse(int u, int v, int label)
{
	for (int i = head[u];~i;i = edge[i].next)
	{
		if (edge[i].u == u&&edge[i].v == v&&edge[i].label == label)
		{
			edge[i].del = 1;
			return;
		}
	}
}

void Graph::dele(int u, int v, int label)
{
	for (int i = head[u];~i;i = edge[i].next)
	{
		if (edge[i].u == u&&edge[i].v == v&&edge[i].label == label)
		{
			edge[i].del = 1;
			edge[i ^ 1].del = 1;
			return;
		}
	}
	//delse(u, v, label);
	//delse(v, u, label);
}

void Graph::printGraph() {
	cout << "head: ";
	for (int i = 0; i < en; i++) {
		cout << head[i] << " ";
	}
	cout << endl;
	
	cout << "vertex:";
	for (int i = 0; i < vn; i++) {
		cout << vtx[i].id;
	}
	cout << endl;

	cout << "edge:" << en << " ";
	for (int i = 0; i < en; i++) {
		cout << edge[i].u <<  " ";//" " << edge[i].v <<
	}
}