#ifndef FUNCIONES_H
#define FUNCIONES_H

using namespace std;

unsigned long int sumaIterativa(unsigned long int n){
  unsigned long int suma = 0;
  for(unsigned long int i=1; i<=n; i++){
    suma+=i;
  }
  return suma;
}

unsigned long int sumaRecursiva(unsigned long int n){
  if(n>0){
    return sumaRecursiva(n-1) + n;
  } else {
    return 0;
  }
}

unsigned long int sumaDirecta(unsigned long int n){
  return (n+1)*n/2;  
}

#endif