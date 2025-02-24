#include "clothing.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <iomanip>


using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand)
    : Product(category, name, price, qty), size_(size), brand_(brand) {}

Clothing::~Clothing() {}

std::set<std::string> Clothing::keywords() const{
    set<string> keywords = parseStringToWords(name_);
    set<string> brandWords = parseStringToWords(brand_);
    // set<string> sizeWords = parseStringToWords(size_);
    keywords.insert(brandWords.begin(), brandWords.end());
    // keywords.insert(sizeWords.begin(), sizeWords.end());
    return keywords;
}


std::string Clothing::displayString() const 
{
    std::stringstream ss;
    ss << name_ << "\nSize: " << size_  << " Brand: " << brand_  << "\n" << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.";

    return ss.str();
}


void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}
