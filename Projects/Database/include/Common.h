#pragma once

#define DB_HT_SIZE 100

typedef unsigned long long int Db_key;
typedef unsigned long long int Db_offset;
typedef unsigned long long int Db_hash;
typedef unsigned long long int Db_idx;
typedef unsigned long long int Db_ll_length;
typedef unsigned long long int Db_node_pos;

enum return_codes
{
    Failure                 = -1,
    LlEmpty                 = -2,
    KeyAlreadyPresent       = -3,
    KeyNotPresent           = -4,
    Success                 = 0
};
