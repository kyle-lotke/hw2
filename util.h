#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> intersection; // this will be the set we are returning

    typename std::set<T>::iterator it = s1.begin(); // create set iterator objects so we can efficiently traverse
    
    for(it = s1.begin(); it != s1.end(); ++it) // iterate through the first set
    {
        if(s2.find(*it) != s2.end()) // if element in s1 exists in s2
        {
            intersection.insert(*it); // add element to intersection
        }
    }
    return intersection;




}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> union_set = s1; // this will be the set we are returning, start by copying s1 into the final set
    typename std::set<T>::iterator it2 = s2.begin(); // define iterator for s2

    while(it2 != s2.end()) {
        union_set.insert(*it2); // this adds every element to the union set but becasue its a set, it ignores duplicates
        ++it2;
    }

    return union_set; // returns combo minus the duplicates
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
