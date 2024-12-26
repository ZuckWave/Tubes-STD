#ifndef MLL_H_INCLUDED
#define MLL_H_INCLUDED
#include <iostream>
#define first(L) L.first
#define last(L) L.last
#define next(P) P->next
#define prev(P) P->prev
#define info(P) P->info
#define next(C) C->next
#define info(C) C->info
using namespace std;

struct Parent {
    string namaMerek;
};

struct Child {
    string model;
    int stock;
};

typedef struct elmP *adrP;
typedef struct elmC *adrC;
typedef Parent infotypeP;
typedef Child infotypeC;

struct listChild {
    adrC first;
};



struct elmP {
    infotypeP info;
    adrP next;
    adrP prev;
    listChild nextCP;
};

struct elmC {
    infotypeC info;
    adrC next;
    adrP nextCP;
};

struct ListParent {
    adrP first;
    adrP last;
};

void createListParent(ListParent &L);
void createListChild(listChild &L);
adrP createElementParent(string namaMerek);
adrC createElementChild(string model, int stock);
void insertFirstParent(ListParent &L, adrP P);
void insertLastParent(ListParent &L, adrP P);
void showDataParent(ListParent L);
void deleteFirstParent(ListParent &L, adrP P);
void deleteParentChild(ListParent &L, listChild &LC, adrP P);
void findDataParent(ListParent L, string nama);
void insertFirstChild(listChild &L, adrC C);
void updateParentChild(ListParent &LP, listChild &LC, adrP P, adrC C);
void showParentChild(ListParent LP, listChild LC);
void findDataChild(listChild LC);
void deleteLastC(listChild &L, adrC C);
void deleteChild(listChild &L, adrC C);
void hitungModel(ListParent LP, listChild LC);

#endif // MLL_H_INCLUDED
