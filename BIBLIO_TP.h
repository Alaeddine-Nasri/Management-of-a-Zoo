#ifndef BIBLIO_TP_H_INCLUDED
#define BIBLIO_TP_H_INCLUDED

typedef struct chaine chaine;
struct chaine
 {
     char  mots[100];
 };
/********************STRUCTURE DE DONNEES********************/
/*STRUCTURE ENCLOS*/
/*On definis la structure de donnee suivante qui decris un enclos.
Un enclos est caracterise par: son nom(qui est unique), son type(cage, aquarium,insectarium, voiliere), la longueur et sa largeur,
le nom d'animaux max qu'il peut contenir, et le poids max qu'il peut supporter*/


typedef struct enclos
{
    char nom_enclos[30];
    char type[30];
    float longueur;
    float largeur;
    int nombre_animaux_max;
    float poids_max;
    int libre;
}enclos;

typedef struct l_enclos
{
    enclos idt;
    struct l_enclos *adr;
}l_enclos;
/*STRUCTURE ENCLOS*/

/*STRUCTURE ANIMAL*/
/*On definis la structure de donnee suivante qui decris un animal.
Un enclos est caracterise par: son nom(qui est unique),sa race, son espece son regime,son pays d'origine
l'enclos au quel il est affecte(par defaut on lui attribue la notion "non affecte"), son poids, sa date de naissance et sa date d'entre au Zoo*/
typedef struct animal{
    char nom[50];
    char race[50];
    char espece[50];
    char regime[50];
    char pays[50];
    char enclos[50];
    int poids;
    int date_naiss;
    int date_entr;

    }animal;
typedef struct l_animals
{
    animal idt;
    struct l_animals* adr;
}l_animals;
/*STRUCTURE ANIMAL*/

/*STRUCTURE ANIMAUX DANGEREUX*/
/*Cette liste contient des animaux consideres comme dangereux
Utilite: cette liste nous permet d'effectuer les test lors de l'affectation.
(Rappel : Un animal dangereux dois etre seul dans un enclos)*/
typedef struct dangereux
{
  char race[50];

}dangereux;
typedef struct l_dangereux
{
  dangereux idt;
  struct l_dangereux *adr;
}l_dangereux;
/*STRUCTURE ANIMAUX DANGEREUX*/

/*STRUCTURE DES AFFECTATIONS*/
/*On definis la structure de donnee suivante qui definis les affectations.
cette structure est definis par le nom de l'animal, l'enclos au quel il est affecte, la date de l'affectation, et la date de depart du Zoo
->Par defaut: si l'animal est toujours dans l'enclos la date de part =0*/
typedef struct affect_depart
{
    char nom_animal[50];
    char nom_enclos[50];
    int date_affectation;
    int date_depart;

}affect_depart;

typedef struct l_affect_depart
{
    affect_depart idt;
    struct l_affect_depart *adr;
}l_affect_depart;
/**STRUCTURE DES PAYS**/

typedef struct l_pays
{
    char org[30];
    struct l_pays* adr;
}l_pays;
/*STRUCTURE DES AFFECTATIONS*/
/********************STRUCTURE DE DONNEES********************/

/********************MACHINES ABSTRAITES********************/

/**********MACHINE ABSTRAITE "ENCLOS"**********/

void allouer_enclos(l_enclos **P);
void *liberer_enclos(l_enclos *P);
void aff_adr_enclos(l_enclos *P, l_enclos *Q);
l_enclos* suivant_enclos(l_enclos *P);
enclos valeur(l_enclos *P);

/**********MACHINE ABSTRAITE "ENCLOS"**********/

/**********MACHINE ABSTRAITE "ANIMAL"**********/

void allouer(l_animals * *p);
void liberer(l_animals* p);
void aff_adr(l_animals* p,l_animals* q);
void aff_val_animal(l_animals* p, animal v);
l_animals* asuivant(l_animals* p);
animal avaleur(l_animals* p);

/**********MACHINE ABSTRAITE "ANIMAL"**********/

/**********MACHINE ABSTRAITE "DANGEREUX"**********/

void allouer_dangereux(l_dangereux **P);
void liberer_dangereux(l_dangereux *P);
void aff_adr_dangereux(l_dangereux *P, l_dangereux *Q);
l_dangereux* dangereux_suivant(l_dangereux *P);

/**********MACHINE ABSTRAITE "DANGEREUX"**********/

/**********MACHINE ABSTRAITE "AFFECTATION"**********/

void allouer_affect_depart(l_affect_depart **P);
void liberer_affect_depart(l_affect_depart *P);
void aff_adr_affect_depart(l_affect_depart *P, l_affect_depart *Q);
l_affect_depart* aff_suivant(l_affect_depart *P);
affect_depart aff_valeur(l_affect_depart *P);

//En plus des modules usuelles on aura besoin de recuprer le dernier element des listes utilise à travers ces deux MODULES
l_animals *queue(l_animals* p);
l_enclos queue_enclos(l_enclos *P);

/**********MACHINE ABSTRAITE "AFFECTATION"**********/

/*******************MACHINES ABSTRAITES*********************/

/*******************MODULES DE GESTION*********************/

/**         MODULES DE MISE A JOUR              **/

/*Role: avoir une mise a jour sur l'etat de l'enclos actuel: poids qui contient, nombre d'animaux actuel
Utilite: Permet d'effectuer les differents test lors des affectations et des suppressions*/

int nbr_actu_animaux(l_enclos *P);         /*Renvoie le nombre d'animaux actuel dans l'enclos pointe par P*/
int etat_enclos(l_enclos *P);              /*Renvoie "1" si l'enclos pointe par P est libre sinon, renvoie "0"*/
int animal_dangereux(l_animals *P);         /*Renvoie "1", si l'animal pointe par P est dangereux, sinon renvoie "0"*/
void race(l_enclos *P ,char *result[]);    /*Result est la race des animaux que contient l'enclos pointe par P*/
int poids_actuel(l_enclos *P);           /*Renvoie le poids actuel dans l'enclos pointe par P  <= somme des poids des animaux dans l'enclos>*/

void MAJ_animal_fichier( l_animals *Atete);  /*Met a jour le contenue du fichier des animaux "animaux.txt"*/
void MAJ_enclos_fichier(l_enclos *Etete);   /*Met a jour le contenue du fichier des enclos "enclos.txt"*/

int date();                                 /*Renvoie la date actuelle*/

/**         MODULES D'INITIALISATION            **/
//Ces modules permettent d'initialiser les champs des enregistrements de chaque structure

void int_enclos(l_enclos *P, char nom[], char type[], float longueur, float largeur, int nbr_animaux_max, float poids_max,int *e_enclos );
void aff_char_animal(l_animals *p,char nom[], char race[],char espece[],char regime[], char pays[],char enclos[],int date_naiss, int date_entr, int poids);
void int_affect(l_affect_depart *P, char animal[], char enclos[],int d_affect, int d_depart);

/**         MODULES DE CREATION DES LLC         **/
void  cree_llc_ani(l_animals* *t); //Creation liste des animaux
void *cree_llc_dangereux(l_dangereux **tete); //creation liste des animaux dangereux
void *cree_llc_enclos (l_enclos **tete); //creation liste des enclos
void *creation_affectation(l_affect_depart **tete); //creation liste des affectations/departs

/**              MODULES D'AFFICHAGE LLC        **/
void *affichage_enclos(l_enclos *P); //Affichage liste des enclos
void *affichage_animal(l_animals *P); //Affichage liste des animaux
void affichage_dangereux(l_dangereux *P); //Affichage liste des animaux dangereux
void affichage_affectation(l_affect_depart *AFF); //Affichage liste des affectations et départs
/**             MODULES D'ADDITION           **/
void ajouter_enclos(l_enclos **tete, int nbr_enclos); //Ajouter un nouvel enclos
void ajouter_dangereux(l_dangereux **tete, int nbr_animaux); //Ajouter une nouvelle race d'animal dangereux
void ajouter_animal(l_animals **Atete); //Ajouter un nouvel animal
void enclos_mm_pays(l_animals *Atete);

/**             MODULES D'ACCES             **/
void Acces_enclos(l_enclos *tete,char nom[20], l_enclos **adr_enclos, l_enclos **prec_enclos);
void Acces_animal(l_animals *tete,char nom[20], l_animals **adr_animal, l_animals **prec_animal);

/**             MODULES DE SUPPRESSION      **/
//La suppression s'effectue sur deux niveaux: en memoire et du fichier de lecture!
void supprimer_animal_fichier(char animal[20]);
void supprimer_enclos_fichier(char nom_enclos[]);

void supprimer_animal(l_animals **tete,l_affect_depart **AFF);
void supprimer_enclos(l_enclos **tete);
void ajouter_date_depart_fichier(l_affect_depart *AFF);

/**             MODULES DE RECHERCHE        **/
void chercher_animal(int type);
void une_annee(l_animals *p,l_affect_depart *AFF);
/**             MODULES DE DEPLACEMENT      **/
void deplacer(char n[30]);//pour les fichiers
void anim_pays(l_animals* *p, l_animals* *o);
void deplacer_animal(l_animals **tete);
/**             MODULE D'AFFECTATION        **/
//Role: affecter un animal a un enclos
void affectation(l_enclos **Etete, l_animals **Atete,l_affect_depart *Ftete, char enclos[], char animal[]);
void tri_enclos(l_enclos **Etete, l_enclos **L1, l_enclos **L2, l_enclos **L3, l_enclos **L4);
void swap(l_enclos *p, l_enclos *q);
void tri_poids(l_enclos *Etete);

//void  basemenu(void);


/**             MODULE DE CLASSIFICATION    **/



/******************AFFICHAGE GRAPHIQUE*********************/
void menu(chaine *lechoix,l_animals *p,l_enclos *q,l_affect_depart *AFF, l_dangereux *D);
void intro(void);
void fin(void);
int choix (chaine *lechoix);
/******************AFFICHAGE GRAPHIQUE*********************/
/*******************MODULES DE GESTION*********************/

#endif // BIBLIO_TP_H_INCLUDED


