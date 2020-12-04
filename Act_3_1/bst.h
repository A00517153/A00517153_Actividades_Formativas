/*---------------
Nombre: Johann Palomino Galvan
Matricula: A00517153
Actividad: Act 3.1
---------------*/

#ifndef BST_H
#define BST_H

#include <iostream>
#include <sstream>
#include <string>

template <class T> class Node;
template <class T> class BST;

template <class T>
class Node{
	private:
		T value;
		Node<T> *left, *right;
		
	public:
		Node(T);
		Node(T, Node<T>*, Node<T>*);
		int height() const;
		void add(T);
		int whatlevelamI(T);
		bool find(T);
		bool ancestors(T,std::stringstream&) const;
		Node<T>* succesor();
		void remove(T);
		void removeChilds();
		void inorder(std::stringstream&) const;
		void preorder(std::stringstream&) const;
		void postorder(std::stringstream&) const;
		void levelorder(std::stringstream&) const;
		void printlevel(std::stringstream&, int) const;

		friend class BST<T>;
};

template <class T>
Node<T>::Node(T val): value(val), left(NULL), right(NULL){}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri):value(val), left(le), right(ri){}

template <class T>
int Node<T>::height() const{
	int lvl_left=0, lvl_right=0;

	if(left!=NULL){lvl_left=left->height()+1;}
	if(right!=NULL){lvl_right=right->height()+1;}
	if(lvl_left==0 && lvl_right==0){return 1;}

	return (lvl_right>lvl_left)?lvl_right:lvl_left;
}

template <class T>
void Node<T>::add(T val){
	if(val<value){
		if(left!=NULL){left->add(val);}
		else {left=new Node<T>(val);}
	} else {
		if(right!=NULL){right->add(val);}
		else {right=new Node<T>(val);}
	}
}

template <class T>
int Node<T>::whatlevelamI(T val){
	if(val==value){return 1;}
	else if(val<value && left!=0){return left->whatlevelamI(val)+1;}
	else if(val>value && right!=0){return right->whatlevelamI(val)+1;}
	return -9999;
}

template <class T>
bool Node<T>::find(T val){
	if(val==value){return true;}
	else if(val<value){return (left!=NULL && left->find(val));}
	else if(val>value){return (right!=NULL && right->find(val));}
}

template <class T>
bool Node<T>::ancestors(T val,std::stringstream &aux) const{
	if(val==value){return true;} 
	else if(val<value){
		if(aux.tellp()!=1){
			aux<<" ";
		}
		aux<<value;
		return (left!=NULL && left->ancestors(val,aux));
	} else if(val>value){
		if(aux.tellp()!=1){
			aux<<" ";
		}
		aux<<value;
		return (right!=NULL && right->ancestors(val,aux));
	}
}

template <class T>
Node<T>* Node<T>::succesor(){
	Node<T> *l=left, *r=right;
	
	if(left==NULL){
		if(right!=NULL){right=NULL;}
		return r;
	}

	if(left->right==NULL){
		left=left->left;
		l->left=NULL;
		return l;
	}

	Node<T> *parent, *child;
	parent=left;
	child=left->right;
	while(child->right!=NULL){
		parent=child;
		child=child->right;
	}
	parent->right=child->left;
	child->left=NULL;
	return child;
}

template <class T>
void Node<T>::remove(T val){
	Node<T> *succ, *old;

	if(val<value && left!=NULL){
		if(left->value==val){
			old=left;
			succ=left->succesor();
			if(succ!=NULL){
				succ->left=old->left;
				succ->remove=old->right;
			}
			left=succ;
			delete old;
		} else {left->remove(val);}
	} else if(val>value && right!=NULL){
		if(right->value==val){
			old=right;
			succ=right->succesor();
			if(succ!=NULL){
				succ->left=old->left;
				succ->right=old->right;
			}
			right=succ;
			delete old;
		} else {right->remove(val);}
	}
}

template <class T>
void Node<T>::removeChilds(){
	if(left!=NULL){
		left->removeChilds();
		delete left;
		left=NULL;
	}
	if(right!=NULL){
		right->removeChilds();
		delete right;
		right=NULL;
	}
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const{
	if(left!=NULL){left->inorder(aux);}
	if(aux.tellp()!=1){aux<<" ";}
	aux<<value;
	if(right!=NULL){right->inorder(aux);}
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const{
	aux<<value;
	if(left!=NULL){
		aux<<" ";
		left->preorder(aux);
	}
	if(right!=NULL){
		aux<<" ";
		right->preorder(aux);
	}
}

template <class T>
void Node<T>::postorder(std::stringstream &aux) const{
	if(left!=NULL){left->postorder(aux);}
	if(right!=NULL){right->postorder(aux);}
	if(aux.tellp()!=1){aux<<" ";}
	aux<<value;
}

template <class T>
void Node<T>::levelorder(std::stringstream &aux) const{
	int lvl=height();
	for(int i=0;i<lvl;i++){printlevel(aux,i);}
}

template <class T>
void Node<T>::printlevel(std::stringstream &aux, int lvl) const{
	if(lvl==0){
		if(aux.tellp()!=1){aux<<" ";}
		aux<<value;
	}
	if(left!=NULL){left->printlevel(aux,lvl-1);}
	if(right!=NULL){right->printlevel(aux,lvl-1);}
}

template <class T>
class BST{
	private:
		Node<T> *root;
	
	public:
		BST();
		~BST();
		std::string visit();
		int height() const;
		void add(T);
		std::string ancestors(T) const;
		int whatlevelamI(T) const;
		bool empty() const;
		bool find(T) const;
		void remove(T);
		void removeAll();
		std::string inorder() const;
		std::string preorder() const;
		std::string postorder() const;
		std::string levelorder() const;	
};

template <class T>
BST<T>::BST():root(NULL){}

template <class T>
BST<T>::~BST(){
	removeAll();
}

template <class T>
std::string BST<T>::visit(){
	std::stringstream aux;
	aux<<preorder()<<"\n";
	aux<<inorder()<<"\n";
	aux<<postorder()<<"\n";
	aux<<levelorder();
	return aux.str();
}

template <class T>
int BST<T>::height() const{
	return root->height();
}

template<class T>
void BST<T>::add(T val){
	if (root!=NULL) {
		if (!root->find(val)) {
			root->add(val);
		}
	} else {
		root=new Node<T>(val);
	}
}

template <class T>
std::string BST<T>::ancestors(T val) const{
	std::stringstream aux;
	aux << "[";
	if (!empty()) {
		if(!root->ancestors(val, aux)){return "[]";}
	}
	aux << "]";
	return aux.str();
}

template <class T>
int BST<T>::whatlevelamI(T val) const{
	if (root!=NULL) {
	 	int num=root->whatlevelamI(val);
		if(num<0) return -1;
		return num;
	} else { return -1;}
}

template <class T>
bool BST<T>::empty() const{
	return (root==NULL);
}

template <class T>
bool BST<T>::find(T val) const{
	if (root!=NULL) {return root->find(val);}
	else {return false;}
}

template <class T>
void BST<T>::remove(T val){
	if (root!=NULL) {
		if (val==root->value) {
			Node<T> *succ=root->succesor();
			if (succ!=NULL) {
				succ->left=root->left;
				succ->right=root->right;
			}
			delete root;
			root=succ;
		} else {root->remove(val);}
	}
}

template <class T>
void BST<T>::removeAll(){
	if (root!=NULL) {root->removeChilds();}
	delete root;
	root = 0;
}

template <class T>
std::string BST<T>::inorder() const{
	std::stringstream aux;
	aux << "[";
	if (!empty()) {root->inorder(aux);}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::preorder() const{
	std::stringstream aux;
	aux << "[";
	if (!empty()) {root->preorder(aux);}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::postorder() const{
	std::stringstream aux;
	aux << "[";
	if (!empty()) {root->postorder(aux);}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::levelorder() const {
	std::stringstream aux;
	aux << "[";
	if (!empty()) {root->levelorder(aux);}
	aux << "]";
	return aux.str();
}

#endif
