#include <iostream>
#include "Gallows.h"

std::string Gallows::getWord(std::istream& inStream)
{
	std::vector<std::string>* words = new std::vector<std::string>();

	while (inStream.eof() == false) {
		
		std::string temp;
		inStream >> temp;
		words->push_back(temp);
	}
	
	std::random_device randomDevice;
	int randomIndex = static_cast<int>(randomDevice() % words->size());
	std::string word = words->at(randomIndex);

	return decriptionWord(word);
}

std::string Gallows::createEncryptedWord()
{
	std::string tmpWord = word_;
	int lengthWord = (int)word_.length();

	for (int ii = 1; ii < lengthWord - 1; ii++) {
		if (tmpWord[ii] == tmpWord[0] || tmpWord[ii] == tmpWord[lengthWord - 1]) {
			continue;
		}
		else
			tmpWord[ii] = '_';
	}
	return tmpWord;
}

Gallows::Gallows(std::istream& inStream)
{
    start_ = std::chrono::system_clock::now();
	counterError_ = 0;
	attempts_ = 0;
	arrayError_ = new char[26];
	word_ = getWord(inStream);
	tmpWord_ = createEncryptedWord();

	for (int ii = 0; ii < 26; ii++) {
		arrayError_[ii] = '0';
	}
}

void Gallows::showEncryptedWord() 
{
	std::cout << tmpWord_ << '\n';
}

bool Gallows::checkNumberErrors()
{
	return counterError_ != 6;
}

bool Gallows::guessWord(std::string wordGuess)
{
	attempts_++;
	if (word_ == wordGuess) {
		return true;
	}
	else
	{
		counterError_ = 6;
		return false;
	}
}

bool Gallows::guessLetter(char letter)
{
	attempts_++;

	int counterLetter = 0;

	for (int ii = 0; ii < word_.length(); ii++) {
		if (word_[ii] == letter) {
			tmpWord_[ii] = letter;
			counterLetter++;
		}
	}
	
	if (counterLetter != 0) 
		return true;
	else
	{
		counterError_++;
		addError(letter);
		return false;
	}
}

int Gallows::availableMoves() {
	return 6 - counterError_;
}

void Gallows::showGallows()
{
	char gallows[7][10][7] = {

			{
				{'#', '#', '#', '#', '#', '#', '#' },
				{' ', ' ', '|', ' ', ' ', ' ', '#' },
				{' ', ' ', '|', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', '#', '#' }
			},
			{
				{'#', '#', '#', '#', '#', '#', '#' },
				{' ', ' ', '|', ' ', ' ', ' ', '#' },
				{' ', ' ', '|', ' ', ' ', ' ', '#' },
				{' ', ' ', 'O', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', '#', '#' }
			},
			{
				{'#', '#', '#', '#', '#', '#', '#' },
				{' ', ' ', '|', ' ', ' ', ' ', '#' },
				{' ', ' ', '|', ' ', ' ', ' ', '#' },
				{' ', ' ', 'O', ' ', ' ', ' ', '#' },
				{' ', ' ', '|', ' ', ' ', ' ', '#' },
				{' ', ' ', '|', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', '#', '#' }
			},
			{
				{'#', '#', '#', '#', '#', '#', '#' },
				{' ', ' ', '|', ' ', ' ', ' ', '#' },
				{' ', ' ', '|', ' ', ' ', ' ', '#' },
				{' ', ' ', 'O', ' ', ' ', ' ', '#' },
				{' ', '/', '|', ' ', ' ', ' ', '#' },
				{' ', ' ', '|', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', '#', '#' }
			},
			{
				{'#', '#', '#', '#', '#', '#', '#' },
				{' ', ' ', '|', ' ', ' ', ' ', '#' },
				{' ', ' ', '|', ' ', ' ', ' ', '#' },
				{' ', ' ', 'O', ' ', ' ', ' ', '#' },
				{' ', '/', '|', '\\', ' ', ' ', '#' },
				{' ', ' ', '|', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', '#', '#' }
			},
			{
				{'#', '#', '#', '#', '#', '#', '#' },
				{' ', ' ', '|', ' ', ' ', ' ', '#' },
				{' ', ' ', '|', ' ', ' ', ' ', '#' },
				{' ', ' ', 'O', ' ', ' ', ' ', '#' },
				{' ', '/', '|', '\\', ' ', ' ', '#' },
				{' ', ' ', '|', ' ', ' ', ' ', '#' },
				{' ', '/', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', '#', '#' }
			},
			{
				{'#', '#', '#', '#', '#', '#', '#' },
				{' ', ' ', '|', ' ', ' ', ' ', '#' },
				{' ', ' ', '|', ' ', ' ', ' ', '#' },
				{' ', ' ', 'O', ' ', ' ', ' ', '#' },
				{' ', '/', '|', '\\', ' ', ' ', '#' },
				{' ', ' ', '|', ' ', ' ', ' ', '#' },
				{' ', '/', ' ', '\\', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', ' ', '#' },
				{' ', ' ', ' ', ' ', ' ', '#', '#' }
			},
	};

	for (int ii = 0; ii < 10; ii++) {
		for (int jj = 0; jj < 7; jj++) {
			std::cout << "\033[31m" << gallows[counterError_][ii][jj] << "\033[0m";
		}
		std::cout << '\n';
	}
}

void Gallows::printTime() {
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start_;
	std::cout << "\nВремя игры: " << elapsed_seconds.count() << " сек." << std::endl;
}

void Gallows::gameStatisticsByWord()
{
	printTime();
	std::cout << "Количество попыток: " << attempts_ << '\n';
	std::cout << "Искомое слово: " << word_ << '\n';
}

void Gallows::printError() 
{
	for (int ii = 0; ii < 26; ii++) {
		if (arrayError_[ii] != '0')
			std::cout << arrayError_[ii] << ' ';
	}
}

void Gallows::gameStatisticsByLetter()
{
	printTime();
	std::cout << "Количество попыток: " << attempts_ << '\n';
	std::cout << "Количество ошибок: " << counterError_ << '\n';
	std::cout << "Искомое слово: " << word_ << '\n';
	std::cout << "Ошибки: \n";
	printError();
}

void Gallows::addError(char letter)
{
	for (int ii = 0; ii < 26; ii++) {
		if (arrayError_[ii] == '0') {
			arrayError_[ii] = letter;
			break;
		}
	}
}

bool Gallows::wordGuessed()
{
	return tmpWord_ == word_;
}

bool Gallows::isLooser()
{
	return counterError_ == 6;
}

std::string Gallows::decriptionWord(std::string word) {

	for (int ii = 0; ii <= word.size(); ii++) {
		word[ii] -= 3;
	}
	return word;
}