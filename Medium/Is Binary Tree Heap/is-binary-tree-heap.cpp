//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// Tree Node
struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Function to Build Tree
Node *buildTree(string str) {
    // Corner Case
    if (str.length() == 0 || str[0] == 'N') return NULL;

    // Creating vector of strings from input
    // string after spliting by space
    vector<string> ip;

    istringstream iss(str);
    for (string str; iss >> str;) ip.push_back(str);

    // Create the root of the tree
    Node *root = new Node(stoi(ip[0]));

    // Push the root to the queue
    queue<Node *> queue;
    queue.push(root);

    // Starting from the second element
    int i = 1;
    while (!queue.empty() && i < ip.size()) {

        // Get and remove the front of the queue
        Node *currNode = queue.front();
        queue.pop();

        // Get the current Node's value from the string
        string currVal = ip[i];

        // If the left child is not null
        if (currVal != "N") {

            // Create the left child for the current Node
            currNode->left = new Node(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->left);
        }

        // For the right child
        i++;
        if (i >= ip.size()) break;
        currVal = ip[i];

        // If the right child is not null
        if (currVal != "N") {

            // Create the right child for the current Node
            currNode->right = new Node(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->right);
        }
        i++;
    }

    return root;
}


// } Driver Code Ends
// User Function template for C++

// Structure of node
/*struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};*/

class Solution {
  private:
    int countNode(struct Node* root){
        if(!root) return 0;
        
        int leftCount = countNode(root->left);
        int rightCount = countNode(root->right);
        return 1 + leftCount + rightCount;
    }
    
    bool isCBT(struct Node* root, int index, int count){
        if(!root) return true;
        
        if(index >= count) return false;
        else{
            bool leftAns = isCBT(root->left, 2*index + 1, count);
            bool rightAns = isCBT(root->right, 2*index + 2, count);
            
            return leftAns && rightAns;
        }
    }
    
    bool isMaxOrder(struct Node* root){
        // leaf node is heap
        if(root->left == NULL && root->right == NULL) return true;
        
        if(root->right == NULL){
            return root->data > root->left->data;
        }
        else{
            bool leftAns = isMaxOrder(root->left);
            bool rightAns = isMaxOrder(root->right);
            
            return (leftAns && rightAns && root->data > root->left->data && root->data > root->right->data);
        }
    }
  public:
    bool isHeap(struct Node* tree) {
        int index = 0;
        int count = countNode(tree);
        
        if(isCBT(tree, index, count) && isMaxOrder(tree)){
            return true;
        }
        else return false;
    }

};

//{ Driver Code Starts.

int main() {
    int tc;
    scanf("%d ", &tc);
    while (tc--) {
        string treeString;
        getline(cin, treeString);
        Solution ob;
        Node *root = buildTree(treeString);
        if (ob.isHeap(root))
            cout << 1 << endl;
        else
            cout << 0 << endl;
    }

    return 0;
}
// } Driver Code Ends