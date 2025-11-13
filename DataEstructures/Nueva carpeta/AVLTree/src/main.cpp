#include <iostream>
#include "avltree.hpp"

int main(int argc, char *argv[])
{
    AVLTree<int> btree;

    btree.addData(3);
    btree.addData(4);


    btree.addData(1);
    btree.addData(5);
    btree.addData(7);
    btree.addData(20);

    btree.deleteData(3);

    AVLTree<int> b2(btree);

    btree.deleteAll();
    if(btree.isEmpty()) std::cout << "Se elimino correctamente" <<endl;
    else std::cout << "NOpe" << endl;


    getchar();
}
