#ifndef FICHIER_H
#define FICHIER_H

#include <string>
#include <filesystem> // Pour manipuler les fichiers et dossiers

class Fichier {
private:
    std::string dossierSortie; // Le chemin du dossier o� les fichiers de sortie seront enregistr�s

public:
    // Constructeur qui d�finit le dossier de sortie
    explicit Fichier(const std::string& dossier);

    // M�thode pour cr�er le dossier (avec nettoyage s'il existe d�j�)
    void creerDossier();

    // M�thode pour sauvegarder une grille dans un fichier
    void sauvegarderGrille(const std::string& grille, int iteration) const;

    // Accesseur pour obtenir le chemin du dossier de sortie
    std::string getDossierSortie() const;
};

#endif // FICHIER_H
