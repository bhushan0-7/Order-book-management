
#include <iostream>
#include <map>
#include <deque>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

enum Side { BUY, SELL };

struct Order {
    int id;
    Side side;
    int price;
    int qty;
    bool active;

    Order(int i, Side s, int p, int q)
        : id(i), side(s), price(p), qty(q), active(true) {}
};

struct Trade {
    int buyId;
    int sellId;
    int price;
    int qty;
};

class MatchingEngine {
    map<int, deque<Order*>, greater<int>> buyBook;
    map<int, deque<Order*>> sellBook;

    unordered_map<int, Order*> orderLookup;
    vector<Trade> trades;
    int nextId = 1;

    void cleanupFront(deque<Order*>& q) {
        while (!q.empty() &&
              (!q.front()->active || q.front()->qty == 0))
            q.pop_front();
    }

    void matchBuy(Order* incoming) {
        while (incoming->qty > 0 && !sellBook.empty()) {
            auto it = sellBook.begin();

            if (incoming->price != -1 &&
                it->first > incoming->price)
                break;

            auto &q = it->second;
            cleanupFront(q);

            while (!q.empty() && incoming->qty > 0) {
                Order* sell = q.front();

                int traded = min(incoming->qty, sell->qty);

                trades.push_back(
                    {incoming->id, sell->id, sell->price, traded});

                incoming->qty -= traded;
                sell->qty -= traded;

                if (sell->qty == 0) {
                    sell->active = false;
                    q.pop_front();
                }
            }

            cleanupFront(q);
            if (q.empty()) sellBook.erase(it);
        }

        if (incoming->qty > 0 && incoming->price != -1)
            buyBook[incoming->price].push_back(incoming);
        else if (incoming->qty == 0)
            incoming->active = false;
    }

    void matchSell(Order* incoming) {
        while (incoming->qty > 0 && !buyBook.empty()) {
            auto it = buyBook.begin();

            if (incoming->price != -1 &&
                it->first < incoming->price)
                break;

            auto &q = it->second;
            cleanupFront(q);

            while (!q.empty() && incoming->qty > 0) {
                Order* buy = q.front();

                int traded = min(incoming->qty, buy->qty);

                trades.push_back(
                    {buy->id, incoming->id, buy->price, traded});

                incoming->qty -= traded;
                buy->qty -= traded;

                if (buy->qty == 0) {
                    buy->active = false;
                    q.pop_front();
                }
            }

            cleanupFront(q);
            if (q.empty()) buyBook.erase(it);
        }

        if (incoming->qty > 0 && incoming->price != -1)
            sellBook[incoming->price].push_back(incoming);
        else if (incoming->qty == 0)
            incoming->active = false;
    }

public:
    int limitOrder(Side side, int price, int qty) {
        Order* o = new Order(nextId++, side, price, qty);
        orderLookup[o->id] = o;

        if (side == BUY) matchBuy(o);
        else matchSell(o);

        return o->id;
    }

    void marketOrder(Side side, int qty) {
        Order* o = new Order(nextId++, side, -1, qty);

        if (side == BUY) matchBuy(o);
        else matchSell(o);

        delete o;
    }

    void cancelOrder(int id) {
        auto it = orderLookup.find(id);
        if (it == orderLookup.end()) return;

        it->second->active = false;
        it->second->qty = 0;
    }

    void modifyOrder(int id, int newPrice, int newQty) {
        auto it = orderLookup.find(id);
        if (it == orderLookup.end()) return;

        Order* old = it->second;
        if (!old->active) return;

        Side s = old->side;
        cancelOrder(id);
        limitOrder(s, newPrice, newQty);
    }

    void printTrades() {
        cout << "\n=== TRADE HISTORY ===\n";
        for (auto &t : trades) {
            cout << "BUY#" << t.buyId
                 << " SELL#" << t.sellId
                 << " PRICE=" << t.price
                 << " QTY=" << t.qty << "\n";
        }
    }

    void printBook() {
        cout << "\n=== BUY BOOK ===\n";
        for (auto &lvl : buyBook) {
            for (auto *o : lvl.second) {
                if (o->active && o->qty > 0)
                    cout << "ID=" << o->id
                         << " P=" << o->price
                         << " Q=" << o->qty << "\n";
            }
        }

        cout << "\n=== SELL BOOK ===\n";
        for (auto &lvl : sellBook) {
            for (auto *o : lvl.second) {
                if (o->active && o->qty > 0)
                    cout << "ID=" << o->id
                         << " P=" << o->price
                         << " Q=" << o->qty << "\n";
            }
        }
    }
};

int main() {
    MatchingEngine engine;

    /*
    Commands:

    BUY price qty
    SELL price qty

    MARKET_BUY qty
    MARKET_SELL qty

    CANCEL id

    MODIFY id newPrice newQty

    PRINT
    END
    */

    string cmd;

    while (cin >> cmd) {
        if (cmd == "END") break;

        if (cmd == "BUY") {
            int p,q;
            cin >> p >> q;
            cout << "OrderID="
                 << engine.limitOrder(BUY,p,q)
                 << "\n";
        }
        else if (cmd == "SELL") {
            int p,q;
            cin >> p >> q;
            cout << "OrderID="
                 << engine.limitOrder(SELL,p,q)
                 << "\n";
        }
        else if (cmd == "MARKET_BUY") {
            int q;
            cin >> q;
            engine.marketOrder(BUY,q);
        }
        else if (cmd == "MARKET_SELL") {
            int q;
            cin >> q;
            engine.marketOrder(SELL,q);
        }
        else if (cmd == "CANCEL") {
            int id;
            cin >> id;
            engine.cancelOrder(id);
        }
        else if (cmd == "MODIFY") {
            int id,p,q;
            cin >> id >> p >> q;
            engine.modifyOrder(id,p,q);
        }
        else if (cmd == "PRINT") {
            engine.printTrades();
            engine.printBook();
        }
    }

    engine.printTrades();
    engine.printBook();
}
