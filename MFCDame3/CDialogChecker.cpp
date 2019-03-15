#include "stdafx.h"
#include "CDialogChecker.h"


CDialogChecker::CDialogChecker()
{
	m_origine_X = 0;
	m_origine_Y = 0;
	m_destination_X = 0;
	m_destination_Y = 0;
}


CDialogChecker::~CDialogChecker()
{
}
BEGIN_MESSAGE_MAP(CDialogChecker, CDialog)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


void CDialogChecker::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialog::OnPaint() for painting messages
	
	CString le_string;
	CRect le_rectangle;

	int x, y;
	CGrid::pion pion;

	COLORREF couleur;
	couleur = (100, 255, 0);
	int unsigned sizeVect_ordi, sizeVect_humain;
	//CClientDC dc(this);
	CBrush brosse_ordi, brosse_humain;
	

	brosse_ordi.CreateSolidBrush(RGB(255, 0, 0));		// rouge
	brosse_humain.CreateSolidBrush(RGB(0, 0, 0));		// noir
	
	CPen crayon_noir, crayon_blanc;
	crayon_noir.CreatePen(PS_SOLID, 1,RGB(0,0,0));  // noir
	crayon_blanc.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));  //blanc
	
	CPoint p1;

	int unsigned ID;

	
	int left, right, upper, lower;

	p1.x = grid_origine_x;
	p1.y = grid_origine_y;
	dc.MoveTo(p1.x, p1.y);

	

	// Dessine grille de jeu

	for (x = grid_origine_x; x <= grid_origine_x + largeur; x = x + largeur/10)
	{

		p1.x = x;
		p1.y = grid_origine_y;
		dc.MoveTo(p1.x, p1.y);
		p1.y = grid_origine_y + hauteur;
		dc.LineTo(p1.x, p1.y);
	};

	for (y = grid_origine_y; y <= grid_origine_y + hauteur; y = y + hauteur/10)
	{
		p1.x = grid_origine_x;
		p1.y = y;
		dc.MoveTo(p1.x, p1.y);
		p1.x = grid_origine_x + largeur;
		dc.LineTo(p1.x, p1.y);

	};

	sizeVect_ordi = m_vector_grid_ordi.size();
	dc.SelectObject(brosse_ordi);

	for (ID = 0; ID < sizeVect_ordi; ID++)
	{
		pion = m_vector_grid_ordi.at(ID);
		left = grid_origine_x + largeur / 10 * pion.actual_x;
		right = grid_origine_x + largeur / 10 * (pion.actual_x + 1);
		upper = (grid_origine_y + hauteur) - hauteur / 10 * (pion.actual_y + 1);
		lower = (grid_origine_y + hauteur) - hauteur / 10 * pion.actual_y;

		dc.Ellipse(left, upper, right, lower);
		dc.SelectObject(crayon_blanc);
		//dc.MoveTo(left, lower);
		
		le_rectangle.SetRect(left, upper+hauteur/40, right, lower);

		le_string.Format(_T("%2d"), pion.ID);
		dc.DrawText(le_string, le_rectangle, DT_CENTER);

	};

	sizeVect_humain = m_vector_grid_humain.size();
	dc.SelectObject(brosse_humain);
	for (ID = 0; ID < sizeVect_humain; ID++)
	{

		pion = m_vector_grid_humain.at(ID);
		left = grid_origine_x + largeur / 10 * pion.actual_x;
		right = grid_origine_x + largeur / 10 * (pion.actual_x + 1);
		upper = (grid_origine_y + hauteur) - hauteur / 10 * (pion.actual_y + 1);
		lower = (grid_origine_y + hauteur) - hauteur / 10 * pion.actual_y;

		dc.Ellipse(left, upper, right, lower);

		dc.SelectObject(crayon_blanc);
		//dc.MoveTo(left, lower);

		le_rectangle.SetRect(left, upper + hauteur / 40, right, lower);

		le_string.Format(_T("%2d"), pion.ID);
		dc.DrawText(le_string, le_rectangle, DT_CENTER);
	};

	dc.SelectObject(crayon_noir);

	dc.MoveTo(m_origine_X, m_origine_Y);
	dc.LineTo(m_destination_X, m_destination_Y);
}




void CDialogChecker::TransferPionsToDisplay(std::vector <CGrid::pion>  vecteur_pion_humain, std::vector <CGrid::pion> vecteur_pion_ordi)
{
	
	m_vector_grid_ordi = vecteur_pion_ordi;
	m_vector_grid_humain =  vecteur_pion_humain;

}




void CDialogChecker::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default


	if ((nFlags & MK_LBUTTON) == MK_LBUTTON)
	{

		CClientDC dc(this);
		Invalidate();

		m_destination_X = point.x;
		m_destination_Y = point.y;

		dc.SetPixel(point.x, point.y, RGB(0, 0, 0));

		dc.MoveTo(m_origine_X, m_origine_Y);
		dc.LineTo(point.x, point.y);
	};
	CDialog::OnMouseMove(nFlags, point);
}


void CDialogChecker::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	int case_origine_x, case_origine_y;

	m_origine_X = point.x;
	m_origine_Y = point.y;

	case_origine_x = (m_destination_X - grid_origine_x) / (hauteur / 10);
	case_origine_y = 9 - (m_destination_Y - grid_origine_y) / (largeur / 10);

	CDialog::OnLButtonDown(nFlags, point);
}


void CDialogChecker::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	int case_destination_x, case_destination_y;

	m_destination_X = point.x;
	m_destination_Y = point.y;
	
	case_destination_x = (m_destination_X - grid_origine_x) / (hauteur/10);
	case_destination_y = 9-(m_destination_Y - grid_origine_y) / (largeur/10);


	CDialog::OnLButtonUp(nFlags, point);
}
