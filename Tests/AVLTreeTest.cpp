/*
 * testAVLTree.cpp
 *
 *  Created on: 19 ���� 2013
 *      Author: shirel
 */

#include "../Submission//avl_tree.h"
#include <vector>
#include <ostream>
#include <random>
#include <chrono>
#include <algorithm>


template<class T>
class PrintTree{
    void operator()(T data){
        std::cout << data << endl;
    }
};

void seperate(int count){
    std::cout << "test no. " << count << std::endl << std::endl;
}

int main(){
	AVLTree<int> tree;
   int count = 1;
	//Specific Cases

	/*correct output for the four next cases
	1 BF: 0 Height: 0
	2 BF: 0 Height: 1
	3 BF: 0 Height: 0 */

	//basic LL root change
	tree.insert(3);
	tree.insert(2);
	tree.insert(1);
	//tree.printTree();
    for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
        std::cout << *(*avl_it) << std::endl;
    }
	tree.empty();
    seperate(count);
    count++;

	//basic LR root change
	tree.insert(3);
	tree.insert(1);
	tree.insert(2);
	//tree.printTree();
    for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
        std::cout << *(*avl_it) << std::endl;
    }
	tree.empty();
    seperate(count);
    count++;

	//basic RR root change
	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	//tree.printTree();
    for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
        std::cout << *(*avl_it) << std::endl;
    }
	tree.empty();
    seperate(count);
    count++;

	//basic RL root change
	tree.insert(1);
	tree.insert(3);
	tree.insert(2);
	//tree.printTree();
    for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
        std::cout << *(*avl_it) << std::endl;
    }
	tree.empty();
    seperate(count);
    count++;

	//basic LR not root change
	/*correct output
	1 BF: 0 Height: 0
	2 BF: 0 Height: 1
	3 BF: 0 Height: 0
	4 BF: 1 Height: 2
	5 BF: 0 Height: 0
	6 BF: 1 Height: 3
	7 BF: 0 Height: 0
	8 BF: 1 Height: 1 */
	tree.insert(6);
	tree.insert(4);
	tree.insert(8);
	tree.insert(3);
	tree.insert(5);
	tree.insert(7);
	tree.insert(1);
	tree.insert(2);
	//tree.printTree();
    for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
        std::cout << *(*avl_it) << std::endl;
    }
	tree.empty();
    seperate(count);
    count++;

	//basic LL not root change
	/*correct output
	1 BF: 0 Height: 0
	2 BF: 0 Height: 1
	3 BF: 0 Height: 0
	4 BF: 1 Height: 2
	5 BF: 0 Height: 0
	6 BF: 1 Height: 3
	7 BF: 0 Height: 0
	8 BF: 1 Height: 1 */
	tree.insert(6);
	tree.insert(4);
	tree.insert(8);
	tree.insert(3);
	tree.insert(5);
	tree.insert(7);
	tree.insert(2);
	tree.insert(1);
	//tree.printTree();
    for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
        std::cout << *(*avl_it) << std::endl;
    }
	tree.empty();
    seperate(count);
    count++;

	//basic RR not root change
	/*correct output
	 * 1 BF: 0 Height: 0
	2 BF: 0 Height: 1
	3 BF: 0 Height: 0
	5 BF: 1 Height: 2
	7 BF: 0 Height: 0*/
	tree.insert(5);
	tree.insert(7);
	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	//tree.printTree();
    for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
        std::cout << *(*avl_it) << std::endl;
    }
	tree.empty();
    seperate(count);
    count++;

	//basic RL not root change
	/*correct output
	 * 1 BF: 0 Height: 0
	2 BF: 0 Height: 1
	3 BF: 0 Height: 0
	5 BF: 1 Height: 2
	7 BF: 0 Height: 0*/
	tree.insert(5);
	tree.insert(7);
	tree.insert(1);
	tree.insert(3);
	tree.insert(2);
	//tree.printTree();
    for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
        std::cout << *(*avl_it) << std::endl;
    }
	tree.empty();
    seperate(count);
    count++;

	//root deletion no roll successor is a neighbour
	/*correct output
	2 BF: 0 Height: 0
	3 BF: 1 Height: 1
	5 BF: 1 Height: 2
	6 BF: 0 Height: 0*/
	tree.insert(4);
	tree.insert(5);
	tree.insert(3);
	tree.insert(2);
	tree.insert(6);
	tree.remove(4);
	//tree.printTree();
    for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
        std::cout << *(*avl_it) << std::endl;
    }
	tree.empty();
    seperate(count);
    count++;

	//root deletion no roll successor is not a neighbour
	/*correct output
	2 BF: 0 Height: 0
	3 BF: 1 Height: 1
	5 BF: 0 Height: 2
	6 BF: 0 Height: 0
	7 BF: 0 Height: 1
	8 BF: 0 Height: 0 */
	tree.insert(4);
	tree.insert(3);
	tree.insert(7);
	tree.insert(2);
	tree.insert(5);
	tree.insert(8);
	tree.insert(6);
	tree.remove(4);
	//tree.printTree();
    for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
        std::cout << *(*avl_it) << std::endl;
    }
	tree.empty();
    seperate(count);
    count++;

	//node deletion no roll successor is a neighbour case7
	/*correct output
	1 BF: 0 Height: 0
	2 BF: 1 Height: 1
	4 BF: 1 Height: 2
	5 BF: 0 Height: 0
	7 BF: 1 Height: 3
	8 BF: -1 Height: 1
	9 BF: 0 Height: 0*/
	tree.insert(7);
	tree.insert(3);
	tree.insert(8);
	tree.insert(2);
	tree.insert(4);
	tree.insert(9);
	tree.insert(5);
	tree.insert(1);
	tree.remove(3);
	//tree.printTree();
    for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
        std::cout << *(*avl_it) << std::endl;
    }
	tree.empty();
    seperate(count);
    count++;

	//node deletion no roll successor is not a neighbour case8
	/*correct output
	1 BF: 0 Height: 0
	2 BF: 1 Height: 1
	5 BF: 0 Height: 2
	6 BF: 0 Height: 0
	7 BF: 0 Height: 1
	8 BF: 0 Height: 0
	9 BF: 0 Height: 3
	10 BF: 0 Height: 0
	12 BF: -1 Height: 2
	13 BF: -1 Height: 1
	14 BF: 0 Height: 0*/
	tree.insert(9);
	tree.insert(3);
	tree.insert(12);
	tree.insert(2);
	tree.insert(7);
	tree.insert(10);
	tree.insert(13);
	tree.insert(1);
	tree.insert(5);
	tree.insert(8);
	tree.insert(14);
	tree.insert(6);
	tree.remove(3);
	//tree.printTree();
    for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
        std::cout << *(*avl_it) << std::endl;
    }
	tree.empty();
    seperate(count);
    count++;

	//node deletion causing LR case9
	/*correct output
	1 BF: 0 Height: 0
	2 BF: 0 Height: 1
	3 BF: 0 Height: 0
	4 BF: 0 Height: 2
	7 BF: -1 Height: 1
	8 BF: 0 Height: 0*/
	tree.insert(7);
	tree.insert(2);
	tree.insert(8);
	tree.insert(1);
	tree.insert(4);
	tree.insert(9);
	tree.insert(3);
	tree.remove(9);
	//tree.printTree();
    for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
        std::cout << *(*avl_it) << std::endl;
    }
	tree.empty();
    seperate(count);
    count++;

	//node deletion causing LL case10
	/*correct output
	1 BF: 0 Height: 0
	2 BF: 1 Height: 1
	3 BF: 0 Height: 2
	4 BF: 0 Height: 0
	7 BF: 0 Height: 1
	8 BF: 0 Height: 0*/
	tree.insert(7);
	tree.insert(3);
	tree.insert(8);
	tree.insert(2);
	tree.insert(4);
	tree.insert(9);
	tree.insert(1);
    for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
        std::cout << *(*avl_it) << std::endl;
    }
	tree.remove(9);
	//tree.printTree();
   for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
        std::cout << *(*avl_it) << std::endl;
    }
	tree.empty();
    seperate(count);
    count++;

	//node deletion causing RR case11
	/*correct output
	2 BF: 0 Height: 0
	3 BF: 0 Height: 1
	7 BF: 0 Height: 0
	8 BF: 0 Height: 2
	9 BF: -1 Height: 1
	10 BF: 0 Height: 0*/
	tree.insert(3);
	tree.insert(2);
	tree.insert(8);
	tree.insert(7);
	tree.insert(1);
	tree.insert(9);
	tree.insert(10);
	tree.remove(1);
	//tree.printTree();
    for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
        std::cout << *(*avl_it) << std::endl;
    }
	tree.empty();
    seperate(count);
    count++;

	//node deletion causing RL case12
	/*correct output
	* 2 BF: 0 Height: 0
	3 BF: 1 Height: 1
	7 BF: 0 Height: 2
	10 BF: 0 Height: 0
	13 BF: 0 Height: 1
	14 BF: 0 Height: 0*/
	tree.insert(3);
	tree.insert(2);
	tree.insert(13);
	tree.insert(7);
	tree.insert(1);
	tree.insert(14);
	tree.insert(10);
	tree.remove(1);
	//tree.printTree();
    //for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
     //   std::cout << *(*avl_it) << std::endl;
    //}
	tree.empty();
    seperate(count);
    count++;

	//double rotations RL and RR case 13
	/*correct output
	3 BF: 0 Height: 0
	5 BF: 0 Height: 1
	7 BF: 0 Height: 0
	9 BF: 0 Height: 2
	11 BF: 0 Height: 0
	13 BF: 1 Height: 1
	15 BF: 0 Height: 3
	17 BF: 0 Height: 0
	19 BF: -1 Height: 2
	21 BF: -1 Height: 1
	23 BF: 0 Height: 0*/
	tree.insert(9);
	tree.insert(3);
	tree.insert(15);
	tree.insert(1);
	tree.insert(7);
	tree.insert(13);
	tree.insert(19);
	tree.insert(5);
	tree.insert(11);
	tree.insert(17);
	tree.insert(21);
	tree.insert(23);
	tree.remove(1);
	//tree.printTree();
    for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
        std::cout << *(*avl_it) << std::endl;
    }
	tree.empty();
    seperate(count);
    count++;

	//double rotations RR and RR case 14
	/*correct output
	3 BF: 0 Height: 0
	7 BF: 0 Height: 1
	8 BF: 0 Height: 0
	9 BF: 0 Height: 2
	11 BF: 0 Height: 0
	13 BF: 1 Height: 1
	15 BF: 0 Height: 3
	17 BF: 0 Height: 0
	19 BF: -1 Height: 2
	21 BF: -1 Height: 1
	23 BF: 0 Height: 0*/
	tree.insert(9);
	tree.insert(3);
	tree.insert(15);
	tree.insert(1);
	tree.insert(7);
	tree.insert(13);
	tree.insert(19);
	tree.insert(8);
	tree.insert(11);
	tree.insert(17);
	tree.insert(21);
	tree.insert(23);
	tree.remove(1);
	//tree.printTree();
    for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
        std::cout << *(*avl_it) << std::endl;
    }
	tree.empty();
    seperate(count);
    count++;

	//double rotations RL and LL case 15
	/*correct output
	6 BF: 0 Height: 0
	7 BF: 1 Height: 1
	8 BF: 1 Height: 2
	9 BF: 0 Height: 0
	10 BF: 0 Height: 3
	11 BF: -1 Height: 1
	12 BF: 0 Height: 0
	15 BF: 0 Height: 2
	17 BF: 0 Height: 0
	18 BF: 0 Height: 1
	20 BF: 0 Height: 0
	 */
	tree.insert(15);
	tree.insert(10);
	tree.insert(20);
	tree.insert(8);
	tree.insert(11);
	tree.insert(17);
	tree.insert(21);
	tree.insert(7);
	tree.insert(9);
	tree.insert(12);
	tree.insert(18);
	tree.insert(6);
	tree.remove(21);
	//tree.printTree();
    //for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
   //     std::cout << *(*avl_it) << std::endl;
    //}
	tree.empty();
    seperate(count);
    count++;

	//double rotations LR and LL case 16
	/*correct output
	6 BF: 0 Height: 0
	7 BF: 1 Height: 1
	8 BF: 1 Height: 2
	9 BF: 0 Height: 0
	10 BF: 0 Height: 3
	11 BF: -1 Height: 1
	12 BF: 0 Height: 0
	15 BF: 0 Height: 2
	20 BF: 0 Height: 0
	21 BF: 0 Height: 1
	22 BF: 0 Height: 0 */
	tree.insert(15);
	tree.insert(10);
	tree.insert(20);
	tree.insert(8);
	tree.insert(11);
	tree.insert(17);
	tree.insert(22);
	tree.insert(7);
	tree.insert(9);
	tree.insert(12);
	tree.insert(21);
	tree.insert(6);
	tree.remove(17);
	//tree.printTree();
    for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
        std::cout << *(*avl_it) << std::endl;
    }
	tree.empty();
    seperate(count);
    count++;

	//delete node cause LR
	/*correct output
	  2 BF: 0 Height: 0
	3 BF: -1 Height: 2
	4 BF: 0 Height: 0
	6 BF: 1 Height: 1*/

	tree.insert(5);
	tree.insert(3);
	tree.insert(6);
	tree.insert(2);
	tree.insert(4);
	tree.remove(5);
	//tree.printTree();
    for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
        std::cout << *(*avl_it) << std::endl;
    }
	tree.empty();
    seperate(count);
    count++;

	//delete node cause LR
	/*correct output
	 * 2 BF: 0 Height: 0
	3 BF: 0 Height: 1
	6 BF: 0 Height: 0*/
	tree.insert(5);
	tree.insert(3);
	tree.insert(6);
	tree.insert(2);
	tree.remove(5);
	//tree.printTree();
    for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
        std::cout << *(*avl_it) << std::endl;
    }
	tree.empty();
    seperate(count);
    count++;



	std::vector<int> vector;
	 for (int i=1; i<=10000; i++) vector.push_back(i);

	 //Randomly insert and removes nodes
	 for (int k = 0; k < 1; ++k) {
		 unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		 shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
		 for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
				tree.insert(*it);
		 }
         //tree.printTree();

		for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
             std::cout << *(*avl_it) << std::endl;
		 }

	//	int deleted = 1, i = 1;
		//shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
      //   for (std::vector<int>::iterator it = vector.begin() ; i<=50; ++it){
      //       tree.remove(*it);
     //        i++;
     //    }
        // for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it!= tree.end(); ++avl_it){
        //     std::cout << *(*avl_it) << std::endl;
        // }
        tree.remove(650);
		tree.remove(750);
		tree.remove(1900);
		tree.remove(2780);
         tree.remove(3450);
         tree.remove(5439);
         tree.remove(6780);
         tree.remove(7780);
         tree.remove(9999);
         for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it != tree.end(); ++avl_it){
             std::cout << *(*avl_it) << std::endl;
         }
         //for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
		//		tree.remove(*it);
				//std::cout << "delete no." << deleted << ":" << std::endl;
				//tree.printTree();
                //std::cout << std::endl << std::endl << std::endl;
               // deleted++;
		// }
		 tree.empty();
      /*   for(AVLTree<int>::AvlIterator avl_it=tree.begin(); avl_it!= avl_it.end(); ++avl_it){
             std::cout << *avl_it << std::endl;
         }*/
		 //std::cout << '\n';
	}

	return 0;
}

