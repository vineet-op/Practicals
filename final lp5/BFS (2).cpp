#include <iostream>
#include <queue>
#include <omp.h>

using namespace std;

class Node {
public:
    Node *left, *right;
    int data;

    Node(int data) {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class Breadthfs {
public:
    Node *insert(Node *, int);
    void bfs(Node *);
};

// Inserts a Node in the tree
Node *insert(Node *root, int data) {
    if (!root) {
        // Create a new Node with the given data if the tree is empty
        root = new Node(data);
        return root;
    }

    // Use a queue for level-order insertion
    queue<Node *> q;
    q.push(root);

    while (!q.empty()) {
        Node *temp = q.front();
        q.pop();

        // Insert the new Node as the left child if left child is empty
        if (temp->left == nullptr) {
            temp->left = new Node(data);
            return root;
        } else {
            // Otherwise, enqueue the left child for further processing
            q.push(temp->left);
        }

        // Insert the new Node as the right child if right child is empty
        if (temp->right == nullptr) {
            temp->right = new Node(data);
            return root;
        } else {
            // Otherwise, enqueue the right child for further processing
            q.push(temp->right);
        }
    }

    return nullptr;
}

// Perform breadth-first search (BFS) traversal of the tree
void bfs(Node *head) {
    queue<Node *> q;
    q.push(head);

    // Process each level of the tree
    while (!q.empty()) {
        int qSize = q.size();

        // Process each node at the current level in parallel (OpenMP)
        #pragma omp parallel for
        for (int i = 0; i < qSize; i++) {
            Node *currNode = nullptr;

            // Critical section to access and print the current node
            #pragma omp critical
            {
                currNode = q.front();
                q.pop();
                // Print the data of the current node
                cout << "\t" << currNode->data;
            }

            // Enqueue left child (if exists) of the current node
            if (currNode->left)
                q.push(currNode->left);
            
            // Enqueue right child (if exists) of the current node
            if (currNode->right)
                q.push(currNode->right);
        }
    }
}

int main() {
    Node *root = nullptr;
    int data;
    char ans;

    // Insert nodes into the tree based on user input
    do {
        cout << "Enter node's data: ";
        cin >> data;
        root = insert(root, data);

        cout << "Do you want to insert one more Node? ('y' | 'n'): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    // Perform breadth-first search (BFS) traversal starting from the root
    cout << "Breadth-First Search (BFS) Traversal:" << endl;
    bfs(root);

    return 0;
}
