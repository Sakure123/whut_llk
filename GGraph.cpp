#include "GGraph.h"
AdjMatrix GGraph::m_AdjMatrix; 
GGraph::GGraph()
{
	InitGraph();
}
void GGraph::InitGraph()
{
	for (int i = 0; i < 160; i++)
	{
		m_Vertices[i] = -1;
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			m_AdjMatrix[i][j] = true;
		}
	}
}
