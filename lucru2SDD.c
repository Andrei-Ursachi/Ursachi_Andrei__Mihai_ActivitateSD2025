#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128


struct Student {
    int id;
    char* nume;
    float medie;
};


struct Nod {
    struct Student st;
    struct Nod* next;
};

struct Nod* inserareLista(struct Nod* p, struct Student s) {
    struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));
    if (!nou) {
        fprintf(stderr, "Eroare la alocarea memoriei!\n");
        exit(EXIT_FAILURE);
    }

    nou->st = s;
    nou->next = p;
    return nou;
}

void parseList(struct Nod* p) {
    while (p) {
        printf("%d %s %.2f\n", p->st.id, p->st.nume, p->st.medie);
        p = p->next;
    }
}

struct Student stergereStudent(struct Nod** p) {
    struct Nod* tmp = *p;
    struct Student s;

    if (tmp) {
        if (tmp->next) {
            while (tmp->next->next)
                tmp = tmp->next;
            s = tmp->next->st;
            free(tmp->next);
            tmp->next = NULL;
        }
        else {
            s = tmp->st;
            free(tmp);
            *p = NULL;
        }
    }

    return s;
}

int main() {
    struct Nod* prim = NULL;
    struct Student stud;
    FILE* f;
    f = fopen("Studenti.txt", "r");
    if (!f) {
        fprintf(stderr, "Nu am putut deschide fisierul!\n");
        return EXIT_FAILURE;
    }

    char* token, file_buf[LINESIZE], sep_list[] = ",\n";
    while (fgets(file_buf, sizeof(file_buf), f)) {
        token = strtok(file_buf, sep_list);
        if (!token) continue;

        stud.id = atoi(token);

        token = strtok(NULL, sep_list);
        if (!token) {
            fprintf(stderr, "Format invalid pentru nume!\n");
            continue;
        }
        stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
        if (!stud.nume) {
            fprintf(stderr, "Eroare la alocarea memoriei pentru nume!\n");
            continue;
        }
        strcpy(stud.nume, token);

        token = strtok(NULL, sep_list);
        if (!token) {
            fprintf(stderr, "Format invalid pentru medie!\n");
            free(stud.nume);
            continue;
        }
        stud.medie = (float)atof(token);
        prim = inserareLista(prim, stud);
    }

    fclose(f);

    printf("\nLista dupa creare:\n");
    parseList(prim);
    if (prim) {
        stud = stergereStudent(&prim);
        printf("\nLista dupa stergere student:\n");
        parseList(prim);
        printf("Student extras: %d %s\n", stud.id, stud.nume);
        free(stud.nume);
    }

    while (prim) {
        stud = stergereStudent(&prim);
        free(stud.nume);
    }

    printf("Lista dupa dezalocare:\n");
    parseList(prim);

    return EXIT_SUCCESS;
}