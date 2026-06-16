#include "OrderBook.cpp"
#include <iostream>

int main(){
    unordered_map<string, OrderBook> books;
    string type;
    string id;
    string symbol;
    ll quantity;
    ll price;
    ll order_id = 1;
    ll t=0;

    while(cin>>type){
        if(type=="PRINT"){
            cin>>symbol;
            if(books.find(symbol)==books.end()) {
                cout<<"No orders for symbol: "<<symbol<<endl;
                continue;
            }
            else{
                books[symbol].printBuy_Orders();
                books[symbol].printSell_Orders();
                books[symbol].printTrades();
            }
        }
        else if(type=="CANCEL"){
            cin>>symbol>>id;
            if(books.find(symbol)==books.end()){
                cout<<"No orders for symbol: "<<symbol<<endl;
                continue;
            }
            else{
                books[symbol].cancel_order(id);
            }
        }
        else if(type=="BUY"||type=="SELL"){
            cin>>id>>symbol>>quantity>>price;
            Order o(id,symbol,type,quantity,price,t++);
             if(books.find(symbol) == books.end()) {
            OrderBook ob;
            books[symbol] = ob;
        }
        books[symbol].process_order(o);
        } 
        else if(type=="END") break; 
        else {
            cout<<"Invalid command"<<endl;
        }    
     }
}