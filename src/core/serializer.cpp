#include "serializer.hpp"

#include "crypto/sha3.hpp"//#include "../../crypto/sha3.hpp"
#include "tools/string.hpp"

#include <nlohmann/json.hpp>

/** Thoughts and ideas: I think cart and wishlist data should be stored locally in the database file:
    1. Data privacy: By storing cart and wishlist data locally, you can ensure that sensitive information is not shared across the network or exposed to unauthorized users. This can help to protect users' privacy and ensure that their data is secure.
    2. Performance: Retrieving data from a local database file can be faster than accessing data stored in a DHT, since it does not require network communication. This can help to improve the performance of your application and provide a better user experience.
    3. Ease of implementation: Storing data locally in a database file can be easier to implement and maintain than using a DHT. You can use a variety of database technologies and libraries to store and manage your data, and you may be able to take advantage of existing tools and frameworks to simplify development.

Suggestions from ChatGPT:
If each product has a unique UUID, then you can use the UUID as the key in your DHT. This will ensure that each product can be easily and efficiently retrieved by its UUID, without having to hash the entire product dictionary or the product image metadata. Using the UUID as the key also has the added advantage of making the key more human-readable and easier to work with, since UUIDs are usually represented as strings.

However, if you still want to use a hash as the key, you can use a hash of the UUID. This will ensure that each product still has a unique key, while also keeping the size of the key relatively small.

Using a hash of the entire product dictionary or the product image metadata as the key may be less efficient, as it will require more processing power to compute the hash and may result in larger keys. Additionally, it may not be necessary to hash the entire dictionary or image metadata if the UUID already provides a unique identifier for the product.



Yes, you are correct. In a DHT, it's important that the keys for storing and retrieving data are consistent with the key used for routing. The node ID is typically a cryptographic hash and is used for routing, so the key used for storing and retrieving data should also be a hash to ensure that the DHT functions properly.

In your case, if you want to use a UUID as the primary identifier for products, you could hash the UUID to generate a key that can be used in the DHT. Alternatively, you could include the UUID as a field within the product dictionary and hash the entire dictionary to generate the key for the DHT.
**/

namespace neroshop_crypto = neroshop::crypto;
namespace neroshop_string = neroshop::string;

// both info hashes (keys) and node ids should use the same hash function to ensure that the distance metric used in the Kademlia routing table is consistent and nodes can effectively search for and store information. Additionally, it simplifies the implementation of the routing table and node lookup algorithms, as only one hash function needs to be used throughout the system.

//-----------------------------------------------------------------------------

static std::string extract_hash(const std::string& str) { // extracts hash after separator
    size_t separator_pos = str.find_first_of("_-");
    if (separator_pos == std::string::npos) {
        // Separator not found in string
        return "";
    }
    return str.substr(separator_pos + 1);
}

static std::string extract_prefix(const std::string& str) {
    size_t separator_pos = std::min(str.find("_"), str.find("-"));
    std::string name_prefix = separator_pos == std::string::npos ? str : str.substr(0, separator_pos);
    return name_prefix;
}

//-----------------------------------------------------------------------------

std::pair<std::string, std::vector<uint8_t>> neroshop::Serializer::serialize(const neroshop::Object& obj) {
    std::string name_prefix = "";
    nlohmann::json json_object = {};
    
    if(std::holds_alternative<Seller>(obj)) {
        name_prefix = "user";
        const Seller& seller = std::get<Seller>(obj);
        json_object["display_name"] = seller.get_name();
        json_object["monero_address"] = seller.get_id(); // used as identifier
        std::string public_key = seller.get_public_key();
        if(!public_key.empty()) json_object["public_key"] = public_key;
        //json_object["avatar"] = ; // TODO: Avatars
    }
    
    if(std::holds_alternative<Product>(obj)) {
        name_prefix = "product";
        const Product& product = std::get<Product>(obj);
        json_object["id"] = product.get_id();
        json_object["name"] = product.get_name();
        json_object["description"] = product.get_description();
        for (const auto& attr : product.get_attributes()) {
            nlohmann::json attribute_obj = {};
            if (!attr.color.empty()) attribute_obj["color"] = attr.color;
            if (!attr.size.empty()) attribute_obj["size"] = attr.size;
            if (attr.weight != 0.0) attribute_obj["weight"] = attr.weight;
            if (!attr.material.empty()) attribute_obj["material"] = attr.material;
            bool dimensions_empty = (std::get<0>(attr.dimensions) == 0.0 && std::get<1>(attr.dimensions) == 0.0 && std::get<2>(attr.dimensions) == 0.0) || (std::get<3>(attr.dimensions).empty()); // make sure either all values in the dimensions tuple contains non-zero values or a non-empty string
            if (!dimensions_empty) {
                std::string format = neroshop_string::lower(std::get<3>(attr.dimensions));
                format.erase(std::remove_if(format.begin(), format.end(), [](char c) { return c == 'x' || c == '-' || c == ' '; }), format.end());
                nlohmann::json dimensions_obj = {};
                if(format == "dh") {
                    dimensions_obj["diameter"] = std::get<0>(attr.dimensions);
                    dimensions_obj["height"] = std::get<1>(attr.dimensions);
                }                
                if(format == "wdh") {
                    dimensions_obj["width"] = std::get<0>(attr.dimensions);
                    dimensions_obj["depth"] = std::get<1>(attr.dimensions);
                    dimensions_obj["height"] = std::get<2>(attr.dimensions);
                }
                if(format == "lwh") {
                    if(std::get<0>(attr.dimensions) != 0.0) dimensions_obj["length"] = std::get<0>(attr.dimensions);
                    dimensions_obj["width"] = std::get<1>(attr.dimensions);
                    if(std::get<2>(attr.dimensions) != 0.0) dimensions_obj["height"] = std::get<2>(attr.dimensions);
                }
                attribute_obj["dimensions"] = dimensions_obj;
            }
            if (!attr.brand.empty()) attribute_obj["brand"] = attr.brand;
            if (!attr.model.empty()) attribute_obj["model"] = attr.model;
            if (!attr.manufacturer.empty()) attribute_obj["manufacturer"] = attr.manufacturer;
            if (!attr.country_of_origin.empty()) attribute_obj["country_of_origin"] = attr.country_of_origin;
            if (!attr.warranty_information.empty()) attribute_obj["warranty_information"] = attr.warranty_information;
            if (!attr.product_code.empty()) attribute_obj["product_code"] = attr.product_code;
            if (!attr.style.empty()) attribute_obj["style"] = attr.style;
            if (!attr.gender.empty()) attribute_obj["gender"] = attr.gender;
            if (attr.age_range.second > 0) {
                nlohmann::json age_range_obj = {};
                age_range_obj["min"] = attr.age_range.first;
                age_range_obj["max"] = attr.age_range.second;
                attribute_obj["age_range"] = age_range_obj;
            }
            if (!attr.energy_efficiency_rating.empty()) attribute_obj["energy_efficiency_rating"] = attr.energy_efficiency_rating;
            if (!attr.safety_features.empty()) {
                nlohmann::json safety_features_array = nlohmann::json::array();
                for (const auto& feature : attr.safety_features) {
                    safety_features_array.push_back(feature);
                }
                attribute_obj["safety_features"] = safety_features_array;
            }
            if (attr.quantity_per_package != 0) attribute_obj["quantity_per_package"] = attr.quantity_per_package;
            if (!attr.release_date.empty()) attribute_obj["release_date"] = attr.release_date;
            json_object["attributes"].push_back(attribute_obj); // rename to "variants" or "variant_options"?
        }
        std::string product_code = product.get_code();
        if(!product_code.empty()) json_object["code"] = product_code; // can be left empty esp. if variants have their own product codes
        json_object["category_id"] = product.get_category_id(); // TODO: just use a category string
        int subcategory_id = product.get_subcategory_id();
        if(subcategory_id != -1) json_object["subcategory_id"] = subcategory_id; // TODO: just use a subcategory string
        std::vector<std::string> tags = product.get_tags();
        if (!tags.empty()) {
            nlohmann::json tags_array = {};
            for (const auto& tag : tags) {
                tags_array.push_back(tag);
            }
            json_object["tags"] = tags_array;
        }
        //json_object["images"] = // TODO: Product Images
    }
    
    if(std::holds_alternative<Listing>(obj)) {
        name_prefix = "listing";
        const Listing& listing = std::get<Listing>(obj);
        json_object["id"] = listing.get_id();
        json_object["product_id"] = listing.get_product_id();
        json_object["seller_id"] = listing.get_seller_id();
        json_object["quantity"] = listing.get_quantity();
        json_object["price"] = listing.get_price();
        json_object["currency"] = listing.get_currency();
        json_object["condition"] = listing.get_condition();
        json_object["location"] = listing.get_location();
        json_object["date"] = listing.get_date();
    }
    
    if(std::holds_alternative<Cart>(obj)) { 
        name_prefix = "cart";
        const Cart& cart = std::get<Cart>(obj);
        json_object["id"] = cart.get_id();
        json_object["owner_id"] = cart.get_owner_id();
        for (const auto& item : cart.contents) {
            nlohmann::json cart_item_obj = {};
            cart_item_obj["product_id"] = std::get<0>(item);
            cart_item_obj["quantity"] = std::get<1>(item);
            cart_item_obj["seller_id"] = std::get<2>(item);
            json_object["contents"].push_back(cart_item_obj); // cart_items // TODO: encrypt cart contents
        }
    }
    
    if(std::holds_alternative<Order>(obj)) {
        name_prefix = "order";
        const Order& order = std::get<Order>(obj);
        json_object["id"] = order.get_id();
        json_object["created_at"] = order.get_date();
        json_object["status"] = order.get_status_as_string();
        json_object["customer_id"] = order.get_customer_id();
        json_object["subtotal"] = order.get_subtotal();
        json_object["discount"] = order.get_discount();
        json_object["shipping_cost"] = order.get_shipping_cost();
        json_object["total"] = order.get_total();
        json_object["payment_option"] = order.get_payment_option_as_string();
        if(order.get_payment_coin() != PaymentCoin::None) json_object["coin"] = order.get_payment_coin_as_string();
        json_object["delivery_option"] = order.get_delivery_option_as_string();
        json_object["notes"] = order.get_notes(); // TODO: encrypt notes
        for(const auto& item : order.get_items()) {
            nlohmann::json order_item_obj = {};
            order_item_obj["product_id"] = std::get<0>(item);
            order_item_obj["quantity"] = std::get<1>(item);
            order_item_obj["seller_id"] = std::get<2>(item);
            json_object["items"].push_back(order_item_obj); // order_items // TODO: encrypt order items
        }
    }
    
    if(std::holds_alternative<ProductRating>(obj)) {
        name_prefix = "product_rating";
        const ProductRating& product_rating = std::get<ProductRating>(obj);
        json_object["product_id"] = product_rating.product_id;
        json_object["stars"] = product_rating.stars;
        json_object["rater_id"] = product_rating.rater_id;
        json_object["comments"] = product_rating.comments;
        json_object["signature"] = product_rating.signature;
    }
    
    if(std::holds_alternative<SellerRating>(obj)) {
        name_prefix = "seller_rating";
        const SellerRating& seller_rating = std::get<SellerRating>(obj);
        json_object["seller_id"] = seller_rating.seller_id;
        json_object["score"] = seller_rating.score;
        json_object["rater_id"] = seller_rating.rater_id;
        json_object["comments"] = seller_rating.comments;
        json_object["signature"] = seller_rating.signature;
    }    
    // TODO: Favorites (wishlists). EDIT: Favorites won't be stored in the DHT but will be stored locally
    // Use versioning or timestamping for updating values in DHT. Keys remain the same.
    //-------------------------------------------------------------
    assert(!name_prefix.empty() && "Invalid neroshop object type");
    // Get the `value`
    std::string value = json_object.dump();
    // Convert the string to a byte string (UTF-8 encoding) in case we ever decide to store values as bytes instead of as json string
    std::vector<uint8_t> value_bytes = nlohmann::json::to_msgpack(json_object);
    // Generate `key` by hashing the value
    std::string key = neroshop_crypto::sha3_256(value);//std::string key = neroshop_crypto::sha3_256(value_bytes);
    //-------------------------------------------------------------
    #ifdef NEROSHOP_DEBUG
    std::cout << json_object.dump(4) << "\n";
    
    std::cout << "\nkey (hash of value): " << key << "\n";
    std::cout << "value: " << value << "\n";
    std::cout << "bytes (to_msgpack):\n";
    for (auto byte : value_bytes) {
        std::cout << std::hex << (int)byte << " "; // A hex string is simply a way of representing data in hexadecimal format, which is commonly used for representing binary data in a human-readable form.
    }
    std::cout << "\njson (from msgpack):\n";
    nlohmann::json bytes_to_json = nlohmann::json::from_msgpack(value_bytes);
    std::cout << bytes_to_json << "\n";
    assert(value == bytes_to_json.dump()); // The value should be the same as the bytes dumped
    #endif
    
    // Return key-value pair
    return std::make_pair(name_prefix + "_" + key, value_bytes);
}

//-----------------------------------------------------------------------------

std::shared_ptr<neroshop::Object> neroshop::Serializer::deserialize(const std::pair<std::string, std::vector<uint8_t>>& data, std::size_t length) {//const neroshop::Object& neroshop::Serializer::deserialize(const std::pair<std::string, std::vector<uint8_t>>& data) {
    // First element of the pair is the key
    std::string key = data.first;//extract_hash(data.first);
    // Second element of the pair is the serialized value
    std::vector<uint8_t> serialized_value = data.second;
    // Deserialize the value
    nlohmann::json value = nlohmann::json::from_msgpack(serialized_value);
    ////std::string json_string = value.dump();
    // Deserialize the JSON object and create the appropriate variant object
    std::string name_prefix = extract_prefix(key);
    std::shared_ptr<neroshop::Object> variant_object;
    if(name_prefix == "user") {
        Seller seller;
        //variant_object = std::make_shared<Object>(seller);//std::make_shared<Object>(std::move(seller));
    }
    
    if(name_prefix == "product") {
        Product product; // initialize the Product object
        product.set_id(value["id"].get<std::string>());
        product.set_name(value["name"].get<std::string>());
        product.set_description(value["description"].get<std::string>());
        assert(value["attributes"].is_array());
        for (const auto& attribute : value["attributes"]) {
            Attribute attr {};
            if (attribute.contains("color")) attr.color = attribute["color"].get<std::string>();
            if (attribute.contains("size")) attr.size = attribute["size"].get<std::string>();
            if (attribute.contains("weight")) attr.weight = attribute["weight"].get<double>();
            if (attribute.contains("material")) attr.material = attribute["material"].get<std::string>();
            if (attribute.contains("brand")) attr.brand = attribute["brand"].get<std::string>();
            if (attribute.contains("model")) attr.model = attribute["model"].get<std::string>();
            if (attribute.contains("manufacturer")) attr.manufacturer = attribute["manufacturer"].get<std::string>();
            if (attribute.contains("country_of_origin")) attr.country_of_origin = attribute["country_of_origin"].get<std::string>();
            if (attribute.contains("warranty_information")) attr.warranty_information = attribute["warranty_information"].get<std::string>();
            if (attribute.contains("product_code")) attr.product_code = attribute["product_code"].get<std::string>();
            if (attribute.contains("style")) attr.style = attribute["style"].get<std::string>();
            if (attribute.contains("gender")) attr.gender = attribute["gender"].get<std::string>();
            if (attribute.contains("energy_efficiency_rating")) attr.energy_efficiency_rating = attribute["energy_efficiency_rating"];
            if (attribute.contains("release_date")) attr.release_date = attribute["release_date"];
        
            if (attribute.contains("dimensions")) {
                nlohmann::json dimensions_obj = attribute["dimensions"];
                if (dimensions_obj.contains("diameter")) {
                    attr.dimensions = std::make_tuple(dimensions_obj["diameter"], dimensions_obj["height"], 0.0, "DH");
                } else if (dimensions_obj.contains("width") && dimensions_obj.contains("depth") && dimensions_obj.contains("height")) {
                    attr.dimensions = std::make_tuple(dimensions_obj["width"], dimensions_obj["depth"], dimensions_obj["height"], "WDH");
                } else if (dimensions_obj.contains("length") && dimensions_obj.contains("width") && dimensions_obj.contains("height")) {
                    attr.dimensions = std::make_tuple(dimensions_obj["length"], dimensions_obj["width"], dimensions_obj["height"], "LWH");
                }
            }
        
            if (attribute.contains("age_range")) {
                nlohmann::json age_range_obj = attribute["age_range"];
                if (age_range_obj.contains("min") && age_range_obj.contains("max")) {
                    attr.age_range = std::make_pair(age_range_obj["min"], age_range_obj["max"]);
                }
            }
        
            if (attribute.contains("safety_features")) {
                nlohmann::json safety_features_array = attribute["safety_features"];
                if (safety_features_array.is_array()) {
                    for (const auto& feature : safety_features_array) {
                        if (!feature.empty()) {
                            attr.safety_features.push_back(feature);
                        }
                    }
                }
            }
        
            if (attribute.contains("quantity_per_package")) {
                attr.quantity_per_package = attribute["quantity_per_package"];
            }
        
            product.add_attribute(attr);
        }
        if (value.contains("code")) product.set_code(value["code"].get<std::string>());
        product.set_category_id(value["category_id"].get<int>());
        if (value.contains("subcategory_id")) product.set_subcategory_id(value["subcategory_id"].get<int>());
        if (value.contains("tags")) product.set_tags(value["tags"].get<std::vector<std::string>>());
        product.print_product();
        variant_object = std::make_shared<Object>(std::move(product)); // move the object into the shared_ptr
    }
    
    if(name_prefix == "listing") {
        Listing listing;
        listing.set_id(value["id"].get<std::string>());
        listing.set_product_id(value["product_id"].get<std::string>());
        listing.set_seller_id(value["seller_id"].get<std::string>());
        listing.set_quantity(value["quantity"].get<int>());
        listing.set_price(value["price"].get<double>());
        listing.set_currency(value["currency"].get<std::string>());
        listing.set_condition(value["condition"].get<std::string>());
        listing.set_location(value["location"].get<std::string>());
        listing.set_date(value["date"].get<std::string>());
        variant_object = std::make_shared<Object>(std::move(listing));
    }
    
    if(name_prefix == "cart") {
        Cart cart;
        cart.set_id(value["id"].get<std::string>());
        cart.set_owner_id(value["owner_id"].get<std::string>());
        assert(value["contents"].is_array());
        std::vector<std::tuple<std::string, int, std::string>> cart_items;
        for (const auto& item : value["contents"]) {
            std::string product_id = item["product_id"].get<std::string>();
            int quantity = item["quantity"].get<int>();
            std::string seller_id = item["seller_id"].get<std::string>();
            cart_items.emplace_back(product_id, quantity, seller_id);
        }
        cart.set_contents(cart_items);
        variant_object = std::make_shared<Object>(cart);
    }
    
    if(name_prefix == "order") {
        Order order;
        order.set_id(value["id"].get<std::string>());
        order.set_date(value["created_at"].get<std::string>());
        order.set_status_by_string(value["status"].get<std::string>());
        order.set_customer_id(value["customer_id"].get<std::string>());
        order.set_subtotal(value["subtotal"].get<double>());
        order.set_discount(value["discount"].get<double>());
        order.set_shipping_cost(value["shipping_cost"].get<double>());
        order.set_total(value["total"].get<double>());
        order.set_payment_option_by_string(value["payment_option"].get<std::string>());
        order.set_payment_coin_by_string(value["payment_coin"].get<std::string>());
        order.set_delivery_option_by_string(value["delivery_option"].get<std::string>());
        order.set_notes(value["notes"].get<std::string>());
        assert(value["items"].is_array()); // items should be an array of objects
        std::vector<std::tuple<std::string, int, std::string>> order_items;
        for (const auto& item : value["items"]) {
            std::string product_id = item["product_id"].get<std::string>();
            int quantity = item["quantity"].get<int>();
            std::string seller_id = item["seller_id"].get<std::string>();
            order_items.emplace_back(product_id, quantity, seller_id);
        }
        order.set_items(order_items);
        variant_object = std::make_shared<Object>(order);
    }
    
    if(name_prefix == "product_rating") {
        ProductRating product_rating;
        product_rating.rater_id = value["rater_id"].get<std::string>();
        product_rating.comments = value["comments"].get<std::string>();
        product_rating.signature = value["signature"].get<std::string>();
        product_rating.product_id = value["product_id"].get<std::string>();
        product_rating.stars = value["stars"].get<int>();
        variant_object = std::make_shared<Object>(product_rating);
    }
    
    if(name_prefix == "seller_rating") {
        SellerRating seller_rating;
        seller_rating.rater_id = value["rater_id"].get<std::string>();
        seller_rating.comments = value["comments"].get<std::string>();
        seller_rating.signature = value["signature"].get<std::string>();
        seller_rating.seller_id = value["seller_id"].get<std::string>();
        seller_rating.score = value["score"].get<int>();
        variant_object = std::make_shared<Object>(seller_rating);
    }
    // Return variant object as shared_ptr
    return variant_object;
}

//-----------------------------------------------------------------------------

template <typename... Args>
std::string neroshop::Serializer::to_json(Args&&... args) {
    nlohmann::json json_object = nlohmann::json::object({std::forward<Args>(args)...});
    return json_object.dump();
}

/*int main() {
    std::cout << neroshop::Serializer::to_json(std::make_pair("key1", 123), 
        std::make_pair("key2", "value2"), 
        std::make_pair("key3", true)) << "\n";
    std::cout << "\n";


    neroshop::Object obj = neroshop::Product { "my_product_uuid", "Nintendo Switch Lite", "A really fun gaming system", 
        {
            {.color = "yellow"   , .size = "lite", .weight = .61, .product_code = "00045496882303"}, // 0.61 lbs
            {.color = "gray"     , .size = "lite", .weight = .61, .product_code = "00045496882280"},
            {.color = "turquoise", .size = "lite", .weight = .61, .product_code = "00045496882266"},
            {.color = "coral"    , .size = "lite", .weight = .61, .product_code = "00045496882662"},
            {.color = "blue"     , .size = "lite", .weight = .61, .product_code = "00045496882716"},
        },
        "",//"my_product_code",
        0, -1,
        {"video games", "nintendo", "switch lite"}
    };
    
    neroshop::ProductRating pr = { "user1", "Good product", "signed", "product123", 4 };
    
    neroshop::SellerRating sr = { "user2", "Fast shipping", "signed", "seller456", 1 };
    
    std::pair<std::string, std::vector<uint8_t>> result = neroshop::Serializer::serialize(obj); // pass the variant to the serialize function
    std::string key = result.first;
    nlohmann::json value_json = nlohmann::json::from_msgpack(result.second);
    //std::cout << key << ": " << value_json << "\n";
    assert(neroshop_crypto::sha3_256(value_json.dump()) == extract_hash(key)); // key must be hash of value
    
    
    auto obj2 = neroshop::Serializer::deserialize(result);
    
    
    std::pair<std::string, std::vector<uint8_t>> result2 = neroshop::Serializer::serialize(*obj2); // pass the variant to the serialize function
    std::string key2 = result2.first;
    nlohmann::json value_json2 = nlohmann::json::from_msgpack(result2.second);
    //std::cout << key2 << ": " << value_json2 << "\n";
    assert(neroshop_crypto::sha3_256(value_json2.dump()) == extract_hash(key2)); // key must be hash of value
    return 0;
}*/
// g++ serializer.cpp crypto/sha3_256.cpp tools/logger.cpp price/*.cpp config.cpp script.cpp cart.cpp product.cpp listing.cpp order.cpp database/database.cpp database/sqlite.cpp -o serialize -lcrypto -lssl -I../../external/json/single_include -Icrypto -I../../external/stduuid/include -I../../external/stduuid/ -I../../external/lua/src -L../../build -lsqlite3 -lcurl -llua  

