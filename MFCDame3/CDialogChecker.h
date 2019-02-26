#pragma once
#include <afxwin.h>
#include <vector>
#include "CGrid.h"


class CDialogChecker :
	public CDialog
{
public:
	CDialogChecker();
	~CDialogChecker();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();

	std::vector <CGrid::pion> m_vector_grid_ordi;
	std::vector <CGrid::pion> m_vector_grid_humain;

public:	void TransferPionsToDisplay(std::vector <CGrid::pion>  vecteur_pion_humain, std::vector <CGrid::pion> vecteur_pion_ordi);

};

