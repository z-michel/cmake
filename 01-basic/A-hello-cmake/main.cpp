#include <iostream>
#include "hello_local.h"  			//Header in same directory as main.cpp
#include "hello_shared.h" 			//GN Sample project header
#include "hello_static.h"
#include "goodbye.h"      	//Header in zach-dir/ subdirectory

int main(int argc, char *argv[])
{
   std::cout << "Hello CMake!" << std::endl;
   printf("%s", GetStaticText());
   print_hello();
   print_goodbye();
   return 0;
}
