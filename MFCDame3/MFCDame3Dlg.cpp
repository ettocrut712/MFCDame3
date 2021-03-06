
// MFCDame3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCDame3.h"
#include "MFCDame3Dlg.h"
#include "afxdialogex.h"
#include <string>
#include <sstream>
#include <time.h>






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
	//, m_Ord_Pion_Grid(_T(""))
//	, m_Hum_Pion_Grid(_T(""))
	, m_str_score_grid(_T(""))
	, m_str_moves_total(_T(""))
	, m_str_pion_moved(_T(""))
	//, m_str_MaxNiveau(0)
	, m_str_MaxNiveau(_T(""))
	, m_BOOL_DessineGrid(FALSE)
	//, m_move_debug_NT(_T(""))
	, m_ctrl_move_start_tracking(0)
	, m_pion_max_ID(_T(""))
	, m_pion_max_move(_T(""))
	, m_pion_min_ID(_T(""))
	, m_pion_min_move(_T(""))
	, m_pion_max_ID_niv_3(_T(""))
	, m_pion_min_ID_niv_4(_T(""))
	, m_pion_max_move_niv_3(_T(""))
	, m_pion_min_move_niv_4(_T(""))
	, m_nbre_coups(_T(""))
	, m_souris_x(_T(""))
	, m_souris_y(_T(""))
	, m_STR_nbre_pion_selection_finale(_T(""))
	, m_sTime2(_T(""))
	, m_Hum_Pion_Grid(_T(""))
	, m_Ord_Pion_Grid(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDame3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SUIVI_JEU, m_ListBox_Suivi_Jeu);
	DDX_Text(pDX, IDC_Ord_Pion_Jeu, m_ord_pion_jeu);
	DDX_Text(pDX, IDC_Hum_Pion_Jeu, m_Hum_Pion_Jeu);
	//	DDX_Text(pDX, IDC_Ord_Pion_Grid, m_Ord_Pion_Grid);
	//	DDX_Text(pDX, IDC_Hum_Pion_Grid, m_Hum_Pion_Grid);
	DDX_Text(pDX, IDC_Score_Grid, m_str_score_grid);
	DDX_Control(pDX, IDC_MOVE_LIST, m_listBox_move);
	DDX_Text(pDX, IDC_moves_total, m_str_moves_total);
	DDX_Text(pDX, IDC_PION_MOVED, m_str_pion_moved);
	//  DDX_Text(pDX, IDC_MAX_NIVEAU, m_str_MaxNiveau);
	DDX_Text(pDX, IDC_MAX_NIVEAU, m_str_MaxNiveau);
	DDX_Check(pDX, IDC_DRAW_GRID, m_BOOL_DessineGrid);
	//  DDX_Text(pDX, IDC_MOVE_DEBUG_NT, m_move_debug_NT);
	//  DDX_Text(pDX, IDC_MOVE_DEBUG_NT, m_move_start_tracking);
	DDX_Text(pDX, IDC_MOVE_DEBUG_NT, m_ctrl_move_start_tracking);
	//  DDX_Text(pDX, IDC_STATIC_pion_max, m_pion_max_ID);
	//  DDX_Text(pDX, IDC_pion_max_move, m_pion_min_move);
	DDX_Text(pDX, IDC_pion_min_ID, m_pion_min_ID);
	//  DDX_Text(pDX, IDC_pion_min_move, m_pion_min_move);
	DDX_Text(pDX, IDC_pion_max_move, m_pion_max_move);
	DDX_Text(pDX, IDC_STATIC_pion_max_ID, m_pion_max_ID);
	DDX_Text(pDX, IDC_pion_max_move, m_pion_max_move);
	DDX_Text(pDX, IDC_pion_min_ID, m_pion_min_ID);
	DDX_Text(pDX, IDC_pion_min_move, m_pion_min_move);
	DDX_Text(pDX, IDC_STATIC_Pion_max_ID_niveau_3, m_pion_max_ID_niv_3);
	DDX_Text(pDX, IDC_STATIC_pion_min_ID_niveau_4, m_pion_min_ID_niv_4);
	DDX_Text(pDX, IDC_pion_max_move_niveau_3, m_pion_max_move_niv_3);
	DDX_Text(pDX, IDC_pion_min_move_niveau_4, m_pion_min_move_niv_4);
	DDX_Text(pDX, IDC_NOMBRE_DE_COUPS, m_nbre_coups);
	DDX_Text(pDX, IDC_SOURIS_X, m_souris_x);
	DDX_Text(pDX, IDC_SOURIS_Y, m_souris_y);
	DDX_Text(pDX, IDC_PION_SELECTION_FINALE, m_STR_nbre_pion_selection_finale);
	DDX_Text(pDX, IDC_STATIC_TIME, m_sTime2);
	DDX_Text(pDX, IDC_Hum_Pion_Grid, m_Hum_Pion_Grid);
	DDX_Text(pDX, IDC_Ord_Pion_Grid, m_Ord_Pion_Grid);
}

BEGIN_MESSAGE_MAP(CMFCDame3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Init_BUTTON, &CMFCDame3Dlg::OnClickedInitButton)
	ON_BN_CLICKED(IDC_Reset_BUTTON, &CMFCDame3Dlg::OnClickedResetButton)
	ON_BN_CLICKED(IDC_calcul_score_initial_BUTTON, &CMFCDame3Dlg::OnClickedCalculScoreInitialButton)
	ON_BN_CLICKED(IDC_calcul_score_grid_sub_BUTTON, &CMFCDame3Dlg::OnClickedComptePionsGridSubButton)
	ON_BN_CLICKED(IDC_evalueMove_BUTTON, &CMFCDame3Dlg::OnBnClickedEvalueMoveButton)
	ON_BN_CLICKED(IDC_ORDI_JOUE_BUTTON, &CMFCDame3Dlg::OnBnClickedOrdiJoueButton)
	ON_BN_CLICKED(IDC_HUMAIN_JOUE_BUTTON, &CMFCDame3Dlg::OnBnClickedHumainJoueButton)
	ON_BN_CLICKED(IDC_UPT_NIVEAU, &CMFCDame3Dlg::OnBnClickedUptNiveau)
	ON_STN_CLICKED(IDC_STATIC_PION_ID, &CMFCDame3Dlg::OnStnClickedStaticPionId)
	ON_BN_CLICKED(IDC_BOUTON_JOUE, &CMFCDame3Dlg::OnBnClickedBoutonJoue)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BTN_TROUVE_BEST_PION, &CMFCDame3Dlg::OnBnClickedBtnTrouveBestPion)
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_Ord_Pion_Grid, &CMFCDame3Dlg::OnStnClickedOrdPionGrid)
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
	//m_Ord_Pion_Grid = "0";
	//m_Hum_Pion_Grid = "0";
	m_str_score_grid = "0";
	m_str_moves_total="0";
	m_str_pion_moved ="0";
	GridJeu.m_nbre_pion_meilleurs = 7;
	m_STR_nbre_pion_selection_finale = "7";

	

	m_dlgChecker.Create(IDD_CHECKER_DIALOG, this);
	m_dlgChecker.ShowWindow(SW_SHOW);
	
	//****************nouveau code
	
	SetTimer(ID_CLOCK_TIMER,500, NULL);

	//****************************



	OnClickedInitButton();
	UpdateData(FALSE);

	m_dlgChecker.TransferPionsToDisplay(GridJeu.pion_vector_grid_humain, GridJeu.pion_vector_grid_ordi);
	m_dlgChecker.Invalidate();

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
	
	CString leString;
	dessineGrid = false;

	UpdateData(TRUE);
	
	m_number_of_moves = 0;
	m_number_of_pions_moved = 0;
	m_BOOL_DessineGrid = false;
	m_str_moves_total.Format(_T("%d"), m_number_of_moves);
	m_str_pion_moved.Format(_T("%d"), m_number_of_pions_moved);
	m_str_MaxNiveau.Format(_T("%d"),GridJeu.max_niveau);
	m_STR_nbre_pion_selection_finale.Format(_T("%d"), GridJeu.m_nbre_pion_meilleurs);

	
	
	leString.Format(_T("ctrl start tracking: %d"), m_ctrl_move_start_tracking);
	m_ListBox_Suivi_Jeu.InsertString(-1, leString);					// insere une ligne vide pour affichage plus facilement lisible.	

	UpdateData(FALSE);

	UpdateWindow();

	//GridJeu.max_niveau.Format("%d", m_str_MaxNiveau);

	
	m_ListBox_Suivi_Jeu.InsertString(-1,_T("--------------"));
	m_ListBox_Suivi_Jeu.InsertString(-1,_T("Init Jeu"));

	GridJeu.CreatePionsOrdi();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Crée pions ordi"));

	GridJeu.CreatePionHumain();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Crée pions humain"));

	GridJeu.TransferTousPionToMainGrid();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Transfer pions vers grille de jeu"));

	
	GridJeu.CloneGridMainToSub();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Clone grid_main vers grid_sub"));

	GridJeu.ResetScorePions();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Reset points des pions"));

	OnClickedCalculScoreInitialButton();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Calcul du pointage initial (nombre de pions de chaque joueur)"));

	OnClickedComptePionsGridSubButton();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Calcule le pointage de la grille grid_sub "));


	GridJeu.ResetPionVectorGrid();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Reset vecteur de pion de la grille de jeu"));

	PrintGrid();
	UpdateWindow();

}


void CMFCDame3Dlg::OnClickedResetButton()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	GridJeu.max_niveau = _ttoi(m_str_MaxNiveau);



	m_ListBox_Suivi_Jeu.ResetContent();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Reset de la liste de suivi du jeu"));

	m_listBox_move.ResetContent();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Reset de la liste des calculs de mouvement"));

	m_ListBox_Suivi_Jeu.InsertString(-1, _T("--------------"));
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Reset Jeu"));

	OnClickedInitButton();

	m_dlgChecker.TransferPionsToDisplay(GridJeu.pion_vector_grid_humain, GridJeu.pion_vector_grid_ordi);
	m_dlgChecker.Invalidate();

}





void CMFCDame3Dlg::OnClickedCalculScoreInitialButton()
{
	// TODO: Add your control notification handler code here



	CString leString;

	GridJeu.CalculScoreInitial();

	int temp = GridJeu.GetScoreInitialOrdi();

	leString.Format(_T("pointage_initial ordi: %d"), temp);
	m_ListBox_Suivi_Jeu.InsertString(-1, leString);

	m_ord_pion_jeu.Format(_T("%d"), temp);

	temp = GridJeu.GetScoreInitialHum();
	leString.Format(_T("pointage_initial Hum: %d"), temp);
	m_ListBox_Suivi_Jeu.InsertString(-1, leString);

	m_Hum_Pion_Jeu.Format(_T("%d"), temp);

	UpdateData(FALSE);

}


void CMFCDame3Dlg::OnClickedComptePionsGridSubButton()
{
	// TODO: Add your control notification handler code here

	int temp;
	int score_grid;
	CString leString;
	
	GridJeu.ComptePionsGrid();

	temp = GridJeu.GetScoreGridOrdi();
	leString.Format(_T("pointage_grid ordi: %d"), temp);
	m_ListBox_Suivi_Jeu.InsertString(-1, leString);
	
	
	//m_Ord_Pion_Grid.Format(_T("%d"), temp);


	temp = GridJeu.GetScoreGridHum();
	leString.Format(_T("pointage_grid hum: %d"), temp);
	m_ListBox_Suivi_Jeu.InsertString(-1, leString);
	
	//m_Hum_Pion_Grid.Format(_T("%d"), temp);


	score_grid = (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum()) - (GridJeu.GetScoreGridOrdi() - GridJeu.GetScoreInitialOrdi());
	m_str_score_grid.Format(_T("%d"), score_grid);


	UpdateData(FALSE);

}


void CMFCDame3Dlg::OnBnClickedEvalueMoveButton()
{
	// TODO: Add your control notification handler code here
	int pionID;
	
	CGrid::pion m_pion_evalue1, m_pion_evalue2, minimax_pion, pion;

	int niveau = 0;
	
	int sizeVect;

	int score = 0;

	CString leString;
	

	int alpha = -1000;
	int beta = 1000;


	auto pGrid = &CGrid::grid_sub;

	m_ListBox_Suivi_Jeu.ResetContent();

	
	//***************************************
	
	int le_niveau = 0;
	
	GridJeu.CalculScoreInitial();										// calcule le nombre de joueurs de chaque équipe avant de faire les analyses de mouvement.  Score = (# joueurs ennemi initial - # joeurs ennemi final) - (# joueurs ami initial - # joeurs ami final)

	sizeVect = GridJeu.GetPionVectHumSize();

	GridJeu.ResetScorePions();

		for (pionID = 0; pionID < sizeVect; pionID++)							//Pour tous les pions qui sont encore dans le jeu, calculer le meilleur pion à bouger.
		{
			m_pion_evalue1 = GridJeu.GetPionFromVectHumain(pionID);				//Obtient un pion du vecteur	


			minimax_pion = CalculeMove_max(m_pion_evalue1, le_niveau, alpha, beta, m_pion_evalue2);	
																				// minimax_pion est le résultat de l'évaluation complétée pour les mouvements de ce pion.

			leString.Format(_T("Pion: %3d   move: %3d   points: %3d   "), m_pion_evalue1.ID, minimax_pion.move, minimax_pion.score);
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);
			
			minimax_pion.ID = m_pion_evalue1.ID;
																				
			GridJeu.SetPionScore(minimax_pion);
			
			

		};


		sizeVect = GridJeu.GetPionVectOrdiSize();

		for (pionID = 0; pionID < sizeVect; pionID++)							//Pour tous les pions qui sont encore dans le jeu, calculer le meilleur pion à bouger.
		{
			m_pion_evalue1 = GridJeu.GetPionFromVectOrdi(pionID);				//Obtient un pion du vecteur	


			minimax_pion = CalculeMove_max(m_pion_evalue1, le_niveau, alpha, beta, m_pion_evalue2);
			// minimax_pion est le résultat de l'évaluation complétée pour les mouvements de ce pion.

			
			leString.Format(_T("Pion: %3d   move: %3d   points: %3d   "), m_pion_evalue1.ID, minimax_pion.move, minimax_pion.score);
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);

			minimax_pion.ID = m_pion_evalue1.ID;

			GridJeu.SetPionScore(minimax_pion);
			

		};  // FIN : for (pionID = 0; pionID < sizeVect; pionID++)
	
	

	//**************************************

	


};


void CMFCDame3Dlg::OnBnClickedOrdiJoueButton()
{
	// TODO: Add your control notification handler code here

	int pionID, score;
	CGrid::pion pion_ordi, my_pion_min, minimax_pion;
	int actual_x, actual_y;

	int le_niveau = 0;
	
	int sizeVect;
	CString leString;

	sizeVect = GridJeu.GetPionVectOrdiSize();

	GridJeu.ResetScorePions();

	int alpha = -1000;
	int beta = 1000;
	
	
	UpdateData(TRUE);
	GridJeu.max_niveau = _ttoi(m_str_MaxNiveau);
	m_number_of_moves = 0;
	m_number_of_pions_moved = 0;
	m_str_moves_total.Format(_T("%d"), m_number_of_moves);
	m_str_pion_moved.Format(_T("%d"), m_number_of_pions_moved);
	m_str_MaxNiveau.Format(_T("%d"), GridJeu.max_niveau);
	m_ListBox_Suivi_Jeu.ResetContent();
	
	leString.Format(_T("ctrl start tracking: %d"), m_ctrl_move_start_tracking);
	m_ListBox_Suivi_Jeu.InsertString(-1, leString);

	UpdateData(FALSE);

	dessineGrid = false;

	if ((m_number_of_moves > m_ctrl_move_start_tracking) && m_BOOL_DessineGrid)
	{

		dessineGrid = true;
		PrintGrid();
		UpdateWindow();

	};

	if (dessineGrid)
	{
		
		leString.Format(_T("1-OnClickButton Début analyse ordi"));

		m_listBox_move.InsertString(-1, leString);

		leString.Format(_T("2-OnBnClickedOrdiJoueButton: config initiale"));
		m_listBox_move.InsertString(-1, leString);

		PrintGrid();
		UpdateWindow();
	};

	
	GridJeu.CalculScoreInitial();										// calcule le nombre de joueurs de chaque équipe avant de faire les analyses de mouvement.  Score = (# joueurs ennemi initial - # joeurs ennemi final) - (# joueurs ami initial - # joeurs ami final)
	
	if (GridJeu.pion_vector_ordi.size() > 0 && GridJeu.pion_vector_humain.size() >0)
	{

		
	
		for (pionID = 0; pionID < sizeVect; pionID++)						//Pour tous les pions qui sont encore dans le jeu, calculer le meilleur pion à bouger.
		{
			pion_ordi = GridJeu.GetPionFromVectOrdi(pionID);				//Obtient un pion du vecteur	


			minimax_pion = CalculeMove_max(pion_ordi, le_niveau, alpha, beta, my_pion_min);	// minimax_pion est le résultat de l'évaluation complétée pour les mouvements de ce pion.
		
			pion_ordi.score = minimax_pion.score;
			pion_ordi.move = minimax_pion.move;								
		
			GridJeu.SetPionScore(pion_ordi);

			//***************************** DEBUG***********************
			if (m_number_of_pions_moved > m_number_of_moves)
			{
				UpdateWindow();
			};

			//*********************************************************
			// Une fois tous les pions évalués.  On choisit le meilleur pion à bouger
		

		};  // FIN : for (pionID = 0; pionID < sizeVect; pionID++)
	
		
		pion_ordi = GridJeu.TrouveBestPionOrdi();


		if (pion_ordi.ID == -100)					// ID = -1 indique qu'aucun pion n'a pu bouger...
		{
			m_listBox_move.ResetContent();
			leString.Format(_T("ECHEC: NE PEUT TROUVER DE PION QUI PUISSE BOUGER "));
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);					// insere une ligne vide pour affichage plus facilement lisible.
			m_listBox_move.InsertString(-1, leString);
		}

	
		else

		{
			m_listBox_move.ResetContent();
			leString.Format(_T("Avant"));
			m_listBox_move.InsertString(-1, leString);
			PrintGrid();

			actual_x = pion_ordi.actual_x;
			actual_y = pion_ordi.actual_y;



			if (GridJeu.MovePion(pion_ordi, GridJeu.delta_x, GridJeu.delta_y, pion_ordi.move))
			{

			
			score = GridJeu.GetPionScore(pion_ordi);
			leString.Format(_T("Déplacement de pion: %d  réussi.  points: %d"), pion_ordi.ID, score);
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);					// insere une ligne vide pour affichage plus facilement lisible.																										
			m_listBox_move.InsertString(-1, leString);

			leString.Format(_T("Déplace de case (x,y) %d,%d   à  case (x,y) %d, %d"), actual_x, actual_y, pion_ordi.new_x, pion_ordi.new_y);
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);
			}
			else
			{
			leString.Format(_T("ECHEC: Déplacement de pion: %d "), pion_ordi.ID);
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);					// insere une ligne vide pour affichage plus facilement lisible.
			m_listBox_move.InsertString(-1, leString);
			};

			GridJeu.TransferTousPionToMainGrid();
			GridJeu.CloneGridMainToSub();
			OnClickedCalculScoreInitialButton();

			leString.Format(_T("Après"));
			m_listBox_move.InsertString(-1, leString);
		}
	}
	else  // ELSE de:  if (GridJeu.pion_vector_ordi.size() > 0 && GridJeu.pion_vector_humain.size() >0)
	{
		m_listBox_move.ResetContent();
		leString.Format(_T("ERREUR: UN DES DEUX JOUEURS N'A PLUS DE PIONS "));
		m_ListBox_Suivi_Jeu.InsertString(-1, leString);					// insere une ligne vide pour affichage plus facilement lisible.
		m_listBox_move.InsertString(-1, leString);

	};
	m_dlgChecker.TransferPionsToDisplay(GridJeu.pion_vector_grid_humain, GridJeu.pion_vector_grid_ordi);
	m_dlgChecker.Invalidate();


		PrintGrid();
		UpdateWindow();
	
};


void CMFCDame3Dlg::OnBnClickedHumainJoueButton()
{
	// TODO: Add your control notification handler code here

	int pionID, score;
	CGrid::pion pion_humain, my_pion_min, minimax_pion;


	int le_niveau = 0;

	int sizeVect;
	CString leString;

	sizeVect = GridJeu.GetPionVectHumSize();

	GridJeu.ResetScorePions();

	int alpha = -1000;
	int beta = 1000;
	
	
	UpdateData(TRUE);
	GridJeu.max_niveau = _ttoi(m_str_MaxNiveau);


	m_number_of_moves = 0;
	m_number_of_pions_moved = 0;

	m_str_moves_total.Format(_T("%d"), m_number_of_moves);
	m_str_pion_moved.Format(_T("%d"), m_number_of_pions_moved);
	m_str_MaxNiveau.Format(_T("%d"), GridJeu.max_niveau);
	
	m_ListBox_Suivi_Jeu.ResetContent();
	leString.Format(_T("ctrl start tracking: %d"), m_ctrl_move_start_tracking);
	m_ListBox_Suivi_Jeu.InsertString(-1, leString);

	UpdateData(FALSE);

	dessineGrid = false;
	

	if ((m_number_of_moves > m_ctrl_move_start_tracking) && m_BOOL_DessineGrid)
	{

		dessineGrid = true;
		PrintGrid();
		UpdateWindow();

	};
	
	leString.Format(_T("1-OnClickButton Début analyse humain"));
	m_ListBox_Suivi_Jeu.InsertString(-1, leString);

	GridJeu.CalculScoreInitial();											// calcule le nombre de joueurs de chaque équipe avant de faire les analyses de mouvement.  Score = (# joueurs ennemi initial - # joeurs ennemi final) - (# joueurs ami initial - # joeurs ami final)


	if (GridJeu.pion_vector_ordi.size() > 0 && GridJeu.pion_vector_humain.size() > 0)
	{

		for (pionID = 0; pionID < sizeVect; pionID++)
		{
			pion_humain = GridJeu.GetPionFromVectHumain(pionID);				//retourne le pion "humain" pion(pionID)

			minimax_pion = CalculeMove_max(pion_humain, le_niveau, alpha, beta, my_pion_min);	// minimax_pion est le résultat de l'évaluation complétée pour les mouvements de ce pion.

			pion_humain.score = minimax_pion.score;
			pion_humain.move = minimax_pion.move;


			GridJeu.SetPionScore(pion_humain);
			// on met à jour le score pour ce pion

		}; // FIN: for (pionID = 0; pionID < sizeVect; pionID++)


		pion_humain = GridJeu.TrouveBestPionHumain();

		if (pion_humain.ID == -100)					// ID = -1 indique qu<aucun pion n<a pu bouger...
		{
			m_listBox_move.ResetContent();
			leString.Format(_T("ECHEC: NE PEUT TROUVER DE PION QUI PUISSE BOUGER "));
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);					// insere une ligne vide pour affichage plus facilement lisible.
			m_listBox_move.InsertString(-1, leString);
		}

		else
		{

			m_listBox_move.ResetContent();
			leString.Format(_T("Avant"));
			m_listBox_move.InsertString(-1, leString);
			PrintGrid();

			if (GridJeu.MovePion(pion_humain, GridJeu.delta_x, GridJeu.delta_y, pion_humain.move))
			{
				score = GridJeu.GetPionScore(pion_humain);
				leString.Format(_T("Déplacement de pion: %d  réussi.  point: %d "), pion_humain.ID, score);
				m_ListBox_Suivi_Jeu.InsertString(1, leString);					// insere une ligne vide pour affichage plus facilement lisible.																										
				m_listBox_move.InsertString(-1, leString);
			}

			else

			{
				leString.Format(_T("ECHEC: Déplacement de pion: %d "), pion_humain.ID);
				m_ListBox_Suivi_Jeu.InsertString(1, leString);					// insere une ligne vide pour affichage plus facilement lisible.
				m_listBox_move.InsertString(-1, leString);
			};

			GridJeu.TransferTousPionToMainGrid();
			GridJeu.CloneGridMainToSub();
			OnClickedCalculScoreInitialButton();

			leString.Format(_T("Après"));
			m_listBox_move.InsertString(-1, leString);
		}
	};

	m_dlgChecker.TransferPionsToDisplay(GridJeu.pion_vector_grid_humain, GridJeu.pion_vector_grid_ordi);
	m_dlgChecker.Invalidate();

	PrintGrid();
	UpdateWindow();
};

CGrid::pion CMFCDame3Dlg::CalculeMove_max(CGrid::pion &pion_max, int niveau, int alpha, int beta, CGrid::pion &pion_min)
{
	// TODO: Add your implementation code here.


	int v = -1000;
	CGrid::pion  temp_pion, retire_pion_opposant, pion_score;
	CString leString;
	int sizeVectPionRetire = 0;
	int sizeVectorMovePion = 0;
	int removed_ID, removed_x, removed_y;
	int le_niveau = niveau;

	bool pion_has_moved_on_one_move = false;		// permet de savoir si le pion a bougé au moins une fois parmi toutes les analyses.  S'il n'a pas bougé, on arrête son analyse, il est coincé.  On ne continue pas au niveau suivant.

	int move, score;
	bool pionRemoved;

	int max_pion = 0;
	int max_score = -1000;
	int max_move =0;
	
	le_niveau = le_niveau + 1;
	
	

	if ((le_niveau > GridJeu.max_niveau) || pion_max.removed)
	{


		if (dessineGrid)
		{
			leString.Format(_T("-1-CalculeMove_max  niveau max atteint. Niv.: %d:  "), le_niveau-1);  
			m_listBox_move.InsertString(-1, leString);

		};
		
		


		GridJeu.ComptePionsGrid();												// compte le nombre de pion de chaque joueur.

																				// CalculeMove_max ici 

		score = GridJeu.CalculScoreGrid_max(pion_max);							// pion_max sert a identifier quel est le joueur principal.  ID >0 -> ordi, ID < 0 - > humain
		
		
		if (dessineGrid)
		{
			leString.Format(_T("-4 -CalculeMove_max: points: %d pour pion ID: %d"), pion_max.score, pion_max.ID);
			m_listBox_move.InsertString(-1, leString);

		};

		pion_score.score = score;
		pion_score.move = pion_max.move;
	
		return pion_score;														// ici, on n'a rien changé au pion, donc on retourne.

	};  // fin: if (niveau > GridJeu.max_niveau)

	//*****************************************************************************************************



	for ( move = 0; move <= 1; move++)  // move 0: +x, +y; move 1: -x,+y; move 2: +x, -y; move 3: -x, -y;
	{
		
		m_number_of_moves = m_number_of_moves + 1;
		m_str_moves_total.Format(_T("%d"), m_number_of_moves);

		switch (le_niveau - 1)													// sert à afficher le progrès des recherches sur l'écran.
		{
		case 0:
			m_pion_max_ID.Format(_T("%d"), pion_max.ID);
			m_pion_max_move.Format(_T("%d"), move);
			UpdateData(FALSE);
			break;

		case 1:
			m_pion_min_ID.Format(_T("%d"), pion_min.ID);
			m_pion_min_move.Format(_T("%d"), move);
			UpdateData(FALSE);
			break;

		case 2:
			m_pion_max_ID_niv_3.Format(_T("%d"), pion_max.ID);
			m_pion_max_move_niv_3.Format(_T("%d"), move);
			UpdateData(FALSE);
			break;

		case 3:
			m_pion_min_ID_niv_4.Format(_T("%d"), pion_min.ID);
			m_pion_min_move_niv_4.Format(_T("%d"), move);
			UpdateData(FALSE);
			break;

		default:
			UpdateData(FALSE);
			break;


		};

		
		

		

		if ((m_number_of_moves > m_ctrl_move_start_tracking) && m_BOOL_DessineGrid)
		{
			
			dessineGrid = true;
			PrintGrid();
			UpdateWindow();

		};
						
		temp_pion = GridJeu.EvalueMove(pion_max, GridJeu.delta_x, GridJeu.delta_y, le_niveau, move);

		pionRemoved = false;

		if (temp_pion.hasMoved)
		{

			pion_has_moved_on_one_move = true;

			if (temp_pion.removed)
			{
				pionRemoved = true;
				removed_ID = temp_pion.removed_ID;			//sauvegarde l'info sur le pion qui a peut-être été retiré
				removed_x = temp_pion.removed_x;
				removed_y = temp_pion.removed_y;

				temp_pion.removed = FALSE;					//changer la valeur avant de pousser le pion dans le vecteur des pions qui ont bougé.  Requis de mettre FALSE à ce pion parce que ce n'est pas lui qui a bougé.

			};
			GridJeu.PushPionOnMoveVector(temp_pion);												// sauve la config du pion.  new x,y contient destination.  old x,y : origine, new x,y : nouvelle case.
			GridJeu.AjustePion_in_VectorGrid_to_new_xy(temp_pion);		
			GridJeu.AjoutPion_to_Grid__at_new_xy(temp_pion);										// Ajoute le pion dans sa nouvelle postion (utilise new x,y pour ses coordonnées)
			GridJeu.grid_sub[temp_pion.actual_x][temp_pion.actual_y].ID = 0;						// Le pion quitte la case.  Indique comme vide avec ID=0;
			
			m_number_of_pions_moved = m_number_of_pions_moved + 1;
			m_str_pion_moved.Format(_T("%d"), m_number_of_pions_moved);
			UpdateData(FALSE);
																									// Mettre à jour la grille de jeu
			
			temp_pion.actual_x = temp_pion.new_x;													//met a jour les coordonnes pour indiquer le nouveau point de départ pour l'analyse. 
			temp_pion.actual_y = temp_pion.new_y;													// qui vient d'être mise à jour dans les opérations qui précèdent.

			if (dessineGrid)
			{
				leString.Format(_T("-5 CalculeMove_max: 6 Reset ID: %d -> 0 dans (x,y) (%d, %d) Niveau: %d "), temp_pion.ID, temp_pion.actual_x, temp_pion.actual_y, le_niveau);
				m_listBox_move.InsertString(-1, leString);

				leString.Format(_T("-6 CalculeMove_max: 6a Met ID %d dans (%d,  %d) Niveau: %d"), temp_pion.ID, temp_pion.new_x, temp_pion.new_y, le_niveau);
				m_listBox_move.InsertString(-1, leString);
				
				PrintGrid();
				UpdateWindow();
			};

			
			if (pionRemoved)
			{
					
				retire_pion_opposant = GridJeu.RetirePionCalcul(temp_pion);				// Retire un pion de la grille (ID=0) et met "pion_min.removed" = true dans le vecteurpionGrid approprié.  
																						//ID du pion retiré est temp_pion.remove_ID, ses coordonnées sont remove_x, remove_y
																						// retourne un  pion avec toute l'info sur le pion retiré.

				GridJeu.PushPionOnMoveVector(retire_pion_opposant);						// push le pion retiré dans le stack pour restauration future.


				if (dessineGrid)
				{
					leString.Format(_T("-7 CalculeMove_max Retiré pion du calcul ID: %d dans (%d, %d) Niveau: %d"), retire_pion_opposant.ID, retire_pion_opposant.actual_x, retire_pion_opposant.actual_y, le_niveau);
					m_listBox_move.InsertString(-1, leString);
					PrintGrid();
					UpdateWindow();
				};
			};  //Fin: if(temp_pion.removed)
			
			//***************************************************************************

			pion_score = CalculeMove_min(temp_pion, le_niveau, alpha, beta, pion_min);
			
			//***************************************************************************
					   			 
			pion_score.score = pion_score.score * -1;									//inverse le signe ici.  Le gain d'un joueur est la perte de l'autre.
			pion_score.move = move;
			temp_pion = GridJeu.PopPionFromMoveVector();								//on remet la grille comme avant de bourger le pion avant d'évaluer le prochain move ou pion.

			if (pion_score.score > max_score)
			{
				max_score = pion_score.score;
				max_pion = pion_max.ID;
				max_move = move;
			};


			if (temp_pion.removed)														// Remettre le pion retiré sur la grille de jeu.
			{
				GridJeu.AjoutPionGrid_removed(temp_pion);									// Ajout pion dans le jeu (dans vecteur des pions actifs) et ajoute dans gille de jeu[].
				GridJeu.AjustePion_in_VectorGrid_to_removed_xy(temp_pion);

				if (dessineGrid)
				{
					leString.Format(_T("-9 CalculeMove_max Remet pion ID: %d dans (%d, %d) Niveau: %d"), temp_pion.ID, temp_pion.actual_x, temp_pion.actual_y, le_niveau);
					m_listBox_move.InsertString(-1, leString);
					PrintGrid();
					UpdateWindow();
				};
			
				temp_pion = GridJeu.PopPionFromMoveVector();									// récupérer le pion qui a fait le retrait.
			};  //FIN:  if (temp_pion.removed)
		
			GridJeu.AjoutPion_to_Grid__at_actual_xy(temp_pion);												// Ajout pion dans le jeu (dans vecteur des pions actifs) et ajoute dans gille de jeu[]
			GridJeu.AjustePion_in_VectorGrid_to_actual_xy(temp_pion);
			GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].ID = 0;							// ID=0 indique que la case est vide.

			if (dessineGrid)
			{

				leString.Format(_T("-10 CalculeMove_max Remet pion ID: %d dans (%d, %d) Niveau: %d"), temp_pion.ID, temp_pion.actual_x, temp_pion.actual_y, le_niveau);
				m_listBox_move.InsertString(-1, leString);

				PrintGrid();
				UpdateWindow();
			};

		} // FIN:  if (temp_pion.hasMoved)  code qui suit: ici le pion n'a pas bougé

		else

		{		// debut ELSE:  if (temp_pion.hasMoved)  code qui suit: ici le pion n'a pas bougé

			if (le_niveau > 1)
			{
				GridJeu.ComptePionsGrid();															// compte le nombre de pion de chaque joueur.

				score = GridJeu.CalculScoreGrid_max(pion_max);											// au niveau 1, si le pion ne bouge pas, son score ne peut changer.

				if (pion_score.score > max_score)
				{
					max_score = pion_score.score;
					max_pion = pion_max.ID;
					max_move = move;

				};
			};
			
			
		};// FIN:  if (temp_pion.hasMoved)

		

	}; // FIN: for (move = 0; move <= 1; move++)

	
	if (pion_has_moved_on_one_move)																	// si le pion a bougé au moins une fois, alors il a un score et on peut le transmettre
	{
		pion_score.score = max_score;
		pion_score.move = max_move;
	}
	else
	{
		pion_score.score = -1000;
		pion_score.move = 0;
	};
	return pion_score;

};//FIN: calculMove_max

CGrid::pion CMFCDame3Dlg::CalculeMove_max2(CGrid::pion &pion_max, int niveau, int alpha, int beta, CGrid::pion &pion_min)
{
	// TODO: Add your implementation code here.


	int v = -1000;
	CGrid::pion  temp_pion, retire_pion_opposant, pion_score, pion_max2;
	CString leString;
	int sizeVectPionRetire = 0;
	int sizeVectorMovePion = 0;
	int removed_ID, removed_x, removed_y;
	int le_niveau = niveau;

	bool pion_has_moved_on_one_move = false;		// permet de savoir si le pion a bougé au moins une fois parmi toutes les analyses.  S'il n'a pas bougé, on arrête son analyse, il est coincé.  On ne continue pas au niveau suivant.

	int move, score;
	score = 0;
	bool pionRemoved;

	int max_pion = 0;
	int max_score = -1000;
	int max_move = 0;
	int sizeVect, lePion;
	le_niveau = le_niveau + 1;



	if ((le_niveau > GridJeu.max_niveau) || pion_max.removed)
	{


		if (dessineGrid)
		{
			leString.Format(_T("-1-CalculeMove_max  niveau max atteint. Niv.: %d:  "), le_niveau - 1);
			m_listBox_move.InsertString(-1, leString);

		};




		GridJeu.ComptePionsGrid();												// compte le nombre de pion de chaque joueur.

																				// CalculeMove_max ici 

		score = GridJeu.CalculScoreGrid_max(pion_max);							// pion_max sert a identifier quel est le joueur principal.  ID >0 -> ordi, ID < 0 - > humain


		if (dessineGrid)
		{
			leString.Format(_T("-4 -CalculeMove_max: points: %d pour pion ID: %d"), pion_max.score, pion_max.ID);
			m_listBox_move.InsertString(-1, leString);

		};

		pion_score.score = score;
		pion_score.move = pion_max.move;

		return pion_score;														// ici, on n'a rien changé au pion, donc on retourne.

	};  // fin: if (niveau > GridJeu.max_niveau)

	//*****************************************************************************************************

	if (pion_max.ID < 0)											// ID du pion.  ID > 0 = ordi. ID < 0 = humain (l'autre  joueur).
	{
		sizeVect = GridJeu.GetPionVectHum_grid_Size();				// Trouve la dimension du vecteur Humain 
	};

	if (pion_max.ID > 0)
	{
		sizeVect = GridJeu.GetPionVectOrdi_grid_Size();				// Trouve la dimension du vecteur ordi 
	};



	// pour chaque pion...

	for (lePion = 0; lePion < sizeVect; lePion++)					// Boucle pour évaluer les pions du joueur représentant "pion_max"
	{
		//***************************************************************************************************************ICI


		if (pion_max.ID < 0)
		{
			pion_max2 = GridJeu.GetPionFromGridHumain(lePion);		// Va chercher un pion  
		};

		if (pion_max.ID > 0)
		{
			pion_max2 = GridJeu.GetPionFromGridOrdi(lePion);
		};

		for (move = 0; move <= 1; move++)							// move 0: +x, +y; move 1: -x,+y; move 2: +x, -y; move 3: -x, -y;
		{

			m_number_of_moves = m_number_of_moves + 1;
			m_str_moves_total.Format(_T("%d"), m_number_of_moves);

			switch (le_niveau - 1)									// sert à afficher le progrès des recherches sur l'écran.
			{
			case 0:
				m_pion_max_ID.Format(_T("%d"), pion_max.ID);
				m_pion_max_move.Format(_T("%d"), move);
				UpdateData(FALSE);
				break;

			case 1:
				m_pion_min_ID.Format(_T("%d"), pion_min.ID);
				m_pion_min_move.Format(_T("%d"), move);
				UpdateData(FALSE);
				break;

			case 2:
				m_pion_max_ID_niv_3.Format(_T("%d"), pion_max.ID);
				m_pion_max_move_niv_3.Format(_T("%d"), move);
				UpdateData(FALSE);
				break;

			case 3:
				m_pion_min_ID_niv_4.Format(_T("%d"), pion_min.ID);
				m_pion_min_move_niv_4.Format(_T("%d"), move);
				UpdateData(FALSE);
				break;

			default:
				UpdateData(FALSE);
				break;


			};






			if ((m_number_of_moves > m_ctrl_move_start_tracking) && m_BOOL_DessineGrid)
			{

				dessineGrid = true;
				PrintGrid();
				UpdateWindow();

			};

			temp_pion = GridJeu.EvalueMove(pion_max2, GridJeu.delta_x, GridJeu.delta_y, le_niveau, move);

			pionRemoved = false;

			if (temp_pion.hasMoved)
			{

				pion_has_moved_on_one_move = true;

				if (temp_pion.removed)
				{
					pionRemoved = true;
					removed_ID = temp_pion.removed_ID;			//sauvegarde l'info sur le pion qui a peut-être été retiré
					removed_x = temp_pion.removed_x;
					removed_y = temp_pion.removed_y;

					temp_pion.removed = FALSE;					//changer la valeur avant de pousser le pion dans le vecteur des pions qui ont bougé.  Requis de mettre FALSE à ce pion parce que ce n'est pas lui qui a bougé.

				};
				GridJeu.PushPionOnMoveVector(temp_pion);												// sauve la config du pion.  new x,y contient destination.  old x,y : origine, new x,y : nouvelle case.
				GridJeu.AjustePion_in_VectorGrid_to_new_xy(temp_pion);
				GridJeu.AjoutPion_to_Grid__at_new_xy(temp_pion);										// Ajoute le pion dans sa nouvelle postion (utilise new x,y pour ses coordonnées)
				GridJeu.grid_sub[temp_pion.actual_x][temp_pion.actual_y].ID = 0;						// Le pion quitte la case.  Indique comme vide avec ID=0;

				m_number_of_pions_moved = m_number_of_pions_moved + 1;
				m_str_pion_moved.Format(_T("%d"), m_number_of_pions_moved);
				UpdateData(FALSE);
				// Mettre à jour la grille de jeu

				temp_pion.actual_x = temp_pion.new_x;													//met a jour les coordonnes pour indiquer le nouveau point de départ pour l'analyse. 
				temp_pion.actual_y = temp_pion.new_y;													// qui vient d'être mise à jour dans les opérations qui précèdent.

				if (dessineGrid)
				{
					leString.Format(_T("-5 CalculeMove_max: 6 Reset ID: %d -> 0 dans (x,y) (%d, %d) Niveau: %d "), temp_pion.ID, temp_pion.actual_x, temp_pion.actual_y, le_niveau);
					m_listBox_move.InsertString(-1, leString);

					leString.Format(_T("-6 CalculeMove_max: 6a Met ID %d dans (%d,  %d) Niveau: %d"), temp_pion.ID, temp_pion.new_x, temp_pion.new_y, le_niveau);
					m_listBox_move.InsertString(-1, leString);

					PrintGrid();
					UpdateWindow();
				};


				if (pionRemoved)
				{

					retire_pion_opposant = GridJeu.RetirePionCalcul(temp_pion);				// Retire un pion de la grille (ID=0) et met "pion_min.removed" = true dans le vecteurpionGrid approprié.  
																							//ID du pion retiré est temp_pion.remove_ID, ses coordonnées sont remove_x, remove_y
																							// retourne un  pion avec toute l'info sur le pion retiré.

					GridJeu.PushPionOnMoveVector(retire_pion_opposant);						// push le pion retiré dans le stack pour restauration future.


					if (dessineGrid)
					{
						leString.Format(_T("-7 CalculeMove_max Retiré pion du calcul ID: %d dans (%d, %d) Niveau: %d"), retire_pion_opposant.ID, retire_pion_opposant.actual_x, retire_pion_opposant.actual_y, le_niveau);
						m_listBox_move.InsertString(-1, leString);
						PrintGrid();
						UpdateWindow();
					};
				};  //Fin: if(temp_pion.removed)

				//***************************************************************************

				pion_score = CalculeMove_min(temp_pion, le_niveau, alpha, beta, pion_min);

				//***************************************************************************

				pion_score.score = pion_score.score * -1;									//inverse le signe ici.  Le gain d'un joueur est la perte de l'autre.
				pion_score.move = move;
				temp_pion = GridJeu.PopPionFromMoveVector();								//on remet la grille comme avant de bourger le pion avant d'évaluer le prochain move ou pion.

				if (pion_score.score > max_score)
				{
					max_score = pion_score.score;
					max_pion = pion_max2.ID;
					max_move = move;
				};


				if (temp_pion.removed)														// Remettre le pion retiré sur la grille de jeu.
				{
					GridJeu.AjoutPionGrid_removed(temp_pion);									// Ajout pion dans le jeu (dans vecteur des pions actifs) et ajoute dans gille de jeu[].
					GridJeu.AjustePion_in_VectorGrid_to_removed_xy(temp_pion);

					if (dessineGrid)
					{
						leString.Format(_T("-9 CalculeMove_max Remet pion ID: %d dans (%d, %d) Niveau: %d"), temp_pion.ID, temp_pion.actual_x, temp_pion.actual_y, le_niveau);
						m_listBox_move.InsertString(-1, leString);
						PrintGrid();
						UpdateWindow();
					};

					temp_pion = GridJeu.PopPionFromMoveVector();									// récupérer le pion qui a fait le retrait.
				};  //FIN:  if (temp_pion.removed)

				GridJeu.AjoutPion_to_Grid__at_actual_xy(temp_pion);												// Ajout pion dans le jeu (dans vecteur des pions actifs) et ajoute dans gille de jeu[]
				GridJeu.AjustePion_in_VectorGrid_to_actual_xy(temp_pion);
				GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].ID = 0;							// ID=0 indique que la case est vide.

				if (dessineGrid)
				{

					leString.Format(_T("-10 CalculeMove_max Remet pion ID: %d dans (%d, %d) Niveau: %d"), temp_pion.ID, temp_pion.actual_x, temp_pion.actual_y, le_niveau);
					m_listBox_move.InsertString(-1, leString);

					PrintGrid();
					UpdateWindow();
				};

			} // FIN:  if (temp_pion.hasMoved)  code qui suit: ici le pion n'a pas bougé

			else

			{		// debut ELSE:  if (temp_pion.hasMoved)  code qui suit: ici le pion n'a pas bougé

				if (le_niveau > 1)
				{
					GridJeu.ComptePionsGrid();														// compte le nombre de pion de chaque joueur.

					score = GridJeu.CalculScoreGrid_max(pion_max);									// au niveau 1, si le pion ne bouge pas, son score ne peut changer.

					if (pion_score.score > max_score)
					{
						max_score = pion_score.score;
						max_pion = pion_max2.ID;
						max_move = move;

					};
				};


			};// FIN:  if (temp_pion.hasMoved)



		}; // FIN: for (move = 0; move <= 1; move++)

	}; // FIN for (lePion = 0; lePion < sizeVect; lePion++)

	if (pion_has_moved_on_one_move)																	// si le pion a bougé au moins une fois, alors il a un score et on peut le transmettre
	{
		pion_score.score = max_score;
		pion_score.move = max_move;
		pion_score.ID = max_pion;
	}
	else
	{
		pion_score.score = -1000;
		pion_score.move = 0;
		pion_score.ID = max_pion;
	};
	return pion_score;

};//FIN: calculMove_max


CGrid::pion CMFCDame3Dlg::CalculeMove_min(CGrid::pion &pion_max, int niveau, int alpha, int beta, CGrid::pion &lePion_min)
{
	// TODO: Add your implementation code here.
	//CalculeMovePionHumain_min(pion &pion, int niveau, int alpha, int beta)

	int v = 1000;
	
	CGrid::pion pion_return_minmax, pion_min, temp_pion,retire_pion_opposant, pion_score;
		CString leString;

		int min_score = 1000;
		int min_pion = 0;
		int min_move = 0;
		int score, move, lePion, sizeVect,le_niveau;
		
		sizeVect = 0;
		score = 0;
		int sizeVectPionRetire = 0;
		int sizeVectorMovePion = 0;
		bool pionRemoved = false;
		bool testRemoved = false;

		
		
		le_niveau = niveau;
		

		//********************************************************************************************
		le_niveau = le_niveau + 1;

		if (le_niveau > GridJeu.max_niveau)
		{
			
			if (dessineGrid)
			{
				leString.Format(_T("1-CalculeMove_min Niveau max atteint: niveau: %d"), le_niveau);
				m_listBox_move.InsertString(-1, leString);

			};
			
			// CalculeMove_min ici			
			GridJeu.ComptePionsGrid();												// compte le nombre de pion de chaque joueur.
			score = GridJeu.CalculScoreGrid_min(pion_max);								// pion_max sert a identifier quel est le joueur principal.  ID >0 -> ordi, ID < 0 - > humain
			
			


			pion_score.score = score;
			pion_score.ID = pion_max.ID;
			pion_score.move = pion_max.move;

			return pion_score;
			

		};	// Fin : if (le_niveau > GridJeu.max_niveau)
		
		//***************************************************************************************
		
		if (pion_max.ID > 0)											// ID du pion.  ID > 0 = ordi. ID < 0 = humain (l'autre  joueur).
		{
			sizeVect = GridJeu.GetPionVectHum_grid_Size();				// Trouve la dimension du vecteur Humain (qui est l'opposant de l'ordi ici)
		};

		if (pion_max.ID < 0)
		{
			sizeVect = GridJeu.GetPionVectOrdi_grid_Size();				// Trouve la dimension du vecteur ordi (qui est l'opposant de l'humain ici)
		};

		

		// pour chaque pion...

		for (lePion = 0; lePion < sizeVect; lePion++)				// Boucle pour évaluer les pions du joueur
		{
			//***************************************************************************************************************ICI
			

			if (pion_max.ID > 0)
			{
				pion_min = GridJeu.GetPionFromGridHumain(lePion);	// Va chercher un pion de l'adversaire. 
			};

			if (pion_max.ID < 0)
			{
				pion_min = GridJeu.GetPionFromGridOrdi(lePion);
			};

			
			if (!pion_min.removed)															//si le pion est présent pion.removed = false;
			{
				
				// pour chaque move...

				for (move = 0; move < 2; move++)
				{
					m_number_of_moves = m_number_of_moves + 1;
					m_str_moves_total.Format(_T("%d"), m_number_of_moves);

					switch (le_niveau-1) 
					{
					case 0:
						m_pion_max_ID.Format(_T("%d"), pion_max.ID);
						m_pion_max_move.Format(_T("%d"), move);
						UpdateData(FALSE);
						break;

					case 1:
						m_pion_min_ID.Format(_T("%d"), pion_min.ID);
						m_pion_min_move.Format(_T("%d"), move);
						UpdateData(FALSE);
						break;

					case 2:
						m_pion_max_ID_niv_3.Format(_T("%d"), pion_max.ID);
						m_pion_max_move_niv_3.Format(_T("%d"), move);
						UpdateData(FALSE);
						break;

					case 3:
						m_pion_min_ID_niv_4.Format(_T("%d"), pion_min.ID);
						m_pion_min_move_niv_4.Format(_T("%d"), move);
						UpdateData(FALSE);
						break;

					default:
						UpdateData(FALSE);
						break;


					};
					

					if (m_number_of_moves > m_ctrl_move_start_tracking && m_BOOL_DessineGrid)
					{
						dessineGrid = true;
						PrintGrid();
						UpdateWindow();
					};

					temp_pion = GridJeu.EvalueMove(pion_min, GridJeu.delta_x, GridJeu.delta_y, le_niveau, move);
																									// EvalueMove retourne un pion avec les nouvelles coordonnées dans new_x, new_y si le pion a bougé.
																									// temp.pion.removed = true indique qu'on a mangé un pion ennemi.  new_x, new_y pointe alors sur la case vide, après le pion mangé.
					pionRemoved = false;

					if (temp_pion.hasMoved)
					{
					
						m_number_of_pions_moved = m_number_of_pions_moved + 1;						//augmente le compteur de mouvements, pour affichage ...
						m_str_pion_moved.Format(_T("%d"), m_number_of_pions_moved);
						UpdateData(FALSE);															// Mettre à jour l'affichage du nombre de move effectués.
																									//  Si le pion a bougé, alors...
					
						if (temp_pion.removed)
						{
							if (temp_pion.removed_ID == pion_max.ID)
							{
								GridJeu.ComptePionsGrid();											// compte le nombre de pion de chaque joueur.
								score = GridJeu.CalculScoreGrid_min(pion_max);						// pion_max sert a identifier quel est le joueur principal.  ID >0 -> ordi, ID < 0 - > humain
								pion_score.score = score + 1;										// ajouter 1 au score pour tenir compte du pion qui est retiré mais pas compté (grille n'a pas été mise à jour ici)
								pion_score.ID = pion_max.ID;
								pion_score.move = pion_max.move;

								return pion_score;

							};
							
							pionRemoved = true;
							//removed_ID = temp_pion.removed_ID;										//sauvegarde l'info sur le pion qui a peut-être été retiré
							//removed_x = temp_pion.removed_x;
							//removed_y = temp_pion.removed_y;

							temp_pion.removed = FALSE;												//changer la valeur avant de pousser le pion dans le vecteur des pions qui ont bougé.  Requis de mettre FALSE à ce pion parce que ce n'est pas lui qui a bougé.

						};

						GridJeu.PushPionOnMoveVector(temp_pion);
						GridJeu.AjustePion_in_VectorGrid_to_new_xy(temp_pion);
						GridJeu.AjoutPion_to_Grid__at_new_xy(temp_pion);							// Ajoute le pion dans sa nouvelle postion (utilise new x,y pour ses coordonnées)
						GridJeu.grid_sub[temp_pion.actual_x][temp_pion.actual_y].ID = 0;			// Le pion quitte la case.  Indique comme vide avec ID=0;

						//temp_pion.actual_x = temp_pion.new_x;										//met a jour les coordonnes pour indiquer où se trouve le pion maintenant ("new x,y") qui doit être analysé.  Ce qui correspond aussi à la grille de jeu 
						//temp_pion.actual_y = temp_pion.new_y;										// qui vient d'être mise à jour dans les opérations qui précèdent.

						if (dessineGrid)
						{
							leString.Format(_T("5 CalculeMove_min: 6  Met ID %d -> 0 dans (%d, %d) Niveau: %d, move: %d "), temp_pion.ID, temp_pion.actual_x, temp_pion.actual_y, le_niveau, m_number_of_moves);
							m_listBox_move.InsertString(-1, leString);

							leString.Format(_T("6 CalculeMove_min: 6a Met ID %d      dans (%d, %d) Niveau: %d "), temp_pion.ID, temp_pion.new_x, temp_pion.new_y, le_niveau);
							m_listBox_move.InsertString(-1, leString);
							
							PrintGrid();
							UpdateWindow();
						};

						if (le_niveau == 2)
						{
							lePion_min.ID = temp_pion.ID;
							lePion_min.new_x = temp_pion.new_x;
							lePion_min.new_y = temp_pion.new_y;
							lePion_min.actual_x = temp_pion.new_x;											//met a jour les coordonnes pour indiquer où se trouve le pion maintenant ("new x,y") qui doit être analysé.  Ce qui correspond aussi à la grille de jeu 
							lePion_min.actual_y = temp_pion.new_y;											// met a jour les coordonnes pour indiquer où se trouve le pion maintenant("new x,y") qui doit être analysé.Ce qui correspond aussi à la grille de jeu
							lePion_min.hasMoved = temp_pion.hasMoved;
							lePion_min.score = temp_pion.score;
							lePion_min.dame = temp_pion.dame;
							lePion_min.move = temp_pion.move;
							lePion_min.removed = temp_pion.removed;
							lePion_min.removed_ID = temp_pion.removed_ID;
							lePion_min.removed_x = temp_pion.removed_x;
							lePion_min.removed_y = temp_pion.removed_y;
						};
						
						if (pionRemoved)												// Si ce pion a capturé un pion ennemi (si removed = TRUE), alors retire le pion ennemi du grid. 
																						//Sauvegarde dans stack pour restauration future...
						{

							
							retire_pion_opposant = GridJeu.RetirePionCalcul(temp_pion);				// Retire un pion de la grille (ID -> 0) et met "pion_min.removed = true" dans pion_vector_grid_ordi/humain.  
																									//ID du pion retiré, info temp_pion.removed_ID, removed_x, removed_y sont mis à jour.
							
						
							GridJeu.PushPionOnMoveVector(retire_pion_opposant);						// push le pion retiré dans le stack pour restauration future.

														
							if (dessineGrid)
							{
								leString.Format(_T("7 CalculeMove_min Retiré pion du calcul ID: %d dans (%d, %d) Niveau: %d "), retire_pion_opposant.ID, retire_pion_opposant.actual_x, retire_pion_opposant.actual_y, le_niveau);
								m_listBox_move.InsertString(-1, leString);

								PrintGrid();

								UpdateWindow();

							};

						};  // Fin: if (pionRemoved)

						//*******************************************************************************

						pion_score = CalculeMove_max2(pion_max, le_niveau, alpha, beta, lePion_min);

						//*******************************************************************************

						pion_score.score = -1 * pion_score.score;											// le gain d'un joueur  devient une perte pour l'autre joueur. 

																											// ici, on retourne de la fonction recursive (CalculeMove_max), 
																											//on remet le jeu comme avant de bourger le pion avant d'évaluer le prochain move ou pion.
						temp_pion = GridJeu.PopPionFromMoveVector();

						if (temp_pion.removed)																// Remettre le pion retiré sur la grille de jeu.
						{
							GridJeu.AjoutPionGrid_removed(temp_pion);
																											// Ajout pion dans le jeu (dans vecteur des pions actifs) et ajoute dans gille de jeu[]
							GridJeu.AjustePion_in_VectorGrid_to_removed_xy(temp_pion);						// pion retiré: ID est celle du pion retiré, removed_x,y: coordonnées du pion retiré.

							if (dessineGrid)
							{
								leString.Format(_T("8 CalculeMove_min Remet pion ID = %d dans (%d, %d) Niveau: %d"), temp_pion.ID, temp_pion.actual_x, temp_pion.actual_y, le_niveau);
								m_listBox_move.InsertString(-1, leString);
								PrintGrid();
								UpdateWindow();
							};

							temp_pion = GridJeu.PopPionFromMoveVector();									// récupérer le pion qui a fait le retrait.

						}; //FIN:  if (temp_pion.removed)

						GridJeu.AjoutPion_to_Grid__at_actual_xy(temp_pion);									// Ajout pion dans le jeu (dans vecteur des pions actifs) et ajoute dans gille de jeu[]
						GridJeu.AjustePion_in_VectorGrid_to_actual_xy(temp_pion);
						GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].ID = 0;							// ID=0 indique que la case est vide.

						if (pion_score.score < min_score)
						{
							min_score = pion_score.score;
							min_pion = temp_pion.ID;
							min_move = move;

						};
						
						if (dessineGrid)
						{
							leString.Format(_T("9 CalculeMove_min:  Met ID = 0  dans (%d, %d) Niveau: %d "), temp_pion.new_x, temp_pion.new_y, le_niveau);
							m_listBox_move.InsertString(-1, leString);

							leString.Format(_T("10 CalculeMove_min:  Met ID = %d dans (%d, %d) Niveau: %d "), temp_pion.ID, temp_pion.actual_x, temp_pion.actual_y, le_niveau);
							m_listBox_move.InsertString(-1, leString);

							PrintGrid();
							UpdateWindow();
						};



					} // Fin: if(hasMoved?)

					else

					{ // DEBUT: if (temp_pion.hasMoved) else...   ici le pion n'a pas bougé.
						
						GridJeu.ComptePionsGrid();																			// Ici, le pion n'a pas bougé.   On calcule le score de la situation.															
																															// compte le nombre de pion de chaque joueur.
						score = GridJeu.CalculScoreGrid_max(lePion_min);

						if (score < min_score)
						{
							min_score = score;
							min_pion = pion_min.ID;
							min_move = move;

						};



					};// FIN: if (temp_pion.hasMoved)

					

				}; // FIN: for (move = 0; move <= 1; move++)

					

			}  // FIN: if (!pionRetire)

			else

			{   // else: if (!pionRetire)
				GridJeu.ComptePionsGrid();			// Le pion a été retiré (ne fait plus partie de la grille).  Calcule le score comme si le niveau max avait été atteint.

				score = GridJeu.CalculScoreGrid_min(pion_max);

				if (score < min_score)
				{
					min_score = score;
					min_pion = pion_min.ID;
					min_move = 0;
				};

			};

		};  //FIN:  for (lePion = 0; lePion < sizeVect; lePion++)
		
		pion_score.score = min_score;
		pion_score.move = min_move;
		pion_score.ID = pion_min.ID;

	return pion_score;  // retourne le pion avec son score.
		
};  // FIN: calculeMove_min

void CMFCDame3Dlg::PrintGrid()
{
	int i, j,k,l, ID;
	CString leString;

	leString.Format(_T("----------------------"));
	m_listBox_move.InsertString(-1, leString);

	leString.Format(_T("move: %d"), m_number_of_moves);
	m_listBox_move.InsertString(-1, leString);

	for (i = GridJeu.max_grid_size-1; i >= 0; i--)
		
	{
		
		
			leString.Format(_T("y: %d  %10d  %10d  %10d  %10d  %10d  %10d  %10d  %10d  %10d  %10d"), i, GridJeu.grid_sub[0][i].ID, GridJeu.grid_sub[1][i].ID, GridJeu.grid_sub[2][i].ID, GridJeu.grid_sub[3][i].ID, GridJeu.grid_sub[4][i].ID, GridJeu.grid_sub[5][i].ID, GridJeu.grid_sub[6][i].ID, GridJeu.grid_sub[7][i].ID, GridJeu.grid_sub[8][i].ID, GridJeu.grid_sub[9][i].ID);
			
			
			m_listBox_move.InsertString(-1, leString);

		
	};
	

	leString.Format(_T("  "));
	m_listBox_move.InsertString(-1, leString);

	leString.Format(_T("x:  %10d  %10d  %10d  %10d  %10d  %10d  %10d  %10d  %10d  %10d"),0,1,2,3,4,5,6,7,8,9);


	m_listBox_move.InsertString(-1, leString);

	leString.Format(_T("----------------------"));
	m_listBox_move.InsertString(-1, leString);



	// check si 2 cases ont le meme ID:
	for (i = 0; i < 10; i++)

	{
		for (j = 0; j < 10; j++)
		{
			
			ID = GridJeu.grid_sub[i][j].ID;
			
			for (k = 0; k < 10; k++)

			{
				for (l = 0; l < 10; l++)
				{

					
					if ((i != k) || (j != l))
					{
						if (ID == GridJeu.grid_sub[k][l].ID)
						{
							if (ID != 0)
							{
								leString.Format(_T("Doublon trouvé.  ID: %d, move: %d"), ID, m_number_of_moves);
								m_listBox_move.InsertString(-1, leString);
								dessineGrid = true;

								m_ListBox_Suivi_Jeu.InsertString(-1, leString);
							};
						};
					};

				};
			};
			
		};
	};

};

//************************************************************

void CMFCDame3Dlg::CheckDoublon()
{
	int i, j, k, l, ID;
	CString leString;

	
	// check si 2 cases ont le meme ID:
	for (i = 0; i < 10; i++)

	{
		for (j = 0; j < 10; j++)
		{

			ID = GridJeu.grid_sub[i][j].ID;

			for (k = 0; k < 10; k++)

			{
				for (l = 0; l < 10; l++)
				{


					if ((i != k) || (j != l))
					{
						if (ID == GridJeu.grid_sub[k][l].ID)
						{
							if (ID != 0)
							{
								leString.Format(_T("Doublon trouvé.  ID: %d, move: %d"), ID, m_number_of_moves);
								m_listBox_move.InsertString(-1, leString);
								dessineGrid = true;

								m_ListBox_Suivi_Jeu.InsertString(-1, leString);
							};
						};
					};

				};
			};

		};
	};

};

//************************************************************

void CMFCDame3Dlg::PrintScorePions()
{
	
	CGrid::pion lepion;
	CString leString;

	m_ListBox_Suivi_Jeu.InsertString(-1, _T("--------------"));

	lepion = GridJeu.TrouveBestPionOrdi();
	leString.Format(_T("Meilleur pointage ordi: ID %d,  points: %d,  move: %d."), lepion.ID, lepion.score, lepion.move);
	m_ListBox_Suivi_Jeu.InsertString(-1, leString);


	lepion = GridJeu.TrouveBestPionHumain();
	leString.Format(_T("Meilleur pointage humain: ID %d, points: %d,  move: %d."), lepion.ID, lepion.score, lepion.move);
	m_ListBox_Suivi_Jeu.InsertString(-1, leString);

	m_ListBox_Suivi_Jeu.InsertString(-1, _T("--------------"));

};




void CMFCDame3Dlg::OnBnClickedUptNiveau()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	GridJeu.max_niveau = _ttoi(m_str_MaxNiveau);

}


void CMFCDame3Dlg::OnStnClickedStaticPionId()
{
	// TODO: Add your control notification handler code here
}


void CMFCDame3Dlg::OnBnClickedBoutonJoue()
{
	int i, nombre_coups ;

	UpdateData(TRUE);

	nombre_coups = _ttoi(m_nbre_coups);
	GridJeu.m_nbre_pion_meilleurs = _ttoi(m_STR_nbre_pion_selection_finale);

	for (i = 0; i < nombre_coups; i++)
	{
		
		OnBnClickedOrdiJoueButton();
		OnBnClickedHumainJoueButton();


		m_dlgChecker.TransferPionsToDisplay( GridJeu.pion_vector_grid_humain, GridJeu.pion_vector_grid_ordi);
		m_dlgChecker.Invalidate();
		
		//PaintGrid_graphic();


		m_STR_nbre_pion_selection_finale.Format(_T("%d"), GridJeu.m_nbre_pion_meilleurs);
		m_nbre_coups.Format(_T("%d"), nombre_coups-i-1);
		UpdateData(FALSE);
	};
	
	m_dlgChecker.TransferPionsToDisplay(GridJeu.pion_vector_grid_humain, GridJeu.pion_vector_grid_ordi);
	
	//m_dlgChecker.InvalidateRect();
	
	m_dlgChecker.Invalidate();

	m_dlgChecker.UpdateWindow();





	// TODO: Add your control notification handler code here
}


void CMFCDame3Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

		
	CDialogEx::OnMouseMove(nFlags, point);
}


int CMFCDame3Dlg::PaintGrid_graphic()
{
	// TODO: Add your implementation code here.

	
	return 0;
	
}


void CMFCDame3Dlg::OnBnClickedBtnTrouveBestPion()
{
	// TODO: Add your control notification handler code here
	
	CGrid::pion lePion;
	CString leString;

	OnBnClickedEvalueMoveButton();

	lePion = GridJeu.TrouveBestPionHumain();

	leString.Format(_T("Meilleur points humain: ID %d,  points: %d,  move: %d."), lePion.ID, lePion.score, lePion.move);
	m_ListBox_Suivi_Jeu.InsertString(-1, leString);

	lePion = GridJeu.TrouveBestPionOrdi();

	leString.Format(_T("Meilleur points ordi: ID %d,  points: %d,  move: %d."), lePion.ID, lePion.score, lePion.move);
	m_ListBox_Suivi_Jeu.InsertString(-1, leString);

}







void CMFCDame3Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CString leString;
	CTime curTime = CTime::GetCurrentTime();
	CGrid::pion lePion, tempPion;
	int score, move;
	score = 0;
	move = 0;

	UpdateData(TRUE);
	GridJeu.max_niveau = _ttoi(m_str_MaxNiveau);

	m_sTime2= curTime.Format("%H:%M:%S");
	UpdateData(FALSE);

	if (m_dlgChecker.m_HumainBouge)
	{
		KillTimer(IDC_STATIC_TIME);

		lePion = GridJeu.TrouvePionAt_XY(m_dlgChecker.m_case_origine_x, m_dlgChecker.m_case_origine_y);

	

		if ((m_dlgChecker.m_case_origine_x - m_dlgChecker.m_case_destination_x) < 0)
		{
			lePion.move = 0;
			move = 0;
		};

		if ((m_dlgChecker.m_case_origine_x - m_dlgChecker.m_case_destination_x) > 0)
		{
			lePion.move = 1;
			move = 1;
		};


		if (lePion.ID == 999)
		{
			// ici, le pion joué par l'utilisateur ne fait pas partie des pions HUMAIN.  Message d'erreur à afficher.  On oublie ce move
			leString.Format(_T("VOUS NE POUVEZ JOUER LES PIONS ASSIGNES A L'ORDINATEUR (pions rouges)"));
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);
		} 
		else
		{
			tempPion = GridJeu.EvalueMove(lePion, GridJeu.delta_x, GridJeu.delta_y, 1, move);
			
			if (GridJeu.MovePion(lePion, GridJeu.delta_x, GridJeu.delta_y, lePion.move))
			{
				score = GridJeu.GetPionScore(lePion);
				leString.Format(_T("Déplacement de pion: %d  réussi.  points: %d "), lePion.ID, score);
				m_ListBox_Suivi_Jeu.InsertString(1, leString);					// insere une ligne vide pour affichage plus facilement lisible.																										
				m_listBox_move.InsertString(-1, leString);
			}

			else

			{
				leString.Format(_T("ECHEC: Déplacement de pion: %d "), lePion.ID);
				m_ListBox_Suivi_Jeu.InsertString(1, leString);					// insere une ligne vide pour affichage plus facilement lisible.
				m_listBox_move.InsertString(-1, leString);
			};

			GridJeu.TransferTousPionToMainGrid();
			GridJeu.CloneGridMainToSub();
			OnClickedCalculScoreInitialButton();

			leString.Format(_T("Après"));
			m_listBox_move.InsertString(-1, leString);
			m_dlgChecker.TransferPionsToDisplay(GridJeu.pion_vector_grid_humain, GridJeu.pion_vector_grid_ordi);

			m_dlgChecker.m_origine_X = 0;
			m_dlgChecker.m_origine_Y = 0;
			m_dlgChecker.m_destination_X = 0;
			m_dlgChecker.m_destination_Y = 0;

			m_dlgChecker.Invalidate();

			PrintGrid();
			UpdateWindow();

		};

		OnBnClickedOrdiJoueButton();

		m_dlgChecker.m_HumainBouge = false;
		SetTimer(ID_CLOCK_TIMER, 500, NULL);
	};


	CDialogEx::OnTimer(nIDEvent);
}


void CMFCDame3Dlg::OnStnClickedOrdPionGrid()
{
	// TODO: Add your control notification handler code here
}
