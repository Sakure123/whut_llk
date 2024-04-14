#include "CGameLogic.h"

void CGameLogic::InitMap(AdjMatrix m_AdjMatrix)
{
	
}

bool CGameLogic::IsLink(Vertex v1, Vertex v2)
{
	//一条直线连通
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	if (GGraph::m_AdjMatrix[nRow1][nCol1] == false || GGraph::m_AdjMatrix[nRow2][nCol2] == false)
		return false;
	if (nRow1 == nRow2)
	{
		if ((LinkInRow(v1, v2)))
		{
			//Clear(v1, v2);
			return true;
		}
	}
	if (nCol1 == nCol2)
	{
		if ((LinkInCol( v1, v2)))
		{
			//Clear( v1, v2);
			return true;
		}
	}
	//两条直线连通
	if ((OneCornerLink(v1, v2)) == true)
	{
		//Clear( v1, v2);
		return true;
	}
	//三条直线连通
	if ((TwoCornerLink( v1, v2)) == true)
	{
		//Clear( v1, v2);
		return true;
	}
	return false;
}

void CGameLogic::Clear( Vertex v1, Vertex v2)
{
	GGraph::m_AdjMatrix[v1.row][v1.col] = false;
	GGraph::m_AdjMatrix[v2.row][v2.col] = false;
}

bool CGameLogic::LinkInRow( Vertex v1, Vertex v2)
{
	int nRow = v2.row;
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	if (nCol1 > nCol2)
	{
		int temp = nCol1;
		nCol1 = nCol2;
		nCol2 = temp;
	}
	for (int i = nCol1+1; i <= nCol2; i++)
	{
		if (i == nCol2)
		{
			return true;
		}
		if (GGraph::m_AdjMatrix[nRow][i] != false)
		{
			break;
		}
	}
	return false;
}

bool CGameLogic::LinkInCol(Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol1 = v1.col;
	if (nRow1 > nRow2)
	{
		int temp = nRow1;
		nRow1 = nRow2;
		nRow2 = temp;
	}
	for (int i = nRow1 + 1; i <=nRow2; i++)
	{
		if (i == nRow2)
		{
			return true;
		}
		if (GGraph::m_AdjMatrix[i][nCol1] != false)
		{
			break;
		}
	}
	return false;
}

bool CGameLogic::LineCol(int nRow1, int nRow2, int nCol1)
{
	if (nRow1 > nRow2)
	{
		int temp = nRow1;
		nRow1 = nRow2;
		nRow2 = temp;
	}
	for (int i = nRow1 + 1; i <= nRow2; i++)
	{
		if (i == nRow2)
		{
			return true;
		}
		if (GGraph::m_AdjMatrix[i][nCol1] != false)
		{
			break;
		}
	}
	return false;
}

bool CGameLogic::LineRow(int nRow1, int nCol1, int nCol2)
{
	if (nCol1 > nCol2)
	{
		int temp = nCol1;
		nCol1 = nCol2;
		nCol2 = temp;
	}
	for (int i = nCol1 + 1; i <= nCol2; i++)
	{
		if (i == nCol2)
		{
			return true;
		}
		if (GGraph::m_AdjMatrix[nRow1][i] != false)
		{
			break;
		}
	}
	return false;
}

bool CGameLogic::OneCornerLink(Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	if (GGraph::m_AdjMatrix[nRow1][nCol2]==false)//判断第一个图像的横线与第二个图像的纵线的交点是否连通
	{
		if ((LineRow(nRow1, nCol1, nCol2))&&(LineCol(nRow1, nRow2, nCol2)))//判断该交点的横线与纵线是否连通
		{

				return true;
		
		}
	}
	if(GGraph::m_AdjMatrix[nRow2][nCol1]==false)//判断第一个图像的纵线与第二个图像的横线的交点是否连通
	{
		if ((LineCol(nCol1, nRow1, nRow2))&&(LineRow(nRow2, nCol1, nCol2)))//判断该交点的横线与纵线是否连通
		{
				return true;
		}
	}
	return false;
}

bool CGameLogic::TwoCornerLink(Vertex v1, Vertex v2)
{
	for (int nCol = 0; nCol < 16; nCol++)
	{
		if (GGraph::m_AdjMatrix[v1.row][nCol] == false && GGraph::m_AdjMatrix[v2.row][nCol] == false)//找到和y轴平行的可以连通的线与两个点的横轴的两个交点
		{
			if (LineCol(v1.row, v2.row, nCol))//这两个交点判断其是否为连通
			{
				if (LineRow(v1.row, v1.col, nCol) && LineRow(v2.row, v2.col, nCol))//判断这两个交点与第一个图像和第二的图像的横线是否连通
				{
					return true;
				}
			}
		}
	}
	for (int nRow = 0; nRow < 10; nRow++)
	{
		if (GGraph::m_AdjMatrix[nRow][v1.col] == false && GGraph::m_AdjMatrix[nRow][v2.col] == false)//找到和x轴平行的可以连通的线与两个点的横轴的两个交点
		{
			if (LineRow(nRow, v1.col, v2.col))//这两个交点判断其是否为连通
			{
				if (LineCol(nRow, v1.row, v1.col) && LineCol(nRow, v2.row, v2.col))//判断这两个交点与第一个图像和第二的图像的纵线是否连通
				{
					return true;
				}
			}
		}
	}
	return false;
}
