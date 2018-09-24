#include "stdafx.h"
#include "CGrid.h"

#define DEBUG	// utilisé pour le debuggage du programme...

CGrid::CGrid()
{
}


CGrid::~CGrid()
{
}

/*struct gridJeu  copie pour référence...
{
	int ID;						// ID du pion qui est au point x,y
	int niveauGrid;				// niveau où on est rendu dans l'évaluation
	int grid[10][10];			// coordonnées de la casse


};*/

void CGrid::RetirePionGrid(int pionID, int main_sub)		// main_sub: 0 -> retire du grid_Main, 1-> retire du grid_Sub
{
	// Utilisé pour retirer un pion avec un ID spécifique du jeu.

	unsigned short int i, j;

	// Retire le pion du grillage de jeu en premier


	for (i = 0; i < max_grid_size; i++)
	{
		for (j = 0; j < max_grid_size; j++)
		{

			if (grid_main[i][j] == pionID)
			{
				if (main_sub == 0)			// ici main_sub =0, retire pion du grid_main
				{
					grid_main[i][j] = 0;
					return;
				}
				else
				{
											// ici main_sub =1, on retire le pion du grid_sub.
					grid_sub[i][j] = 0;
					return;
				};
			};
		};
	};

};

void CGrid::RetirePionJeu(int pionID)				// Retire le pion des vecteurs de pions actifs du jeu.
{

	unsigned short int i;
												// Retire le pion du vecteur des pions actifs.

		if (pionID > 0)							// ID >0 -> pion ordi  , ID < 0 -> pion_humain
		{
			for (i = 0; i < pion_vector_ordi.size(); i++)
			{
				if (pion_vector_ordi.at(i).ID == pionID)
				{
					pion_vector_ordi.erase(pion_vector_ordi.begin() + i);

					return;
				};

			};

		}
		else									// ID < 0, donc pion humain.
		{
			for (i = 0; i < pion_vector_humain.size(); i++)
			{
				if (pion_vector_humain.at(i).ID == pionID)
				{

					pion_vector_humain.erase(pion_vector_humain.begin() + i);

					return;
				};

			};

		};

	}

	void CGrid::TransferTousPionToGrid()
	{
		for (unsigned short int pionID = 0; pionID < (pion_vector_ordi.size()); pionID++)	// le vector pion contient les pions actifs…

		{
			int x = pion_vector_ordi.at(pionID).old_x;
			int y = pion_vector_ordi.at(pionID).old_y;

			grid_main[x][y] = pion_vector_ordi.at(pionID).ID;										// Pour chaque pion, marque la case où se trouve ce pion.  Equipe > 0 = ordi, Equipe < 0 = humain, 0= vide

		};

		for (unsigned short int pionID = 0; pionID < (pion_vector_humain.size()); pionID++)	// le vector pion contient les pions restants…

		{
			int x = pion_vector_humain.at(pionID).old_x;
			int y = pion_vector_humain.at(pionID).old_y;

			grid_main[x][y] = pion_vector_humain.at(pionID).ID;;										// Pour chaque pion, marque la case où se trouve ce pion.  Equipe > 0 = ordi, Equipe < 0 = humain, 0= vide

		};


	}

	void CGrid::CloneGrid()
	{
		// copie les données de grid_main vers grid_sub
		int i, j;
		for (i = 0; i < max_grid_size; i++)
		{
			for (j = 0; j < max_grid_size; j++)
			{
				grid_sub[i][j] = grid_main[i][j];

			};
		};
	}

	void CGrid::ResetMainGrid()
	{
		int i, j;

		for (i = 0; i < max_grid_size; i++)
		{
			for (j = 0; j < max_grid_size; j++)
			{
				grid_main[i][j] = 0;										// grid_main[x][y] contient l'ID du pion qui est situé dans cette case.
			};
		};
	}

	CGrid::pion_move CGrid::TrouveBestPionOrdi()									//recherche le pion qui a le plus haut pointage pour le prochain mouvement (selon minimax)
	{
		int score;
		unsigned short int i;
		pion temp_pion;														// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
		score = -1000;
		// initialise à la valeur négative la plus élevée possible...

		pion_move bestPion;

		for (i = 0; i < pion_vector_ordi.size(); i++)
		{

			temp_pion = pion_vector_ordi.at(i);
			if (temp_pion.move > -1)											// si move = -1, le pion n'a pas bougé.  Donc score n'a pas de valeur significative.
			{
				if (temp_pion.score > score)
				{
					bestPion.score = temp_pion.score;
					bestPion.ID = temp_pion.ID;
					bestPion.move = temp_pion.move;

				};
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

				if (grid_sub[i][j] < 0) score_humain_grid++;

				else if (grid_sub[i][j] > 0) score_ordi_grid++;


			};
		};
	}

	CGrid::pion_move CGrid::TrouveBestPionHumain()									//recherche le pion qui a le plus haut pointage pour le prochain mouvement (selon minimax)
	{
		unsigned int i;
		int score;
		pion temp_pion;														// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
		score = -1000;
		// initialise à la valeur négative la plus élevée possible...

		pion_move bestPion;

		for (i = 0; i < pion_vector_humain.size(); i++)
		{

			temp_pion = pion_vector_humain.at(i);
			if (temp_pion.move > -1)											// si move = -1, le pion n'a pas bougé.  Donc score n'a pas de valeur significative.
			{
				if (temp_pion.score > score)
				{
					bestPion.score = temp_pion.score;
					bestPion.ID = temp_pion.ID;
					bestPion.move = temp_pion.move;

				};
			};

		};

		return bestPion;
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

	int CGrid::SetPionScore(int pionID, int score, int move)				// si le score du pion est déjà plus élevé que le nouveau score, on ne change pas le score.
																			// retourne 1: score changé, retourne 0: score inchangé.
	{
		unsigned int i;
		pion temp_pion;

		if (pionID > 0)														// ID >0 -> pion ordi  , ID < 0 -> pion_humain
		{
			for (i = 0; i < pion_vector_ordi.size(); i++)
			{
				if (pion_vector_ordi.at(i).ID == pionID)
				{
					temp_pion = pion_vector_ordi.at(i);

					if (temp_pion.score < score)
					{

						temp_pion.score = score;
						temp_pion.move = move;
						pion_vector_ordi.erase(pion_vector_ordi.begin() + i);
						pion_vector_ordi.push_back(temp_pion);
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
				if (pion_vector_humain.at(i).ID == pionID)
				{

					temp_pion = pion_vector_humain.at(i);

					if (temp_pion.score < score)
					{

						temp_pion.score = score;
						temp_pion.move = move;
						pion_vector_humain.erase(pion_vector_humain.begin() + i);
						pion_vector_humain.push_back(temp_pion);
						return 1;
					};

					return 0;
				};

			};

		};

		return 0;
	}

	void CGrid::ResetSubGrid()
	{

		int i, j;

		for (i = 0; i < max_grid_size; i++)
		{
			for (j = 0; j < max_grid_size; j++)
			{
				grid_sub[i][j] = 0;			// grid_main[x][y] contient l'ID du pion qui est situé dans cette case.
			};
		};

	}

	void CGrid::CreatePionsOrdi()
	{

		int i;
		pion pion_1;
		pion_vector_ordi.clear();

		for (i = 1; i < 6; i++)																	// crée les pions de la rangée "0"
		{

			pion_1.ID = i;
			pion_1.old_x = (i-1) * 2;
			pion_1.old_y = 0;
			pion_1.new_x = pion_1.old_x;
			pion_1.new_y = pion_1.old_y;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;																	// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
			pion_1.attaque = false;
			pion_vector_ordi.push_back(pion_1);
		};

		for (i = 6; i < 11; i++)																// crée les pions de la rangée "1"
		{

			pion_1.ID = i;
			pion_1.old_x = (i - 6) * 2 + 1;
			pion_1.old_y = 1;
			pion_1.new_x = pion_1.old_x;
			pion_1.new_y = pion_1.old_y;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;																	// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
			pion_1.attaque = false;	
			pion_vector_ordi.push_back(pion_1);
		};

		for (i = 11; i < 16; i++)																	// crée les pions de la rangée "0"
		{

			pion_1.ID = i;
			pion_1.old_x = (i - 11) * 2;
			pion_1.old_y = 2;
			pion_1.new_x = pion_1.old_x;
			pion_1.new_y = pion_1.old_y;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;																	// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
			pion_1.attaque = false;
			pion_vector_ordi.push_back(pion_1);
		};

		for (i = 16; i < 21; i++)																// crée les pions de la rangée "1"
		{

			pion_1.ID = i;
			pion_1.old_x = (i - 16) * 2 + 1;
			pion_1.old_y = 3;
			pion_1.new_x = pion_1.old_x;
			pion_1.new_y = pion_1.old_y;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;																	// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
			pion_1.attaque = false;
			pion_vector_ordi.push_back(pion_1);
		};


	}


	void CGrid::CreatePionHumain()
	{
		int i;
		pion pion_1;
		pion_vector_humain.clear();

		for (i = 1; i < 6; i++)																	// crée les pions de la rangée "0"
		{

			pion_1.ID = -i;
			pion_1.old_x = (i-1) * 2 + 1;
			pion_1.old_y = 9;
			pion_1.new_x = pion_1.old_x;
			pion_1.new_y = pion_1.old_y;


			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;					// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.	
			pion_1.attaque = false;						
			pion_vector_humain.push_back(pion_1);
		};

		for (i = 6; i < 11; i++)																// crée les pions de la rangée "1"
		{

			pion_1.ID = -i;
			pion_1.old_x = (i - 6) * 2;
			pion_1.old_y = 8;
			pion_1.new_x = pion_1.old_x;
			pion_1.new_y = pion_1.old_y;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;																	// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
			pion_1.attaque = false;
			pion_vector_humain.push_back(pion_1);
		};

		for (i = 11; i < 16; i++)																	// crée les pions de la rangée "0"
		{

			pion_1.ID = -i;
			pion_1.old_x = (i - 11) * 2 + 1;
			pion_1.old_y = 7;
			pion_1.new_x = pion_1.old_x;
			pion_1.new_y = pion_1.old_y;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;																	// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
			pion_1.attaque = false;
			pion_vector_humain.push_back(pion_1);
		};

		for (i = 16; i < 21; i++)																// crée les pions de la rangée "1"
		{

			pion_1.ID = -i;
			pion_1.old_x = (i - 16) * 2;
			pion_1.old_y = 6;
			pion_1.new_x = pion_1.old_x;
			pion_1.new_y = pion_1.old_y;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;																	// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
			pion_1.attaque = false;
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

		// Evalue si la nouvelle position est libre et qu'on est toujours dans les limites du jeu lorsqu'on calcule la destination
		// Si on est dans les limites, on vérifie si on peut bouger (destination libre) et on retourne un pion avec la nouvelle position et le move qui est effectué.
		// Si on est hors limites, alors on retourne move = -1 

		pion m_pion;
		


		const long multiple = 1000;

		if (pion_1.ID < 0) m_delta_y = -m_delta_y; // inverse le déplacement vertical pour un pion adversaire.

		switch (move)  // calcule la case destination à évaluer.  Est-ce qu'on peut accéder à cette case?
		{
		case 0:
			m_pion.new_x = pion_1.old_x + m_delta_X;
			m_pion.new_y = pion_1.old_y + m_delta_y;
			break;

		case 1:
			m_pion.new_x = pion_1.old_x - m_delta_X;
			m_pion.new_y = pion_1.old_y + m_delta_y;
			break;

		case 2:
			m_pion.new_x = pion_1.old_x + m_delta_X;
			m_pion.new_y = pion_1.old_y- m_delta_y;
			break;

		case 3:
			m_pion.new_x = pion_1.old_x - m_delta_X;
			m_pion.new_y = pion_1.old_y - m_delta_y;
			break;

		};
			
		m_pion.ID = pion_1.ID;
		m_pion.old_x = pion_1.old_x;
		m_pion.old_y = pion_1.old_y;
		
		m_pion.dame = pion_1.dame;	// copie l'info sur le pion (dame: true/false)
		m_pion.move = move;			// identifie le move à évaluer
		m_pion.attaque = false;

		// génère un nouveau ID pour le pion en fonction du niveau.
/*
		if (pion_1.ID > 0)  // si c'est un pion  de l'ordi... pion.ID va de -20 à -1, de +1 à +20.  ID ne peut être "0".
		{

			// pion temporaire: ID: niveau 0 pion 0 devient pion 100000 au niveau 1, pion 200000 au niveau 2, etc. 
			// Structure ID pion temporaire: N (ID) 0 x y: pion 1, niveau 1, x=5, y = 6: 101056.  X: 0..9, y: 0..9, ID: -20..20,  

			if (pion_1.ID > 100000)
			{
				m_pion.ID = 100000 * le_niveau + multiple * ((pion_1.ID - 100000 * (le_niveau - 1)) / multiple) + m_pion.old_x * 10 + m_pion.old_y;
			}
			else
			{
				m_pion.ID = 100000 * le_niveau + multiple * pion_1.ID + m_pion.old_x * 10 + m_pion.old_y;
			};
		};

		if (pion_1.ID < 0) 
		{
			// pion temporaire: ID: niveau 0 pion 0 devient pion 100000 au niveau 1, pion 200000 au niveau 2, etc. 
			// Structure ID pion temporaire: N (ID) 0 x y: pion 1, niveau 1, x=5, y = 6: 101056.  X: 0..9, y: 0..9, ID: -20..20,  

			pion_1.ID = pion_1.ID*-1;		// inverse le signe. Utilise la même formule que pour un ID positif. Inverse le signe à la fin...

			if (pion_1.ID > 100000) m_pion.ID = 100000 * le_niveau + multiple * ((pion_1.ID - 100000 * (le_niveau - 1)) / multiple) + m_pion.old_x * 10 + m_pion.old_y;
			else m_pion.ID = 100000 * le_niveau + multiple * pion_1.ID + m_pion.old_x * 10 + m_pion.old_y;
			pion_1.ID = pion_1.ID*-1;

		};
	
	*/
		if (m_pion.new_x > -1 && m_pion.new_x < max_grid_size && m_pion.new_y> -1 && m_pion.new_y < max_grid_size)		// Vérifie si le pion est dans les limites de la grille de jeu

		{
			if (grid_sub[m_pion.new_x][m_pion.new_y] == 0 )										// si grid[x][y] = 0, alors case est vide.
			{
				return m_pion;															// retourne le pion et les nouvelles coordonnées.
			}
			else if (grid_sub[m_pion.new_x][m_pion.new_y] < 0)							// si grid_Jeu[x][y] <0 , alors case contient un pion de l'adversaire.
			{
				if (grid_sub[m_pion.new_x + delta_x][m_pion.new_y + delta_y] == 0)		// Évalue la case derrière le pion ennemi.  Est-elle libre? Si oui, on peut sauter et manger ce pion.
				{
					m_pion.new_x = m_pion.new_x + delta_x;								// Met le pion dans la case vide après le pion ennemi.
					m_pion.new_y = m_pion.new_y + delta_y;
					m_pion.attaque = true;
					return m_pion;
				}
				else																	// ici, la case derrière le pion ennemi n'est pas libre. On ne peut bouger (ne peut attaquer)																	
				{
					m_pion.move = -1;
				}
			}

			else if ((grid_sub[m_pion.new_x][m_pion.new_y] > 0))						// si grid_Jeu[x][y] > 0 , contient un pion de l'équipe. On ne peut bouger: ID pion = -10000;
			{
				
				m_pion.move = -1;
				return m_pion;
			};
		}

		else																			// ici le pion se retrouve hors de la grille de jeu.  On ne peut effectuer ce move.
		{
			
			m_pion.move = -1;
			return m_pion;																// case hors de la grille de jeu. On ne peut bouger: ID pion = -10000;
		};
		

		return m_pion;																	// MOD TEMP: COMPILATEUR SE PLAINT SI CE N<EST PAS LÀ.
	};




	CGrid::pion CGrid::GetPionFromVectOrdi(int le_pion)
	{
		return pion_vector_ordi.at(le_pion);
	};

	CGrid::pion CGrid::GetPionFromVectHumain(int le_pion)
	{
		return pion_vector_humain.at(le_pion);
	};

	CGrid::pion  CGrid::CalculeMovePionOrdi_max(pion &pion,  int niveau, int alpha, int beta)		 // max
	{
		int v = -1000;
		CGrid::pion v1;


		v1.score = -1000;
		v1.ID = pion.ID;

		int le_niveau = niveau;
		le_niveau = le_niveau + 1;
		
		int move;
		
		CGrid::pion temp_pion;
				
		if (niveau > max_niveau)
		{
			
			CalculScoreGrid();			// compte le nombre de pion de chaque joueur.
										// calcule le score pour ce pion.
			v1.score = (GetScoreInitialHum() - GetScoreGridHum()) - (GetScoreGridOrdi() - GetScoreInitialOrdi());
			 
			return v1;
		}
		else
		{
			for (move = 0; move < 2; move++)
			{
				v1.move = move;
				temp_pion = EvalueMove(pion, CGrid::delta_x, CGrid::delta_y, le_niveau, move);
				
				if (temp_pion.move > -1)			//  >0 veut dire que le pion peut bouger.  <0 , le pion ne peut faire le move.  Donc on passe au move suivant.
				{
					//	move pion - moveStack push;

					v1 = CalculeMovePionHumain_min(v1, le_niveau, alpha, beta);
					
					// move pion - moveStack pop;

 					if (v1.score > v) v = v1.score;
					if (v1.score >= beta)
					{
						v1.score = v;
						return v1;

					};
					if (v1.score > alpha)
					{
						alpha = v1.score;
					}
				}
				else
				{
					v1.move = -1;					// ici le pion ne peut bouger.
					return v1;
				};

			
			};

			return v1;

		}
	};

	CGrid::pion CGrid::CalculeMovePionHumain_min(pion &pion, int niveau, int alpha, int beta)
		{
			
			CGrid::pion v1,my_pion, temp_pion;
			int le_niveau, v;
			le_niveau = niveau;
			int score, move;
			int sizeVect;
			int pionID;
			
			v = 1000;
			v1.ID = pion.ID;
			v1.move = pion.move;
			v1.score = pion.score;

			sizeVect = GetPionVectHumSize();
			le_niveau = le_niveau + 1;
			
			if (le_niveau > CGrid::max_niveau)
			{
				CalculScoreGrid();			// compte le nombre de pion de chaque joueur.
				score = (GetScoreInitialHum() - GetScoreGridHum()) - (GetScoreGridOrdi() - GetScoreInitialOrdi());
				v1.score = score;
				
				return v1;
			}
			else
			{
				for (pionID = 0; pionID < sizeVect; pionID++)
				{
					my_pion = GetPionFromVectHumain(pionID);

					for (move = 0; move < 2; move++)
					{
						temp_pion = EvalueMove(pion, CGrid::delta_x, CGrid::delta_y, le_niveau, move);
						if (temp_pion.move > 0)			//  >0 veut dire que le pion peut bouger.  <0 , le pion ne peut faire le move.  Donc on passe au move suivant.
						{
							//	move pion - ordi dans moveStack;
							v1 = CalculeMovePionOrdi_max(my_pion, le_niveau, alpha, beta);
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
							v1.move = -1;
							return v1;


						}
					}
				}
				return v1;
			}
		};

		