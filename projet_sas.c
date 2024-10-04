#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
struct date{
    int jour;
    int mois;
    int annee;
};

struct reservation {
    int  id;
    char nom[20];
    char prenom[20];
    char telephone[20];
    int age;
    int statut;
    struct date date_reservation;
    };

struct reservation reservations[1000];
int nb_reservation = 0;
int id_table[10000];
int id = 110;
int idi;
int conteur_id = 0;
int i,j,d,choix,revenu,verifi;

const char *reset = "\033[0m";
const char *vert = "\033[32m";
const char *rouge = "\033[31m";
const char *jaune = "\033[33m";
const char *bleu = "\033[34m";
const char *magenta = "\033[35m";
const char *cyan = "\033[36m";
const char *blanc = "\033[37m";
const char *gris = "\033[90m";

// la fonction qui generer des id
int generer_id() {
    id++; 
    id_table[conteur_id] = id;
    conteur_id++; 
    return id; }

// la fonction qui verifier le nom 
int nom_verifier(char *nom){
    if (strlen(nom) >= 20) {
        printf("%sLe nom est trop long.%s\n",rouge,reset);
        return 0;}

    for (int i = 0; nom[i] != '\0'; i++) {
        if (!isalpha(nom[i]) && nom[i] != ' ') {
            printf("%sle nom ne doit contenir que des lettres .%s\n",rouge,reset);
            return 0;}
    }
return 1;}

// la fonction qui verifier le numero de telephone
int numero_valide(const char *numero) {
    int longueur = strlen(numero);
    if (longueur != 10) {
        return 0;}

    if (numero[0] != '0' || (numero[1] != '6' && numero[1] != '7')) {
        return 0;}

    for (int i = 0; i < longueur; i++) {
        if (numero[i] < '0' || numero[i] > '9') {
            return 0;}}

    for (int i = 0; i < nb_reservation; i++) {
        if (strcmp(reservations[i].telephone, numero) == 0 ) {
            printf("%sle numero existe deja :%s\n",rouge,reset);
            return 0;} }
    return 1;}

// la fonction qui verifier l'age
int age_valide(int age) {
    if (age >= 0 && age <= 120){
        return 1;}
    else{
        printf("%sce l\'age n\'est pas valide . %s\n",rouge,reset);
        return 0;} 
}

// la fonction qui verifier la date de reservation
int date_valide(int jour, int mois, int annee) {
    int jours[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (annee % 4 ==0) {
        jours[1]=29;}

    if (mois < 1 || mois > 12) {
        return 0;}

    if (jour < 1 || jour > jours[mois - 1]) {
        return 0;}
    
    if (annee < 2020  || annee > 2030){
        return 0;}

    return 1;}

//la fonction qui verifier les entier
int entier_valide(int *entier){
        verifi = scanf("%d",entier);
        if (verifi != 1 ){
            printf("%sentrer un entier s'il te plais .%s\n",rouge,reset);
            while (getchar() != '\n');
            return 0;
        }
        return 1;
}

//la fonction qui trouve une reservation
int trouver_reservation(int reference) {
    for (int i = 0; i < nb_reservation; i++) {
        if (reservations[i].id == reference) {
            return i; 
        }
    }
    return -1;
}

//modifier une reservation
void modifier_reservation() {
    char nouveau_nom[20],nouveau_prenom[20],*nouveau_telephone;
    int nouveau_age,nouveau_statut;
    struct date nouveau_date;
    int reference;
    do {
        printf("entrer la reference de la reservation a modifier : ");
        d = scanf("%d",&reference);
        if (d != 1){
            printf("%sverifier votre reference .%s\n",rouge,reset);
            while (getchar() != '\n');}
    } while (d != 1);

    int index = trouver_reservation(reference);

    if (index != -1) {
        printf("%sModification de la reservation %s%d\n",jaune,reset,reference);
        getchar();
        {debutvnom:
        printf("nouveau nom : ");
        fgets(nouveau_nom,20,stdin);
        nouveau_nom[strcspn(nouveau_nom, "\n")] = '\0';}
        if (!nom_verifier(nouveau_nom)){
            goto debutvnom;}

        {debutvprenom:
        printf("nouveau prenom : ");
        fgets(nouveau_prenom,20,stdin);
        nouveau_prenom[strcspn(nouveau_prenom, "\n")] = '\0';}
        if (!nom_verifier(nouveau_prenom)){
            goto debutvprenom;}
        
        {debutvnumero:
        printf("nouveau numero de telephone : ");
        scanf("%s",nouveau_telephone);
        nouveau_telephone[strcspn(nouveau_telephone, "\n")] = '\0';}
        if (!numero_valide(nouveau_telephone)){
            printf("%sce nomero n\'est pas validie \n%s",rouge,reset);
            goto debutvnumero;}
        
        {debutvage:
        do{
            printf("nouveau age :");
        }while(!entier_valide(&nouveau_age) );
        if(!age_valide(nouveau_age)){
            goto debutvage;}}
        
        {printf("%sStatut de la nouveau reservation :%s\n",jaune,reset);
        printf("1. Valide\n");
        printf("2. Reporte\n");
        printf("3. Annule\n");
        printf("4. Traite\n");
        debutvchoix:
        do{
            printf("Votre choix : ");
        }while(!entier_valide(&nouveau_statut));
        if ( nouveau_statut < 1 || nouveau_statut > 4){
            printf("%schoix invalide :%s\n",rouge,reset);
            goto debutvchoix;
        }}

        {printf("%sDate de reservation :%s\n",jaune,reset);
        debutvdate:
        do{
            printf("Joure : ");
        }while(!entier_valide(&nouveau_date.jour));
        do{
            printf("Mois : ");
        }while(!entier_valide(&nouveau_date.mois));
        do{
            printf("Annee : ");
        }while(!entier_valide(&nouveau_date.annee));

        if (!date_valide(nouveau_date.jour,nouveau_date.mois,nouveau_date.annee)){
            goto debutvdate;
        }}
         
        strcpy(reservations[index].prenom, nouveau_prenom);
        strcpy(reservations[index].nom, nouveau_nom);
        strcpy(reservations[index].telephone, nouveau_telephone);
        reservations[index].statut = nouveau_statut;
        reservations[index].age = nouveau_age;
        reservations[index].date_reservation = nouveau_date;
    } else {
        printf("%sReservation non trouvee.%s\n",rouge,reset);
    }
}

// supprimer une reservation
void supprimer_reservation() {
    int reference;
    do {
        printf("entrer la reference de la reservation a supprimer : ");
        d = scanf("%d",&reference);
        if (d != 1){
            printf("%sverifier votre reference .%s\n",rouge,reset);
            while (getchar() != '\n');}
    } while (d != 1);

    int index = trouver_reservation(reference);

    if (index != -1) {
        for (int i = index; i < nb_reservation - 1; i++) {
            reservations[i] = reservations[i + 1];
        }
        nb_reservation--;
        printf("%sreservation supprimee avec succes.%s\n",vert,reset);
    } else {
        printf("%sreservation non trouvee.%s\n",rouge,reset);
    }
}

// la fonction tri par nom
void tri_nom() {
    for (int i = 1; i < nb_reservation; i++) {
        struct reservation tmp = reservations[i];
        j = i - 1;
        while (j >= 0 && strcmp(tmp.nom , reservations[j].nom) < 0) {
            reservations[j + 1] = reservations[j];
            j--;
        }
        reservations[j + 1] = tmp;
    }
}

// la fonction tri par statut
void tri_statut() {
    for (int i = 1; i < nb_reservation; i++) {
        struct reservation tmp = reservations[i];
        int j = i - 1;
        while (j >= 0 && tmp.statut < reservations[j].statut) {
            reservations[j + 1] = reservations[j];
            j--;
        }
        reservations[j + 1] = tmp;
    }
}

//statut
char *statut(int *n){
    if (*n==1){
        return "valide";
    }else if (*n==2){
        return "reporte";
    }else if (*n==3){
        return "annulee";
    }else if (*n==4){
        return "traite";
    }else {
        return "val";
    }
}

// recherche par id
void rechercher_id() {
    do {
        printf("%sreference :%s ",jaune,reset);
        d = scanf("%d", &idi);
        if (d != 1 || revenu < 0 || revenu > 1){
            printf("%svirifier votre reference .%s\n",rouge,reset);
            while (getchar() != '\n');}
    } while (d != 1 || revenu < 0 || revenu > 5);


    for (i = 0; i < nb_reservation; i++) {
        if (reservations[i].id == idi) {
            char *G=statut(&reservations[i].statut);
                printf("+------+-----------------+-----------------+-----------------+-------+---------+------------+\n");
                printf("| %sID%s   |  %sNom%s            | %sPrenom%s          |  %sTelephone%s      | %sAge%s   | %sStatut%s  | %sDate%s       |\n",bleu,reset,magenta,reset,cyan,reset,jaune,reset,vert,reset,gris,reset,rouge,reset);
                printf("+------+-----------------+-----------------+-----------------+-------+---------+------------+\n");
                printf("| %s%-4d%s | %s%-15s%s | %s%-15s%s |  %s%-13s%s  | %s%-5d%s | %s%-7s%s | %s%02d/%02d/%04d%s |\n", bleu ,reservations[i].id , reset ,
               magenta,reservations[i].nom,reset,
               cyan,reservations[i].prenom,reset,
               jaune,reservations[i].telephone,reset,
               vert,reservations[i].age,reset,
               gris,G,reset,
               rouge,reservations[i].date_reservation.jour,
               reservations[i].date_reservation.mois,
               reservations[i].date_reservation.annee,reset);
               printf("+------+-----------------+-----------------+-----------------+-------+---------+------------+\n");
               d=1;
        }
    }
    if (!d){
    printf("%sce reference n exeste pas.%s",jaune,reset);
}}

// recherche par nom
void recherche_nom(){
    char nom_a_rechercher[20];
    getchar();
    {debutrecherch:
    printf("%secrit le nom a rechercher :%s",jaune,reset);
    fgets(nom_a_rechercher, sizeof(nom_a_rechercher), stdin);
    nom_a_rechercher[strcspn(nom_a_rechercher, "\n")] = '\0';}
    if (!nom_verifier(nom_a_rechercher)){
        goto debutrecherch;
        }
    
    for (i = 0; i < nb_reservation ; i++) {
        if (!strcmp(reservations[i].nom, nom_a_rechercher)) {
            char *D = statut(&reservations[i].statut);
             printf("+------+-----------------+-----------------+-----------------+-------+--------+------------+\n");
                printf("| %sID%s   |  %sNom%s            | %sPrenom%s          |  %sTelephone%s      | %sAge%s   | %sStatut%s | %sDate%s       |\n",bleu,reset,magenta,reset,cyan,reset,jaune,reset,vert,reset,gris,reset,rouge,reset);
                printf("+------+-----------------+-----------------+-----------------+-------+--------+------------+\n");
                printf("| %s%-4d%s | %s%-15s%s | %s%-15s%s |  %s%-13s%s  | %s%-5d%s | %s%-7s%s| %s%02d/%02d/%04d%s |\n", bleu ,reservations[i].id , reset ,magenta,reservations[i].nom,reset,cyan,reservations[i].prenom,reset,jaune,reservations[i].telephone,reset,vert,reservations[i].age,reset,gris,D,reset,rouge,reservations[i].date_reservation.jour,reservations[i].date_reservation.mois,reservations[i].date_reservation.annee,reset);
                printf("+------+-----------------+-----------------+-----------------+-------+--------+------------+\n");
                d=1;}}
    if (!d){
        printf("%sce reference n exeste pas.%s",jaune,reset);
}}

// 1.Ajouter une reservation
void ajouter_reservation() {
    if (nb_reservation == 1000 ) {
        printf("%sLe tableau de réservations est plein.%s\n",rouge,reset);
        return;}
    
    struct reservation nouvelle_reservation;
    getchar();
    {debutnom:
    printf("nom : ");
    fgets(nouvelle_reservation.nom,20,stdin);
    nouvelle_reservation.nom[strcspn(nouvelle_reservation.nom, "\n")] = '\0';}

    if (!nom_verifier(nouvelle_reservation.nom)){
        goto debutnom;}

    {debutprenom:
    printf("prenom : ");
    fgets(nouvelle_reservation.prenom,20,stdin);
    nouvelle_reservation.prenom[strcspn(nouvelle_reservation.prenom, "\n")] = '\0';}
    
    if (!nom_verifier(nouvelle_reservation.prenom)){
        goto debutprenom;}

    {debutnumero:
    printf("numero de telephone : ");
    scanf("%s", nouvelle_reservation.telephone);
    nouvelle_reservation.telephone[strcspn(nouvelle_reservation.telephone, "\n")] = '\0';}

    if (!numero_valide(nouvelle_reservation.telephone)){
        printf("%sce nomero n\'est pas validie \n%s",rouge,reset);
        goto debutnumero;}
    
    {debutage:
    do{
        printf("age :");
        }while(!entier_valide(&nouvelle_reservation.age) );}

    if(!age_valide(nouvelle_reservation.age)){
        goto debutage;}

    {printf("%sStatut de la reservation :%s\n",jaune,reset);
    printf("1. Valide\n");
    printf("2. Reporte\n");
    printf("3. Annule\n");
    printf("4. Traite\n");
    debutchoix:
    do{
        printf("Votre choix : ");
    }while(!entier_valide(&nouvelle_reservation.statut));
    if ( nouvelle_reservation.statut < 1 || nouvelle_reservation.statut > 4){
        printf("%schoix invalide :%s\n",rouge,reset);
        goto debutchoix;
    }}

    {printf("%sDate de reservation :%s\n",jaune,reset);
    debutdate:
    do{
        printf("Joure : ");
    }while(!entier_valide(&nouvelle_reservation.date_reservation.jour));
    do{
        printf("Mois : ");
    }while(!entier_valide(&nouvelle_reservation.date_reservation.mois));
    do{
        printf("Annee : ");
    }while(!entier_valide(&nouvelle_reservation.date_reservation.annee));

    if (!date_valide(nouvelle_reservation.date_reservation.jour,nouvelle_reservation.date_reservation.mois,nouvelle_reservation.date_reservation.annee)){
        printf("%scette date invalide :%s\n",rouge,reset);
        printf("%sentrer la date :%s\n",jaune,reset);
        goto debutdate;
    }}
    int H = generer_id();
    nouvelle_reservation.id = H;

    {reservations[nb_reservation] = nouvelle_reservation;
    nb_reservation++;}
    printf("%sreservation ajoute avec succes !%s\n",vert,reset);}

// 2. Modifier ou supprimer une reservation :
void modifier_supprimer() {
    int choix1;
    printf("%s *******choisir********%s\n",jaune,reset);
    printf("1. Modifier une reservation\n");
    printf("2. Supprimer une reservation\n");
    debutchoix:
    do{
        printf("%sVotre choix :%s ",jaune,reset);
    }while(!entier_valide(&choix1));
    if ( choix1 < 1 || choix1 > 2){
        printf("%schoix invalide :%s\n",rouge,reset);
        goto debutchoix;
    }

    switch (choix1) {
            case 1:
                modifier_reservation();
                break;
            case 2:
                supprimer_reservation();
                break;
            default:
                printf("%sChoix invalide.%s\n",rouge,reset);
        }
}

// 3. Afficher les details d une reservation
void afficher_reservations() {
    printf("                       %sListe des reservation :%s\n",jaune,reset);
    printf("+------+-----------------+-----------------+-----------------+------+---------+------------+\n");
    printf("| %sID%s   |  %sNom%s            | %sPrenom%s          |  %sTelephone%s      | %sAge%s  | %sStatut%s  | %sDate%s       |\n",bleu,reset,magenta,reset,cyan,reset,jaune,reset,vert,reset,gris,reset,rouge,reset);
    printf("+------+-----------------+-----------------+-----------------+------+---------+------------+\n");
    for (int i = 0; i < nb_reservation; i++) {
        char *Z=statut(&reservations[i].statut);
        printf("| %s%-4d%s |",bleu,reservations[i].id , reset);
        printf(" %s%-15s%s |",magenta,reservations[i].nom,reset);
        printf(" %s%-15s%s |",cyan,reservations[i].prenom,reset);
        printf("  %s%-13s%s  |",jaune,reservations[i].telephone,reset);
        printf(" %s%-4d%s |",vert,reservations[i].age,reset);
        printf(" %s%-7s%s |",gris,Z,reset);
        printf(" %s%02d/%02d/%04d%s |\n",rouge,reservations[i].date_reservation.jour,reservations[i].date_reservation.mois,reservations[i].date_reservation.annee,reset);
        printf("+------+-----------------+-----------------+-----------------+------+---------+------------+\n");
        }
}

// 4. Tri des reservations :
void tri_reservation(){
    printf("%s *******choisir********%s\n",jaune,reset);
    printf("1. Tri des reservations par Nom.\n");
    printf("2. Tri des reservations par statut (valide, reporte, annule, traite).\n");
    debuttchoix:
    do{
        printf("%sVotre choix :%s ",jaune,reset);
    }while(!entier_valide(&choix));
    if ( choix < 1 || choix > 2){
        printf("%schoix invalide :%s\n",rouge,reset);
        goto debuttchoix;
    }

    switch (choix) {
            case 1:
                tri_nom();
                afficher_reservations();
                break;
            case 2:
                tri_statut();
                afficher_reservations();
                break;
            default:
                printf("%sChoix invalide.%s\n",rouge,reset);
        }
}

// 5.Recherche des reservations :
void recherche_reservation(){
    printf("%s *******choisir********%s\n",jaune,reset);
    printf("1. rechreche par reference.\n");
    printf("2. recherche par nom.\n");
    debutrecherche:
    do{
        printf("%sVotre choix :%s ",jaune,reset);
    }while(!entier_valide(&choix));
    if ( choix < 1 || choix > 2){
        printf("%schoix invalide :%s\n",rouge,reset);
        goto debutrecherche;
    }

    switch (choix) {
            case 1:
                rechercher_id();
                break;
            case 2:
                recherche_nom();
                break;
            default:
                printf("%sChoix invalide.%s\n",rouge,reset);
        }
}

// 6.Statistiques
void statistique(){
    float somme_age = 0;
    for (int i = 0; i < nb_reservation; i++) {
        somme_age = somme_age + reservations[i].age;}
    float moyen = somme_age / nb_reservation;
    printf("%s la moyenne d'age est  :%s %s%.2f%s %sans%s\n",vert,reset,jaune,moyen,reset,vert,reset);

    int tranches_age[3] = {0}; 

    for (int i = 0; i < nb_reservation; i++) {
        int age = reservations[i].age;
        if (age <= 18) {
            tranches_age[0]++;
        } else if (age <= 35) {
            tranches_age[1]++;
        } else {
            tranches_age[2]++;
        }
    }

    printf("%s****Repartition par tranche d age :****%s\n",vert,reset);
    printf("+-----------------+--------+\n");
    printf("| %sTranche d age%s   | Nombre |\n", bleu, reset);
    printf("+-----------------+--------+\n");
    printf("| 0-18 ans        | %-6d |\n",tranches_age[0]);
    printf("| 19-35 ans       | %-6d |\n",tranches_age[1]);
    printf("| 36+ ans         | %-6d |\n",tranches_age[2]);
    printf("+-----------------+--------+\n");

    int tranches_statut[4] = {0}; 

    for (int i = 0; i < nb_reservation; i++) {
        int stat = reservations[i].statut;
        if (stat == 1) {
            tranches_statut[0]++;
        } else if (stat == 2) {
            tranches_statut[1]++;
        } else if ( stat == 3 ){
            tranches_statut[2]++;
        }else {
            tranches_statut[3]++;
        }
    }
    printf("%s***les statistique de statut***%s\n",vert,reset);
    printf("+-----------------+--------+\n");
    printf("| %sStatut%s          | Nombre |\n", bleu, reset);
    printf("+-----------------+--------+\n");
    for (int i = 0; i < 4; i++) {
        int a=i+1;
        char *S=statut(&a);
        printf("| %s%-15s%s | %-6d |\n", bleu, S, reset, tranches_statut[i]);
    }
    printf("+-----------------+--------+\n");
}

// fonction pricipale
int main(){
    char *noms[10]={"anouar","ali","said","salma","fouad","aziz","zayd","fatima","aicha","mouad"};
    char *prenoms[10]={"alaoui","mahra","bouchta","rgig","afghol","ajdid","myan","bahra","bicho","filali"};
    char *phons[10]={"0612121212","0724242424","0689789878","0723242526","0656575859","0783456234","0609080706","0715234678","0651620763","0763425378"};
    int ages[10]={31,71,12,65,67,23,89,45,98,41};
    int statuts[10]={1, 3, 2, 4, 1, 2, 3, 4, 2, 1};
    int jours[10]={11, 23, 12, 4, 15, 2, 13, 24, 20, 1};
    int mois[10]={11, 3, 7, 4, 1, 2, 5, 9, 2, 12};
    int annees[10]={2020, 2021, 2022, 2023, 2024, 2025, 2026, 2027, 2028, 2029};
    for (int k = 0 ; k < 10 ; k++ ){
        strcpy(reservations[k].nom,noms[k]);
        strcpy(reservations[k].prenom,prenoms[k]);
        strcpy(reservations[k].telephone,phons[k]);
        reservations[k].age=ages[k];
        reservations[k].statut=statuts[k];
        reservations[k].date_reservation.jour=jours[k];
        reservations[k].date_reservation.mois=mois[k];
        reservations[k].date_reservation.annee=annees[k];
        reservations[k].id=generer_id();
        nb_reservation++;
    }
    debut:
    printf("\n%s**********Menu*********%s\n",jaune,reset);
    printf("1. Ajouter une reservation :\n");
    printf("2. Modifier ou supprimer une reservation :\n");
    printf("3. Afficher les details des reservations :\n");
    printf("4. Tri des reservations :\n");
    printf("5. Recherche des reservations :\n" );
    printf("6. Statistiques :\n");
    printf("0. quitter\n");
    do {
        printf("%schoix :%s ",jaune,reset);
        verifi = scanf("%d", &choix);
        if (verifi != 1 || choix < 0 || choix > 6){
            printf("%schoix invalide.%s\n",rouge,reset);
            while (getchar() != '\n');}
            
    } while (verifi != 1 || choix < 0 || choix > 6);
    switch (choix) {
        case 1:
            ajouter_reservation();
            break;
        case 2:
            modifier_supprimer();
            break;
        case 3:
            afficher_reservations();
            break;
        case 4:
            tri_reservation();
            break;
        case 5:
            recherche_reservation();
            break;
        case 6:
            statistique();
            break;
        case 0:
            printf("au revoir!\n");
            break;
        default:
            printf("%sChoix invalide.%s\n", rouge, reset);
            break;}

    printf("%schoisir 0 ou 1 pour quitter ou bien revenir au menu pricipal %s\n",jaune,reset);
    printf("0. quitter le programme\n");
    printf("1. revenir au menu principal\n");
    do {
        printf("%schoix :%s ",jaune,reset);
        d = scanf("%d", &revenu);
        if (d != 1 || revenu < 0 || revenu > 1){
            printf("%svirifier votre choix .%s\n",rouge,reset);
            while (getchar() != '\n');}
    } while (d != 1 || revenu < 0 || revenu > 5);
    if (revenu == 1)
    goto debut ;
    else if (revenu == 0)
    printf("%smerci%s",vert,reset);
    return 0;

}