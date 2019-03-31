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

void CGrid::AjoutPionGrid_removed(pion lePion)
{							// Utilisé pour remettre un pion en jeu après que le calcul (MINIMAX) l'impliquant soit terminé.
							// Ajoute le pion sur la grille de jeu et restaure la situation tel qu'avant le retrait pour évaluation.
							// Ajoute le pion sur le vecteur des pions du grid.

	//grid_sub[lePion.removed_x][lePion.removed_y].ID = lePion.ID;							// ID du pion.
	grid_sub[lePion.removed_x][lePion.removed_y].removed = FALSE;									// état du pion (removed = pion retiré)
	grid_sub[lePion.removed_x][lePion.removed_y].ID = lePion.removed_ID;
	grid_sub[lePion.removed_x][lePion.removed_y].removed_x = 0;
	grid_sub[lePion.removed_x][lePion.removed_y].removed_y = 0;
	grid_sub[lePion.removed_x][lePion.removed_y].removed_ID = 0;
	grid_sub[lePion.removed_x][lePion.removed_y].new_x = 0;								// coordonnees X (destination lors d'un déplacement)
	grid_sub[lePion.removed_x][lePion.removed_y].new_y = 0;								// coordonnees Y
	grid_sub[lePion.removed_x][lePion.removed_y].actual_x = lePion.removed_x;								// coordonnees X (destination lors d'un déplacement)
	grid_sub[lePion.removed_x][lePion.removed_y].actual_y = lePion.removed_y;								// coordonnees Y
	grid_sub[lePion.removed_x][lePion.removed_y].dame = lePion.dame;								// si le pion devient une dame, alors dame = TRUE;
	grid_sub[lePion.removed_x][lePion.removed_y].score = lePion.score;								// score calculé pour ce pion (évaluation minimax)
	grid_sub[lePion.removed_x][lePion.removed_y].move = lePion.move;								// dernier move du pion
	grid_sub[lePion.removed_x][lePion.removed_y].hasMoved = lePion.hasMoved;
};

void CGrid::AjoutPion_to_Grid__at_actual_xy(pion lePion)
{							// 
							// Ajoute un  pion à la position lePion old x,y
							// 

																							// ID du pion.
	grid_sub[lePion.actual_x][lePion.actual_y].removed = FALSE;									// état du pion (removed = pion retiré)
	grid_sub[lePion.actual_x][lePion.actual_y].ID = lePion.ID;
	grid_sub[lePion.actual_x][lePion.actual_y].removed_x = 0;
	grid_sub[lePion.actual_x][lePion.actual_y].removed_y = 0;
	grid_sub[lePion.actual_x][lePion.actual_y].removed_ID= 0;
	grid_sub[lePion.actual_x][lePion.actual_y].new_x = lePion.new_x;								// coordonnees X (destination lors d'un déplacement)
	grid_sub[lePion.actual_x][lePion.actual_y].new_y = lePion.new_y;								// coordonnees Y
	grid_sub[lePion.actual_x][lePion.actual_y].actual_x = lePion.actual_x;								// coordonnees X (destination lors d'un déplacement)
	grid_sub[lePion.actual_x][lePion.actual_y].actual_y = lePion.actual_y;								// coordonnees Y
	grid_sub[lePion.actual_x][lePion.actual_y].dame = lePion.dame;								// si le pion devient une dame, alors dame = TRUE;
	grid_sub[lePion.actual_x][lePion.actual_y].score = lePion.score;								// score calculé pour ce pion (évaluation minimax)
	grid_sub[lePion.actual_x][lePion.actual_y].move = lePion.move;								// dernier move du pion
	grid_sub[lePion.actual_x][lePion.actual_y].hasMoved = lePion.hasMoved;
};				

void CGrid::AjoutPion_to_Grid__at_new_xy(pion lePion)
{							// 
							// Ajoute un  pion à la position lePion new x,y
							// 

																							// ID du pion.
	grid_sub[lePion.new_x][lePion.new_y].removed = FALSE;									// état du pion (removed = pion retiré)
	grid_sub[lePion.new_x][lePion.new_y].removed_x = 0;
	grid_sub[lePion.new_x][lePion.new_y].ID = lePion.ID;
	grid_sub[lePion.new_x][lePion.new_y].removed_y = 0;
	grid_sub[lePion.new_x][lePion.new_y].removed_ID = 0;
	grid_sub[lePion.new_x][lePion.new_y].new_x = lePion.new_x;								// coordonnees X (destination lors d'un déplacement)
	grid_sub[lePion.new_x][lePion.new_y].new_y = lePion.new_y;								// coordonnees Y
	grid_sub[lePion.new_x][lePion.new_y].actual_x = lePion.new_x;								// coordonnees X (destination lors d'un déplacement)
	grid_sub[lePion.new_x][lePion.new_y].actual_y = lePion.new_y;								// coordonnees Y
	grid_sub[lePion.new_x][lePion.new_y].dame = lePion.dame;								// si le pion devient une dame, alors dame = TRUE;
	grid_sub[lePion.new_x][lePion.new_y].score = lePion.score;								// score calculé pour ce pion (évaluation minimax)
	grid_sub[lePion.new_x][lePion.new_y].move = lePion.move;								// dernier move du pion
	grid_sub[lePion.new_x][lePion.new_y].hasMoved = lePion.hasMoved;


};

void CGrid::AjustePion_in_VectorGrid_to_new_xy(pion lePion)
{
																			// met à jour le vecteur pion apres avoir déplacé un pion.   new x,y -> old x,y
	
	int unsigned i;

	if (lePion.ID > 0)														// ID >0 -> pion ordi  , ID < 0 -> pion_humain
	{
		for (i = 0; i < pion_vector_grid_ordi.size(); i++)					// remettre en jeu le pion qui avait été retiré.
		{
			if (pion_vector_grid_ordi.at(i).ID == lePion.ID)
			{
				//pion_vector_grid_ordi.erase(pion_vector_grid_ordi.begin() + i);

				pion_vector_grid_ordi.at(i).removed = false;
				pion_vector_grid_ordi.at(i).new_x = lePion.new_x;
				pion_vector_grid_ordi.at(i).new_y = lePion.new_y;
				pion_vector_grid_ordi.at(i).actual_x = lePion.new_x;				//info modifiée ici. Le reste est inchangé.
				pion_vector_grid_ordi.at(i).actual_y = lePion.new_y;				//info modifiée ici. Le reste est inchangé.
				pion_vector_grid_ordi.at(i).dame = lePion.dame;
				pion_vector_grid_ordi.at(i).score = lePion.score;
				pion_vector_grid_ordi.at(i).move = lePion.move;
				pion_vector_grid_ordi.at(i).hasMoved = lePion.hasMoved;
				pion_vector_grid_ordi.at(i).removed_ID = lePion.removed_ID;
				pion_vector_grid_ordi.at(i).removed_x = lePion.removed_x;
				pion_vector_grid_ordi.at(i).removed_y = lePion.removed_y;

			};

		};

	}
	else																	// ID < 0, donc pion humain joue.
	{
		for (i = 0; i < pion_vector_grid_humain.size(); i++)				// recherche le pion qui est retiré.  Le pion retiré est toujours un opposant.  Si joueur = humain, opposant = humain.
		{
			if (pion_vector_grid_humain.at(i).ID == lePion.ID)
			{
				//pion_vector_grid_humain.erase(pion_vector_grid_humain.begin() + i);

				pion_vector_grid_humain.at(i).removed = false;
				pion_vector_grid_humain.at(i).new_x = lePion.new_x;
				pion_vector_grid_humain.at(i).new_y = lePion.new_y;
				pion_vector_grid_humain.at(i).actual_x = lePion.new_x;				//info modifiée ici. Le reste est inchangé.
				pion_vector_grid_humain.at(i).actual_y = lePion.new_y;				//info modifiée ici. Le reste est inchangé.
				pion_vector_grid_humain.at(i).dame = lePion.dame;
				pion_vector_grid_humain.at(i).score = lePion.score;
				pion_vector_grid_humain.at(i).move = lePion.move;
				pion_vector_grid_humain.at(i).hasMoved = lePion.hasMoved;
				pion_vector_grid_humain.at(i).removed_ID = lePion.removed_ID;
				pion_vector_grid_humain.at(i).removed_x = lePion.removed_x;
				pion_vector_grid_humain.at(i).removed_y = lePion.removed_y;
			};

		};

	};

};


void CGrid::AjustePion_in_VectorGrid_to_actual_xy(pion lePion)
{
	// met à jour le vecteur pion apres avoir déplacé un pion.   new x,y -> old x,y

	int unsigned i;

	if (lePion.ID > 0)														// ID >0 -> pion ordi  , ID < 0 -> pion_humain
	{
		for (i = 0; i < pion_vector_grid_ordi.size(); i++)					// remettre en jeu le pion qui avait été retiré.
		{
			if (pion_vector_grid_ordi.at(i).ID == lePion.ID)
			{
				//pion_vector_grid_ordi.erase(pion_vector_grid_ordi.begin() + i);

				pion_vector_grid_ordi.at(i).removed = false;
				pion_vector_grid_ordi.at(i).new_x = lePion.new_x;
				pion_vector_grid_ordi.at(i).new_y = lePion.new_y;
				pion_vector_grid_ordi.at(i).actual_x = lePion.actual_x;				//info modifiée ici. Le reste est inchangé.
				pion_vector_grid_ordi.at(i).actual_y = lePion.actual_y;				//info modifiée ici. Le reste est inchangé.
				pion_vector_grid_ordi.at(i).dame = lePion.dame;
				pion_vector_grid_ordi.at(i).score = lePion.score;
				pion_vector_grid_ordi.at(i).move = lePion.move;
				pion_vector_grid_ordi.at(i).hasMoved = lePion.hasMoved;
				pion_vector_grid_ordi.at(i).removed_ID = lePion.removed_ID;
				pion_vector_grid_ordi.at(i).removed_x = lePion.removed_x;
				pion_vector_grid_ordi.at(i).removed_y = lePion.removed_y;

			};

		};

	}
	else																	// ID < 0, donc pion humain joue.
	{
		for (i = 0; i < pion_vector_grid_humain.size(); i++)				// recherche le pion qui est retiré.  Le pion retiré est toujours un opposant.  Si joueur = humain, opposant = humain.
		{
			if (pion_vector_grid_humain.at(i).ID == lePion.ID)
			{
				//pion_vector_grid_humain.erase(pion_vector_grid_humain.begin() + i);

				pion_vector_grid_humain.at(i).removed = false;
				pion_vector_grid_humain.at(i).new_x = lePion.new_x;
				pion_vector_grid_humain.at(i).new_y = lePion.new_y;
				pion_vector_grid_humain.at(i).actual_x = lePion.actual_x;				//info modifiée ici. Le reste est inchangé.
				pion_vector_grid_humain.at(i).actual_y = lePion.actual_y;				//info modifiée ici. Le reste est inchangé.
				pion_vector_grid_humain.at(i).dame = lePion.dame;
				pion_vector_grid_humain.at(i).score = lePion.score;
				pion_vector_grid_humain.at(i).move = lePion.move;
				pion_vector_grid_humain.at(i).hasMoved = lePion.hasMoved;
				pion_vector_grid_humain.at(i).removed_ID = lePion.removed_ID;
				pion_vector_grid_humain.at(i).removed_x = lePion.removed_x;
				pion_vector_grid_humain.at(i).removed_y = lePion.removed_y;
			};

		};

	};

};

void CGrid::AjustePion_in_VectorGrid_to_removed_xy(pion lePion)
{
	// met à jour le vecteur pion apres avoir déplacé un pion

	int unsigned i;

	if (lePion.ID > 0)														// ID >0 -> pion ordi  , ID < 0 -> pion_humain
	{
		for (i = 0; i < pion_vector_grid_ordi.size(); i++)					// remettre en jeu le pion qui avait été retiré.
		{
			if (pion_vector_grid_ordi.at(i).ID == lePion.ID)
			{
				//pion_vector_grid_ordi.erase(pion_vector_grid_ordi.begin() + i);

				pion_vector_grid_ordi.at(i).removed = false;
				pion_vector_grid_ordi.at(i).new_x = lePion.new_x;
				pion_vector_grid_ordi.at(i).new_y = lePion.new_y;
				pion_vector_grid_ordi.at(i).actual_x = lePion.removed_x;				//info modifiée ici. Le reste est inchangé.
				pion_vector_grid_ordi.at(i).actual_y = lePion.removed_y;				//info modifiée ici. Le reste est inchangé.
				pion_vector_grid_ordi.at(i).dame = lePion.dame;
				pion_vector_grid_ordi.at(i).score = lePion.score;
				pion_vector_grid_ordi.at(i).move = lePion.move;
				pion_vector_grid_ordi.at(i).hasMoved = lePion.hasMoved;
				pion_vector_grid_ordi.at(i).removed_ID = lePion.removed_ID;
				pion_vector_grid_ordi.at(i).removed_x = lePion.removed_x;
				pion_vector_grid_ordi.at(i).removed_y = lePion.removed_y;

			};

		};

	}
	else																	// ID < 0, donc pion humain joue.
	{
		for (i = 0; i < pion_vector_grid_humain.size(); i++)				// recherche le pion qui est retiré.  Le pion retiré est toujours un opposant.  Si joueur = humain, opposant = humain.
		{
			if (pion_vector_grid_humain.at(i).ID == lePion.ID)
			{
				//pion_vector_grid_humain.erase(pion_vector_grid_humain.begin() + i);

				pion_vector_grid_humain.at(i).removed = false;
				pion_vector_grid_humain.at(i).new_x = lePion.new_x;
				pion_vector_grid_humain.at(i).new_y = lePion.new_y;
				pion_vector_grid_humain.at(i).actual_x = lePion.removed_x;				//info modifiée ici. Le reste est inchangé.
				pion_vector_grid_humain.at(i).actual_y = lePion.removed_y;				//info modifiée ici. Le reste est inchangé.
				pion_vector_grid_humain.at(i).dame = lePion.dame;
				pion_vector_grid_humain.at(i).score = lePion.score;
				pion_vector_grid_humain.at(i).move = lePion.move;
				pion_vector_grid_humain.at(i).hasMoved = lePion.hasMoved;
				pion_vector_grid_humain.at(i).removed_ID = lePion.removed_ID;
				pion_vector_grid_humain.at(i).removed_x = lePion.removed_x;
				pion_vector_grid_humain.at(i).removed_y = lePion.removed_y;
			};

		};

	};

};


CGrid::pion CGrid::RetirePionCalcul(pion lePion)

{							// Utilisé pour retirer un pion du jeu lors du calcul (pion retiré lors du calcul, pour évaluation par MINIMAX)
							// Retire le pion sur la grille de jeu.
							// Retire le pion sur le vecteur des pions du grid.  Marque: removed = true
							// Le pion reste parmi les pions du joueurs jusqu'après l'évaluation des mouvements.  Le retrait se fait seulement quand le mouvement devient officiel.

	int unsigned i;
	pion pion_retire;
							// Retire le pion du vecteur des pions actifs.  Et retire pion de la grille de jeu sub_main (pour évaluation MINIMAX)


	grid_sub[lePion.removed_x][lePion.removed_y].ID = 0;

	



	// Met à jour le vecteur qui contient la grille de jeu.  Requis afin d'effectuer un scan de tous les pions actifs seulement.

	if (lePion.ID > 0)														// ID >0 -> pion ordi  , ID < 0 -> pion_humain
	{
		for (i = 0; i < pion_vector_grid_humain.size(); i++)				// recherche le pion qui est retiré.  Le pion retiré est toujours un opposant.  Si joueur = ordi, opposant = humain.
		{
			if (pion_vector_grid_humain.at(i).ID == lePion.removed_ID)
			{
				

				pion_vector_grid_humain.at(i).removed = true;
				pion_vector_grid_humain.at(i).removed_x = lePion.removed_x;
				pion_vector_grid_humain.at(i).removed_y = lePion.removed_y;

				pion_retire.ID = lePion.removed_ID;
				pion_retire.removed = true;
				pion_retire.removed_ID = lePion.removed_ID;
				pion_retire.removed_x = lePion.removed_x;
				pion_retire.removed_y = lePion.removed_y;
				pion_retire.new_x = 0;		// coordonnees X (destination lors d'un déplacement)
				pion_retire.new_y = 0;		// coordonnees Y
				pion_retire.actual_x = pion_vector_grid_humain.at(i).actual_x;		// coordonnees X (destination lors d'un déplacement)
				pion_retire.actual_y = pion_vector_grid_humain.at(i).actual_y;		// coordonnees Y
				pion_retire.dame = pion_vector_grid_humain.at(i).dame;			// si le pion devient une dame, alors dame = TRUE;
				pion_retire.score = pion_vector_grid_humain.at(i).score;		// score calculé pour ce pion (évaluation minimax)
				pion_retire.move = pion_vector_grid_humain.at(i).move;
				pion_retire.hasMoved = pion_vector_grid_humain.at(i).hasMoved;
			};

		};

	}
	else																// ID < 0, donc pion humain joue.
	{
		for (i = 0; i < pion_vector_grid_ordi.size(); i++)				// recherche le pion qui est retiré.  Le pion retiré est toujours un opposant.  Si joueur = humain, opposant = ordi.
		{
			if (pion_vector_grid_ordi.at(i).ID == lePion.removed_ID)
			{
				//pion_vector_grid_humain.erase(pion_vector_grid_humain.begin() + i);
				
				pion_vector_grid_ordi.at(i).removed = true;
				pion_vector_grid_ordi.at(i).removed_x = lePion.removed_x;
				pion_vector_grid_ordi.at(i).removed_y = lePion.removed_y;

				pion_retire.ID = lePion.removed_ID;
				pion_retire.removed = true;
				pion_retire.removed_ID = lePion.removed_ID;
				pion_retire.removed_x = lePion.removed_x;
				pion_retire.removed_y = lePion.removed_y;
				pion_retire.new_x = pion_vector_grid_ordi.at(i).new_x;		// coordonnees X (destination lors d'un déplacement)
				pion_retire.new_y = pion_vector_grid_ordi.at(i).new_y;		// coordonnees Y
				pion_retire.actual_x = pion_vector_grid_ordi.at(i).actual_x;		// coordonnees X (destination lors d'un déplacement)
				pion_retire.actual_y = pion_vector_grid_ordi.at(i).actual_y;		// coordonnees Y
				pion_retire.dame = pion_vector_grid_ordi.at(i).dame;		// si le pion devient une dame, alors dame = TRUE;
				pion_retire.score = pion_vector_grid_ordi.at(i).score;		// score calculé pour ce pion (évaluation minimax)
				pion_retire.move = pion_vector_grid_ordi.at(i).move;
				pion_retire.hasMoved = pion_vector_grid_ordi.at(i).hasMoved;

						
			};

		};

	};
	return pion_retire;

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
		TransferTousPionToMainGrid();			// Repeuple la grille de jeu main
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
				grid_main[i][j].actual_x = 0;								// coordonnees X (origine lors d'un déplacement)
				grid_main[i][j].actual_y = 0;								// coordonnees Y
				
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
			int x = pion_vector_ordi.at(pionID).actual_x;
			int y = pion_vector_ordi.at(pionID).actual_y;

			grid_main[x][y].ID = pion_vector_ordi.at(pionID).ID;									// Pour chaque pion, marque la case où se trouve ce pion.  Equipe > 0 = ordi, Equipe < 0 = humain, 0= vide
			grid_main[x][y].removed = pion_vector_ordi.at(pionID).removed;							// état du pion (removed = pion retiré)
			grid_main[x][y].new_x = pion_vector_ordi.at(pionID).new_x;								// coordonnees X (destination lors d'un déplacement)
			grid_main[x][y].new_y = pion_vector_ordi.at(pionID).new_y;								// coordonnees Y
			grid_main[x][y].actual_x = pion_vector_ordi.at(pionID).actual_x;								// coordonnees X (origine lors d'un déplacement)
			grid_main[x][y].actual_y = pion_vector_ordi.at(pionID).actual_y;								// coordonnees Y
			grid_main[x][y].dame = pion_vector_ordi.at(pionID).dame;								// si le pion devient une dame, alors dame = TRUE;
			grid_main[x][y].score = pion_vector_ordi.at(pionID).score;								// score calculé pour ce pion (évaluation minimax)
			grid_main[x][y].move = pion_vector_ordi.at(pionID).move;								// dernier move du pion


		};

		for (unsigned short int pionID = 0; pionID < (pion_vector_humain.size()); pionID++)			// le vector pion contient les pions de l'opposant

		{
			int x = pion_vector_humain.at(pionID).actual_x;
			int y = pion_vector_humain.at(pionID).actual_y;

			grid_main[x][y].ID = pion_vector_humain.at(pionID).ID;									// Pour chaque pion, marque la case où se trouve ce pion.  Equipe > 0 = ordi, Equipe < 0 = humain, 0= vide
			grid_main[x][y].removed = pion_vector_humain.at(pionID).removed;						// état du pion (removed = pion retiré)
			grid_main[x][y].new_x = pion_vector_humain.at(pionID).new_x;							// coordonnees X (destination lors d'un déplacement)
			grid_main[x][y].new_y = pion_vector_humain.at(pionID).new_y;							// coordonnees Y
			grid_main[x][y].actual_x = pion_vector_humain.at(pionID).actual_x;							// coordonnees X (origine lors d'un déplacement)
			grid_main[x][y].actual_y = pion_vector_humain.at(pionID).actual_y;							// coordonnees Y
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
				grid_sub[i][j].actual_x = grid_main[i][j].actual_x;							// coordonnees X (origine lors d'un déplacement)
				grid_sub[i][j].actual_y = grid_main[i][j].actual_y;							// coordonnees Y
				grid_sub[i][j].dame = grid_main[i][j].dame;							// si le pion devient une dame, alors dame = TRUE;
				grid_sub[i][j].score = grid_main[i][j].score; 							// score calculé pour ce pion (évaluation minimax)
				grid_sub[i][j].move = grid_main[i][j].move; 							// dernier move du pion
				
				

			};
		};
	}


	CGrid::pion CGrid::TrouveBestPionOrdi()										//recherche le pion qui a le plus haut pointage pour le prochain mouvement (selon minimax)
	{
		int random_ID, min_pion_y_ID, min_pion_y, best_y, worst_ID;
		int score, le_niveau, move;

		int unsigned ID;

		unsigned short int i,j,k;
		pion temp_pion;														
		score = -1000;
		// initialise à la valeur négative la plus élevée possible...

		std::vector <pion> listeMeilleursPions;									// contient la liste des meilleurs pions ( 5 max)
		std::vector <pion> listeFinaleMeilleursPions;

		listeMeilleursPions.clear();

		best_y = 0;																// position en "y" de départ afin de déterminer quels sont les pions les plus près de l'ennemi. ordi min "y" = 0 et augmente vers 9.,  
																				// ordi part de "y"= 0 et augmente vers 9
		// initialise à la valeur négative la plus élevée possible...
		
		
		pion bestPion;

		bestPion.score = 0;
		bestPion.ID = 0;
		worst_ID = 0;
		min_pion_y = 9;


		for (i = 0; i < pion_vector_ordi.size(); i++)
		{
			temp_pion = pion_vector_ordi.at(i);

			if (temp_pion.score > 0)											// trouve tous les pions qui ont un score différent de "0". (s'il y en a ...)
			{
				
				if (temp_pion.score > bestPion.score)
				{
					listeMeilleursPions.clear();
					bestPion.score = temp_pion.score;							// Identifie le meilleur pion s'il y en a plus d'un.
					bestPion.ID = temp_pion.ID;
					bestPion.move = temp_pion.move;

				};

				if (temp_pion.score == bestPion.score)
				{
					listeMeilleursPions.push_back(temp_pion);					// on a plus d'un pion avec le meilleur score alors il faudra choisir
				};

			};
		};


		if (listeMeilleursPions.size() == 0)									// Si la liste est vide, alors il n'y a aucun pion qui a un score > 0.  IL faut alors chercher les pions les mieux placés et un choisir un pour bouger.
		{

			for (i = 0; i < pion_vector_ordi.size(); i++)
			{
				temp_pion = pion_vector_ordi.at(i);


				if (listeMeilleursPions.size() < m_nbre_pion_meilleurs)			// prendre les "n" premiers pions (max) pour commencer à peupler le vecteur des meilleurs pions.
																				// il se peut qu'on ait moins de 5 pions s'il reste moins de 5 pions en jeu.
				{
					listeMeilleursPions.push_back(temp_pion);

					if (temp_pion.actual_y > best_y)
					{
						best_y = temp_pion.actual_y;								// trouve le pion le plus rapproché de l'ennemi (celui qui est le plus près de y = 9)
					};

					if (temp_pion.actual_y < min_pion_y)
					{
						min_pion_y = temp_pion.actual_y;							// trouve le pion le plus éloigné de l'ennemi (celui qui est le plus près de y = 0).  Sera utilisé pour substitutions dans "else"
					};
					


				}


				else
				{

					if (temp_pion.actual_y > best_y)									// ici, on a déjà 5 pions dans la liste et on compare le nouveau pion avec ceux déjà enregistré.  S'il est plus près de l'ennemi, on remplace un pion de la liste.
					{
						min_pion_y_ID = 0;
						best_y = temp_pion.actual_y;
																					// dans la liste, trouve le pions avec le "y" le plus petit (le plus éloigné de l'ennemi) et le remplacer par ce pion.
						for (j = 0; j < listeMeilleursPions.size(); j++)
						{
							
							if (listeMeilleursPions.at(j).actual_y == min_pion_y)
							{
								min_pion_y_ID = j;									// recherche le pion le plus éloigné de l'ennemi (celui avec le "y" le plus petit)
								min_pion_y = listeMeilleursPions.at(j).actual_y;
							};
						};

						listeMeilleursPions.at(min_pion_y_ID) = temp_pion;

						min_pion_y = 9;

						for (k = 0; k < listeMeilleursPions.size(); k++)			// recherche et mise à jour du nouveau min_pion_y
						{
							if (listeMeilleursPions.at(k).actual_y < min_pion_y)
							{
								min_pion_y_ID = k;								// recherche le pion le plus éloigné de l'ennemi (celui avec le "y" le plus petit)
								min_pion_y = listeMeilleursPions.at(k).actual_y;
							};

						};
					
					}  // Fin:  if (temp_pion.actual_y > best_y)

					else															// si le pion n'améliore pas le meilleur "y", peut-il améliorer le pire "min_pion_y"?
					{
						if (temp_pion.actual_y > min_pion_y)
						{
							min_pion_y = 9;

							for (k = 0; k < listeMeilleursPions.size(); k++)			// recherche et mise à jour du min_pion_y
							{
								if (listeMeilleursPions.at(k).actual_y < min_pion_y)
								{
									min_pion_y_ID = k;								// recherche le pion le plus éloigné de l'ennemi (celui avec le "y" le plus petit)
									min_pion_y = listeMeilleursPions.at(k).actual_y;
								};

							};

							listeMeilleursPions.at(min_pion_y_ID) = temp_pion;
						};
					};
				}; // FIN  "else" de :  if (listeMeilleursPions.size() < 5)... else
			}; //  FIN for(...)
		}  // if (listeMeilleursPions.size() == 0)   FIN for(...)

		else			// else de :  if (listeMeilleursPions.size() == 0)  la liste les meilleurs pions un score > 0.
		
		{																								// le meilleur pion a déjà été identifié lors du premier scan des pions. il suffit de le retourner pour compléter.	
			
			srand(time(NULL));

			random_ID = rand() % 100;

			random_ID = random_ID * listeMeilleursPions.size();

			random_ID = random_ID / 100;


			bestPion = listeMeilleursPions.at(random_ID);

			return bestPion;																				// cherche le pion avec le meilleur score et joue le.

		};
		
		// rendu ici, on a une liste avec des pions qui sont les mieux positionnés (y le plus élevé).  Reste à choisir le quel on veut faire bouger...

		le_niveau = 0;

																											// On recherche alors un pion qui peut se déplacer et qui est le plus près de l'ennemi.
			for (ID = 0; ID < listeMeilleursPions.size(); ID++)
			{
																											// ICI, on vérifie si les ions peuvent bouger.
					listeMeilleursPions.at(ID).hasMoved = FALSE;

				for (move = 0; move < 2; move++)
				{
					temp_pion = EvalueMove(listeMeilleursPions.at(ID), delta_x, delta_y, le_niveau, move);
					
					if (temp_pion.hasMoved)																	// si le pion peut bouger, on le marque 
					{
						listeMeilleursPions.at(ID).hasMoved = TRUE;
						listeMeilleursPions.at(ID).move = move;
							
					};

				};  // FIN:  for (move...

			};  // FIN:  for (ID =0...

			listeFinaleMeilleursPions.clear();

			for (ID = 0; ID < listeMeilleursPions.size(); ID++)
			{
					
					if (listeMeilleursPions.at(ID).hasMoved)																	// si le pion ne peut bouger, on le retire de la liste...
					{
						listeFinaleMeilleursPions.push_back(listeMeilleursPions.at(ID));

					};

			};  // FIN:  for (ID =0...

			// rendu ici, on a une list de pions les mieux placés et qui peuvent bouger (hasMoved = true).  On choisit au hasard un pion et on le fait bouger.
				
			if (listeFinaleMeilleursPions.size() == 0)
			{

				//ICI on ne trouve aucun pion 'a jouer.  Problemo...

				bestPion.ID = -100;			// ID= -1 indique qu'aucun pion n'a été trouvé...
				return bestPion;
			};
			
			
			srand(time(NULL));

			random_ID = rand() % 100;

			random_ID = random_ID * listeFinaleMeilleursPions.size();

			random_ID = random_ID / 100;


			bestPion = listeFinaleMeilleursPions.at(random_ID);

			
		

		return bestPion;
	}

	CGrid::pion CGrid::TrouveBestPionHumain()									//recherche le pion qui a le plus haut pointage pour le prochain mouvement (selon minimax)
	{
		int random_ID, min_pion_y_ID, min_pion_y, best_y, worst_ID;
		int score, le_niveau, move;
		int unsigned ID;
		unsigned short int i, j, k;
		pion temp_pion;
		score = -1000;															// initialise à la valeur négative la plus élevée possible...
		

		

		std::vector <pion> listeMeilleursPions;									// contient la liste des meilleurs pions ( 5 max)
		std::vector <pion> listeFinaleMeilleursPions;

		listeMeilleursPions.clear();

		best_y = 9;																// position en "y" de départ afin de déterminer quels sont les pions les plus près de l'ennemi. humain min "y" = 9 et diminue vers 0.,  
																				// humain part de "y"= 9 et diminue vers 0
		// initialise à la valeur négative la plus élevée possible...


		pion bestPion;

		bestPion.score = 0;
		bestPion.ID = 0;
		worst_ID = 0;
		min_pion_y = 0;


		for (i = 0; i < pion_vector_humain.size(); i++)
		{
			temp_pion = pion_vector_humain.at(i);

			if (temp_pion.score > 0)											// trouve tous les pions qui ont un score différent de "0". (s'il y en a ...)
			{
				if (temp_pion.score > bestPion.score)
				{
					listeMeilleursPions.clear();
					//listeMeilleursPions.push_back(temp_pion);
					bestPion.score = temp_pion.score;							// Identifie le meilleur pion s'il y en a plus d'un.
					bestPion.ID = temp_pion.ID;
					bestPion.move = temp_pion.move;
					
				};
				
				
				if (temp_pion.score == bestPion.score)
				{
					listeMeilleursPions.push_back(temp_pion);					// on a plus d'un pion avec le meilleur score alors il faudra choisir
				};

			};
		};


		if (listeMeilleursPions.size() == 0)									// Si la liste est vide, alors il n'y a aucun pion qui a un score > 0.  IL faut alors chercher les pions les mieux placés et un choisir un pour bouger.
		{

			for (i = 0; i < pion_vector_humain.size(); i++)
			{
				temp_pion = pion_vector_humain.at(i);


				if (listeMeilleursPions.size() < m_nbre_pion_meilleurs)								// prendre les 5 premiers pions (max) pour commencer à peupler le vecteur des meilleurs pions.
																				// il se peut qu'on ait moins de 5 pions s'il reste moins de 5 pions en jeu.
				{
					listeMeilleursPions.push_back(temp_pion);

					if (temp_pion.actual_y < best_y)
					{
						best_y = temp_pion.actual_y;								// trouve le pion le plus rapproché de l'ennemi (celui qui est le plus près de y = 0)
					};

					if (temp_pion.actual_y > min_pion_y)
					{
						min_pion_y = temp_pion.actual_y;							// trouve le pion le plus éloigné de l'ennemi (celui qui est le plus près de y = 9).  Sera utilisé pour substitutions dans "else"
					};



				}


				else
				{

					if (temp_pion.actual_y < best_y)									// ici, on a déjà 5 pions dans la liste et on compare le nouveau pion avec ceux déjà enregistré.  S'il est plus près de l'ennemi, on remplace un pion de la liste.
					{
						min_pion_y_ID = 0;
						best_y = temp_pion.actual_y;
																					// dans la liste, trouve le pions avec le "y" le plus petit (le plus éloigné de l'ennemi) et le remplacer par ce pion.
						for (j = 0; j < listeMeilleursPions.size(); j++)
						{

							if (listeMeilleursPions.at(j).actual_y == min_pion_y)
							{
								min_pion_y_ID = j;									// recherche le pion le plus éloigné de l'ennemi (celui avec le "y" le plus petit)
								min_pion_y = listeMeilleursPions.at(j).actual_y;
							};
						};

						listeMeilleursPions.at(min_pion_y_ID) = temp_pion;

						min_pion_y = 0;

						for (k = 0; k < listeMeilleursPions.size(); k++)			// recherche et mise à jour du nouveau min_pion_y (le pire pion pour sa position eloignee du but)
						{
							if (listeMeilleursPions.at(k).actual_y > min_pion_y)
							{
								min_pion_y_ID = k;									// recherche le pion le plus éloigné de l'ennemi (celui avec le "y" le plus grand)
								min_pion_y = listeMeilleursPions.at(k).actual_y;
							};

						};

					}  // Fin:  if (temp_pion.actual_y > best_y)

					else															// si le pion n'améliore pas le meilleur "y", peut-il améliorer le pire "min_pion_y"?
					{
						if (temp_pion.actual_y < min_pion_y)
						{
							min_pion_y = 0;

							for (k = 0; k < listeMeilleursPions.size(); k++)		// recherche et mise à jour du min_pion_y
							{
								if (listeMeilleursPions.at(k).actual_y > min_pion_y)
								{
									min_pion_y_ID = k;								// recherche le pion le plus éloigné de l'ennemi (celui avec le "y" le plus grand)
									min_pion_y = listeMeilleursPions.at(k).actual_y;
								};

							};

							listeMeilleursPions.at(min_pion_y_ID) = temp_pion;
						};
					};
				}; // FIN  "else" de :  if (listeMeilleursPions.size() < 5)... else
			}; //  FIN for(...)
		}  // if (listeMeilleursPions.size() == 0)   FIN for(...)

		else			// else de :  if (listeMeilleursPions.size() == 0)  la liste les meilleurs pions un score > 0.

		{																			// le meilleur pion a déjà été identifié lors du premier scan des pions. il suffit de le retourner pour compléter.	
			
			
			
			srand(time(NULL));

			random_ID = rand() % 100;

			random_ID = random_ID * listeMeilleursPions.size();

			random_ID = random_ID / 100;


			bestPion = listeMeilleursPions.at(random_ID);

			return bestPion;														// cherche le pion avec le meilleur score et joue le.

		};

		// rendu ici, on a une liste avec des pions qui sont les mieux positionnés (y le plus élevé).  Reste à choisir le quel on veut faire bouger...

		le_niveau = 0;

																										// On recherche alors un pion qui peut se déplacer et qui est le plus près de l'ennemi.
		for (ID = 0; ID < listeMeilleursPions.size(); ID++)
		{
			listeMeilleursPions.at(ID).hasMoved = FALSE;

			for (move = 0; move < 2; move++)
			{
				temp_pion = EvalueMove(listeMeilleursPions.at(ID), delta_x, delta_y, le_niveau, move);

				if (temp_pion.hasMoved)																	// si le pion peut bouger, on le marque 
				{
					listeMeilleursPions.at(ID).hasMoved = TRUE;
					listeMeilleursPions.at(ID).move = move;

				};

			
			};  // FIN:  for (move...

		};  // FIN:  for (ID =0...

		listeFinaleMeilleursPions.clear();

		for (ID = 0; ID < listeMeilleursPions.size(); ID++)
		{

			if (listeMeilleursPions.at(ID).hasMoved)																	// si le pion ne peut bouger, on le retire de la liste...
			{
				listeFinaleMeilleursPions.push_back(listeMeilleursPions.at(ID));

			};

		};  // FIN:  for (ID =0...
			
			// rendu ici, on a une list de pions les mieux placés et qui peuvent bouger (hasMoved = true).  On choisit au hasard un pion et on le fait bouger.

		if (listeFinaleMeilleursPions.size() == 0)
		{

			//ICI on ne trouve aucun pion 'a jouer.  Problemo...

			bestPion.ID = -100;			// ID= -1 indique qu'aucun pion n'a été trouvé...
			return bestPion;
		};
		
		
		srand(time(NULL));

		random_ID = rand() % 100;

		random_ID = random_ID * listeFinaleMeilleursPions.size();

		random_ID = random_ID / 100;


		bestPion = listeFinaleMeilleursPions.at(random_ID);



		return bestPion;
	}




	void CGrid::CalculScoreInitial()																	// le score d'un joueur est le nombre de pion qui reste en jeu;
	{

		score_ordi_initial = pion_vector_ordi.size();

		score_humain_initial = pion_vector_humain.size();

	}


	int CGrid::CalculScoreGrid_max(CGrid::pion &lePion)
	{
		// utilisé par calculMove_max pour calculer le pointage.  Ici, le pointage est calculé du point de vue du pion_max.  IE le pion qui cherche à maximiser ses points est l'attaquant.
		//"lePion" identifie qui est l'attaquant.  Le calcul se fait du point de son point de vue.
		
		if (lePion.ID > 0)
		{
			lePion.score = (GetScoreInitialHum() - GetScoreGridHum()) - ( GetScoreInitialOrdi() - GetScoreGridOrdi());  // 

			// score = gains (pions retirés de l'opposant) - pertes (pions perdus de mon équipe)
			
		};


		// SI L'HUMAIN JOUE, LA FORMULE DE CALCUL DU POINTAGE DEVIENT:
		if (lePion.ID < 0)
		{
			lePion.score = (GetScoreInitialOrdi() - GetScoreGridOrdi()) - (GetScoreInitialHum() - GetScoreGridHum());	 
			
			// score = gains (pions retirés de l'opposant) - pertes (pions perdus de mon équipe)
		};

		

		return lePion.score;
	
	};

	int CGrid::CalculScoreGrid_min(CGrid::pion &lePion)
	{
		// utilisé par calculMove_min pour calculer le pointage.  Ici, le pointage est calculé du point de vue de l'opposant du pion_max.  IE le pion qui cherche à maximiser ses points est l'opposant. 
		//"lePion" identifie qui est l'attaquant.  Le calcul se fait du point de vue de son opposant.

		if (lePion.ID > 0)
		{
			lePion.score =  (GetScoreInitialOrdi() - GetScoreGridOrdi()) - (GetScoreInitialHum() - GetScoreGridHum());  

			// score = gains (pions retirés de l'opposant) - pertes (pions perdus de mon équipe)

		};


		// SI L'HUMAIN JOUE, LA FORMULE DE CALCUL DU POINTAGE DEVIENT:
		if (lePion.ID < 0)
		{
			lePion.score = (GetScoreInitialHum() - GetScoreGridHum()) - (GetScoreInitialOrdi() - GetScoreGridOrdi());

			// score = gains (pions retirés de l'opposant) - pertes (pions perdus de mon équipe)
		};



		return lePion.score;

	};

	void CGrid::ComptePionsGrid()																		// le score d'un joueur est le nombre de pion qui reste en jeu;
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
			temp_pion.move = 0;
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
			temp_pion.move = 0;
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


						return 1;
					};

										
				};

			};

			return 0;

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
						return 1;
					};
					
				};

			};

			return 0;

		};

		
	};


	void CGrid::CreatePionsOrdi()
	{

		int i;
		pion pion_1;
		pion_vector_ordi.clear();

		// CODE DEBUG ******************************************

/*		pion_1.ID = 15;
		pion_1.actual_x = 3;
		pion_1.actual_y = 3;
		pion_1.new_x = pion_1.actual_x;
		pion_1.new_y = pion_1.actual_y;
		pion_1.hasMoved = FALSE;
		pion_1.niveau = 0;
		pion_1.dame = false;
		pion_1.score = -1000;
		pion_1.move = 0;												// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
		pion_1.removed = false;
		pion_vector_ordi.push_back(pion_1);

		pion_1.ID = 18;
		pion_1.actual_x = 7;
		pion_1.actual_y = 5;
		pion_1.new_x = pion_1.actual_x;
		pion_1.new_y = pion_1.actual_y;
		pion_1.hasMoved = FALSE;
		pion_1.niveau = 0;
		pion_1.dame = false;
		pion_1.score = -1000;
		pion_1.move = 0;												// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
		pion_1.removed = false;
		pion_vector_ordi.push_back(pion_1);


		pion_1.ID = 20;
		pion_1.actual_x = 5;
		pion_1.actual_y = 3;
		pion_1.new_x = pion_1.actual_x;
		pion_1.new_y = pion_1.actual_y;
		pion_1.hasMoved = FALSE;
		pion_1.niveau = 0;
		pion_1.dame = false;
		pion_1.score = -1000;
		pion_1.move = 0;												// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.
		pion_1.removed = false;
		pion_vector_ordi.push_back(pion_1);

		//*****************************************************

*/		for (i = 1; i < max_grid_size/2+1; i++)								// crée les pions de la rangée "0"
		{

			pion_1.ID = i;
			pion_1.actual_x = (i-1) * 2;
			pion_1.actual_y = 0;
			pion_1.new_x = pion_1.actual_x;
			pion_1.new_y = pion_1.actual_y;
			pion_1.hasMoved = FALSE;
			pion_1.niveau = 0;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = 0;												
			pion_1.removed = false;
			pion_vector_ordi.push_back(pion_1);
		};

		for (i = max_grid_size / 2 + 1; i < max_grid_size + 1; i++)			// crée les pions de la rangée "1"
		{

			pion_1.ID = i;
			pion_1.actual_x = (i - (max_grid_size / 2 + 1)) * 2 + 1;
			pion_1.actual_y = 1;
			pion_1.new_x = pion_1.actual_x;
			pion_1.new_y = pion_1.actual_y;
			pion_1.hasMoved = FALSE;
			pion_1.niveau = 0;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = 0;												
			pion_1.removed = false;	
			pion_vector_ordi.push_back(pion_1);
		};

		for (i = max_grid_size + 1; i < max_grid_size*1.5 + 1; i++)			// crée les pions de la rangée "2"
		{

			pion_1.ID = i;
			pion_1.actual_x = (i - (max_grid_size + 1)) * 2;
			pion_1.actual_y = 2;
			pion_1.new_x = pion_1.actual_x;
			pion_1.new_y = pion_1.actual_y;
			pion_1.hasMoved = FALSE;
			pion_1.niveau = 0;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = 0;												
			pion_1.removed = false;
			pion_vector_ordi.push_back(pion_1);
		};

		for (i = max_grid_size * 1.5 + 1; i < max_grid_size*2+1; i++)		// crée les pions de la rangée "3"
		{

			pion_1.ID = i;
			pion_1.actual_x = (i - (max_grid_size * 1.5 + 1)) * 2 + 1;
			pion_1.actual_y = 3;
			pion_1.new_x = pion_1.actual_x;
			pion_1.new_y = pion_1.actual_y;
			pion_1.hasMoved = FALSE;
			pion_1.niveau = 0;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = 0;												
			pion_1.removed = false;
			pion_vector_ordi.push_back(pion_1);
		};

		
	}


	void CGrid::CreatePionHumain()
	{
		int i;
		pion pion_1;
		pion_vector_humain.clear();

		// DEBUG CODE ***************************************
/*		pion_1.ID = -18;
		pion_1.actual_x = 5;
		pion_1.actual_y = 5;
		pion_1.new_x = pion_1.actual_x;
		pion_1.new_y = pion_1.actual_y;
		pion_1.hasMoved = FALSE;
		pion_1.niveau = 0;
		pion_1.dame = false;
		pion_1.score = -1000;
		pion_1.move = 0;												// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.	
		pion_1.removed = false;
		pion_vector_humain.push_back(pion_1);



		pion_1.ID = -19;
		pion_1.actual_x = 6;
		pion_1.actual_y = 6;
		pion_1.new_x = pion_1.actual_x;
		pion_1.new_y = pion_1.actual_y;
		pion_1.hasMoved = FALSE;
		pion_1.niveau = 0;
		pion_1.dame = false;
		pion_1.score = -1000;
		pion_1.move = -1;												// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.	
		pion_1.removed = false;
		pion_vector_humain.push_back(pion_1);

		
		pion_1.ID = -20;
		pion_1.actual_x = 9;
		pion_1.actual_y = 5;
		pion_1.new_x = pion_1.actual_x;
		pion_1.new_y = pion_1.actual_y;
		pion_1.hasMoved = FALSE;
		pion_1.niveau = 0;
		pion_1.dame = false;
		pion_1.score = -1000;
		pion_1.move = -1;												// move = -1 indique qu'aucun move n'a été fait.  Donc ne pas tenir compte du score.	
		pion_1.removed = false;
		pion_vector_humain.push_back(pion_1);
*/	// DEBUG CODE ***************************************





		
		for (i = 1; i < max_grid_size / 2 + 1; i++)							// crée les pions de la rangée "0"
		{

			pion_1.ID = -i;
			pion_1.actual_x = (i-1) * 2 + 1;
			pion_1.actual_y = 9;
			pion_1.new_x = pion_1.actual_x;
			pion_1.new_y = pion_1.actual_y;
			pion_1.hasMoved = FALSE;
			pion_1.niveau = 0;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = 0;													
			pion_1.removed = false;						
			pion_vector_humain.push_back(pion_1);
		};

		for (i = max_grid_size / 2 + 1; i < max_grid_size + 1; i++)			// crée les pions de la rangée "1"
		{

			pion_1.ID = -i;
			pion_1.actual_x = (i - (max_grid_size / 2 + 1)) * 2;
			pion_1.actual_y = 8;
			pion_1.new_x = pion_1.actual_x;
			pion_1.new_y = pion_1.actual_y;
			pion_1.hasMoved = FALSE;
			pion_1.niveau = 0;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = 0;												
			pion_1.removed = false;
			pion_vector_humain.push_back(pion_1);
		};

		for (i = max_grid_size + 1; i < max_grid_size*1.5 + 1; i++)			// crée les pions de la rangée "2"
		{

			pion_1.ID = -i;
			pion_1.actual_x = (i - (max_grid_size + 1)) * 2 + 1;
			pion_1.actual_y = 7;
			pion_1.new_x = pion_1.actual_x;
			pion_1.new_y = pion_1.actual_y;
			pion_1.hasMoved = FALSE;
			pion_1.niveau = 0;
			pion_1.dame = false;
			pion_1.score = -1000;
			pion_1.move = 0;												
			pion_1.removed = false;
			pion_vector_humain.push_back(pion_1);
		};

		
		for (i = max_grid_size * 1.5 + 1; i < max_grid_size * 2 + 1; i++)	// crée les pions de la rangée "3"
		{

				pion_1.ID = -i;
				pion_1.actual_x = (i - (max_grid_size * 1.5 + 1)) * 2;
				pion_1.actual_y = 6;
				pion_1.new_x = pion_1.actual_x;
				pion_1.new_y = pion_1.actual_y;
				pion_1.hasMoved = FALSE;
				pion_1.niveau = 0;
				pion_1.dame = false;
				pion_1.score = -1000;
				pion_1.move = 0;																	
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
	//*****************************************************************************

	int CGrid::GetPionVectOrdi_grid_Size()
	{

		return pion_vector_grid_ordi.size();
	};

	int CGrid::GetPionVectHum_grid_Size()
	{

		return pion_vector_grid_humain.size();
	};
	



	CGrid::pion CGrid::EvalueMove(pion & pion_1, int m_delta_X, int m_delta_y, int le_niveau, int move)
	{

		// Evalue si la nouvelle position est libre et qu'on reste dans les limites du jeu
		// Si on est dans les limites, on vérifie si on peut bouger (destination libre).  Si on peut bouger, on retourne un pion avec la nouvelle position et les coordonnées du pion sont mises à jour.		
		// Si on est hors limites, alors on retourne move = pion_min 
		// Si on reste dans les limites et que move>0, alors les coordonnées new_y, new_y contiennent la nouvelle position du pion.  actual_x, actual_y contiennent la position originale.
		// Si le move attérit sur un pion ennemi et que la case suivante est libre, alors on peut passer par dessus le pion ennemi (double delta_x, delta_y) et le retirer du jeu.  
		// Restera à retirer le pion ennemi.


		pion m_pion, pion_removed;;

		int dx, dy,a,b,c;
		
		m_pion.ID = pion_1.ID;
		m_pion.actual_x = pion_1.actual_x;
		m_pion.actual_y = pion_1.actual_y;
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
		
		

		

		switch (move)  //Le pion : origine = actual_x,y 
			{
			case 0:
				m_pion.new_x = pion_1.actual_x + dx;
				m_pion.new_y = pion_1.actual_y + dy;
				break;

			case 1:
				m_pion.new_x = pion_1.actual_x - dx;
				m_pion.new_y = pion_1.actual_y + dy;
				break;

			case 2:
				m_pion.new_x = pion_1.actual_x + dx;
				m_pion.new_y = pion_1.actual_y - dy;
				break;

			case 3:
				m_pion.new_x = pion_1.actual_x - dx;
				m_pion.new_y = pion_1.actual_y - dy;
				break;
/*************************DEBUG CODE**************************************************/

			default:
				m_pion.new_x = pion_1.actual_x - dx;


				/***********************************************************/
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
			





				return m_pion;														//Retourne le pion et les nouvelles coordonnées (new_x, new_y) sont valides. On peut déplacer ce pion.
			};

			
			
			if (c > 0)			
																				// les ID sont de même signe, l'opération donne >0 alors la case est occupée par un pion de la même équipe.  Pion reste dans la position actual_x, actual_y.  
				
			{
				
																				// Contient un pion de notre équipe, on ne peut bouger.

				m_pion.new_x = m_pion.actual_x;
				m_pion.new_y = m_pion.actual_y;
				m_pion.hasMoved = FALSE;
				m_pion.removed = FALSE;

				



				return m_pion;
			};
			
			


																					//Dernier cas possible:  "C < 0" ici
																					// les 2 sont de signe différent. La case est occupée par un pion de l'autre équipe.
				

																					//On peut vérifier si on peut retirer le pion en passant par dessus le pion ennemi: but: manger le pion ennemi.

				
				m_pion.removed_x = m_pion.new_x;									// sauvegarde les coordonnées du  pion ennemi qui pourrait être retiré, avant de faire l'analyse qui suit.
				m_pion.removed_y = m_pion.new_y;
				m_pion.removed_ID = grid_sub[m_pion.new_x][m_pion.new_y].ID;		// sauvegarde l'ID du pion qui sera retiré


				switch (move)														//Calcule la case destination suivante à évaluer.  
																					//Est-ce qu'on peut accéder à cette case? 
																					//Si oui, on saute par dessus pion ennemi et on le retire.
				{
				case 0:
					m_pion.new_x = m_pion.new_x + dx;
					m_pion.new_y = m_pion.new_y + dy;
					break;

				case 1:
					m_pion.new_x = m_pion.new_x - dx;
					m_pion.new_y = m_pion.new_y + dy;
					break;

				case 2:
					m_pion.new_x = m_pion.new_x + dx;
					m_pion.new_y = m_pion.new_y - dy;
					break;

				case 3:
					m_pion.new_x = m_pion.new_x - dx;
					m_pion.new_y = m_pion.new_y - dy;
					break;

				};  // fin : switch(move)
				


				if (m_pion.new_x > -1 && m_pion.new_x < max_grid_size && m_pion.new_y> -1 && m_pion.new_y < max_grid_size)		
																				// Vérifie si le pion est dans les limites de la grille de jeu
				{
					if (grid_sub[m_pion.new_x][m_pion.new_y].ID == 0)			// Évalue la case derrière le pion ennemi.  Est-elle libre? Si oui, on peut sauter par dessus le pion ennemi et le retirer.
					{
						m_pion.removed = true;									// Indique qu'on peut retirer un pion ennemi.  Les coordonnées new.x, new.y sont valides pour le pion qui attaque.  m_pion.removed_x,y contient les coordonnées du pion retiré.
						m_pion.hasMoved = TRUE;									// le pion s'est déplacé.  A conserver cette info pour l'évaluation au prochain niveau.  Nouveau point de départ de l'analyse = new_x, new_y.
						return m_pion;
					}
					else														// ici, la case derrière le pion ennemi n'est pas libre. On ne peut sauter et retirer le pion ennemi																
					{
						

						m_pion.new_x = pion_1.actual_x;							// remet les coordonnées tel qu'avant l'évaluation du saut.
						m_pion.new_y = pion_1.actual_y;
						m_pion.removed = FALSE;
						m_pion.hasMoved = FALSE;

						
						return m_pion;									
					}; 
				
				} 
				else
				{																// pion tombe hors limite du jeu.  On ne peut bouger le pion.

					m_pion.new_x = pion_1.actual_x;
					m_pion.new_y = pion_1.actual_y;
					m_pion.removed = FALSE;
					m_pion.hasMoved = FALSE;


					return m_pion;

				};//fin: if (pion dans limites du jeu)

			//};  // fin: if c < 0)

			
		} // fin: si pion est dans les limites du jeu

		else															// ici le pion se retrouve hors de la grille de jeu.  On ne peut effectuer ce move.
		{
		m_pion.new_x = pion_1.actual_x;
		m_pion.new_y = pion_1.actual_y;
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
		bool problemeSize = FALSE;

		
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

	int CGrid::GetPionScore(pion pionID)
	{
		
		int unsigned i;
		if (pionID.ID > 0)												// ID >0 -> pion ordi  , ID < 0 -> pion_humain
		{
			for (i = 0; i < pion_vector_ordi.size(); i++)
			{
				if (pion_vector_ordi.at(i).ID == pionID.ID)
				{
					return pionID.score;
									
				};

			};
		}
		else																// ID < 0, donc pion humain.
		{
			for (i = 0; i < pion_vector_humain.size(); i++)
			{
				if (pion_vector_humain.at(i).ID == pionID.ID)
				{
					return pionID.score;
				};
			};
		};

	};

	bool CGrid::MovePion(pion &pion_1, int m_delta_X, int m_delta_y, int move)
	{
	
		CGrid::pion pion, retire_pion_opposant;
		int i, size, niveau;
		niveau = 0;

		pion = EvalueMove(pion_1, m_delta_X, m_delta_y, niveau,move);

		
		if (pion.hasMoved)
		{
			pion_1.actual_x = pion.new_x;
			pion_1.actual_y = pion.new_y;
			pion_1.new_x = pion.new_x;
			pion_1.new_y = pion.new_y;
			
			
			pion_1.hasMoved = FALSE;
			pion_1.niveau = 0;
			pion_1.dame = false;
			pion_1.removed = false;
			
			
			if (pion_1.ID > 0)
			{
				size = pion_vector_ordi.size();

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
				size = pion_vector_humain.size();

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
			
			TransferTousPionToMainGrid();
			CloneGridMainToSub();
			ResetPionVectorGrid();

			
			return TRUE;

		}
		else   // if (pion.hasMoved)
		{
			pion_1.actual_x = pion.new_x;
			pion_1.actual_y = pion.new_y;
			pion_1.new_x = pion.actual_x;
			pion_1.new_y = pion.actual_y;


			pion_1.hasMoved = FALSE;
			pion_1.niveau = 0;
			pion_1.dame = false;
			//pion_1.score = -1000;
			//pion_1.move = 0;												
			pion_1.removed = false;
			return FALSE;

		};


	
	};

	CGrid::pion CGrid::TrouvePionAt_XY(int case_x, int case_y)
	{
		CGrid::pion lePion;

		int sizeVect = 0;
		
		sizeVect = sizeVect = GetPionVectHumSize();
		int i =0;

		for (i = 0; i < sizeVect; i ++)
		{
			lePion = GetPionFromVectHumain(i);				//retourne le pion "humain" pion(pionID = i)

			if (lePion.actual_x == case_x && lePion.actual_y == case_y)
				return lePion;
		};

		// si on se rend ici, c'est parce que l'utilisateur a cliqué sur un pion ORDI au lieu d'un pion Humain...

		lePion.ID = 999;		// indique que le pion n'a pas été trouvé...

		return lePion;

		
	};
