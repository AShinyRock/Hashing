// hashing2Arrays.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Hannah Beckley
//Holds pointers to the objects in the array and objects link to collisions

#include <iostream>

using namespace std;

//determines the length of the hash table
const int tIndex = 5;

/* Hash Table
 - all values are set to "" and nullptr by defualt
 - deleteHT(<TABLENAME>) should be called when the user is done with the hash table
 - "this" refers to the class object used to call the function
*/
class hashNode {
public:
    string word;
    hashNode* next;

    hashNode() {
        this->word = "";
        this->next = nullptr;
    }
    hashNode(string w) {
        this->word = w;
        this->next = nullptr;
    }
    hashNode(string w, hashNode* n) {
        this->word = w;
        this->next = n;
    }
    ~hashNode() {
        //cout << "Destructor called." << endl;     //testing
        delete this->next;
    }
    void deleteHT(hashNode* table[]) {
        for (int i = 0; i <= tIndex - 1; i++) {
            if (table[i] != NULL) {
                table[i]->~hashNode();
            }
        }
    }

    hashNode* _findIndex(hashNode* head, hashNode* newNode) {
        //More efficiant solution
        //(new element is placed first)
        hashNode* temp = new hashNode(head->word, head->next);
        head = newNode;
        head->next = temp;
        return head;

        /* //Solution with recursion (below)
           //(new element is placed last) 
        if (head->next == nullptr) {
            head->next = newNode;
            //hashNode* temp = new hashNode(head->word);
            //head = newNode;
            //head->next = temp;
        }
        else {
            findIndex(head->next, newNode);
        }*/
    }

    void hashFunction(string w, hashNode* hashTable[tIndex]) {
        //hashing equation
        int x = w.at(w.length() - 1);
        int index = x % tIndex;     // tIndex = 5

        hashNode* newNode = new hashNode(w);

        if (hashTable[index] == NULL) {
            hashTable[index] = newNode;
        }
        else {
            hashTable[index] = _findIndex(hashTable[index], newNode);
        }
    }

};

int main()
{
    //std::cout << "Hello World!\n";  //testing

    hashNode* hashTable[tIndex] = {};
    string array[] = { "Hi", "Hello", "Goodday", "Konichiwa", "Nihow", "Ohiyo", "Bonjour" };

    int size = sizeof(array) / sizeof(string);

    //Creating a hash table
    for (int i = 0; i <= size - 1; i++) {
        hashTable[tIndex]->hashFunction(array[i], hashTable);
    }

    //Call to destroy the hash table
    hashTable[tIndex]->deleteHT(hashTable);

    return 0;

}

