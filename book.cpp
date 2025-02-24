#include "book.h"
#include "util.h"
#include <iostream>
#include <sstream>


using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author)
    : Product(category, name, price, qty), isbn_(isbn), author_(author) {}

Book::~Book() {}

std::set<std::string> Book::keywords() const{
    set<string> keywords = parseStringToWords(name_);
    set<string> authorWords = parseStringToWords(author_);
    keywords.insert(authorWords.begin(), authorWords.end());
    keywords.insert(isbn_); // needs to be unparsed
    return keywords;
}

std::string Book::displayString() const{
    stringstream ss;
    ss << name_ << "\n" << "Author: " << author_ << " ISBN: " << isbn_ << "\n" << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Book::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}

