#include "order.h"
#include "Types.h"
#include <iostream>

int main(){
  Order o;
  o.ordId  = 1;
  o.instrId = 100;
  o.price = 100100;
  o.qty = 1000;
  o.isIoc = false;
  o.remaining = o.qty;
  o.side = Side::BUY;


  std:: cout << "Order created: Id = "<< o.ordId << "InstrId = "<<o.instrId << "Price = "<< o.price <<"Qty = "<<o.qty<< "\n";
  return 0;
}