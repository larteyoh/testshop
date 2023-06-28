#pragma once

#ifndef BACKEND_HPP_NEROSHOP
#define BACKEND_HPP_NEROSHOP

#include <QObject>
#include <QUrl>
#include <QString>
#include <QStringList>

#include "wallet_controller.hpp"
#include "user_controller.hpp"

#include <iostream>

namespace neroshop {
class Backend : public QObject { // This class was created for storing utility functions and backend implementations // Maybe I should rename this to BackendTools?
    Q_OBJECT 
public:
    Backend(QObject *parent = nullptr);
    ~Backend();
    
    //Q_PROPERTY(int categoryProductCount READ getCategoryProductCount NOTIFY categoryProductCountChanged)
    //Q_PROPERTY(QVariantList searchResults READ getSearchResults NOTIFY searchResultsChanged)

    Q_INVOKABLE QString urlToLocalFile(const QUrl& url) const;
    Q_INVOKABLE void copyTextToClipboard(const QString& text);

    Q_INVOKABLE QStringList getCurrencyList() const;
    Q_INVOKABLE int getCurrencyDecimals(const QString& currency) const;
    Q_INVOKABLE QString getCurrencySign(const QString& currency) const;
    Q_INVOKABLE bool isSupportedCurrency(const QString& currency) const;
    
    /*Q_INVOKABLE */static void initializeDatabase(); // Cannot be a Q_INVOKABLE since it will only be used in C++
    static std::string getDatabaseHash();
    // TODO: Use Q_ENUM for sorting in order by a specific column (e.e Sort.Name, Sort.Id)
    Q_INVOKABLE QVariantList getCategoryList(bool sort_alphabetically = false) const;
    //Q_INVOKABLE QStringList getSubCategoryList(int category_id);
    Q_INVOKABLE int getCategoryIdByName(const QString& category_name) const;
    Q_INVOKABLE int getCategoryProductCount(int category_id) const; // returns number of products that fall under a specific category
    
    Q_INVOKABLE QVariantList getNodeList(const QString& coin) const;
    Q_INVOKABLE QVariantList getNodeListDefault(const QString& coin) const;
    Q_INVOKABLE bool isWalletDaemonRunning() const;

    QVariantList validateDisplayName(const QString& display_name) const; // Validates display name based on regex requirements
    QVariantList checkDisplayName(const QString& display_name) const; // Checks database for display name availability
    
    Q_INVOKABLE QVariantList registerUser(WalletController* wallet_controller, const QString& display_name, UserController * user_controller);
    Q_INVOKABLE bool loginWithWalletFile(WalletController* wallet_controller, const QString& path, const QString& password, UserController * user_controller);
    Q_INVOKABLE bool loginWithMnemonic(WalletController* wallet_controller, const QString& mnemonic, UserController * user_controller);
    Q_INVOKABLE bool loginWithKeys(WalletController* wallet_controller, UserController * user_controller);
    Q_INVOKABLE bool loginWithHW(WalletController* wallet_controller, UserController * user_controller);
    
    Q_INVOKABLE QVariantList getListings(); // Products listed by sellers
    Q_INVOKABLE QVariantList getListingsByCategory(int category_id);
    Q_INVOKABLE QVariantList getListingsByMostRecent();
    Q_INVOKABLE QVariantList getListingsByOldest();
    Q_INVOKABLE QVariantList getListingsByAlphabeticalOrder();
    Q_INVOKABLE QVariantList getListingsByPriceLowest();
    Q_INVOKABLE QVariantList getListingsByPriceHighest();
    //Q_INVOKABLE QVariantList getListingsByMostFavorited();
    //Q_INVOKABLE QVariantList getListingsByMostSales();
    //Q_INVOKABLE QVariantList getProducts(); // Registered products
    Q_INVOKABLE QVariantList getListingsByMostRecentLimit(int limit);
    
    Q_INVOKABLE QVariantList getSearchResults(const QString& search_term, int count = 1000); // count is the maximum number of search results (total). The search results (per page) can be between 10-100 or 50-100
    
    // Products should be registered so that sellers can list pre-existing products without the need to duplicate a product which is unnecessary and can make the database bloated
    Q_INVOKABLE bool createFolders();
    Q_INVOKABLE QVariantMap uploadProductImage(const QString& filename, int image_id);
    Q_INVOKABLE bool saveProductImage(const QString& fileName, const QString& listingKey);    
    Q_INVOKABLE QVariantList getProductImages(const QString& product_id);
    Q_INVOKABLE int getProductStarCount(const QString& product_id);
    Q_INVOKABLE int getProductStarCount(const QString& product_id, int star_number);
    Q_INVOKABLE float getProductAverageStars(const QString& product_id);
    
    Q_INVOKABLE QString getDisplayNameById(const QString& user_id);
    
    Q_INVOKABLE int getCartMaximumItems();
    Q_INVOKABLE int getCartMaximumQuantity();
    
    Q_INVOKABLE int getStockAvailable(const QString& product_id);
    
    Q_INVOKABLE QVariantList getInventory(const QString& user_id);
    
    Q_INVOKABLE void createOrder(UserController * user_controller, const QString& shipping_address);
    
    static int deleteExpiredOrders();

signals:
    //void categoryProductCountChanged();//(int category_id);
    //void searchResultsChanged();
private:
};
}
#endif
