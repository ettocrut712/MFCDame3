
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
	ON_BN_CLICKED(IDC_retire_pion_BUTTON, &CMFCDame3Dlg::OnClickedRetirePionButton)
	ON_BN_CLICKED(IDC_calcul_score_initial_BUTTON, &CMFCDame3Dlg::OnClickedCalculScoreInitialButton)
	ON_BN_CLICKED(IDC_calcul_score_grid_sub_BUTTON, &CMFCDame3Dlg::OnClickedCalculScoreGridSubButton)
	ON_BN_CLICKED(IDC_evalueMove_BUTTON, &CMFCDame3Dlg::OnBnClickedevaluemoveButton)
	ON_BN_CLICKED(IDC_ORDI_JOUE_BUTTON, &CMFCDame3Dlg::OnBnClickedOrdiJoueButton)
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


void CMFCDame3Dlg::OnClickedRetirePionButton()
{
	// TODO: Add your control notification handler code here
/*

	int i;
	CString leString;
	int main_sub;
	
	
	for (i = -20; i < -8; i++)
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
	*/
	
	OnClickedCalculScoreInitialButton();
	OnClickedCalculScoreGridSubButton();
	
	

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
//	int score;

	for (pionID = 0; pionID < sizeVect; pionID++)
	{
		my_pion = GridJeu.GetPionFromGridOrdi(pionID);



		leString.Format(_T("1-OnClickButton: Pion no:  %d    Pion ID: %d, niveau %d"), pionID, my_pion.ID, le_niveau);
		m_ListBox_Suivi_Jeu.InsertString(-1, leString);

		minimax_pion = CalculeMoveOrdi_max(my_pion, le_niveau, alpha, beta);  // minimax_pion est le résultat de l'évaluation complétée pour les mouvements de ce pion.


		


		if (minimax_pion.move < 0)
		{															// ici le pion n'a pu bouger.  Donc pas de score valide.
			leString.Format(_T("2-OnClickButton: (move <0)  Pion ID: %d,  score:  %d,  move: %d, alpha: %d, beta: %d"), minimax_pion.ID, minimax_pion.score, minimax_pion.move, alpha, beta);
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);
		
		}

		else
		{															// ici le pion a pu bouger.  Donc on met à jour le score pour ce pion
			
		//	GridJeu.SetPionScore(minimax_pion.ID, minimax_pion.score, minimax_pion.move);
						
			leString.Format(_T("2-OnClickButton: (move <0)  Pion ID: %d,  score:  %d,  move: %d, alpha: %d, beta: %d"), minimax_pion.ID, minimax_pion.score, minimax_pion.move, alpha, beta);
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);
			GridJeu.SetPionScore(minimax_pion, minimax_pion.score, minimax_pion.move);
			
		};
		
																	


	};

																	// Une fois tous les pions évalués.  On choisit le meilleur pion à bouger
	PrintScorePions();

	
};


CGrid::pion CMFCDame3Dlg::CalculeMoveOrdi_max(CGrid::pion &pion, int niveau, int alpha, int beta)  // max
{
	// TODO: Add your implementation code here.
	//CalculeMoveOrdi_max(CGrid::pion &pion, int niveau, int alpha, int beta)

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

		int move, test, dx, dy;
		
		bool testremoved;


		dx = GridJeu.delta_x;
		dy = GridJeu.delta_y;

		leString.Format(_T("4-CalculeMoveOrdi: Pion ID: %d,  niveau: %d,  move: %d, alpha: %d, beta: %d"), pion.ID, le_niveau, v1.move, alpha, beta  );
		m_ListBox_Suivi_Jeu.InsertString(-1, leString);

		if (le_niveau > GridJeu.max_niveau)
		{

			leString.Format(_T("5-CalculeMoveOrdi max niveau atteint: Pion ID: %d,  niveau: %d,  move: %d, alpha: %d, beta: %d"), pion.ID, le_niveau, v1.move, alpha, beta);
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);
			
			GridJeu.CalculScoreGrid();			// compte le nombre de pion de chaque joueur.
												// calcule le score pour ce pion.
			pion.score = (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum()) - (GridJeu.GetScoreGridOrdi() - GridJeu.GetScoreInitialOrdi());
			
			//***************DEBUT: CODE A RETIRER ******************
			if (pion.score != 0)
			{
				leString.Format(_T("POINTAGE Pion ID: %d,   %d"), pion.ID, pion.score);
				m_listBox_move.InsertString(-1, leString);
				
				
				test = 1;  // test pour debuggage. Breakpoint à retirer avec ce code.
			};

			//***************FIN:CODE A RETIRER ******************

			leString.Format(_T("5a-CalculeMoveOrdi max niveau atteint: initialHumain: %d,  grid Humain: %d,  initial ordi: %d, grid Ordi: %d"), GridJeu.GetScoreInitialHum(), GridJeu.GetScoreGridHum(), GridJeu.GetScoreGridOrdi(), GridJeu.GetScoreGridOrdi());
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);

			return pion;		// ici, on n'a rien changé au pion, donc on retourne.

		}  // fin: if (niveau > GridJeu.max_niveau)

		else

		{  // ici: niveau < max_niveau.  Donc , on continue...

			for (move = 0; move <= 3; move++)
			{
				v1.move = move;

				temp_pion = GridJeu.EvalueMove(pion, GridJeu.delta_x, GridJeu.delta_y, le_niveau, move);

				leString.Format(_T("6-CalculeMoveOrdi.evalueMove   Move: %d -> Résultat: %d"), move, temp_pion.move);
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
					
					leString.Format(_T("max: 1 avant"));
					m_listBox_move.InsertString(-1, leString);
					
					PrintGrid();
					UpdateWindow();

					leString.Format(_T("max: 1 apres - ID=0 dans %d  %d"),temp_pion.old_x, temp_pion.old_y);
					m_listBox_move.InsertString(-1, leString);

					GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].ID =0;						// Le pion quitte la case.  Indique comme vide avec ID=0;
					PrintGrid();
					UpdateWindow();
					
					
					leString.Format(_T("max: 2 avant"));
					m_listBox_move.InsertString(-1, leString); 
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
					
					

					leString.Format(_T("max: 2 apres"));
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
						


						// move: correspond au mouvement associé au score (directions (x,y) -> 0= +/+ , 1 = -/+, 2 = +/-, 3 = -/-)  -1: ne peut bouger le pion
						

						GridJeu.PushPionOnStack(retire_pion_opposant);			// push le pion dans le stack pour restauration future.
																				// L'ordre des moves sauvés sur le stack: 
																				
						
						// Mettre à jour le vecteur et la grille de  jeu:

						//Retire  le pion de la grille de jeu et du vecteur des pions de la grille pour continuer l'évaluation du jeu.
						//GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y] = 0 + retire pion du vecteurGrid
						
						leString.Format(_T("max: 3 avant"));
						m_listBox_move.InsertString(-1, leString);
						
						PrintGrid();
						UpdateWindow();

						GridJeu.RetirePionCalcul(retire_pion_opposant);			// Retire pion de la grille et du vecteur pion approprié.		
						
						leString.Format(_T("max: 3 apres"));
						m_listBox_move.InsertString(-1, leString);
													

						leString.Format(_T("Retiré pion ID: %d"), retire_pion_opposant.ID);
						m_listBox_move.InsertString(-1, leString);
						PrintGrid(); // ICI ON CHECK TEMP PION
						UpdateWindow();
						GridJeu.CalculScoreGrid();			// compte le nombre de pion de chaque joueur.
												// calcule le score pour ce pion.
						pion.score = (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum()) - (GridJeu.GetScoreGridOrdi() - GridJeu.GetScoreInitialOrdi());
						
						
					}; // if (temp_pion.move >= 0)
							
					temp_pion.old_x = temp_pion.new_x;	// met à jour les coordonnées pour l'évaluation de la grille qui suit avec la nouvelle configuration.
					temp_pion.old_y = temp_pion.new_y;

				v1 = CalculeMoveHum_min(temp_pion, le_niveau, alpha, beta);

					leString.Format(_T("7a-CalculeMoveHum: score: %d ,  niveau: %d,  move: %d, alpha: %d, beta: %d"), v1.score, le_niveau, v1.move, alpha, beta);
					m_ListBox_Suivi_Jeu.InsertString(-1, leString);
					
					//remettre le grid_sub dans l'état avant le mouvement.
					//move pion - moveStack pop;

					temp_pion = GridJeu.PopPionFromStack();


					if (temp_pion.removed) // Si a été retiré, alors remettre le pion retiré sur la grille de jeu.
					{
						
						
						temp_pion.removed = false;					// modifie la valeur avant de remettre dans le jeu.
						
						GridJeu.AjoutPionCalcul(temp_pion);			// Ajout pion dans le jeu (dans vecteur des pions actifs)
						
						
						leString.Format(_T("max: 4 avant"));
						m_listBox_move.InsertString(-1, leString);

						PrintGrid();
						UpdateWindow();
						
						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].ID = temp_pion.ID;
						 GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].old_x = temp_pion.old_x;
						 GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].old_y = temp_pion.old_y;
						 GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].new_x = temp_pion.new_x;
						 GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].new_y = temp_pion.new_y;
						 GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].dame = temp_pion.dame;
						 GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].score = temp_pion.score;
						 GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].move = temp_pion.move;
						 GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].removed = false;
						 
						// pas besoin de mettre à jour l'ancienne case puisque ce pion n'était pas sur la grille de jeu avant d'être réintégré.

						 leString.Format(_T("max: 4 apres"));
						 m_listBox_move.InsertString(-1, leString);
						 
						 PrintGrid(); 
						 UpdateWindow();
						

						 leString.Format(_T("Restaure pion ID: %d"), retire_pion_opposant.ID);
						 m_listBox_move.InsertString(-1, leString);

						// Remettre le pion dans la grille de jeu.

						 temp_pion = GridJeu.PopPionFromStack(); // récupérer le pion qui a fait le retrait.

						

					};

																	// Ici le pion a bougé et on le remet à sa position originale.

					leString.Format(_T(" Move ID: %d, Niv: %d  de: %d, %d  à %d, %d Niv: %d M: %d R: %d"), temp_pion.ID, le_niveau, temp_pion.new_x, temp_pion.new_y, temp_pion.old_x, temp_pion.old_y, le_niveau, move, temp_pion.move);
					m_listBox_move.InsertString(-1, leString);

					leString.Format(_T("max: 5 avant"));
					m_listBox_move.InsertString(-1, leString);
					PrintGrid();
					UpdateWindow();
					
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

					leString.Format(_T("max: 5 apres"));
					m_listBox_move.InsertString(-1, leString);
					PrintGrid();
					UpdateWindow();




						

					if (v1.score > v) v = v1.score;
					if (v1.score >= beta)
					{
						v1.score = v;

						leString.Format(_T("7b-CalculeMoveOrdi: score: %d ,  niveau: %d,  move: %d, alpha: %d, beta: %d"), v1.score, le_niveau, v1.move, alpha, beta);
						m_ListBox_Suivi_Jeu.InsertString(-1, leString);
						return v1;

					};
					if (v1.score > alpha)
					{
						
						alpha = v1.score;

						leString.Format(_T("7c-CalculeMoveOrdi: score: %d ,  niveau: %d,  move: %d, alpha: %d, beta: %d"), v1.score, le_niveau, v1.move, alpha, beta);
						m_ListBox_Suivi_Jeu.InsertString(-1, leString);
					}

					return v1;

				}   // fin: if (temp_pion.move >= 0)

				else
				{										// Ici , le pion ne peut bouger.  Calculer le score et retourner la valeur comme si le niveau max avait été atteint.
					
					leString.Format(_T(" Move ID: %d, Niv: %d  de: %d, %d  à %d, %d  Niv: %d M: %d R: %d"), temp_pion.ID,  le_niveau, temp_pion.old_x, temp_pion.old_y, temp_pion.new_x, temp_pion.new_y, le_niveau, move, temp_pion.move);
					m_listBox_move.InsertString(-1, leString);
					
					GridJeu.CalculScoreGrid();			
														// compte le nombre de pion de chaque joueur.
														// calcule le score pour ce pion.
					pion.score = (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum()) - (GridJeu.GetScoreGridOrdi() - GridJeu.GetScoreInitialOrdi());

					leString.Format(_T("7d-CalculeMoveOrdi Ne peut bouger pion. Calcul score: initialHumain: %d,  grid Humain: %d,  initial ordi: %d, grid Ordi: %d"), GridJeu.GetScoreInitialHum(), GridJeu.GetScoreGridHum(), GridJeu.GetScoreGridOrdi(), GridJeu.GetScoreGridOrdi());
					m_ListBox_Suivi_Jeu.InsertString(-1, leString);

					pion.move = -1;						// ici le pion ne peut bouger.
					return pion;
				};

			
			};  // boucle: for (move = 0; move < 4; move++)

			return pion;

		} // fin: if (niveau > GridJeu.max_niveau)
	
}




CGrid::pion CMFCDame3Dlg::CalculeMoveHum_min(CGrid::pion &pion, int niveau, int alpha, int beta)
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

		sizeVect = GridJeu.GetPionVectHumSize();
		le_niveau = le_niveau + 1;

		leString.Format(_T("8-CalculeMoveHum: Pion ordi ID: %d,  niveau: %d,  move: %d, alpha: %d, beta: %d"), v1.ID, le_niveau, v1.move, alpha, beta);
		m_ListBox_Suivi_Jeu.InsertString(-1, leString);

		if (le_niveau > GridJeu.max_niveau)
		{
			leString.Format(_T("9a-CalculeMoveHum MAX NIVEAU ATTEINT: Pion ID: %d,  niveau: %d,  move: %d, alpha: %d, beta: %d"), pion.ID, le_niveau, v1.move, alpha, beta);
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);
			
			GridJeu.CalculScoreGrid();			// compte le nombre de pion de chaque joueur.
			score = (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum()) - (GridJeu.GetScoreGridOrdi() - GridJeu.GetScoreInitialOrdi());
			v1.score = score;


			// CODE POUR TEST>  ENLEVER***********************

			int i;
			if (v1.score != 0)
			{
				i = 1;
			};

			// FIN CODE POUR TEST>  ENLEVER***********************


			leString.Format(_T("9b-CalculeMoveOrdi max niveau atteint: initialHumain: %d,  grid Humain: %d,  initial ordi: %d, grid Ordi: %d"), GridJeu.GetScoreInitialHum(), GridJeu.GetScoreGridHum(), GridJeu.GetScoreGridOrdi(), GridJeu.GetScoreGridOrdi());
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);

			leString.Format(_T("9c-CalculeMoveHum max niveau atteint: score: %d ,  niveau: %d,  move: %d, alpha: %d, beta: %d"), score , le_niveau, v1.move, alpha, beta);
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);
								   			
			return v1;
		};	// Fin : if (le_niveau > GridJeu.max_niveau)
		
		
		for (lePion = 0; lePion < sizeVect; lePion++)   // Boucle pour évaluer les pions du joueur ennemi.
		{
			my_pion = GridJeu.GetPionFromGridHumain(lePion);

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
					m_listBox_move.InsertString(-1, leString);

					// MOVE HUMAIN (min)

					
					leString.Format(_T("min: 6 avant"));
					m_listBox_move.InsertString(-1, leString);
					PrintGrid();
					UpdateWindow();


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
					
					
					leString.Format(_T("min: 6 apres: "));
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

							
							leString.Format(_T("min: 7 avant"));
							m_listBox_move.InsertString(-1, leString);
							PrintGrid();
							UpdateWindow();

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

							leString.Format(_T("min: 7 apres"));
							m_listBox_move.InsertString(-1, leString);
							PrintGrid();
							UpdateWindow();


							GridJeu.CalculScoreGrid();			// compte le nombre de pion de chaque joueur.
							score = (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum()) - (GridJeu.GetScoreGridOrdi() - GridJeu.GetScoreInitialOrdi());
							v1.score = score;
							return v1;

						};

						GridJeu.PushPionOnStack(retire_pion_opposant);			// push le pion dans le stack pour restauration future.
																				// L'ordre des moves sauvés sur le stack: 
						// Mettre à jour le vecteur et la grille de  jeu:

						//Retire  le pion de la grille de jeu et du vecteur des pions de la grille pour continuer l'évaluation du jeu.
						//GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y] = 0 + retire pion du vecteurGrid

						GridJeu.RetirePionCalcul(retire_pion_opposant);			// Retire pion de la grille et du vecteur pion approprié.		

						leString.Format(_T("Retiré pion ID: %d"), retire_pion_opposant.ID);
						m_listBox_move.InsertString(-1, leString);

						leString.Format(_T("12-CalculeMoveHum: Pion ID: %d,  niveau: %d,  move: %d, alpha: %d, beta: %d"), pion.ID, le_niveau, temp_pion.move, alpha, beta);
						m_ListBox_Suivi_Jeu.InsertString(-1, leString);

						leString.Format(_T(" Move ID: %d, Niv: %d  de: %d, %d  à %d, %d Niv: %d  M: %d R: %d"), temp_pion.ID, le_niveau, temp_pion.new_x, temp_pion.new_y, temp_pion.old_x, temp_pion.old_y, le_niveau, move, temp_pion.move);
						m_listBox_move.InsertString(-1, leString);

					};  // Fin: if (testremoved)

					v1 = CalculeMoveOrdi_max(v1, le_niveau, alpha, beta);

					temp_pion = GridJeu.PopPionFromStack();


					if (temp_pion.removed) // Remettre le pion retiré sur la grille de jeu.
					{


						temp_pion.removed = false;					// modifie la valeur avant de remettre dans le jeu.

						GridJeu.AjoutPionCalcul(temp_pion);			// Ajout pion dans le jeu (dans vecteur des pions actifs)

						
						leString.Format(_T("min: 8 avant"));
						m_listBox_move.InsertString(-1, leString);
						PrintGrid();
						UpdateWindow();

						GridJeu.grid_sub[temp_pion.old_x][temp_pion.old_y].ID = temp_pion.ID;
						GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].old_x = temp_pion.old_x;
						GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].old_y = temp_pion.old_y;
						GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].new_x = temp_pion.new_x;
						GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].new_y = temp_pion.new_y;
						GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].dame = temp_pion.dame;
						GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].score = temp_pion.score;
						GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].move = temp_pion.move;
						GridJeu.grid_sub[retire_pion_opposant.old_x][retire_pion_opposant.old_y].removed = false;
						
						
						leString.Format(_T("min: 8 apres"));
						m_listBox_move.InsertString(-1, leString);
						PrintGrid();
						UpdateWindow();


						leString.Format(_T("Restaure pion ID: %d"), retire_pion_opposant.ID);
						m_listBox_move.InsertString(-1, leString);

						// Remettre le pion dans la grille de jeu.

						temp_pion = GridJeu.PopPionFromStack(); // récupérer le pion qui a fait le retrait.



					};

					// Ici le pion a bougé et on le remet à sa position originale.

					
					leString.Format(_T("min: 9 avant"));
					m_listBox_move.InsertString(-1, leString);
					PrintGrid();
					UpdateWindow();

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

					leString.Format(_T("min: 9 apres"));
					m_listBox_move.InsertString(-1, leString);
					PrintGrid();
					UpdateWindow();

					leString.Format(_T(" Move ID: %d, Niv: %d  de: %d, %d  à %d, %d Niv: %d M: %d R: %d"), temp_pion.ID, le_niveau, temp_pion.new_x, temp_pion.new_y, temp_pion.old_x, temp_pion.old_y, le_niveau, move, temp_pion.move);
					m_listBox_move.InsertString(-1, leString);

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
					m_listBox_move.InsertString(-1, leString);
						
						
						
					GridJeu.CalculScoreGrid();			// compte le nombre de pion de chaque joueur.
															// calcule le score pour ce pion.
					v1.score = (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum()) - (GridJeu.GetScoreGridOrdi() - GridJeu.GetScoreInitialOrdi());

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
	unsigned int i, vectorsize;
	CGrid::pion lepion;
	CString leString;

	lepion = GridJeu.TrouveBestPionOrdi();
	leString.Format(_T("Score: ID %d,  score: %d,  move: %d."), lepion.ID, lepion.score, lepion.move);
	m_listBox_move.InsertString(-1, leString);


};