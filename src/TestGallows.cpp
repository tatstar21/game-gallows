
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include "Gallows.h"

int main(int argc, char* argv[], char* envp[])
{
	setlocale(LC_ALL, "Russian");

	char* inFileName = nullptr;

	if (argc == 2) {
		inFileName = argv[1];
	}
	else {
		std::cout << "Введите имя входного файла со словами: ";
		std::cin >> inFileName;
	}

	try
	{
		std::ifstream inFile(inFileName);
		Gallows gallows(inFile);
		inFile.close();

		gallows.showEncryptedWord();

		std::cout << "\a\033[34mИГРА ВИСЕЛИЦА\033[0m\n";
		std::cout << "\a\033[33m**************\033[0m\n";

		while (gallows.checkNumberErrors())
		{
			std::cout << "\nХотите угадать слово сразу или по буквам?: \n";
			std::cout << "Если слово целиком - нажмите 1;\nЕсли по буквам - нажмите 2;\nДругое - выход!\n";
			int choice;
			std::cin >> choice;
			std::cin.ignore();

			if (choice == 1)
			{
				std::cout << "Введите слово: ";
				std::string wordGuess;
				std::cin >> wordGuess;

				if (gallows.guessWord(wordGuess)) {
					std::cout << "\a\033[32mПОЗДРАВЛЯЮ!!!Вы угадали слово!!!\033[0m\n";
				}
				else {
					std::cout << "\a\033[31mСлово не угаданно! Вы ПРОИГРАЛИ!\033[0m\n";
					gallows.showGallows();
				}
				gallows.gameStatisticsByWord();
				exit(0);
			}
			else if (choice == 2) {

				bool isError = false;
				std::cout << "Введите букву: ";
				char letter;
				std::cin >> letter;

				if (gallows.guessLetter(letter)) {
					std::cout << "\a\033[32mВы угадали букву!\033[0m\n";
				}
				else
				{
					std::cout << "\a\033[31mВы не угадали букву!\033[0m\n";
					std::cout << "\a\033[34mВы можете ошибиться еще "
						<< gallows.availableMoves() << " раз!\033[0m\n";
					gallows.showGallows();
				}

				if (gallows.wordGuessed())
				{
					std::cout << "\a\033[32mВы угадали слово по буквам!\033[0m\n";
					gallows.gameStatisticsByLetter();
					gallows.showGallows();
					exit(0);
				}
				gallows.showEncryptedWord();


				if (gallows.isLooser()) {
					std::cout << "\a\033[31mВы ПРОИГРАЛИ!\033[0m\n";
					gallows.gameStatisticsByLetter();
				}

			}
			else {
				std::cout << "\nВыход из программы!\n";
				gallows.showGallows();
				gallows.gameStatisticsByLetter();
				exit(4);
			}
		}
	}
	catch (const char* error)
	{
		std::cerr << "\a\x1b[31m" << error << "!!!\n\x1b[0m";
		return 1;
	}

	return 0;
}

