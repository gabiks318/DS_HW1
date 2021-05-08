//
// Created by Gabriel on 06/05/2021.
//

#include "test_utilities.h"
#include "../avl_tree.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

#define NUMBER_TESTS 3

ostream& printInt(int num, ostream& os){
    return os << num << endl;
}
template<class T>
class PrintFile{
public:
    PrintFile(const string& file_name){
        clearFile(file_name);
        file = ofstream (file_name);
    }
    ~PrintFile(){
        file.close();
    }
    ofstream file;
    void operator()(T& data){
        file << data << " ";
    }
};

template<class T>
class PrintTree{
    void operator()(T data){
        std::cout << data << endl;
    }
};

bool testAVLTreeCreateDestroy(){
    bool result = true;
    AVLTree<int> tree = AVLTree<int>();
    ASSERT_TEST(tree.getHeight() == 0, returnLabel);
    returnLabel:
    return result;
}

bool testAVLIntInsert1(){
    bool result = true;
    AVLTree<int> tree= AVLTree<int>();
    int num = 5;
    tree.insert(num);
    string expected = "../tests/outputs/avl_int_print1.txt";
    string tested = "../tests/outputs/output.txt";
    PrintFile<int> printFile(tested);
//    clearFile(tested);
//    ofstream output_file(tested);

    tree.inorder(printFile);
    return result;
}

bool testAVLReverseInorder(){
    bool result = true;
    AVLTree<int> tree= AVLTree<int>();
    tree.insert(9);
    tree.insert(4);
    tree.insert(22);
    tree.insert(2);
    tree.insert(6);
    tree.insert(14);
    tree.insert(50);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(8);
    tree.insert(12);
    tree.insert(16);
    tree.insert(44);
    tree.insert(53);
    tree.insert(11);
    tree.insert(13);
    tree.insert(25);
    tree.insert(56);

    tree.reverseInorder();

returnLabel:
    return result;
}

/* bool test(){
    bool result = true;

returnLabel:
    return result;
} */

bool (*tests[]) (void) = {
        testAVLTreeCreateDestroy,
        testAVLIntInsert1,
        testAVLReverseInorder
};

const char* testNames[] = {
        "testAVLTreeCreateDestroy",
        "testAVLIntInsert1",
        "testAVLReverseInorder"
};

int main(int argc, char *argv[]) {
    if (argc == 1) {
        for (int test_idx = 0; test_idx < NUMBER_TESTS; test_idx++) {
            RUN_TEST(tests[test_idx], testNames[test_idx]);
        }
        return 0;
    }
    if (argc != 2) {
        fprintf(stdout, "Usage: priority_queue_tests <test index>\n");
        return 0;
    }

    int test_idx = strtol(argv[1], NULL, 10);
    if (test_idx < 1 || test_idx > NUMBER_TESTS) {
        fprintf(stderr, "Invalid test index %d\n", test_idx);
        return 0;
    }

    RUN_TEST(tests[test_idx - 1], testNames[test_idx - 1]);
    return 0;
}