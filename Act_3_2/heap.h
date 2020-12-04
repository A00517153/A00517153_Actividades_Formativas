/*---------------
Nombre: Johann Palomino Galvan
Matricula: A00517153
Actividad: Act 3.2
---------------*/

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <string>
#include <sstream>

template <class T>
class Heap {
    private:
	    T *data;
	    unsigned int tam;
	    unsigned int cont;	    

    public:
	    Heap(unsigned int ta);
	    ~Heap();
		T pop();
	    void push(T);
	    int size();
	    int top();
	    bool empty() const;
	    bool full() const;	    
	    void clear();	 
		unsigned int parent(unsigned int) const;
	    unsigned int left(unsigned int) const;
	    unsigned int right(unsigned int) const;
	    void heapify(unsigned int);
	    void swap(unsigned int, unsigned int);
		std::string toString() const;   
};


template <class T>
Heap<T>::Heap(unsigned int ta):tam(ta),cont(0),data(new T[ta]){
	;
}

template <class T>
Heap<T>::~Heap(){
	delete [] data; 
	data=NULL;
	tam=cont=0;
}

template <class T>
T Heap<T>::pop(){
	T aux = *data;
	*data = data[--cont];
	heapify(0);
	return aux;
}

template <class T>
void Heap<T>::push(T val){
	unsigned int pos=cont;
	++cont;
	while (pos>0 && val<data[parent(pos)]) {
		data[pos]=data[parent(pos)];
		pos=parent(pos);
	}
	data[pos]=val;
}

template <class T>
int Heap<T>::size(){
	return cont;
}

template <class T>
int Heap<T>::top(){
	return *data;
}

template <class T>
bool Heap<T>::empty()const{
	return (cont==0);
}

template <class T>
bool Heap<T>::full()const{
	return (cont==tam);
}

template <class T>
void Heap<T>::clear(){
	cont=0;
}

template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const{
	return (pos-1)/2;
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const{
	return (2*pos+1);
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const{
	return (2*pos+2);
}

template <class T>
void Heap<T>::heapify(unsigned int pos){
	unsigned int le=left(pos);
	unsigned int ri=right(pos);
	unsigned int min=pos;
	
	if(le<=cont && data[le]<data[min]){min=le;}
	if(ri<=cont && data[ri]<data[min]){min=ri;}
	if(min!=pos){
		swap(pos, min);
		heapify(min);
	}
}

template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
	T aux=data[i];
	data[i]=data[j];
	data[j]=aux;
}

template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;
	aux<<"[";
	for(unsigned int i=0;i<cont;++i){
		if(i!=0){aux<<" ";}
		aux<<data[i];
	}
	aux<<"]";
	return aux.str();
}



#endif
