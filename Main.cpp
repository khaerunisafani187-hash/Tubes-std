#include "Tubes.h"

int main() {
    ListParent L;
    createList(L);

    cout << "1. INSERT DATA PARENT (3 KONSER)" << endl;
    // Kapasitas K01 dibuat 3 agar bisa langsung menguji validasi kuota penuh
    insertParent(L, createParent("K01", "aespa SYNK:COMPLaeXITY", "14-12-2026", 3));
    insertParent(L, createParent("K02", "NMIXX 1ST WORLD TOUR <EPISODE 1: ZERO FRONTIER>", "20-12-2026", 5));
    insertParent(L, createParent("K03", "TWICE <THIS IS FOR> World Tour", "28-12-2026", 4));
    printParent(L);

    cout << "\n2. INSERT DATA CHILD (6 TIKET + UJI KUOTA PENUH)" << endl;
    adrParent p1 = findParent(L, "K01");
    adrParent p2 = findParent(L, "K02");
    adrParent p3 = findParent(L, "K03");

    // 3 Tiket masuk ke K01 (kapasitas 3 -> langsung penuh)
    insertChild(p1, createChild("T001", "Yu Jimin", "VIP", 3200000));
    insertChild(p1, createChild("T002", "Seol Yoon-a", "Reguler", 1600000));
    insertChild(p1, createChild("T003", "Minatozaki Sana", "VIP", 3200000));

    // Uji Fitur Kreatif (Cek Kuota Otomatis): mencoba tambah tiket ke-4 di K01
    insertChild(p1, createChild("T004", "Danielle Mars", "Reguler", 1600000));

    // 2 Tiket masuk ke K02
    insertChild(p2, createChild("T005", "Hanni Pham", "VIP", 2500000));
    insertChild(p2, createChild("T006", "Kang Hae-Rin", "Reguler", 1200000));

    // 1 Tiket masuk ke K03
    insertChild(p3, createChild("T007", "Kim Min-Jeong", "Reguler", 850000));

    cout << "\n3. PRINT ALL (SELURUH STRUKTUR MLL)" << endl;
    printAll(L);

    cout << "\n4. UJI SEARCH PARENT & SEARCH CHILD" << endl;
    adrParent cariP = findParent(L, "K02");
    if (cariP != nullptr) {
        cout << "Parent ditemukan: " << cariP->info.namaArtis
             << " (" << cariP->info.tanggal << ")" << endl;

        adrChild cariC = findChild(cariP, "T005");
        if (cariC != nullptr) {
            cout << "Child ditemukan di K02: " << cariC->info.namaPembeli
                 << " - Kategori " << cariC->info.kategori << endl;
        }
    }

    if (findParent(L, "K99") == nullptr) {
        cout << "Pencarian ID K99: Konser tidak ditemukan (sesuai harapan)." << endl;
    }

    cout << "\n5. UJI FITUR KREATIF: FILTER PENONTON VIP" << endl;
    printPenontonVIP(L);

    cout << "\n6. UJI DELETE CHILD (HAPUS T002 DARI K01)" << endl;
    deleteChild(p1, "T002");
    cout << "Daftar tiket K01 setelah T002 dihapus (Sisa Kuota sekarang: "
         << cekSisaKuota(p1) << "):" << endl;
    printChild(p1);
    cout << "Total pendapatan terbaru K01: Rp" << hitungTotalPendapatan(p1) << endl;

    cout << "\n7. UJI DELETE PARENT (HAPUS KONSER K03)" << endl;
    deleteParent(L, "K03"); 

    cout << "\n8. PRINT ALL AKHIR (HASIL VERIFIKASI)" << endl;
    printAll(L);

    return 0;
}