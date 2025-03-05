
#include<stdio.h>
#include<string.h>
#include<malloc.h>
typedef struct Casa Casa;
typedef struct Nod Nod;


struct Casa {
	int nrPereti;
	char* tipAcoperis;
};

struct Nod {
	Casa info;
	Nod*next;
};

Casa createCasa(const char* tipAcoperis, int nrPereti) {
	Casa casa;
	casa.tipAcoperis = (char*)malloc(sizeof(char) * (strlen(tipAcoperis) + 1));
	strcpy(casa.tipAcoperis, tipAcoperis);
	casa.nrPereti = nrPereti;
	return casa;
}

Nod* createNod(Casa casa, Nod* next) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = casa;
	nou->next = next;
	return nou;
}

Nod* inserareSfarsit(Nod* cap, Casa casa) {
	Nod* nou = createNod(casa, NULL);
	if (cap) {
		Nod* temp = cap;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
	else {
		cap = nou;
	}
	return cap;
}

void afisareCasa(Casa casa) {
	printf("Casa %s are %d pereti.\n", casa.tipAcoperis, casa.nrPereti);
}

void afisareListaCase(Nod* cap) {
	while (cap) {
		afisareCasa(cap->info);
		cap = cap->next;
	}
}

Nod* inserareInceput(Nod* cap, Casa casa) {
	Nod* nou = createNod(casa, cap);
	return nou;
}

Nod* mediePereti(Nod* cap) {
	if (cap) {
		int nr = 0;
		int r = 0;
		while (cap) {
			nr++;
			r += cap->info.nrPereti;
			cap = cap->next;
		}
		return r / nr;
	}
	else {
		return 0;
	}
}

void stergereLista(Nod* cap) {
	while (cap) {
		Nod* aux = cap;
		cap = cap->next;
		free(aux->info.tipAcoperis);
		free(aux);
	}
	return cap;
}

void main() {
	Casa casa = createCasa("faraPereti", 1);
	Nod* node = createNod(casa, NULL);
	Nod* cap = NULL;
	cap = inserareSfarsit(cap, createCasa("Mansarda", 10));
	cap = inserareSfarsit(cap, createCasa("Fluture", 12));
	cap = inserareSfarsit(cap, createCasa("Plat", 6));
	cap = inserareSfarsit(cap, createCasa("Panta", 10));

	afisareListaCase(cap);
	cap = inserareInceput(cap, createCasa("Panta inegala", 16));

	afisareListaCase(cap);
	printf("%5.2f", mediePereti(cap));


}
