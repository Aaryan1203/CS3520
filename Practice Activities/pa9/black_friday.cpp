#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include <algorithm> 
using namespace std;

// function object for sorting by the second element of pairs
int SortBySecond(const pair<string, double> &a, const pair<string, double> &b)
{
    return a.second < b.second;
};

// function object to print a store and a product
void print_store_and_product(const pair<string, string> &pair)
{
    cout << pair.first << ", best price offered by: " << pair.second << endl;
}

// function object to print every product and all of its prices
void print_every_product_price(const pair<string, vector<double>> product)
{
    cout << setw(30) << product.first;
    for (const auto &price : product.second)
    {
        cout << setw(15) << fixed << setprecision(2) << price;
    };
    cout << endl;
}

// function object to print every product and its average price
void print_average_price(const pair<string, double> &product)
{
    cout << product.first << ": " << product.second << endl;
}

int main()
{
    // Define the items and stores
    vector<string> items = {"iPhone14", "iPad Pro", "Noise Cancelling Headphones", "Back Roller", "Bike"};
    vector<string> stores = {"eBay", "Amazon", "BestBuy", "OfficeMax", "Staples"};

    map<string, vector<double>> prices;

    // adding prices to each product
    prices["iPhone14"] = {995.49, 978.99, 999.99, 1009.99, 1005.79};
    prices["iPad Pro"] = {1499.00, 1545.99, 1500.49, 1520.75, 1459.98};
    prices["Noise Cancelling Headphones"] = {299.99, 289.99, 279.99, 295.49, 285.79};
    prices["Back Roller"] = {45.99, 47.99, 42.49, 40.99, 44.79};
    prices["Bike"] = {479.99, 499.99, 509.99, 495.49, 505.79};

    // printing out each product and its price from every store
    cout << "Every product and its price from every store" << endl;
    cout << left << setw(30) << "Name";
    for (const auto &store : stores)
    {
        cout << setw(15) << store;
    }
    cout << endl;

    for_each(prices.begin(), prices.end(), print_every_product_price);
    cout << endl;

    // display the prices from all different stores
    cout << "Prices from all different stores" << endl;
    for (size_t store_num = 0; store_num < stores.size(); ++store_num)
    {
        cout << "Store Name: " << stores[store_num] << endl;
        for (const auto &item : items)
        {
            cout << setw(30) << item << setw(15) << fixed << setprecision(2) << prices[item][store_num] << endl;
        }
        cout << endl;
    }

    // map for average of product prices
    map<string, double> average_prices;
    for (const auto &item : items)
    {
        double sum = 0;
        for (const auto &price : prices[item])
        {
            sum += price;
        }
        double average = sum / prices[item].size();
        average_prices[item] = average;
    }

    // Vector to store pairs of item and average price for sorting
    vector<pair<string, double>> sorted_average_prices(average_prices.begin(), average_prices.end());

    // Sort the vector by the second element of the pairs using a function object
    sort(sorted_average_prices.begin(), sorted_average_prices.end(), SortBySecond);

    // average price of every item
    cout << "Average price of every item sorted in ascending order" << endl;
    for_each(sorted_average_prices.begin(), sorted_average_prices.end(), print_average_price);
    cout << endl;

    // map to hold the store for the best price for each product
    map<string, string> best_prices;
    for (const auto &product : prices)
    {
        int best_index = 0;
        for (int i = 1; i < prices[product.first].size(); ++i)
        {
            if (prices[product.first][i] < prices[product.first][best_index])
            {
                best_index = i;
            }
        }
        best_prices[product.first] = stores[best_index];
    }

    // prints the best store for each product
    cout << "Best store for each product" << endl;
    for_each(best_prices.begin(), best_prices.end(), print_store_and_product);
}