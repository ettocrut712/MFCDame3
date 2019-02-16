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
		int old_x=0;							// coordonnees X (origine lors d'un d�placement)
		int old_y=0;							// coordonnees Y
		int new_x=0;							// coordonnees X (destination lors d'un d�placement)
		int new_y=0;							// coordonnees Y
		

		bool hasMoved = FALSE;					// TRUE: le pion s'est d�plac�,  FALSE: le pion ne s'est pas d�plac�.  Utilis� lors de l'�valuation des mouvements possibles des pions.
												// Si le pion ne s'est pas d�plac�, alors sa position est dans old_x, old_y.  Si le pion s'est d�plac�, sa position est dans new_x, new_y.

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

	void CreatePionsOrdi();							// test ok
	void CreatePionHumain();						// test ok

	void TransferTousPionToMainGrid();					// test ok


	//void RetirePionGrid(int pionID, int main_sub);	// test ok
	void RetirePionJeu(pion pionID);					// test ok  Quand l'analyse est compl�t�e, on retire un pion d�finitivement du jeu ici.
	
	void AjoutPionGrid_old(pion lePion);				// Utilis� pour remettre un pion en jeu apr�s que le calcul l'impliquant soit termin�.
	void AjoutPionGrid_new(pion lePion);				// Utilis� pour remettre un pion en jeu apr�s que le calcul l'impliquant soit termin�.
	pion RetirePionCalcul(pion lePion);				// Utilis� pour retirer un pion du jeu lors du calcul (pion retir� lors du calcul, pour �valuation par minimax)
	void AjustePionVectorGrid(pion lePion);
	

	void ResetScorePions();
	int SetPionScore(pion pionID);

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
	void CalculScoreGrid();							// test ok
	

	// MOUVEMENT DES PIONS

	
	pion EvalueMove(pion & pion_1, int m_delta_X, int m_delta_y, int le_niveau, int move);

	bool MovePion(pion & pion_1, int m_delta_X, int m_delta_y, int move);
	

	pion grid_sub[10][10];						//grid secondaire utilis� pour suivre le mouvement des pions lors du calcul MINIMAX.

	pion grid_main[10][10];						//grid principal avant changement.  PAS D'UTILISATION POUR LE MOMENT. 
	
	int max_niveau = 2;
	int max_grid_size = 10;						// grille de 10 par 10 max (selon le web, c'est le grid pour un jeu de dame)

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


	
	
