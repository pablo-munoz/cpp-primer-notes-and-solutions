// Exercise 15.29, page 779
//
// Repeat your program, but this time store shared_ptrs to objects of
// type Quote. Explain any discrepancy in the sum generated by the
// this version and the previous program. If there is no discrepancy,
// explain why there isn’t one.

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Quote.h"

class Disc_quote : public Quote {
public:
  Disc_quote() = default;
  Disc_quote(const std::string &book, double price, std::size_t qty, double disc):
    Quote(book, price), quantity(qty), discount(disc) {}
  double net_price(std::size_t) const = 0;
protected:
  std::size_t quantity = 0;
  double discount = 0.0;
};

class Bulk_quote : public Disc_quote {
public:
  Bulk_quote() = default;
  Bulk_quote(const std::string &book, double price, std::size_t qty, double disc):
    Disc_quote(book, price, qty, disc) {}
  double net_price(std::size_t num) const {
    return (num > quantity) ? (1-discount)*price*num : price*num;
  }
};

int main(int argc, char *argv[argc])
{
  std::vector<std::shared_ptr<Quote>> quote_vec;

  quote_vec.push_back(std::make_shared<Quote>("123-456", 10));
  quote_vec.push_back(std::make_shared<Bulk_quote>("123-456", 15, 5, 0.15));

  for (auto &q : quote_vec) {
    std::cout << q->net_price(10) << std::endl;
  }
  
  return 0;
}
