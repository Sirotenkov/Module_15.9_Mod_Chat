#include "chat.h"
#include "iostream"
#include "string.h"

Chat::Chat() {
    data_count = 0;
}
void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    //data[data_count++] = AuthData(_login, sha1(_pass, pass_length));
    data.add(_login, sha1(_pass, pass_length));
}
bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    uint* pass_hash = data.find(_login);
    if (pass_hash == nullptr) return false;

    uint* digest = sha1(_pass, pass_length);

    bool cmpHashes = !memcmp(pass_hash, digest, SHA1HASHLENGTHBYTES);
    delete[] digest;

    return cmpHashes;
}
