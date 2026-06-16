#include "Order.hpp"
#include "Trade.hpp"
class OrderBook{

    private:
    map<ll,list<Order>,greater<ll>> Buy;  //To store Buy Orders
    map<ll,list<Order>> Sell; //To store Sell Orders
    void match_sell_order(Order &o);
    void match_buy_order(Order &o);
    unordered_map<string,OrderLocation> order_locations;

    public:
    vector<Trade> trades;
    void addOrder(Order &o);  
    void printBuy_Orders();
    void printSell_Orders();
    void printTrades();
    void process_order(Order &o);
    void cancel_order(string order_id);
    ll bestBid();
    ll bestAsk();
};