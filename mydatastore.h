
#include <string>
#include <set>
#include <vector>
#include <map>
#include "datastore.h"
#include "product.h"
#include "user.h"
#include "util.h"

class mydatastore : public DataStore {
    public:
        // constructor + destructor + definition of pure virtual functions
        mydatastore();
        ~mydatastore();

        void addProduct(Product* p);
        void addUser(User* u);
        std::vector<Product*> search(std::vector<std::string>& terms, int type);
        void dump(std::ostream& ofile);

        void add(std::string uname, Product* p);
        void display(std::string uname);
        void buy(std::string uname);
        

    
    private:
    std::map<std::string, User*> users_; // user map

    std::set<Product*> products_; // product set

    std::map<std::string, std::set<Product*>> prodKeyWords_; // keyword map, string as keys, products as values

    std::vector<Product*> lastSearch_; // vector of last search

    std::map<std::string, std::vector<Product*> > cart_; // user cart
};