#include <iostream>

#include "voreterator.hpp"

int main () {
  char buf[10] = "vo pitux";
  voreterator<1, 1> case_(buf, 2, 2);
  voreterator<2, 1> word (buf+3, 7);
  
  for (auto str : case_) {
    std::cout << str << std::endl;
    ++word;
  }
}
