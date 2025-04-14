#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int cod;
    char* den;
    float pret;
    float cant;
} produs;

typedef struct nodLs {
    produs info;
    struct nodLs* next;
} nodLs;

nodLs* inserare(nodLs* cap, produs p) {
    nodLs* nou = (nodLs*)malloc(sizeof(nodLs));
    if (!nou) return NULL;

    nou->info.cod = p.cod;
    nou->info.pret = p.pret;
    nou->info.cant = p.cant;

    nou->info.den = (char*)malloc((strlen(p.den) + 1) * sizeof(char));
    if (!nou->info.den) {
        free(nou);
        return NULL;
    }
    strcpy(nou->info.den, p.den);

    nou->next = NULL;

    if (cap == NULL) {
        cap = nou;
    }
    else {
        nodLs* aux = cap;
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = nou;
    }
    return cap;
}

void traversare(nodLs* cap) {
    nodLs* aux = cap;
    while (aux != NULL) {
        printf("Cod = %d", aux->info.cod);
        printf(", Denumire = %s", aux->info.den);
        printf(", Pret = %.2f", aux->info.pret);
        printf(", Cantitate = %.2f\n", aux->info.cant);
        aux = aux->next;
    }
}

void dezalocare(nodLs* cap) {
    nodLs* aux = cap;
    while (aux != NULL) {
        nodLs* temp = aux->next;
        free(aux->info.den);
        free(aux);
        aux = temp;
    }
}

int main() {
    int n;
    printf("Numar de produse: ");
    scanf("%d", &n);

    nodLs* cap = NULL;
    produs p;
    char buffer[100]; 


    for (int i = 0; i < n; i++) {
        printf("\nCodul produsului %d: ", i + 1);
        scanf("%d", &p.cod);

        printf("Denumirea produsului %d: ", i + 1);
        scanf("%s", buffer);
        p.den = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(p.den, buffer);

        printf("Pretul produsului %d: ", i + 1);
        scanf("%f", &p.pret);

        printf("Cantitatea produsului %d: ", i + 1);
        scanf("%f", &p.cant);

        cap = inserare(cap, p);
        free(p.den);
    }

 
    FILE* f = fopen("fisier.txt", "r");
    if (!f) {
        printf("Eroare la deschiderea fisierului!\n");
        dezalocare(cap);
        return 1;
    }

    fscanf(f, "%d", &n);

    for (int i = 0; i < n; i++) {
        fscanf(f, "%d", &p.cod);

        fscanf(f, "%s", buffer);
        p.den = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(p.den, buffer);

        fscanf(f, "%f", &p.pret);
        fscanf(f, "%f", &p.cant);

        cap = inserare(cap, p);
        free(p.den);
    }

    fclose(f);

    traversare(cap);
    dezalocare(cap);
    return 0;
}