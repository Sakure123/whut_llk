#include "CGameControl.h"
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}

void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
}

bool CGameControl::Link()
{
	if (m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col)//判断图片是否为同一张
	{
		return false;
	}
	CGameLogic gamelogic;
	if (gamelogic.IsLink(m_ptSelFirst, m_ptSelSec))
	{
		return true;
	}
	return false;
}

