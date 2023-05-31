#include "hash_table.h"

HashTable::HashTable() {
    count = 0;
    mem_size = 8;
    array = new Pair[mem_size];
}
HashTable::~HashTable() {
    delete[] array;
}
void HashTable::add(LoginName _login, uint* pass_hash) {
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++) {
        index = hash_func(_login, i);
        if (array[index].status == enPairStatus::free) {
            // найдена пустая ячейка, занимаем ее
            break;
        }
    }
    if (i >= mem_size) return; // все перебрали, нет места

    // кладем в свободную ячейку пару
    array[index] = Pair(_login, pass_hash);
    count++;
}
int HashTable::hash_func(LoginName _login, int offset) {
    // вычисляем индекс
    int sum = 0, i = 0;
    for (; i < NAMELENGTH; i++) {
        sum += _login[i];
    }
    // квадратичные пробы
    return ((sum % mem_size) * offset * offset) % mem_size;
}

void HashTable::del(LoginName _login) {
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++) {
        index = hash_func(_login, i);
        if (array[index].status == enPairStatus::engaged &&
            !strcmp(array[index].login, _login)) {
            array[index].status = enPairStatus::deleted;
            count--;
            return;
        }
        else if (array[index].status == enPairStatus::free) {
            return;
        }
    }
}

uint* HashTable::find(LoginName _login) {

    for (int i = 0; i < mem_size; i++) {
        int index = hash_func(_login, i);
        if (array[index].status == enPairStatus::engaged &&
            !strcmp(array[index].login, _login)) {
            return array[index].pass_hash;
        }
        else if (array[index].status == enPairStatus::free) {
            return nullptr;
        }
    }
    return nullptr;
}
