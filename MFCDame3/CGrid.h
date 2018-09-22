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

/*	struct gridJeu
	{
		int ID;						// ID du pion qui est au point x,y
		int niveauGrid;				// niveau où on est rendu dans l'évaluation
		int grid[10][10];			// coordonnées de la casse
				

	};
	*/

	struct pion
	{
		long int ID;							// ID du pion
		int old_x;									// coordonnees X (origine lors d'un déplacement)
		int old_y;									// coordonnees Y
		int new_x;									// coordonnees X (origine lors d'un déplacement)
		int new_y;									// coordonnees Y

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
	int delta_x = 1;							// deplacement permis en x (+/-)
	int delta_y = 1;

	void RetirePionGrid(int pionID, int main_sub);	// test ok
	void RetirePionJeu(int pionID);					// test ok
	void TransferTousPionToGrid();					// test ok
	void CloneGrid();								// test ok
	void ResetMainGrid();
	pion_move TrouveBestPionOrdi();
	void CalculScoreInitial();						// test ok					
	void CalculScoreGrid();							// test ok
	int GetScoreInitialOrdi();						// test ok
	int GetScoreInitialHum();						// test ok
	int GetScoreGridOrdi();							// test ok
	int GetScoreGridHum();							// test ok
	

	int CalculeMovePionOrdi_max(int niveau, int alpha, int beta);
	int CalculeMovePionHumain_min(int niveau, int alpha, int beta);


	pion_move TrouveBestPionHumain();
	void ResetScorePions();
	int SetPionScore(int pionID, int score, int move);
	void ResetSubGrid();
	void CreatePionsOrdi();							// test ok
	void CreatePionHumain();						// test ok

	pion EvalueMove(pion & pion_1, int m_delta_X, int m_delta_y, int le_niveau, int move);
	
	int GetPionVectOrdiSize();
	int GetPionVectHumSize();
	pion GetPionFromVectOrdi(int le_pion);
	pion GetPionFromVectHumain(int le_pion);
	
	


	int grid_sub[10][10];						//grid secondaire après changement.  Transféré au niveau suivant pour suite des calculs (recursion)
	int grid_main[10][10];						//grid principal avant changement 
	int max_niveau = 2;


private:

	int score_ordi_initial, score_humain_initial;
	int score_ordi_grid, score_humain_grid;


	//gridJeu grid_Main;
//	gridJeu grid_Sub;

	


	
	
	int max_grid_size = 10;						// grille de 10 par 10 max (selon le web, c'est le grid pour un jeu de dame)

							// deplacement permis en y (+/-)
	std::vector <pion> pion_vector_ordi;
	std::vector <pion> pion_vector_humain;
	std::stack<pion_move> stack_move_pion;


};


	
	
