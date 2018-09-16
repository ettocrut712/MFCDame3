#include "stdafx.h"
#include "CGrid.h"

#define DEBUG	// utilisé pour le debuggage du programme...

CGrid::CGrid()
{
}


CGrid::~CGrid()
{
}

	

void CGrid::RetirePionGrid(int pionID, int main_sub)		// main_sub: 0 -> retire du grid_main, 1-> retire du grid_sub
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
				if (main_sub == 0)
				{
					grid_main[i][j] = 0;
					return;
				}
				else
				{
					grid_sub[i][j] = 0;
					return;
				};
			};
			// grid_main[x][y] contient l'ID du pion qui est situé dans cette case.
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
			int x = pion_vector_ordi.at(pionID).x;
			int y = pion_vector_ordi.at(pionID).y;

			grid_main[x][y] = pion_vector_ordi.at(pionID).ID;										// Pour chaque pion, marque la case où se trouve ce pion.  Equipe > 0 = ordi, Equipe < 0 = humain, 0= vide

		};

		for (unsigned short int pionID = 0; pionID < (pion_vector_humain.size()); pionID++)	// le vector pion contient les pions restants…

		{
			int x = pion_vector_humain.at(pionID).x;
			int y = pion_vector_humain.at(pionID).y;

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
																			// retoure 1: score changé, retourne 0: score inchangé.
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
			pion_1.x = (i-1) * 2;
			pion_1.y = 0;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;																	// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
			pion_vector_ordi.push_back(pion_1);
		};

		for (i = 6; i < 11; i++)																// crée les pions de la rangée "1"
		{

			pion_1.ID = i;
			pion_1.x = (i - 6) * 2 + 1;
			pion_1.y = 1;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;																	// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
			pion_vector_ordi.push_back(pion_1);
		};

		for (i = 11; i < 16; i++)																	// crée les pions de la rangée "0"
		{

			pion_1.ID = i;
			pion_1.x = (i - 11) * 2;
			pion_1.y = 2;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;																	// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
			pion_vector_ordi.push_back(pion_1);
		};

		for (i = 16; i < 21; i++)																// crée les pions de la rangée "1"
		{

			pion_1.ID = i;
			pion_1.x = (i - 16) * 2 + 1;
			pion_1.y = 3;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;																	// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
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
			pion_1.x = (i-1) * 2 + 1;
			pion_1.y = 9;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;																	// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
			pion_vector_humain.push_back(pion_1);
		};

		for (i = 6; i < 11; i++)																// crée les pions de la rangée "1"
		{

			pion_1.ID = -i;
			pion_1.x = (i - 6) * 2;
			pion_1.y = 8;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;																	// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
			pion_vector_humain.push_back(pion_1);
		};

		for (i = 11; i < 16; i++)																	// crée les pions de la rangée "0"
		{

			pion_1.ID = -i;
			pion_1.x = (i - 11) * 2 + 1;
			pion_1.y = 7;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;																	// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
			pion_vector_humain.push_back(pion_1);
		};

		for (i = 16; i < 21; i++)																// crée les pions de la rangée "1"
		{

			pion_1.ID = -i;
			pion_1.x = (i - 16) * 2;
			pion_1.y = 6;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = -1;																	// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
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