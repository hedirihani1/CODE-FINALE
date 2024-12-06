#include "Fichier.h"
#include <iostream>
#include <fstream>   // Pour lire/�crire des fichiers
#include <sstream>   // Pour manipuler des cha�nes de caract�res
#include <filesystem> // Pour g�rer les fichiers et r�pertoires

// Constructeur de la classe Fichier, qui initialise le chemin du dossier de sortie
Fichier::Fichier(const std::string& dossier) : dossierSortie(dossier) {}

// Cr�er le dossier de sortie, ou le nettoyer s'il existe d�j�
void Fichier::creerDossier() {
    namespace fs = std::filesystem; // Alias pour simplifier l'utilisation de filesystem

    try {
        if (fs::exists(dossierSortie)) { // V�rifier si le dossier existe d�j�
            // Si le dossier existe, supprimer les fichiers qu'il contient
            for (const auto& entry : fs::directory_iterator(dossierSortie)) {
                fs::remove(entry.path()); // Supprimer chaque fichier du dossier
            }
            std::cout << "Dossier existant '" << dossierSortie << "' nettoy�.\n";
        }
        else {
            // Si le dossier n'existe pas, le cr�er
            fs::create_directories(dossierSortie);
            std::cout << "Dossier '" << dossierSortie << "' cr�� avec succ�s.\n";
        }
    }
    catch (const fs::filesystem_error& e) { // En cas d'erreur lors de la gestion du dossier
        std::cerr << "Erreur lors de la gestion du dossier : " << e.what() << "\n";
    }
}

// Sauvegarder une grille dans un fichier
void Fichier::sauvegarderGrille(const std::string& grille, int iteration) const {
    namespace fs = std::filesystem; // Alias pour simplifier l'utilisation de filesystem

    try {
        // G�n�rer le nom du fichier en fonction de l'it�ration (ex: generation_1.txt)
        std::string filename = dossierSortie + "/generation_" + std::to_string(iteration) + ".txt";

        // Ouvrir le fichier pour �crire la grille
        std::ofstream file(filename);
        if (!file.is_open()) { // Si le fichier n'a pas pu �tre ouvert
            std::cerr << "Erreur : Impossible de cr�er le fichier " << filename << "\n";
            return;
        }

        file << grille; // �crire la grille dans le fichier
        file.close(); // Fermer le fichier
        std::cout << "Grille sauvegard�e dans " << filename << "\n";
    }
    catch (const fs::filesystem_error& e) { // En cas d'erreur lors de la sauvegarde du fichier
        std::cerr << "Erreur lors de la sauvegarde : " << e.what() << "\n";
    }
}

// Retourner le chemin du dossier de sortie
std::string Fichier::getDossierSortie() const {
    return dossierSortie; // Retourner le chemin du dossier de sortie
}
