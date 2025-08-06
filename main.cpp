#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

const vector<string> couleurs = {"rouge", "bleu", "vert", "violet", "jaune", "rose"};
const int LONGUEUR_CODE = 4;
const int nbTentatives = 12;

// Fonction pour comparer deux codes
pair<int, int> comparerCodes(const vector<int>& secret, const vector<int>& proposition) {
    int bonnesPositions = 0;
    int bonnesCouleurs = 0;
    vector<int> secretCopie = secret;
    vector<int> propositionCopie = proposition;

    // Compter les bonnes positions
    for (int i = 0; i < LONGUEUR_CODE; ++i) {
        if (proposition[i] == secret[i]) {
            bonnesPositions++;
            secretCopie[i] = -1; // Marquer comme trouvé
            propositionCopie[i] = -2; // Marquer comme trouvé
        }
    }

    // Compter les bonnes couleurs aux mauvaises positions
    for (int i = 0; i < LONGUEUR_CODE; ++i) {
        if (propositionCopie[i] != -2) { // Si pas trouvé
            for (int j = 0; j < LONGUEUR_CODE; ++j) {
                if (propositionCopie[i] == secretCopie[j]) {
                    bonnesCouleurs++;
                    secretCopie[j] = -1; // Marquer comme trouvé
                    break;
                }
            }
        }
    }

    return {bonnesPositions, bonnesCouleurs};
}

// Fonction pour afficher les couleurs
void afficherCouleurs() {
    cout << "Couleurs disponibles : ";
    for (const auto& couleur : couleurs) {
        cout << couleur << " ";
    }
    cout << endl;
}

// Fontion pour modeSoloGenerer, génère toutes les combinaisons possibles en prenant en compte les issues des essais précédents
void genererLesCombinaisons(vector<vector<int>>& possibilites, vector<int>& enCours, int profondeur) {
    if (profondeur == LONGUEUR_CODE) {
        possibilites.push_back(enCours);
        return;
    }
    for (int i = 0; i < couleurs.size(); ++i) {
        enCours.push_back(i);
        genererLesCombinaisons(possibilites, enCours, profondeur + 1);
        enCours.pop_back();
    }
}

//Fonction permettant d'afficher la combinaison demandée
void afficherCombinaison(const vector<int>& combinaison) {
    for (int color : combinaison) {
        cout << couleurs[color] << " ";
    }
    cout << endl;
}


// Fonction pour le mode 2 joueurs
void modeDeuxJoueurs() {
    vector<int> secret(LONGUEUR_CODE);
    afficherCouleurs();
    cout << "Joueur 1, entrez votre combinaison (4 couleurs parmi les 6 disponibles) :\n";

    for (int i = 0; i < LONGUEUR_CODE; ++i) {
        string couleur;
        cin >> couleur;
        auto it = find(couleurs.begin(), couleurs.end(), couleur);
        if (it != couleurs.end()) {
            secret[i] = distance(couleurs.begin(), it);
        } else {
            cout << "Couleur invalide, essayez encore.\n";
            --i; // Réessayer pour la même position
        }
    }

    for (int i = 0; i < 50; ++i){
        cout<<endl;
    }

    cout<<"Pour rappel, ";
    afficherCouleurs();
    cout << "Joueur 2, trouvez la combinaison en 12 essais maximum.\n";
    cout<<endl;
    for (int essai = 1; essai <= nbTentatives; ++essai) {
        vector<int> proposition(LONGUEUR_CODE);
        cout << "Essai " << essai << " : ";
        for (int i = 0; i < LONGUEUR_CODE; ++i) {
            string couleur;
            cin >> couleur;
            auto it = find(couleurs.begin(), couleurs.end(), couleur);
            if (it != couleurs.end()) {
                proposition[i] = distance(couleurs.begin(), it);
            }
            else {
                cout << "Couleur invalide, essayez encore.\n";
                --i; // Réessayer pour la même position
            cout<<endl;
            }
        }
        auto result = comparerCodes(secret, proposition);
        cout << "Couleurs bien placées : " << result.first << ", Couleurs correctes : " << result.second << endl;

        if (result.first == LONGUEUR_CODE) {
            cout<<endl;
            cout << "Félicitations, Joueur 2, vous avez trouvé la combinaison !\n";
            cout<<endl;
            return;
        }
        cout<<endl;
    }
    cout << "Désolé, Joueur 2, vous avez épuisé vos essais. La combinaison était : ";
    afficherCombinaison(secret);
    cout << endl;
    cout<<endl;
}

// Fonction pour le mode solo (le programme génère la combinaison)
void modeSoloGenerer() {
    vector<int> secret(LONGUEUR_CODE);
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < LONGUEUR_CODE; ++i) {
        secret[i] = rand() % couleurs.size();
    }
    afficherCouleurs();
    cout << "Trouvez la combinaison en 12 essais maximum.\n";
    cout<<endl;
    for (int essai = 1; essai <= nbTentatives; ++essai) {
        vector<int> proposition(LONGUEUR_CODE);
        cout << "Essai " << essai << " : ";
        for (int i = 0; i < LONGUEUR_CODE; ++i) {
            string couleur;
            cin >> couleur;
            auto it = find(couleurs.begin(), couleurs.end(), couleur);
            if (it != couleurs.end()) {
                proposition[i] = distance(couleurs.begin(), it);
            } else {
                cout << "Couleur invalide, essayez encore.\n";
                --i; // Réessayer pour la même position
            }
        }


        auto result = comparerCodes(secret, proposition);
        cout << "Couleurs bien placées : " << result.first << ", Couleurs correctes : " << result.second << endl;

        if (result.first == LONGUEUR_CODE) {
            cout<<endl;
            cout << "Félicitations, vous avez trouvé la combinaison !\n";
            return;
        }
        cout<<endl;
        cout<<endl;
    }
    cout << "Désolé, vous avez épuisé vos essais. La combinaison était : ";
    afficherCombinaison(secret);

    cout <<endl;
    cout << endl;
}






// Fonction pour le mode solo (le joueur donne la combinaison, le programme essaie de deviner)
void modeSoloDeviner() {
    vector<int> secret(LONGUEUR_CODE);
    afficherCouleurs();
    cout << "Joueur, entrez votre combinaison (4 couleurs parmi les 6 disponibles) :\n";


    for (int i = 0; i < LONGUEUR_CODE; ++i) {
        string couleur;
        cin >> couleur;
        auto it = find(couleurs.begin(), couleurs.end(), couleur);
        if (it != couleurs.end()) {
            secret[i] = distance(couleurs.begin(), it);
        } else {
            cout << "Couleur invalide, essayez encore.\n";
            --i; // Réessayer pour la même position
        }
    }

    vector<vector<int>> possibilites;
    vector<int> enCours;
    genererLesCombinaisons(possibilites, enCours, 0);
    vector<int> proposition = {0, 0, 1, 1}; // Hypothèse initiale (rouge, rouge, bleu, bleu)
    int essais = 0;


    cout<<endl;
    cout << "Le programme va tenter de deviner votre combinaison en 12 essais maximum."<<endl;
    cout<<endl;


    while (essais < nbTentatives) {
        essais++;

        // Comparer la proposition avec le secret
        auto [bonnesPositions, bonnesCouleurs] = comparerCodes(secret, proposition);

        // Afficher l'essai
        cout << "Essai " << essais << ": ";
        afficherCombinaison(proposition);
        cout << "Couleurs bien placées : " << bonnesPositions << ", Couleurs correctes : " << bonnesCouleurs << endl;
        cout <<endl;

        if (bonnesPositions == LONGUEUR_CODE) {
            cout << "\nLe programme a trouvé la combinaison en " << essais << " essais !\n";
            cout<<endl;
            return;
        }

        // Réduire les possibilités
        vector<vector<int>> nouvellesPossibilites;
        for (const auto& possibilite : possibilites) {
            auto [p, c] = comparerCodes(proposition, possibilite);
            if (p == bonnesPositions && c == bonnesCouleurs) {
                nouvellesPossibilites.push_back(possibilite);
            }
        }
        possibilites = nouvellesPossibilites;

        // Choisir la prochaine hypothèse (simplement la première possibilité restante)
        if (!possibilites.empty()) {
            proposition = possibilites[0];
        } else {
            cout << "Erreur : Plus de possibilités, solution non trouvée.\n";
            break;
        }
    }

    cout << "Le programme n'a pas trouvé la combinaison dans les essais. La combinaison était : ";
    afficherCombinaison(secret);
    cout << endl;
    cout<<endl;
}


// Fonction principale pour exécuter le jeu
int main() {
    system ("chcp 1252");
    srand(static_cast<unsigned int>(time(0)));
    int choix;

    do {
        cout << "Choisissez un mode de jeu:\n";
        cout << "1. Règles du jeu\n";
        cout << "2. Mode 2 joueurs\n";
        cout << "3. Mode solo (vous devinez)\n";
        cout << "4. Mode solo (programme devine)\n";
        cout << "5. Quitter\n";
        cin >> choix;

        switch (choix) {
            case 1:
                cout << "Le jeu de base se joue a deux, le premier joueur choisit une combinaison de 4 billes de couleurs ordonnées.\n";
                cout << "Il y a 6 couleurs possibles, la combinaison peut contenir plusieurs fois une même couleur.\n";
                cout << "Cette combinaison est cachée au second joueur, dont l’objectif est de la retrouver. A chaque tour, le second joueur propose une combinaison de 4 billes. \n";
                cout << "Le premier lui donne le nombre de billes de la bonne couleur à la bonne place et le nombre de bille de la bonne couleur à la mauvaise place. \n";
                cout << "Le second joueur a 12 tours pour retrouver, par déduction, la combinaison. \n";
                cout << "Ici le programme se charge de donner les couleurs bien placées ou non, c'est pourquoi le jeu programme n'impose pas d'être en duo pour s'amuser. \n";
                cout << "Il y a 3 modes différents, un mode 2 joueurs avec le même principe que celui expliqué précédemment, seule différence le joueur 1 n'a pas besoin de dire le nombre de couleur correcte. \n";
                cout << "Il existe aussi deux modes solo, un où le programme génère la combinaison et le joueur doit la trouver. \n";
                cout << "Et un où le joueur indique la combinaison à trouver et le programme suit la méthode de David Knuth pour résoudre le problème. \n";
                cout << endl;
                cout << endl; break;
            case 2: modeDeuxJoueurs(); break;
            case 3: modeSoloGenerer(); break;
            case 4: modeSoloDeviner(); break;
            case 5: cout << "Au revoir!\n"; break;
            default: cout << "Choix invalide. Veuillez réessayer.\n"; break;
        }
    } while (choix != 5);

    return 0;
    }