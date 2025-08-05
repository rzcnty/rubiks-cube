#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "data_types.h"

#define HASH_TABLE_BASED_SIZE 9999991

typedef struct Hash_Table Hash_Table;

Hash_Table* New_Hash_Table(int size);
void ht_insert(Hash_Table* table, const State* state);
int ht_search(const Hash_Table* table, const State* state);
void Delete_Hash_Table(Hash_Table* table);
void Show_Hash_Table(Hash_Table* table);

#endif
