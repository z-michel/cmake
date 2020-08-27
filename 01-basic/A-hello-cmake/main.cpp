#include <iostream>

#include "lib/gn/examples/simple_build/hello.cc"

int main(int argc, char *argv[])
{
   std::cout << "Hello CMake!" << std::endl;
   print_hello();
   return 0;
}