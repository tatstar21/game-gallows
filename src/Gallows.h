#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <random>

class Gallows
{
public:
	Gallows(std::istream& inStream);
	std::string getWord(std::istream& inStream);
	void showEncryptedWord();
	bool checkNumberErrors();
	bool guessWord(std::string wordGuess);
	void showGallows();
	void gameStatisticsByWord();
	void gameStatisticsByLetter();
	bool guessLetter(char letter);

	int availableMoves();	
	bool isLooser();
	bool wordGuessed();

private:
	
	std::string word_;
	char* arrayError_;
	int counterError_;
	int attempts_;
	std::string tmpWord_;
	std::chrono::system_clock::time_point start_;

	void printTime();
	void printError();
	std::string createEncryptedWord();
	void addError(char letter);

	static std::string decriptionWord(std::string word);
};

