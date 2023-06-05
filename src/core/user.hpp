#ifndef USER_HPP_NEROSHOP
#define USER_HPP_NEROSHOP

#include <iostream>
#include <memory> // std::unique_ptr
#include <string>
#include <vector>

#include "product.hpp"
#include "order.hpp"

enum class UserAccountType : unsigned int { Guest, Buyer, Seller };

namespace neroshop {

class Cart; // forward declaration

class User { // base class of seller and buyer // sellers can buy and sell while buyers (including guests) can only buy but cannot sell
public: 
    User();
    virtual ~User(); // by making this virtual both base and derived class destructors will be called instead of just the base destructor alone
    // account-related stuff (will continue adding more account features)
    void rate_seller(const std::string& seller_id, int score, const std::string& comments, const std::string& signature); // seller score (0-1) // use int and NOT unsigned int 'cause unsigned int assumes the arg will never be negative number, but when arg is negative, it converts it to some random positive number
    void rate_item(const std::string& item_id, int stars, const std::string& comments, const std::string& signature); // star ratings (1-5)    
    void convert(); // converts buyer to seller //void revert(); // I don't see the reason for degrading your account after an upgrade hehe ... //void report_user(const User& user, const std::string& reason); // report a user
    void delete_account();
    void logout();
    // cart-related stuff (50% complete - cart class still needs some more work)
    void add_to_cart(const std::string& product_id, int quantity = 1);
    void add_to_cart(const neroshop::Product& item, int quantity = 1); // use int and NOT unsigned int 'cause unsigned int assumes the arg will never be negative number, but when arg is negative, it converts it to some random positive number
    void remove_from_cart(const std::string& product_id, int quantity = 1);
    void remove_from_cart(const neroshop::Product& item, int quantity = 1);
    void clear_cart();
    // order-related stuff (50% complete - order class still needs some more work)
    void create_order(const std::string& shipping_address);// const;//void create_order();
    // favorite-or-wishlist-related stuff (100% complete)
    void add_to_favorites(const std::string& product_id);
    void add_to_favorites(const neroshop::Product& item);
    void remove_from_favorites(const std::string& product_id);
    void remove_from_favorites(const neroshop::Product& item);
    void clear_favorites();
    // avatar-related stuff (10% complete)
    void upload_avatar(const std::string& filename);
    bool export_avatar();
    void delete_avatar();
    // setters
    void set_public_key(const std::string& public_key);
    void set_private_key(const std::string& private_key);
    // getters
    std::string get_public_key() const;
    // account-related stuff - getters
    std::string get_id() const;//unsigned int get_id() const;
    std::string get_name() const;
    UserAccountType get_account_type() const;
    std::string get_account_type_string() const;
    // buyer-related stuff - getters
    neroshop::Cart * get_cart() const;
    neroshop::Order * get_order(unsigned int index) const;
    unsigned int get_order_count() const;
    std::vector<neroshop::Order *> get_order_list() const;
    neroshop::Product * get_favorite(unsigned int index) const;
    unsigned int get_favorites_count() const;
    std::vector<neroshop::Product *> get_favorites_list() const;
    // boolean
    bool is_guest() const;
    bool is_buyer() const;
    bool is_seller() const;
    bool is_online() const; // online does not mean logged in // checks if user has internet, and user is logged_in
    bool is_registered() const;
    static bool is_registered(const std::string& name);
    bool is_logged() const; // the same for every derived class // user has entered their login information
    bool has_email() const;
    bool has_avatar() const;
    // item-related stuff - boolean
    bool has_purchased(const std::string& product_id); // checks if an item was previously purchased or not
    bool has_purchased(const neroshop::Product& item); // checks if an item was previously purchased or not
    bool has_favorited(const std::string& product_id); // checks if an item is in a user's favorites or wishlist
    bool has_favorited(const neroshop::Product& item); // checks if an item is in a user's favorites or wishlist
    // callbacks
    void on_registration(const std::string& name); // on registering an account
    //virtual User * on_login(const std::string& username);// = 0; // load all data: orders, reputation/ratings, settings // for all users
    void on_checkout();//(const neroshop::Order& order); // for all users
    virtual void on_order_received(); // for sellers only
    // friends
    friend class Backend;
    friend class UserController;
    friend class Serializer;
protected: // can only be accessed by classes that inherit from class User (even instants of the bass class User cannot call these functions unless you dynamically cast them into a derived class)
    void set_id(const std::string& id);//void set_id(unsigned int id);
    void set_name(const std::string& name); // the same for every derived class 
    void set_account_type(UserAccountType account_type); // either buyer or seller // the same for every derived class 
    void set_logged(bool logged); // the same for every derived class
    void set_online(bool online);
    // loading into memory so we don't always have to fetch from the database within the same session
    void load_cart();
    void load_orders(); // on login, load all orders this user has made so far (this function is called only once per login)
    void load_favorites(); // on login, load favorites (this function is called only once per login)
private:
    std::string id;
    std::string name;
    UserAccountType account_type; // seller, buyer (guest)
    bool logged; // determines whether user is logged in or not//bool online;
    std::string public_key;
    std::string private_key;
    std::unique_ptr<Cart> cart;
    std::vector<std::shared_ptr<neroshop::Order>> order_list;
    std::vector<std::shared_ptr<neroshop::Product>> favorites_list; // I get the error "/usr/include/c++/9/bits/stl_uninitialized.h:127:72: error: static assertion failed: result type must be constructible from value type of input range" while trying to use unique_ptr so I'm stuck with a shared_ptr container for now
    std::string get_private_key() const;
};
}
#endif
