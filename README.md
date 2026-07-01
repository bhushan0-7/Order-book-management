# Order-book-management
C++ Order Book Matching Engine supporting limit/market orders, price-time priority, cancellations, modifications, and trade execution.

## Supported Order Types

### Limit Order
Executes at the specified price or better. Any remaining quantity is added to the order book.

### Market Order
Executes immediately against the best available prices. Any unfilled quantity is discarded.

## Input Format

BUY LIMIT <order_id> <symbol> <quantity> <price>
SELL LIMIT <order_id> <symbol> <quantity> <price>

BUY MARKET <order_id> <symbol> <quantity>
SELL MARKET <order_id> <symbol> <quantity>

CANCEL <symbol> <order_id>

PRINT <symbol>

END
