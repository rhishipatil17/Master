#ifndef COMMON_H
#define COMMON_H

#define DB_HT_SIZE 100

typedef unsigned long long int Db_key;
typedef unsigned long long int Db_offset;
typedef unsigned long long int Db_ll_length;
typedef unsigned long long int Db_hash;
typedef unsigned long long int Db_idx;

enum return_codes
{
    Success = 0,
    Failure = -1
};

#endif
