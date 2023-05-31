#include <iostream>
#include "chat.h"

#define OP_REG 1
#define OP_LOGIN 2
#define OP_EXIT 0

int main()
{
    setlocale(LC_CTYPE, "ru");
    Chat ch;
    while (true)
    {
        std::string login, pass;
        int op_type;
        bool success;

        std::cout << "Введите тип операции, 1 - регистрация, 2 - вход, 0 - выход: ";
        std::cin >> op_type;

        switch (op_type)
        {
        case OP_REG:
            std::cout << "Введите имя пользователя: ";
            std::cin >> login;
            std::cout << "Введите пароль: ";
            std::cin >> pass;

            ch.reg((char*)login.data(), (char*)pass.data(), pass.size());
            break;

        case OP_LOGIN:
            std::cout << "Введите имя пользователя: ";
            std::cin >> login;
            std::cout << "Введите пароль: ";
            std::cin >> pass;

            success = ch.login((char*)login.data(), (char*)pass.data(), pass.size());

            if (success) {
                std::cout << "Вход выполнен" << std::endl;
            }
            else {
                std::cout << "Не удалось выполнить вход" << std::endl;
            }
            break;

        case OP_EXIT:
        default:
            return 0;
        }
    }

    return 0;
}
