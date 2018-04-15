/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */
#include <iostream>
#include <fstream>
#include <tuple>
#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
	vector<std::tuple<std::string, std::string, std::string>> ret;

	ifstream wordsFile(word_list_fname);
	string word;
	if (wordsFile.is_open()) {
		while (getline(wordsFile, word)) {
			int len = word.length();
			if (len == 5){
				string homo1 = word.substr(1,5);		//word 
				string homo2 = word.substr(0,1) + word.substr(2,5);
				if (d.homophones(homo1, word) && d.homophones(homo2, word)){
					ret.push_back(make_tuple(word, homo1, homo2));
					//std::cout<<word<<std::endl;
				}
			}	     
		}
	}

	return ret;
}



