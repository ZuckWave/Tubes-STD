#include "mll.h"
#include <iostream>

using namespace std;

void menu() {
    cout << "\n=== SISTEM MANAJEMEN TOKO ELEKTRONIK DZAKY DAN GIAN ===" << endl;
    cout << "1. Insert data merek (parent) dari depan/belakang" << endl;
    cout << "2. Tampilkan semua data merek" << endl;
    cout << "3. Hapus data merek dan modelnya" << endl;
    cout << "4. Cari data merek" << endl;
    cout << "5. Insert data model (child)" << endl;
    cout << "6. Ubah data merek/model" << endl;
    cout << "7. Tampilkan seluruh data merek dan modelnya" << endl;
    cout << "8. Cari data model pada merek tertentu" << endl;
    cout << "9. Hapus data model pada merek tertentu" << endl;
    cout << "10. Hitung banyaknya model/seri" << endl;
    cout << "0. Keluar" << endl;
    cout << "Pilihan: ";
}

int main() {
    ListParent LP;
    listChild LC;
    createListParent(LP);
    createListChild(LC);
    adrC C;
    adrP P;

    int choice = 0;
    string namaMerek, model, posisi, parentMerek;
    int stock;
    int jumlahMerek, jumlahModel;

    do {
        menu();
        cin >> choice;
        cout << endl;

        switch(choice) {
            case 1: {
                cout << "Masukkan berapa banyak merek yang ingin dimasukkan: ";
                cin >> jumlahMerek;

                for (int i = 1; i <= jumlahMerek; i++) {
                    cout << "Masukkan nama merek ke-" << i << ": ";
                    cin >> namaMerek;
                    cout << "Masukkan posisi (Depan/Belakang): ";
                    cin >> posisi;

                    adrP P = createElementParent(namaMerek);
                    if (posisi == "Depan") {
                        insertFirstParent(LP, P);
                        cout << "Merek " << namaMerek << " berhasil ditambahkan di depan!" << endl;
                    } else if (posisi == "Belakang") {
                        insertLastParent(LP, P);
                        cout << "Merek " << namaMerek << " berhasil ditambahkan di belakang!" << endl;
                    } else {
                        cout << "Posisi tidak valid! Gunakan 'Depan' atau 'Belakang'." << endl;
                    }
                }
                break;
            }
            case 2: {
                cout << "=== DAFTAR MEREK ===" << endl;
                showDataParent(LP);
                break;
            }
            case 3: {
                cout << "Masukkan nama merek yang akan dihapus: ";
                cin >> namaMerek;
                adrP P = first(LP);
                bool found = false;

                while (P != NULL && !found) {
                    if (info(P).namaMerek == namaMerek) {
                        found = true;
                        deleteParentChild(LP, LC, P);
                        cout << "Merek dan semua modelnya berhasil dihapus!" << endl;
                    } else {
                        P = next(P);
                    }
                }

                if (!found) {
                    cout << "Merek tidak ditemukan!" << endl;
                }
                break;
            }
            case 4: {
                cout << "Masukkan nama merek yang dicari: ";
                cin >> namaMerek;
                findDataParent(LP, namaMerek);
                break;
            }
            case 5: {
                cout << "Masukkan nama merek untuk model baru: ";
                cin >> parentMerek;
                adrP P = first(LP);
                bool found = false;

                while (P != NULL && !found) {
                    if (info(P).namaMerek == parentMerek) {
                        found = true;
                        cout << "Masukkan berapa banyak model yang ingin dimasukkan untuk merek " << parentMerek << ": ";
                        cin >> jumlahModel;
                    } else {
                        P = next(P);
                    }
                }
                for (int i = 1; i <= jumlahModel; i++) {
                            cout << "Masukkan nama model ke-" << i << " untuk merek " << parentMerek << ": ";
                            cin >> model;
                            cout << "Masukkan jumlah stok: ";
                            cin >> stock; //for diluar while aja

                            adrC C = createElementChild(model, stock);
                            C->nextCP = P;  // Link child ke parent
                            insertFirstChild(LC, C);
                            cout << "Model " << model << " berhasil ditambahkan untuk merek " << parentMerek << "!" << endl;
                }

                if (!found) {
                    cout << "Merek " << parentMerek << " tidak ditemukan!" << endl;
                }
                break;
            }
            case 6: {
                cout << "Masukkan nama merek: ";
                cin >> namaMerek;
                adrP P = first(LP);
                bool found = false;

                while (P != NULL && !found) {
                    if (info(P).namaMerek == namaMerek) {
                        found = true;
                        adrC C = first(LC);
                        bool childFound = false;

                        while (C != NULL && !childFound) {
                            if (C->nextCP == P) {
                                childFound = true;
                                updateParentChild(LP, LC, P, C);
                            } else {
                                C = next(C);
                            }
                        }

                        if (!childFound) {
                            cout << "Tidak ada model untuk merek ini!" << endl;
                        }
                    } else {
                        P = next(P);
                    }
                }

                if (!found) {
                    cout << "Merek tidak ditemukan!" << endl;
                }
                break;
            }
            case 7: {
                cout << "=== DAFTAR MEREK DAN MODEL ===" << endl;
                showParentChild(LP, LC);
                break;
            }
            case 8: {
                findDataChild(LC);
                break;
            }
            case 9: {
                cout << "Masukkan nama model yang akan dihapus: ";
                cin >> model;
                adrC C = first(LC);
                bool found = false;

                while (C != NULL && !found) {
                    if (info(C).model == model) {
                        found = true;
                        deleteChild(LC, C);
                    } else {
                        C = next(C);
                    }
                }

                if (!found) {
                    cout << "Model tidak ditemukan!" << endl;
                }
                break;
            }
            case 10: {
                hitungModel(LP, LC);
                break;
            }
            case 0: {
                cout << "Terima kasih!" << endl;
                break;
            }
            default: {
                cout << "Pilihan tidak valid!" << endl;
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
