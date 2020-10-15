#include "BinaryTrees.hpp"

#include<iostream>
#include<string>
#include<fstream>
#include<stack>
#include<sstream>


using namespace std;

//Nodo////////////////////////////
template<typename T>
Node<T>::Node(){
    this->right = nullptr;
    this->left = nullptr;
    this->parent = nullptr;
    this->colorisblack = true;
}

template<typename T>
Node<T>::Node(T value){
    this->item = value;
}

template<typename T>
Node<T>::~Node(){}


//Árbol Binario
template<typename T> BinaryTree<T>::BinaryTree(){
    this->treenil = new Node<T>;
        this->treenil->colorisblack = true;
        this->treenil->item = 666;

    this->root = this->treenil;
}

template<typename T>
void BinaryTree<T>::freememory(Node<T>* ptr){
    if(ptr!=this->treenil){
        freememory(ptr->left);
        freememory(ptr->right);
        delete ptr;
    }
}
template<typename T> BinaryTree<T>::~BinaryTree(){
        this->freememory(this->root);
        delete this->treenil;
}


template<typename T>
void BinaryTree<T>:: InOrderTreeWalk(){
    stack<Node<T>*> S;
    Node<T> *nodo = this->root;
    while (nodo!=this->treenil || S.empty() == false)
    {
        while (nodo != this->treenil)
        {
            S.push(nodo);
            nodo = nodo->left;
        }

        nodo = S.top();
        S.pop();

        cout<<nodo->item <<" ";
        nodo = nodo->right;
    }
    cout<<endl;
}

//Árbol binario de búsqueda //////////////////////
template<typename T>BinarySearchTree<T>::BinarySearchTree(){}
template<typename T>BinarySearchTree<T>::~BinarySearchTree(){
    
}

template<typename T>
void BinarySearchTree<T>::Insert(T value, Node<T>** ptr){
    //Reservar memoria para el nuevo nodo
    Node<T>* new_node_ptr = new Node<T>(value);
        new_node_ptr->right = this->treenil;
        new_node_ptr->left = this->treenil;
        new_node_ptr->colorisblack = true; //Para los árboles no rojo-negros
    
    Node<T>* i = this->root; //i sirve para iterar
    Node<T>* j = this->treenil; //j guarda el antecesor de i en cada ciclo
    while (i!=this->treenil)
    {
        //Guardar el ciclo anterior
        j = i;
        
        //Revisar que no se repita
        if(i->item == value){
            cout<<"No se pudo insetar el elemento"<<value<<"porque ya estaba en la estructura."<<endl;
            ptr = nullptr;
            return;
        }
        //Avanzar
        if(value < i->item){
            i = i->left;
        }else{
            i = i->right;
        }
    }
    if(j == this->treenil) 
    {
        //Si el árbol está vacío
        this->root = new_node_ptr;
        new_node_ptr->parent = this->treenil;
    }else if(value < j->item){
        j->left = new_node_ptr;
    }else{
        j->right = new_node_ptr;
    }
    new_node_ptr->parent = j;
    //Guardár el lugar en el que se guardó el nuevo elemento
    *ptr = new_node_ptr;
}

template<typename T>
void BinarySearchTree<T>::Insert(T value)
{
    Node<T>* ptr;
    this->Insert(value, &ptr);
}

template<typename T>
Node<T>* BinarySearchTree<T>::Search(T value){
    Node<T>* ptr = this->root;

    while(ptr!=this->treenil){
        if(value == ptr->item){
            break;
        }else if(value < ptr->item){
            ptr = ptr->left;
        }else{
            ptr = ptr->right;
        }
    }
    if(ptr==this->treenil){
        ptr = nullptr;
    }
    return ptr;
}

template<typename T>
bool BinarySearchTree<T>::BoolSearch(T value){
    if(this->Search(value) != this->treenil){
        return true;
    }else{
        return false;
    }

}

template<typename T>
void BinarySearchTree<T>::Delete(T value)
{
    //Encontrar el nodo a borrar
    Node<T>* ptr = this->Search(value);

    //Si no se encuentra en el árbol
    if(ptr==this->treenil){
        return;
    }
    

    if(ptr->left == this->treenil && ptr->right==this->treenil)//Si no tiene hijos
    {
        if(ptr!=this->root)//Si ptr no es la raíz
        {
            //Dejar como treenil al apuntador correcto del papá
            if(ptr->parent->right == ptr)
            {
                ptr->parent->right = this->treenil;
            }else{
                ptr->parent->left = this->treenil;
            }
        }else{
            this->root = this->treenil;
        }
        //Liberar la memoria del nodo
        delete ptr;
    }else if((ptr->left == this->treenil && ptr->right!=this->treenil)||(ptr->right == this->treenil && ptr->left!=this->treenil)) //Si ptr tiene solamente un hijo
    {
        //Identificar cuál hijo es
        Node<T>* child;
        if(ptr->left!=this->treenil){
            child = ptr->left;
        }else{
            child = ptr->right;
        }

        if(this->root != ptr) //Si ptr no es la raíz
        {
            //Hacer que el padre de ptr apunte al hijo de ptr y viceversa
            if(ptr->parent->left==ptr){
                ptr->parent->left = child;
            }else{
                ptr->parent->right = child;
            }
            child->parent = ptr->parent;
        }else //Si ptr es la raíz
        {
            this->root = child;
            child->parent = this->treenil;
        }

        delete ptr;
    }else //Si ptr tiene dos hijos
    {
        //Encontrar el sucesor
        Node<T>* sucesor = ptr->right;
        while(sucesor->left != this->treenil){
            sucesor = sucesor->left;
        }
        //Reemplazar el contenido de ptr con el de su sucesor
        ptr->item = sucesor->item;

        //Borrar el sucesor
        if(sucesor->right == this->treenil && sucesor->left == this->treenil)//Si el sucesor no tiene hijos
        {
            if(sucesor->parent->right == sucesor)//Si el sucesor es un hijo derecho
            {
                sucesor->parent->right = this->treenil;
            }else//Si el sucesor es un hijo izquierdo
            {
                sucesor->parent->left = this->treenil;
            }
        }else //Si el sucesor tiene únicamente un hijo derecho (no puede tener dos porque si tuviera un hijo izquierdo entonces no sería el sucesor)
        {
            if(sucesor->parent->right == sucesor)//Si el sucesor es un hijo derecho
            {
                sucesor->parent->right = sucesor->right;
            }else//Si el sucesor es un hijo izquierdo
            {
                sucesor->parent->left = sucesor->left;
            }
            sucesor->right->parent = sucesor->parent;
        }
        
        delete sucesor;
    }
}


// Árbol Binario Rojo-Negro///////////////////
template<typename T>
BinaryRedBlackTree<T>::BinaryRedBlackTree(){}
template<typename T>
BinaryRedBlackTree<T>::~BinaryRedBlackTree(){}

template<typename T>
void BinaryRedBlackTree<T>::leftrotate(Node<T>* nodo){
    //aux será el nodo que 'rotará' a la izquierda
    Node<T>* aux = nodo->right; 
    //Convertir el sub-árbol izquierdo de aux en el el sub-árbol derecho de nodo
    nodo->right = aux->left;
    if(aux->left != this->treenil){
        aux->left->parent = nodo;
    }
    //Unir el padre de nodo con aux
    aux->parent = nodo->parent;
    if(nodo->parent == this->treenil){
        this->root = aux;
    }else if(nodo == nodo->parent->left){
        nodo->parent->left = aux;
    }else{
        nodo->parent->right = aux;
    }
    //Ligar nodo con aux (en su sub-árbol izquierdo)
    aux->left = nodo;
    nodo->parent = aux;
}

template<typename T>
void BinaryRedBlackTree<T>::rightrotate(Node<T>* nodo){
    //aux será el nodo que 'rotará' a la derecha
    Node<T>* aux = nodo->left; 
    //Convertir el sub-árbol derecho de aux en el el sub-árbol izquierdo de nodo
    nodo->left = aux->right;
    if(aux->right != this->treenil){
        aux->right->parent = nodo;
    }
    //Unir el padre de nodo con aux
    aux->parent = nodo->parent;
    if(nodo->parent == this->treenil){
        this->root = aux;
    }else if(nodo == nodo->parent->right){
        nodo->parent->right = aux;
    }else{
        nodo->parent->left = aux;
    }
    //Ligar nodo con aux (en su sub-árbol derecho)
    aux->right = nodo;
    nodo->parent = aux;
}

template<typename T>
void BinaryRedBlackTree<T>::RBInsertFixup(Node<T>* z)
{
    //Z será el nodo en que se presente algún quiebre de las propiedades de árbol rojo-negro
    Node<T>* y; //y será un nodo auxiliar
    while(z->parent->colorisblack == false){
        if(z->parent == z->parent->parent->left) //Si el padre de z es un hijo izquierdo
        {
            y = z->parent->parent->right; //y = tío de z
            if(y->colorisblack == false) //Caso 1: Si el tío de z es de color rojo
            {
                //Cambiar colores:
                z->parent->colorisblack = true;
                y->colorisblack = true;
                z->parent->parent->colorisblack = false;
                //Mover z para el siguiente punto de incongruencia
                z = z->parent->parent;
            }else{
                if(z->parent->right == z) //Caso 2: El tío de z es negro y z es un hijo derecho
                {
                    z = z->parent;
                    this->leftrotate(z);
                }
                //Caso 3: El tío de z es negro y z es un hijo izquierdo
                z->parent->colorisblack = true;
                z->parent->parent->colorisblack = false;
                this->rightrotate(z->parent->parent);
            }
        }else //Si el padre de z es un hijo derecho
        {
            y = z->parent->parent->left; //y = tío de z
            if(y->colorisblack==false) //Caso 1: Si el tío de z es de color rojo
            {
                //Cambiar colores:
                z->parent->colorisblack = true;
                y->colorisblack = true;
                z->parent->parent->colorisblack = false;
                //Mover z para el siguiente punto de incongruencia
                z = z->parent->parent;
            }else{
                
                if(z->parent->left == z) //Caso 2: El tío de z es negro y z es un hijo izquierdo
                {
                    z = z->parent;
                    this->rightrotate(z);
                }
                //Caso 3: El tío de z es negro y z es un hijo derecho
                z->parent->colorisblack = true;
                z->parent->parent->colorisblack = false;
                this->leftrotate(z->parent->parent);
            }
        }
        
    }
    this->root->colorisblack = true;
}

template<typename T>
void BinaryRedBlackTree<T>::RBTransplant(Node<T>* u, Node<T>* v)
{
    if(u->parent == this->treenil)//Si u es la raíz
    {
        this->root = v;
    }else if( u == u->parent->left) //Si u es un hijo izquierdo
    {
        u->parent->left = v;
    }else //Si u es un hijo derecho
    {
        u->parent->right = v;
    }
    //Ajustar el padre de v
    v->parent = u->parent;
    
}

template<typename T>
void BinaryRedBlackTree<T>::RBDeleteFixup(Node<T>* x)
{
    Node<T>* w; //w apuntará al hermano de x
    while(x!=this->root && x->colorisblack == true)
    {
        if(x==x->parent->left) //Si x es un hijo izquierdo
        {
            w = x->parent->right;
            if(w->colorisblack==false)//Caso 1: Si w, el hermano de x, es rojo
            {
                w->colorisblack = true;
                x->parent->colorisblack = false;
                this->leftrotate(x->parent);
                w = x->parent->right;
            }
            else if(w->left->colorisblack == true && w->right->colorisblack == true)//Caso 2: w es negro y ambos de sus hijos son negros
            {
                w->colorisblack = false;
                x = x->parent;
            }else{
                if(w->right->colorisblack==true)//Caso 3: w es negro, el hijo izquierdo de w es rojo y el hijo derecho de w es negro
                {
                    w->left->colorisblack = true;
                    w->colorisblack = false;
                    this->rightrotate(w);
                    w = x->parent->right;
                }
                //Caso 4: w es negro y el hijo derecho de w es rojo
                w->colorisblack = x->parent->colorisblack;
                x->parent->colorisblack = true;
                w->right->colorisblack = true;
                this->leftrotate(x->parent);
                x = this->root;
            }
        }else //Si x es un hijo derecho
            {
            w = x->parent->left;
            if(w->colorisblack==false)//Caso 1: Si w, el hermano de x, es rojo
            {
                w->colorisblack = true;
                x->parent->colorisblack = false;
                this->rightrotate(x->parent);
                w = x->parent->left;
            }
            else if(w->right->colorisblack == true && w->left->colorisblack == true)//Caso 2: w es negro y ambos de sus hijos son negros
            {
                w->colorisblack = false;
                x = x->parent;
            }else{
                if(w->left->colorisblack==true)//Caso 3: w es negro, el hijo derecho de w es rojo y el hijo izquierdo de w es negro
                {
                    w->right->colorisblack = true;
                    w->colorisblack = false;
                    this->leftrotate(w);
                    w = x->parent->left;
                }
                //Caso 4: w es negro y el hijo izquierdo de w es rojo
                w->colorisblack = x->parent->colorisblack;
                x->parent->colorisblack = true;
                w->left->colorisblack = true;
                this->rightrotate(x->parent);
                x = this->root;
            }
        }
    }
    x->colorisblack = true;
}

template<typename T>
void BinaryRedBlackTree<T>::Insert(T value)
{
    //Primero insertarlo como si fuera un árbol binario de búsqueda
    Node<T>* new_node_ptr = nullptr;
    this->BinarySearchTree<T>::Insert(value, &new_node_ptr);
    if(new_node_ptr == nullptr){
        //si no se pudo insertar por haber estado repetido
        return;
    }
    //Colorearlo de rojo
        new_node_ptr->colorisblack = false;
    
    //Reparar las propiedades de un árbol rojo-negro (RB-Insert-Fixup)
    this->RBInsertFixup(new_node_ptr);
}

template<typename T>
Node<T>* BinaryRedBlackTree<T>::Search(T value)
{
    return this->BinarySearchTree<T>::Search(value);
}

template<typename T>
void BinaryRedBlackTree<T>::Delete(T value)
{
    Node<T> *x,*y,*z;
    //Encontrar el nodo a eliminar
    z  = this->Search(value); //z es el nodo que queremos eliminar
    if(z==this->treenil){
        return;
    }
    //y es el nodo que se sacará del árbol o se meterá al árbol para poder quitar a z
    //x será el que sustituirá el lugar de y
    bool y_original_color_is_black;//Guardará color original de y antes de cualquier cambio
    if(z->left == this->treenil) //Si z no tiene hijo izquierdo
    {
        y = z;
        y_original_color_is_black = y->colorisblack;

        x = z->right;
        this->RBTransplant(z, z->right);
    }else if(z->right == this->treenil)//Si z no tiene hijo derecho pero sí hijo izquierdo
    {
        y = z; 
        y_original_color_is_black = y->colorisblack;

        x = z->left;
        this->RBTransplant(z, z->left);
    }else //Si z tiene dos hijos.
    {
        //Fijar y como el sucesor de z
        y = z->right;
        while(y->left!=this->treenil){
            y = y->left;
        }
        y_original_color_is_black = y->colorisblack;
        x = y->right;
        if(y->parent == z)
        {
            x->parent = y;
        }else{
            this->RBTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        this->RBTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->colorisblack = z->colorisblack;
    }
    delete z;
    if(y_original_color_is_black == true){
        this->RBDeleteFixup(x);
    }

}



/////////////////////////////////////////////////////////
///////Para imprimir los árboles en LaTex////////////////
template<typename T>
void BinaryTree<T>::CreateTexTree(std::string name)
{
    string filename = name+".tex";
    int n; //Representará en número de corchetes de cierre a insertar.
    ofstream myfile;
    myfile.open(filename);

        myfile<<TexHeader();
        myfile<<"\\begin{document}\n";
        myfile<<tikzset();
        myfile<<"\\begin{forest}\n";
        myfile<<fortree();
        //////////////////////////////////////////////////////////
        //Llenado de nodos (en resumen es un pre-order tree-walk)
        stack<Node<T>*> S;
        Node<T> *nodo, *ptr;
        S.push(this->root);
        while(S.empty() == false){
            nodo = S.top();
            S.pop();
            myfile<<this->TexStringNode(nodo);
                //Para cerrar los corchetes (])
                if(nodo->left == this->treenil && nodo->right == this->treenil) //Si es un nodo hoja
                {
                    if(nodo==this->root){
                        //Si es el único nodo
                        n = 1;
                    }else if(nodo==nodo->parent->left && nodo->parent->right != this->treenil){
                        //Si es hijo izquierdo y tiene un hermano no nulo
                        n = 1;
                    }else{
                        //Hay que contar cuántos sub-árboles cierra este nodo
                        //Es el número de caminos derechos o forzados desde la última bifurcación en la que se tomó un camino izquierdo no forzado; ese camino izquierdo sí cuenta.
                        n = 1;
                        ptr = this->root;
                        while(ptr != nodo)
                        {
                            if(ptr->item < nodo->item)//Camino derecho
                            {
                                ptr = ptr->right;
                                n++;
                            }else //Camino izquierdo
                            {
                                if(ptr->right != this->treenil)//Si no fue forzado
                                {
                                    n = 1;
                                }else //Si fue forzado
                                {
                                    n++;
                                }
                                ptr = ptr->left;
                            }
                        }
                        
                    }
                    for(int i=0; i<n; i++)
                    {
                        myfile<<"]";
                    }myfile<<"\n";
                }
            
            if(nodo->right!=this->treenil){
                S.push(nodo->right);
            }
            if(nodo->left!=this->treenil){
                S.push(nodo->left);
            }
        }

        ///////////////////////////////////////////////////////////
        myfile<<"\\end{forest}\n";
        myfile<<"\\end{document}\n";

    myfile.close();
}

std::string TexHeader()
{
    string header = "";
    header = "\\documentclass[border=3mm]{standalone}\n\\usepackage{forest}\n";
    return header;
}

std::string tikzset(){
    string tikzset = "\\tikzset{   forest node/.style = {align=center, inner sep=0pt, text centered,    font=\\sffamily},  black_node/.style = {forest node, circle, white, font=\\sffamily\\bfseries, draw=black, fill=black,  text width=1.5cm},   red_node/.style = {forest node, circle, red, draw=red,    text width=1.5cm, very thick}, nil_node/.style = {forest node, rectangle, draw=black,     minimum width=0.5cm, minimum height=0.5em} }\n";
    return tikzset;
}

std::string fortree(){
    string fortree = "for tree = {circle, draw, minimum size=4ex, inner sep=2pt, grow = south } \n";
    return fortree;

}


template<typename T>
std::string BinaryTree<T>::TexStringNode(Node<T>* nodo){
    string texline = "";
    string str_value = "";
    stringstream ss;

    ss<<nodo->item;
    ss>>str_value;

    
    if(nodo==this->treenil){
        texline += "[ , nil_node";
    }else if(nodo->colorisblack == true){
        texline += "["+str_value+", black_node ";
    }else{
        texline += "["+str_value+", red_node ";
    }

    return texline;
}
