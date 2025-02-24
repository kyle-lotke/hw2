#include "movie.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <iomanip>


using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating)
    : Product(category, name, price, qty), genre_(genre), rating_(rating) {}

Movie::~Movie() {}

std::set<std::string> Movie::keywords() const{
    set<string> keywords = parseStringToWords(name_);
    set<string> genreWords = parseStringToWords(genre_);
    keywords.insert(genreWords.begin(), genreWords.end());
    return keywords;
}

std::string Movie::displayString() const 
{
    std::stringstream s;
    s << name_ << "\nGenre: " << genre_  << " Rating: " << rating_  << "\n" << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.";

    return s.str();
}

void Movie::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}

