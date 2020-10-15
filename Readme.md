# Alex Nakamura Díaz Francés NUA:314283

# Final project, Data Structures and Algorithms: Binary Trees

## Content
The file BinaryTrees.hpp has all the declarations of the templates used for the classes. The file BinaryTrees.cpp has all the definitions for those classes. I decided to keep the project in two separate files so that it would be more comprehensible but, for that reason, we have to compile it in a certain way. The file main.cpp has a demonstration program for the classes. 

There is one class for Nodes and three classes for trees—BinaryTree, BinarySearchTree and BinaryRedBlackTree—. All the clases have the same type of node so that the inheritance between classes is simpler.
- The class BinaryTree has the basic tree structure, the constructor and destructor functions, and the methods for printing trees both in a terminal as well as in a LaTex document.
- The class BinarySearchTree has functions to search, insert and delete nodes.
- The class BinaryRedBlackTree modifies class BinarySearchTree's functions to work like a Red-Black Binary Tree. The implementation was based in Cormen's book _Introduction to Algorithms_.

## Compilation
A Make File is included to compile the demonstration program. It is important to compile the files BinaryTrees.cpp and BinaryTrees.hpp both in the same directory but linking only the file BinaryTrees.hpp. For example

	c++ -Wall -std=c++11 BinaryTrees.hpp main.cpp  -o DemoProgram

---
# Proyecto Final , Estructuras de datos y análisis de algoritmos.

### Contenido:
En el archivo BinaryTrees.hpp se encuentran las declaraciones de los templates para las clases. En el archivo BinaryTrees.cpp se encuentran las definiciones de los templates para las clases. Decidí separarlo en dos para que fuera más comprensible pero, por lo mismo, hay que tener cuidado con la compilación. El archivo main.cpp es un programa que prueba las clases.

Se incluyen una clase de Nodos y tres clases de árboles —Node, BinaryTree, BinarySearchTree y BinaryRedBlackTree—. Para que fuera más fácil la herencia, todas están implementadas con nodos que tienen colores y con un nodo nulo centinela. 
- La clase BinaryTree tiene implementadas la estructura de los árboles y las funciones constructoras, destructoras y de impresión tanto en pantalla como en un pdf usando LaTex. 
- La clase BinarySearchTree tiene implementadas funciones de inserción, búsqueda y eliminación de las cuales todas fueron adaptadas de lo que hice para la práctica 10. 
- Las clase BinaryRedBlackTree fue implementada basándome principalmente en el libro de Cormen.


### Para la compilación del proyecto:
Se incluye un Makefile que compila un programa para probar el proyecto. En caso de que no se use el Makefile, es importante compilar con los archivos BinaryTrees.cpp y BinaryTrees.hpp ambos en la misma carpeta pero ligando únicamente el archivo BinaryTrees.hpp. Por ejemplo:

	c++ -Wall -std=c++11 BinaryTrees.hpp main.cpp  -o DemoProgram