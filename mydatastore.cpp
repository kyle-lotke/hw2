#include "product.h"
#include "mydatastore.h"

using namespace std;

// default constructor
mydatastore::mydatastore() { }

// default destructor
mydatastore::~mydatastore() {
	
	for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it)
		delete it->second;

	for (set<Product*>::iterator it2 = products_.begin(); it2 != products_.end(); ++it2)
		delete *it2;

}


// add product to datastore
void mydatastore::addProduct(Product* p) {

	// obtain a set of p's keywords
	set<string> keyword = p->keywords();

	// iterate through each word in kW and insert p into that word's products set
	for (set<string>::iterator it = keyword.begin(); it != keyword.end(); it++)
		prodKeyWords_[*it].insert(p);
	
	// add p to products_
	products_.insert(p);

}


void mydatastore::addUser(User* u) {
	users_[u->getName()] = u; // add user to map
}


/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
std::vector<Product*> mydatastore::search(std::vector<std::string>& words, int boolean) {
	set<Product*> search_results; // set of search results

	// AND
	if (boolean == 0) {
		for (vector<string>::iterator it = words.begin(); it != words.end(); ++it) {
			
			if (it == words.begin())
				search_results = setUnion(search_results, prodKeyWords_[*it]); // first iteration creates new set
			
			else {
				search_results = setIntersection(search_results, prodKeyWords_[*it]); // not first make it an and search
            }
		}

	}

	// OR
	else if (boolean == 1) {
		for (vector<string>::iterator it = words.begin(); it != words.end(); ++it) // loop through words
			search_results = setUnion(search_results, prodKeyWords_[*it]); // union because its or
	}

	
	lastSearch_.assign(search_results.begin(), search_results.end()); // set all results to lastSearch_
	return lastSearch_;
}


// reamke db from products + users
void mydatastore::dump(std::ostream& ofile) {
	
	set<Product*> p; // set of products

	
	for (map<string, set<Product*>>::iterator it = prodKeyWords_.begin(); it != prodKeyWords_.end(); ++it) // dump all products
		p = setUnion(p, it->second);

	ofile << "<products>" << endl;

	for (set<Product*>::iterator it = p.begin(); it != p.end(); ++it)
		(*it)->dump(ofile);

	ofile << "</products>" << endl;
	// end dump products

	// dump all users
	ofile << "<users>" << endl;

	for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it)
		it->second->dump(ofile);

	ofile << "</users>" << endl;

}

// add item at index to users cart
void mydatastore::add(string userName, Product* p) {
	if (users_.find(userName) != users_.end() && products_.find(p) != products_.end()) { // if the username and product exists add it
		
		cart_[userName].push_back(p);
    }
    else {
        cout << "Invalid request" << endl;
    }
}

void mydatastore::display(std::string userName) {

	if (users_.find(userName) != users_.end()) { // does username exist
		// grab user cart
		vector<Product*> uCart = cart_[userName];

		int count = 1;
		// print every item in cart and return true
		for (vector<Product*>::iterator it = uCart.begin(); it != uCart.end(); ++it) {
			cout << "Item " << count << endl;
			cout << (*it)->displayString() << "\n" << endl;
			count++;
		}
	
	} else cout << "Invalid username" << endl; // not valid user

}

void mydatastore::buy(std::string userName) {
  // Ensure valid user exists
    if (users_.find(userName) == users_.end()) {  
        cout << "Invalid username" << endl;  
        return; // Exit immediately if user is not found
    }

    // Ensure user has a cart before proceeding
    if (cart_.find(userName) == cart_.end() || cart_.at(userName).empty()) {
        return; // No cart to process, exit early
    }

    // Grab user object
    User* user_temp = users_[userName];

		// must use while loop because of unknown quantities of objects
		vector<Product*>::iterator it = cart_[userName].begin();
		
		while (it != cart_[userName].end()) { // loop through cart
			// create temp current product
			Product* prod_temp(*it);

			// if it exits add to the quanitiy
			if (prod_temp->getQty() > 0 && prod_temp->getPrice() <= user_temp->getBalance()) {

				// create second it
				vector<Product*>::iterator it2 = it;
 
				prod_temp->subtractQty(1); // take from user cart
				
				user_temp->deductAmount(prod_temp->getPrice()); // take from user balance
				
				cart_[userName].erase(it2); // erase after updating qty

			} 
            else {
                ++it;
            }
		}
	}