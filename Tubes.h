#ifndef MLL_H_INCLUDED
#define MLL_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

struct Konser {
    string idKonser;
    string namaArtis;
    string tanggal;
    int kapasitas;
};

struct Tiket {
    string noTiket;
    string namaPembeli;
    string kategori; 
    int harga;
};

typedef struct elmChild *adrChild;
typedef struct elmParent *adrParent;

struct elmChild {
    Tiket info;
    adrChild next;
};

struct elmParent {
    Konser info;
    adrParent next;
    adrChild firstChild;
};

struct ListParent {
    adrParent first;
};

void createList(ListParent &L);

adrParent createParent(string idKonser, string namaArtis, string tanggal, int kapasitas);
void insertParent(ListParent &L, adrParent P);
adrParent findParent(ListParent L, string idKonser);
void deleteParent(ListParent &L, string idKonser);
void printParent(ListParent L);

adrChild createChild(string noTiket, string namaPembeli, string kategori, int harga);
void insertChild(adrParent P, adrChild C);
adrChild findChild(adrParent P, string noTiket);
void deleteChild(adrParent P, string noTiket);
void printChild(adrParent P);
void printAll(ListParent L);

int hitungJumlahTiket(adrParent P);
int cekSisaKuota(adrParent P);
int hitungTotalPendapatan(adrParent P);
void printPenontonVIP(ListParent L);

#endif //TUBES_H_INCLUDED