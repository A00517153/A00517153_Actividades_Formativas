#ifndef FUNCIONES_H
#define FUNCIONES_H

using namespace std;

long int sumaIterativa(long int n){
  long int suma = 0;
  for(long int i=1; i<=n; i++){
    suma+=i;
  }
  return suma;
}

long int sumaRecursiva(long int n){
  if(n>0){
    return sumaRecursiva(n-1) + n;
  } else {
    return 0;
  }
}

long int sumaDirecta(long int n){
  if(n>0){
    return (n+1)*n/2;
  } else {
    return 0;
  }
  
}

#endif