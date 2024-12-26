#include "mll.h"
#include <iostream>
using namespace std;

void createListParent(ListParent &L) {
    first(L) = NULL;
    last(L) = NULL;
}

adrP createElementParent(string namaMerek) {
    adrP P = new elmP;
    info(P).namaMerek = namaMerek;
    next(P) = NULL;
    prev(P) = NULL;
    return P;
}

void createListChild(listChild &L) {
    first(L) = NULL;
}

adrC createElementChild(string model, int stock) {
    adrC C = new elmC;
    info(C).model = model;
    info(C).stock = stock;
    next(C) = NULL;
    C->nextCP = NULL;
    return C;
}

void insertFirstParent(ListParent &L, adrP P) {
    if (first(L) != NULL) {
        next(P) = first(L);
        prev(first(L)) = P;
        first(L) = P;
    } else {
        first(L) = P;
        last(L) = P;
    }
}

void insertLastParent(ListParent &L, adrP P) {
    if (last(L) != NULL) {
        next(last(L)) = P;
        prev(P) = last(L);
        last(L) = P;
    } else {
        first(L) = P;
        last(L) = P;
    }
}

void deleteFirstParent(ListParent &L, adrP &P) {
    P = first(L);
    if(first(L) != last(L)) {
        first(L) = next(P);
        next(P) = NULL;
        prev(first(L)) = NULL;
    } else {
        first(L) = NULL;
        last(L) = NULL;
    }
}

void deleteLastC(listChild &L, adrC &C) {
    if(first(L) == NULL) {
        cout << "List Kosong" << endl;
        return;
    }

    if(next(first(L)) == NULL) {
        C = first(L);
        first(L) = NULL;
    } else {
        adrC Q = first(L);
        while(next(next(Q)) != NULL) {
            Q = next(Q);
        }
        C = next(Q);
        next(Q) = NULL;
    }
}

void showDataParent(ListParent L) {
    adrP P = first(L);
    if (P == NULL) {
        cout << "Merek Kosong!" << endl;
    } else {
        while (P != NULL) {
            cout << "Nama Merek: " << info(P).namaMerek << endl;
            P = next(P);
        }
    }
}

void deleteParentChild(ListParent &L, listChild &LC, adrP P) {
    if (P == NULL) {
        return;
    }

    adrC C = first(LC);
    adrC tempNext;

    while (C != NULL) {
        tempNext = next(C);
        if (C->nextCP == P) {
            if (C == first(LC)) {
                first(LC) = next(C);
            } else {
                adrC Q = first(LC);
                while (Q != NULL && next(Q) != C) {
                    Q = next(Q);
                }
                if (Q != NULL) {
                    next(Q) = next(C);
                }
            }
            delete C;
        }
        C = tempNext;
    }

    if (P == first(L)) {
        adrP temp = P;
        first(L) = next(P);
        if (first(L) != NULL) {
            prev(first(L)) = NULL;
        } else {
            last(L) = NULL;
        }
        delete temp;
    } else if (P == last(L)) {
        last(L) = prev(P);
        next(last(L)) = NULL;
        delete P;
    } else {
        next(prev(P)) = next(P);
        prev(next(P)) = prev(P);
        delete P;
    }
}

void findDataParent(ListParent L, string nama) {
    adrP P = first(L);
    bool found = false;
    while (P != NULL) {
        if (info(P).namaMerek == nama) {
            cout << "Merek ditemukan: " << info(P).namaMerek << endl;
            found = true;
            break;
        }
        P = next(P);
    }
    if (!found) {
        cout << "Merek tidak ditemukan!" << endl;
    }
}

void insertFirstChild(listChild &L, adrC C) {
    if (first(L) == NULL) {
        first(L) = C;
    } else {
        next(C) = first(L);
        first(L) = C;
    }
}

void updateParentChild(ListParent &LP, listChild &LC, adrP P, adrC C) {
    if (P == NULL || C == NULL) {
        cout << "Parent atau Child tidak valid!" << endl;
        return;
    }

    int pilihan;
    cout << "Pilih data yang ingin diupdate:" << endl;
    cout << "1. Update Parent" << endl;
    cout << "2. Update Child" << endl;
    cout << "Masukkan pilihan (1/2): ";
    cin >> pilihan;

    if (pilihan == 1) {
        cout << "Mengupdate data Parent: " << endl;
        cout << "Nama Merek Lama: " << info(P).namaMerek << endl;
        cout << "Masukkan Nama Merek Baru: ";
        cin >> info(P).namaMerek;
        cout << "Update data Parent berhasil!" << endl;
    } else if (pilihan == 2) {
        cout << "Mengupdate data Child: " << endl;
        cout << "Model Lama: " << info(C).model << endl;
        cout << "Masukkan Model Baru: ";
        cin >> info(C).model;
        cout << "Stock Lama: " << info(C).stock << endl;
        cout << "Masukkan Stock Baru: ";
        cin >> info(C).stock;
        cout << "Update data Child berhasil!" << endl;
    } else {
        cout << "Pilihan tidak valid!" << endl;
    }
}

void showParentChild(ListParent LP, listChild LC) {
    adrP P = first(LP);
    if (P == NULL) {
        cout << "List Parent Kosong!" << endl;
        return;
    }

    while (P != NULL) {
        cout << "Merek: " << info(P).namaMerek << endl;
        adrC C = first(LC);
        bool hasChild = false;

        while (C != NULL) {
            if (C->nextCP == P) {
                cout << "  Model: " << info(C).model << ", Stock: " << info(C).stock << endl;
                hasChild = true;
            }
            C = next(C);
        }

        if (!hasChild) {
            cout << "  Tidak ada model untuk merek ini" << endl;
        }
        P = next(P);
    }
}

void findDataChild(listChild LC) {
    string model, namaMerek;
    cout << "Masukkan nama merek: ";
    cin >> namaMerek;
    cout << "Masukkan model yang ingin dicari: ";
    cin >> model;

    adrC C = first(LC);
    bool found = false;

    while (C != NULL) {
        if (C->nextCP != NULL && C->nextCP->info.namaMerek == namaMerek) {
            if (info(C).model == model) {
                cout << "Model ditemukan: " << info(C).model << ", Stock: " << info(C).stock << endl;
                found = true;
                break;
            }
        }
        C = next(C);
    }

    if (!found) {
        cout << "Model atau Parent tidak ditemukan!" << endl;
    }
}

void deleteChild(listChild &L, adrC C) {
    if (C == NULL) {
        cout << "Child tidak ditemukan!" << endl;
        return;
    }

    if (first(L) == C) {
        first(L) = next(C);
    } else {
        adrC temp = first(L);
        while (temp != NULL && next(temp) != C) {
            temp = next(temp);
        }

        if (temp != NULL) {
            next(temp) = next(C);
        }
    }
    C = NULL;
    cout << "Child berhasil dihapus!" << endl;
}

void hitungModel(ListParent LP, listChild LC) {
    string namaMerek;
    cout << "Masukkan nama merek untuk menghitung jumlah model: ";
    cin >> namaMerek;

    adrP P = first(LP);
    bool found = false;

    while (P != NULL) {
        if (info(P).namaMerek == namaMerek) {
            found = true;
            int counter = 0;
            adrC C = first(LC);
            while (C != NULL) {
                if (C->nextCP == P) {
                    counter++;
                }
                C = next(C);
            }
            cout << "Jumlah Model pada Merek " << namaMerek << ": " << counter << endl;
            break;
        }
        P = next(P);
    }

    if (!found) {
        cout << "Merek tidak ditemukan!" << endl;
    }
}
