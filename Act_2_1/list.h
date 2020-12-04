/*---------------
Nombre: Johann Palomino Galvan
Matricula: A00517153
Actividad: Act 2.1 
---------------*/

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>
#include <sstream>

template <class T> class Link;
template <class T> class List;

template <class T>
class Link{
    private:
        Link(T);
        Link(T, Link<T>*);
        Link(const Link<T>&);
        ~Link();

        T value;
        Link<T> *next;

        friend class List<T>;
        friend class Link<T>;
};

template <class T>
Link<T>::Link(T val):value(val), next(NULL){}

template <class T>
Link<T>::Link(T val, Link* nxt):value(val), next(nxt){}

template <class T>
Link<T>::Link(const Link<T> &src):value(src.value), next(src.next){}

template <class T>
Link<T>::~Link(){
    next=NULL;
    
}

template <class T>
class List{
    public:
        List();
        List(const List<T>&);
        ~List();
        bool empty() const;
        void add_first(T);
        void add(T);
        int find(T);
        void update(int,T);
        T remove(T);
        std::string toString()const;
        
    private:
        Link<T> *head;
        int size;
};

template <class T>
List<T>::List():head(NULL),size(0){}

template <class T>
List<T>::List(const List<T> &src):head(src.head),size(src.size){}

template <class T>
List<T>::~List(){
    Link<T> *p=head,*del;
    while(p!=NULL){
        del=p;
        p=p->next;
        del->~Link();
    }
}

template <class T>
bool List<T>::empty() const {return (size==0);}

template <class T>
void List<T>::add_first(T val){
    Link<T> *newLink=new Link<T>(val);

    newLink->next=head;
    head=newLink;
    size++;
}

template <class T>
void List<T>::add(T val){
    Link<T> *newLink=new Link<T>(val), *p;

    if(empty()){
        add_first(val);
        return;
    }

    p=head;
    while(p->next !=NULL){
        p=p->next;
    }

    newLink->next=NULL;
    p->next=newLink;
    size++;
}

template <class T>
int List<T>::find(T val){
    int n=0;
    Link<T> *p=head;

    while(p!=NULL){
        if(p->value == val){return n;}
        p=p->next;
        n++;
    }
    return -1;
}

template <class T>
void List<T>::update(int pos, T val){
    int i=0;
    Link<T> *p=head;
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
T List<T>::remove(T val){
    int i=0;
    Link<T> *p=head,*del;
    T vRet;
    if(val==0){
        vRet=p->value;
        head=p->next;
        p->~Link();
        size--;
        return vRet;
    }
    while((p->next)!=NULL){
        if((i+1)==val){
            del=p->next;
            p->next=del->next;
            vRet=del->value;
            del->~Link();
            size--;
            return vRet;
        }
        p=p->next;
        i++;
    }
    return NULL;
}

template <class T>
std::string List<T>::toString()const{
    std::stringstream aux;
    Link<T> *p=head;

    aux<<"[";
    while(p!=NULL){
        aux<<p->value;
        if(p->next!=NULL){
            aux<<", ";
        }
        p=p->next;
    }
    aux<<"]";
    return aux.str();
}

#endif