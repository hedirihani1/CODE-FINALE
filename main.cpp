#include <iostream>
#include <sstream>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include "Grid.h"
#include "Jeu.h"
#include "Fichier.h"
#include "Rendu.h"

// Génère un nom de dossier unique basé sur le nom de fichier et l'heure actuelle
std::string genererNomDossier(const std::string& filename) {
    namespace fs = std::filesystem;

    // Obtenir l'heure actuelle
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    // Convertir l'heure en format struct tm
    std::tm tm;
    localtime_s(&tm, &now_c);

    // Créer un flux de sortie pour formater l'heure
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");

    // Utiliser la base du nom du fichier pour générer le dossier de sortie
    std::string baseFilename = fs::path(filename).stem().string();
    return baseFilename + "_" + oss.str() + "_out";
}

int main() {
    // Demander à l'utilisateur le chemin du fichier d'entrée
    std::string filename;
    std::cout << "Entrez le chemin du fichier d'entrée : ";
    std::getline(std::cin, filename);

    // Charger la grille à partir du fichier
    Grid grille;
    try {
        grille.loadFromFile(filename);
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur : Impossible de charger le fichier. Vérifiez le chemin et réessayez.\n";
        return 1; // Sortie avec code d'erreur
    }

    // Générer le nom du dossier de sortie en fonction du fichier d'entrée
    std::string dossierSortie = genererNomDossier(filename);
    Fichier gestionnaireFichier(dossierSortie);
    gestionnaireFichier.creerDossier(); // Créer le dossier de sortie

    Jeu jeu(grille, gestionnaireFichier); // Initialiser le jeu avec la grille et le gestionnaire de fichiers

    // Demander à l'utilisateur quel mode d'affichage choisir
    int choixMode;
    std::cout << "Choisissez un mode d'affichage :\n";
    std::cout << "1. Mode console\n";
    std::cout << "2. Mode graphique\n";
    std::cout << "Entrez votre choix : ";
    std::cin >> choixMode;

    // Demander le nombre d'itérations maximum
    int nombreIterations = 0;
    std::cout << "Entrez le nombre maximum d'itérations : ";
    std::cin >> nombreIterations;

    if (choixMode == 1) {
        // Mode console
        std::cout << "Mode console sélectionné.\n";
        std::cout << "État initial :\n";
        jeu.afficherGrille(); // Afficher la grille initiale
        jeu.sauvegarderGrille(0); // Sauvegarder la grille initiale

        // Boucle sur les itérations
        for (int iteration = 1; iteration <= nombreIterations; ++iteration) {
            jeu.prochaineIteration(); // Passer à l'itération suivante

            // Vérifier si l'état actuel est identique au précédent
            if (jeu.estIdentiqueALaPrecedente()) {
                std::cout << "Arrêt : la génération actuelle est identique à la précédente à l'itération " << iteration << ".\n";
                break; // Arrêter si les générations sont identiques
            }

            std::cout << "\nGénération " << iteration << " :\n";
            jeu.afficherGrille(); // Afficher la grille à l'itération courante
            jeu.sauvegarderGrille(iteration); // Sauvegarder la grille de l'itération courante
        }
    }
    else if (choixMode == 2) {
        // Mode graphique
        std::cout << "Mode graphique sélectionné.\n";

        // Définir la taille des cellules et les dimensions de la fenêtre
        const int CELL_SIZE = 20; // Taille d'une cellule
        const int WINDOW_WIDTH = grille.getCols() * CELL_SIZE; // Largeur de la fenêtre
        const int WINDOW_HEIGHT = grille.getRows() * CELL_SIZE; // Hauteur de la fenêtre

        // Créer un objet Rendu pour afficher la grille avec SFML
        Rendu* rendu = new Rendu(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);

        // Boucle sur les itérations
        for (int iteration = 1; iteration <= nombreIterations; ++iteration) {
            if (!rendu->estOuverte()) { // Vérifier si la fenêtre est toujours ouverte
                std::cout << "Fenêtre fermée, arrêt de la simulation.\n";
                break; // Arrêter si la fenêtre est fermée
            }

            jeu.prochaineIteration(); // Passer à l'itération suivante

            // Vérifier si l'état actuel est identique au précédent
            if (jeu.estIdentiqueALaPrecedente()) {
                std::cout << "Arrêt : la génération actuelle est identique à la précédente à l'itération " << iteration << ".\n";
                break; // Arrêter si les générations sont identiques
            }

            jeu.sauvegarderGrille(iteration); // Sauvegarder la grille de l'itération courante

            // Dessiner la grille mise à jour
            rendu->dessinerGrille(jeu.getGrid());
            rendu->afficher(); // Afficher la fenêtre

            // Pause entre les itérations (500 ms)
            rendu->attendre(500);
        }

        delete rendu; // Libérer la mémoire après utilisation
    }
    else {
        std::cerr << "Choix invalide. Le programme va s'arrêter.\n";
        return 1; // Sortie avec code d'erreur si le choix est invalide
    }

    return 0; // Fin normale du programme
}
