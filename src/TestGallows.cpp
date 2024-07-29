
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
		std::cout << "������� ��� �������� ����� �� �������: ";
		std::cin >> inFileName;
	}

	try
	{
		std::ifstream inFile(inFileName);
		Gallows gallows(inFile);
		inFile.close();

		gallows.showEncryptedWord();

		std::cout << "\a\033[34m���� ��������\033[0m\n";
		std::cout << "\a\033[33m**************\033[0m\n";

		while (gallows.checkNumberErrors())
		{
			std::cout << "\n������ ������� ����� ����� ��� �� ������?: \n";
			std::cout << "���� ����� ������� - ������� 1;\n���� �� ������ - ������� 2;\n������ - �����!\n";
			int choice;
			std::cin >> choice;
			std::cin.ignore();

			if (choice == 1)
			{
				std::cout << "������� �����: ";
				std::string wordGuess;
				std::cin >> wordGuess;

				if (gallows.guessWord(wordGuess)) {
					std::cout << "\a\033[32m����������!!!�� ������� �����!!!\033[0m\n";
				}
				else {
					std::cout << "\a\033[31m����� �� ��������! �� ���������!\033[0m\n";
					gallows.showGallows();
				}
				gallows.gameStatisticsByWord();
				exit(0);
			}
			else if (choice == 2) {

				bool isError = false;
				std::cout << "������� �����: ";
				char letter;
				std::cin >> letter;

				if (gallows.guessLetter(letter)) {
					std::cout << "\a\033[32m�� ������� �����!\033[0m\n";
				}
				else
				{
					std::cout << "\a\033[31m�� �� ������� �����!\033[0m\n";
					std::cout << "\a\033[34m�� ������ ��������� ��� "
						<< gallows.availableMoves() << " ���!\033[0m\n";
					gallows.showGallows();
				}

				if (gallows.wordGuessed())
				{
					std::cout << "\a\033[32m�� ������� ����� �� ������!\033[0m\n";
					gallows.gameStatisticsByLetter();
					gallows.showGallows();
					exit(0);
				}
				gallows.showEncryptedWord();


				if (gallows.isLooser()) {
					std::cout << "\a\033[31m�� ���������!\033[0m\n";
					gallows.gameStatisticsByLetter();
				}

			}
			else {
				std::cout << "\n����� �� ���������!\n";
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

