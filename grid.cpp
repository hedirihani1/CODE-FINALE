#include "Grid.h"
#include <iostream>
#include <fstream>

// Constructeur par d�faut : initialise une grille vide
Grid::Grid() : rows(0), cols(0) {}

// Constructeur avec dimensions sp�cifiques : initialise la grille avec des cellules mortes
Grid::Grid(int rows, int cols) : rows(rows), cols(cols) {
    data.resize(rows, std::vector<Cellule>(cols)); // Redimensionne la grille avec des cellules mortes
}

// M�thode pour charger les donn�es depuis un fichier
void Grid::loadFromFile(const std::string& filename) {
    std::ifstream file(filename); // Ouvre le fichier pour lecture
    if (!file.is_open()) { // V�rifie si le fichier a �t� ouvert correctement
        std::cerr << "Erreur: Impossible d'ouvrir le fichier " << filename << std::endl;
        return;
    }

    // Lit les dimensions de la grille (lignes et colonnes)
    file >> rows >> cols;

    // Redimensionne la matrice de donn�es pour correspondre aux dimensions lues
    data.resize(rows, std::vector<Cellule>(cols));

    // Lit les valeurs de la grille depuis le fichier et met � jour les cellules
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int value;
            file >> value; // Lit la valeur de chaque cellule (0 ou 1)
            data[i][j].setEtat(value == 1); // Met � jour l'�tat de la cellule (vivante ou morte)
        }
    }

    file.close(); // Ferme le fichier apr�s la lecture
}

// M�thode pour afficher la grille
void Grid::display() const {
    std::cout << "Dimensions: " << rows << "x" << cols << std::endl; // Affiche les dimensions de la grille
    for (const auto& row : data) { // Parcourt chaque ligne de la grille
        for (const auto& cell : row) { // Parcourt chaque cellule dans la ligne
            std::cout << cell << " "; // Affiche l'�tat de la cellule (vivante/morte)
        }
        std::cout << std::endl; // Nouvelle ligne apr�s chaque ligne de cellules
    }
}

// M�thode pour obtenir une cellule sp�cifique
const Cellule& Grid::getCell(int x, int y) const {
    return data[x][y]; // Retourne la cellule situ�e aux coordonn�es (x, y)
}

// M�thode pour modifier l'�tat d'une cellule sp�cifique
void Grid::setCell(int x, int y, bool vivante) {
    data[x][y].setEtat(vivante); // Met � jour l'�tat de la cellule (vivante ou morte)
}

// M�thode pour obtenir le nombre de lignes de la grille
int Grid::getRows() const {
    return rows; // Retourne le nombre de lignes
}

// M�thode pour obtenir le nombre de colonnes de la grille
int Grid::getCols() const {
    return cols; // Retourne le nombre de colonnes
}
