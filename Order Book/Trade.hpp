#ifndef TRADE_HPP
#define TRADE_HPP
#include "common.hpp"

struct Trade{
    string buy_order_id;
    string sell_order_id;
    string symbol;
    long long quantity;
    long long price;
    Trade(string b_id,string s_id,string symbol,long long quantity,long long price):
         buy_order_id(b_id),sell_order_id(s_id),symbol(symbol),quantity(quantity),price(price){}
};

#endif