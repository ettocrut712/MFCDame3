
// MFCDame3Dlg.h : header file
//

#include "CGrid.h"
#pragma once


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

	afx_msg void OnClickedRetirePionButton();
	afx_msg void OnClickedCalculScoreInitialButton();
	afx_msg void OnClickedCalculScoreGridSubButton();
	CString m_ord_pion_jeu;
	CString m_Hum_Pion_Jeu;
	CString m_Ord_Pion_Grid;
	CString m_Hum_Pion_Grid;
	CString m_str_score_grid;
	afx_msg void OnBnClickedevaluemoveButton();
	afx_msg void OnBnClickedOrdiJoueButton();
	CGrid::pion CalculeMoveOrdi_max(CGrid::pion &pion, int niveau, int alpha, int beta);
	CGrid::pion  CalculeMoveHum_min(CGrid::pion &pion, int niveau, int alpha, int beta);
	CListBox m_listBox_move;
	void PrintGrid();
	void PrintScorePions();
};
