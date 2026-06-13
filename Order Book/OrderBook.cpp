#include "OrderBook.hpp"
#include<iostream>

void OrderBook::addOrder(Order &o) {
        if(o.type=="Buy") {  
            Buy[o.price].push_back(o); //Add Buy Order
        }
        else if(o.type=="Sell") { //Add Sell Order
            Sell[o.price].push_back(o);
        }
        return;
}

void OrderBook::printBuy_Orders(){  //Print all the Buy Orders
    if(Buy.empty()) {
        cout<<"---NO BUY ORDERS---"<<endl;
        cout<<endl;
        return;
    }
    cout<<"------BUY ORDERS------"<<endl;
    cout<<"Price           Quantity"<<endl;
    for(auto& it:Buy) {
        long long price=it.first;
        long long quantity=0;
        for(auto& it1:it.second) {
            quantity+=(it1.remaining_quantity);
        }
        cout<<price<<"           "<<quantity<<endl;
    }
    cout<<endl;
    return;
}

void OrderBook::printSell_Orders(){//Print all the Sell Orders
    if(Sell.empty()) {
        cout<<"---NO SELL ORDERS---"<<endl;
        cout<<endl;
        return;
    }
    cout<<"------SELL ORDERS------"<<endl;
    cout<<"Price           Quantity"<<endl;
    for(auto& it:Sell) {
        long long price=it.first;
        long long quantity=0;
        for(auto& it1:it.second) {
            quantity+=(it1.remaining_quantity);
        }
        cout<<price<<"           "<<quantity<<endl;
    }
    cout<<endl;
    return;
}
 void OrderBook::printTrades(){
    if(trades.empty()) {
        cout<<"---NO TRADES---"<<endl;
        cout<<endl;
        return;
    }
    cout<<"------TRADES------"<<endl;
    cout<<"Buy Order ID     Sell Order ID     Symbol     Quantity     Price"<<endl;
    for(auto& it:trades) {
        cout<<it.buy_order_id<<"     "<<it.sell_order_id<<"     "<<it.symbol<<"     "<<it.quantity<<"     "<<it.price<<endl;
    }
    cout<<endl;
 }
ll OrderBook::bestBid(){
    if(Buy.empty()) return -1;
    return Buy.begin()->first;
}

ll OrderBook::bestAsk(){
    if(Sell.empty()) return -1;
    return Sell.begin()->first;
}

void OrderBook::match_sell_order(Order &o){
     while(o.remaining_quantity>0 && !Buy.empty() && o.price<=bestBid()){
        long long best_bid=bestBid();
        list<Order> &buy_orders=Buy[best_bid];
        auto it=buy_orders.begin();
        while(o.remaining_quantity>0 && it!=buy_orders.end()){
            if(it->remaining_quantity<=o.remaining_quantity){
                Trade t(it->id,o.id,o.symbol,it->remaining_quantity,it->price);
                trades.push_back(t);
                o.remaining_quantity-=it->remaining_quantity;
                it=buy_orders.erase(it);
            }
            else{
                Trade t(it->id,o.id,o.symbol,o.remaining_quantity,it->price);
                trades.push_back(t);
                it->remaining_quantity-=o.remaining_quantity;
                o.remaining_quantity=0;
            }
        }
        if(buy_orders.empty()) {
            Buy.erase(best_bid);
        }
     }
     if(o.remaining_quantity>0) {
        Sell[o.price].push_back(o);
     }
     return;
}
 void OrderBook::match_buy_order(Order &o){
        while(o.remaining_quantity>0 && !Sell.empty() && o.price>=bestAsk()){
            long long best_ask=bestAsk();
            list<Order> &sell_orders=Sell[best_ask];
            auto it=sell_orders.begin();
            while(o.remaining_quantity>0 && it!=sell_orders.end()){
                if(it->remaining_quantity<=o.remaining_quantity){
                    Trade t(o.id,it->id,o.symbol,it->remaining_quantity,it->price);
                    trades.push_back(t);
                    o.remaining_quantity-=it->remaining_quantity;
                    it=sell_orders.erase(it);
                }
                else {
                    Trade t(o.id,it->id,o.symbol,o.remaining_quantity,it->price);
                    trades.push_back(t);
                    it->remaining_quantity-=o.remaining_quantity;
                    o.remaining_quantity=0;
                }
            }
            if(sell_orders.empty()){
                Sell.erase(best_ask);
            }
        }
        if(o.remaining_quantity>0) {
            Buy[o.price].push_back(o);
        }
 }

void OrderBook::process_order(Order &o){
     if(o.type=="Buy") {
        match_buy_order(o);
    }
    else if(o.type=="Sell"){
         match_sell_order(o);
     }
}
