#include <iostream>
#include <stdio.h>
#include <cstdlib>

std::string alfabet = "abcdefghijklmnopqrstuvwxyz";
std::string qwerty = "qwertyuiopasdfghjklzxcvbnm";
std::string charset;

int cl = 26;
char space = 32;

int whichLetter(char letter) //zwraca liczbę porządkową z litery
{
    for (int i = 0; i < cl; i++)
    {
        if (charset[i] == letter)
        {
            return i + 1;
        }
        else
        {
        }
    }
}
char encode(int lp) //zwraca litere z liczby porządkowej
{
    return charset[lp - 1];
}
char shift(char letter, int shifter) //przesuwa jedną litere o wybrane przesunięcie
{
    if ((letter >=32 && letter<=64) || letter >= 123 && letter <= 126)
    {
        return letter;
    }
    else
    {
        if (shifter % cl == 0)
        {
            return letter;
        }
        else
        {
            if ((whichLetter(letter) + shifter) % cl == 0)
            {
                return charset[cl - 1];
            }
            else
            {
                return encode((whichLetter(letter) + shifter) % cl);
            }
        }
    }
}
void printLine(std::string linia, int przesuniecie)
{
    int length;
    length = linia.size();
    for (int i = 0; i < length; i++)
    {
        std::cout << shift(linia[i], przesuniecie);
    }
}
std::string shiftLine(std::string linia, int przesuniecie)
{
    int length;
    length = linia.size();
    std::string shifted = linia;
    for (int i = 0; i <= length; i++)
    {
        shifted[i] = shift(linia[i], przesuniecie);
    }
    return shifted;
}