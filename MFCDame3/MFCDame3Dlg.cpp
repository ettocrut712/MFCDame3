
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
	DDX_Control(pDX, IDC_MOVE_LIST, m_listBox_move);
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
	CGrid::pion my_pion;
	CGrid::pion m_pion_evalue;

	int niveau = 0;
	int move;
	int sizeVect;
	CString leString;
	
	auto pGrid = &CGrid::grid_sub;

	sizeVect = GridJeu.GetPionVectOrdiSize();
	


	for (pionID = 0; pionID < sizeVect; pionID++)
	{
		my_pion = GridJeu.GetPionFromVectOrdi(pionID);

		
		
		for (move = 0; move <=3; move++)			// changer le 2 en fonction du type de pion: dame = 4 moves.  Pion -> 2 moves max.
		{
			m_pion_evalue = GridJeu.EvalueMove( my_pion, GridJeu.delta_x, GridJeu.delta_y, niveau, move);
			
			leString.Format(_T("Pion: %d ,  move: %d .  Resultat: %d"), my_pion.ID, move, m_pion_evalue.move);
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);


		};
	};

	sizeVect = GridJeu.GetPionVectHumSize();



	for (pionID = 0; pionID < sizeVect; pionID++)
	{
		my_pion = GridJeu.GetPionFromVectHumain(pionID);



		for (move = 0; move <= 3; move++)			// changer le 2 en fonction du type de pion: dame = 4 moves.  Pion -> 2 moves max.
		{
			m_pion_evalue = GridJeu.EvalueMove(my_pion, GridJeu.delta_x, GridJeu.delta_y, niveau, move);


			leString.Format(_T("Pion: %d ,  move: %d .  Resultat: %d"), my_pion.ID, move, m_pion_evalue.move);
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);


		};
	};


}


void CMFCDame3Dlg::OnBnClickedOrdiJoueButton()
{
	// TODO: Add your control notification handler code here

	int pionID;
	CGrid::pion my_pion, minimax_pion;
	

	int le_niveau = 0;
	
	int sizeVect;
	CString leString;

	sizeVect = GridJeu.GetPionVectOrdiSize();

	GridJeu.ResetScorePions();

	int alpha = -1000;
	int beta = 1000;
	unsigned int i;
	int sizeVectPionRetire;
	bool pionRetire = false;


	for (pionID = 0; pionID < sizeVect; pionID++)						//Pour tous les pions qui sont encore dans le jeu, calculer le meilleur pion à bouger.
	{
		my_pion = GridJeu.GetPionFromVectOrdi(pionID);					//Obtient un pion du vecteur	

		leString.Format(_T("    "));
		m_ListBox_Suivi_Jeu.InsertString(-1, leString);					// insere une ligne vide pour affichage plus facilement lisible.


		leString.Format(_T("1-OnClickButton ordi: Pion %d de %d ,   ID: %d, niveau %d, position (x,y): (%d, %d)"), pionID + 1, sizeVect, my_pion.ID, le_niveau, my_pion.old_x, my_pion.old_y);
		m_ListBox_Suivi_Jeu.InsertString(-1, leString);
		// pionID+1: pour corriger l'affichage.  Sinon affiche 0 pour le 1er pion traité.

		sizeVectPionRetire = GridJeu.pion_vecteur_retire_calcul.size();	//Obtient le nombre de pions qui ont été retirés (size du vecteur = nombre de pions)

		if (sizeVectPionRetire > 0)												// Vu que des pions ont été retirés, vérifie si c'est le pion sur lequel on travaille actuellement
		{


			pionRetire = false;													// initialisation initiale  à "FALSE" la variable de contrôle pour la découverte d'un pion retiré.

			for (i = 0; i < GridJeu.pion_vecteur_retire_calcul.size(); i++)		//Pour chaque pions retiré dans la liste
			{
				if (GridJeu.pion_vecteur_retire_calcul.at(i).ID == my_pion.ID)
				{
					pionRetire = true;											//Le pion correspond à un pion retiré du jeu, alors la variable de contrôle devient "TRUE" (on travaille sur un pion retiré).

					leString.Format(_T("2a-OnClickButton: trouvé un pion ordi retiré: %d   coord: (x,y): (%d, %d) "), my_pion.ID, my_pion.old_x, my_pion.old_y);
					m_ListBox_Suivi_Jeu.InsertString(-1, leString);

				};

			};



			if (!pionRetire)	// si le pion n'a pas été retiré alors:
			{
				minimax_pion = CalculeMove_max(my_pion, le_niveau, alpha, beta);  // minimax_pion est le résultat de l'évaluation complétée pour les mouvements de ce pion.





				if (minimax_pion.move < 0)
				{															// ici le pion n'a pu bouger.  Donc pas de score valide.
					leString.Format(_T("2b-OnClickButton ordi: (move <0)  Pion ID: %d,  score:  %d,  move: %d, alpha: %d, beta: %d"), minimax_pion.ID, minimax_pion.score, minimax_pion.move, alpha, beta);
					m_ListBox_Suivi_Jeu.InsertString(-1, leString);

				}

				else
				{															// ici le pion a pu bouger.  Donc on met à jour le score pour ce pion



					leString.Format(_T("2c-OnClickButton ordi: (move <0)  Pion ID: %d,  score:  %d,  move: %d, alpha: %d, beta: %d"), minimax_pion.ID, minimax_pion.score, minimax_pion.move, alpha, beta);
					m_ListBox_Suivi_Jeu.InsertString(-1, leString);
					GridJeu.SetPionScore(minimax_pion, minimax_pion.score, minimax_pion.move);

				};

			};  // FIN : if (sizeVect ==0)


		};

		// Une fois tous les pions évalués.  On choisit le meilleur pion à bouger
		PrintScorePions();

	}
}


void CMFCDame3Dlg::OnBnClickedHumainJoueButton()
{
	// TODO: Add your control notification handler code here

	int pionID;
	CGrid::pion my_pion, minimax_pion;


	int le_niveau = 0;

	int sizeVect;
	CString leString;

	sizeVect = GridJeu.GetPionVectHumSize();

	GridJeu.ResetScorePions();

	int alpha = -1000;
	int beta = 1000;
	unsigned int i;
	int sizeVectPionRetire;
	bool pionRetire = false;
	

	for (pionID = 0; pionID < sizeVect; pionID++)
	{
		my_pion = GridJeu.GetPionFromVectHumain(pionID);						//retourne le pion "humain" pion(pionID)

		leString.Format(_T("    "));
		m_ListBox_Suivi_Jeu.InsertString(-1, leString);							// insere une ligne vide pour affichage plus facilement lisible.

		leString.Format(_T("1-OnClickButton humain: Pion %d de %d ,   ID: %d, niveau %d, position (x,y): (%d, %d)"), pionID+1, sizeVect, my_pion.ID, le_niveau, my_pion.old_x, my_pion.old_y);

																				// pionID+1: pour corriger l'affichage.  Sinon affiche 0 pour le 1er pion traité.  On veut "1" pour le 1er pion.

		m_ListBox_Suivi_Jeu.InsertString(-1, leString);

		sizeVectPionRetire = GridJeu.pion_vecteur_retire_calcul.size();

		if (sizeVectPionRetire > 0)												// Vu que des pions ont été retirés, vérifie si c'est le pion sur lequel on travaille actuellement
		{

			
			pionRetire = false;													// initialisation initiale  à "FALSE" la variable de contrôle pour la découverte d'un pion retiré.

			for (i = 0; i < GridJeu.pion_vecteur_retire_calcul.size(); i++)		//Pour chaque pions retiré dans la liste
			{
				if (GridJeu.pion_vecteur_retire_calcul.at(i).ID == my_pion.ID)
				{
					pionRetire = true;											//Le pion correspond à un pion retiré du jeu, alors la variable de contrôle devient "TRUE" (on travaille sur un pion retiré).

					leString.Format(_T("2a-OnClickButton: trouvé un pion ordi retiré: %d   coord: (x,y): (%d, %d) "), my_pion.ID, my_pion.old_x, my_pion.old_y);
					m_ListBox_Suivi_Jeu.InsertString(-1, leString);
					
				};

			};

			if (!pionRetire) // si le pion n'est pas retiré...
			{
				minimax_pion = CalculeMove_max(my_pion, le_niveau, alpha, beta);	// minimax_pion est le résultat de l'évaluation complétée pour les mouvements de ce pion.

				if (minimax_pion.move < 0)
				{																	// ici le pion n'a pu bouger.  Donc pas de score valide.
					leString.Format(_T("2-OnClickButton: (move <0)  Pion ID: %d,  score:  %d,  move: %d, alpha: %d, beta: %d"), minimax_pion.ID, minimax_pion.score, minimax_pion.move, alpha, beta);
					m_ListBox_Suivi_Jeu.InsertString(-1, leString);

				}

				else
				{																	// ici le pion a pu bouger.  Donc on met à jour le score pour ce pion


					leString.Format(_T("2-OnClickButton: (move <0)  Pion ID: %d,  score:  %d,  move: %d, alpha: %d, beta: %d"), minimax_pion.ID, minimax_pion.score, minimax_pion.move, alpha, beta);
					m_ListBox_Suivi_Jeu.InsertString(-1, leString);
					GridJeu.SetPionScore(minimax_pion, minimax_pion.score, minimax_pion.move);

				};
			};  // FIN: if (!pionRetire)  Le pion est retiré donc on passe au pion suivant.

		}; // FIN: if (sizeVectPionRetire > 0)
	}; // FIN: for (pionID = 0; pionID < sizeVect; pionID++)


	
	PrintScorePions();
}

CGrid::pion CMFCDame3Dlg::CalculeMove_max(CGrid::pion &pion, int niveau, int alpha, int beta)  
{
	// TODO: Add your implementation code here.
	

		int v = -1000;
		CGrid::pion v1, temp_pion, retire_pion_opposant;
		CString leString;

		v1.score = -1000;
		v1.ID = pion.ID;
		v1.move = pion.move;
		v1.old_x = pion.old_x;
		v1.old_y = pion.old_y;
		v1.new_x = pion.new_x;
		v1.new_y = pion.new_y;
		v1.score = pion.score;
		v1.removed = pion.removed;
		v1.dame = pion.removed;
		
		int le_niveau = niveau;
		le_niveau = le_niveau + 1;

		int move, dx, dy;
		
		bool testremoved;

		dx = GridJeu.delta_x;
		dy = GridJeu.delta_y;

		leString.Format(_T("4-CalculeMove_max: Pion ID: %d,  niveau: %d,  move: %d, alpha: %d, beta: %d"), pion.ID, le_niveau, v1.move, alpha, beta  );
		m_ListBox_Suivi_Jeu.InsertString(-1, leString);

		if (le_niveau > GridJeu.max_niveau)
		{

			leString.Format(_T("5-CalculeMove_max  niveau max atteint"));
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);
			
			GridJeu.CalculScoreGrid();			// compte le nombre de pion de chaque joueur.



			// SI L'ORDI JOUE, LA FORMULE DE CALCUL DU POINTAGE EST:
			if (pion.ID > 0)
			{
				pion.score = (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum()) - (GridJeu.GetScoreGridOrdi() - GridJeu.GetScoreInitialOrdi());
				// score = +humains retirés - ordis retirés
				
				
			};

			
			// SI L'HUMAIN JOUE, LA FORMULE DE CALCUL DU POINTAGE DEVIENT:
			if (pion.ID < 0)
			{
				pion.score = (GridJeu.GetScoreInitialOrdi() - GridJeu.GetScoreGridOrdi()) - (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum());
				// score = +ordis retirés  - humains retirés 
				

			};
		
			leString.Format(_T("5a-CalculeMove_max: score: %d pour ID: %d"), pion.score, pion.ID);
			m_listBox_move.InsertString(-1, leString);

			leString.Format(_T("5b-CalculeMove_max initialHumain: %d,  grid Humain: %d,  initial ordi: %d, grid Ordi: %d"), GridJeu.GetScoreInitialHum(), GridJeu.GetScoreGridHum(), GridJeu.GetScoreGridOrdi(), GridJeu.GetScoreGridOrdi());
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);

			return pion;		// ici, on n'a rien changé au pion, donc on retourne.

		}  // fin: if (niveau > GridJeu.max_niveau)

		else

		{  // ici: niveau < max_niveau.  Donc , on continue...

			for (move = 0; move <= 3; move++)  // move 0: +x, +y; move 1: -x,+y; move 2: +x, -y; move 3: -x, -y;
			{
				v1.move = move;

				temp_pion = GridJeu.EvalueMove(pion, GridJeu.delta_x, GridJeu.delta_y, le_niveau, move);

				leString.Format(_T("6-CalculeMove_max.evalueMove   Move: %d -> Bouge: %d (oui:0/non:-1:) )"), move, temp_pion.move);
				m_ListBox_Suivi_Jeu.InsertString(-1, leString);

				if (temp_pion.move >= 0)			
				{
					//  ">=0" veut dire que le pion peut bouger.  
					//  <0 , le pion ne peut bouger.

					//move pion - moveStack push;

					testremoved = temp_pion.removed;	// sauvegarde l'état "removed" 
					temp_pion.removed = false;			// removed = false indique que le pion a bougé.  True = le pion a été retiré.
														// La valeur est modifiée ici avant de l'ajouter au stack.
		
					GridJeu.PushPionOnStack(temp_pion);  // sauve la config du pion.


														// Mettre à jour la grille de jeu avec le mouvement du pion
														// La case originale du pion (old_x, old_y) a été modifiée par "EvalueMove" avec ID =0, ce qui indique une case vide.
					

					leString.Format(_T("max: 1  met ID %d -> 0 dans %d - %d"),temp_pion.ID, temp_pion.old_x, temp_pion.old_y);
					m_listBox_move.InsertString(-1, leString);

					GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].ID =0;						// Le pion quitte la case.  Indique comme vide avec ID=0;
					PrintGrid();
					UpdateWindow();
					
					
					

					// Mettre à jour la grille de jeu

					GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].ID = temp_pion.ID;
					GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].removed = false;
					GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].new_x = temp_pion.new_x;		// coordonnees X (destination lors d'un déplacement)
					GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].new_y = temp_pion.new_y;		// coordonnees Y
					GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].old_x = temp_pion.old_x;		// coordonnees X (destination lors d'un déplacement)
					GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].old_y = temp_pion.old_y;		// coordonnees Y
					GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].dame = temp_pion.dame;		// si le pion devient une dame, alors dame = TRUE;
					GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].score = temp_pion.score;		// score calculé pour ce pion (évaluation minimax)
					GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].move = temp_pion.move;
					
					

					leString.Format(_T("max: 2 met ID = %d dans %d - %d"), temp_pion.ID, temp_pion.new_x, temp_pion.new_y);
					m_listBox_move.InsertString(-1, leString);
					PrintGrid();
					UpdateWindow();

					if (testremoved)					// Si ce pion a capturé un pion ennemi (pion.removed = TRUE), alors retire le pion ennemi du grid. Sauvegarde dans stack pour restauration future...
					{
						
						if (temp_pion.ID < 0) dy = -dy;								// inverser le sens de déplacement pour le pion humain.

						switch (move)												//Calcule la position du pion à retirer.  
																					
						{
						case 0:
							retire_pion_opposant.old_x = temp_pion.old_x + dx; 
							retire_pion_opposant.old_y = temp_pion.old_y + dy;
							break;

						case 1:
							retire_pion_opposant.old_x = temp_pion.old_x - dx;
							retire_pion_opposant.old_y = temp_pion.old_y + dy;
							break;

						case 2:
							retire_pion_opposant.old_x = temp_pion.old_x + dx;
							retire_pion_opposant.old_y = temp_pion.old_y - dy;
							break;

						case 3:
							retire_pion_opposant.old_x = temp_pion.old_x - dx;
							retire_pion_opposant.old_y = temp_pion.old_y - dy;
							break;

						};  // fin : switch(move)

						retire_pion_opposant.ID = GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].ID;
						retire_pion_opposant.removed = true;
						retire_pion_opposant.new_x = GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].new_x;		// coordonnees X (destination lors d'un déplacement)
						retire_pion_opposant.new_y = GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].new_y;		// coordonnees Y
						retire_pion_opposant.old_x = GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].old_x;		// coordonnees X (destination lors d'un déplacement)
						retire_pion_opposant.old_y = GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].old_y;		// coordonnees Y
						retire_pion_opposant.dame = GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].dame;			// si le pion devient une dame, alors dame = TRUE;
						retire_pion_opposant.score = GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].score;		// score calculé pour ce pion (évaluation minimax)
						retire_pion_opposant.move = move;							
						


						// move: correspond au mouvement associé au score (directions (x,y) -> 0= +/+ , 1 = -/+, 2 = +/-, 3 = -/-)  -1: ne peut bouger le pion
						

						GridJeu.PushPionOnStack(retire_pion_opposant);			// push le pion dans le stack pour restauration future.
																				// L'ordre des moves sauvés sur le stack: 
																				
						
						// Mettre à jour le vecteur et la grille de  jeu:

						//Retire  le pion de la grille de jeu et du vecteur des pions de la grille pour continuer l'évaluation du jeu.
						//GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y] = 0 + retire pion du vecteurGrid
						
						

						GridJeu.RetirePionCalcul(retire_pion_opposant);			// Retire pion de la grille et du vecteur pion approprié.		
						
						
													

						leString.Format(_T("Retiré du calcul pion ID: %d"), retire_pion_opposant.ID);
						m_listBox_move.InsertString(-1, leString);
						PrintGrid();
						UpdateWindow();
					
					}; // FIN: if (testremoved)	
							
					temp_pion.old_x = temp_pion.new_x;				// Le pion a bougé.  Met à jour les coordonnées avec la nouvelle configuration pour la prochaine évaluation (CalculeMove_min).
					temp_pion.old_y = temp_pion.new_y;

					v1 = CalculeMove_min(temp_pion, le_niveau, alpha, beta);

					leString.Format(_T("7a-CalculeMoveHum: score: %d ,  niveau: %d,  move: %d, alpha: %d, beta: %d"), v1.score, le_niveau, v1.move, alpha, beta);
					m_ListBox_Suivi_Jeu.InsertString(-1, leString);
					
																	//remettre le grid_sub dans l'état avant le mouvement.
																	//move pion - moveStack pop;

					temp_pion = GridJeu.PopPionFromStack();


					if (temp_pion.removed)							// Si le pion a été retiré, alors remettre le pion retiré sur la grille de jeu.
					{
						
						
						temp_pion.removed = false;					// modifie la valeur avant de remettre dans le jeu.
						
						GridJeu.AjoutPionCalcul(temp_pion);			// Ajout pion dans le jeu (dans vecteur des pions actifs)
						
						
						
						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].ID = temp_pion.ID;
						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].old_x = temp_pion.old_x;
						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].old_y = temp_pion.old_y;
						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].new_x = temp_pion.new_x;
						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].new_y = temp_pion.new_y;
						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].dame = temp_pion.dame;
						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].score = temp_pion.score;
						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].move = temp_pion.move;
						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].removed = false;
						 
						// pas besoin de mettre à jour l'ancienne case puisque ce pion n'était pas sur la grille de jeu avant d'être réintégré.

						
						

						 leString.Format(_T("Remet ID -> %d  dans %d - %d"), temp_pion.ID, temp_pion.old_x, temp_pion.old_y);
						 m_listBox_move.InsertString(-1, leString);

						 leString.Format(_T("max: 4 apres"));
						 m_listBox_move.InsertString(-1, leString);

						 PrintGrid();
						 UpdateWindow();

						// Remettre le pion dans la grille de jeu.

						 temp_pion = GridJeu.PopPionFromStack(); // récupérer le pion qui a fait le retrait.

						

					};  // FIN : if (temp_pion.removed)

																	// Ici le pion a bougé et on le remet à sa position originale.

					leString.Format(_T(" Move ID: %d, Niv: %d  de: %d, %d  à %d, %d Niv: %d M: %d R: %d"), temp_pion.ID, le_niveau, temp_pion.new_x, temp_pion.new_y, temp_pion.old_x, temp_pion.old_y, le_niveau, move, temp_pion.move);
					m_ListBox_Suivi_Jeu.InsertString(-1, leString);

										
					GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].ID = temp_pion.ID;
					GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].removed = false;
					GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].new_x = temp_pion.new_x;		// coordonnees X (destination lors d'un déplacement)
					GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].new_y = temp_pion.new_y;		// coordonnees Y
					GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].old_x = temp_pion.old_x;		// coordonnees X (destination lors d'un déplacement)
					GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].old_y = temp_pion.old_y;		// coordonnees Y
					GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].dame = temp_pion.dame;		// si le pion devient une dame, alors dame = TRUE;
					GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].score = temp_pion.score;		// score calculé pour ce pion (évaluation minimax)
					GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].move = temp_pion.move;
					
					GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].ID = 0;						// enlève pion de la case où le pion avait bougé.

					leString.Format(_T("Remet pion ID 0 -> %d  dans %d - %d"), temp_pion.ID, temp_pion.old_x, temp_pion.old_y);
					m_listBox_move.InsertString(-1, leString);

					leString.Format(_T("max: 4b ID %d -> 0  dans %d - %d"), temp_pion.ID, temp_pion.new_x, temp_pion.new_y);
					m_listBox_move.InsertString(-1, leString);

					PrintGrid();
					UpdateWindow();




						

					if (v1.score > v) v = v1.score;
					if (v1.score >= beta)
					{
						v1.score = v;

						leString.Format(_T("7b-CalculeMove_max: score: %d ,  niveau: %d,  move: %d, alpha: %d, beta: %d"), v1.score, le_niveau, v1.move, alpha, beta);
						m_ListBox_Suivi_Jeu.InsertString(-1, leString);
						return v1;

					};
					if (v1.score > alpha)
					{
						
						alpha = v1.score;

						leString.Format(_T("7c-CalculeMove_max: score: %d ,  niveau: %d,  move: %d, alpha: %d, beta: %d"), v1.score, le_niveau, v1.move, alpha, beta);
						m_ListBox_Suivi_Jeu.InsertString(-1, leString);
					}

					return v1;

				}   // fin: if (temp_pion.move >= 0)

				else
				{										// Ici , le pion ne peut bouger.  Calculer le score et retourner la valeur comme si le niveau max avait été atteint.
					
					leString.Format(_T(" Move ID: %d, Niv: %d  de: %d, %d  à %d, %d  Niv: %d M: %d R: %d"), temp_pion.ID,  le_niveau, temp_pion.old_x, temp_pion.old_y, temp_pion.new_x, temp_pion.new_y, le_niveau, move, temp_pion.move);
					m_ListBox_Suivi_Jeu.InsertString(-1, leString);
					
					GridJeu.CalculScoreGrid();			

					// SI L'ORDI JOUE, LA FORMULE DE CALCUL DU POINTAGE EST:
					if (pion.ID > 0)
					{
						pion.score = (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum()) - (GridJeu.GetScoreGridOrdi() - GridJeu.GetScoreInitialOrdi());
					};


					// SI L'HUMAIN JOUE, LA FORMULE DE CALCUL DU POINTAGE DEVIENT:
					if (pion.ID < 0)
					{
						pion.score = (GridJeu.GetScoreInitialOrdi() - GridJeu.GetScoreGridOrdi()) - (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum());
					};

					leString.Format(_T("7d-CalculeMove_max Ne peut bouger pion. Calcul score: initialHumain: %d,  grid Humain: %d,  initial ordi: %d, grid Ordi: %d"), GridJeu.GetScoreInitialHum(), GridJeu.GetScoreGridHum(), GridJeu.GetScoreGridOrdi(), GridJeu.GetScoreGridOrdi());
					m_ListBox_Suivi_Jeu.InsertString(-1, leString);

					pion.move = -1;						// ici le pion ne peut bouger.
					return pion;
				};

			
			};  // boucle: for (move = 0; move < 4; move++)

			return pion;

		}; // fin: if (niveau > GridJeu.max_niveau)
	
};




CGrid::pion CMFCDame3Dlg::CalculeMove_min(CGrid::pion &pion, int niveau, int alpha, int beta)
{
	// TODO: Add your implementation code here.
	//CalculeMovePionHumain_min(pion &pion, int niveau, int alpha, int beta)

		CGrid::pion v1, my_pion, temp_pion,retire_pion_opposant;
		CString leString;

		int score, move, lePion, sizeVect,le_niveau, v, dx,dy;
		le_niveau = niveau;
		bool testremoved = false;

		dx = GridJeu.delta_x;
		dy = GridJeu.delta_y;

		v = 1000;
		v1.ID = pion.ID;
		v1.move = pion.move;
		v1.old_x = pion.old_x;
		v1.old_y = pion.old_y;
		v1.new_x = pion.new_x;
		v1.new_y = pion.new_y;
		v1.score = pion.score;
		v1.removed = pion.removed;
		v1.dame = pion.dame;

		
		
		le_niveau = le_niveau + 1;

		leString.Format(_T("8-CalculeMoveHum: Pion ordi ID: %d,  niveau: %d,  move: %d, alpha: %d, beta: %d"), v1.ID, le_niveau, v1.move, alpha, beta);
		m_ListBox_Suivi_Jeu.InsertString(-1, leString);

		if (le_niveau > GridJeu.max_niveau)
		{
			leString.Format(_T("9a-CalculeMoveHum MAX NIVEAU ATTEINT: Pion ID: %d,  niveau: %d,  move: %d, alpha: %d, beta: %d"), pion.ID, le_niveau, v1.move, alpha, beta);
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);
			
			GridJeu.CalculScoreGrid();			// compte le nombre de pion de chaque joueur.

			// SI L'ORDI JOUE, LA FORMULE DE CALCUL DU POINTAGE EST:
			if (pion.ID > 0)
			{
				score = (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum()) - (GridJeu.GetScoreGridOrdi() - GridJeu.GetScoreInitialOrdi());
				leString.Format(_T("max: niveau> max: score: %d pour ID: %d"), score, pion.ID);
				m_listBox_move.InsertString(-1, leString);
			};


			// SI L'HUMAIN JOUE, LA FORMULE DE CALCUL DU POINTAGE DEVIENT:
			if (pion.ID < 0)
			{
				score = (GridJeu.GetScoreInitialOrdi() - GridJeu.GetScoreGridOrdi()) - (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum());
				leString.Format(_T("max: niveau> max: score: %d pour ID: %d"), score, pion.ID);
				m_listBox_move.InsertString(-1, leString);
			};
			
			v1.score = score;

			leString.Format(_T("9b-CalculeMove_max max niveau atteint: initialHumain: %d,  grid Humain: %d,  initial ordi: %d, grid Ordi: %d"), GridJeu.GetScoreInitialHum(), GridJeu.GetScoreGridHum(), GridJeu.GetScoreGridOrdi(), GridJeu.GetScoreGridOrdi());
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);

			leString.Format(_T("9c-CalculeMoveHum max niveau atteint: score: %d ,  niveau: %d,  move: %d, alpha: %d, beta: %d"), score , le_niveau, v1.move, alpha, beta);
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);
								   			
			return v1;
		};	// Fin : if (le_niveau > GridJeu.max_niveau)
		
		if (pion.ID > 0)
		{
			sizeVect = GridJeu.GetPionVectHumSize();				// Trouve la dimension du vecteur Humain (qui est l'opposant de l'ordi ici)
		};
		if (pion.ID < 0)
		{
			sizeVect = GridJeu.GetPionVectOrdiSize();				// Trouve la dimension du vecteur ordi (qui est l'opposant de l'humain ici)
		};

		for (lePion = 0; lePion < sizeVect; lePion++)   // Boucle pour évaluer les pions du joueur ennemi.
		{
			
			if (pion.ID >0)
			{
				my_pion = GridJeu.GetPionFromGridHumain(lePion);
			};

			if (pion.ID < 0)
			{
				my_pion = GridJeu.GetPionFromGridOrdi(lePion);
			};



			leString.Format(_T("10-CalculeMoveHum: pion no: %d   ID: %d "), lePion, my_pion.ID);
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);

			for (move = 0; move <= 3; move++)  
			{
				v1.move = move;
				
				temp_pion = GridJeu.EvalueMove(my_pion, GridJeu.delta_x, GridJeu.delta_y, le_niveau, move);	
				

				leString.Format(_T("11-CalculeMoveHum: pion iD: %d,  move %d, Résultat:  %d"), temp_pion.ID, move, temp_pion.move);
				m_ListBox_Suivi_Jeu.InsertString(-1, leString);

					
				if (temp_pion.move >= 0)			//  >0 veut dire que le pion peut bouger.  <0 , le pion ne peut faire le move.  Donc on passe au move suivant.
				{
					

					testremoved = temp_pion.removed;	// sauvegarde le paramètre: "removed" 
					temp_pion.removed = false;
					
					//move pion - moveStack push;
					GridJeu.PushPionOnStack(temp_pion);

					//mettre à jour grid_sub: pion a bougé pour évaluation de ce move.
					leString.Format(_T(" Move ID: %d, Niv: %d  de: %d, %d  à %d, %d Niv: %d  M: %d R: %d"), temp_pion.ID, le_niveau, temp_pion.old_x, temp_pion.old_y, temp_pion.new_x, temp_pion.new_y, le_niveau, move, temp_pion.move);
					m_ListBox_Suivi_Jeu.InsertString(-1, leString);

										

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
					
					
					leString.Format(_T("min: 6 Met ID %d -> 0 dans %d - %d"), temp_pion.ID, temp_pion.old_x, temp_pion.old_y);
					m_listBox_move.InsertString(-1, leString);

					leString.Format(_T("min: 6a Met ID 0 -> %d dans %d - %d"), temp_pion.ID, temp_pion.new_x, temp_pion.new_y);
					m_listBox_move.InsertString(-1, leString);
					PrintGrid();
					UpdateWindow();

					if (testremoved)					// Si ce pion a capturé un pion ennemi (.removed = TRUE), alors retire le pion ennemi du grid. Sauvegarde dans stack pour restauration future...
					{

						if (temp_pion.ID < 0) dy = -dy;								// inverser le sens de déplacement pour le pion humain.

						switch (move)												//Calcule la position du pion à retirer.  

						{
						case 0:
							retire_pion_opposant.old_x = temp_pion.old_x + dx;
							retire_pion_opposant.old_y = temp_pion.old_y + dy;
							break;

						case 1:
							retire_pion_opposant.old_x = temp_pion.old_x - dx;
							retire_pion_opposant.old_y = temp_pion.old_y + dy;
							break;

						case 2:
							retire_pion_opposant.old_x = temp_pion.old_x + dx;
							retire_pion_opposant.old_y = temp_pion.old_y - dy;
							break;

						case 3:
							retire_pion_opposant.old_x = temp_pion.old_x - dx;
							retire_pion_opposant.old_y = temp_pion.old_y - dy;
							break;

						};  // fin : switch(move)

						retire_pion_opposant.ID = GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].ID;
						retire_pion_opposant.removed = true;
						retire_pion_opposant.new_x = GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].new_x;		// coordonnees X (destination lors d'un déplacement)
						retire_pion_opposant.new_y = GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].new_y;		// coordonnees Y
						retire_pion_opposant.old_x = GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].old_x;		// coordonnees X (destination lors d'un déplacement)
						retire_pion_opposant.old_y = GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].old_y;		// coordonnees Y
						retire_pion_opposant.dame = GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].dame;			// si le pion devient une dame, alors dame = TRUE;
						retire_pion_opposant.score = GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].score;		// score calculé pour ce pion (évaluation minimax)
						retire_pion_opposant.move = move;

						if (retire_pion_opposant.ID == pion.ID)
						{		// Ici, le pion qui est retiré, est le pion pour lequel "max" a demandé l'évaluation.
								//  Sans ce pion, on ne peut continuer.  Donc on fait l'évaluation et on retourne la valeur.
							
							temp_pion = GridJeu.PopPionFromStack();		// retire le pion du stack.


							leString.Format(_T("min: 6b Pion en évaluation retiré: pion ID %d dans %d %d,  move: %d"), pion.ID, pion.old_x, pion.old_y, move);
							m_ListBox_Suivi_Jeu.InsertString(-1, leString);
							
							GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].ID = temp_pion.ID;			// remettre le pion à sa case originale.
							GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].removed = false;
							GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].new_x = temp_pion.new_x;		// coordonnees X (destination lors d'un déplacement)
							GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].new_y = temp_pion.new_y;		// coordonnees Y
							GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].old_x = temp_pion.old_x;		// coordonnees X (destination lors d'un déplacement)
							GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].old_y = temp_pion.old_y;		// coordonnees Y
							GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].dame = temp_pion.dame;		// si le pion devient une dame, alors dame = TRUE;
							GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].score = temp_pion.score;		// score calculé pour ce pion (évaluation minimax)
							GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].move = temp_pion.move;
							
							GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].ID = 0;						// enlève pion de la case où le pion avait bougé.

							leString.Format(_T("min: 6c Met ID = %d -> 0 dans %d - %d"), 0, temp_pion.new_x, temp_pion.new_y);
							m_listBox_move.InsertString(-1, leString);

							leString.Format(_T("min: 6d Met ID = %d dans  %d %d"),temp_pion.ID, temp_pion.old_x, temp_pion.old_y);
							m_listBox_move.InsertString(-1, leString);

							leString.Format(_T("min: 7 apres"));
							m_listBox_move.InsertString(-1, leString);
							PrintGrid();
							UpdateWindow();


							GridJeu.CalculScoreGrid();			// compte le nombre de pion de chaque joueur.


							// SI L'ORDI JOUE, LA FORMULE DE CALCUL DU POINTAGE EST:
							if (pion.ID > 0)
							{
								score = (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum()) - (GridJeu.GetScoreGridOrdi() - GridJeu.GetScoreInitialOrdi());

								leString.Format(_T("min: 7 score: %d pour ID: %d  move: %d"), score, v1.ID, move);
								m_listBox_move.InsertString(-1, leString);
							};


							// SI L'HUMAIN JOUE, LA FORMULE DE CALCUL DU POINTAGE DEVIENT:
							if (pion.ID < 0)
							{
								score = (GridJeu.GetScoreInitialOrdi() - GridJeu.GetScoreGridOrdi()) - (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum());

								leString.Format(_T("min: 7 score: %d pour ID: %d  move: %d"), score, v1.ID, move);
								m_listBox_move.InsertString(-1, leString);
							};
							
							
							
							v1.score = score;
							return v1;

						};

						GridJeu.PushPionOnStack(retire_pion_opposant);			// push le pion dans le stack pour restauration future.
																				// L'ordre des moves sauvés sur le stack: 
						// Mettre à jour le vecteur et la grille de  jeu:

						//Retire  le pion de la grille de jeu et du vecteur des pions de la grille pour continuer l'évaluation du jeu.
						//GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y] = 0 + retire pion du vecteurGrid

						GridJeu.RetirePionCalcul(retire_pion_opposant);			// Retire pion de la grille et du vecteur pion approprié.

						
						leString.Format(_T("Retiré pion du calcul ID: %d dans %d - %d"), retire_pion_opposant.ID, retire_pion_opposant.old_x, retire_pion_opposant.old_y);
						m_listBox_move.InsertString(-1, leString);

						leString.Format(_T("12-CalculeMove_min: Pion ID: %d,  niveau: %d,  move: %d, alpha: %d, beta: %d"), pion.ID, le_niveau, temp_pion.move, alpha, beta);
						m_ListBox_Suivi_Jeu.InsertString(-1, leString);

						leString.Format(_T(" Move ID: %d, Niv: %d  de: %d, %d  à %d, %d Niv: %d  M: %d R: %d"), temp_pion.ID, le_niveau, temp_pion.new_x, temp_pion.new_y, temp_pion.old_x, temp_pion.old_y, le_niveau, move, temp_pion.move);
						m_ListBox_Suivi_Jeu.InsertString(-1, leString);

					};  // Fin: if (testremoved)

					v1 = CalculeMove_max(v1, le_niveau, alpha, beta);

					temp_pion = GridJeu.PopPionFromStack();


					if (temp_pion.removed) // Remettre le pion retiré sur la grille de jeu.
					{


						temp_pion.removed = false;					// modifie la valeur avant de remettre dans le jeu.

						GridJeu.AjoutPionCalcul(temp_pion);			// Ajout pion dans le jeu (dans vecteur des pions actifs)

						
						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].ID = temp_pion.ID;
						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].old_x = temp_pion.old_x;
						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].old_y = temp_pion.old_y;
						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].new_x = temp_pion.new_x;
						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].new_y = temp_pion.new_y;
						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].dame = temp_pion.dame;
						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].score = temp_pion.score;
						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].move = temp_pion.move;
						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].removed = false;
						

						leString.Format(_T("Remet pion ID: %d dans %d - %d"), temp_pion.ID, temp_pion.old_x, temp_pion.old_y);
						m_listBox_move.InsertString(-1, leString);

						leString.Format(_T("min: 8 apres"));
						m_listBox_move.InsertString(-1, leString);
						PrintGrid();
						UpdateWindow();

						// Remettre le pion dans la grille de jeu.

						temp_pion = GridJeu.PopPionFromStack(); // récupérer le pion qui a fait le retrait.



					};

					// Ici le pion a bougé et on le remet à sa position originale.

					
					GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].ID = temp_pion.ID;
					GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].removed = false;
					GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].new_x = temp_pion.new_x;		// coordonnees X (destination lors d'un déplacement)
					GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].new_y = temp_pion.new_y;		// coordonnees Y
					GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].old_x = temp_pion.old_x;		// coordonnees X (destination lors d'un déplacement)
					GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].old_y = temp_pion.old_y;		// coordonnees Y
					GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].dame = temp_pion.dame;		// si le pion devient une dame, alors dame = TRUE;
					GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].score = temp_pion.score;		// score calculé pour ce pion (évaluation minimax)
					GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].move = temp_pion.move;
					
					GridJeu.grid_sub[temp_pion.new_x][temp_pion.new_y].ID = 0;						// ID=0 indique que la case est vide.

					
					leString.Format(_T("min: 9 Met ID %d -> 0 dans %d - %d"), temp_pion.ID, temp_pion.new_x, temp_pion.new_y);
					m_listBox_move.InsertString(-1, leString);
					
					leString.Format(_T("min: 9 Met ID = %d -> %d - %d"), temp_pion.ID, temp_pion.old_x, temp_pion.old_y);
					m_listBox_move.InsertString(-1, leString);




					PrintGrid();
					UpdateWindow();

					leString.Format(_T(" Move ID: %d, Niv: %d  de: %d, %d  à %d, %d Niv: %d M: %d R: %d"), temp_pion.ID, le_niveau, temp_pion.new_x, temp_pion.new_y, temp_pion.old_x, temp_pion.old_y, le_niveau, move, temp_pion.move);
					m_ListBox_Suivi_Jeu.InsertString(-1, leString);

					if (v1.score < v)
					{
						v = v1.score;
					};

					if (v1.score <= alpha)
					{
					v1.score = v;
					return v1;
					};

					if (v1.score < beta) 
					{
					beta = v1.score;
					};  // fin: if (temp_pion.move >= 0)
					
					
					// Ici , le pion ne peut bouger.  Calculer le score et retourner la valeur comme si le niveau max avait été atteint.
						
					leString.Format(_T(" Move ID: %d, Niv: %d  de: %d, %d  à %d, %d  Niv: %d M: %d R: %d"), temp_pion.ID, le_niveau, temp_pion.old_x, temp_pion.old_y, temp_pion.new_x, temp_pion.new_y, le_niveau, move, temp_pion.move);
					m_ListBox_Suivi_Jeu.InsertString(-1, leString);
						
						
						
					GridJeu.CalculScoreGrid();					// compte le nombre de pion de chaque joueur.
																// calcule le score pour ce pion.

					// SI L'ORDI JOUE, LA FORMULE DE CALCUL DU POINTAGE EST:
					if (pion.ID > 0)
					{
						v1.score = (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum()) - (GridJeu.GetScoreGridOrdi() - GridJeu.GetScoreInitialOrdi());
						leString.Format(_T("min: 10a score: %d pour ID: %d"), v1.score, v1.ID);
						m_listBox_move.InsertString(-1, leString);
					};


					// SI L'HUMAIN JOUE, LA FORMULE DE CALCUL DU POINTAGE DEVIENT:
					if (pion.ID < 0)
					{
						v1.score = (GridJeu.GetScoreInitialOrdi() - GridJeu.GetScoreGridOrdi()) - (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum());
						leString.Format(_T("min: 10b score: %d pour ID: %d"), v1.score, v1.ID);
						m_listBox_move.InsertString(-1, leString);
					};
					

					leString.Format(_T("12a-CalculeMoveHum Ne peut bouger pion. Calcul score: initialHumain: %d,  grid Humain: %d,  initial ordi: %d, grid Ordi: %d"), GridJeu.GetScoreInitialHum(), GridJeu.GetScoreGridHum(), GridJeu.GetScoreGridOrdi(), GridJeu.GetScoreGridOrdi());
					m_ListBox_Suivi_Jeu.InsertString(-1, leString);
					
					return v1;


					} // fin: if (temp_pion.move >= 0)

				}  // fin: for (move = 0; move <= 3; move++)

			} // Fin de la boucle pour évaluer les pions du joueur ennemi: for (lePion = 0; lePion < sizeVect; lePion++)

			return v1;
		
};

void CMFCDame3Dlg::PrintGrid()
{
	int i, j,k,l, ID, test;
	CString leString;

	for (i = 0; i < 10; i++)
		
	{
		for (j = 0; j < 10; j = j + 10)
		{
			leString.Format(_T("i:%d   %d   %d   %d   %d   %d   %d   %d   %d   %d   %d"), i, GridJeu.grid_sub[i][j].ID, GridJeu.grid_sub[i][j + 1].ID, GridJeu.grid_sub[i][j + 2].ID, GridJeu.grid_sub[i][j + 3].ID, GridJeu.grid_sub[i][j + 4].ID, GridJeu.grid_sub[i][j + 5].ID, GridJeu.grid_sub[i][j + 6].ID, GridJeu.grid_sub[i][j + 7].ID, GridJeu.grid_sub[i][j + 8].ID, GridJeu.grid_sub[i][j + 9].ID);
			m_listBox_move.InsertString(-1, leString);

		};
	};

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
								leString.Format(_T("Doublon trouvé.  ID: %d"), ID);
								m_listBox_move.InsertString(-1, leString);
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

	lepion = GridJeu.TrouveBestPionOrdi();
	leString.Format(_T("Score ordi: ID %d,  score: %d,  move: %d."), lepion.ID, lepion.score, lepion.move);
	m_listBox_move.InsertString(-1, leString);


	lepion = GridJeu.TrouveBestPionHumain();
	leString.Format(_T("Score humain: ID %d,  score: %d,  move: %d."), lepion.ID, lepion.score, lepion.move);
	m_listBox_move.InsertString(-1, leString);


};


