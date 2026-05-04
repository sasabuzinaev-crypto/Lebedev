
#include "Field.h"
#include <iostream>
#include <locale>
int main()
{
    std::setlocale(LC_ALL, "Russian");

    Field game(true);

    for (;;)
    {
        if (game.isOver())
            break;

        game.print();

        std::cout << "Ходит "
                  << (game.isRedTurnNow() ? "красный" : "желтый")
                  << " игрок. Выберите столбец (1-" << FIELD_WIDTH << "):\n";

        int move = 0;

        if (!(std::cin >> move))
            return 0;

        bool ok = game.makeTurn(move);

        if (!ok)
        {
            std::cout << "Ошибка хода. Попробуйте ещё раз.\n";
        }
    }

    game.printResult();
    return 0;
}