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
		long int ID;							// ID du pion
		int old_x;								// coordonnees X (origine lors d'un déplacement)
		int old_y;								// coordonnees Y
		int new_x;								// coordonnees X (destination lors d'un déplacement)
		int new_y;								// coordonnees Y

		bool dame;  							// si le pion devient une dame, alors dame = TRUE;
		int score;								// score calculé pour ce pion (évaluation minimax)
		int move;								// correspond au mouvement associé au score (directions (x,y) -> 0= +/+ , 1 = -/+, 2 = +/-, 3 = -/-)  -1: ne peut bouger le pion
		bool attaque;							// attaque = true: on peut retirer un pion ennemi. Utilise la procédure d'attaque pour corriger le jeu.
												// attaque = False: on ne peut retirer un pion ennemi. Mouvement normal.

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

	void TransferTousPionToGrid();					// test ok


	void RetirePionGrid(int pionID, int main_sub);	// test ok
	void RetirePionJeu(int pionID);					// test ok
	
	void ResetScorePions();
	int SetPionScore(int pionID, int score, int move);

	int GetPionVectOrdiSize();
	int GetPionVectHumSize();
	pion GetPionFromVectOrdi(int le_pion);
	pion GetPionFromVectHumain(int le_pion);

	pion_move TrouveBestPionOrdi();
	pion_move TrouveBestPionHumain();


	// OPERATIONS SUR LES GRILLES DE JEU (MAIN, SUB)

	void CloneGrid();								// test ok
	void ResetMainGrid();
	
	void ResetSubGrid();

	// CALCUL DU POINTAGE

	int GetScoreInitialOrdi();						// test ok
	int GetScoreInitialHum();						// test ok
	void CalculScoreInitial();						// test ok
	
	int GetScoreGridOrdi();							// test ok
	int GetScoreGridHum();							// test ok
	void CalculScoreGrid();							// test ok
	

	// MOUVEMENT DES PIONS

	pion CalculeMovePionOrdi_max(pion & m_pion, int niveau, int alpha, int beta);
	pion CalculeMovePionHumain_min(pion &pion, int niveau, int alpha, int beta);
	pion EvalueMove(pion & pion_1, int m_delta_X, int m_delta_y, int le_niveau, int move);
	

	int grid_sub[10][10];						//grid secondaire après changement.  Transféré au niveau suivant pour suite des calculs (recursion)
	int grid_main[10][10];						//grid principal avant changement 
	int max_niveau = 3;


private:

	int score_ordi_initial, score_humain_initial;
	int score_ordi_grid, score_humain_grid;

	
	int max_grid_size = 10;						// grille de 10 par 10 max (selon le web, c'est le grid pour un jeu de dame)

												// deplacement permis en y (+/-)
	std::vector <pion> pion_vector_ordi;		// contient l'état des pions ordi du jeu
	std::vector <pion> pion_vector_humain;		// contient l'état des pions humains du jeu
	std::stack<pion_move> stack_move_pion;		// contient les mouvements qui sont effectués sur la grille de jeu lors de l'évaluation  minimax.


};


	
	
