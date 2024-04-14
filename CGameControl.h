#pragma once
#include"global.h"
#include"CGameLogic.h"
class CGameControl:public GGraph
{
public:
	void SetFirstPoint(int nRow, int nCol);
	void SetSecPoint(int nRow, int nCol);
	bool Link();
	Vertex m_ptSelFirst;
	Vertex m_ptSelSec;
};

