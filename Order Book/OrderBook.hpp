#include "Order.hpp"
#include "Trade.hpp"
class OrderBook{

    private:
    map<ll,list<Order>,greater<ll>> Buy;  //To store Buy Orders
    map<ll,list<Order>> Sell; //To store Sell Orders
    vector<Trade> trades;
    void match_sell_order(Order &o);
    void match_buy_order(Order &o);

    public:
    void addOrder(Order &o);  
    void printBuy_Orders();
    void printSell_Orders();
    void printTrades();
    void process_order(Order &o);
    ll bestBid();
    ll bestAsk();
};