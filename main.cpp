#include"BinaryTrees.hpp"

#include<iostream>
#include<string>
#include<random>
#include<ctime>

using namespace std;

//Para generar números aleatorios.
class Random{
    private:
        default_random_engine engine;
    public:
        Random(long unsigned S){engine.seed(S);randomint(1,2);}
        ~Random(){}
        int randomint(int a, int b){
            uniform_int_distribution<int> uniform_int(a,b);
            return uniform_int(engine);
        }
};


int main(void){

   cout<<endl<<"Programa para probar los arboles binarios"<<endl<<endl;
   //Pruebas con los árboles
   BinarySearchTree<int> BST;
   BinaryRedBlackTree<int> BRBT;

   int n = 20;
   int random_index;
   //Llenar los árboles de números aleatorios no repetidos.
   Random r((long unsigned int)time(0));
   vector<int> v;
   for(int i=0; i<n; i++){
       v.push_back(i+1);
   }
   cout<<"Insertando en los arboles:"<<endl;
   for(int i=1; i<=n; i++){
       random_index = r.randomint(0,n-i);
       BST.Insert(v[random_index]);
       BRBT.Insert(v[random_index]);
       cout<<v[random_index]<<" ";
       swap(v[random_index], v[n-i]);
    }cout<<endl;

    //Generar imágenes para poder visualizar
    cout<<"InOrder TreWalks de los dos arboles:"<<endl;
    BRBT.InOrderTreeWalk();
    BST.InOrderTreeWalk();
    
    
    cout<<"Generando archivos de LaTex..."<<endl;
    cout<<"\tBinarySearchTree.tex"<<endl;
    cout<<"\tBinaryRedBlackTree.tex"<<endl;
        BST.CreateTexTree("BinarySearchTree");
        BRBT.CreateTexTree("BinaryRedBlackTree");


    //Prueba de las funciones de búsqueda
    cout<<"Prueba de las funciones de busqueda:"<<endl;
    cout<<endl<<"BRBT.BoolSearch("<<n+5<<") = "<<(BRBT.BoolSearch(n+5) ? "True":"False")<<endl;
    cout<<"BRBT.BoolSearch("<<n/2<<") = "<<(BRBT.BoolSearch(n/2) ? "True":"False")<<endl;
    cout<<"BRBT.Search("<<n/2<<") = "<<BRBT.Search(n/2)<<endl<<endl;

    //Prueba de la eliminación
    cout<<"Prueba de la funcion de eliminacion: (enter para continuar)"<<endl;
        getchar();
    cout<<"Eliminando de los arboles a los nodos:"<<endl;
    
    for(int i=1; i<=n/4; i++){
            random_index = r.randomint(0,n-i);
            BST.Delete(v[random_index]);
            BRBT.Delete(v[random_index]);
            cout<<v[random_index]<<" "<<endl;
            swap(v[random_index], v[n-i]);
        }cout<<endl;
    

    
    //Visualizar los cambios
    cout<<"InOrder TreWalks de los dos arboles:"<<endl;
        BRBT.InOrderTreeWalk();
        BST.InOrderTreeWalk();
    
    cout<<"Generando archivos de LaTex..."<<endl;
    cout<<"\tBinarySearchTree.tex"<<endl;
    cout<<"\tBinaryRedBlackTree.tex"<<endl;
        BST.CreateTexTree("BinarySearchTree");
        BRBT.CreateTexTree("BinaryRedBlackTree");
        
    return 0;
}