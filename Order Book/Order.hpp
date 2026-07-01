#ifndef ORDER_HPP
#define ORDER_HPP
#include "common.hpp"
struct Order {

    string id; //unique identifier for a order
    string symbol; //ticker
    string type; //Buy or Sell order
    string order_type;
    ll quantity;
    ll remaining_quantity;
    ll price;
    ll time_stamp;

    Order(const string& id,const string& symbol,const string& order_type,const string& type,
        ll quantity,ll price,ll time):id(id),symbol(symbol),
        order_type(order_type),type(type),quantity(quantity),price(price),time_stamp(time),remaining_quantity(quantity){}

};

struct OrderLocation{
    bool is_buy;
    ll price;
    list<Order>::iterator it;
       OrderLocation() {}
    OrderLocation(bool is_buy,ll price,list<Order>::iterator it):is_buy(is_buy),price(price),it(it){}
};
#endif
