
#include "project.h"
#include <time.h>
time_t deadlineTime;
time_t currentTime;

void    add_task(){
    int pl = iden;
    book[pl].remaining_days = 0;
    book[pl].id = ++iden;
    char buffer[500];
    int  loop = 0;
    char status;
    while (loop <= 1){
        switch(loop){
            case 0 : printf("Veuillez entrer un titre pour la nouvelle tache : \n"); break;
            case 1 : printf("Veuillez entrer une description pour la nouvelle tache : \n"); break;
            default: break;
        }
        scanf("%s", buffer);
        switch (loop)
        {
        case 0 : strcpy(book[pl].titre, buffer); bzero(buffer, sizeof(buffer)); break;
        case 1 : strcpy(book[pl].description, buffer); bzero(buffer, sizeof(buffer)); break;
        default:
            break;
        }
        loop++;
    }
    printf("Veuillez rentrer le status de votre tache -R = À Realiser, E = En-cours, F = Finalisée- : \n");
    scanf("%s", &status);
    switch(status){
        case 'R' : book[pl].real = true; break;
        case 'E' : book[pl].en_cours = true; break;
        case 'F' : book[pl].final = true; break;
        default : break;
    }
    printf("Veuillez entrer la date limite de la tâche (format : AAAA-MM-JJ HH:MM:SS) : \n");
    scanf(" %19s", buffer);

    // Convertir la chaîne de caractères en structure tm
    struct tm timeInfo;
   strptime(buffer, "%Y-%m-%d", &timeInfo);

    // Convertir la structure tm en time_t 1970 tl ldat li3tih
    deadlineTime = mktime(&timeInfo);

    // Obtenir le temps actuel 1970 dbq
    time(&currentTime);

    // Calculer la différence entre le temps actuel et la date limite en jours
    time_t diff = deadlineTime - currentTime;//seconde
    int remainingDays = diff / (24 * 60 * 60);// chehal b9i ta3 lesjour
    book[pl].remaining_days = remainingDays;

    strcpy(book[pl].deadline, buffer);
    bzero(buffer, sizeof(buffer));
}

void add_many(){
int c ;
    while (1)
    {
        add_task();
        printf("Voulez vous rajouter une nouvelle tache entrez 1 pour continuer autre que 1 pour revenir aux options :\n");
        scanf("%d",&c);
        if(c != 1)
            break;
    }
    return;
}
void delete_task(int task_id) {
    if(!iden){
        printf("Aucune tache à supprimer\n");
        return;
    }
    for (int i = 0; i < iden; i++) {
        if (book[i].id == task_id) {
            // Suppression de la tâche en décalant les éléments suivants dans le tableau
            for (int j = i; j < iden - 1; j++) {
                book[j] = book[j + 1];
            }

            iden--; // Décrémentation du nombre de tâches
            printf("La tâche avec l'identifiant %d a été supprimée.\n", task_id);
            return;
        }
    }

    printf("Aucune tâche trouvée avec l'identifiant %d.\n", task_id);
}
void search_taskid(){
    int serchid;
    printf("entre id");
    scanf("%d",&serchid);
    for (int i = 0; i < iden; i++) {
        if (book[i].id == serchid) {
            printf("Tâche trouvée :\n");
            printf("Identifiant : %d\n", book[i].id);
            printf("Titre : %s\n", book[i].titre);
            printf("Description : %s\n", book[i].description);
            printf("Date limite : %s\n", book[i].deadline);
            if(book[i].final && !book[i].en_cours && !book[i].real)
                printf("la tache est finalisé.\n");
            else if(!book[i].final && book[i].en_cours && !book[i].real)
                printf("la tache est en cours de réalisation\n");
            else if(!book[i].final && !book[i].en_cours && book[i].real)
                printf("la tache est a réaliser\n");
        }    
    }
    printf("Aucune tâche trouvée avec l'identifiant %d.\n",serchid );
}
void search_title(char* title) {
    for (int i = 0; i < iden; i++) {
        if (strcmp(book[i].titre, title) == 0) {
            printf("Tâche trouvée :\n");
            printf("Identifiant : %d\n", book[i].id);
            printf("Titre : %s\n", book[i].titre);
            printf("Description : %s\n", book[i].description);
            printf("Date limite : %s\n", book[i].deadline);
            if(book[i].final && !book[i].en_cours && !book[i].real)
                printf("la tache est finalisé\n");
            else if(!book[i].final && book[i].en_cours && !book[i].real)
                printf("la tache est en cours de réalisation\n");
            else if(!book[i].final && !book[i].en_cours && book[i].real)
                printf("la tache est a réaliser\n");
        }
    }
    printf("Aucune tâche trouvée avec le titre \"%s\".\n", title);
}
void search_task(){
    int d;
    char f[100];
        printf("Afin de chercher une tache à partir de son id : Entrez 1\nAfin de chercher une tache à partir de son titre : Entrez 2\n");
        scanf("%d",&d);
        if(!iden){
        printf("Aucune tache à rechercher\n");
        return;}
        switch(d){
            case 1 :search_taskid();break;
            case 2 :
            {
                printf("entre vos status");
                scanf("%s",f);
                search_title(f);break;
            }
            default : break; 
}
}
// comparaison et tri des titres par alpha des taches
void insertionSort() {
    int i, j;
    t_tache key;

    for (i = 1; i < iden; i++) {
        key = book[i];
        j = i - 1;

        while (j >= 0 && strcmp(book[j].titre, key.titre) > 0) {
            book[j+1] = book[j];
            j = j - 1;
        }
        book[j+1] = key;
    }
}
// comparaison et tri des deadlines
void insertionSortDDL(){
    int i, j;
    t_tache key;

    for (i = 1; i < iden; i++) {
        key = book[i];
        j = i - 1;

        while (j >= 0 && book[j].remaining_days > key.remaining_days) {
            book[j+1] = book[j];
            j = j - 1;
        }
        book[j+1] = key;
    }
}
    
void    printelements(int mode){
    if(!mode){
        for (int i = 0; i != iden; i++){
            printf("L'identificateur de la tache est %d\n Le titre de la tache est %s\n La description de la tache est %s\n Le deadline de la tache est %s\n Les jours restants pour le deadline est %d\n",book[i].id,book[i].titre,book[i].description,book[i].deadline,book[i].remaining_days);
            if (book[i].real && !book[i].en_cours && !book[i].final )
                printf("La tache n'a toujours pas été commencé.\n");
            else if (book[i].en_cours && !book[i].final && !book[i].real )
                printf("La tache est en cours de réalisation.\n");
            else if (book[i].final && !book[i].real && !book[i].en_cours )
                printf("La tache a été finalisé.\n");
        }
    }
    else{
        for (int i = 0; i != iden; i++){
            if (book[i].remaining_days <= 3){
                printf("** LES TACHES URGENTES : *** \nL'identificateur de la tache est %d\n Le titre de la tache est %s\n La description de la tache est %s\n Le deadline de la tache est %s\n Les jours restants pour le deadline est %d\n",book[i].id,book[i].titre,book[i].description,book[i].deadline,book[i].remaining_days);
                if (book[i].real && !book[i].en_cours && !book[i].final )
                    printf("La tache n'a toujours pas été commencé.\n");
                else if (book[i].en_cours && !book[i].final && !book[i].real )
                    printf("La tache est en cours de réalisation.\n");
                else if (book[i].final && !book[i].real && !book[i].en_cours )
                    printf("La tache a été finalisé.\n");
            }
        }
    }
}
void show_statistics(){
    if(!iden){
        printf("Aucune tache n est prevu\n");
    return;}
    int d;
    int i =0;
    d=0;
    while(i < iden){
        if(book[i].final)
          d++;
        i++;
    }
printf("le nombre total des tâches est : %d\n",iden );
printf("le nombre de tâches complètes est %d incomplètes: %d\n",d, iden - d );
i = 0;
while(i < iden){
    if (!book[i].final)
        printf("Le nombre de jours restants pour la tache dont id : %d  est : %d \n",book[i].id, book[i].remaining_days);
    i++;
}
}
void modify_task()
{
   
    int id = 0;
    char buffer[600];
    int i = 0;
    printf("Quelle tache voulez vous modifier, rentrez un identifiant 1-600 \n");
    scanf("%d", &id);
    if(!iden || iden < id){
        printf("Aucune tache à modifier\n");
      return;}
    for(i = 0; book[i].id != id; i++){}
    while (1){
        printf("Entrez 1 pour changer la description, 2 pour le status et 3 pour le deadline, 0 si vous ne voulez rien changer\n");
        scanf("%d", &id);
        switch(id){
            case 0 : return;break;
            case 1 : {
                printf("Rentrez la nouvelle description!\n");
                scanf("%s", buffer);
                bzero(book[i].description, sizeof(book[i].description));
                strcpy(book[i].description, buffer);
                bzero(buffer, sizeof(buffer));
                break;
            } 
            case 2 :
            {
                char S[10];
                printf("Rentrez le nouveau status\n R ou E ou F\n");
                scanf("%s", S);
                switch(S[0]){
                    case 'R' :{
                        book[i].final = false;
                        book[i].en_cours = false;
                        book[i].real = true;
                        break;
                    }
                    case 'E' :{
                        book[i].final = false;
                        book[i].real = false;
                        book[i].en_cours = true;
                        break;
                    }
                    case 'F' :{
                        book[i].en_cours = false;
                        book[i].real = false;
                        book[i].final = true;
                        break;
                    }
                }
                break;
            }
            case 3 :
            {
                printf("Rentrez le nouveau deadline\n");
                scanf("%s", buffer);
                bzero(book[i].deadline, sizeof(book[i].deadline));
                strcpy(book[i].deadline, buffer);
                bzero(buffer, sizeof(buffer));
                break;
            }
            default : break;
        }
    }  
}
void show_tasks()
{
    int s;
    printf("Rentrez 1 pour un affichage par ordre alphabetiques des taches \nRentrez 2 pour un affichage par Deadline \nRentrez 3 pour un affichage normal des taches\n" );
    scanf("%d",&s);
    if(!iden){
        printf("Aucune tache à afficher\n");
        return;
    }
    switch (s){
        case 1:insertionSort();printelements(0);break;
        case 2:insertionSortDDL();printelements(0);break;
        case 3: printelements(1);break;
    }
}

int main(){
    bzero(book, sizeof(book));
    int num = 0;
    do {
        printf("******************************************************************\n");
        printf("Veuillez entrer un nombre de 1-7, 8 si vous voulez quitter le programme\n");
        printf("1.Pour ajouter une tache.\n");
        printf("2.Pour ajouter plusieurs taches à la fois.\n");
        printf("3.Pour afficher la liste des taches.\n");
        printf("4.Pour modifier une tache.\n");
        printf("5.Pour supprimer une tache.\n");
        printf("6.Pour recherche une tache.\n");
        printf("7.Pour avoir les statistiques des taches.\n");
        printf("8.Pour quitter le programme.\n");
        printf("******************************************************************\n");
        scanf("%d",&num);
        switch(num){
            case 1 : add_task(); printf("Vous avez ajouté une tache.\n");break; 
            case 2 : add_many(); printf("Vous avez ajouté plusieurs taches\n"); break;
            case 3 : show_tasks(); break;
             case 4 : modify_task(); break;
            case 5 : printf("Veuillez entrer l'identifiant de la tâche à supprimer : ");
                     int task_id;
                     scanf("%d", &task_id);
                     delete_task(task_id);
                     break;
            case 6 : search_task();break;
            case 7 : show_statistics();break;
            case 8 : printf("Vous avez quitte le programme\n"); exit(0);
            default : printf("Erreur d'Input\n"); break;
        }
       
    } while(1);
    
}