#include <iostream>
#include "btree.hpp"

int main(int argc, char *argv[])
{
    BTree<int> btree;

    btree.addData(3);
    btree.addData(4);


    btree.addData(1);

    BTree<int> b2(btree);

    btree.deleteAll();
    if(btree.isEmpty()) std::cout << "Se elimino correctamente" <<endl;
    else std::cout << "NOpe" << endl;


    getchar();
}
