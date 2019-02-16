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
		int old_x=0;							// coordonnees X (origine lors d'un déplacement)
		int old_y=0;							// coordonnees Y
		int new_x=0;							// coordonnees X (destination lors d'un déplacement)
		int new_y=0;							// coordonnees Y
		

		bool hasMoved = FALSE;					// TRUE: le pion s'est déplacé,  FALSE: le pion ne s'est pas déplacé.  Utilisé lors de l'évaluation des mouvements possibles des pions.
												// Si le pion ne s'est pas déplacé, alors sa position est dans old_x, old_y.  Si le pion s'est déplacé, sa position est dans new_x, new_y.

		int niveau =0;							// indique à quel niveau ( cycle min/max) le pion a été déplacé.  Si plusieurs pions sont déplacés lorsque au même niveau, ils ont tous le "niveau" identique. 
		bool dame = FALSE;  					// si le pion devient une dame, alors dame = TRUE;
		int score =0;							// score calculé pour ce pion (évaluation minimax)
		int move=0;								// correspond au mouvement associé au score (directions (x,y) -> 0= +/+ , 1 = -/+, 2 = +/-, 3 = -/-)  -1: ne peut bouger le pion
		bool removed= FALSE;					// removed = true: on peut retirer un pion ennemi. Les coordonnées du pion retiré sont dans removed_x,y.
												// removed = False: on ne peut retirer un pion ennemi. Mouvement normal.
		int removed_x = 0;						// coordonnées du pion retiré 
		int removed_y = 0;						// coordonnées du pion retiré
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
	void RetirePionJeu(pion pionID);					// test ok  Quand l'analyse est complétée, on retire un pion définitivement du jeu ici.
	
	void AjoutPionGrid_old(pion lePion);				// Utilisé pour remettre un pion en jeu après que le calcul l'impliquant soit terminé.
	void AjoutPionGrid_new(pion lePion);				// Utilisé pour remettre un pion en jeu après que le calcul l'impliquant soit terminé.
	pion RetirePionCalcul(pion lePion);				// Utilisé pour retirer un pion du jeu lors du calcul (pion retiré lors du calcul, pour évaluation par minimax)
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
	
	void ResetPionVectorGrid();						// Reset le vecteur des pions présents sur la grille de jeu (utilisé lors du calcul de mouvements).  
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
	

	pion grid_sub[10][10];						//grid secondaire utilisé pour suivre le mouvement des pions lors du calcul MINIMAX.

	pion grid_main[10][10];						//grid principal avant changement.  PAS D'UTILISATION POUR LE MOMENT. 
	
	int max_niveau = 2;
	int max_grid_size = 10;						// grille de 10 par 10 max (selon le web, c'est le grid pour un jeu de dame)

	// OPERATIONS SUR LE vecteur DES MOUVEMENTS DE PIONS

	void PushPionOnMoveVector(pion & lePion);
	pion PopPionFromMoveVector();
	std::vector <pion> pion_vecteur_retire_calcul;	// contient les pions qui sont retirés temporairement pour le calcul.



	int score_ordi_initial, score_humain_initial;
	int score_ordi_grid, score_humain_grid;

	
	

												// deplacement permis en y (+/-)
	std::vector <pion> pion_vector_ordi;		// contient l'état des pions ordi du jeu
	std::vector <pion> pion_vector_humain;		// contient l'état des pions humains du jeu
	std::vector<pion> vector_move_pion;			// contient les mouvements qui sont sauvegardés lors de l'évaluation  minimax.
	std::vector <pion> pion_vector_grid_ordi;	// contient l'état des pions ordi de la grille de jeu
	std::vector <pion> pion_vector_grid_humain;	// contient l'état des pions humains de la grille de jeu
	


};


	
	
