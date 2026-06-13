#ifndef ORDER_HPP
#define ORDER_HPP
#include "common.hpp"
struct Order {

    string id; //unique identifier for a order
    string symbol; //ticker
    string type; //Buy or Sell order
    ll quantity;
    ll remaining_quantity;
    ll price;
    ll time_stamp;

    //constructer for order
    Order(string id,string symbol,string type,
        ll quantity,ll price,ll time):id(id),symbol(symbol),
        type(type),quantity(quantity),price(price),time_stamp(time),remaining_quantity(quantity){}

};
#endif
