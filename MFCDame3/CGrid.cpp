#include "stdafx.h"
#include "CGrid.h"

#define DEBUG	// utilisé pour le debuggage du programme...

CGrid::CGrid()

{
	CGrid::niveau = 0;
	//CGrid::grid_main=0;
	//CGrid::grid_sub=0;
	CGrid::score_humain_initial=0;
	CGrid::score_ordi_initial=0;
	CGrid::score_ordi_grid=0;
	CGrid::score_humain_grid=0;
}


CGrid::~CGrid()
{
}



void CGrid::AjoutPionCalcul(pion lePion)
{							// Utilisé pour remettre un pion en jeu après que le calcul (MINIMAX) l'impliquant soit terminé.
							// Ajoute le pion sur la grille de jeu et restaure la situation tel qu'avant le retrait pour évaluation.
							// Ajoute le pion sur le vecteur des pions du grid.

	unsigned int i;

	grid_sub[lePion.removed_x][lePion.removed_y].ID = lePion.ID;									// ID du pion.

	/*grid_sub[lePion.old_x][lePion.old_y].removed = lePion.removed;							// état du pion (removed = pion retiré)
	grid_sub[lePion.old_x][lePion.old_y].new_x = lePion.new_x;								// coordonnees X (destination lors d'un déplacement)
	grid_sub[lePion.old_x][lePion.old_y].new_y = lePion.new_y;								// coordonnees Y
	grid_sub[lePion.old_x][lePion.old_y].old_x = lePion.old_x;								// coordonnees X (destination lors d'un déplacement)
	grid_sub[lePion.old_x][lePion.old_y].old_y = lePion.old_y;								// coordonnees Y
	grid_sub[lePion.old_x][lePion.old_y].dame = lePion.dame;								// si le pion devient une dame, alors dame = TRUE;
	grid_sub[lePion.old_x][lePion.old_y].score = lePion.score;								// score calculé pour ce pion (évaluation minimax)
	grid_sub[lePion.old_x][lePion.old_y].move = lePion.move;								// dernier move du pion
*/


	for (i = 0; i < pion_vecteur_retire_calcul.size(); i++)
	{
		if (pion_vecteur_retire_calcul.at(i).ID == lePion.ID)
		{
			pion_vecteur_retire_calcul.erase(pion_vecteur_retire_calcul.begin() + i);

		};

	};

	
};				


void CGrid::RetirePionCalcul(pion lePion)

{							// Utilisé pour retirer un pion du jeu lors du calcul (pion retiré lors du calcul, pour évaluation par MINIMAX)
							// Retire le pion sur la grille de jeu.
							// Retire le pion sur le vecteur des pions du grid.
							// Le pion reste parmi les pions du joueurs jusqu'après l'évaluation des mouvements.  Le retrait se fait ailleurs quand le mouvement devient officiel.

	int i;

							// Retire le pion du vecteur des pions actifs.  Et retire pion de la grille de jeu sub_main (pour évaluation MINIMAX)


	grid_sub[lePion.removed_x][lePion.removed_y].ID = 0;

	pion_vecteur_retire_calcul.push_back(lePion);  // Ajoute le pion à la liste des pions retirés.



	// Met à jour le vecteur qui contient la grille de jeu.  Requis afin d'effectuer un scan de tous les pions actifs seulement.

	if (lePion.ID > 0)							// ID >0 -> pion ordi  , ID < 0 -> pion_humain
	{
		for (i = 0; i < pion_vector_grid_ordi.size(); i++)
		{
			if (pion_vector_grid_ordi.at(i).ID == lePion.ID)
			{
				pion_vector_grid_ordi.erase(pion_vector_grid_ordi.begin() + i);
			
			};

		};

	}
	else									// ID < 0, donc pion humain.
	{
		for (i = 0; i < pion_vector_grid_humain.size(); i++)
		{
			if (pion_vector_grid_humain.at(i).ID == lePion.ID)
			{
				pion_vector_grid_humain.erase(pion_vector_grid_humain.begin() + i);

						
			};

		};

	};

};	// FIN: RetirePionCalcul(pion lePion)			





void CGrid::RetirePionJeu(pion pionID)			// Retire  définitivement le pion du jeu. Le jeu avance.  
												// Ici l'évaluation a été complétée et le choix du joueur (ordi ou humain) affecte le jeu.
												// Le vecteur des pions du joueur et les grilles de jeu sont modifiées.
{

	unsigned short int i;
	

													// Efface le pion de la liste des pions du jeu
		if (pionID.ID > 0)							// ID > 0 -> pion ordi  , ID < 0 -> pion_humain
		{
			for (i = 0; i < pion_vector_ordi.size(); i++)
			{
				if (pion_vector_ordi.at(i).ID == pionID.ID)
				{
					pion_vector_ordi.erase(pion_vector_ordi.begin() + i);

				};

			};

		}
		else									// ID < 0, donc pion humain.
		{
			for (i = 0; i < pion_vector_humain.size(); i++)
			{
				if (pion_vector_humain.at(i).ID == pionID.ID)
				{

					pion_vector_humain.erase(pion_vector_humain.begin() + i);

				};

			};

		};

		ResetPionVectorGrid();					// Efface les vecteurs de pions de la grille. Transfert les pions du jeu vers les vecteurs de pions de la grille de jeu
		TransferTousPionToMainGrid();				// Repeuple la grille de jeu main
		CloneGridMainToSub();					// Copie la grille de jeu grid_main vers grid_sub.

	}

	void CGrid::TransferTousPionToMainGrid()
	{
		int i,j;

																		//Réinitialisation de la grille

		for (i = 0; i < max_grid_size; i++ )
		{
			for (j = 0; j < max_grid_size; j++)
			{
				grid_main[i][j].ID = 0;
				
				grid_main[i][j].removed = FALSE;						// état du pion (removed = pion retiré)
				grid_main[i][j].new_x = 0;								// coordonnees X (destination lors d'un déplacement)
				grid_main[i][j].new_y = 0;								// coordonnees Y
				grid_main[i][j].old_x = 0;								// coordonnees X (origine lors d'un déplacement)
				grid_main[i][j].old_y = 0;								// coordonnees Y
				
				grid_main[i][j].dame = FALSE;								// si le pion devient une dame, alors dame = TRUE;
				grid_main[i][j].score = 0;								// score calculé pour ce pion (évaluation minimax)
				grid_main[i][j].move = 0;								// dernier move du pion
				grid_main[i][j].hasMoved = FALSE;

				grid_main[i][j].removed_x = 0;							// coordonnées du pion retiré 
				grid_main[i][j].removed_y = 0;							// coordonnées du pion retiré
					


			};

		};
		
		for (unsigned short int pionID = 0; pionID < (pion_vector_ordi.size()); pionID++)	// le vector pion contient les pions actifs…

		{
			int x = pion_vector_ordi.at(pionID).old_x;
			int y = pion_vector_ordi.at(pionID).old_y;

			grid_main[x][y].ID = pion_vector_ordi.at(pionID).ID;									// Pour chaque pion, marque la case où se trouve ce pion.  Equipe > 0 = ordi, Equipe < 0 = humain, 0= vide
			grid_main[x][y].removed = pion_vector_ordi.at(pionID).removed;							// état du pion (removed = pion retiré)
			grid_main[x][y].new_x = pion_vector_ordi.at(pionID).new_x;								// coordonnees X (destination lors d'un déplacement)
			grid_main[x][y].new_y = pion_vector_ordi.at(pionID).new_y;								// coordonnees Y
			grid_main[x][y].old_x = pion_vector_ordi.at(pionID).old_x;								// coordonnees X (origine lors d'un déplacement)
			grid_main[x][y].old_y = pion_vector_ordi.at(pionID).old_y;								// coordonnees Y
			grid_main[x][y].dame = pion_vector_ordi.at(pionID).dame;								// si le pion devient une dame, alors dame = TRUE;
			grid_main[x][y].score = pion_vector_ordi.at(pionID).score;								// score calculé pour ce pion (évaluation minimax)
			grid_main[x][y].move = pion_vector_ordi.at(pionID).move;								// dernier move du pion


		};

		for (unsigned short int pionID = 0; pionID < (pion_vector_humain.size()); pionID++)			// le vector pion contient les pions de l'opposant

		{
			int x = pion_vector_humain.at(pionID).old_x;
			int y = pion_vector_humain.at(pionID).old_y;

			grid_main[x][y].ID = pion_vector_humain.at(pionID).ID;									// Pour chaque pion, marque la case où se trouve ce pion.  Equipe > 0 = ordi, Equipe < 0 = humain, 0= vide
			grid_main[x][y].removed = pion_vector_humain.at(pionID).removed;						// état du pion (removed = pion retiré)
			grid_main[x][y].new_x = pion_vector_humain.at(pionID).new_x;							// coordonnees X (destination lors d'un déplacement)
			grid_main[x][y].new_y = pion_vector_humain.at(pionID).new_y;							// coordonnees Y
			grid_main[x][y].old_x = pion_vector_humain.at(pionID).old_x;							// coordonnees X (origine lors d'un déplacement)
			grid_main[x][y].old_y = pion_vector_humain.at(pionID).old_y;							// coordonnees Y
			grid_main[x][y].dame = pion_vector_humain.at(pionID).dame;								// si le pion devient une dame, alors dame = TRUE;
			grid_main[x][y].score = pion_vector_humain.at(pionID).score;							// score calculé pour ce pion (évaluation minimax)
			grid_main[x][y].move = pion_vector_humain.at(pionID).move;								// dernier move du pion
		};


	}

	void CGrid::CloneGridMainToSub()
	{
		// copie les données de grid_main vers grid_sub
		int i, j;
		for (i = 0; i < max_grid_size; i++)
		{
			for (j = 0; j < max_grid_size; j++)
			{
				grid_sub[i][j].ID = grid_main[i][j].ID; 							// Pour chaque pion, marque la case où se trouve ce pion.  Equipe > 0 = ordi, Equipe < 0 = humain, 0= vide
				grid_sub[i][j].removed = grid_main[i][j].removed;						// état du pion (removed = pion retiré)
				grid_sub[i][j].new_x = grid_main[i][j].new_x; 							// coordonnees X (destination lors d'un déplacement)
				grid_sub[i][j].new_y = grid_main[i][j].new_y;							// coordonnees Y
				grid_sub[i][j].old_x = grid_main[i][j].old_x;							// coordonnees X (origine lors d'un déplacement)
				grid_sub[i][j].old_y = grid_main[i][j].old_y;							// coordonnees Y
				grid_sub[i][j].dame = grid_main[i][j].dame;							// si le pion devient une dame, alors dame = TRUE;
				grid_sub[i][j].score = grid_main[i][j].score; 							// score calculé pour ce pion (évaluation minimax)
				grid_sub[i][j].move = grid_main[i][j].move; 							// dernier move du pion
				
				

			};
		};
	}

//std::vector <pion> pion_vector_grid_ordi;
//	std::vector <pion> pion_vector_grid_humain;

	CGrid::pion CGrid::TrouveBestPionOrdi()									//recherche le pion qui a le plus haut pointage pour le prochain mouvement (selon minimax)
	{
		int score;
		unsigned short int i;
		pion temp_pion;														// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
		score = -1000;
		// initialise à la valeur négative la plus élevée possible...

		pion bestPion;

		for (i = 0; i < pion_vector_ordi.size(); i++)
		{
			temp_pion = pion_vector_ordi.at(i);
			
			if (temp_pion.score >= score)
			{
				score = temp_pion.score;
				bestPion.ID = temp_pion.ID;
				bestPion.score = temp_pion.score;
				bestPion.move = temp_pion.move;
				bestPion.old_x = temp_pion.old_x;
				bestPion.old_y = temp_pion.old_y;
				bestPion.new_x = temp_pion.new_x;
				bestPion.new_y = temp_pion.new_y;

			};
		};

		return bestPion;
	}

	CGrid::pion CGrid::TrouveBestPionHumain()									//recherche le pion qui a le plus haut pointage pour le prochain mouvement (selon minimax)
	{
		unsigned int i;
		int score;
		pion temp_pion;														// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
		score = -1000;
		// initialise à la valeur négative la plus élevée possible...

		pion bestPion;

		for (i = 0; i < pion_vector_humain.size(); i++)
		{

			temp_pion = pion_vector_humain.at(i);

				if (temp_pion.score >= score)
				{
					score = temp_pion.score;
					bestPion.ID = temp_pion.ID;
					bestPion.score = temp_pion.score;
					bestPion.move = temp_pion.move;
					bestPion.old_x = temp_pion.old_x;
					bestPion.old_y = temp_pion.old_y;
					bestPion.new_x = temp_pion.new_x;
					bestPion.new_y = temp_pion.new_y;
					
				};
		};

		return bestPion;
	}

	void CGrid::CalculScoreInitial()												// le score d'un joueur est le nombre de pion qui reste en jeu;
	{

		score_ordi_initial = pion_vector_ordi.size();

		score_humain_initial = pion_vector_humain.size();

	}

	void CGrid::CalculScoreGrid()												// le score d'un joueur est le nombre de pion qui reste en jeu;
	{

		int i, j;
		score_ordi_grid = 0;
		score_humain_grid = 0;

		for (i = 0; i < max_grid_size; i++)
		{
			for (j = 0; j < max_grid_size; j++)
			{

				if (grid_sub[i][j].ID < 0) score_humain_grid++;

				else if (grid_sub[i][j].ID > 0) score_ordi_grid++;


			};
		};
	}



	void CGrid::ResetScorePions()
	{
		// remet à 0,  le score de tous les pions (requis au début de la recherche par minimax)
		unsigned int i;
		pion temp_pion;

		std::vector <pion> pion_temp_vector;

		pion_temp_vector.clear();

		for (i = 0; i < pion_vector_ordi.size(); i++)
		{

			temp_pion = pion_vector_ordi.at(i);
			temp_pion.score = -1000;
			temp_pion.move = -1;
			pion_temp_vector.push_back(temp_pion);						// sauvegarde dans vecteur temporaire
		};

		pion_vector_ordi.clear();


		for (i = 0; i < pion_temp_vector.size(); i++)
		{
			temp_pion = pion_temp_vector.at(i);
			pion_vector_ordi.push_back(temp_pion);

		};


		pion_temp_vector.clear();

		for (i = 0; i < pion_vector_humain.size(); i++)
		{

			temp_pion = pion_vector_humain.at(i);
			temp_pion.score = -1000;
			temp_pion.move = -1;
			pion_temp_vector.push_back(temp_pion);						// sauvegarde dans vecteur temporaire
		};

		pion_vector_humain.clear();


		for (i = 0; i < pion_temp_vector.size(); i++)
		{
			temp_pion = pion_temp_vector.at(i);
			pion_vector_humain.push_back(temp_pion);

		};

	}

	int CGrid::SetPionScore(pion pionID)								// si le score du pion est déjà plus élevé que le nouveau score, on ne change pas le score.
																		// retourne 1: score a changé, retourne 0: score inchangé.
	{
		unsigned int i;
		pion temp_pion;

		if (pionID.ID > 0)												// ID >0 -> pion ordi  , ID < 0 -> pion_humain
		{
			for (i = 0; i < pion_vector_ordi.size(); i++)
			{
				if (pion_vector_ordi.at(i).ID == pionID.ID)
				{
					temp_pion = pion_vector_ordi.at(i);

					if (temp_pion.score < pionID.score)
					{

						temp_pion.score = pionID.score;
						temp_pion.move = pionID.move;
						pion_vector_ordi.at(i) = temp_pion;

						//pion_vector_grid_ordi.erase(pion_vector_grid_ordi.begin() + i);
						//pion_vector_grid_ordi.push_back(temp_pion);
						return 1;
					};



					return 0;
				};

			};

		}
		else																// ID < 0, donc pion humain.
		{
			for (i = 0; i < pion_vector_humain.size(); i++)
			{
				if (pion_vector_humain.at(i).ID == pionID.ID)
				{

					temp_pion = pion_vector_humain.at(i);

					if (temp_pion.score < pionID.score)
					{

						temp_pion.score = pionID.score;
						temp_pion.move = pionID.move;
						pion_vector_humain.at(i)=temp_pion;
						//pion_vector_humain.push_back(temp_pion);
						return 1;
					};

					return 0;
				};

			};

		};

		
	};


	void CGrid::CreatePionsOrdi()
	{

		int i;
		pion pion_1;
		pion_vector_ordi.clear();

		for (i = 1; i < max_grid_size/2+1; i++)								// crée les pions de la rangée "0"
		{

			pion_1.ID = i;
			pion_1.old_x = (i-1) * 2;
			pion_1.old_y = 0;
			pion_1.new_x = pion_1.old_x;
			pion_1.new_y = pion_1.old_y;
			pion_1.hasMoved = FALSE;
			pion_1.niveau = 0;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;												// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
			pion_1.removed = false;
			pion_vector_ordi.push_back(pion_1);
		};

		for (i = max_grid_size / 2 + 1; i < max_grid_size + 1; i++)			// crée les pions de la rangée "1"
		{

			pion_1.ID = i;
			pion_1.old_x = (i - (max_grid_size / 2 + 1)) * 2 + 1;
			pion_1.old_y = 1;
			pion_1.new_x = pion_1.old_x;
			pion_1.new_y = pion_1.old_y;
			pion_1.hasMoved = FALSE;
			pion_1.niveau = 0;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;												// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
			pion_1.removed = false;	
			pion_vector_ordi.push_back(pion_1);
		};

		for (i = max_grid_size + 1; i < max_grid_size*1.5 + 1; i++)			// crée les pions de la rangée "2"
		{

			pion_1.ID = i;
			pion_1.old_x = (i - (max_grid_size + 1)) * 2;
			pion_1.old_y = 2;
			pion_1.new_x = pion_1.old_x;
			pion_1.new_y = pion_1.old_y;
			pion_1.hasMoved = FALSE;
			pion_1.niveau = 0;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;												// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
			pion_1.removed = false;
			pion_vector_ordi.push_back(pion_1);
		};

		for (i = max_grid_size * 1.5 + 1; i < max_grid_size*2+1; i++)		// crée les pions de la rangée "3"
		{

			pion_1.ID = i;
			pion_1.old_x = (i - (max_grid_size * 1.5 + 1)) * 2 + 1;
			pion_1.old_y = 3;
			pion_1.new_x = pion_1.old_x;
			pion_1.new_y = pion_1.old_y;
			pion_1.hasMoved = FALSE;
			pion_1.niveau = 0;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;												// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
			pion_1.removed = false;
			pion_vector_ordi.push_back(pion_1);
		};


	}


	void CGrid::CreatePionHumain()
	{
		int i;
		pion pion_1;
		pion_vector_humain.clear();

		
		for (i = 1; i < max_grid_size / 2 + 1; i++)							// crée les pions de la rangée "0"
		{

			pion_1.ID = -i;
			pion_1.old_x = (i-1) * 2 + 1;
			pion_1.old_y = 9;
			pion_1.new_x = pion_1.old_x;
			pion_1.new_y = pion_1.old_y;
			pion_1.hasMoved = FALSE;
			pion_1.niveau = 0;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;												// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.	
			pion_1.removed = false;						
			pion_vector_humain.push_back(pion_1);
		};

		for (i = max_grid_size / 2 + 1; i < max_grid_size + 1; i++)			// crée les pions de la rangée "1"
		{

			pion_1.ID = -i;
			pion_1.old_x = (i - (max_grid_size / 2 + 1)) * 2;
			pion_1.old_y = 8;
			pion_1.new_x = pion_1.old_x;
			pion_1.new_y = pion_1.old_y;
			pion_1.hasMoved = FALSE;
			pion_1.niveau = 0;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;												// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
			pion_1.removed = false;
			pion_vector_humain.push_back(pion_1);
		};

		for (i = max_grid_size + 1; i < max_grid_size*1.5 + 1; i++)			// crée les pions de la rangée "2"
		{

			pion_1.ID = -i;
			pion_1.old_x = (i - (max_grid_size + 1)) * 2 + 1;
			pion_1.old_y = 7;
			pion_1.new_x = pion_1.old_x;
			pion_1.new_y = pion_1.old_y;
			pion_1.hasMoved = FALSE;
			pion_1.niveau = 0;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;												// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
			pion_1.removed = false;
			pion_vector_humain.push_back(pion_1);
		};

		
		for (i = max_grid_size * 1.5 + 1; i < max_grid_size * 2 + 1; i++)	// crée les pions de la rangée "3"
		{

				pion_1.ID = -i;
				pion_1.old_x = (i - (max_grid_size * 1.5 + 1)) * 2;
				pion_1.old_y = 6;
				pion_1.new_x = pion_1.old_x;
				pion_1.new_y = pion_1.old_y;
				pion_1.hasMoved = FALSE;
				pion_1.niveau = 0;
				pion_1.dame = false;
				pion_1.score = -1000;
				pion_1.move = -1;																	// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
				pion_1.removed = false;
			
			pion_vector_humain.push_back(pion_1);
		};
 


	}


	int CGrid::GetScoreInitialOrdi()

	{
		
		return score_ordi_initial;
	}

	int CGrid::GetScoreInitialHum()

	{
		return score_humain_initial;
	}

	int CGrid::GetScoreGridOrdi()
	{
		return score_ordi_grid;
	};
	
	
	int CGrid::GetScoreGridHum()
	{
		return  score_humain_grid;
	
	};
	//******************************************************************************


	int CGrid::GetPionVectOrdiSize()
	{
		return pion_vector_ordi.size();
	};
	
	
	int CGrid::GetPionVectHumSize() 
	{
	
		return pion_vector_humain.size();
	};


	CGrid::pion CGrid::EvalueMove(pion & pion_1, int m_delta_X, int m_delta_y, int le_niveau, int move)
	{

		// Evalue si la nouvelle position est libre et qu'on reste dans les limites du jeu
		// Si on est dans les limites, on vérifie si on peut bouger (destination libre).  Si on peut bouger, on retourne un pion avec la nouvelle position et les coordonnées du pion sont mises à jour.		
		// Si on est hors limites, alors on retourne move = -1 
		// Si on reste dans les limites et que move>0, alors les coordonnées new_y, new_y contiennent la nouvelle position du pion.  old_x, old_y contiennent la position originale.
		// Si le move attérit sur un pion ennemi et que la case suivante est libre, alors on peut passer par dessus le pion ennemi (double delta_x, delta_y) et le retirer du jeu.  
		// Restera à retirer le pion ennemi.


		pion m_pion, pion_removed;;

		int dx, dy,a,b,c;
		
		m_pion.ID = pion_1.ID;
		m_pion.old_x = pion_1.old_x;
		m_pion.old_y = pion_1.old_y;
		m_pion.new_x = pion_1.new_x;
		m_pion.new_y = pion_1.new_y;
		m_pion.hasMoved = FALSE;
		m_pion.dame = pion_1.dame;									// copie l'info sur le pion (dame: true/false)
		m_pion.move = move;											// identifie le move à évaluer
		m_pion.removed = FALSE;
		m_pion.score = pion_1.score;
		m_pion.niveau = le_niveau;
		m_pion.removed_x = pion_1.removed_x;
		m_pion.removed_y = pion_1.removed_y;


		dx = m_delta_X;
		dy = m_delta_y;
		
		const long multiple = 1000;

		if (pion_1.ID < 0)											// inverse le déplacement vertical pour un pion humain.  Pion ordi dans le bas du jeu, pion humain dans le haut du jeu.
		{ 
			dy = -m_delta_y;
		}; 
		
		

		

		switch (move)  //Le pion : origine = old_x,y 
			{
			case 0:
				m_pion.new_x = pion_1.old_x + dx;
				m_pion.new_y = pion_1.old_y + dy;
				break;

			case 1:
				m_pion.new_x = pion_1.old_x - dx;
				m_pion.new_y = pion_1.old_y + dy;
				break;

			case 2:
				m_pion.new_x = pion_1.old_x + dx;
				m_pion.new_y = pion_1.old_y - dy;
				break;

			case 3:
				m_pion.new_x = pion_1.old_x - dx;
				m_pion.new_y = pion_1.old_y - dy;
				break;

			};

		
				
		if (m_pion.new_x > -1 && m_pion.new_x < max_grid_size && m_pion.new_y> -1 && m_pion.new_y < max_grid_size)		// Vérifie si le pion est dans les limites de la grille de jeu

		{
			
			a = m_pion.ID;
			b = grid_sub[m_pion.new_x][m_pion.new_y].ID;
			c = a * b;																// Test de polarité (+/-) pour identifier si la case contient un pion ami ou ennemi.  
																					// Si a*b < 0: les deux sont ennemis (polarité (+/-) des ID sont différents.
																					// Si a*b = 0, alors la case destination est vide (ID=0).
																					// Si a*b > 0 alors le pion et la case sont des joueurs de la même équipe (même polarité).


			if (c == 0)																
			{
				m_pion.hasMoved = TRUE;												// grid[m_pion.new_x][m_pion.new_y].ID = 0, alors case est vide.
				return m_pion;														//Retourne le pion et les nouvelles coordonnées (new_x, new_y) sont valides. On déplace ce pion.
			};

			
			
			if (c > 0)			
				// les ID sont de même signe, l'opération donne >0 alors la case est occupée par un pion de la même équipe.  Pion reste dans la position old_x, old_y.  
				
			{
				
				// Contient un pion de notre équipe, on ne peut bouger.

				m_pion.new_x = pion_1.new_x;
				m_pion.new_y = pion_1.new_y;
				m_pion.hasMoved = FALSE;
				return m_pion;
			};
			
			


				//Dernier cas possible:  "C < 0" ici
				// les 2 sont de signe différent. La case est occupée par un pion de l'autre équipe.
				

				//On peut vérifier si on peut retirer le pion en passant par dessus le pion ennemi: but: manger le pion ennemi.

				
				m_pion.removed_x = m_pion.new_x;									// sauvegarde les coordonnées du  pion ennemi qui pourrait être retiré, avant de faire l'analyse qui suit.
				m_pion.removed_y = m_pion.new_y;

				switch (move)														//Calcule la case destination suivante à évaluer.  
																					//Est-ce qu'on peut accéder à cette case? 
																					//Si oui, on saute par dessus pion ennemi et on le retire.
				{
				case 0:
					m_pion.new_x = m_pion.new_x + m_delta_X;
					m_pion.new_y = m_pion.new_y + m_delta_y;
					break;

				case 1:
					m_pion.new_x = m_pion.new_x - m_delta_X;
					m_pion.new_y = m_pion.new_y + m_delta_y;
					break;

				case 2:
					m_pion.new_x = m_pion.new_x + m_delta_X;
					m_pion.new_y = m_pion.new_y - m_delta_y;
					break;

				case 3:
					m_pion.new_x = m_pion.new_x - m_delta_X;
					m_pion.new_y = m_pion.new_y - m_delta_y;
					break;

				};  // fin : switch(move)
				
				if (m_pion.new_x > -1 && m_pion.new_x < max_grid_size && m_pion.new_y> -1 && m_pion.new_y < max_grid_size)		
																		// Vérifie si le pion est dans les limites de la grille de jeu
				{
					if (grid_sub[m_pion.new_x][m_pion.new_y].ID == 0)	// Évalue la case derrière le pion ennemi.  Est-elle libre? Si oui, on peut sauter par dessus le pion ennemi et le retirer.
					{
						m_pion.removed = true;							// Indique qu'on peut retirer un pion ennemi.  Les coordonnées new.x, new.y sont valides pour le pion qui attaque.  m_pion.removed_x,y contient les coordonnées du pion retiré.
						m_pion.hasMoved = TRUE;							// le pion s'est déplacé.  A conserver cette info pour l'évaluation au prochain niveau.  Nouveau point de départ de l'analyse = new_x, new_y.
						return m_pion;
					}
					else												// ici, la case derrière le pion ennemi n'est pas libre. On ne peut sauter et retirer le pion ennemi																
					{
						

						m_pion.new_x = pion_1.new_x;					// remet les coordonnées tel qu'avant l'évaluation du saut.
						m_pion.new_y = pion_1.new_y;
						m_pion.removed = FALSE;
						m_pion.hasMoved = FALSE;
						return m_pion;									
					}; 
				
				} 
				else
				{														// pion tombe hors limite du jeu.  On ne peut bouger le pion.

					m_pion.new_x = pion_1.new_x;
					m_pion.new_y = pion_1.new_y;
					m_pion.hasMoved = FALSE;
					return m_pion;

				};//fin: if (pion dans limites du jeu)

			//};  // fin: if c < 0)

			
		} // fin: si pion est dans les limites du jeu

		else															// ici le pion se retrouve hors de la grille de jeu.  On ne peut effectuer ce move.
		{
		m_pion.new_x = pion_1.new_x;
		m_pion.new_y = pion_1.new_y;
		//m_pion.move = -1;
		m_pion.removed = FALSE;
		m_pion.hasMoved = FALSE;
		return m_pion;												
		};
		
	};




	CGrid::pion CGrid::GetPionFromVectOrdi(int le_pion)
	{
		return pion_vector_ordi.at(le_pion);
	};

	CGrid::pion CGrid::GetPionFromVectHumain(int le_pion)
	{
		return pion_vector_humain.at(le_pion);
	};

	
	void CGrid::PushPionOnMoveVector(pion & lePion)
	{
	
		vector_move_pion.push_back(lePion);
	
	};


	CGrid::pion CGrid::PopPionFromMoveVector()
	{
	
		int sizeVector;
		pion lePion;
		sizeVector = vector_move_pion.size();
		lePion = vector_move_pion.at(sizeVector-1);
		vector_move_pion.pop_back();
		return lePion;
	};


	CGrid::pion CGrid::GetPionFromGridOrdi(int le_pion)
	{
		

		return pion_vector_grid_ordi.at(le_pion);

		
	};
	
	
	CGrid::pion CGrid::GetPionFromGridHumain(int le_pion)
	{
		return pion_vector_grid_humain.at(le_pion);
	};

	void CGrid::ResetPionVectorGrid()
	{	// lit tous les pions qui sont dans le jeu et peuple la grille de la liste des pions de la grille de jeu( vecteurs de pion).  Permet l'accès aux pions de la grille de jeu sans modifier les pions du jeu.
		// Utilisé lors de l'évaluation des move possibles.  Utilise la grille de jeu pour l'évaluaton.

		int i, vector_size;

		CGrid::pion le_pion;

		pion_vector_grid_ordi.clear();
		pion_vector_grid_humain.clear();

		 
		
	
		vector_size =pion_vector_ordi.size();
		

		for (i = 0; i < vector_size; i++)
		{
		
		le_pion = pion_vector_ordi.at(i);
					
		pion_vector_grid_ordi.push_back(le_pion);

		};

		vector_size = pion_vector_humain.size();

		for(i=0; i< vector_size; i++)
		{
				
			le_pion = pion_vector_humain.at(i);
				
			pion_vector_grid_humain.push_back(le_pion);
		};

		

	
	};

	bool CGrid::MovePion(pion &pion_1, int m_delta_X, int m_delta_y, int move)
	{
	
		CGrid::pion pion, retire_pion_opposant;
		int i, size, niveau;
		niveau = 0;

		pion = EvalueMove(pion_1, m_delta_X, m_delta_y, niveau,move);

		size = pion_vector_ordi.size();

		if (pion.hasMoved)
		{
			pion_1.old_x = pion.new_x;
			pion_1.old_y = pion.new_y;
			pion_1.new_x = pion.new_x;
			pion_1.new_y = pion.new_y;
			
			pion_1.hasMoved = FALSE;
			pion_1.niveau = 0;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;												// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
			pion_1.removed = false;
			
			
			if (pion_1.ID > 0)
			{
				for (i = 0; i < size; i++)
				{
					if (pion_vector_ordi.at(i).ID == pion.ID)
					{
						pion_vector_ordi.at(i) = pion_1;

					};

				};
			}
			else
			{
				for (i = 0; i < size; i++)
				{
					if (pion_vector_humain.at(i).ID == pion.ID)
					{
						pion_vector_humain.at(i) = pion_1;

					};

				};



			};





			if (pion.removed)
			{
				// Si ce pion a capturé un pion ennemi (temp_pion.removed = TRUE), alors retire le pion de la grille de jeu. 
				//Sauvegarde dans stack pour restauration future...



				retire_pion_opposant.ID = grid_sub[pion.removed_x][pion.removed_y].ID;
				retire_pion_opposant.removed = true;
				retire_pion_opposant.removed_x = pion.removed_x;
				retire_pion_opposant.removed_y = pion.removed_y;

				//PushPionOnMoveVector(retire_pion_opposant);			// push le pion dans le stack pour restauration future.

				RetirePionJeu(retire_pion_opposant);			// Retire pion du jeu.

				

			};  //Fin: if(temp_pion.removed)
			//pion_vector_ordi.push_back(pion_1);
			return TRUE;

		}
		else
		{
			return FALSE;

		};


	
	};

	
