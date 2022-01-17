#include "DSAvlTree.h"
#include "DSAvl_Map.h"
#include "catch.hpp"

TEST_CASE("Tests for methods and operators for DSAvlTree", "[DSAvlTree]") {
    DSAvlTree<int> tree;

    SECTION("AVLTree insert mention") {
        tree.insert(10);
        tree.printTree();
        tree.insert(5);
        tree.insert(15);
        tree.printTree();
        tree.clear();

        tree.insert(10);
        tree.insert(11);
        tree.insert(12);
        tree.printTree();

        tree.insert(10);
        tree.insert(9);
        tree.insert(8);
        tree.printTree();

        DSAvlTree<int> newTree(tree);
        newTree.insert(44);
        newTree.insert(403329024);
        newTree.printTree();
        tree.printTree();

        std::cout << newTree.contains(44) << std::endl;
        std::cout << newTree.contains(3) << std::endl;
    }

}

TEST_CASE("Tests for methods and operators for DSAvl_Map", "[DSAvl_Map]") {
    DSAvl_Map<int, std::vector<std::string>> test01;
    SECTION(":3") {
        test01.insert(5).emplace_back("lemonade");
        test01.insert(10).emplace_back("strawberry");
        test01.getValue(5).emplace_back("kachow");
        test01.getValue(5).emplace_back("shapow");

        for(int i = 0; i < test01.getValue(5).size(); i++)
            std::cout << test01.getValue(5).operator[](i) << ", ";
        std::cout << std::endl;

    }
}