#pragma once
#include"GGraph.h"
#include"global.h"
class CGameLogic
{
public:
	void InitMap(AdjMatrix m_AdjMatrix);
	bool IsLink(Vertex v1, Vertex v2);
	void Clear(Vertex v1, Vertex v2);
protected:
	bool LinkInRow(Vertex v1, Vertex v2);
	bool LinkInCol(Vertex v1, Vertex v2);
	bool LineRow(int nRow1, int nRow2, int nCol1);
	bool LineCol(int nRow1, int nCol1, int nCol2);
	bool OneCornerLink(Vertex v1, Vertex v2);
	bool TwoCornerLink(Vertex v1, Vertex v2);
};

