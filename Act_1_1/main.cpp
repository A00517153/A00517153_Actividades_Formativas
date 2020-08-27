#include <iostream>
#include "funciones.h"

using namespace std;

void test(unsigned long int n){
  cout<<sumaIterativa(n)<<endl;
  cout<<sumaRecursiva(n)<<endl;
  cout<<sumaDirecta(n)<<endl;
}

int main() {
  test(0);
}