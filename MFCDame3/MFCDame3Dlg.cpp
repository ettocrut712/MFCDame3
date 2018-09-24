
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

	GridJeu.CloneGrid();
	m_ListBox_Suivi_Jeu.InsertString(-1, _T("Clone grid_main vers grid_sub"));

	OnClickedCalculScoreInitialButton();
	OnClickedCalculScoreGridSubButton();

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

	OnClickedCalculScoreInitialButton();
	OnClickedCalculScoreGridSubButton();


	int i = 0;
	i = i + 1;
}


void CMFCDame3Dlg::OnClickedRetirePionButton()
{
	// TODO: Add your control notification handler code here

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

/*	for (i = -20; i < 21; i++)
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

		
		
		for (move = 0; move < 2; move++)			// changer le 2 en fonction du type de pion: dame = 4 moves.  Pion -> 2 moves max.
		{
			m_pion_evalue = GridJeu.EvalueMove( my_pion, GridJeu.delta_x, GridJeu.delta_y, niveau, move);


			leString.Format(_T("Pion: %d ,  move: %d .  Resultat: %d"), pionID, move, m_pion_evalue.move);
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
		my_pion = GridJeu.GetPionFromVectOrdi(pionID);



		leString.Format(_T("1-OnClickButton: Pion no:  %d    Pion ID: %d, niveau %d"), pionID, my_pion.ID, le_niveau);
		m_ListBox_Suivi_Jeu.InsertString(-1, leString);

		minimax_pion = CalculeMoveOrdi_max(my_pion, le_niveau, alpha, beta);  // minimax_pion est le résultat de l'évaluation complétée pour les mouvements de ce pion.


		


		if (minimax_pion.move < 0)
		{															// ici le pion ne peut bouger.  Donc pas de score valide.
			leString.Format(_T("2-OnClickButton: (move <0)  Pion ID: %d,  score:  %d,  move: %d, alpha: %d, beta: %d"), minimax_pion.ID, minimax_pion.score, minimax_pion.move, alpha, beta);
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);
		
		}

		else
		{															// ici le pion a pu bouger.  Donc on met à jour le score pour ce pion
			GridJeu.SetPionScore(minimax_pion.ID, minimax_pion.score, minimax_pion.move);
			
			
			leString.Format(_T("2-OnClickButton: (move <0)  Pion ID: %d,  score:  %d,  move: %d, alpha: %d, beta: %d"), minimax_pion.ID, minimax_pion.score, minimax_pion.move, alpha, beta);
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);


		};
		
																	


	};

																	// Une fois tous les pions évalués.  On choisit le meilleur pion à bouger


	
};


CGrid::pion CMFCDame3Dlg::CalculeMoveOrdi_max(CGrid::pion &pion, int niveau, int alpha, int beta)  // max
{
	// TODO: Add your implementation code here.
	//CalculeMoveOrdi_max(CGrid::pion &pion, int niveau, int alpha, int beta)

		// TODO: Add your implementation code here.

	
	{
		int v = -1000;
		CGrid::pion v1;
		CString leString;

		v1.score = -1000;
		v1.ID = pion.ID;
		v1.move = pion.move;
		v1.old_x = pion.old_x;
		v1.old_y = pion.old_y;
		v1.new_x = pion.new_x;
		v1.new_y = pion.new_y;
		v1.score = pion.score;
		v1.attaque = pion.attaque;
		v1.dame = pion.attaque;
	


		int le_niveau = niveau;
		le_niveau = le_niveau + 1;

		int move;

		leString.Format(_T("4-CalculeMoveOrdi: Pion ID: %d,  niveau: %d,  move: %d, alpha: %d, beta: %d"), pion.ID, le_niveau, v1.move, alpha, beta  );
		m_ListBox_Suivi_Jeu.InsertString(-1, leString);

		CGrid::pion temp_pion;

		if (niveau > GridJeu.max_niveau)
		{

			leString.Format(_T("5-CalculeMoveOrdi max niveau atteint: Pion ID: %d,  niveau: %d,  move: %d, alpha: %d, beta: %d"), pion.ID, le_niveau, v1.move, alpha, beta);
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);
			
			GridJeu.CalculScoreGrid();			// compte le nombre de pion de chaque joueur.
										// calcule le score pour ce pion.
			v1.score = (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum()) - (GridJeu.GetScoreGridOrdi() - GridJeu.GetScoreInitialOrdi());




			return v1;
		}
		else
		{
			for (move = 0; move < 2; move++)
			{
				v1.move = move;
				temp_pion = GridJeu.EvalueMove(pion, GridJeu.delta_x, GridJeu.delta_y, le_niveau, move);

				leString.Format(_T("6-CalculeMoveOrdi.evalueMove   Move: %d -> Résultat: %d"), move, temp_pion.move);
				m_ListBox_Suivi_Jeu.InsertString(-1, leString);

				if (temp_pion.move > -1)			//  >0 veut dire que le pion peut bouger.  <0 , le pion ne peut faire le move.  Donc on passe au move suivant.
				{
					//	move pion - moveStack push;

					leString.Format(_T("7-CalculeMoveOrdi-> CalculeMoveHumain Pion ID: %d,  niveau: %d,  move: %d, alpha: %d, beta: %d"), pion.ID, le_niveau, v1.move, alpha, beta);
					m_ListBox_Suivi_Jeu.InsertString(-1, leString);

					v1 = CalculeMoveHum_min(v1, le_niveau, alpha, beta);

					leString.Format(_T("7a-CalculeMoveOrdi: score: %d ,  niveau: %d,  move: %d, alpha: %d, beta: %d"), v1.score, le_niveau, v1.move, alpha, beta);
					m_ListBox_Suivi_Jeu.InsertString(-1, leString);
					

					// move pion - moveStack pop;

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
				}
				else
				{
					//v1.move = -1;					// ici le pion ne peut bouger.
					//return v1;
				};


			};

			return v1;

		}
	};
}




CGrid::pion CMFCDame3Dlg::CalculeMoveHum_min(CGrid::pion &pion, int niveau, int alpha, int beta)

	// TODO: Add your implementation code here.
	//CalculeMovePionHumain_min(pion &pion, int niveau, int alpha, int beta)
	{

		CGrid::pion v1, my_pion, temp_pion;
		CString leString;

		int le_niveau, v;
		le_niveau = niveau;
		int score, move;
		int sizeVect;
		int lePion;

		v = 1000;
		v1.ID = pion.ID;
		v1.move = pion.move;
		v1.old_x = pion.old_x;
		v1.old_y = pion.old_y;
		v1.new_x = pion.new_x;
		v1.new_y = pion.new_y;
		v1.score = pion.score;
		v1.attaque = pion.attaque;
		v1.dame = pion.attaque;

		sizeVect = GridJeu.GetPionVectHumSize();
		le_niveau = le_niveau + 1;

		leString.Format(_T("8-CalculeMoveHum: Pion ordi ID: %d,  niveau: %d,  move: %d, alpha: %d, beta: %d"), v1.ID, le_niveau, v1.move, alpha, beta);
		m_ListBox_Suivi_Jeu.InsertString(-1, leString);

		if (le_niveau > GridJeu.max_niveau)
		{
			leString.Format(_T("9a-CalculeMoveHum max niveau atteint: Pion ID: %d,  niveau: %d,  move: %d, alpha: %d, beta: %d"), pion.ID, le_niveau, v1.move, alpha, beta);
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);
			
			GridJeu.CalculScoreGrid();			// compte le nombre de pion de chaque joueur.
			score = (GridJeu.GetScoreInitialHum() - GridJeu.GetScoreGridHum()) - (GridJeu.GetScoreGridOrdi() - GridJeu.GetScoreInitialOrdi());
			v1.score = score;


			leString.Format(_T("9b-CalculeMoveHum max niveau atteint: score: %d ,  niveau: %d,  move: %d, alpha: %d, beta: %d"), score , le_niveau, v1.move, alpha, beta);
			m_ListBox_Suivi_Jeu.InsertString(-1, leString);
			
			return v1;
		}
		else
		{
			for (lePion = 0; lePion < sizeVect; lePion++)
			{
				my_pion = GridJeu.GetPionFromVectHumain(lePion);

				leString.Format(_T("10-CalculeMoveHum: pion no: %d   ID: %d "), lePion, my_pion.ID);
				m_ListBox_Suivi_Jeu.InsertString(-1, leString);

				for (move = 0; move < 2; move++)  // LIMITE A MODIFIER...
				{
					temp_pion = GridJeu.EvalueMove(my_pion, GridJeu.delta_x, GridJeu.delta_y, le_niveau, move);
					

					leString.Format(_T("11-CalculeMoveHum: pion iD: %d,  move %d, Résultat:  %d"), temp_pion.ID, move, temp_pion.move);
					m_ListBox_Suivi_Jeu.InsertString(-1, leString);

					
					if (temp_pion.move > -1)			//  >0 veut dire que le pion peut bouger.  <0 , le pion ne peut faire le move.  Donc on passe au move suivant.
					{
						//	move pion - ordi dans moveStack;

						leString.Format(_T("12-CalculeMoveHum: Pion ID: %d,  niveau: %d,  move: %d, alpha: %d, beta: %d"), pion.ID, le_niveau, temp_pion.move, alpha, beta);
						m_ListBox_Suivi_Jeu.InsertString(-1, leString);


						v1 = CalculeMoveOrdi_max(v1, le_niveau, alpha, beta);
						// move pion - remove from stack

						if (v1.score < v) v = v1.score;
						if (v1.score <= alpha)
						{
							v1.score = v;
							return v1;
						}
						if (v1.score < beta) beta = v1.score;

					}
					else
					{
						//v1.move = -1;
						//return v1;


					}
				}
			}
			return v1;
		}
	};
