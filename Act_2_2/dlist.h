/*---------------
Nombre: Johann Palomino Galvan
Matricula: A00517153
Actividad: Act 2.2 
---------------*/

#ifndef DLIST_H
#define DLIST_H

#include <iostream>
#include <string>
#include <sstream>

template <class T> class DLink;
template <class T> class DList;

template <class T>
class DLink{
    private:
        DLink(T);
        DLink(T,DLink<T>*);
        DLink(DLink<T>&);
        ~DLink<T>();

        T value;
        DLink<T> *previous;
        DLink<T> *next;
        
        friend class DList<T>;
};

template <class T>
DLink<T>::DLink(T val):value(val),previous(NULL),next(NULL){}

template <class T>
DLink<T>::DLink(T val, DLink* nxt):value(val),next(nxt){}

template <class T>
DLink<T>::DLink(DLink<T> &src):
    value(src.value),previous(src.previous),next(src.next){}

template <class T>
DLink<T>::~DLink(){
    previous=next=NULL;
}

template <class T>
class DList{
    public:
        DList();
        DList(DList<T>&);
        ~DList();

        bool empty() const;
        void add_first(T);
        void add(T);
        int find(T);
        void update(int,T);
        T remove_first();
        T remove(T);

        std::string toStringForward() const;
        std::string toStringBackward() const;

    private:
        DLink<T> *head;
        DLink<T> *tail;
        int size;      
};

template <class T>
DList<T>::DList():head(NULL),size(0){}

template <class T>
DList<T>::DList(DList<T> &src):head(src->head),tail(src->tail),size(src-size){}

template <class T>
DList<T>::~DList(){
    DLink<T> *p=head, *del=p;
    while((p->next)!=tail){
        p=p->next;
        del->~DLink();
        size--;
        del=p;
    }
    del->~DLink();
    head=tail=NULL;
}

template <class T>
bool DList<T>::empty() const {return (size==0);}

template <class T>
void DList<T>::add_first(T val){
    DLink<T> *newLink=new DLink<T>(val);
    head=newLink;
    tail=newLink;
    size++;
}

template <class T>
void DList<T>::add(T val){
    DLink<T> *newLink=new DLink<T>(val);
    if(empty()){
        add_first(val);
        return;
    }
    tail->next=newLink;
    newLink->previous=tail;
    tail=newLink;
    size++;
}

template <class T>
int DList<T>::find(T val){
    int n=0;
    DLink<T> *p=head;
    while(p!=NULL){
        if(p->value==val){return n;}
        p=p->next;
        n++;
    }
    return -1;
}

template <class T>
void DList<T>::update(int pos, T val){
    int i=0;
    DLink<T> *p=head;
    while(p!=NULL){
        if(i==pos){
            p->value=val;
            break;
        }
        p=p->next;
        i++;
    }
}

template <class T>
T DList<T>::remove_first(){
    DLink<T> *p=head;
    T vRet=p->value;
    if(head!=tail){
        head=head->next;
        head->previous=NULL;
    } else {head=tail=NULL;}
    delete p;
    size--;
    return vRet;
}

template <class T>
T DList<T>::remove(T pos){
    int n=0;
    T vRet;
    DLink<T> *p=head;
    if(pos==0){return remove_first();}
    while(n!=pos){
        p=p->next;
        n++;
    }
    pos=p->value;
    p->previous->next=p->next;
    if(p!=tail){p->next->previous=p->previous;}
    else{tail=p->previous;}
    size--;
    delete p;
    return vRet;
}

template <class T>
std::string DList<T>::toStringForward() const{
    std::stringstream aux;
    DLink<T> *p=head;
    aux<<"[";
    while(p!=NULL){
        aux<<p->value;
        if(p->next!=NULL){aux<<", ";}
        p=p->next;
    }
    aux<<"]";
    return aux.str();
}

template <class T>
std::string DList<T>::toStringBackward() const{
    std::stringstream aux;
    DLink<T> *p=tail;
    aux<<"[";
    while(p!=NULL){
        aux<<p->value;
        if(p->previous!=NULL){aux<<", ";}
        p=p->previous;
    }
    aux<<"]";
    return aux.str();
}

#endif