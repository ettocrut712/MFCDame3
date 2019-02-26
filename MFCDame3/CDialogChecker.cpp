#include "stdafx.h"
#include "CDialogChecker.h"


CDialogChecker::CDialogChecker()
{
}


CDialogChecker::~CDialogChecker()
{
}
BEGIN_MESSAGE_MAP(CDialogChecker, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CDialogChecker::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialog::OnPaint() for painting messages
	

	int x, y;
	CGrid::pion pion;

	COLORREF couleur;
	couleur = (100, 255, 0);
	int unsigned sizeVect_ordi, sizeVect_humain;
	//CClientDC dc(this);
	CBrush brosse_ordi, brosse_humain;

	brosse_ordi.CreateSolidBrush(RGB(255, 0, 0));
	brosse_humain.CreateSolidBrush(RGB(0, 0, 0));

	CPoint p1;

	int unsigned ID;

	int hauteur = 400;
	int largeur = hauteur;
	int origine_x = 50;
	int origine_y = 50;
	int left, right, upper, lower;

	p1.x = origine_x;
	p1.y = origine_y;
	dc.MoveTo(p1.x, p1.y);

	

	// Dessine grille de jeu

	for (x = origine_x; x <= origine_x + largeur; x = x + largeur/10)
	{

		p1.x = x;
		p1.y = origine_y;
		dc.MoveTo(p1.x, p1.y);
		p1.y = origine_y + hauteur;
		dc.LineTo(p1.x, p1.y);
	};

	for (y = origine_y; y <= origine_y + hauteur; y = y + hauteur/10)
	{
		p1.x = origine_x;
		p1.y = y;
		dc.MoveTo(p1.x, p1.y);
		p1.x = origine_x + largeur;
		dc.LineTo(p1.x, p1.y);

	};

	sizeVect_ordi = m_vector_grid_ordi.size();
	dc.SelectObject(brosse_ordi);

	for (ID = 0; ID < sizeVect_ordi; ID++)
	{
		pion = m_vector_grid_ordi.at(ID);
		left = origine_x + largeur / 10 * pion.actual_x;
		right = origine_x + largeur / 10 * (pion.actual_x + 1);
		upper = (origine_y + hauteur) - hauteur / 10 * (pion.actual_y + 1);
		lower = (origine_y + hauteur) - hauteur / 10 * pion.actual_y;

		dc.Ellipse(left, upper, right, lower);

	};

	sizeVect_humain = m_vector_grid_humain.size();
	dc.SelectObject(brosse_humain);
	for (ID = 0; ID < sizeVect_humain; ID++)
	{

		pion = m_vector_grid_humain.at(ID);
		left = origine_x + largeur / 10 * pion.actual_x;
		right = origine_x + largeur / 10 * (pion.actual_x + 1);
		upper = (origine_y + hauteur) - hauteur / 10 * (pion.actual_y + 1);
		lower = (origine_y + hauteur) - hauteur / 10 * pion.actual_y;

		dc.Ellipse(left, upper, right, lower);
	};


	


	




	
}




void CDialogChecker::TransferPionsToDisplay(std::vector <CGrid::pion>  vecteur_pion_humain, std::vector <CGrid::pion> vecteur_pion_ordi)
{
	
	m_vector_grid_ordi = vecteur_pion_ordi;
	m_vector_grid_humain =  vecteur_pion_humain;

}


