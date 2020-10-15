#ifndef BinaryTrees_hpp
#define BinaryTrees_hpp
    #include<string>
    
    //Pre-declarar BinaryTree<T>
    template<typename T>
    class BinaryTree;
    //Pre-declarar BinarySearchTree<T>
    template<typename T>
    class BinarySearchTree;
    //Pre-declarar BinaryBlackRedTree<T>
    template<typename T>
    class BinaryRedBlackTree;

    //Pre-declaraciones par imprimir
    std::string TexHeader();
    std::string tikzset();
    std::string fortree();


    //Nodo
    template<typename T>
    class Node
    {
        private:
            friend class BinaryTree<T>;
            friend class BinarySearchTree<T>;
            friend class BinaryRedBlackTree<T>;

        protected:
            Node<T>* right;
            Node<T>* left;
            Node<T>* parent;
            bool colorisblack;
            

        public:
            T item;

            Node();
            Node(T);
            ~Node();
    };

    //Árbol binario
    template<typename T>
    class BinaryTree{
        protected:
            Node<T>* root;
            Node<T>* treenil;
            void freememory(Node<T>*);
        
            //Funciones para imprimirlo en LaTex
            friend std::string TexHeader();
            friend std::string tikzset();
            friend std::string fortree();
            std::string TexStringNode(Node<T>*);

        public:
            BinaryTree();
            ~BinaryTree();
            
            void InOrderTreeWalk();
        
            //Funciones para imprimirlo en LaTex
            void CreateTexTree(std::string filename);

            //Funciones virtuales
            virtual void Insert(T) = 0;
            virtual void Delete(T) = 0;
            virtual Node<T>* Search(T) = 0;
    };

    //Árbol binario de búsqueda
    template<typename T>
    class BinarySearchTree : public BinaryTree<T>{
        protected:
            void Insert(T, Node<T>**);
        
        public:
            BinarySearchTree();
            ~BinarySearchTree();

            void Insert(T) override;
            Node<T>* Search(T) override;
            virtual bool BoolSearch(T);
            void Delete(T) override;
    };

    //Árbol binario rojo-negro
    template<typename T>
    class BinaryRedBlackTree : public BinarySearchTree<T>{
        private:
            //Para inserción y eliminación
            void leftrotate(Node<T>*);
            void rightrotate(Node<T>*);

            void RBInsertFixup(Node<T>*);

            void RBTransplant(Node<T>*, Node<T>*);
            void RBDeleteFixup(Node<T>*);


        public:
            BinaryRedBlackTree();
            ~BinaryRedBlackTree();

            void Insert(T) override;
            Node<T>* Search(T) override;
            void Delete(T) override;
    };


    #include "BinaryTrees.cpp"

#endif
