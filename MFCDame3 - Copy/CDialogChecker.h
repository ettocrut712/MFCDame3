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

		afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		int m_origine_X;
		int m_origine_Y;
		int m_destination_X;
		int m_destination_Y;
		int hauteur = 400;
		int largeur = hauteur;
		int grid_origine_x = 50;
		int grid_origine_y = 50;

		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

