
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
}

BEGIN_MESSAGE_MAP(CMFCDame3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Init_BUTTON, &CMFCDame3Dlg::OnClickedInitButton)
	ON_BN_CLICKED(IDC_Reset_BUTTON, &CMFCDame3Dlg::OnClickedResetButton)
	ON_BN_CLICKED(IDC_calcul_score_initial_BUTTON, &CMFCDame3Dlg::OnClickedCalculScoreInitialButton)
	ON_BN_CLICKED(IDC_calcul_score_grid_sub_BUTTON, &CMFCDame3Dlg::OnClickedCalculScoreGridSubButton)
	ON_BN_CLICKED(IDC_evalueMove_BUTTON, &CMFCDame3Dlg::OnBnClickedevaluemoveButton)
	ON_BN_CLICKED(IDC_ORDI_JOUE_BUTTON, &CMFCDame3Dlg::OnBnClickedOrdiJoueButton)
	ON_BN_CLICKED(IDC_HUMAIN_JOUE_BUTTON, &CMFCDame3Dlg::OnBnClickedHumainJoueButton)
	ON_BN_CLICKED(IDC_UPT_NIVEAU, &CMFCDame3Dlg::OnBnClickedUptNiveau)
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

	m_number_of_moves = 0;
	m_number_of_pions_moved = 0;
	m_BOOL_DessineGrid = true;

		
	m_str_moves_total.Format(_T("%d"), m_number_of_moves);
	m_str_pion_moved.Format(_T("%d"), m_number_of_pions_moved);

	m_str_MaxNiveau.Format(_T("%d"),GridJeu.max_niveau);

	UpdateData(FALSE);

	UpdateData(TRUE);

	//GridJeu.max_niveau.Format("%d", m_str_MaxNiveau);

	
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

	GridJeu.CloneGridMainToSub();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Clone grid_main vers grid_sub"));

	GridJeu.ResetScorePions();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Reset score des pions"));

	OnClickedCalculScoreInitialButton();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Calcul du score initial (nombre de pions de chaque joueur)"));

	OnClickedCalculScoreGridSubButton();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Calcule le score de la grille grid_sub "));


	GridJeu.ResetPionVectorGrid();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Reset vecteur de pion de la grille de jeu"));

	int i=0;
	i = i + 1;

}


void CMFCDame3Dlg::OnClickedResetButton()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	GridJeu.max_niveau = _ttoi(m_str_MaxNiveau);

	
	m_number_of_moves = 0;
	m_number_of_pions_moved = 0;

	m_str_moves_total.Format(_T("%d"), m_number_of_moves);
	m_str_pion_moved.Format(_T("%d"), m_number_of_pions_moved);
	m_str_MaxNiveau.Format(_T("%d"), GridJeu.max_niveau);


	UpdateData(FALSE);

	

	


	m_ListBox_Suivi_Jeu.ResetContent();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Reset de la liste de suivi du jeu"));

	m_listBox_move.ResetContent();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Reset de la liste des calculs de mouvement"));

	m_ListBox_Suivi_Jeu.InsertString(-1, _T("--------------"));
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Reset Jeu"));

	GridJeu.CreatePionsOrdi();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Crée pions ordi"));

	GridJeu.CreatePionHumain();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Crée pions humain"));

	GridJeu.TransferTousPionToGrid();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Transfer pions vers grille grid_main"));

	GridJeu.CloneGridMainToSub();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Clone grid_main vers grid_sub"));

	GridJeu.ResetScorePions();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Reset score des pions"));
	
	OnClickedCalculScoreInitialButton();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Calcul du score initial (nombre de pions de chaque joueur)"));

	OnClickedCalculScoreGridSubButton();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Calcule le score de la grille grid_sub "));

	
	GridJeu.ResetPionVectorGrid();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Reset vecteur de pion de la grille de jeu"));

	

	int i = 0;
	i = i + 1;
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
	
	

	

	if (m_BOOL_DessineGrid)
	{
		
		leString.Format(_T("1-OnClickButton Début analyse ordi"));

		m_listBox_move.InsertString(-1, leString);

		leString.Format(_T("2-OnBnClickedOrdiJoueButton: config initiale"));
		m_listBox_move.InsertString(-1, leString);

		PrintGrid();
		UpdateWindow();
	};

	


	
	for (pionID = 0; pionID < sizeVect; pionID++)						//Pour tous les pions qui sont encore dans le jeu, calculer le meilleur pion à bouger.
	{
		my_pion_max = GridJeu.GetPionFromVectOrdi(pionID);					//Obtient un pion du vecteur	

		leString.Format(_T("    "));
		m_ListBox_Suivi_Jeu.InsertString(-1, leString);					// insere une ligne vide pour affichage plus facilement lisible.


		
																		
			
		my_pion_min.ID = 0;
		my_pion_min.old_x = 0;
		my_pion_min.old_y = 0;
		my_pion_min.new_x = 0;
		my_pion_min.new_y = 0;


		minimax_pion = CalculeMove_max(my_pion_max, le_niveau, alpha, beta, my_pion_min);	// minimax_pion est le résultat de l'évaluation complétée pour les mouvements de ce pion.
		
																			// ici le pion n'a pu bouger.  Donc pas de score valide.
		
		GridJeu.SetPionScore(minimax_pion);
																			// Une fois tous les pions évalués.  On choisit le meilleur pion à bouger
		

	};  // FIN : for (pionID = 0; pionID < sizeVect; pionID++)

	PrintScorePions();
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
	
	
	
	leString.Format(_T("1-OnClickButton Début analyse humain"));
	m_ListBox_Suivi_Jeu.InsertString(-1, leString);

	for (pionID = 0; pionID < sizeVect; pionID++)
	{
		my_pion_max = GridJeu.GetPionFromVectHumain(pionID);					//retourne le pion "humain" pion(pionID)

		leString.Format(_T("    "));
		m_ListBox_Suivi_Jeu.InsertString(-1, leString);						// insere une ligne vide pour affichage plus facilement lisible.

		

		minimax_pion = CalculeMove_max(my_pion_max, le_niveau, alpha, beta, my_pion_min);	// minimax_pion est le résultat de l'évaluation complétée pour les mouvements de ce pion.


		GridJeu.SetPionScore(minimax_pion);

																			// on met à jour le score pour ce pion

	}; // FIN: for (pionID = 0; pionID < sizeVect; pionID++)


	PrintScorePions();
};

CGrid::pion CMFCDame3Dlg::CalculeMove_max(CGrid::pion &pion_max, int niveau, int alpha, int beta, CGrid::pion &pion_min)
{
	// TODO: Add your implementation code here.


	int v = -1000;
	CGrid::pion pion_return_minmax, temp_pion, retire_pion_opposant;
	CString leString;
	int sizeVectPionRetire = 0;
	int sizeVectorMovePion = 0;

	int le_niveau = niveau;
	
	int move,  i;

	bool pionRetire;

	

	//**************************************************************************************************

	le_niveau = le_niveau + 1;

	if (le_niveau == 5)
	{
		int z = 0;
		z = z + 1;

	};

	//**************************************************************************************************

	// VERIFIE SI LE PION EST TOUJOURS PRESENT DANS LA GRILLE DE JEU :

	sizeVectPionRetire = GridJeu.pion_vecteur_retire_calcul.size();			// est-ce que le vecteur des "pions retirés" est vide?  SI oui, aucun pion retiré et on continue. Si NON, alors on vérifie que notre pion est toujours en jeu.
	pionRetire = false;

	if (sizeVectPionRetire > 0)												// Vu que des pions ont été retirés, vérifie si le pion sur lequel on travaille est toujours sur la grille de  jeu.
	{
		// initialisation initiale  à "FALSE" la variable de contrôle pour la découverte d'un pion retiré.

		for (i = 0; i < sizeVectPionRetire; i++)							//Pour chaque pions retiré dans la liste
		{
			if (GridJeu.pion_vecteur_retire_calcul.at(i).ID == pion_max.ID)
			{
				pionRetire = true;											//Le pion correspond à un pion retiré du jeu, alors la variable de contrôle devient "TRUE" (on travaille sur un pion retiré).

				
			}; // FIN:if (GridJeu.pion_vecteur_retire_calcul.at(i).ID == pion.ID) 
		}; // FIN: for (i = 0; i < sizeVectPionRetire; i++)
	}; // FIN:  if (sizeVectPionRetire > 0)

	//************************************************************************************************

	if ((le_niveau > GridJeu.max_niveau) || pionRetire)
	{


		if (m_BOOL_DessineGrid)
		{
			leString.Format(_T("-1-CalculeMove_max  niveau max atteint. Niv.: %d:  "), le_niveau - 1);  //retire 1 au niveau pour afficher le niveau max atteint sans dépasser.
			m_listBox_move.InsertString(-1, leString);

		};
		
		

		GridJeu.CalculScoreGrid();			// compte le nombre de pion de chaque joueur.

		// SI L'ORDI JOUE, LA FORMULE DE CALCUL DU POINTAGE EST:
		if (pion_max.ID > 0)
		{
			pion_max.score = (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum()) - (GridJeu.GetScoreGridOrdi() - GridJeu.GetScoreInitialOrdi());
			// score = +humains retirés - ordis retirés

			if (pion_max.score < 0)
			{
				leString.Format(_T("-2 -CalculeMove_max score < 0, pion ID: %d, niveau: %d, move: %d "), pion_max.ID, le_niveau, m_number_of_moves);
				m_listBox_move.InsertString(-1, leString);

				PrintGrid();
				UpdateWindow();
			};

		};


		// SI L'HUMAIN JOUE, LA FORMULE DE CALCUL DU POINTAGE DEVIENT:
		if (pion_max.ID < 0)
		{
			pion_max.score = (GridJeu.GetScoreInitialOrdi() - GridJeu.GetScoreGridOrdi()) - (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum());
			// score = +ordis retirés  - humains retirés

			if (pion_max.score < 0)
			{
				leString.Format(_T("-3 -CalculeMove_max score < 0, pion ID: %d, niveau: %d, move: %d "), pion_max.ID, le_niveau, m_number_of_moves);
				m_listBox_move.InsertString(-1, leString);

				PrintGrid();
				UpdateWindow();
			};
		};

		
		if (m_BOOL_DessineGrid)
		{
			leString.Format(_T("-4 -CalculeMove_max: score: %d pour pion ID: %d"), pion_max.score, pion_max.ID);
			m_listBox_move.InsertString(-1, leString);

		};


		
		return pion_max;															// ici, on n'a rien changé au pion, donc on retourne.

	};  // fin: if (niveau > GridJeu.max_niveau)

	//*****************************************************************************************************

	// Ici, niveau < max et pion present dans grille de jeu.

	sizeVectorMovePion = GridJeu.vector_move_pion.size();							//Vérifie si le pion a bougé: encore à son origine?
	
	if (sizeVectorMovePion > 0)														// Vu que des pions ont bougé, vérifie si le pion sur lequel on travaille a bougé.
	{

		for (i = sizeVectorMovePion - 1; i >= 0; i--)								//Pour chaque pions retiré dans la liste des pions déplacés...
		{
			if (GridJeu.vector_move_pion.at(i).ID == pion_max.ID)					// Si le pion qu'on joue est dans la liste des pions bougés, alors ajuste les coordonnées de my_pion;
			{
				pion_max.new_x = GridJeu.vector_move_pion.at(i).new_x;
				pion_max.new_y = GridJeu.vector_move_pion.at(i).new_y;
				i = -1;
			};

		};
	};


	for (move = 0; move <= 1; move++)  // move 0: +x, +y; move 1: -x,+y; move 2: +x, -y; move 3: -x, -y;
	{
		
			
		m_number_of_moves = m_number_of_moves + 1;

		/*if (m_number_of_moves > 124)
		{
			int w = 0;
			w = w + 1;
			m_BOOL_DessineGrid = true;
			PrintGrid();
			UpdateWindow();

		};*/
						
		m_str_moves_total.Format(_T("%d"), m_number_of_moves);

		UpdateData(FALSE);
			
			

		pion_max.old_x = pion_max.new_x;				// si le pion n'a pas encore bougé alors old = new.   Donc ceci ne change rien.
		pion_max.old_y = pion_max.new_y;				// si le pion a bougé, alors il faut corriger old pour que le calcul du mouvement se fasse à partir des bonnes coordonnées. old= référence pour calcul.

		temp_pion = GridJeu.EvalueMove(pion_max, GridJeu.delta_x, GridJeu.delta_y, le_niveau, move);

		GridJeu.PushPionOnMoveVector(temp_pion);  // sauve la config du pion.  new x,y contient destination.  old x,y : origine, new x,y : nouvelle case.

		if (temp_pion.hasMoved)
		{
				
			m_number_of_pions_moved = m_number_of_pions_moved + 1;
			m_str_pion_moved.Format(_T("%d"), m_number_of_pions_moved);
			UpdateData(FALSE);
				
																								// Mettre à jour la grille de jeu
			GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].ID = 0;						// Le pion quitte la case.  Indique comme vide avec ID=0;

			GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].ID = temp_pion.ID;

					
			

			if (m_BOOL_DessineGrid)
			{
				leString.Format(_T("-5 CalculeMove_max: 6 Reset ID: %d -> 0 dans (x,y) (%d, %d) Niveau: %d "), temp_pion.ID, temp_pion.old_x, temp_pion.old_y, le_niveau);
				m_listBox_move.InsertString(-1, leString);

				leString.Format(_T("-6 CalculeMove_max: 6a Met ID %d dans (%d,  %d) Niveau: %d"), temp_pion.ID, temp_pion.new_x, temp_pion.new_y, le_niveau);
				m_listBox_move.InsertString(-1, leString);
				
				PrintGrid();
				UpdateWindow();
			};

			
			if (temp_pion.removed)
			{
					// Si ce pion a capturé un pion ennemi (temp_pion.removed = TRUE), alors retire le pion de la grille de jeu. 
					//Sauvegarde dans stack pour restauration future...



				retire_pion_opposant.ID = GridJeu.grid_sub[temp_pion.removed_x][temp_pion.removed_y].ID;
				retire_pion_opposant.removed = true;
				retire_pion_opposant.removed_x = temp_pion.removed_x;
				retire_pion_opposant.removed_y = temp_pion.removed_y;

				GridJeu.PushPionOnMoveVector(retire_pion_opposant);			// push le pion dans le stack pour restauration future.

				GridJeu.RetirePionCalcul(retire_pion_opposant);			// Retire pion de la grille et ajoute au vecteur des pions retirés.

				


				if (m_BOOL_DessineGrid)
				{
					leString.Format(_T("-7 CalculeMove_max Retiré pion du calcul ID: %d dans (%d, %d) Niveau: %d"), retire_pion_opposant.ID, retire_pion_opposant.old_x, retire_pion_opposant.old_y, le_niveau);
					m_listBox_move.InsertString(-1, leString);
					
					PrintGrid();

					UpdateWindow();
				};

				

					

			};  //Fin: if(temp_pion.removed)

		};  //FIN: if (hasMoved)
		



			pion_return_minmax = CalculeMove_min(temp_pion, le_niveau, alpha, beta, pion_min);
																															 
																													
			//PLANTE ICI +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

			temp_pion = GridJeu.PopPionFromMoveVector();																	//on remet la grille comme avant de bourger le pion avant d'évaluer le prochain move ou pion.

			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



			if (temp_pion.niveau != le_niveau)
			{
				

				if (m_BOOL_DessineGrid)
				{

					leString.Format(_T("-8 CalculeMove_max: PopPionFromMoveVector pion.%d.niveau (%d) <> niveau: %d  "), temp_pion.ID, temp_pion.niveau, le_niveau);
					m_listBox_move.InsertString(-1, leString);
				};

			};


			if (temp_pion.removed)																					// Remettre le pion retiré sur la grille de jeu.
				{

	

					GridJeu.AjoutPionCalcul(temp_pion);																// Ajout pion dans le jeu (dans vecteur des pions actifs) et ajoute dans gille de jeu[]

					


					if (m_BOOL_DessineGrid)
					{
						
						leString.Format(_T("-9 CalculeMove_max Remet pion ID: %d dans (%d, %d) Niveau: %d"), temp_pion.ID, temp_pion.old_x, temp_pion.old_y, le_niveau);
						m_listBox_move.InsertString(-1, leString);

						PrintGrid();
						UpdateWindow();
					};

				
					
					

					// Remettre le pion dans la grille de jeu.

					temp_pion = GridJeu.PopPionFromMoveVector(); // récupérer le pion qui a fait le retrait.



				};


				// Ici le pion a bougé et on le remet à sa position originale.

			if (temp_pion.hasMoved)
			{
				GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].ID = 0;						// ID=0 indique que la case est vide.
				GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].ID = temp_pion.ID;

				if (m_BOOL_DessineGrid)
				{
					leString.Format(_T("9 CalculeMove_min:  Met ID = 0  dans (%d, %d) Niveau: %d "), temp_pion.new_x, temp_pion.new_y, le_niveau);
					m_listBox_move.InsertString(-1, leString);

					leString.Format(_T("10 CalculeMove_min:  Met ID = %d dans (%d, %d) Niveau: %d "), temp_pion.ID, temp_pion.old_x, temp_pion.old_y, le_niveau);
					m_listBox_move.InsertString(-1, leString);

					PrintGrid();
					UpdateWindow();
				};

			}
			else
			{
				if (m_BOOL_DessineGrid)
				{
					leString.Format(_T("9 CalculeMove_min:  Pion n'a pas bougé: ID= %d  dans (%d, %d) Niveau: %d "), temp_pion.ID, temp_pion.new_x, temp_pion.new_y, le_niveau);
					m_listBox_move.InsertString(-1, leString);

					PrintGrid();
					UpdateWindow();
				};
			};
			

			
			if (m_BOOL_DessineGrid)
			{
				
				leString.Format(_T("-10 CalculeMove_max Remet pion ID: %d dans (%d, %d) Niveau: %d"), temp_pion.ID, temp_pion.old_x, temp_pion.old_y, le_niveau);
				m_listBox_move.InsertString(-1, leString);

				PrintGrid();
				UpdateWindow();
			};

		

			// Mise à jour alpha, beta, score du pion.
			if (pion_return_minmax.score > v)
			{
				v = pion_return_minmax.score;
			};

			if (pion_return_minmax.score >= beta)
			{
				pion_return_minmax.score = v;
					
			};

			if (pion_return_minmax.score > alpha)
			{
				alpha = pion_return_minmax.score;
			};


				//*************************************
			if (m_BOOL_DessineGrid)
			{
				leString.Format(_T("-11-CalculeMove_max: score: %d pour pion ID: %d"), pion_max.score, pion_max.ID);
				m_listBox_move.InsertString(-1, leString);

			};
			
			

			
	

		}; // FIN: for (move = 0; move <= 1; move++)

		return pion_return_minmax;

};//FIN: calculMove_max




CGrid::pion CMFCDame3Dlg::CalculeMove_min(CGrid::pion &pion_max, int niveau, int alpha, int beta, CGrid::pion &pion_min)
{
	// TODO: Add your implementation code here.
	//CalculeMovePionHumain_min(pion &pion, int niveau, int alpha, int beta)

	int v = 1000;
	
	CGrid::pion pion_return_minmax, my_pion, temp_pion,retire_pion_opposant;
		CString leString;

		int score, move, lePion, sizeVect,le_niveau,i,j,k;
		
		sizeVect = 0;
		score = 0;
		int sizeVectPionRetire = 0;
		int sizeVectorMovePion = 0;
		bool pionRetire = false;
		bool testRemoved = false;

		
		le_niveau = niveau;
		

		

		//********************************************************************************************
		le_niveau = le_niveau + 1;

		if (le_niveau > GridJeu.max_niveau)
		{
			
			if (m_BOOL_DessineGrid)
			{
				leString.Format(_T("1-CalculeMove_min Niveau max atteint: niveau: %d"), le_niveau);
				m_listBox_move.InsertString(-1, leString);

			};
			
			
			
			GridJeu.CalculScoreGrid();			// compte le nombre de pion de chaque joueur.

			// SI L'ORDI JOUE, LA FORMULE DE CALCUL DU POINTAGE EST:
			if (pion_max.ID > 0)
			{
				pion_max.score = (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum()) - (GridJeu.GetScoreGridOrdi() - GridJeu.GetScoreInitialOrdi());

				if (pion_max.score < 0)
				{
					leString.Format(_T("2-CalculeMove_max score < 0, pion ID: %d, niveau: %d, move: %d "), pion_max.ID, le_niveau, m_number_of_moves);
					m_listBox_move.InsertString(-1, leString);
				
					PrintGrid();
					UpdateWindow();
				};
			};


			// SI L'HUMAIN JOUE, LA FORMULE DE CALCUL DU POINTAGE DEVIENT:
			if (pion_max.ID < 0)
			{
				pion_max.score = (GridJeu.GetScoreInitialOrdi() - GridJeu.GetScoreGridOrdi()) - (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum());
				
				if (pion_max.score < 0)
				{
					leString.Format(_T("3-CalculeMove_max score < 0, pion ID: %d, niveau: %d, move: %d "), pion_max.ID, le_niveau, m_number_of_moves);
					m_listBox_move.InsertString(-1, leString);
					PrintGrid();
					UpdateWindow();

				};
			};

			if (pion_max.score != 0)
			{
				
				
				

				if (m_BOOL_DessineGrid)
				{
					leString.Format(_T("4-CalculeMove_max: score: %d pour pion ID: %d"), pion_max.score, pion_max.ID);
					m_listBox_move.InsertString(-1, leString);

				};
				
				

			};
			
			
								   			
			return pion_max;

		};	// Fin : if (le_niveau > GridJeu.max_niveau)
		
		//***************************************************************************************


		if (pion_max.ID > 0)											// ID du pion.  ID > 0 = ordi. ID < 0 = humain (l'autre  joueur).
		{
			sizeVect = GridJeu.GetPionVectHumSize();				// Trouve la dimension du vecteur Humain (qui est l'opposant de l'ordi ici)
		};

		if (pion_max.ID < 0)
		{
			sizeVect = GridJeu.GetPionVectOrdiSize();				// Trouve la dimension du vecteur ordi (qui est l'opposant de l'humain ici)
		};


		// pour chaque pion...

		for (lePion = 0; lePion < sizeVect; lePion++)				// Boucle pour évaluer les pions du joueur
		{
			
			if (pion_max.ID > 0)
			{
				my_pion = GridJeu.GetPionFromGridHumain(lePion);	// Va chercher un pion de l'adversaire. 
			};

			if (pion_max.ID < 0)
			{
				my_pion = GridJeu.GetPionFromGridOrdi(lePion);
			};



																					

			sizeVectPionRetire = GridJeu.pion_vecteur_retire_calcul.size();			// Verifie si pion est toujours présent dans le jeu.

			if (sizeVectPionRetire > 0)												// Vu que des pions ont été retirés, vérifie si le pion sur lequel on travaille est toujours sur la grille de  jeu.
			{

				pionRetire = false;													// initialisation initiale  à "FALSE" la variable de contrôle pour la découverte d'un pion retiré.

				for (i = 0; i < sizeVectPionRetire; i++)							//Pour chaque pions retiré dans la liste
				{
					if (GridJeu.pion_vecteur_retire_calcul.at(i).ID == my_pion.ID)
					{
						pionRetire = true;											//Le pion correspond à un pion retiré du jeu, alors la variable de contrôle devient "TRUE" (on travaille sur un pion retiré).

						
					};

				};
			};





			if (!pionRetire)															// le pion est présent
			{

				sizeVectorMovePion = GridJeu.vector_move_pion.size();					//Vérifie si le pion a bougé: encore à son origine?

				if (sizeVectorMovePion > 0)												// Vu que des pions ont bougé, vérifie si le pion sur lequel on travaille a bougé.
				{

					for (i = sizeVectorMovePion-1; i >= 0 ; i--)							//Pour chaque pions retiré dans la liste des pions déplacés...
					{
						if (GridJeu.vector_move_pion.at(i).ID == my_pion.ID)			// Si le pion qu'on joue est dans la liste des pions bougés, alors ajuste les coordonnées de my_pion;
						{
							my_pion.new_x = GridJeu.vector_move_pion.at(i).new_x;		
							my_pion.new_y = GridJeu.vector_move_pion.at(i).new_y;
							i = -1;
						};

					};
				};

				/*if (my_pion.ID == pion_min.ID)
				{
					
					my_pion.new_x = pion_min.new_x;
					my_pion.new_y = pion_min.new_y;


				};*/
				
				// pour chaque move...

				for (move = 0; move <= 1; move++)
				{
					
					m_number_of_moves = m_number_of_moves + 1;

					/*if (m_number_of_moves > 124)
					{
						int w = 0;
						w = w + 1;
						m_BOOL_DessineGrid = true;
						PrintGrid();
						UpdateWindow();
					};

*/
					m_str_moves_total.Format(_T("%d"), m_number_of_moves);

					UpdateData(FALSE);

					my_pion.old_x = my_pion.new_x;
					my_pion.old_y = my_pion.new_y;


					temp_pion = GridJeu.EvalueMove(my_pion, GridJeu.delta_x, GridJeu.delta_y, le_niveau, move);
					// EvalueMove retourne un pion avec les nouvelles coordonnées dans new_x, new_y si le pion a bougé.
					// temp.pion.removed = true indique qu'on a mangé un pion ennemi.  new_x, new_y pointe alors sur la case vide, après le pion mangé.

					
					GridJeu.PushPionOnMoveVector(temp_pion);

					if (temp_pion.hasMoved)

						//  Si le pion a bougé, alors...
					{

						m_number_of_pions_moved = m_number_of_pions_moved + 1;							//augmente le compteur de mouvements, pour affichage ...
						m_str_pion_moved.Format(_T("%d"), m_number_of_pions_moved);

						UpdateData(FALSE);																// Mettre à jour l'affichage du nombre de move effectués.


						//testRemoved = temp_pion.removed;	// sauvegarde le paramètre: "removed" 
						//temp_pion.removed = false;

						//move pion - moveStack push;   sauve info sur le move du pion.
						

						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].ID = 0;						// indique que l'ancienne position est maintenant libre (ID=0)

						GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].ID = temp_pion.ID;			//Met à jour la grille avec la nouvelle position du pion.
						GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].removed = false;
						GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].new_x = temp_pion.new_x;		// coordonnees X (destination lors d'un déplacement)
						GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].new_y = temp_pion.new_y;		// coordonnees Y
						GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].old_x = temp_pion.old_x;		// coordonnees X (destination lors d'un déplacement)
						GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].old_y = temp_pion.old_y;		// coordonnees Y
						GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].dame = temp_pion.dame;		// si le pion devient une dame, alors dame = TRUE;
						GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].score = temp_pion.score;		// score calculé pour ce pion (évaluation minimax)
						GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].move = temp_pion.move;


						

						if (m_BOOL_DessineGrid)
						{
							leString.Format(_T("5 CalculeMove_min: 6  Met ID %d -> 0 dans (%d, %d) Niveau: %d, move: %d "), temp_pion.ID, temp_pion.old_x, temp_pion.old_y, le_niveau, m_number_of_moves);
							m_listBox_move.InsertString(-1, leString);

							leString.Format(_T("6 CalculeMove_min: 6a Met ID %d      dans (%d, %d) Niveau: %d "), temp_pion.ID, temp_pion.new_x, temp_pion.new_y, le_niveau);
							m_listBox_move.InsertString(-1, leString);
							
							PrintGrid();
							UpdateWindow();
						};

						
						

					};

					if (le_niveau == 2)
					{
						pion_min.ID = temp_pion.ID;
						pion_min.new_x = temp_pion.new_x;
						pion_min.new_y = temp_pion.new_y;

					};

						

						
						
						
					if (temp_pion.removed)												// Si ce pion a capturé un pion ennemi (.removed = TRUE), alors retire le pion ennemi du grid. 
																						//Sauvegarde dans stack pour restauration future...
					{

						retire_pion_opposant.ID = GridJeu.grid_sub[temp_pion.removed_x][temp_pion.removed_y].ID;
						retire_pion_opposant.removed = true;
						retire_pion_opposant.removed_x = temp_pion.removed_x;
						retire_pion_opposant.removed_y = temp_pion.removed_y;

						GridJeu.PushPionOnMoveVector(retire_pion_opposant);														// push le pion dans le stack pour restauration future.
																																// L'ordre des moves sauvés sur le stack: 
																																// Met à jour la grille de  jeu: ID=0 -> old x,y

							//Retire  le pion de la grille de jeu et du vecteur des pions de la grille pour continuer l'évaluation du jeu.
							//GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y] = 0 + retire pion du vecteurGrid

						GridJeu.RetirePionCalcul(retire_pion_opposant);														// Retire pion de la grille et du vecteur pion approprié.


							if (m_BOOL_DessineGrid)
							{
							leString.Format(_T("7 CalculeMove_min Retiré pion du calcul ID: %d dans (%d, %d) Niveau: %d "), retire_pion_opposant.ID, retire_pion_opposant.old_x, retire_pion_opposant.old_y, le_niveau);
							m_listBox_move.InsertString(-1, leString);

							};
							
							

							

					};  // Fin: if (testremoved)

						
						
						
						
						
					pion_return_minmax = CalculeMove_max(pion_max, le_niveau, alpha, beta, pion_min);

						
						// ici, on retourne de la fonction recursive (CalculeMove_max), on remet le jeu comme avant de bourger le pion avant d'évaluer le prochain move ou pion.

					temp_pion = GridJeu.PopPionFromMoveVector();


					if (temp_pion.removed) // Remettre le pion retiré sur la grille de jeu.
						{

							GridJeu.AjoutPionCalcul(temp_pion);																// Ajout pion dans le jeu (dans vecteur des pions actifs) et ajoute dans gille de jeu[]


							if (m_BOOL_DessineGrid)
							{
								leString.Format(_T("8 CalculeMove_min Remet pion ID = %d dans (%d, %d) Niveau: %d"), temp_pion.ID, temp_pion.old_x, temp_pion.old_y, le_niveau);
								m_listBox_move.InsertString(-1, leString);

								PrintGrid();
								UpdateWindow();
							};

							

							// Remettre le pion dans la grille de jeu.

						temp_pion = GridJeu.PopPionFromMoveVector(); // récupérer le pion qui a fait le retrait.



						};

						// Ici le pion a bougé et on le remet à sa position originale.

					if (temp_pion.hasMoved)
					{
						GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].ID = 0;						// ID=0 indique que la case est vide.
						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].ID = temp_pion.ID;

						if (m_BOOL_DessineGrid)
						{
							leString.Format(_T("9 CalculeMove_min:  Met ID = 0  dans (%d, %d) Niveau: %d "), temp_pion.new_x, temp_pion.new_y, le_niveau);
							m_listBox_move.InsertString(-1, leString);

							leString.Format(_T("10 CalculeMove_min:  Met ID = %d dans (%d, %d) Niveau: %d "), temp_pion.ID, temp_pion.old_x, temp_pion.old_y, le_niveau);
							m_listBox_move.InsertString(-1, leString);

							PrintGrid();
							UpdateWindow();
						};

					}
					else
					{
						if (m_BOOL_DessineGrid)
						{
							leString.Format(_T("9 CalculeMove_min:  Pion n'a pas bougé: ID= %d  dans (%d, %d) Niveau: %d "),temp_pion.ID, temp_pion.new_x, temp_pion.new_y, le_niveau);
							m_listBox_move.InsertString(-1, leString);

							PrintGrid();
							UpdateWindow();
						};

					};// FIN: if (temp_pion.hasMoved)
					

						// Mise à jour alpha, beta, score du pion.
					if (pion_return_minmax.score < v)
						{
							v = pion_return_minmax.score;
						};

						if (pion_return_minmax.score <= alpha)
						{
							pion_return_minmax.score = v;
						};

						if (pion_return_minmax.score < beta)
						{
							beta = pion_return_minmax.score;
						}; 

				}; // FIN: for (move = 0; move <= 1; move++)

					

			};  // FIN: if (!pionRetire)

		
		};  //FIN:  for (lePion = 0; lePion < sizeVect; lePion++)

			
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
