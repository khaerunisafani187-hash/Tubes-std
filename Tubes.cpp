#include "Tubes.h"

void createList(ListParent &L) {
    L.first = nullptr;
}

// OPERASI WAJIB PARENT (KONSER)
adrParent createParent(string idKonser, string namaArtis, string tanggal, int kapasitas) {
    adrParent P = new elmParent;
    P->info.idKonser = idKonser;
    P->info.namaArtis = namaArtis;
    P->info.tanggal = tanggal;
    P->info.kapasitas = kapasitas;
    P->next = nullptr;
    P->firstChild = nullptr;
    return P;
}

void insertParent(ListParent &L, adrParent P) {
    if (findParent(L, P->info.idKonser) != nullptr) {
        cout << "ID Konser " << P->info.idKonser << " sudah terdaftar." << endl;
    } else if (L.first == nullptr) {
        L.first = P;
    } else {
        adrParent Q = L.first;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

adrParent findParent(ListParent L, string idKonser) {
    adrParent P = L.first;
    while (P != nullptr && P->info.idKonser != idKonser) {
       P = P->next;  
    }
    return P;
}

void deleteParent(ListParent &L, string idKonser) {
    adrParent P = L.first;
    adrParent prev = nullptr;

    while (P != nullptr && P->info.idKonser != idKonser) {
        prev = P;
        P = P->next;
    }

    if (P == nullptr) {
        cout << "Konser dengan ID " << idKonser << " tidak ditemukan." << endl;
    } else {
        // Hapus semua node Child milik Parent terlebih dahulu (mencegah memory leak)
        adrChild C = P->firstChild;
        while (C != nullptr) {
            adrChild temp = C;
            C = C->next;
            delete temp;
        }
        P->firstChild = nullptr;

        // Lepaskan node Parent dari ListParent
        if (P == L.first) {
            L.first = P->next;
        } else {
            prev->next = P->next;
        }
        delete P;
        cout << "Konser " << idKonser << " beserta seluruh tiketnya berhasil dihapus." << endl;
    }
}

void printParent(ListParent L) {
    if (L.first == nullptr) {
        cout << "Daftar konser masih kosong." << endl;
    } else {
        adrParent P = L.first;
        int i = 1;
        while (P != nullptr) {
            cout << i << ". [" << P->info.idKonser << "] " << P->info.namaArtis
                 << " | Tanggal: " << P->info.tanggal
                 << " | Kapasitas: " << P->info.kapasitas
                 << " (Sisa Kuota: " << cekSisaKuota(P) << ")" << endl;
            P = P->next;
            i++;
        }
    }
}

// OPERASI WAJIB CHILD (TIKET PENONTON)
adrChild createChild(string noTiket, string namaPembeli, string kategori, int harga) {
    adrChild P = new elmChild;
    P->info.noTiket = noTiket;
    P->info.namaPembeli = namaPembeli;
    P->info.kategori = kategori;
    P->info.harga = harga;
    P->next = nullptr;
    return P;
}

void insertChild(adrParent P, adrChild C) {
    if (P == nullptr) {
        cout << "Konser tidak ditemukan, tiket " << endl;
    } else if (cekSisaKuota(P) <= 0) {
        cout << "Kuota konser " << P->info.namaArtis << " sudah penuh, tiket " << C->info.noTiket << " ditolak." << endl;
    } else if (findChild(P, C->info.noTiket) != nullptr) {
        cout << "Tiket " << C->info.noTiket << " sudah terdaftar pada konser " 
             << P->info.namaArtis << "." << endl;
    } else {
        if (P->firstChild == nullptr) {
            P->firstChild = C;
        } else {
            adrChild Q = P->firstChild;
            while (Q->next != nullptr) {
                Q = Q->next;
            }
            Q->next = C;
        }
        cout << "Tiket " << C->info.noTiket << " " << C->info.namaPembeli << " berhasil ditambahkan ke konser "
             << P->info.idKonser << "." << endl;
    }
}

adrChild findChild(adrParent P, string noTiket) {
    if (P == nullptr) {
        return nullptr;
    }

    adrChild C = P->firstChild;
    while (C != nullptr && C->info.noTiket != noTiket) {
        C = C->next;
    }
    return C;
}

void deleteChild(adrParent P, string noTiket) {
    if (P == nullptr || P->firstChild == nullptr) {
        cout << " Data konser tidak ditemukan atau belum memiliki tiket." << endl;
    } else {
        adrChild C = P->firstChild;
        adrChild prev = nullptr;

        while (C != nullptr && C->info.noTiket != noTiket) {
            prev = C;
            C = C->next;
        }

        if (C == nullptr) {
            cout << "Tiket " << noTiket << " tidak ditemukan pada konser " << P->info.idKonser << "." << endl;
        } else {
            if (C == P->firstChild) {
                P->firstChild = C->next;
            } else {
                prev->next = C->next;
            }
            delete C;
            cout << "Tiket " << noTiket << " berhasil dihapus dari konser " << P->info.idKonser << "." << endl;
        }
    }
}


void printChild(adrParent P) {
    if (P == nullptr) {
        cout << "Konser tidak ditemukan." << endl;  
    } else if (P->firstChild == nullptr) {
        cout << " Belum ada penonton yang membeli tiket " << endl;
    } else {
        adrChild C = P->firstChild;
        while (C != nullptr) {
            cout << "   -> [" << C->info.noTiket << "] " << C->info.namaPembeli
                 << " | Kategori: " << C->info.kategori
                 << " | Harga: Rp" << C->info.harga << endl;
            C = C->next;
        }
    }
}

// ==========================================
// TRAVERSAL SELURUH STRUKTUR (PRINT ALL)
// ==========================================

void printAll(ListParent L) {
    if (L.first == nullptr) {
        cout << "Data Multi Linked List kosong." << endl;
    } else {
        adrParent P = L.first;
        while (P != nullptr) {
            cout << "========================================================" << endl;
            cout << "KONSER : [" << P->info.idKonser << "] " << P->info.namaArtis << endl;
            cout << "Tanggal: " << P->info.tanggal
                 << " | Terisi: " << hitungJumlahTiket(P) << "/" << P->info.kapasitas
                 << " | Sisa Kuota: " << cekSisaKuota(P) << endl;
            cout << "Daftar Tiket Penonton:" << endl;
            printChild(P);
            cout << "Total Pendapatan Konser: Rp" << hitungTotalPendapatan(P) << endl;
            P = P->next;
        }
        cout << "========================================================" << endl;
    }
}

// 3 FITUR KREATIF
// Helper untuk menghitung jumlah tiket terjual pada 1 Parent
int hitungJumlahTiket(adrParent P) {
    int jumlah = 0;
    if (P != nullptr) {
        adrChild C = P->firstChild;
        while (C != nullptr) {
            jumlah++;
            C = C->next;
        }
    }
    return jumlah;
}

// Fitur Kreatif 1: Cek sisa kuota kapasitas venue
int cekSisaKuota(adrParent P) {
    if (P == nullptr) {
        return 0;
    }
    return P->info.kapasitas - hitungJumlahTiket(P);
}

// Fitur Kreatif 2: Hitung total pendapatan (revenue) per konser
int hitungTotalPendapatan(adrParent P) {
    int total = 0;
    if (P != nullptr) {
        adrChild C = P->firstChild;
        while (C != nullptr) {
            total = total + C->info.harga;
            C = C->next;
        }
    }
    return total;
}

// Fitur Kreatif 3: Filter dan tampilkan seluruh penonton kategori VIP
void printPenontonVIP(ListParent L) {
    adrParent P = L.first;
    bool ketemu = false;

    while (P != nullptr) {
        adrChild C = P->firstChild;
        while (C != nullptr) {
            if (C->info.kategori == "VIP") {
                cout << "- [" << C->info.noTiket << "] " << C->info.namaPembeli
                     << " | Konser: " << P->info.namaArtis
                     << " | Harga: Rp" << C->info.harga << endl;
                ketemu = true;
            }
            C = C->next;
        }
        P = P->next;
    }

    if (!ketemu) {
        cout << "Tidak ada penonton kategori VIP." << endl;
    }
}