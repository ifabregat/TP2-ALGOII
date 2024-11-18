#include "menu.h"
#include "../extra/ansi.h"

void mostrarLogo()
{
    printf(ANSI_RESET_SCREEN);
    printf(ANSI_COLOR_BLUE "                                  ,'\\\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "    _.----.        ____         ,'  _\\   ___    ___     ____\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "_,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW " \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  |\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "   \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "    \\     ,-'/  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     |\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "     \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    |\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "      \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   |\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "       \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   |\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "        \\_.-'       |__|    `-._ |              '-.|     '-.| |   |\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "                                `'                            '-._|\n" ANSI_COLOR_RESET);
}

void mostrarMenu()
{
    printf(ANSI_COLOR_BLUE "                            (P) Pokedex\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "                            (J) Jugar\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "                            (S) Semilla\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "                            (Q) Salir\n" ANSI_COLOR_RESET);
}

int main()
{
    mostrarLogo();
    mostrarMenu();
    return 0;
}