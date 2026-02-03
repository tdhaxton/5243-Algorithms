# P01 - BST Delete

## Implementing Delete in a Binary Search Tree (BST)

#### For this assignment, I implemented a delete function in a binary search tree. The function traverses the tree with the value it receives as an argument until the value of the current node is neither greater than or less than the value that is being searched for or the traversal reaches a null pointer. 

#### I handled cases where there was no left child, no right child, duplicate children, and both children. In the cases where there was no child, the node was simply deleted. In the cases where there was one child, the child took the place of the deleted node in the BST. When there were two children, I chose to get the successor child to replace the deleted node. This involved finding the leftmost descendent of the right child of the node to be deleted. I did this by creating a method to find and return the successor, and then setting the node for deletion to the successor's value and deleting the successor node.

#### For testing, I deleted nodes from a balanced tree and imbalanced trees, both left- and right-heavy, and a tree with duplicate values. I deleted nodes with no children, one child (both left and right), and two children. I also tested to ensure that the correct successor was chosen to replace a deleted node in a balanced tree.