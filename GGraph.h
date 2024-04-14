#pragma once
#define MAX_VERTEX_NUM 16
#include"global.h"
typedef int Vertexs[160];
typedef bool AdjMatrix[10][16];
class GGraph
{
public:
	GGraph();
	void InitGraph();
	static AdjMatrix  m_AdjMatrix;
protected:
	Vertexs m_Vertices;
	int m_nVertexNum;
	int m_nArcnum;
};

