#pragma once

#include <vector>
#include <array>
#include <CString>
#include <string>
#include <stack>




class CGrid
{
public:
	CGrid();
	~CGrid();


	struct pion
	{
		long int ID=0;							// ID du pion.  ID > 0 = ordi. ID < 0 = humain (l'autre  joueur).
		int actual_x=0;							// coordonnees X (origine lors d'un d�placement)
		int actual_y=0;							// coordonnees Y
		int new_x=0;							// coordonnees X (destination lors d'un d�placement)
		int new_y=0;							// coordonnees Y
		

		bool hasMoved = FALSE;					// TRUE: le pion s'est d�plac�,  FALSE: le pion ne s'est pas d�plac�.  Utilis� lors de l'�valuation des mouvements possibles des pions.
												// Si le pion ne s'est pas d�plac�, alors sa position est dans actual_x, actual_y.  Si le pion s'est d�plac�, sa position est dans new_x, new_y.

		int niveau =0;							// indique � quel niveau ( cycle min/max) le pion a �t� d�plac�.  Si plusieurs pions sont d�plac�s lorsque au m�me niveau, ils ont tous le "niveau" identique. 
		bool dame = FALSE;  					// si le pion devient une dame, alors dame = TRUE;
		int score =0;							// score calcul� pour ce pion (�valuation minimax)
		int move=0;								// correspond au mouvement associ� au score (directions (x,y) -> 0= +/+ , 1 = -/+, 2 = +/-, 3 = -/-)  -1: ne peut bouger le pion
		bool removed= FALSE;					// removed = true: on peut retirer un pion ennemi. Les coordonn�es du pion retir� sont dans removed_x,y.
												// removed = False: on ne peut retirer un pion ennemi. Mouvement normal.
		int removed_x = 0;						// coordonn�es du pion retir� 
		int removed_y = 0;						// coordonn�es du pion retir�
		int removed_ID = 0;

		int alpha = 0;							// pour l'algorithme minimax.  
		int beta = 0;

	};

	struct pion_move
	{
		int ID;
		int score;
		int move;

	};

	int niveau;
	const int delta_x = 1;							// deplacement permis en x (+/-)
	const int delta_y = 1;


	// OPERATIONS SUR LES PIONS

	void CreatePionsOrdi();							
	void CreatePionHumain();							

	void TransferTousPionToMainGrid();					


	//void RetirePionGrid(int pionID, int main_sub);	
	void RetirePionJeu(pion pionID);					//   Quand l'analyse est compl�t�e, on retire un pion d�finitivement du jeu ici.
	
	void AjoutPion_to_Grid__at_actual_xy(pion lePion);				// Utilis� pour remettre un pion en jeu apr�s que le calcul l'impliquant soit termin�.
	void AjoutPion_to_Grid__at_new_xy(pion lePion);				// Utilis� pour remettre un pion en jeu apr�s que le calcul l'impliquant soit termin�.
	void AjoutPionGrid_removed(pion lePion);			// Utilis� pour remettre en jeu un pion qui a �t� enlev� lors des calculs.
	
	
	pion RetirePionCalcul(pion lePion);					// Utilis� pour retirer un pion du jeu lors du calcul (pion retir� lors du calcul, pour �valuation par minimax)
	void AjustePion_in_VectorGrid_to_new_xy(pion lePion);				//Utilis� pour corriger un pion qui s'est d�plac�.  new x,y -> old x,y
	void AjustePion_in_VectorGrid_to_removed_xy(pion lePion);		// Utilis� pour corriger le vecteur "pion" pour un pion qui a �t� retir� et qu'on remet en jeu. removed x,y -> old x,y
	void AjustePion_in_VectorGrid_to_actual_xy(pion lePion);			// Utilis� pour corriger le vecteur "pion" pour un pion qui a �t� d�plac� et qu'on remet � son origine. (lePion. old x,y -> old x,y)


	void ResetScorePions();
	int SetPionScore(pion pionID);
	int GetPionScore(pion pionID);

	int GetPionVectOrdiSize();
	int GetPionVectHumSize();

	int GetPionVectOrdi_grid_Size();
	int GetPionVectHum_grid_Size();


	pion GetPionFromVectOrdi(int le_pion);
	pion GetPionFromVectHumain(int le_pion);

	pion GetPionFromGridOrdi(int le_pion);
	pion GetPionFromGridHumain(int le_pion);

	pion TrouveBestPionOrdi();
	pion TrouveBestPionHumain();


	// OPERATIONS SUR LES GRILLES DE JEU (MAIN, SUB)

	void CloneGridMainToSub();								// test ok
	
	void ResetPionVectorGrid();						// Reset le vecteur des pions pr�sents sur la grille de jeu (utilis� lors du calcul de mouvements).  
													// Ne modifie pas le jeu. Modifie la grille de jeu pour calcul



	// CALCUL DU POINTAGE

	int GetScoreInitialOrdi();						// test ok
	int GetScoreInitialHum();						// test ok
	void CalculScoreInitial();						// test ok
	
	int GetScoreGridOrdi();							// test ok
	int GetScoreGridHum();							// test ok
	void ComptePionsGrid();							// test ok
	int CalculScoreGrid_max(CGrid::pion &lePion);
	int CalculScoreGrid_min(CGrid::pion &lePion);

	// MOUVEMENT DES PIONS

	
	pion EvalueMove(pion & pion_1, int m_delta_X, int m_delta_y, int le_niveau, int move);

	bool MovePion(pion & pion_1, int m_delta_X, int m_delta_y, int move);
	

	pion grid_sub[10][10];						//grid secondaire utilis� pour suivre le mouvement des pions lors du calcul MINIMAX.

	pion grid_main[10][10];						//grid principal avant changement.  PAS D'UTILISATION POUR LE MOMENT. 
	
	int max_niveau = 2;
	int max_grid_size = 10;						// grille de 10 par 10 max (selon le web, c'est le grid pour un jeu de dame)

	int unsigned m_nbre_pion_meilleurs = 7;

	// OPERATIONS SUR LE vecteur DES MOUVEMENTS DE PIONS

	void PushPionOnMoveVector(pion & lePion);
	pion PopPionFromMoveVector();
	std::vector <pion> pion_vecteur_retire_calcul;	// contient les pions qui sont retir�s temporairement pour le calcul.



	int score_ordi_initial, score_humain_initial;
	int score_ordi_grid, score_humain_grid;

	
	

												// deplacement permis en y (+/-)
	std::vector <pion> pion_vector_ordi;		// contient l'�tat des pions ordi du jeu
	std::vector <pion> pion_vector_humain;		// contient l'�tat des pions humains du jeu
	std::vector<pion> vector_move_pion;			// contient les mouvements qui sont sauvegard�s lors de l'�valuation  minimax.
	std::vector <pion> pion_vector_grid_ordi;	// contient l'�tat des pions ordi de la grille de jeu
	std::vector <pion> pion_vector_grid_humain;	// contient l'�tat des pions humains de la grille de jeu
	


};


	
	
