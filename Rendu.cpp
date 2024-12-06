#include "Rendu.h"

// Constructeur avec couleurs par d�faut
Rendu::Rendu(int largeurFenetre, int hauteurFenetre, int tailleCellule)
    : window(sf::VideoMode(largeurFenetre, hauteurFenetre), "Jeu de la Vie - SFML"), // Cr�ation de la fen�tre avec SFML
    cellSize(tailleCellule), // Taille des cellules
    couleurVivante(sf::Color::Black), // Couleur des cellules vivantes (noir)
    couleurMorte(sf::Color::White), // Couleur des cellules mortes (blanc)
    couleurFond(sf::Color::Black) { // Couleur de fond de la fen�tre (noir)
    window.setFramerateLimit(60); // Limite le taux de rafra�chissement � 60 FPS
}

// M�thode pour dessiner la grille dans la fen�tre
void Rendu::dessinerGrille(const Grid& grille) {
    int rows = grille.getRows(); // R�cup�re le nombre de lignes
    int cols = grille.getCols(); // R�cup�re le nombre de colonnes

    window.clear(couleurFond); // Efface la fen�tre et applique la couleur de fond

    for (int x = 0; x < rows; ++x) { // Parcourt chaque ligne de la grille
        for (int y = 0; y < cols; ++y) { // Parcourt chaque colonne de la grille
            // Cr�ation d'une cellule sous forme de rectangle avec une taille de cellule donn�e
            sf::RectangleShape cell(sf::Vector2f(static_cast<float>(cellSize - 1), static_cast<float>(cellSize - 1)));
            cell.setPosition(static_cast<float>(y * cellSize), static_cast<float>(x * cellSize)); // Positionne la cellule sur la fen�tre

            // D�termine si la cellule est vivante ou morte
            if (grille.getCell(x, y).estVivante()) {
                cell.setFillColor(couleurVivante); // Cellule vivante (noire)
            }
            else {
                cell.setFillColor(couleurMorte); // Cellule morte (blanche)
            }

            window.draw(cell); // Dessine la cellule dans la fen�tre
        }
    }
}

// M�thode pour afficher la fen�tre
void Rendu::afficher() {
    window.display(); // Affiche le contenu de la fen�tre
}

// M�thode pour g�rer les �v�nements
bool Rendu::estOuverte() {
    sf::Event event;
    while (window.pollEvent(event)) { // V�rifie s'il y a des �v�nements dans la fen�tre
        if (event.type == sf::Event::Closed) { // Si l'�v�nement est la fermeture de la fen�tre
            window.close(); // Ferme la fen�tre
            return false; // Indique que la fen�tre est ferm�e
        }
    }
    return true; // La fen�tre est toujours ouverte
}

// M�thode pour attendre entre les it�rations
void Rendu::attendre(int milliseconds) const {
    sf::sleep(sf::milliseconds(milliseconds)); // Fait une pause pendant un certain nombre de millisecondes
}
