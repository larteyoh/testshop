//#pragma once
#ifndef SELLER_HPP_NEROSHOP
#define SELLER_HPP_NEROSHOP

#include <cmath> // floor
#include <random>
#include <memory> // std::unique_ptr
#include <vector>

#include "wallet.hpp"
#include "user.hpp"
#include "item.hpp"
#include "currency_converter.hpp"

namespace neroshop {
class Seller : public User { 
public:
	Seller();
	Seller(const std::string& name);
	~Seller();
	void list_item(unsigned int item_id, unsigned int stock_qty, double sales_price = 0.00, std::string currency = "usd", double discount = 0.00, unsigned int discounted_items = 1, unsigned int discount_times = 1, std::string discount_expiry = ""/*"0000-00-00 00:00:00"*/, std::string condition = "new"); // adds an item to the inventory
	void list_item(const neroshop::Item& item, unsigned int stock_qty, double sales_price = 0.00, std::string currency = "usd", double discount = 0.00, unsigned int discounted_items = 1, unsigned int discount_times = 1, std::string discount_expiry = ""/*"0000-00-00 00:00:00"*/, std::string condition = "new");
	void delist_item(unsigned int item_id); // deletes an item from the inventory
	void delist_item(const neroshop::Item& item);
	// setters - item and inventory-related stuff
	void set_stock_quantity(unsigned int item_id, unsigned int stock_qty);
	void set_stock_quantity(const neroshop::Item& item, unsigned int stock_qty);
	// setters - wallet-related stuff
	void set_wallet(const neroshop::Wallet& wallet);// temporary - delete ASAP
	// getters - seller rating system
	unsigned int get_good_ratings() const; // returns the total number of good ratings given to this seller by their customers
	unsigned int get_bad_ratings() const; // returns the total number of bad ratings given to this seller by their customers
	unsigned int get_ratings_count() const; // returns the total number of ratings given to this seller by their customers (includes both good and bad ratings)
	unsigned int get_total_ratings() const; // same as get_ratings_count
	unsigned int get_reputation() const; // returns a percentage of good ratings
	static std::vector<unsigned int> get_top_rated_sellers(unsigned int limit = 50); // returns a container of n seller_ids with the most positive (good) ratings // the default value of n is 50
	// getters - wallet-related stuff
	neroshop::Wallet * get_wallet() const;
	// getters - order-related stuff
    unsigned int get_customer_order(unsigned int index) const;
    unsigned int get_customer_order_count() const;
    std::vector<int> get_pending_customer_orders();
    // getters - sales and statistics-related stuff
    unsigned int get_sales_count() const; // returns the total number of items sold by this seller
    unsigned int get_units_sold(unsigned int item_id) const; // returns the total number of a specific item sold by this seller
    unsigned int get_units_sold(const neroshop::Item& item) const;
    double get_sales_profit() const; // returns the overall profit made from the sale of all items sold by this seller
    double get_profits_made(unsigned int item_id) const; // returns the overall profit made from the sale of a specific item sold by this seller
    double get_profits_made(const neroshop::Item& item) const;
    unsigned int get_item_id_with_most_sales() const; // returns the item_id with the most purchases (based on biggest sum of item_qty in "order_item")
    unsigned int get_item_id_with_most_orders() const; // returns the item_id with the mode (most occuring) or the most ordered item in "order_item"
	//Item * get_item_with_most_sales() const;
	//Item * get_item_with_most_orders() const;
	// boolean
	//bool is_verified() const; // returns true if seller is verified brand owner (or original manufacturer)
	bool has_listed(unsigned int item_id) const; // returns true if this seller has listed an item
	bool has_listed(const neroshop::Item& item) const; // returns true if this seller has listed an item
	bool has_stock(unsigned int item_id) const; // returns true if this seller has an item in stock
	bool has_stock(const neroshop::Item& item) const;
	bool has_wallet() const; // returns true if seller's wallet is opened
	bool has_wallet_synced() const; // returns true if seller's wallet is synced to a node
	// callbacks
	static neroshop::User * on_login(const std::string& username);
	void on_order_received(std::string& subaddress);
	// listening to orders
	void update_customer_orders(); // called multiple times	// listens to and update customer orders
protected:
    void load_customer_orders(); // called one-time when seller logs in
private:
	std::unique_ptr<neroshop::Wallet> wallet;
	std::vector<int> customer_order_list;
};
}
#endif
