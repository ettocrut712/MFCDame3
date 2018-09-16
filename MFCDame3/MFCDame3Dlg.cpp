
// MFCDame3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCDame3.h"
#include "MFCDame3Dlg.h"
#include "afxdialogex.h"
#include <string>
#include <sstream>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCDame3Dlg dialog



CMFCDame3Dlg::CMFCDame3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCDAME3_DIALOG, pParent)
	, m_ord_pion_jeu(_T(""))
	, m_Hum_Pion_Jeu(_T(""))
	, m_Ord_Pion_Grid(_T(""))
	, m_Hum_Pion_Grid(_T(""))
	, m_str_score_grid(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDame3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SUIVI_JEU, m_ListBox_Suivi_Jeu);
	DDX_Text(pDX, IDC_Ord_Pion_Jeu, m_ord_pion_jeu);
	DDX_Text(pDX, IDC_Hum_Pion_Jeu, m_Hum_Pion_Jeu);
	DDX_Text(pDX, IDC_Ord_Pion_Grid, m_Ord_Pion_Grid);
	DDX_Text(pDX, IDC_Hum_Pion_Grid, m_Hum_Pion_Grid);
	DDX_Text(pDX, IDC_Score_Grid, m_str_score_grid);
}

BEGIN_MESSAGE_MAP(CMFCDame3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Init_BUTTON, &CMFCDame3Dlg::OnClickedInitButton)
	ON_BN_CLICKED(IDC_Reset_BUTTON, &CMFCDame3Dlg::OnClickedResetButton)
	ON_BN_CLICKED(IDC_retire_pion_BUTTON, &CMFCDame3Dlg::OnClickedRetirePionButton)
	ON_BN_CLICKED(IDC_calcul_score_initial_BUTTON, &CMFCDame3Dlg::OnClickedCalculScoreInitialButton)
	ON_BN_CLICKED(IDC_calcul_score_grid_sub_BUTTON, &CMFCDame3Dlg::OnClickedCalculScoreGridSubButton)
END_MESSAGE_MAP()


// CMFCDame3Dlg message handlers

BOOL CMFCDame3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here


	m_ord_pion_jeu = "0";
	m_Hum_Pion_Jeu = "0";
	m_Ord_Pion_Grid = "0";
	m_Hum_Pion_Grid = "0";
	m_str_score_grid = "0";
	UpdateData(FALSE);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCDame3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCDame3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCDame3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCDame3Dlg::OnClickedInitButton()
{
	// TODO: Add your control notification handler code here

	
	m_ListBox_Suivi_Jeu.InsertString(-1,_T("--------------"));
	m_ListBox_Suivi_Jeu.InsertString(-1,_T("Init Jeu"));

	GridJeu.CreatePionsOrdi();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Crée pions ordi"));

	GridJeu.CreatePionHumain();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Crée pions humain"));

	GridJeu.TransferTousPionToGrid();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Transfer pions vers grille de jeu"));

	GridJeu.ResetScorePions();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Reset score des pions"));

	GridJeu.CloneGrid();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Clone grid_main vers grid_sub"));


	int i=0;
	i = i + 1;

}


void CMFCDame3Dlg::OnClickedResetButton()
{
	// TODO: Add your control notification handler code here

	m_ListBox_Suivi_Jeu.InsertString(-1, _T("--------------"));
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Reset Jeu"));

	GridJeu.CreatePionsOrdi();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Crée pions ordi"));

	GridJeu.CreatePionHumain();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Crée pions humain"));

	GridJeu.ResetMainGrid();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Reset grid_main"));

	GridJeu.TransferTousPionToGrid();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Transfer pions vers grille de jeu"));

	GridJeu.ResetScorePions();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Reset score des pions"));

	GridJeu.CloneGrid();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Clone grid_main vers grid_sub"));

	int i = 0;
	i = i + 1;
}


void CMFCDame3Dlg::OnClickedRetirePionButton()
{
	// TODO: Add your control notification handler code here

	int i;
	CString leString;
	int main_sub;
	

	for (i = -20; i < 21; i++)
	{
		
		main_sub = 1;										// 0-> retire de main_grid, 1-> retire de grid_sub
		leString.Format(_T("retire pion grid_sub: %d"), i);
		m_ListBox_Suivi_Jeu.InsertString(-1, leString);
		GridJeu.RetirePionGrid(i, main_sub );
		OnClickedCalculScoreGridSubButton();
		OnClickedCalculScoreInitialButton();

	};

	for (i = -20; i < 21; i++)
	{
		
		main_sub = 0;										// 0-> retire de main_grid, 1-> retire de grid_sub
		leString.Format(_T("retire pion grid_main: %d"), i);
		m_ListBox_Suivi_Jeu.InsertString(-1, leString);
		GridJeu.RetirePionGrid(i, main_sub);
		OnClickedCalculScoreGridSubButton();
		OnClickedCalculScoreInitialButton();

	};

	for (i = -20; i < 21; i++)
	{
		int main_sub;
		main_sub = 1;										// 0-> retire de main_grid, 1-> retire de grid_sub
		leString.Format(_T("retire pion du jeu: %d"), i);
		m_ListBox_Suivi_Jeu.InsertString(-1, leString);
		GridJeu.RetirePionJeu(i);
		OnClickedCalculScoreGridSubButton();
		OnClickedCalculScoreInitialButton();
	};

	
	
	
	

}


void CMFCDame3Dlg::OnClickedCalculScoreInitialButton()
{
	// TODO: Add your control notification handler code here



	CString leString;

	GridJeu.CalculScoreInitial();

	int temp = GridJeu.GetScoreInitialOrdi();

	leString.Format(_T("Score_initial ordi: %d"), temp);
	m_ListBox_Suivi_Jeu.InsertString(-1, leString);

	m_ord_pion_jeu.Format(_T("%d"), temp);

	temp = GridJeu.GetScoreInitialHum();
	leString.Format(_T("Score_initial Hum: %d"), temp);
	m_ListBox_Suivi_Jeu.InsertString(-1, leString);

	m_Hum_Pion_Jeu.Format(_T("%d"), temp);

	UpdateData(FALSE);

}


void CMFCDame3Dlg::OnClickedCalculScoreGridSubButton()
{
	// TODO: Add your control notification handler code here

	int temp;
	int score_grid;
	CString leString;
	
	GridJeu.CalculScoreGrid();

	temp = GridJeu.GetScoreGridOrdi();
	leString.Format(_T("Score_grid ordi: %d"), temp);
	m_ListBox_Suivi_Jeu.InsertString(-1, leString);
	
	
	m_Ord_Pion_Grid.Format(_T("%d"), temp);


	temp = GridJeu.GetScoreGridHum();
	leString.Format(_T("Score_grid hum: %d"), temp);
	m_ListBox_Suivi_Jeu.InsertString(-1, leString);
	
	m_Hum_Pion_Grid.Format(_T("%d"), temp);


	score_grid = (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum()) - (GridJeu.GetScoreGridOrdi() - GridJeu.GetScoreInitialOrdi());
	m_str_score_grid.Format(_T("%d"), score_grid);


	UpdateData(FALSE);

}
