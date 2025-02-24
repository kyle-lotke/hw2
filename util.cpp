#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{

    std::istringstream iss(rawWords);
    std::string word;
    std::string current;
    std::set<string> words;

    rawWords = trim(rawWords); // trims to save time iterating

    while(iss >> word) {
        word = trim(word); // gets rid of white space on both ends
        current = "";
        word = convToLower(word); // makes all letters lowercase
        for(unsigned int i = 0; i < word.size(); i++) { // for each space parsed word, iterate through its characters

            if(ispunct(word[i])) { // checks if char is punctuation

                if(current.size() > 1) { // makes sure the length of word is bigger than 1, per assignment directions
                    words.insert(current);
                    current = ""; // reset current
                }
                
            }

            else {
                current += word[i]; // if not punctuation, add character to current string
            }
        }
        if(current.size() > 1) { // need to add last current word if longer than 1
            words.insert(current);
        }
    }
    return words;


}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
