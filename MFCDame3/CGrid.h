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
		bool removed;							// removed = true: on peut retirer un pion ennemi. Utilise la procédure d'removed pour corriger le jeu.
												// removed = False: on ne peut retirer un pion ennemi. Mouvement normal.

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


	//void RetirePionGrid(int pionID, int main_sub);	// test ok
	void RetirePionJeu(pion pionID);					// test ok
	
	void AjoutPionCalcul(pion lePion);				// Utilisé pour remettre un pion en jeu après que le calcul l'impliquant soit terminé.
	void RetirePionCalcul(pion lePion);				// Utilisé pour retirer un pion du jeu lors du calcul (pion retiré lors du calcul, pour évaluation par minimax)

	void ResetScorePions();
	int SetPionScore(pion pionID, int score, int move);

	int GetPionVectOrdiSize();
	int GetPionVectHumSize();

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

	//pion CalculeMovePionOrdi_max(pion & m_pion, int niveau, int alpha, int beta);
	//pion CalculeMovePionHumain_min(pion &pion, int niveau, int alpha, int beta);
	pion EvalueMove(pion & pion_1, int m_delta_X, int m_delta_y, int le_niveau, int move);
	

	pion grid_sub[10][10];						//grid secondaire utilisé pour suivre le mouvement des pions lors du calcul MINIMAX.

	pion grid_main[10][10];						//grid principal avant changement.  PAS D'UTILISATION POUR LE MOMENT. 
	int max_niveau = 2;


	// OPERATIONS SUR LE STACK DES MOUVEMENTS DE PIONS

	void PushPionOnStack(pion & lePion);
	pion PopPionFromStack();

private:

	int score_ordi_initial, score_humain_initial;
	int score_ordi_grid, score_humain_grid;

	
	int max_grid_size = 10;						// grille de 10 par 10 max (selon le web, c'est le grid pour un jeu de dame)

												// deplacement permis en y (+/-)
	std::vector <pion> pion_vector_ordi;		// contient l'état des pions ordi du jeu
	std::vector <pion> pion_vector_humain;		// contient l'état des pions humains du jeu
	std::stack<pion> stack_move_pion;		// contient les mouvements qui sont effectués sur la grille de jeu lors de l'évaluation  minimax.
	std::vector <pion> pion_vector_grid_ordi;
	std::vector <pion> pion_vector_grid_humain;



};


	
	
