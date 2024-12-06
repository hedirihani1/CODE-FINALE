#ifndef RENDU_H
#define RENDU_H

#include <SFML/Graphics.hpp> // Inclut la biblioth�que SFML pour le rendu graphique
#include "Grid.h"             // Inclut la classe Grid pour la gestion de la grille

class Rendu {
private:
    sf::RenderWindow window;  // Fen�tre pour afficher la grille, utilisant SFML
    int cellSize;             // Taille d'une cellule en pixels pour l'affichage
    sf::Color couleurVivante; // Couleur des cellules vivantes (ex: verte)
    sf::Color couleurMorte;   // Couleur des cellules mortes (ex: noire)
    sf::Color couleurFond;    // Couleur de fond de la fen�tre (ex: blanc)

public:
    // Constructeur : initialisation de la fen�tre et des couleurs, et d�finition de la taille des cellules
    Rendu(int largeurFenetre, int hauteurFenetre, int tailleCellule);

    // M�thode pour dessiner la grille dans la fen�tre en fonction des cellules vivantes et mortes
    void dessinerGrille(const Grid& grille);

    // M�thode pour afficher la fen�tre (actualise l'affichage)
    void afficher();

    // M�thode pour v�rifier si la fen�tre est toujours ouverte (utile pour la boucle de rendu)
    bool estOuverte();

    // M�thode pour g�rer la pause entre les it�rations (d�lai entre les affichages)
    void attendre(int milliseconds) const;
};

#endif // RENDU_H
