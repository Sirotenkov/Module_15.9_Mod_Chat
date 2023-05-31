#pragma once

#include <string.h>

#define NAMELENGTH 10  // Зафикcируем длину имени

typedef char LoginName[NAMELENGTH]; // тип имя фрукта
typedef unsigned int uint;

class HashTable { // хэш таблица
public:

    HashTable();
    ~HashTable();
    void add(LoginName _login, uint* pass_hash);

    void del(LoginName _login);
    uint* find(LoginName _login);

private:

    enum enPairStatus {
        free,
        engaged,
        deleted
    };

    struct Pair { // пара ключ-значение

        Pair() :
            login(""),
            pass_hash(nullptr),
            status(enPairStatus::free)
        {}
        Pair(LoginName _login, uint* _pass_hash) :
            pass_hash(_pass_hash),
            status(enPairStatus::engaged) {
            memcpy(login, _login, NAMELENGTH);
        }
        Pair& operator = (const Pair& other) {
            pass_hash = other.pass_hash;
            memcpy(login, other.login, NAMELENGTH);
            status = other.status;

            return *this;
        }

        bool operator == (const Pair& other) {
            return  status == other.status &&
                (status != enPairStatus::engaged || (!strcmp(login, other.login)));
        }

        LoginName login;
        uint* pass_hash;

        enPairStatus status;
    };

    int hash_func(LoginName _login, int offset);

    Pair* array;
    int mem_size;
    int count;
};
