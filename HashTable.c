#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_types.h"
#include "HashTable.h"
#include "GRAPH_SEARCH.h"

typedef struct HashNode {
    State state;
    struct HashNode* next;
} HashNode;

struct Hash_Table {
    int size;
    HashNode** buckets;
};

// Basit ama etkili bir hash fonksiyonu (djb2 algoritması)
// String değil, byte dizisi üzerinde çalışır.
static unsigned long hash_function(const State* state) {
    unsigned long hash = 5381;
    int c;
    int i;
    const unsigned char* str = state->stickers;

    for (i = 0; i < 54; i++) {
        c = str[i];
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

Hash_Table* New_Hash_Table(const int size) {
    Hash_Table* ht = (Hash_Table*)malloc(sizeof(Hash_Table));
    if (ht == NULL) {
        Warning_Memory_Allocation();
    }
    ht->size = size;
    ht->buckets = (HashNode**)calloc(ht->size, sizeof(HashNode*));
    if (ht->buckets == NULL) {
        Warning_Memory_Allocation();
    }
    return ht;
}

// Hash Tablosuna yeni bir durum ekler
void ht_insert(Hash_Table* ht, const State* state) {
    unsigned long hash = hash_function(state);
    int index = hash % ht->size;

    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    if (new_node == NULL) {
        Warning_Memory_Allocation();
    }
    memcpy(&new_node->state, state, sizeof(State));

    new_node->next = ht->buckets[index];
    ht->buckets[index] = new_node;
}

// Hash Tablosunda bir durumu arar
int ht_search(const Hash_Table* ht, const State* state) {
    unsigned long hash = hash_function(state);
    int index = hash % ht->size;

    // O kovanın başındaki düğüme git
    HashNode* current = ht->buckets[index];

    // Bağlı liste boyunca ilerle
    while (current != NULL) {
        // State'leri byte-byte karşılaştır
        if (Compare_States(¤t->state, state) == TRUE) {
            return TRUE; // Bulundu!
        }
        current = current->next;
    }

    return FALSE; // Bulunamadı
}

// Hash Tablosunu ve içindeki tüm düğümleri temizler
void Delete_Hash_Table(Hash_Table* ht) {
    int i;
    for (i = 0; i < ht->size; i++) {
        HashNode* current = ht->buckets[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->buckets);
    free(ht);
}
