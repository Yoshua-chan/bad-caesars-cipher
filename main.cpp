#include <iostream>
#include "header.h"
#include <fstream>
#include <string>
#include <algorithm>
//To-do list

//dodaj tryb live feed... done
//dodaj podstawowy odczyt ze zmiennej... done
//dodaj podstawowy odczyt z pliku... done
//dodaj mozliwosc wpisywania wielu linijek w trybie odczytu ze zmiennej...  done

//dodaj charset QWERTY... done

//dodaj nowe charsety o innej dlugosci niz 26... done
//dodaj alternat ywne tryby zapisu (wypisywanie w konsoli, lub zapisywanie do pliku)

int main()
{

    while (1)
    {
        std::string linia;
        std::fstream plik;
        std::fstream zapis;

        char escape;
        escape = 27;
        char backspace;
        backspace = 8;
        char enter;
        enter = 13;
        char space;
        space = 32;

        char button;

        int dlugoscLinii;
        int x;
        std::string opcja;
        std::string save;
        std::string consoleOut;

        std::cout << "Szyfr cezara v1.0 - by Kacper Yoshua-chan Filipek" << std::endl
                  << "(Work in progress!)";

        std::cout << std::endl
                  << std::endl;

        std::cout << "Wybierz zestaw znakow: " << std::endl;
        std::cout << "[1] Alfabet" << std::endl;
        std::cout << "[2] Qwerty" << std::endl;

        button = getch();
        switch (button)
        {
        case '1':
            charset = alfabet;
            cl = alfabet.size();
            std::cout << "Wybrany zestaw znakow: Alfabet" << std::endl;
            break;

        case '2':
            charset = qwerty;
            cl = qwerty.size();
            std::cout << "Wybrany zestaw znakow: Qwerty" << std::endl;
            break;
        }

        std::cout << "Wybierz funkcje programu" << std::endl;
        std::cout << "[1] Zapis do zmiennej" << std::endl;
        std::cout << "[2] Odczyt z pliku" << std::endl;
        std::cout << "[3] Live feed" << std::endl;

        button = getch();
        switch (button)
        {
        case '1':
            opcja = "zmienna";
            break;
        case '2':
            opcja = "plik";
            break;
        case '3':
            opcja = "live";
            break;
        }
        if (opcja != "live")
        {
            std::cout << "Czy zapisac zakodowany tekst to pliku?" << std::endl;
            std::cout << "[1] Tak" << std::endl;
            std::cout << "[2] Nie" << std::endl;

            button = getch();
            switch (button)
            {
            case '1':
                save = "tak";
                break;
            case '2':
                save = "nie";
                break;
            }
        }
        if (opcja != "live")
        {
            std::cout << "Czy wypisac zakodowany tekst do konsoli?" << std::endl;
            std::cout << "[1] Tak" << std::endl;
            std::cout << "[2] Nie" << std::endl;

            button = getch();
            switch (button)
            {
            case '1':
                consoleOut = "tak";
                break;
            case '2':
                consoleOut = "nie";
                break;
            }
        }
        do
        {
            std::cout << "Podaj przesuniecie: ";
            std::cin >> x;
            if (x > cl || x < -cl)
            {
                std::cout << "x nie moze byc wieksze ani mniejsze od " << cl << std::endl;
            }
        } while (x > cl || x < -cl);

        x = (cl + x) % cl;

        if (opcja == "zmienna") //[1] zapis do zmiennej
        {
            std::cout << std::endl;
            plik.open("temp.txt", std::ios::out);
            std::cout << "Wpisz tekst: " << std::endl;
            std::cin.sync(); //sprawia, ze kompilator nie pomija getlina (nie wiem dlaczego, ale dziala)
            do
            {
                std::getline(std::cin, linia);

                if (linia != "end")
                {
                    plik << linia << std::endl;
                }
            } while (linia != "end");
            plik.close();

            if (consoleOut == "tak")
            {
                std::cout << std::endl
                          << "Finalny tekst: " << std::endl;
            }

            plik.open("temp.txt");
            if (save == "tak")
            {
                zapis.open("output.txt", std::ios::out);
            }
            if (plik.good() == true)
            {
                while (!plik.eof())
                {
                    std::getline(plik, linia);
                    transform(linia.begin(), linia.end(), linia.begin(), ::tolower);
                    if (consoleOut == "tak")
                    {
                        printLine(linia, x);
                        std::cout << std::endl;
                    }
                    if (save == "tak")
                    {
                        zapis << shiftLine(linia, x) << std::endl;
                    }
                }
                plik.close();
                zapis.close();
            }
            plik.open("temp.txt", std::ios::out);
            plik.close();
            std::cout << std::endl << "Zakonczono szyfrowanie tekstu" << std::endl;
        }
        else if (opcja == "plik") //[2] odczyt z pliku
        {
            if (save == "tak")
            {
                zapis.open("output.txt", std::ios::out);
            }

            std::cout << std::endl;
            plik.open("input.txt");
            if (plik.good() == true)
            {
                while (!plik.eof())
                {
                    std::getline(plik, linia);
                    transform(linia.begin(), linia.end(), linia.begin(), ::tolower);
                    if(consoleOut == "tak")
                    {
                    printLine(linia, x);
                    std::cout << std::endl;
                    }
                    if (save == "tak")
                    {
                        zapis << shiftLine(linia, x) << std::endl;
                    }
                }
                plik.close();
                if (save == "tak")
                {
                    zapis.close();
                }
            }
            std::cout << std::endl << "Zakonczono szyfrowanie tekstu" << std::endl;
        }

        std::cout << "[1] Zacznij program od nowa" << std::endl;
        std::cout << "[2] Zakoncz program" << std::endl;

        while (1)
        {
            button = getch();
            if (button == '2')
            {
                exit(1);
            }
            else if (button == '1')
            {
                break;
            }
            else
            {
                std::cout << "Nie ma takiej opcji" << std::endl;
            }
        }
        system("cls");
    }
}
