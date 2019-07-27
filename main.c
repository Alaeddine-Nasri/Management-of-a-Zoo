#include <stdio.h>
#include <stdlib.h>
#include "BIBLIO_TP.h"


main()
{

    l_enclos *P=NULL; l_dangereux *Q=NULL; l_animals *R=NULL,*s=NULL; l_affect_depart *F,*B;

    cree_llc_enclos(&P);cree_llc_ani(&R);creation_affectation(&F);cree_llc_dangereux(&Q);

    intro();
        chaine lechoix[]={"   >>         AFFICHER LES LISTES           <<   ",
                          "   >>         GESTION DES ANIMAUX           <<   ",
                          "   >>         GESTION DES ENCLOS            <<   ",
                          "   >>         RECHERCHE ANIMAUX             <<   ",
                          "   >>    AUTRES FONCTIONS DE GESTIONS       <<   ",
                          "   >>                 EXIT                  <<   ",};
    menu(lechoix,R,P,F,Q);
    return 0;
}
