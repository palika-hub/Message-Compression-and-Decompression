#include <bits/stdc++.h>
using namespace std;
/*
huffman_tree:
Creating a class for the implementation of a binary tree
Public members:
left node - left
right node - right
integer - freq
character - letter

Constructor:
huffman_tree:
Input: frequency and the corresponding character
*/
class huffman_tree
{
public:
    huffman_tree *left;  // left node of the tree
    huffman_tree *right; // right node of the tree
    int freq;
    char letter;
    huffman_tree(int key, char c) // defining a constructor
    {
        freq = key;  // initialising freq, with actual frequency of the letter
        letter = c;  // initialising letter, with the character value
        left = NULL; // initialising the left and right nodes with null
        right = NULL;
    }
};
// Building a priority queue
struct PriorityQueue
{
private:
    vector<huffman_tree *> A; // vector contains the respective nodes of the tree

    void heapify_down(int i)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < A.size() && A[left]->freq < A[i]->freq)
        {
            smallest = left;
        }

        if (right < A.size() && A[right]->freq < A[smallest]->freq)
        {
            smallest = right;
        }

        if (smallest != i)
        {
            swap(A[i], A[smallest]);
            heapify_down(smallest);
        }
    }

    void heapify_up(int i)
    {
        int parent = (i - 1) / 2;
        if (i && A[parent]->freq > A[i]->freq)
        {
            swap(A[i], A[parent]);
            heapify_up(parent);
        }
    }

public:
    int size()
    {
        return A.size();
    }

    bool empty()
    {
        return A.size() == 0;
    }

    void push(huffman_tree *key)
    {
        A.push_back(key);
        int index = A.size() - 1;
        heapify_up(index);
    }

    void pop()
    {
        if (A.size() == 0)
        {
            return;
        }

        A[0] = A.back();
        A.pop_back();

        heapify_down(0);
    }

    huffman_tree *top()
    {
        if (A.size() != 0)
        {
            return A.at(0);
        }

        huffman_tree *node = new huffman_tree(0, '#');
        return node;
    }
};
// Comparing the frequency of a particular node with another to construct the heap accordingly
class comparenode
{
public:
    bool operator()(huffman_tree *nodea, huffman_tree *nodeb)
    {
        return nodea->freq > nodeb->freq;
    }
};

// global initialization of a map and root of a heap.
map<char, pair<int, string>> freq;
huffman_tree *root;

/*
messageDecode:
Input: root of the tree
Output: void type.
It reads through encoded data file and returns the original message
*/
void messageDecode(huffman_tree *root)
{
    ifstream file;
    string encodedString;
    file.open("encoded_data.txt");
    file >> encodedString;
    file.close();
    string ans = "";
    huffman_tree *node = root;
    for (char c : encodedString)
    {
        if (c == '0')
            node = node->left;
        else
            node = node->right;

        if (node->left == NULL and node->right == NULL)
        {
            ans += node->letter; // if you reach a leaf node, it implies that you found a character . We add the character to a string here.
            node = root;
        }
    }
    ofstream write;
    write.open("target_message.txt");
    write << ans; // Printing out the decoded message to another file.
    write << endl;
    write.close();
    return;
}

/*
findCodes:
Input: root of the heap, a vector and an integer to push the code of a particular character into the previous vector
Output: void type. Chnages are being made into the vector.
It also writes the character - frequency table to a file

*/
void findCodes(huffman_tree *root, vector<int> &arr, int top)
{
    if (root->left)
    {
        arr[top] = 0;
        findCodes(root->left, arr, top + 1);
    }
    if (root->right)
    {
        arr[top] = 1;
        findCodes(root->right, arr, top + 1);
    }

    if (root->left == NULL && root->right == NULL)
    {
        ofstream file;
        file.open("huffmanTable.txt", std::ios_base::app);
        file << root->letter << " " << root->freq << " ";
        string binary = "";
        for (int i = 0; i < top; i++)
        {
            binary += to_string(arr[i]);
            file << arr[i];
        }
        freq[root->letter].second = binary;
        file << endl;
        file.close();
    }
    return;
}

/*
buildTree:
Input:: Heap
Output: returnd the root of the constructed binary tree
*/
huffman_tree *buildTree(struct PriorityQueue pq)
{
    while (pq.size() != 1)
    {
        huffman_tree *store_left = pq.top();
        pq.pop();
        huffman_tree *store_right = pq.top();
        pq.pop();
        huffman_tree *node = new huffman_tree(store_left->freq + store_right->freq, '*'); // creating a node, which has frequency = least_greq + second_least_freq
        node->left = store_left;
        node->right = store_right;
        pq.push(node);
    }
    return pq.top();
}
/*
messageEncode:
Input: user message
Output: void type.
Writes the encoded data to a flie
*/
void messageEncode(string message)
{
    struct PriorityQueue pq;
    for (auto it : freq)
    {
        huffman_tree *node = new huffman_tree(it.second.first, it.first);
        pq.push(node);
    }
    ofstream file;
    file.open("huffmanTable.txt");
    file << pq.size();
    file << endl;
    file.close();
    root = buildTree(pq);

    vector<int> arr(pq.size());
    findCodes(root, arr, 0);
    file.open("encoded_data.txt");
    for (char c : message)
    {
        string codedString = "";
        codedString += freq[c].second;
        cout << codedString << endl;
        file << codedString;
    }
    file << endl;
    file.close();
    return;
}
/*
findfrequeny:
Input: user message
Output: void type.
Calculates the respective frequencies of different characters
*/
void findfrequeny(string message)
{
    transform(message.begin(), message.end(), message.begin(), ::tolower);
    for (char c : message)
    {
        freq[c].first++;
    }

    
}

int main()
{
    ifstream file;
    file.open("message.txt");
    std::string message;
    char c;
    while (file.get(c)) {
        message += c;
    }
    // string message;
    file >> message;
    file.close();
    cout<<message<<endl;
    findfrequeny(message);
    messageEncode(message);
    messageDecode(root);
    return 0;
}
