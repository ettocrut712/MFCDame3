
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
}

BEGIN_MESSAGE_MAP(CMFCDame3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Init_BUTTON, &CMFCDame3Dlg::OnClickedInitButton)
	ON_BN_CLICKED(IDC_Reset_BUTTON, &CMFCDame3Dlg::OnClickedResetButton)
	ON_BN_CLICKED(IDC_calcul_score_initial_BUTTON, &CMFCDame3Dlg::OnClickedCalculScoreInitialButton)
	ON_BN_CLICKED(IDC_calcul_score_grid_sub_BUTTON, &CMFCDame3Dlg::OnClickedComptePionsGridSubButton)
	ON_BN_CLICKED(IDC_evalueMove_BUTTON, &CMFCDame3Dlg::OnBnClickedevaluemoveButton)
	ON_BN_CLICKED(IDC_ORDI_JOUE_BUTTON, &CMFCDame3Dlg::OnBnClickedOrdiJoueButton)
	ON_BN_CLICKED(IDC_HUMAIN_JOUE_BUTTON, &CMFCDame3Dlg::OnBnClickedHumainJoueButton)
	ON_BN_CLICKED(IDC_UPT_NIVEAU, &CMFCDame3Dlg::OnBnClickedUptNiveau)
	ON_STN_CLICKED(IDC_STATIC_PION_ID, &CMFCDame3Dlg::OnStnClickedStaticPionId)
	ON_BN_CLICKED(IDC_BOUTON_JOUE, &CMFCDame3Dlg::OnBnClickedBoutonJoue)
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
	m_str_moves_total="0";
	m_str_pion_moved ="0";


	//m_str_MaxNiveau.Format("%d", GridJeu.max_niveau);

	//m_str_MaxNiveau = GridJeu.max_niveau;
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
	
	CString leString;
	dessineGrid = false;

	UpdateData(TRUE);
	
	m_number_of_moves = 0;
	m_number_of_pions_moved = 0;
	m_BOOL_DessineGrid = true;
	m_str_moves_total.Format(_T("%d"), m_number_of_moves);
	m_str_pion_moved.Format(_T("%d"), m_number_of_pions_moved);
	m_str_MaxNiveau.Format(_T("%d"),GridJeu.max_niveau);
	//m_move_debug_NT.Format(_T("%d"), m_move_start_tracking);				// affiche le nombre de move faits avant que le programme ne commence à afficher le détails dans la case de suivi des mouvements.

	
	
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

	GridJeu.ResetScorePions();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Reset score des pions"));

	GridJeu.CloneGridMainToSub();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Clone grid_main vers grid_sub"));

	GridJeu.ResetScorePions();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Reset score des pions"));

	OnClickedCalculScoreInitialButton();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Calcul du score initial (nombre de pions de chaque joueur)"));

	OnClickedComptePionsGridSubButton();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Calcule le score de la grille grid_sub "));


	GridJeu.ResetPionVectorGrid();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Reset vecteur de pion de la grille de jeu"));

	

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


void CMFCDame3Dlg::OnClickedComptePionsGridSubButton()
{
	// TODO: Add your control notification handler code here

	int temp;
	int score_grid;
	CString leString;
	
	GridJeu.ComptePionsGrid();

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


void CMFCDame3Dlg::OnBnClickedevaluemoveButton()
{
	// TODO: Add your control notification handler code here
	int pionID;
	CGrid::pion my_pion_max;
	CGrid::pion m_pion_evalue;

	int niveau = 0;
	int move;
	int sizeVect;
	CString leString;
	
	auto pGrid = &CGrid::grid_sub;

	sizeVect = GridJeu.GetPionVectOrdiSize();
	


	for (pionID = 0; pionID < sizeVect; pionID++)
	{
		my_pion_max = GridJeu.GetPionFromVectOrdi(pionID);

		
		
		for (move = 0; move <=3; move++)			// changer le 2 en fonction du type de pion: dame = 4 moves.  Pion -> 2 moves max.
		{
			m_pion_evalue = GridJeu.EvalueMove( my_pion_max, GridJeu.delta_x, GridJeu.delta_y, niveau, move);
			
			


		};
	};

	sizeVect = GridJeu.GetPionVectHumSize();



	for (pionID = 0; pionID < sizeVect; pionID++)
	{
		my_pion_max = GridJeu.GetPionFromVectHumain(pionID);



		for (move = 0; move <= 3; move++)			// changer le 2 en fonction du type de pion: dame = 4 moves.  Pion -> 2 moves max.
		{
			m_pion_evalue = GridJeu.EvalueMove(my_pion_max, GridJeu.delta_x, GridJeu.delta_y, niveau, move);


			leString.Format(_T("Pion: %d ,  move: %d .  Resultat: %d"), my_pion_max.ID, move, m_pion_evalue.move);
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);


		};
	};


}


void CMFCDame3Dlg::OnBnClickedOrdiJoueButton()
{
	// TODO: Add your control notification handler code here

	int pionID;
	CGrid::pion my_pion_max, my_pion_min, minimax_pion;
	

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

	
	for (pionID = 0; pionID < sizeVect; pionID++)						//Pour tous les pions qui sont encore dans le jeu, calculer le meilleur pion à bouger.
	{
		my_pion_max = GridJeu.GetPionFromVectOrdi(pionID);				//Obtient un pion du vecteur	


		minimax_pion = CalculeMove_max(my_pion_max, le_niveau, alpha, beta, my_pion_min);	// minimax_pion est le résultat de l'évaluation complétée pour les mouvements de ce pion.
		
																			// ici le pion n'a pu bouger.  Donc pas de score valide.
		
		GridJeu.SetPionScore(minimax_pion);
																			// Une fois tous les pions évalués.  On choisit le meilleur pion à bouger
		

	};  // FIN : for (pionID = 0; pionID < sizeVect; pionID++)

	PrintScorePions();

	my_pion_max = GridJeu.TrouveBestPionOrdi();

	m_listBox_move.ResetContent();
	leString.Format(_T("Avant"));
	m_listBox_move.InsertString(-1, leString);
	PrintGrid();

	if (GridJeu.MovePion(my_pion_max, GridJeu.delta_x, GridJeu.delta_y, my_pion_max.move))
	{
		leString.Format(_T("Déplacement de pion: %d  réussi"), my_pion_max.ID);
		m_ListBox_Suivi_Jeu.InsertString(-1, leString);					// insere une ligne vide pour affichage plus facilement lisible.																										
		m_listBox_move.InsertString(-1, leString);
	}
	else
	{
		leString.Format(_T("ECHEC: Déplacement de pion: %d "), my_pion_max.ID);
		m_ListBox_Suivi_Jeu.InsertString(-1, leString);					// insere une ligne vide pour affichage plus facilement lisible.
		m_listBox_move.InsertString(-1, leString);
	};

	GridJeu.TransferTousPionToMainGrid();
	GridJeu.CloneGridMainToSub();
	OnClickedCalculScoreInitialButton();

	leString.Format(_T("Après"));
	m_listBox_move.InsertString(-1, leString);

	PrintGrid();
	UpdateWindow();
};


void CMFCDame3Dlg::OnBnClickedHumainJoueButton()
{
	// TODO: Add your control notification handler code here

	int pionID;
	CGrid::pion my_pion_max, my_pion_min, minimax_pion;


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

	GridJeu.CalculScoreInitial();												// calcule le nombre de joueurs de chaque équipe avant de faire les analyses de mouvement.  Score = (# joueurs ennemi initial - # joeurs ennemi final) - (# joueurs ami initial - # joeurs ami final)

	for (pionID = 0; pionID < sizeVect; pionID++)
	{
		my_pion_max = GridJeu.GetPionFromVectHumain(pionID);					//retourne le pion "humain" pion(pionID)
		
		minimax_pion = CalculeMove_max(my_pion_max, le_niveau, alpha, beta, my_pion_min);	// minimax_pion est le résultat de l'évaluation complétée pour les mouvements de ce pion.

		
		GridJeu.SetPionScore(minimax_pion);

																			// on met à jour le score pour ce pion

	}; // FIN: for (pionID = 0; pionID < sizeVect; pionID++)

	

	my_pion_max = GridJeu.TrouveBestPionHumain();

	m_listBox_move.ResetContent();
	leString.Format(_T("Avant"));
	m_listBox_move.InsertString(-1, leString);
	PrintGrid();

	if (GridJeu.MovePion(my_pion_max, GridJeu.delta_x, GridJeu.delta_y, my_pion_max.move))
	{
		
		
		leString.Format(_T("Déplacement de pion: %d  réussi"), my_pion_max.ID);
		m_ListBox_Suivi_Jeu.InsertString(1, leString);					// insere une ligne vide pour affichage plus facilement lisible.																										
		m_listBox_move.InsertString(-1, leString);
	}
	else
	{
		leString.Format(_T("ECHEC: Déplacement de pion: %d "), my_pion_max.ID);
		m_ListBox_Suivi_Jeu.InsertString(1, leString);					// insere une ligne vide pour affichage plus facilement lisible.
		m_listBox_move.InsertString(-1, leString);
	};

	GridJeu.TransferTousPionToMainGrid();
	GridJeu.CloneGridMainToSub();
	OnClickedCalculScoreInitialButton();

	leString.Format(_T("Après"));
	m_listBox_move.InsertString(-1, leString);
	
	PrintGrid();
	UpdateWindow();
};

CGrid::pion CMFCDame3Dlg::CalculeMove_max(CGrid::pion &pion_max, int niveau, int alpha, int beta, CGrid::pion &pion_min)
{
	// TODO: Add your implementation code here.


	int v = -1000;
	CGrid::pion pion_return_minmax, temp_pion, retire_pion_opposant;
	CString leString;
	int sizeVectPionRetire = 0;
	int sizeVectorMovePion = 0;
	int removed_ID, removed_x, removed_y;
	int le_niveau = niveau;
	
	int move,  i;
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
		
		


		GridJeu.ComptePionsGrid();			// compte le nombre de pion de chaque joueur.

		// CalculeMove_max ici 

		pion_min.score = GridJeu.CalculScoreGrid(pion_max);							// pion_max sert a identifier quel est le joueur principal.  ID >0 -> ordi, ID < 0 - > humain
		
		
		if (dessineGrid)
		{
			leString.Format(_T("-4 -CalculeMove_max: score: %d pour pion ID: %d"), pion_max.score, pion_max.ID);
			m_listBox_move.InsertString(-1, leString);

		};


		
		return pion_min;															// ici, on n'a rien changé au pion, donc on retourne.

	};  // fin: if (niveau > GridJeu.max_niveau)

	//*****************************************************************************************************



	for ( move = 0; move <= 1; move++)  // move 0: +x, +y; move 1: -x,+y; move 2: +x, -y; move 3: -x, -y;
	{
		
		switch (le_niveau - 1)
		{
		case 0:
			m_pion_max_ID.Format(_T("%d"), pion_max.ID);
			m_pion_max_move.Format(_T("%d"), move);
			m_number_of_moves = m_number_of_moves + 1;
			m_str_moves_total.Format(_T("%d"), m_number_of_moves);
			UpdateData(FALSE);
			break;

		case 1:
			m_pion_min_ID.Format(_T("%d"), pion_min.ID);
			m_pion_min_move.Format(_T("%d"), move);
			m_number_of_moves = m_number_of_moves + 1;
			m_str_moves_total.Format(_T("%d"), m_number_of_moves);
			UpdateData(FALSE);
			break;

		case 2:
			m_pion_max_ID_niv_3.Format(_T("%d"), pion_max.ID);
			m_pion_max_move_niv_3.Format(_T("%d"), move);
			m_number_of_moves = m_number_of_moves + 1;
			m_str_moves_total.Format(_T("%d"), m_number_of_moves);
			UpdateData(FALSE);
			break;

		case 3:
			m_pion_min_ID_niv_4.Format(_T("%d"), pion_min.ID);
			m_pion_min_move_niv_4.Format(_T("%d"), move);
			m_number_of_moves = m_number_of_moves + 1;
			m_str_moves_total.Format(_T("%d"), m_number_of_moves);
			UpdateData(FALSE);
			break;

		default:
			m_str_moves_total.Format(_T("%d"), m_number_of_moves);
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
			
			if (temp_pion.removed)
			{
				pionRemoved = true;
				removed_ID = temp_pion.removed_ID;			//sauvegarde l'info sur le pion qui a peut-être été retiré
				removed_x = temp_pion.removed_x;
				removed_y = temp_pion.removed_y;

				temp_pion.removed = FALSE;					//changer la valeur avant de pousser le pion dans le vecteur des pions qui ont bougé.  Requis de mettre FALSE à ce pion parce que ce n'est pas lui qui a bougé.

			};

			GridJeu.PushPionOnMoveVector(temp_pion);		// sauve la config du pion.  new x,y contient destination.  old x,y : origine, new x,y : nouvelle case.
			GridJeu.AjustePionVectorGrid(temp_pion);		
			GridJeu.AjoutPionGrid_new(temp_pion);											// Ajoute le pion dans sa nouvelle postion (utilise new x,y pour ses coordonnées)
			GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].ID = 0;						// Le pion quitte la case.  Indique comme vide avec ID=0;


			m_number_of_pions_moved = m_number_of_pions_moved + 1;
			m_str_pion_moved.Format(_T("%d"), m_number_of_pions_moved);
			UpdateData(FALSE);
				
																							// Mettre à jour la grille de jeu
			


			temp_pion.old_x = temp_pion.new_x;												//met a jour les coordonnes pour indiquer où se trouve le pion (old x,y) qui doit être analysé.  Ce qui correspond aussi à la grille de jeu 
			temp_pion.old_y = temp_pion.new_y;												// qui vient d'être mise à jour dans les opérations qui précèdent.


			if (dessineGrid)
			{
				leString.Format(_T("-5 CalculeMove_max: 6 Reset ID: %d -> 0 dans (x,y) (%d, %d) Niveau: %d "), temp_pion.ID, temp_pion.old_x, temp_pion.old_y, le_niveau);
				m_listBox_move.InsertString(-1, leString);

				leString.Format(_T("-6 CalculeMove_max: 6a Met ID %d dans (%d,  %d) Niveau: %d"), temp_pion.ID, temp_pion.new_x, temp_pion.new_y, le_niveau);
				m_listBox_move.InsertString(-1, leString);
				
				PrintGrid();
				UpdateWindow();
			};

			
			if (pionRemoved)
			{
					
				retire_pion_opposant = GridJeu.RetirePionCalcul(temp_pion);				// Retire un pion de la grille (ID=0) et met "pion_min.removed" = true dans le vecteurpionGrid approprié.  ID du pion retiré est temp_pion.remove_ID, ses coordonnées sont remove_x, remove_y
																						// retourne u  pion avec toute l'info sur le pion retiré.

				GridJeu.PushPionOnMoveVector(retire_pion_opposant);						// push le pion retiré dans le stack pour restauration future.


				if (dessineGrid)
				{
					leString.Format(_T("-7 CalculeMove_max Retiré pion du calcul ID: %d dans (%d, %d) Niveau: %d"), retire_pion_opposant.ID, retire_pion_opposant.old_x, retire_pion_opposant.old_y, le_niveau);
					m_listBox_move.InsertString(-1, leString);
					
					PrintGrid();

					UpdateWindow();
				};
	

			};  //Fin: if(temp_pion.removed)
			

			pion_return_minmax = CalculeMove_min(temp_pion, le_niveau, alpha, beta, pion_min);

		
			

			

			temp_pion = GridJeu.PopPionFromMoveVector();																	//on remet la grille comme avant de bourger le pion avant d'évaluer le prochain move ou pion.




			if (temp_pion.removed)																							// Remettre le pion retiré sur la grille de jeu.
			{

				GridJeu.AjoutPionGrid_old(temp_pion);																			// Ajout pion dans le jeu (dans vecteur des pions actifs) et ajoute dans gille de jeu[]
				GridJeu.AjustePionVectorGrid(temp_pion);
				
				if (dessineGrid)
				{

					leString.Format(_T("-9 CalculeMove_max Remet pion ID: %d dans (%d, %d) Niveau: %d"), temp_pion.ID, temp_pion.old_x, temp_pion.old_y, le_niveau);
					m_listBox_move.InsertString(-1, leString);

					PrintGrid();
					UpdateWindow();
				};

								
				temp_pion = GridJeu.PopPionFromMoveVector();									// récupérer le pion qui a fait le retrait.

			};  //FIN:  if (temp_pion.removed)
		
			GridJeu.AjoutPionGrid_old(temp_pion);												// Ajout pion dans le jeu (dans vecteur des pions actifs) et ajoute dans gille de jeu[]
			GridJeu.AjustePionVectorGrid(temp_pion);
			GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].ID = 0;							// ID=0 indique que la case est vide.

			

			if (dessineGrid)
			{

				leString.Format(_T("-10 CalculeMove_max Remet pion ID: %d dans (%d, %d) Niveau: %d"), temp_pion.ID, temp_pion.old_x, temp_pion.old_y, le_niveau);
				m_listBox_move.InsertString(-1, leString);

				PrintGrid();
				UpdateWindow();
			};

		} // FIN:  if (temp_pion.hasMoved)  code qui suit: ici le pion n'a pas bougé

		else

		{		// debut ELSE:  if (temp_pion.hasMoved)  code qui suit: ici le pion n'a pas bougé

			GridJeu.ComptePionsGrid();			// compte le nombre de pion de chaque joueur.

			pion_max.score = GridJeu.CalculScoreGrid(pion_max);

			if (pion_max.score > max_score)
			{
				max_score = pion_return_minmax.score;
				max_pion = pion_return_minmax.ID;
				max_move = pion_return_minmax.move;

			};

		};// FIN:  if (temp_pion.hasMoved)

		
		
			// CalculeMove_max
			// Mise à jour alpha, beta, score du pion.

	
				//*************************************
			if (dessineGrid)
			{
				leString.Format(_T("-11-CalculeMove_max: score: %d pour pion ID: %d"), pion_max.score, pion_max.ID);
				m_listBox_move.InsertString(-1, leString);

			};
			
			

			// CalculeMove_max ici
			if (pion_return_minmax.score > max_score)
			{
				max_score = pion_return_minmax.score;
				max_pion = pion_return_minmax.ID;
				max_move = pion_return_minmax.move;

			};

	

	}; // FIN: for (move = 0; move <= 1; move++)

	pion_return_minmax.score = max_score;
	pion_return_minmax.ID = max_pion ;
	pion_return_minmax.move = max_move;

	return pion_return_minmax;

};//FIN: calculMove_max




CGrid::pion CMFCDame3Dlg::CalculeMove_min(CGrid::pion &pion_max, int niveau, int alpha, int beta, CGrid::pion &lePion_min)
{
	// TODO: Add your implementation code here.
	//CalculeMovePionHumain_min(pion &pion, int niveau, int alpha, int beta)

	int v = 1000;
	
	CGrid::pion pion_return_minmax, pion_min, temp_pion,retire_pion_opposant;
		CString leString;

		int min_score = 1000;
		int min_pion = 0;
		int min_move = 0;
		int score, move, lePion, sizeVect,le_niveau,i;
		int removed_ID, removed_x, removed_y;
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
			pion_max.score = GridJeu.CalculScoreGrid(pion_max);						// pion_max sert a identifier quel est le joueur principal.  ID >0 -> ordi, ID < 0 - > humain
											   			
			return pion_max;

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

			
			if (!pion_min.removed)															// le pion est présent pion.removed = false;
			{
				
				// pour chaque move...

				for (move = 0; move < 2; move++)
				{
					

					switch (le_niveau-1) 
					{
					case 0:
						m_pion_max_ID.Format(_T("%d"), pion_max.ID);
						m_pion_max_move.Format(_T("%d"), move);
						m_number_of_moves = m_number_of_moves + 1;
						m_str_moves_total.Format(_T("%d"), m_number_of_moves);
						UpdateData(FALSE);
						break;

					case 1:
						m_pion_min_ID.Format(_T("%d"), pion_min.ID);
						m_pion_min_move.Format(_T("%d"), move);
						m_number_of_moves = m_number_of_moves + 1;
						m_str_moves_total.Format(_T("%d"), m_number_of_moves);
						UpdateData(FALSE);
						break;

					case 2:
						m_pion_max_ID_niv_3.Format(_T("%d"), pion_max.ID);
						m_pion_max_move_niv_3.Format(_T("%d"), move);
						m_number_of_moves = m_number_of_moves + 1;
						m_str_moves_total.Format(_T("%d"), m_number_of_moves);
						UpdateData(FALSE);
						break;

					case 3:
						m_pion_min_ID_niv_4.Format(_T("%d"), pion_min.ID);
						m_pion_min_move_niv_4.Format(_T("%d"), move);
						m_number_of_moves = m_number_of_moves + 1;
						m_str_moves_total.Format(_T("%d"), m_number_of_moves);
						UpdateData(FALSE);
						break;

					default:
						m_str_moves_total.Format(_T("%d"), m_number_of_moves);
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
																									//  Si le pion a bougé, alors...
					{
						if (temp_pion.removed)
						{
							pionRemoved = true;
							removed_ID = temp_pion.removed_ID;											//sauvegarde l'info sur le pion qui a peut-être été retiré
							removed_x = temp_pion.removed_x;
							removed_y = temp_pion.removed_y;

							temp_pion.removed = FALSE;													//changer la valeur avant de pousser le pion dans le vecteur des pions qui ont bougé.  Requis de mettre FALSE à ce pion parce que ce n'est pas lui qui a bougé.

						};

						GridJeu.PushPionOnMoveVector(temp_pion);										// pousse sur le vecteurMove le pion qui s'est déplacé.  "removed = false" ici, ce pion n'est pas celui qui est retiré
						GridJeu.AjustePionVectorGrid(temp_pion);										// Ajuste le pion dans le vecteur des pions.  Change ses coordonnées et met à jour l'info (new x,y) du pion.
						GridJeu.AjoutPionGrid_new(temp_pion);											// Ajoute le pion dans sa nouvelle postion (utilise new x,y pour ses coordonnées)
						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].ID = 0;						// Le pion quitte la case.  Indique comme vide avec ID=0;


						m_number_of_pions_moved = m_number_of_pions_moved + 1;							//augmente le compteur de mouvements, pour affichage ...
						m_str_pion_moved.Format(_T("%d"), m_number_of_pions_moved);
						UpdateData(FALSE);																// Mettre à jour l'affichage du nombre de move effectués.

						
						
						
						temp_pion.old_x = temp_pion.new_x;												//met a jour les coordonnes pour indiquer où se trouve le pion maintenant ("new x,y") qui doit être analysé.  Ce qui correspond aussi à la grille de jeu 
						temp_pion.old_y = temp_pion.new_y;												// qui vient d'être mise à jour dans les opérations qui précèdent.

						if (dessineGrid)
						{
							leString.Format(_T("5 CalculeMove_min: 6  Met ID %d -> 0 dans (%d, %d) Niveau: %d, move: %d "), temp_pion.ID, temp_pion.old_x, temp_pion.old_y, le_niveau, m_number_of_moves);
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
							lePion_min.old_x = temp_pion.old_x;
							lePion_min.old_y = temp_pion.old_y;
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
								leString.Format(_T("7 CalculeMove_min Retiré pion du calcul ID: %d dans (%d, %d) Niveau: %d "), retire_pion_opposant.ID, retire_pion_opposant.old_x, retire_pion_opposant.old_y, le_niveau);
								m_listBox_move.InsertString(-1, leString);

								PrintGrid();

								UpdateWindow();

							};

						};  // Fin: if (testremoved)

						pion_return_minmax = CalculeMove_max(pion_max, le_niveau, alpha, beta, lePion_min);

						// ici, on retourne de la fonction recursive (CalculeMove_max), on remet le jeu comme avant de bourger le pion avant d'évaluer le prochain move ou pion.

						temp_pion = GridJeu.PopPionFromMoveVector();


						if (temp_pion.removed) // Remettre le pion retiré sur la grille de jeu.
						{

							GridJeu.AjoutPionGrid_old(temp_pion);																// Ajout pion dans le jeu (dans vecteur des pions actifs) et ajoute dans gille de jeu[]
							GridJeu.AjustePionVectorGrid(temp_pion);															// pion retiré: ID est celle du pion retiré, removed_x,y: coordonnées du pion retiré.

							if (dessineGrid)
							{
								leString.Format(_T("8 CalculeMove_min Remet pion ID = %d dans (%d, %d) Niveau: %d"), temp_pion.ID, temp_pion.old_x, temp_pion.old_y, le_niveau);
								m_listBox_move.InsertString(-1, leString);

								PrintGrid();
								UpdateWindow();
							};

																																	// Remettre le pion dans la grille de jeu.

							temp_pion = GridJeu.PopPionFromMoveVector();																// récupérer le pion qui a fait le retrait.

						
						}; //FIN:  if (temp_pion.removed)

						GridJeu.AjoutPionGrid_old(temp_pion);												// Ajout pion dans le jeu (dans vecteur des pions actifs) et ajoute dans gille de jeu[]
						GridJeu.AjustePionVectorGrid(temp_pion);
						GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].ID = 0;							// ID=0 indique que la case est vide.

						
						if (pion_return_minmax.score < min_score)
						{
							min_score = pion_return_minmax.score;
							min_pion = pion_return_minmax.ID;
							min_move = pion_return_minmax.move;

						};
						
						if (dessineGrid)
						{
							leString.Format(_T("9 CalculeMove_min:  Met ID = 0  dans (%d, %d) Niveau: %d "), temp_pion.new_x, temp_pion.new_y, le_niveau);
							m_listBox_move.InsertString(-1, leString);

							leString.Format(_T("10 CalculeMove_min:  Met ID = %d dans (%d, %d) Niveau: %d "), temp_pion.ID, temp_pion.old_x, temp_pion.old_y, le_niveau);
							m_listBox_move.InsertString(-1, leString);

							PrintGrid();
							UpdateWindow();
						};



					} // Fin: if(hasMoved?)

					else

					{ // DEBUT: if (temp_pion.hasMoved) else...   ici le pion n'a pas bougé.
						
						GridJeu.ComptePionsGrid();																			// Ici, le pion n'a pas bougé.   On calcule le score de la situation.															
																															// compte le nombre de pion de chaque joueur.
						pion_min.score = GridJeu.CalculScoreGrid(pion_max);

						if (pion_min.score < min_score)
						{
							min_score = pion_min.score;
							min_pion = pion_min.ID;
							min_move = move;

						};


					};// FIN: if (temp_pion.hasMoved)

					

				}; // FIN: for (move = 0; move <= 1; move++)

					

			}  // FIN: if (!pionRetire)

			else

			{   // else: if (!pionRetire)
				GridJeu.ComptePionsGrid();			// Le pion a été retiré.  Calcule le score comme si le niveau max avait été atteint.

				pion_min.score = GridJeu.CalculScoreGrid(pion_max);

				if (pion_min.score < min_score)
				{
					min_score = pion_min.score;
					min_pion = pion_min.ID;
					min_move = 0;
				};

			};

		};  //FIN:  for (lePion = 0; lePion < sizeVect; lePion++)
		
	pion_return_minmax.score = min_score;
	pion_return_minmax.ID = pion_max.ID;
	pion_return_minmax.move = pion_max.move;

	return pion_return_minmax;  // retourne le pion avec son score.
		
};  // FIN: calculeMove_min

void CMFCDame3Dlg::PrintGrid()
{
	int i, j,k,l, ID, test;
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
			
			for (l = 0; l < 10; l++)

			{
				for (k = 0; k < 10; k++)
				{

					
					if ((i != k) || (j != l))
					{
						if (ID == GridJeu.grid_sub[k][l].ID)
						{
							if (ID != 0)
							{
								test = 1;
								leString.Format(_T("Doublon trouvé.  ID: %d, move: %d"), ID, m_number_of_moves);
								m_listBox_move.InsertString(-1, leString);

								m_ListBox_Suivi_Jeu.InsertString(-1, leString);
							};
						};
					};

				};
			};
			
		};
	};

};

void CMFCDame3Dlg::PrintScorePions()
{
	
	CGrid::pion lepion;
	CString leString;

	m_ListBox_Suivi_Jeu.InsertString(-1, _T("--------------"));

	lepion = GridJeu.TrouveBestPionOrdi();
	leString.Format(_T("Meilleur score ordi: ID %d,  score: %d,  move: %d."), lepion.ID, lepion.score, lepion.move);
	m_ListBox_Suivi_Jeu.InsertString(-1, leString);


	lepion = GridJeu.TrouveBestPionHumain();
	leString.Format(_T("Meilleur score humain: ID %d,  score: %d,  move: %d."), lepion.ID, lepion.score, lepion.move);
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
	int i, nombre_coups;

	UpdateData(TRUE);

	nombre_coups = _ttoi(m_nbre_coups);

	for (i = 0; i < nombre_coups; i++)
	{
		
		OnBnClickedOrdiJoueButton();
		OnBnClickedHumainJoueButton();
		m_nbre_coups.Format(_T("%d"), nombre_coups-i);
		UpdateData(FALSE);
	};
	
	
	// TODO: Add your control notification handler code here
}
