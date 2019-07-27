#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BIBLIO_TP.h"
#include <windows.h>

/********************MACHINES ABSTRAITES********************/

/**     MACHINE ABSTRAITE "ENCLOS"      **/
void allouer_enclos(l_enclos **P)
{
    *P= (l_enclos*) malloc(sizeof(l_enclos));
}
void *liberer_enclos(l_enclos *P)
{
    free(P);
}
void aff_adr_enclos(l_enclos *P, l_enclos *Q)
{
    P->adr=Q;
}
l_enclos* suivant_enclos(l_enclos *P)
{
    return P->adr;
}
enclos valeur(l_enclos *P)
{
    return P->idt;
}

/**     MACHINE ABSTRAITE "ANIMAL"       **/
void allouer(l_animals * *p)
    {
        *p = (l_animals*)(malloc(sizeof(l_animals)));
    }
void liberer(l_animals* p)
        {
          free(p);
        }
void aff_adr(l_animals* p,l_animals* q){
    p->adr = q ;
    }
void aff_val(l_animals* p, animal v){
    p->idt = v;
    }
l_animals* asuivant(l_animals* p){
        return p->adr;
    }
animal avaleur(l_animals* p){
        return p->idt;
    }
/**     MACHINE ABSTRAITE "DANGEREUX"        **/
void allouer_dangereux(l_dangereux **P)
{
    *P= (l_dangereux*) malloc(sizeof(l_dangereux));
}
void liberer_dangereux(l_dangereux *P)
{
    free(P);
}
void aff_adr_dangereux(l_dangereux *P, l_dangereux *Q)
{
    P->adr=Q;
}
l_dangereux* dangereux_suivant(l_dangereux *P)
{
    return P->adr;
}

/**     MACHINE ABSTRAITE "AFFECTATION"      **/
void allouer_affect_depart(l_affect_depart **P)
{
    *P= (l_affect_depart*) malloc(sizeof(l_affect_depart));
}
void liberer_affect_depart(l_affect_depart *P)
{
    free(P);
}
void aff_adr_affect_depart(l_affect_depart *P, l_affect_depart *Q)
{
    P->adr=Q;
}

l_affect_depart* aff_suivant(l_affect_depart *P)
{
    return P->adr;
}
affect_depart aff_valeur(l_affect_depart *P)
{
    return P->idt;
}

/**     MACHINE ABSTRAITE "PAYS"      **/
void pallouer(l_pays * *p)
    {
        *p = (l_pays*)(malloc(sizeof(l_pays)));
    }
void pliberer(l_pays* p)
        {
          free(p);
        }
void paff_val(l_pays* p, char v[])
{
  strcpy(p->org,v);
}
void paff_adr(l_pays* p,l_pays* q){
 p->adr = q;
 }
l_pays* psuivant(l_pays* p)
{
      return p->adr;
}
char pvaleur(l_pays* p)
{
        return p->org;
}
/********************MACHINES ABSTRAITES********************/

/*******************MODULES DE GESTION*********************/

/**         MODULES DE MISE A JOUR              **/

/** NBR ACTU ANIMAUX **/
int nbr_actu_animaux(l_enclos *P)
{
    int nbr_actu=0;
    char nom[20]; char nom_enclos[20], pays[20], regime[20], race[20], espece[20];
    int date_naiss,date_entr;
    int poids;
    //la recherche se fait dans le fichier des affectations
    //On test si l'animal est encore dans l'enclos
    FILE *fic;
    fic=fopen("animaux.txt","r");
    if (fic!=NULL){
    while (!feof(fic)) {

      //A revoir pour ne lire que l'enclos
     fscanf(fic,"%s %s %s %s %s %s %d %d %d\n",nom,race,espece,regime,pays,nom_enclos,&date_naiss,&date_entr,&poids);
      if(strcmp(nom_enclos, P->idt.nom_enclos)==0){nbr_actu +=1;}
    }
  }
  fclose(fic);
  return nbr_actu;
}
int poids_actuel(l_enclos *P)
{
  int actu=0;
  char nom[20], race[20], espece[20], regime[20], pays[20], nom_enclos[20];
  int date_naiss,date_entr;
  int poids;
  FILE *fic;
  fic=fopen("animaux.txt","r");
  if (fic != NULL){
    while (!feof(fic)) {
      fscanf(fic,"%s %s %s %s %s %s %d %d %d\n", nom, race, espece, regime, pays , nom_enclos,& date_naiss,& date_entr,&poids);
      if (strcmp(nom_enclos, P->idt.nom_enclos)==0){actu+=poids;}
    }
      fclose(fic);

  }
  else {printf("Erreur\n");}

  return actu;
}
/** POIDS ACTUEL**/
/*-utilite de la fonction:
Permet d'effectuer les tests lors de l'affectation pour ne pas depasser le poids max qu'un enclos peut supporter*/


/**ETAT ENCLOS**/
int etat_enclos(l_enclos *P)
/*-principe de la fonction:
renvoie 1 si l'enclos est libre (i.e: nombre_animaux_actuel=0), sinon elle renvoie zero
-Utilite: lors de la suppression d'un enclos*/
{ int etat=1;
  if (nbr_actu_animaux(P)!=0){etat=0;}
  return etat;
}
/**DANGEREUX**/
/*Principe de la fonction:
retourne 1 si l'animal est dangereux */
int animal_dangereux(l_animals *P)
{
  FILE *fic=fopen("dangereux.txt","r");
  int trouv=0; char race[20];
  while((!feof(fic)) && trouv==0){
    fscanf(fic,"%s\n", race);
    if (strcmp(race, P->idt.race)==0){ trouv=1; printf("Cet animal est dangereux\n");}
  }
  return trouv;
}
/**RACE**/
/*Principe : retourne la race des animaux de n'enclos*/

void race(l_enclos *P ,char *result[])
{
    char nom[20]; char nom_enclos[20], pays[20], regime[20], race[20], espece[20];
    int date_naiss,date_entr;
    int poids;

  FILE *fic;
  fic=fopen("animaux.txt","r"); int trouv=0;
  while((!feof(fic)) && (trouv==0)){
    fscanf(fic,"%s %s %s %s %s %s %d %d %d\n",nom,race,espece,regime,pays,nom_enclos,&date_naiss,&date_entr,&poids);
      if(strcmp(nom_enclos, P->idt.nom_enclos)==0){trouv=1; strcpy(result,race);}
 }
 fclose(fic);
}
/**QUEUE**/
l_animals* queue(l_animals* p)
{
    l_animals* q=p;
    if (q != NULL)
    {
    while (asuivant(q) != NULL)
    {
        q=asuivant(q);
    }
    }
    return q;
}

l_enclos queue_enclos(l_enclos *P)
{
   l_enclos *Q=P;
    l_enclos *D;

    while (suivant_enclos(Q) != NULL)
    {   printf("in while\n");
        D=Q;
        Q=suivant_enclos(Q);
        printf("end while\n");
    }
printf("end of function");
return *D;
}

l_pays* pqueue(l_pays* p)
{
    l_pays* q=p;
    l_pays *D;
    if (q != NULL)
    {
    while (psuivant(q) != NULL)
    {   D=q;
        q=psuivant(q);
    }
    }
    return D;
}
/**         MODULES DE MISE A JOUR              **/

/**         MODULES D'INITIALISATION            **/

/**INITIALISATION ENCLOS**/
void int_enclos(l_enclos *P, char nom[], char type[], float longueur, float largeur, int nbr_animaux_max, float poids_max,int *e_enclos )
{
    strcpy(P->idt.nom_enclos,nom);
    strcpy(P->idt.type,type);
    P->idt.longueur= longueur;
    P->idt.largeur= largeur;
    P->idt.nombre_animaux_max= nbr_animaux_max;
    P->idt.poids_max= poids_max;
    P->idt.libre=etat_enclos(P);
    *e_enclos=etat_enclos(P);
}

/**INITIALISATION ANIMAL**/
void aff_char_animal(l_animals *p,char nom[], char race[],char espece[],char regime[], char pays[],char enclos[],int date_naiss, int date_entr, int poids)
{
    fflush(stdin);
    strcpy(p->idt.nom ,nom);
    strcpy(p->idt.race ,race);
    strcpy(p->idt.espece ,espece);
    strcpy(p->idt.regime ,regime);
    strcpy(p->idt.pays ,pays);
    strcpy(p->idt.enclos,enclos);
    p->idt.date_entr=date_entr;
    p->idt.date_naiss=date_naiss;
    p->idt.poids = poids;
    fflush(stdin);
}

/**INITIALISATION AFFECTATION**/
void int_affect(l_affect_depart *P, char animal[], char enclos[],int d_affect, int d_depart)
{
    strcpy(P->idt.nom_animal, animal);
    strcpy(P->idt.nom_enclos, enclos);
    P->idt.date_affectation=d_affect;
    P->idt.date_depart=d_depart;
}
/**         MODULES D'INITIALISATION            **/


/**         MODULES DE CREATION DES LLC         **/

/**LISTE DES ANIMAUX**/
void    cree_llc_ani(l_animals* *t)
{
    l_animals* p, *q; char nom[20],pays[20],race[20],espece[20],regime[20],enclos[20];
    int date_naiss,date_entr;
    int poids;
    FILE *fic =fopen("animaux.txt","r");
    printf("test");
    allouer(&p);
    *t = p ;
    fscanf(fic,"%s %s %s %s %s %s %d %d %d\n",nom,race,espece,regime,pays,enclos,&date_naiss,&date_entr,&poids);
    aff_char_animal(p,nom,race,espece,regime,pays,enclos,date_naiss,date_entr,poids);
    //printf("test %s %s %s %s %s %s %d %d %d\n",p->idt.nom,p->idt.race,p->idt.espece,p->idt.regime,p->idt.pays,p->idt.enclos,p->idt.date_entr,p->idt.date_naiss,p->idt.poids);
        fflush(stdin);
     while(!feof(fic))
        {
        fflush(stdin);
        allouer(&q);

        aff_adr(p,q);
        p=q;
        fscanf(fic,"%s %s %s %s %s %s %d %d %d\n",nom,race,espece,regime,pays,enclos,&date_naiss,&date_entr,&poids);
                aff_char_animal(p,nom,race,espece,regime,pays,enclos,date_naiss,date_entr,poids);

        fflush(stdin);
        }
        aff_adr(p,NULL);
        fclose(fic); //Fermeture du fichier
        printf("creation reussie\n");

}
/**LISTE DES ENCLOS**/
void *cree_llc_enclos (l_enclos **tete)
{
    /*VARIABLES*/
    l_enclos *Q , *P;
    char nom[30]; char type[30];
    float longueur, largeur, poids_max;
    int nbr_animaux_max;
    int etat_enclos=0;

    //Creation premier enclos
    allouer_enclos(tete);
    P=*tete;
    FILE *fic=fopen("enclos.txt","r"); //Ouverture du fichier
    fscanf(fic, "%s %s %f %f %d %f %d\n",nom, type, &longueur,&largeur,&nbr_animaux_max,&poids_max,&etat_enclos );
    int_enclos(P,nom,type,longueur,largeur,nbr_animaux_max,poids_max,&etat_enclos );

    while(!feof(fic))
    {
        allouer_enclos(&Q);
        aff_adr_enclos(P,Q);
        P=Q;
        fscanf(fic, "%s %s %f %f %d %f %d\n",nom, type, &longueur,&largeur,&nbr_animaux_max,&poids_max,&etat_enclos );
        int_enclos(P,nom,type,longueur,largeur,nbr_animaux_max,poids_max,&etat_enclos );

    }
    aff_adr_enclos(P,NULL);
    //printf("nooooooooooooooooooooooooo\n");
    //printf("mouna : %s    %s\n",P->idt.nom_enclos,P->idt.type);
    // *tete = P;
          fclose(fic); //Fermeture du fichier

     printf("creation liste des enclos reussie\n");
}
/**LISTE DES ANIMAUX DANGEREUX**/
void *cree_llc_dangereux(l_dangereux **tete)
{
    /*VARIABLES*/
    l_dangereux *P, *Q;
    char race[30];
    allouer_dangereux(&P);
    *tete=P;
    FILE *fic=fopen("dangereux.txt","r");
    if (fic !=NULL) {
    fscanf(fic,"%s\n",race);
    strcpy(P->idt.race, race);
    while(!feof(fic)){
        allouer_dangereux(&Q);
        aff_adr_dangereux(P,Q);
        P=Q;
        fscanf(fic,"%s\n", race);
        strcpy(P->idt.race,race);
    }
    aff_adr_dangereux(P,NULL);
    }
    else {printf("Erreur impossible d'ouvrir le fichier");}
    fclose(fic);
    printf("Creation liste des animaux dangereux reussie!\n");
}

/**LISTE DES AFFECTATIONS**/
void *creation_affectation(l_affect_depart **tete)
{
    l_affect_depart *F, *P;
    char animal[30];
    char enclos[30];
    int date_aff;
    int date_depart;
    allouer_affect_depart(&F);
    *tete=F;
    FILE *fic=fopen("affectation.txt","r");
    if (fic !=NULL){
        fscanf(fic, "%s %s %d %d\n",animal, enclos, &date_aff,& date_depart);
        int_affect(F,animal,enclos,date_aff,date_depart);
        while(!feof(fic)){
            allouer_affect_depart(&P);
            aff_adr_affect_depart(F,P);
            F=P;
            fscanf(fic,"%s %s %d %d\n", animal,enclos,&date_aff,&date_depart);
            int_affect(F,animal,enclos,date_aff,date_depart);
        }
        aff_adr_affect_depart(F,NULL);
    }
    else {printf("Erreur\n");}
    fclose(fic);
}
/**LISTE DES PAYS**/
void    cree_llc_pays(l_pays* *t,char pays[])
{
    l_pays* p;
    pallouer(&p);
    *t = p;
    strcpy(p->org,pays);
    paff_adr(p,NULL);
}
/**         MODULES DE CREATION DES LLC         **/

/**              MODULES D'AFFICHAGE LLC        **/

/**AFFICHAGE ENCLOS**/
void *affichage_enclos(l_enclos *P)
{
    int k=0;
    char c[10];
    strcpy(c,"oui");
    printf("NOM     |TYPE       |LONGUEUR     |LARGEUR      |NBR ANIMAUX       |POIDS MAX      |ETAT\n");
    while(P!=NULL) {
            if(k<35){
    printf("%s %10s %20f %15f %10d %15f %12d\n",P->idt.nom_enclos, P->idt.type, P->idt.longueur, P->idt.largeur, P->idt.nombre_animaux_max,P->idt.poids_max, P->idt.libre);
    k++;
        }
        else{
        printf("voulez vous continuer oui ou non ??\n");
        scanf("%s",c);
        if(strcmp(c,"oui")==0){ system("cls");k=0;
        printf("NOM     |TYPE       |LONGUEUR     |LARGEUR      |NBR ANIMAUX       |POIDS MAX      |ETAT\n");
        textbackground(2);
        }
        else break;
    }
    P=suivant_enclos(P);
}
}
/**AFFICHAGE ANIMAUX**/
void *affichage_animal(l_animals *p)
{   int k=0;
    char c[10];
    strcpy(c,"oui");
    printf("NOM   |RACE     |ESPECE     |Regime      |PAYS     |ENCLOS    |DATE DE NAISSANCE     |DATE D'ENTR      |POIDS\n");
    while (p!=NULL && (strcmp(c,"oui")==0)){
        if(k<35){
        printf("%s    %9s %9s %9s %9s %9s %15d %15d %10d\n",p->idt.nom,p->idt.race,p->idt.espece,p->idt.regime,p->idt.pays,p->idt.enclos,p->idt.date_naiss ,p->idt.date_entr,p->idt.poids);
        k++;
        }
        else{
        printf("voulez vous continuer oui ou non ??\n");
        scanf("%s",c);
        if(strcmp(c,"oui")==0){ textbackground(0);system("cls");textbackground(2);k=0;
        printf("NOM   |RACE     |ESPECE     |Regime      |PAYS     |ENCLOS    |DATE DE NAISSANCE     |DATE D'ENTR      |POIDS\n");
        textbackground(2);
        }
        else break;
        }
        p=asuivant(p);
    }
}

/**AFFICHAGE DANGREUX**/
void affichage_dangereux(l_dangereux *p)
{
    printf("RACE\n");
    while (p!=NULL){
        printf("%9s|\n", p->idt.race);
        p=dangereux_suivant(p);
    }
}
/** AFFICHAGE Affectation **/
void affichage_affectation(l_affect_depart *AFF){
    int k=0;
    char c[10];
    strcpy(c,"oui");
    printf("Nom d'animal|      |Nom d'enclos|    |date affectation|   |date depart\n");
    while(AFF != NULL)
    {
        if(k<35){
        printf("\n%7s %7s %20d/%d/%d %20d/%d/%d\n",AFF->idt.nom_animal,AFF->idt.nom_enclos,((AFF->idt.date_affectation)/1000000),((AFF->idt.date_affectation)/10000)%100,(AFF->idt.date_affectation)%10000,((AFF->idt.date_depart)/1000000),((AFF->idt.date_depart)/10000)%100,(AFF->idt.date_depart)%10000);
        k++;
        }
        else{
        printf("voulez vous continuer oui ou non ??\n");
        scanf("%s",c);
        if(strcmp(c,"oui")==0){ system("cls");k=0;
        printf("Nom d'animal|      |Nom d'enclos|    |date affectation|   |date depart\n");
        textbackground(2);
        }
        else break;
        }
        AFF = aff_suivant(AFF);
    }
}

/**              MODULES D'AFFICHAGE LLC        **/

/**             MODULES D'ADDITION           **/
/**AJOUTER ANIMAL**/
void ajouter_animal(l_animals **Atete)
{
  /*VARIABLES*/
    int sel=0;
    char nom[20], race[20] ,regime[20] ,espece[20] ,pays[20] , enclos[20];
    int poids=0;
    int date_entr=0, date_naiss=0;
    l_animals *A=NULL, *PA=NULL;
    l_animals *P, *Q=NULL;
    FILE *fichi;
  /*Traitement*/
    Q=queue(Atete);
    printf("->Nom de l'animal\n");
    scanf("%s", nom);
    Acces_animal(Atete, nom,&A,&PA);
    if(A==NULL){
        allouer(&P);
        printf("\n->Race:  ");
        scanf("%s", race);
        printf("\n->Espece:  ");
        scanf("%s",espece);
        printf("\n->Regime alimentaire : ");
        scanf("%s",regime);
        printf("\n->Pays d'origine: ");
        scanf("%s",pays);
        printf("\nl'animal n'est pas encore affecte a un enclos!");
        strcpy(enclos,"non-affecte");
        printf("\n->poids = ");
        scanf("%d",&poids);
        printf("\n->date de naissance: \n<Veuillez introduire la date: jj/mm/aa, ne laissez pas d'espace S.V.P> \n");
        scanf("%d",&date_naiss);
        printf("->date d'entree: \n 1.Entrer la date d'aujourd'hui \n 2.Entrer la date manuellement ");
        scanf("%d",&sel);
        if (sel==1){
            date_entr=date();
        }
        else{
            printf("\nEntrez la date d'ajout :<Veuillez introduire la date: jj/mm/aa, ne laissez pas d'espace S.V.P> \n");
            scanf("%d",&date_entr);
        }
        aff_char_animal(P,nom,race,espece,regime,pays,enclos,date_naiss,date_entr,poids);
        if (*Atete==NULL){ *Atete=P; Q=P;}
        else{
            aff_adr(Q,P);
            P=NULL;
        }
          /*MISE A JOUR DU CONTENUE DU FICHIER*/
          fichi=fopen("animaux.txt","a");
          fprintf(fichi,"%s %s %s %s %s %s %d %d %d\n",nom,race,espece,regime,pays,enclos,date_naiss,date_entr,poids);


    }
    else {printf("Nom non-valide, cet animal existe deja!\n");}
  fclose(fichi);
}


/**AJOUTER DANGEREUX**/
void ajouter_dangereux(l_dangereux **tete, int nbr_dangereux)
{
    /*VARIABLES*/
    char race[30];
    int cpt=0;
    l_dangereux *P;
    while(cpt!=nbr_dangereux){
        allouer(&P);
    if (tete==NULL) {*tete=P;aff_adr_dangereux(P,NULL);}
    else {aff_adr_dangereux(P,dangereux_suivant(tete)); aff_adr_dangereux(tete,P);}
        printf("Race de l'animal : \n");
        scanf("%s", race);
        //Initialisation
        strcpy(P->idt.race, race);
        //Ecriture dans le fichier
        FILE *fic=fopen("dangereux.txt","a");
        if(fic==NULL){printf("Erreur : l'ouverture du fichier as echoue\n");}
        else {
            fprintf(fic,"%s\n",P->idt.race);
        }
        fclose(fic);
        cpt+=1;
    }
}
/**AJOUTER ENCLOS**/
void MAJ_enclos_fichier(l_enclos *Etete)
{
    FILE *fic;
    l_enclos *E;
    E=Etete;
    fic=fopen("enclos.txt","w");
    if(fic==NULL){printf("Erreur\n");}
    else{
        while(E!=NULL){
            fprintf(fic,"%s %s %f %f %d %f %d\n", E->idt.nom_enclos,E->idt.type, E->idt.longueur, E->idt.largeur, E->idt.nombre_animaux_max, E->idt.poids_max, E->idt.libre);
            E=suivant_enclos(E);
        }
    }
    fclose(fic);
}
/************************************************/
void enclos_mm_pays(l_animals *Atete)
{   FILE *fic=fopen("mm_enclos.txt","w");
    l_animals *A= Atete; l_animals *S=NULL;
    while(A!=NULL){
        S=Atete;
        int cpt=1;
        while(S!=NULL){
            if ((strcmp(A->idt.pays,S->idt.pays)==0)&&(strcmp(A->idt.enclos,S->idt.enclos)==0)){
                    cpt+=1;
            }
            S=asuivant(S);
        }
        if (cpt>2){
                fprintf(fic,"%s\n",A->idt.enclos);
                printf("%s  ->  ",A->idt.enclos );
        }
        A=asuivant(A);
    }
    fclose(fic);
}
/**/

void ajouter_enclos(l_enclos **tete, int nbr_enclos){
  //Variables
  char nom[20], type[20];
  int t, cpt=0;
  int nbr_animaux, etat=0;
  int longueur, largeur,poids;
  FILE *fic=fopen("enclos.txt","a");
  l_enclos *E=NULL, *PE=NULL;
  l_enclos *P, *Q=NULL;
  while(cpt!=nbr_enclos){
    printf("Nom de l'enclos <Exemple : E02>\n" );  scanf("%s",nom );
    Acces_enclos(*tete,nom,&E,&PE);
    if(E==NULL){
            allouer_enclos(&P);
      cpt+=1;
      printf("Selectionner le type de l'enclos:\n 1.cage\n 2.voiliere\n 3.aquarium\n 4.insectarium\n");
      scanf("%d",&t);
      if(t==1){strcpy(type,"cage");}
      else{
        if(t==2) {strcpy(type,"voiliere");}
        else{
          if(t==3){strcpy(type,"aquarium");}
          else{
            if (t==4) {strcpy(type,"insectarium");}
          }
        }
      }
      printf("\nlongueur=");  scanf("%f",&longueur);
      printf("\nlargeur=");   scanf("%f",&largeur);
      printf("\nnombre d'animaux max=");  scanf("%d",&nbr_animaux );
      printf("\npoids max="); scanf("%f",&poids);

      int_enclos(P,nom,type,longueur,largeur,nbr_animaux,poids,&etat);
      printf("%s %s %f %f %d %f %d\n",P->idt.nom_enclos, P->idt.type, P->idt.longueur,P->idt.largeur,P->idt.nombre_animaux_max,P->idt.poids_max, P->idt.libre);
      //Chainage
      if(*tete==NULL){ printf("premier enclos");*tete=P; Q=P;}
      else{
        aff_adr_enclos(&Q,&P);
        Q=P;

      }
        /**MISE A JOUR FICHIER**/

      FILE *fic=fopen("enclos.txt","a");
    if(fic!=NULL){
        fprintf(fic,"%s %s %f %f %d %f %d\n",P->idt.nom_enclos,P->idt.type,P->idt.longueur,P->idt.largeur,P->idt.nombre_animaux_max,P->idt.poids_max,P->idt.libre);
    }
  fclose(fic);
    }
    else{printf("Nom invalide, ce nom existe deja.\n" );}
  }

}
/**AJOUTER PAYS**/
void ajouter_pays(l_pays *p,char pays[])
{
    l_pays* q=NULL,*r=NULL;
    pallouer(&q);
    r=pqueue(p);
    paff_adr(&r,&q);
    strcpy(p->org,pays);
}
/**             MODULES D'ADDITION           **/

/**             MODULES D'ACCES             **/

/**ACCES ENCLOS**/
void Acces_enclos(l_enclos *tete,char nom[20], l_enclos **adr_enclos, l_enclos **prec_enclos)
{
  /*VARIABLES*/
  l_enclos *P;  int trouv;

  /*Initialisation*/
  P=tete;   trouv=0;

  while ((P!=NULL) && (trouv==0)) {
    if (strcmp(nom, P->idt.nom_enclos)==0){trouv= 1;}
    else { *prec_enclos=P; P=suivant_enclos(P);
    }
  }
   *adr_enclos=P;
}

/**ACCES ANIMAL**/
void Acces_animal(l_animals *tete,char n[50], l_animals **adr_animal, l_animals **prec_animal)
{
  /*VARIABLES*/
  l_animals *P;  int trouv;  //char nom[50];

  /*Initialisation*/
  P=tete;   trouv=0;
  prec_animal=NULL;
  while ((P!=NULL) && (trouv==0)) {
    if (strcmp(n, P->idt.nom)==0){trouv= 1;}
    else { P = asuivant(P);
    prec_animal=P;
    }
  }
   *adr_animal=P;
if (trouv==0) {printf(".",n );}
}
/**             MODULES D'ACCES             **/

/**             MODULES DE SUPRESSIONS      **/

/**SUPPRESSION ANIMAL FICHIER**/
void supprimer_animal_fichier(char animal[20])
{
  FILE *fich1 , *fich2;
  char nom[20],pays[20],race[20],espece[20],regime[20],enclos[20];
  int date_naiss,date_entr;
  int poids;
  fich1 = fopen("animaux.txt","r");
  if (fich1 == NULL){printf("Erreur");}
  else{
    fich2 = fopen("fichier2.txt","a");
         if (fich2 == NULL){printf("Erreur");}
         else
            {
            while(!feof(fich1)) {
            fscanf(fich1,"%s %s %s %s %s %s %d %d %d\n",nom,race,espece,regime,pays,enclos,&date_naiss,&date_entr,&poids);
            if(strcmp(nom,animal) != 0 ) {
            fprintf(fich2,"%s %s %s %s %s %s %d %d %d\n",nom,race,espece,regime,pays,enclos,date_naiss,date_entr,poids);}
            }
            fclose(fich2);
         }
        fclose(fich1);
    rename("animaux.txt","useless.txt");
    rename("fichier2.txt","animaux.txt");
    remove("useless.txt");
    }
   printf("Suppresion fichier reussie \n");
}
void MAJ_animal_fichier( l_animals *Atete)
{
  FILE *fic;
  l_animals *A=Atete;
  fic=fopen("animaux.txt","w");
  if (fic==NULL){printf("ERREUR\n");}
  else{
        //printf("test");
    while (A!=NULL) {
        //printf("test3");

      fprintf(fic, "%s %s %s %s %s %s %d %d %d\n",A->idt.nom,A->idt.race,A->idt.espece,A->idt.regime,A->idt.pays,A->idt.enclos, A->idt.date_naiss,A->idt.date_entr,A->idt.poids);
      A=asuivant(A);
    }
  }
  fclose(fic);
}

/**SUPRESSION ENCLOS FICHIER**/

void supprimer_enclos_fichier(char nom_enclos[])
{
  FILE *fich1, *fich2;
  /*VARIABLES*/
  char nom[30]; char type[30];
  float longueur, largeur, poids_max;
  int nbr_animaux_max;
  int etat_enclos;
  //Ouverture de l'ancien fichier
  fich1 = fopen("enclos.txt","r");
  if (fich1==NULL){printf("Erreur\n");}
  else {
    //Ouverture(creation) nouveau fichier
    fich2 = fopen("enclosnouv.txt","w");
    if (fich2==NULL){printf("Erreur\n" );}
    else {
      while(!feof(fich1)){
        fscanf(fich1, "%s %s %f %f %d %f %d\n",nom, type, &longueur,&largeur,&nbr_animaux_max,&poids_max,&etat_enclos );
        if (strcmp(nom, nom_enclos)!=0){
        fprintf(fich2, "%s %s %f %f %d %f %d\n",nom, type,longueur,largeur,nbr_animaux_max,poids_max,etat_enclos );
        }
      }
      fclose(fich2);
    }
    fclose(fich1);
    remove("enclos.txt");
    rename("enclosnouv.txt","enclos.txt");
  }
  printf("Suppresion fichier reussie \n");
}

/**      SUPPRIMER ENCLOS       **/

void supprimer_enclos(l_enclos **tete)
  {
    /*Variables*/
    l_enclos *P=NULL, *Q=NULL; char nom[30]; int supp=0;
    /*Suppresion memoire*/
    printf("Enclos a supprimer\n");
    scanf("%s",nom );    Acces_enclos(*tete,nom,&P,&Q);

    /*Traitement*/
    if(P==NULL){ printf("Enclos non existant!\n");}
    else {
      /*test etat de l'enclos */
      if (P->idt.libre==1){
        /*Si l'enclos est libre on supprime*/
        if (suivant_enclos(&P)==NULL){aff_adr_enclos(&Q,NULL);}
        else{
                l_enclos *s=P;
                    aff_adr_enclos(Q,suivant_enclos(P));
                   liberer_enclos(s);

        }
        supp=1;
        printf("Enclos supprime avec succes\n" );
      }
      else {printf("Enclos non vide, Suppresion interdite! \n");}

  }
  if(supp==1){
    printf("Suppresion memoire reussie\n");
   supprimer_enclos_fichier(nom);
    }
}

/**      SUPPRIMER ENCLOS       **/
/*Note: un animal ne peut etre supprimer que si il existe,on effectue
  alors un test sur son existence */
  void supprimer_animal(l_animals **tete,l_affect_depart **AFF)
  {
    /*Variables*/
    l_affect_depart *F;
    F = *AFF;
    int stop,cpt;
    l_animals *P, *Q;int supp,da; char nom[50];
    /*Suppresion memoire*/
    printf("donner le nom a supprimer\n");
    scanf("%s",nom);
    Acces_animal(*tete,nom,&P,&Q);
    /*Traitement*/
    if(P==NULL){ printf("Animal non existant!\n");}
    else {
        //Si l'enclos est libre on supprime
        aff_adr(Q,asuivant(Q));
        liberer(P);
        supp=1;
        printf("Animal supprime avec succes\n" );

  }
  if(supp==1){
    supprimer_animal_fichier(nom);
    printf("%s",nom);
    printf("entrer la date de depart: \n");
    scanf("%d",&da);
    while((F != NULL)&&(stop != 1))
    {
        //printf("whileeeeeeeeeeeeeeeeee\n");
        if(strcmp(F->idt.nom_animal,nom)==0)
        {
            F->idt.date_depart = da;
            cpt = 1;
            stop = 1;
        }
        F = aff_suivant(F);
    }
  }
  if((supp == 1) && (cpt ==1))
  {
      ajouter_date_depart_fichier(*AFF);
  }
}
/***********************************************/

void ajouter_date_depart_fichier(l_affect_depart *AFF)
{
    l_affect_depart *F;
    F = AFF;
    FILE *fic = fopen("affectation.txt","w");
    fclose(fic);
    fic = fopen("affectation.txt","a");
    while(F != NULL)
    {
        fprintf(fic,"%s %s %d %d\n",F->idt.nom_animal,F->idt.nom_enclos,F->idt.date_affectation,F->idt.date_depart);
        F = aff_suivant(F);
    }
    fclose(fic);
}
/*******************************************************/

void une_annee(l_animals *p,l_affect_depart *AFF)
{
    l_animals *q;l_affect_depart*F;
    int cpt=0;
    q = p ; F = AFF;

    while(q != NULL)
    {
        F = AFF;
        while(F != NULL)
        {
            if(strcmp(F->idt.nom_animal,q->idt.nom)==0)
            {
                if(F->idt.date_depart == (q->idt.date_entr+1))
                {
                    cpt++;
                    if (cpt == 1){printf("les aniemaux qui on quite le zoo une année apres leurs entre :\n");}
                    printf("%s\n",F->idt.nom_animal);
                }
            }
            F = aff_suivant(F);
        }
        q = asuivant(q);
    }
    if(cpt == 0 ){printf("aucun animal\n");}
}

/*************************************************/
/**             MODULES DE SUPRESSIONS      **/

/**             MODULES DE RECHERCHE     **/

/**    CHERCHER UN ANIMAL    **/


void chercher_animal(int type)
{
    FILE *fic = fopen("animaux.txt","r");
    char nom[20],pays[20],race[20],espece[20],regime[20],enclos[20];
    int date_naiss;
    int date_entr;
    int poids;
    int annee1,annee2,jour1,jour2,mois1,mois2;
    if (fic == NULL) {printf("Erreur");}
    else{
            textcolor(4);
        printf("1)avant une date donnee\n2)après une date donnee\n3)entre deux dates donnees\n\n","right",4,11,20);
        textcolor(15);
        printf("choisir un numero de 1 a 3\n","right",4,11,20);
        scanf("%d",&type);
        if (type == 1)
        {
            printf("Entrer la date : \n Le jour :");
            scanf("%d",&jour1);
            printf("Entrer le mois :\n");
            scanf("%d",&mois1);
            printf("entrer l'annee: \n");
            scanf("%d",&annee1);
            while(!feof(fic))
            {
                fscanf(fic,"%s %s %s %s %s %s %d %d %d\nif",nom,race,espece,regime,pays,enclos,&date_naiss,&date_entr,&poids);
                /*printf("le nom = :  %s\n",nom);
                printf("le race = :  %s\n",race);*/
                //printf("le nom = :  %d\n",date_entr);
                //printf("le module = :  %d\n",date_entr%10000);
                if(date_entr%10000 < annee1){printf("le nom d'animale : %s de la race : %s entrer le : %d\n",nom,race,date_entr);}
                else if((date_entr%10000 == annee1) && (date_entr/1000 < mois1)){printf("le nom d'animale : %s de la race : %s entrer le : %d\n",nom,race,date_entr);}
                else if((date_entr%10000 == annee1) && (date_entr/1000 == mois1) && ((date_entr/100000 < jour1))) {printf("le nom d'animale : %s de la race : %s entrer le : %d\n",nom,race,date_entr);}
            }
        }
        else if(type == 2)
        {
            printf("Entrer la date : \n Le jour :");
            scanf("%d",&jour1);
            printf("Entrer le mois :\n");
            scanf("%d",&mois1);
            printf("entrer l'annee: \n");
            scanf("%d",&annee1);
            while(!feof(fic))
            {
                fscanf(fic,"%s %s %s %s %s %s %d %d %d\nif",nom,race,espece,regime,pays,enclos,&date_naiss,&date_entr,&poids);
                if(date_entr%10000 > annee1){printf("le nom d'animale : %s de la race  : %s entrer le : %d\n",nom,race,date_entr);}
                else if((date_entr%1000 == annee1) && (date_entr/1000 > mois1)){printf("le nom d'animale : %s de la race : %s entrer le : %d\n",nom,race,date_entr);}
                else if((date_entr%1000 == annee1) && (date_entr/1000 == mois1) && ((date_entr/100000 > jour1)) ){printf("le nom d'animale : %s de la race : %s entrer le: %d\n",nom,race,date_entr);}
            }
        }
        else if(type == 3)
        {
            printf("Entrer la 1er date : \n Le jour :");
            scanf("%d",&jour1);
            printf("Entrer le mois du 1er date :\n");
            scanf("%d",&mois1);
            printf("entrer l'année du 1er date: \n");
            scanf("%d",&annee1);
            printf("Entrer la 2eme date : \n Le jour :");
            scanf("%d",&jour2);
            printf("Entrer le mois du 2eme date :\n");
            scanf("%d",&mois2);
            printf("entrer l'année du 2eme date: \n");
            scanf("%d",&annee2);
            while(!feof(fic))
            {
                fscanf(fic,"%s %s %s %s %s %s %d %d %d\nif",nom,race,espece,regime,pays,enclos,&date_naiss,&date_entr,&poids);
                if((date_entr%10000 < annee2) && (date_entr%10000 > annee1)){printf("le nom d'animale : %s de la race : %s entrer le: %d\n",nom,race,date_entr);}
                else if((annee2 == annee1) && (date_entr/1000 < mois2) && (date_entr/1000 > mois1)){printf("le nom d'animale : %s de la race : %s entrer le : %d\n",nom,race,date_entr);}
                else if((annee2 == annee1) && (mois2 == mois1) && ((date_entr/100000 < jour2)&&(date_entr/100000 > jour1))){printf("le nom d'animale : %s de la race : %s entrer le : %d\n",nom,race,date_entr);}
            }
        }
        else
        {
            printf("Erreur\n");
        };
    }
    fclose(fic);
}

/**             MODULES DE DEPLACEMENT          **/

/**   DEPLACER "FICHIER"   **/

void deplacer(char n[30])
{
    FILE *fich1, * fich2;
    char nom[20],enclos[20];
    int date_naiss,date_entr;
    int poids;
    fich1 = fopen("affectation.txt","r");
    if (fich1 == NULL){printf("Erreur");}
    else
    {
        fich2 = fopen("affectation2.txt","a");
        if (fich2 == NULL){printf("Erreur");}
        else
        {
            while(!feof(fich1))
            {
                fscanf(fich1,"%s %s %d %d\n",nom,enclos,&date_naiss,&date_entr);
                if(strcmp(nom,n) != 0)
                {
                    fprintf(fich2,"%s %s %d %d\n",nom,enclos,date_naiss,date_entr);
                }
         }
         fclose(fich2);
        }
        fclose(fich1);
    }
    remove("affectation.txt");
    rename("affectation2.txt","affectation.txt");
}
/**DEPLACER ANIMAL**/


/**     HEURE ET DATES     **/
int date()
{
    SYSTEMTIME Time;

    GetLocalTime(&Time);
   int date;
    printf("Nous sommes le : %02d/%02d/%04d.\n",
    Time.wDay, Time.wMonth, Time.wYear);
    date=(Time.wDay*1000000)+(Time.wMonth*10000)+Time.wYear;
    return date;
}

/**				MODULES D'AFFECTATION 		**/
void affectation(l_enclos **Etete, l_animals **Atete,l_affect_depart *Ftete, char enclos[], char animal[])
{
  /*variables*/
  l_enclos *E=NULL, *PE=NULL;
  l_animals *A=NULL, *PA=NULL;
  int etat; int dang; char Erace[20];
  /*Initialisation*/
  Acces_animal(*Atete,animal, &A, &PA);
  Acces_enclos(*Etete, enclos, &E,&PE);
  if (A==NULL){printf("Cet animal n'existe pas: Entrez un nom valide\n");}
  else {

    if (E==NULL){printf("Cet enclos n'exite pas : Entrez un nom valide\n");}
    else{
      dang=animal_dangereux(A);
      if((dang==1)&&(E->idt.libre==0)) {printf("Affectation interdite : animal dangereux, enclos occupe\n" );}
      else{
        /*Si l'enclos est libre on effectue pas de test sur la suite*/
        if(E->idt.libre==0){
          race(E,&Erace);
          if (strcmp(Erace,A->idt.race)!=0){printf("Affectation interdite: Race non compatible\n");}
          else{
            if ((nbr_actu_animaux(E)+1) > E->idt.nombre_animaux_max){ printf("Affectation interdite: poids maximium depasse\n");}
            else{
              if((poids_actuel(E)+A->idt.poids)> E->idt.poids_max){printf("Affectation interdite nbr maximium depasse\n");}
              else{
         aff_char_animal(A,A->idt.nom,A->idt.race,A->idt.espece,A->idt.regime,A->idt.pays,E->idt.nom_enclos,A->idt.date_naiss,A->idt.date_entr,A->idt.poids);
          MAJ_animal_fichier(*Atete);
          /**Mise a jour contenue du fichier**/
      int_enclos(E,E->idt.nom_enclos,E->idt.type,E->idt.longueur,E->idt.largeur,E->idt.nombre_animaux_max, E->idt.poids_max,&etat);
      MAJ_enclos_fichier(*Etete);
    /**MISE A JOUR FICHIER AFFECTATION**/
    FILE *fic;
    fic=fopen("affectation.txt","a");
    l_affect_depart *F;
    allouer_affect_depart(&F);
    if (Ftete==NULL){Ftete=F; aff_adr_affect_depart(F,NULL);}
    else {aff_adr_affect_depart(F,aff_suivant(F)); aff_adr_affect_depart(Ftete,F);}
    int_affect(F,A->idt.nom, E->idt.nom_enclos,date(),0);
    fprintf(fic,"%s %s %d %d\n", F->idt.nom_animal,F->idt.nom_enclos,F->idt.date_affectation,F->idt.date_depart);
    fclose(fic);
              }
            }
          }
        }
        else{
          printf("Enclos libre, affectation en cours...\n");
         aff_char_animal(A,A->idt.nom,A->idt.race,A->idt.espece,A->idt.regime,A->idt.pays,E->idt.nom_enclos,A->idt.date_naiss,A->idt.date_entr,A->idt.poids);
          MAJ_animal_fichier(*Atete);

          /**Mise a jour contenue du fichier**/
      int_enclos(E,E->idt.nom_enclos,E->idt.type,E->idt.longueur,E->idt.largeur,E->idt.nombre_animaux_max, E->idt.poids_max,&etat);
      MAJ_enclos_fichier(*Etete);
    /**MISE A JOUR FICHIER AFFECTATION**/
    FILE *fic;
    fic=fopen("affectation.txt","a");
    l_affect_depart *F;
    allouer_affect_depart(&F);
    if (Ftete==NULL){Ftete=F; aff_adr_affect_depart(F,NULL);}
    else {aff_adr_affect_depart(F,aff_suivant(F)); aff_adr_affect_depart(Ftete,F);}
    int_affect(F,A->idt.nom, E->idt.nom_enclos,date(),0);
    fprintf(fic,"%s %s %d %d\n", F->idt.nom_animal,F->idt.nom_enclos,F->idt.date_affectation,F->idt.date_depart);
    fclose(fic);
        }
      }

    }
  }
}

/*********************************/
void swap(l_enclos *p, l_enclos *q)
{
    char enclos[20], type [20];
    float longueur, largeur, poids_max;
    int nbr_animaux_max, etat;
    /*Sauvegarde*/

    strcpy(enclos,p->idt.nom_enclos);
    strcpy(type,p->idt.type);
    longueur= p->idt.longueur;
    largeur= p->idt.largeur;
    poids_max=p->idt.poids_max;
    nbr_animaux_max= p->idt.nombre_animaux_max;
    etat= p->idt.libre;

    //premiere etape :   a<-b
    strcpy(p->idt.nom_enclos,q->idt.nom_enclos);
    strcpy(p->idt.type, q->idt.type);
    p->idt.longueur=q->idt.longueur;
    p->idt.largeur=q->idt.largeur;
    p->idt.nombre_animaux_max=q->idt.nombre_animaux_max;
    p->idt.poids_max=q->idt.poids_max;
    p->idt.libre= q->idt.libre;

    //deuxieme etape : b<-a
    strcpy(q->idt.nom_enclos,enclos);
    strcpy(q->idt.type,type);
    q->idt.longueur=longueur;
    q->idt.largeur= largeur;
    q->idt.nombre_animaux_max= nbr_animaux_max;
    q->idt.poids_max=poids_max;
    q->idt.libre=etat;
}
/************* Class *********************/
void tri_poids(l_enclos *Etete)
{
  int swapped, i;
  l_enclos *ptr1, *q;
  l_enclos *lptr=NULL;
  if(Etete==NULL)
      return;
  do {
    swapped =0;
    ptr1=Etete;
    while (suivant_enclos(ptr1)!=lptr){
      q=suivant_enclos(ptr1);
      if (ptr1->idt.poids_max < q->idt.poids_max){
        swap(ptr1,q);
        swapped=1;
      }
      ptr1=suivant_enclos(ptr1);
    }
    lptr=ptr1;
  }while(swapped);

}

void tri_enclos(l_enclos **Etete, l_enclos **L1, l_enclos **L2, l_enclos **L3, l_enclos **L4)
{
    FILE *fic=fopen("enclos.txt","r");
    l_enclos *E;
    E=*Etete;
    *L1=NULL,*L2=NULL,*L3=NULL,*L4=NULL;
    l_enclos *L11=NULL,*L12=NULL, *L13=NULL, *L14=NULL;
    l_enclos *Q1=NULL, *Q2=NULL, *Q3=NULL, *Q4=NULL;
    /**On définis lesl listes comme suit:
    L1 liste des enclos de type: cage
    L2 liste des enclos de type aquarium
    L3 lise des enclos de type voiliere
    L4 liste des enclos de type insectarium**/
    /**FIHCIER
    Chaque liste sera enregistre dans un fichier nomme :"type.txt"**/
    FILE *fic1, *fic2, *fic3, *fic4;
    fic1=fopen("cage.txt","w");
    fic2=fopen("aquarium.txt","w");
    fic3=fopen("voiliere.txt","w");
    fic4=fopen("insectarium.txt","w");
int etat;

    while(E!=NULL){
            printf("tets%d\n",E->idt.libre);
            printf("eeee\n");
        if(E->idt.libre==0){
        if (strcmp(E->idt.type,"cage")==0){
             fic1=fopen("cage.txt","a");
printf("test \n");
                        allouer_enclos(&L11);
                        int_enclos(L11,E->idt.nom_enclos,E->idt.type, E->idt.longueur,E->idt.largeur,E->idt.nombre_animaux_max,E->idt.poids_max,&etat);

                        if ((*L1)==NULL){printf("if");*L1=L11; Q1=L11;aff_adr_enclos(Q1,NULL);printf("Eif");}
                        else {printf("i");
                            aff_adr_enclos(Q1,L11);
                            aff_adr_enclos(L11,NULL);
                            Q1=L11;
                            printf("E");
                        }
                        //printf("pkljhhygkjhgf %s\n",Q1->adr->idt.nom_enclos);
printf("test\n");
                   if (fic1!=NULL){fprintf(fic1,"%s %s %f %f %d %f %d\n",E->idt.nom_enclos, E->idt.type, E->idt.longueur,E->idt.largeur, E->idt.nombre_animaux_max, E->idt.poids_max, E->idt.libre);}
                }
        if (strcmp(E->idt.type,"aquarium")==0){
                 fic2=fopen("aquarium.txt","a");

                        allouer_enclos(&L12);
                        int_enclos(L12,E->idt.nom_enclos,E->idt.type, E->idt.longueur,E->idt.largeur,E->idt.nombre_animaux_max,E->idt.poids_max,&etat);

                        if (*L2==NULL){*L2=L12; Q2=L12;aff_adr_enclos(L12,NULL);}
                        else {
                            aff_adr_enclos(Q2,L12);
                         //   aff_adr_enclos(L12,NULL);
                            Q2=L12;
                        }

                if (fic2 !=NULL){
                    fprintf(fic2,"%s %s %f %f %d %f %d\n",E->idt.nom_enclos, E->idt.type, E->idt.longueur,E->idt.largeur, E->idt.nombre_animaux_max, E->idt.poids_max,E->idt.libre);
                }


        }
        if (strcmp(E->idt.type,"voiliere")==0){

                fic3=fopen("voiliere.txt","a");
                        allouer_enclos(&L13);
                        int_enclos(L13,E->idt.nom_enclos,E->idt.type, E->idt.longueur,E->idt.largeur,E->idt.nombre_animaux_max,E->idt.poids_max,&etat);

                        if (*L3==NULL){*L3=L13; Q3=L13;aff_adr_enclos(L13,NULL);}
                        else {
                            aff_adr_enclos(Q3,L13);
                          //  aff_adr_enclos(L13,NULL);
                            Q3=L13;
                        }
                if (fic3 !=NULL){
                    fprintf(fic3,"%s %s %f %f %d %f %d\n",E->idt.nom_enclos, E->idt.type, E->idt.longueur,E->idt.largeur, E->idt.nombre_animaux_max, E->idt.poids_max, E->idt.libre);
                }

        }
        if(strcmp(E->idt.type,"insectarium")==0){
                fic4=fopen("insectarium.txt","a");
                        allouer_enclos(&L14);
                        int_enclos(L14,E->idt.nom_enclos,E->idt.type, E->idt.longueur,E->idt.largeur,E->idt.nombre_animaux_max,E->idt.poids_max,&etat);

                        if (*L4==NULL){*L4=L14; Q4=L14;aff_adr_enclos(L14,NULL);}
                        else {
                            aff_adr_enclos(Q4,L14);
                         //   aff_adr_enclos(L14,NULL);
                            Q4=L14;
                        }
                if (fic4 !=NULL){
                    fprintf(fic4,"%s %s %f %f %d %f %d\n",E->idt.nom_enclos, E->idt.type, E->idt.longueur,E->idt.largeur, E->idt.nombre_animaux_max, E->idt.poids_max, E->idt.libre);
                }
        }

        }
        E=suivant_enclos(E);
    }

            fclose(fic1); fclose(fic4);
            fclose(fic3); fclose(fic2);
}

/*void fussioner(l_enclos *Etete, l_enclos *L1, l_enclos *L2, l_enclos *L3, l_enclos *L4)
{
  l_enclos *Q1=NULL,*Q2=NULL, *Q3=NULL;
  printf("Fusion\n" );
*Q1=queue_enclos(L1);
  *Q2=queue_enclos(L2);
  *Q3=queue_enclos(L3);
  aff_adr_enclos(&Q1,&L2);
  aff_adr_enclos(&Q2,&L3);
  aff_adr_enclos(&Q3,&L4);
  MAJ_enclos_fichier(Etete);
}
*/

/**             MODULES DE CLASSIFICATION       **/


void anim_pays(l_animals* *p, l_animals* *o)
{
    int cpt,pass=0,ecr=0,stop,cptin=0;
    FILE *fic = fopen("mm_pays.txt","w");
    l_animals *t, *s,*q,*m;char nom[30];
    t =*p;q= *o;
    while (t != NULL){
    fic = fopen("mm_pays.txt","a");
    fseek(fic,0,SEEK_END);
        cpt =0;
        s = *p;
        if(pass ==0)
        {
        while (s != NULL)
        {
            if(strcmp(t->idt.pays,s->idt.pays)==0)
            {
                cpt++;
                if(cpt>1)
                {
                    if(ecr == 0){printf("\n   le pays : %s   \n",t->idt.pays);ecr = 1;}
                    fprintf(fic,"%s %s %s %s %s %s %d %d %d\n",s->idt.nom,s->idt.race,s->idt.espece,s->idt.regime,s->idt.pays,s->idt.enclos,s->idt.date_naiss,s->idt.date_entr,s->idt.poids);
                }
                if(cpt==1){strcpy(nom,s->idt.nom);}
            }
            s = asuivant(s);
        }
        if(cpt>1)
        {
            s = *p;
            while(s != NULL)
            {
                if(strcmp(nom,s->idt.nom)==0)
                {
                    fprintf(fic,"%s %s %s %s %s %s %d %d %d\n",s->idt.nom,s->idt.race,s->idt.espece,s->idt.regime,s->idt.pays,s->idt.enclos,s->idt.date_naiss,s->idt.date_entr,s->idt.poids);
                }
                s = asuivant(s);
            }
        }
        }
        //printf("\n");
        t = asuivant(t);fclose(fic);
        cree_llc_anim_pays(&q);

        stop = 0 ;
        m =q;
        while((m != NULL) && (stop == 0))
        {
            if(strcmp(m->idt.pays,t->idt.pays) == 0)
            {
                //cptin++;
                pass = 1;
                //ecr = 1;
                if(t!=NULL){
                t = asuivant(t);}
                stop = 1;
            }
            else{
                    pass = 0;
            if (cptin==0)
            {
                pass = 0;
                ecr = 0 ;
            }
            m = asuivant(m);
            }
        }
        cptin=0;
    }
    fclose(fic);
}

/**********************************************************/

void    cree_llc_anim_pays(l_animals* *t)
{
    l_animals* p, *q; char nom[20],pays[20],race[20],espace[20],regime[20],enclos[20];
    int date_naiss,date_entr;
    int poids;
    FILE *fic =fopen("mm_pays.txt","r");
    allouer(&p);
    *t = p ;
    fscanf(fic,"%s %s %s %s %s %s %d %d %d",nom,race,espace,regime,pays,enclos,&date_naiss,&date_entr,&poids);

    aff_char_animal(p,nom,race,espace,regime,pays,enclos,date_naiss,date_entr,poids);

        fflush(stdin);
     while(!feof(fic))
        {
        fflush(stdin);
        allouer(&q);
        aff_adr(p,q);
        p=q;
        fscanf(fic,"\n%s %s %s %s %s %s %d %d %d\n",nom,race,espace,regime,pays,enclos,&date_naiss,&date_entr,&poids);
        aff_char_animal(p,nom,race,espace,regime,pays,enclos,date_naiss,date_entr,poids);

        fflush(stdin);
        }
        aff_adr(p,NULL);
        fclose(fic); //Fermeture du fichier
}
/**********************************************************/

void les_pays(l_animals* *p,char pays[20])
{
    l_animals *q, *k;
    q = *p;
    int cptin=0,cptout=1,cpt,ecr=0;
    int stop=1;
    cpt = 0;
    printf("on a tout c'est pays :\n");
    while(q !=NULL)
    {
        k = *p;
        while((k != NULL) && (cptin!=cptout-1)&& (stop!=0))
        {
            if(strcmp(q->idt.pays,k->idt.pays)==0)
            {
                ecr = 1;
                stop = 0;
            }
            else{ecr= 0;}
            k = asuivant(k);
            cptin++;
        }
        if(ecr == 0){printf("|  %9s  |",q->idt.pays);cpt++;}
        if(cpt ==5 ){printf("\n");cpt = 0;}
        stop =1;
        cptin = 0; cptout++;
        q = asuivant(q);
    }
    printf("\n coisissez le pays que vous voulez\n");
    scanf("%s",pays);
}

/**************************************************************/

void les_races(l_animals *p,char race[20],char pays[20])
{
    l_animals *q, *k;
    q = p;
    int cptin=0,cptout=1,cpt,ecr=0;
    int stop=1;
    cpt = 0;
    printf("Dans le pays %s on a tout ces races :\n",pays);
    printf("| %s ",q->idt.pays);
    while(q !=NULL)
    {
        k = p;
        while((k != NULL) && (cptin!=cptout-1)&& (stop!=0))
        {
            if(strcmp(q->idt.race,k->idt.race)==0)
            {
                ecr = 1;
                stop = 0;
            }
            else{ecr= 0;}
            k = asuivant(k);
            cptin++;
        }
        if(ecr == 0){printf("|  %9s  |",q->idt.race);cpt++;}
        if(cpt ==5 ){printf("\n");cpt = 0;}
        stop =1;
        cptin = 0; cptout++;
        q = asuivant(q);
    }
    printf("\n coisissez la race que vous voulez\n");
    scanf("%s",race);
}
/***********************************************************/

void les_especes(l_animals *p,char espece[20],char pays[20])
{
    l_animals *q, *k;
    q = p;
    int cptin=0,cptout=1,cpt,ecr=0;
    int stop=1;
    cpt = 0;
    printf("Dans le pays %s on a tout ces races :\n",pays);
    while(q !=NULL)
    {
        k = p;
        while((k != NULL) && (cptin!=cptout-1)&& (stop!=0))
        {
            //printf("%d ||",cptin);
            if(strcmp(q->idt.espece,k->idt.espece)==0)
            {
                //sprintf("NULL\n");
                ecr = 1;
                stop = 0;
            }
            else{ecr= 0;}
            k = asuivant(k);
            cptin++;
        }
        if(ecr == 0){printf("|  %9s  |",q->idt.espece);cpt++;}
        if(cpt == 5){printf("\n");cpt = 0;}
        stop = 1;
        cptin = 0; cptout++;
        //printf("cptout : %d\n",cptout);
        q = asuivant(q);
    }
    printf("\n choisissez la race que vous voulez\n");
    scanf("%s",espece);
}

/**********************************************************/
void anim_mm_pays(l_animals* *p, char pays[30],l_animals* *s)
{
    l_animals *q;
    q = *p ;
    FILE *fic = fopen("anim_mm_pays.txt","w");
    fclose(fic);
    fic = fopen("anim_mm_pays.txt","a");
    while(q != NULL)
    {
        if(strcmp(q->idt.pays,pays)==0)
        {
            fprintf(fic,"%s %s %s %s %s %s %d %d %d\n",q->idt.nom,q->idt.race,q->idt.espece,q->idt.regime,q->idt.pays,q->idt.enclos,q->idt.date_naiss,q->idt.date_entr,q->idt.poids);
        }
        q = asuivant(q);
    }
    fclose(fic);
    cree_llc_anim_mm_pays(s);
}
/**/   /******/     /*****/  /******/       /***/ /**/   /******/     /*****/  /******/       /***//**/   /******/     /*****/  /******/       /***//**/   /******/     /*****/  /******/       /***/
void    cree_llc_anim_mm_pays(l_animals* *t)
{
    l_animals* p, *q; char nom[20],pays[20],race[20],espace[20],regime[20],enclos[20];
    int date_naiss,date_entr;
    int poids;
    FILE *fic =fopen("anim_mm_pays.txt","r");
    allouer(&p);
    *t = p ;
    fscanf(fic,"%s %s %s %s %s %s %d %d %d",nom,race,espace,regime,pays,enclos,&date_naiss,&date_entr,&poids);

    aff_char_animal(p,nom,race,espace,regime,pays,enclos,date_naiss,date_entr,poids);

        fflush(stdin);
     while(!feof(fic))
        {
        fflush(stdin);
        allouer(&q);
        aff_adr(p,q);
        p=q;
        fscanf(fic,"\n%s %s %s %s %s %s %d %d %d\n",nom,race,espace,regime,pays,enclos,&date_naiss,&date_entr,&poids);
        aff_char_animal(p,nom,race,espace,regime,pays,enclos,date_naiss,date_entr,poids);


        }
        aff_adr(p,NULL);
        fclose(fic); //Fermeture du fichier
        //printf("creation reussie\n");
}

/**/         /**/
/*****************************/

void class_race(l_animals* *p,char pays[20])
{
    char race[20];
    l_animals* q ,*f;
    q = *p;
    int cpt =0;
   // printf("%s la race class\n",q->idt.race);
   printf("teeeeesttttttt les races\n");
    les_races(*p,race,pays);
    //printf("end of test les races \n");
    printf("la race selon la liste %s\n",q->idt.race);
    printf("tout ces animaux sont de la race %s\n",race);
    while(q != NULL)
    {

        if(strcmp(race,q->idt.race)==0)
        {
            printf("|  %s  |",q->idt.nom);
            cpt++;
        }
        if (cpt == 5){printf("\n");cpt = 0;}
        q = asuivant(q);
    }
}
/**************************************************************/
void class_espece(l_animals* *p,char pays[20])
{
    char espece[20];
    l_animals* q ,*f;
    q = *p;
    int cpt =0;
   // printf("teeeeesttttttt les especes\n");
    les_especes(*p,espece,pays);
   // printf("end of test les especes \n");
   // printf("la race selon la liste %s\n",q->idt.espece);
    printf("tout ces animaux sont de l'espece %s\n",espece);
    while(q != NULL)
    {

        if(strcmp(espece,q->idt.espece)==0)
        {
            printf("|  %s  |",q->idt.nom);
            cpt++;
        }
        if (cpt == 5){printf("\n");cpt = 0;}
        q = asuivant(q);
    }
}


/**/ /////////////////////////
/**** grafic                **/
void menu(chaine *lechoix,l_animals *p,l_enclos *q,l_affect_depart *AFF,l_dangereux *D)
{ int *e,*d,*n;
  int x,y,nb_c;
  FILE *f;
//  cree_cle(&n,&e,&d);
  char name[20],mot[20],rmp[20];
  char dest[20];
  char psw[20]; ////////--- pour l'acces aux cles ---////////////
  char *old_locale, *saved_locale;
  deb:
  basemenu();
  switch(choix(lechoix))
  { case 1: system("cls");
   int i,x=0,y=0,ch;int type;

        ch=1;
        basemenu();
         chaine menu1[]={ "   >>           LISTE DES ANIMAUX           <<   ",
                          "   >>           LISTE DES ENCLOS            <<   ",
                          "   >>      LISTE DES ANIMAUX DANGEREUX      <<   ",
                          "   >>      LISTE DES AFFECTATIONS/DEPARTS   <<   ",
                          "   >>                                       <<   ",
                          "   >>                Retour                 <<   ",};
     do{
      for(i=0;i<6;i++)
        {if(i==ch){
            textbackground(2);
            textcolor(15);
             printdirection(menu1[i].mots,"right",35,(22+i+1),0);
             }
         else{     textbackground(15);
                   textcolor(0);
             printdirection(menu1[i].mots,"right",35,(22+i+1),0);
             }

    }

    x=readkey();
    switch(x){
     case 336 : ch = (ch+1)%6;
                break;
     case 328: ch = (ch+5)%6;
               break;
     case 13 :
         y=1;
        break;

       }

 }while(y!=1);
 //ch+1


        switch(ch+1){
        case 1:
            system("cls");
           // bande();
            //printf("test\n");
            textcolor(15);
            textbackground(2);
            affichage_animal(p);
            system("pause");
            break;
        case 2:
            system("cls");
           // bande();
            printf("test\n");
            textcolor(15);
            textbackground(2);
            affichage_enclos(q);
            system("pause");
            break;
           system("pause");
           break;
    case 3:
            system("cls");
           // bande();
            printf("test\n");
            textcolor(15);
            textbackground(2);
            affichage_dangereux(D);
            system("pause");
            break;
           system("pause");
           break;
        case 4:
            system("cls");
           // bande();
            printf("test\n");
            textcolor(15);
            textbackground(2);
            affichage_affectation(AFF);
            system("pause");
            break;
        }
           system("pause");
           break;
    case 2: system("cls");
            x=0;y=0;

            ch=1;
            basemenu();
            chaine menu2[]={ "   >>           AJOUTER UN ANIMAL           <<   ",
            "   >>         SUPPRIMER UN ANIMAL           <<   ",
            "   >>     AFFECTER UN ANIMAL A UN ENCLOS    <<   ",
            "   >>    DEPLACER UN ANIMAL VERS UN ENCLOS  <<   ",
            "   >>                                       <<   ",
            "   >>                Retour                 <<   "};
            do{
            for(i=0;i<6;i++)
            {if(i==ch){
            textbackground(2);
            textcolor(15);
            printdirection(menu2[i].mots,"right",35,(22+i+1),0);
            }
            else{     textbackground(15);
            textcolor(0);
            printdirection(menu2[i].mots,"right",35,(22+i+1),0);
            }

            }
            x=readkey();
            switch(x){
            case 336 : ch = (ch+1)%6;
            break;
            case 328: ch = (ch+5)%6;
            break;
            case 13 :
            y=1;
            break;

                       }

            }while(y!=1);
                 //ch+1


            switch(ch+1){
                char enclos[10],animal[10];
                    case 1:
            system("cls");
           // bande();
            printf("test\n");
            textcolor(15);
            textbackground(2);
            ajouter_animal(p);
            system("pause");
            break;
        case 2:
            system("cls");
           // bande();
            printf("test\n");
            textcolor(15);
            textbackground(2);
            supprimer_animal(&p,&AFF);
            system("pause");
            break;
           system("pause");
           break;
    case 3:
            system("cls");
           // bande();
            printf("test\n");
            textcolor(15);
            textbackground(2);
            printf("-> nom de l'animal\n");
            scanf("%s",animal);
            printf("-> nom de l'enclos\n");
            scanf("%s",enclos);
            affectation(&q,&p,AFF,enclos,animal);
            system("pause");
            break;
           system("pause");
           break;
        case 4:
            system("cls");
           // bande();
            printf("test\n");
            textcolor(15);
            textbackground(2);
           deplacer_animal(&p);
           printf("donner le nom de l'animal\n");
           scanf("%s",animal);
            deplacer(animal);
            affectation(&q,&p,AFF,enclos,animal);
            system("pause");
            break;
            }
            system("pause");
            break;
    case 3: system("cls");
            x=0;y=0;

            ch=1;
            basemenu();
            chaine menu3[]={
            "   >>           AJOUTER UN ENCLOS           <<   ",
            "   >>          SUPPRIMER UNE ENCLOS         <<   ",
            "   >>       TRIER LA LISTE DES ENCLOS       <<   ",
            "   >>                                       <<   ",
            "   >>                                       <<   ",
            "   >>                Retour                 <<   "};
            do{
            for(i=0;i<6;i++)
            {if(i==ch){
            textbackground(2);
            textcolor(15);
            printdirection(menu3[i].mots,"right",35,(22+i+1),0);
            }
            else{     textbackground(15);
            textcolor(0);
            printdirection(menu3[i].mots,"right",35,(22+i+1),0);
            }

            }
            x=readkey();
            switch(x){
            case 336 : ch = (ch+1)%6;
            break;
            case 328: ch = (ch+5)%6;
            break;
            case 13 :
            y=1;
            break;

                       }

            }while(y!=1);
                 //ch+1


            switch(ch+1){
                 l_enclos *L1=NULL, *L2=NULL, *L3=NULL, *L4=NULL;
            case 1:system("cls");
           // bande();
            printf("test\n");
            textcolor(15);
            textbackground(2);
            ajouter_enclos(&q,1);
            system("pause");
            break;
           system("pause");
            break;
            case 2:
                system("cls");
           // bande();
            printf("test\n");
            textcolor(15);
            textbackground(2);
            supprimer_enclos(&q);
            system("pause");
            break;
            case 3:
                 system("cls");
           // bande();
            printf("test\n");
            textcolor(15);
            textbackground(2);
             printf("-----------------------------------------------------------------TRI ENCLOS SELON LE TYPE\n");
             tri_enclos(&q,&L1,&L2,&L3,&L4);
             affichage_enclos(L1);
             printf("\n");printf("\n"); affichage_enclos(L2); printf("\n");printf("\n"); affichage_enclos(L3); printf("\n"); printf("\n");affichage_enclos(L4);
                //Tri enclos selon le poids
            printf("-----------------------------------------------------------------TRI ENCLOS SELON LE POIDS\n");

             tri_poids(L1); tri_poids(L2); tri_poids(L3); tri_poids(L4);
             affichage_enclos(L1);
             printf("\n");printf("\n"); affichage_enclos(L2); printf("\n");printf("\n"); affichage_enclos(L3); printf("\n"); printf("\n");affichage_enclos(L4);

            }

           system("pause");
            break;
    case 4:
            system("cls");
            bande();
            textcolor(15);
            textbackground(2);
            printdirection("                                           Rechercher des animaux                                            ","right",0,3,3);
            gotoxy(1,5);
            chercher_animal(type);
            system("pause");
            break;
    case 5:system("cls");
            x=0;y=0;

            ch=1;
            basemenu();
            chaine menu5[]={ ">>     ANIMAUX ISSU DU MEME PAYS D'ORIGINE    <<  ",
                             ">>  ENCLOS CONTENANT DES ANIMAUX DU MEME PAYS <<  ",
                             ">>LES ANIMAUX QUITTANT LE ZOO APRES UNE ANNEE <<  ",
                             ">>                                            <<  ",
                             ">>                                            <<  ",
                             ">>                    RETOUR                  <<  "};
            do{
            for(i=0;i<6;i++)
            {if(i==ch){
            textbackground(2);
            textcolor(15);
            printdirection(menu5[i].mots,"right",35,(22+i+1),0);
            }
            else{     textbackground(15);
            textcolor(0);
            printdirection(menu5[i].mots,"right",35,(22+i+1),0);
            }

            }
            x=readkey();
            switch(x){
            case 336 : ch = (ch+1)%6;
            break;
            case 328: ch = (ch+5)%6;
            break;
            case 13 :
            y=1;
            break;

                       }

            }while(y!=1);
                 //ch+1


            switch(ch+1){
                char pays[30],selon[10];
                l_animals *s=NULL;
                int repeat = 0;
            case 1:system("cls");
           // bande();
            printf("test\n");
            textcolor(15);
            textbackground(2);
            les_pays(&p,pays);
            anim_mm_pays(&p,pays,&s);
            printf("voulez vous les classer selon la race ou l'espece !! \n");
            printf("entre 'race' pour race , 'espece' pour espece ,'quit' pour quiter \n ");
            printf("votre choix :  ");
            scanf("%s",selon);
            printf("%s\n",selon);
            if(strcmp(selon,"race")==0)
            {
                printf("voici le classement par race :\n");
                class_race(&s,pays);
                repeat = 1;
            }
            else if(strcmp(selon,"espece")==0)
            {
                class_espece(&s,pays);
                repeat = 1;
            }
            else if(strcmp(selon,"quit")==0)
            {
                exit(0);
                repeat = 1;
            }
            else { repeat = 0;}
            system("pause");
            break;
            case 2:
                system("cls");
            bande();
            gotoxy(1,1);
            textcolor(15);
            textbackground(2);
            enclos_mm_pays(p);
            system("pause");
            break;
            case 3:
            system("cls");
            bande();
            gotoxy(1,1);
            textcolor(15);
            textbackground(2);
            une_annee(p,AFF);
            }
            system("pause");
            break;



    case 6:

          goto fin;

  }
  goto deb;
  fin:
  fin();
}
void  basemenu(void)
{int i,y,a=0,z,d,b;
system("mode con lines=40 cols=120");
system("cls");
system("COLOR 02");
        blancln(5);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
moverect("up");
textbackground(2);
textcolor(15);
y=7;
gotoxy(35,y);
 printf("%c%c%c%c%c   %c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c     %c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+1);
 printf("%c%c%c%c%c%c %c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c    %c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+2);
 printf("%c%c%c%c%c%c%c%c%c%c%c%c%c   %c%c%c        %c%c%c%c%c%c   %c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+3);
 printf("%c%c%c%c%c%c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c  %c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+4);
 printf("%c%c%c  %c%c%c  %c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c %c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+5);
 printf("%c%c%c   %c   %c%c%c   %c%c%c        %c%c%c%c  %c%c%c%c%c%c%c   %c%c%c   %c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+6);
 printf("%c%c%c       %c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c    %c%c%c%c%c   %c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219); gotoxy(35,y+7);
 printf("%c%c%c       %c%c%c   %c%c%c%c%c%c%c%c   %c%c%c%c     %c%c%c%c    %c%c%c%c%c%c%c ",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
gotoxy(30,20);
textcolor(2);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,22);delay(50);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,23);delay(50);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,24);delay(50);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,25);delay(50);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,26);delay(50);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,27);delay(50);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,28);delay(50);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,29);delay(50);

printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(30,31);delay(50);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
textcolor(2);
z=86;
d=20;
textbackground(0);
b=10;  textbackground(b);

printdirection("                                                     \n","left",z,d+2,0);textbackground(b);
printdirection("                                                     \n","left",z,d+3,0);textbackground(b);
printdirection("                                                     \n","left",z,d+4,0);textbackground(b);
printdirection("                                                     \n","left",z,d+5,0);textbackground(b);
printdirection("                                                     \n","left",z,d+6,0);textbackground(b);
printdirection("                                                     \n","left",z,d+7,0);textbackground(b);
printdirection("                                                     \n","left",z,d+8,0);textbackground(b);
printdirection("                                                     \n","left",z,d+9,0);

}
//-----------------------------------------------------------------------------------------------
void intro(void){int y;
system("mode con lines=40 cols=120");
system("COLOR 02");
 y=1;
 textcolor(2);
  gotoxy(1,y);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+1);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+2);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+3);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+4);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+5);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+6);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+7);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+8);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+9);
delay(500);
  decalrectangle(1);
  //**********************************************************************************************************************
    textbackground(0);
    textcolor(10);

        printdirection("Ecole Nationale Superieur en Informatique d'Alger ","right",38,1,45);

        printdirection("Annee Universitaire 2018/2019","right",49,2,45) ;
        decalrectangle(2);
        textcolor(2);
textbackground(0);
gotoxy(35,10);
 printf("%c%c%c%c%c%c%c%c%c%c             %c%c%c%c%c%c%c%c%c           %c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219) ;delay(50);gotoxy(35,11);
 printf("    %c%c                 %c%c     %c%c             %c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);delay(50);gotoxy(35,12);
 printf("    %c%c                 %c%c     %c%c             %c%c\n",219,219,219,219,219,219,219,219,219,219);delay(50);gotoxy(35,13);
 printf("    %c%c                 %c%c%c%c%c%c%c%c%c             %c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219);delay(50);gotoxy(35,14);
 printf("    %c%c                 %c%c                    %c%c\n",219,219,219,219,219,219,219);delay(50);gotoxy(35,15);
 printf("    %c%c                 %c%c                  %c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219);
delay(300);
 decalrectangle(3);
textbackground(0);
textcolor(2);
 gotoxy(14,20);

printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);gotoxy(14,21);
printf("%c                                                                                            %c\n",186,186);gotoxy(14,22);
printf("%c                                                                                            %c\n",186,186);gotoxy(14,23);
printf("%c                                                                                            %c\n",186,186);gotoxy(14,24);
printf("%c                                                                                            %c\n",186,186);gotoxy(14,25);
printf("%c                                                                                            %c\n",186,186);gotoxy(14,26);
printf("%c                                                                                            %c\n",186,186);gotoxy(14,27);
printf("%c                                                                                            %c\n",186,186);gotoxy(14,28);
textbackground(0);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
printdirection(">","down",20,22,60);
printdirection("Realise par : ","left",35,22,60);

printdirection(" e ","down",64,23,60);
printdirection(" n ","down",63,23,60);
printdirection(" i ","down",62,23,60);
printdirection(" d ","down",61,23,60);
printdirection("ad ","down",60,23,60);
printdirection("nE ","down",59,23,60);
printdirection("ua ","down",58,23,60);
printdirection("ol7 ","down",57,23,60);
printdirection("MA0 ","down",56,23,60);
printdirection("||| ","down",54,23,60);
printdirection("I e ","down",52,23,60);
printdirection("LIp ","down",51,23,60);
printdirection("ARu ","down",50,23,60);
printdirection("MSo ","down",49,23,60);
printdirection("MAr ","down",48,23,60);
printdirection("ANG ","down",47,23,60);
printdirection(" | Semestre 02","right",80,24,30);
printdirection("> Encadree par :       Dr Timgelit","right",20,27,45);
textbackground(0);
gotoxy(wherex()-14,wherey()+3);
system("pause");
}
void fin(void){
    system("COLOR 02");
    system("cls");
    textbackground(15);
    textcolor(0);
    decalrectangle(1);
    textcolor(15);
    textbackground(0);
    printdirection("           Nous vous remercions d'avoir utiliser notre programme    ","right",20,2,30 );
delay(1000);
textbackground(15);
    textcolor(0);
decalrectangle(2);
decalrectangle(3);
gotoxy(15,10);
    textbackground(2);
    textcolor(15);
    printdirection("  Pour toute remarque contactez nous sur :  ","right",wherex()+24,wherey(),20);textbackground(2);
    printdirection("       ","down",60,wherey()+4,15);
     textbackground(0);textcolor(15);
    printdirection(" AMMALI Mouna ","right",24,16,15);
        textbackground(15);textcolor(0);
     printdirection(" e-mail: im_ammali@esi.dz ","right",17,18,15);
     textbackground(0);textcolor(15);
    printdirection(" NASRI Ala-Eddine ","right",85,16,15);
        textbackground(15);textcolor(0);
     printdirection(" e-mail: ia_nasri@esi.dz ","right",79,18,15);


       gotoxy(38,wherey()+7);
       textcolor(2);
       system("pause");
}
int choix (chaine *lechoix){
    int i,x=0,y=0,ch;

ch=1;
 do{
  for(i=0;i<6;i++)
    {if(i==ch){
        textbackground(2);
        textcolor(15);
         printdirection(lechoix[i].mots,"right",35,(22+i+1),0);
         }
     else{     textbackground(15);
               textcolor(0);
         printdirection(lechoix[i].mots,"right",35,(22+i+1),0);
         }

    }
    x=readkey();
    switch(x){
     case 336 : ch = (ch+1)%6;
                break;
     case 328: ch = (ch+5)%6;
               break;
     case 13 :
         y=1;
        break;

       }

 }while(y!=1);
 return ch+1;
                      }
//----------------------------------Bibliotheque Conio pour l'interface graphique ----------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
typedef enum
{
    BLACK,          /**< black color */
    BLUE,           /**< blue color */
    GREEN,          /**< green color */
    CYAN,           /**< cyan color */
    RED,            /**< red color */
    MAGENTA,        /**< magenta color */
    BROWN,          /**< brown color */
    LIGHTGRAY,      /**< light gray color */
    DARKGRAY,       /**< dark gray color */
    LIGHTBLUE,      /**< light blue color */
    LIGHTGREEN,     /**< light green color */
    LIGHTCYAN,      /**< light cyan color */
    LIGHTRED,       /**< light red color */
    LIGHTMAGENTA,   /**< light magenta color */
    YELLOW,         /**< yellow color */
    WHITE           /**< white color */
} COLORS;

/*@{*/
/**
 * This defines enables you to use all MinGW conio.h functions without
 * underscore.
 */
#define cgets   _cgets
#define cprintf _cprintf
#define cputs   _cputs
#define cscanf  _cscanf

#ifdef UNICODE
    #define cgetws   _cgetws
    #define getwch   _getwch
    #define getwche  _getwche
    #define putwch   _putwch
    #define ungetwch _ungetwch
    #define cputws   _cputws
    #define cwprintf _cwprintf
    #define cwscanf  _cwscanf
#endif
/*@}*/

/**
 * Define alias for _conio_gettext.
 * If you want to use gettext function from some other library
 * (e.g. GNU gettext) you have to define _CONIO_NO_GETTEXT_ so you won't get
 * name conflict.
 */
#ifndef _CONIO_NO_GETTEXT_
  #define gettext _conio_gettext
#endif

#define ScreenClear clrscr

/**
 * @anchor cursortypes
 * @name Cursor types
 * Predefined cursor types. */
/*@{*/
#define _NOCURSOR 0         /**< no cursor */
#define _SOLIDCURSOR 100    /**< cursor filling whole cell */
#define _NORMALCURSOR 20    /**< cursor filling 20 percent of cell height */
/*@}*/

/**
 * Structure holding information about screen.
 * @see gettextinfo
 * @see inittextinfo
 */
struct text_info {
    unsigned char curx;          /**< cursor coordinate x */
    unsigned char cury;          /**< cursor coordinate y */
    unsigned short attribute;    /**< current text attribute */
    unsigned short normattr;     /**< original value of text attribute after
                                      start of the application. If you don't
                                      called the <TT>inittextinfo</TT> on the
                                      beginning of the application, this always
                                      will be black background and light gray
                                      foreground */
    unsigned char screenwidth;   /**< screen width */
    unsigned char screenheight;  /**< screen height */
};

/**
 * Structure used by gettext/puttext.
 * @see _conio_gettext
 * @see puttext
 */
struct char_info {
#ifdef UNICODE
    wchar_t letter;        /**< character value */
#else
    char letter;           /**< character value */
#endif
    unsigned short attr;   /**< attribute value */
};

static int __BACKGROUND = BLACK;
static int __FOREGROUND = LIGHTGRAY;
static struct text_info __text_info = {
    1, 1,
    LIGHTGRAY + (BLACK << 4),
    LIGHTGRAY + (BLACK << 4),
    80, 25
};
static int __CONIO_TOP = 0;
static int __CONIO_LEFT = 0;
void  basemenu(void);
static void
__fill_text_info (void)
{
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    __CONIO_LEFT = info.srWindow.Left;
    __CONIO_TOP = info.srWindow.Top;
    __text_info.curx = info.dwCursorPosition.X - __CONIO_LEFT + 1;
    __text_info.cury = info.dwCursorPosition.Y - __CONIO_TOP  + 1;
    __text_info.attribute = info.wAttributes;
    __text_info.screenwidth  = info.srWindow.Right - info.srWindow.Left + 1;
    __text_info.screenheight = info.srWindow.Bottom - info.srWindow.Top + 1;
}

void
gettextinfo (struct text_info * info)
{
    __fill_text_info();
    *info = __text_info;
}

void
inittextinfo (void)
{
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo (GetStdHandle(STD_OUTPUT_HANDLE), &info);
    __text_info.normattr = info.wAttributes;
}

void
clrscr (void)
{
    DWORD written;
    int i;

    __fill_text_info();
    for (i = __CONIO_TOP; i < __CONIO_TOP + __text_info.screenheight; i++) {
      FillConsoleOutputAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
        __FOREGROUND + (__BACKGROUND << 4), __text_info.screenwidth,
        (COORD) {__CONIO_LEFT, i},
        &written);
      FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',
        __text_info.screenwidth,
        (COORD) {__CONIO_LEFT, i},
        &written);
    }
    gotoxy (1, 1);
}


void
clreol (void)
{
    COORD coord;
    DWORD written;

    __fill_text_info();
    coord.X = __CONIO_LEFT + __text_info.curx - 1;
    coord.Y = __CONIO_TOP  + __text_info.cury - 1;

    FillConsoleOutputAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
      __FOREGROUND + (__BACKGROUND << 4),
      __text_info.screenwidth - __text_info.curx + 1, coord, &written);
    FillConsoleOutputCharacter (GetStdHandle (STD_OUTPUT_HANDLE),
      ' ', __text_info.screenwidth - __text_info.curx + 1, coord, &written);
    gotoxy (__text_info.curx, __text_info.cury);
}


void
delline (void)
{
    COORD coord;
    SMALL_RECT rect;
    CHAR_INFO fillchar;

    __fill_text_info();
    coord.X = __CONIO_LEFT;
    coord.Y = __CONIO_TOP + __text_info.cury - 1;
    rect.Left = __CONIO_LEFT;
    rect.Top = __CONIO_TOP + __text_info.cury;
    rect.Right = __CONIO_LEFT + __text_info.screenwidth - 1;
    rect.Bottom = __CONIO_TOP + __text_info.screenheight - 1;
    fillchar.Attributes = __FOREGROUND + (__BACKGROUND << 4);
#ifdef UNICODE
    fillchar.Char.UnicodeChar = L' ';
    ScrollConsoleScreenBufferW (GetStdHandle (STD_OUTPUT_HANDLE),
      &rect, NULL, coord, &fillchar);
#else
    fillchar.Char.AsciiChar = ' ';
    ScrollConsoleScreenBufferA (GetStdHandle (STD_OUTPUT_HANDLE),
      &rect, NULL, coord, &fillchar);
#endif


    gotoxy (__text_info.curx, __text_info.cury);
}

void
insline (void)
{
    COORD coord;
    SMALL_RECT rect;
    CHAR_INFO fillchar;

    __fill_text_info();
    coord.X = __CONIO_LEFT;
    coord.Y = __CONIO_TOP + __text_info.cury;
    rect.Left = __CONIO_LEFT;
    rect.Top = __CONIO_TOP + __text_info.cury - 1;
    rect.Right = __CONIO_LEFT + __text_info.screenwidth - 1;
    rect.Bottom = __CONIO_TOP + __text_info.screenheight - 2;
    fillchar.Attributes = __FOREGROUND + (__BACKGROUND << 4);
#ifdef UNICODE
    fillchar.Char.UnicodeChar = L' ';
    ScrollConsoleScreenBufferW (GetStdHandle (STD_OUTPUT_HANDLE),
      &rect, NULL, coord, &fillchar);
#else
    fillchar.Char.AsciiChar = ' ';
    ScrollConsoleScreenBufferA (GetStdHandle (STD_OUTPUT_HANDLE),
      &rect, NULL, coord, &fillchar);
#endif

    gotoxy (__text_info.curx, __text_info.cury);
}

void
movetext (int left, int top, int right, int bottom, int destleft, int desttop)
{
    struct char_info * buffer;

    buffer = malloc ((right - left + 1) * (bottom - top + 1) * sizeof(struct char_info));
    gettext (left, top, right, bottom, buffer);
    puttext (destleft, desttop, destleft + right - left, desttop + bottom - top, buffer);
    free(buffer);
}

void
_conio_gettext (int left, int top, int right, int bottom,
  struct char_info * buf)
{
    int i;
    SMALL_RECT r;
    CHAR_INFO* buffer;
    COORD size;

    __fill_text_info();
    r = (SMALL_RECT) {__CONIO_LEFT + left - 1, __CONIO_TOP + top - 1,
      __CONIO_LEFT + right - 1, __CONIO_TOP + bottom - 1};
    size.X = right - left + 1;
    size.Y = bottom - top + 1;
    buffer = malloc (size.X * size.Y * sizeof(CHAR_INFO));

    ReadConsoleOutput (GetStdHandle (STD_OUTPUT_HANDLE),
      (PCHAR_INFO) buffer, size, (COORD) {0, 0}, &r);

    for (i = 0; i < size.X * size.Y; i++)
    {
#ifdef UNICODE
        buf[i].letter = buffer[i].Char.UnicodeChar;
#else
        buf[i].letter = buffer[i].Char.AsciiChar;
#endif
        buf[i].attr = buffer[i].Attributes;
    }
    free (buffer);
}

void
puttext (int left, int top, int right, int bottom, struct char_info * buf)
{
    int i;
    SMALL_RECT r;
    CHAR_INFO* buffer;
    COORD size;

    __fill_text_info();
    r = (SMALL_RECT) {__CONIO_LEFT + left - 1, __CONIO_TOP + top - 1,
      __CONIO_LEFT + right - 1, __CONIO_TOP + bottom - 1};
    size.X = right - left + 1;
    size.Y = bottom - top + 1;
    buffer = malloc (size.X * size.Y * sizeof(CHAR_INFO));

    for (i = 0; i < size.X * size.Y; i++)
    {
#ifdef UNICODE
        buffer[i].Char.UnicodeChar = buf[i].letter;
#else
        buffer[i].Char.AsciiChar = buf[i].letter;
#endif
        buffer[i].Attributes = buf[i].attr;
    }

    WriteConsoleOutput (GetStdHandle (STD_OUTPUT_HANDLE),
      buffer, size, (COORD) {0, 0}, &r);
    free (buffer);
}

void
gotoxy(int x, int y)
{
  COORD c;

  c.X = __CONIO_LEFT + x - 1;
  c.Y = __CONIO_TOP  + y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void
cputsxy (int x, int y, char * str)
{
    gotoxy (x, y);
    cputs (str);
}

void
putchxy (int x, int y, char ch)
{
    gotoxy (x, y);
    putch (ch);
}

void
_setcursortype (int type)
{
    CONSOLE_CURSOR_INFO Info;

    if (type == 0) {
        Info.bVisible = FALSE;
    } else {
      Info.dwSize = type;
      Info.bVisible = TRUE;
    }
    SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE),
      &Info);
}


void
textattr (int _attr)
{
    __FOREGROUND = _attr & 0xF;
    __BACKGROUND = _attr >> 4;
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), _attr);
}

void
normvideo (void)
{
    textattr (__text_info.normattr);
}

void
textbackground (int color)
{
    __BACKGROUND = color;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
      __FOREGROUND + (color << 4));
}


void
textcolor (int color)
{
    __FOREGROUND = color;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
      color + (__BACKGROUND << 4));
}


int
wherex (void)
{
    __fill_text_info();
    return __text_info.curx;
}


int
wherey (void)
{
    __fill_text_info();
    return __text_info.cury;
}

char *
getpass (const char * prompt, char * str)
{
    int maxlength = str[0];
    int length = 0;
    int ch = 0;
    int x, y;

    cputs(prompt);
    __fill_text_info();
    x = __text_info.curx;
    y = __text_info.cury;

    while (ch != '\r') {
        ch = getch();
        switch (ch) {
            case '\r' : /* enter */
                break;
            case '\b' : /* backspace */
                if (length > 0) putchxy (x + --length, y, ' ');
                gotoxy (x + length, y);
                break;
            default:
                if (length < maxlength) {
                    putchxy (x + length, y, '*');
                    str[2 + length++] = ch;
                }
        }
    }

    str[1] = length;
    str[2 + length] = '\0';
    return &str[2];
}

void
highvideo (void)
{
    if (__FOREGROUND < DARKGRAY) textcolor(__FOREGROUND + 8);
}

void
lowvideo (void)
{
    if (__FOREGROUND > LIGHTGRAY) textcolor(__FOREGROUND - 8);
}

void
delay (int ms)
{
    Sleep(ms);
}

void
switchbackground (int color)
{
    struct char_info* buffer;
    int i;

    buffer = malloc(__text_info.screenwidth * __text_info.screenheight *
      sizeof(struct char_info));
    _conio_gettext(1, 1, __text_info.screenwidth, __text_info.screenheight,
      buffer);
    for (i = 0; i < __text_info.screenwidth * __text_info.screenheight; i++) {
        unsigned short attr = buffer[i].attr & 0xF;
        buffer[i].attr = (color << 4) | attr;
    }
    puttext(1, 1, __text_info.screenwidth, __text_info.screenheight, buffer);
    free(buffer);
}

void
flashbackground (int color, int ms)
{
    struct char_info* buffer;

    buffer = malloc(__text_info.screenwidth * __text_info.screenheight *
      sizeof(struct char_info));
    _conio_gettext(1, 1, __text_info.screenwidth, __text_info.screenheight,
      buffer);
    switchbackground(color);
    delay(ms);
    puttext(1, 1, __text_info.screenwidth, __text_info.screenheight, buffer);
    free(buffer);
}

void
clearkeybuf (void)
{
    while (kbhit()) {
        getch();
    }
}

#ifdef __cplusplus
}
#endif

//--------------------------------------------------------------------------------------------------------------------------
void bande(void){
    int i;
   for(i=1;i<41;i++){
        textbackground(2);
    printdirection("                ","right",105,i,0);
   }

   }


void decalrectangle(int much)
{int y;
if(much==1){y=11;}
if(much==2){y=21;}
if(much==3){y=31;}
textbackground(0);
textcolor(0);

gotoxy(1,y-10);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y-9);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y-8);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y-7);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y-6);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y-5);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y-4);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y-3);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y-2);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y-1);
delay(10);
textbackground(2);
textcolor(2);
gotoxy(1,y);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+1);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+2);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+3);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+4);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+5);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+6);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+7);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+8);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(1,y+9);

}
void moverect(char mot[4])

{ int i,y;
    if (strcmp(mot,"up")==0){y=35;
    for(i=0;i<25;i++){
    gotoxy(1,y-i);
textcolor(2);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
if(i!=0)
{gotoxy(1,y-i+5);
textbackground(0);
textcolor(0);
  printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
 textbackground(2);
}delay(50);
}}
if(strcmp(mot,"down")==0)
{y=10;
    for(i=0;i<25;i++){
    gotoxy(1,y+i);
textcolor(3);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
if(i!=0)
{gotoxy(1,y+i);
textbackground(15);
textcolor(15);
  printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
 textbackground(3);
}delay(50);
}

}
}
 int readkey(void) //Lit une touche du clavier
{
    int key;
    clearkeybuf();
    key=getch();
    if (key==0){
        key=getch()+256;}
    if( key==224){
        key=getch()+256;}

    return key;
}


void blancln(int nombreln)
{ int i;
for(i=0;i<nombreln;i++){printf(" \n");}
}
void printdirection(char mot[120],char direction[6],int x ,int y ,int delai)//Impression dans une direction donnée
{int i;

    if(strcmp(direction,"up")==0)
{for(i=0;i<strlen(mot);i++)
 {   gotoxy(x,y-i);
     printf("%c",mot[i]);
     delay(delai);

 }
}
    if(strcmp(direction,"down")==0)
    { for(i=0;i<strlen(mot);i++)
    {gotoxy(x,y+i);
     printf("%c",mot[i]);
     delay(delai);
    }

    }
    if(strcmp(direction,"right")==0)
    { for(i=0;i<strlen(mot);i++)
    {gotoxy(x+i,y);
    printf("%c",mot[i]);
    delay(delai);
    }}
    if(strcmp(direction,"left")==0)
    { for(i=0;i<strlen(mot);i++)
    {gotoxy(x-i,y);
    printf("%c",mot[strlen(mot)-i-1]);
    delay(delai);
    }

    }
textbackground(0);}
/***********************************************/
void deplacer_animal(l_animals **tete)
  {
    //Variables
    l_animals *P, *Q;int supp,da; char nom[50];
    //Suppresion memoire
    printf("donner le nom a supprimer\n");
    scanf("%s",nom);
    Acces_animal(*tete,nom,&P,&Q);
    //Traitement
    if(P==NULL){ printf("Animal non existant!\n");}
    else {
        //Si l'enclos est libre on supprime
        aff_adr(Q,asuivant(Q));
        liberer(P);
        supp=1;
        printf("Animal supprime avec succes\n" );

  }
  if(supp==1){
    printf("Suppresion memoire reussie\n");
    supprimer_animal_fichier(nom);
}}

/*******************MODULES DE GESTION*********************/
