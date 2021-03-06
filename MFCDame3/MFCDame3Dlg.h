
// MFCDame3Dlg.h : header file
//

#include "CGrid.h"

#pragma once



class CnewDialogChecker :
	public CDialog
{
public:
	CnewDialogChecker();
	~CnewDialogChecker();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();

	std::vector <CGrid::pion> m_vector_grid_ordi;
	std::vector <CGrid::pion> m_vector_grid_humain;

public:	void TransferPionsToDisplay(std::vector <CGrid::pion>  vecteur_pion_humain, std::vector <CGrid::pion> vecteur_pion_ordi);

		//************************** nouveau code ******
		
		bool m_HumainBouge = false;

		//**********************************************

		afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		int m_origine_X;
		int m_origine_Y;
		int m_destination_X;
		int m_destination_Y;
		int m_case_origine_x, m_case_origine_y, m_case_destination_x, m_case_destination_y;
		

		int hauteur = 400;
		int largeur = hauteur;
		int grid_origine_x = 50;
		int grid_origine_y = 50;

		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};




// CMFCDame3Dlg dialog
class CMFCDame3Dlg : public CDialogEx
{
// Construction
public:
	CMFCDame3Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDAME3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListBox_Suivi_Jeu;
	afx_msg void OnClickedInitButton();
	afx_msg void OnClickedResetButton();

	CGrid GridJeu;


	afx_msg void OnClickedCalculScoreInitialButton();
	afx_msg void OnClickedComptePionsGridSubButton();
	CString m_ord_pion_jeu;
	CString m_Hum_Pion_Jeu;
//	CString m_Ord_Pion_Grid;
//	CString m_Hum_Pion_Grid;
	CString m_str_score_grid;
	afx_msg void OnBnClickedEvalueMoveButton();
	afx_msg void OnBnClickedOrdiJoueButton();


	CGrid::pion CalculeMove_max(CGrid::pion &pion_max, int niveau, int alpha, int beta, CGrid::pion &pion_min);
	CGrid::pion CalculeMove_max2(CGrid::pion &pion_max, int niveau, int alpha, int beta, CGrid::pion &pion_min);
	CGrid::pion CalculeMove_min(CGrid::pion &pion_max, int niveau, int alpha, int beta, CGrid::pion &pion_min);
	void CheckDoublon();

	CListBox m_listBox_move;
	int m_number_of_moves, m_number_of_pions_moved;
	int PaintGrid_graphic();
	int m_ctrl_move_start_tracking;

	void PrintGrid();
	void PrintScorePions();
	afx_msg void OnBnClickedHumainJoueButton();
	
	// int m_str_MaxNiveau;// int m_str_MaxNiveau;
	
	BOOL m_BOOL_DessineGrid;
	bool dessineGrid;
	
	afx_msg void OnBnClickedUptNiveau();
	afx_msg void OnStnClickedStaticPionId();
	afx_msg void OnBnClickedBoutonJoue();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	CString m_pion_max_ID;
	CString m_pion_max_move;
	CString m_pion_min_ID;
	CString m_pion_min_move;
	
	CString m_pion_max_ID_niv_3;
	CString m_pion_min_ID_niv_4;
	CString m_pion_max_move_niv_3;
	CString m_pion_min_move_niv_4;
	CString m_nbre_coups;
	
	CString m_souris_x;
	CString m_souris_y;
	CString m_STR_nbre_pion_selection_finale;
	CString m_str_MaxNiveau;
	CString m_str_moves_total;
	CString m_str_pion_moved;

	//***************code Timer** 

	CString m_Time2;


	//****************************

	afx_msg void OnBnClickedBtnTrouveBestPion();
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	//**************************nouveau code ******************

	CnewDialogChecker m_dlgChecker;

	


	//*************************************************************

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_sTime2;
	afx_msg void OnStnClickedOrdPionGrid();
	CString m_Hum_Pion_Grid;
	CString m_Ord_Pion_Grid;
};




