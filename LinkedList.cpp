///
// Created by Jeremy Cruz on 9/12/18.
//

#include <cstdlib>
#include "stdio.h"
#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int totalNode=0;

class LinkedList {
private:
    typedef struct node { // creates the node structure
        string data;
        node *next;

    } *nodePtr;

    nodePtr head;
    nodePtr curr;
    nodePtr temp;


// Public functions below used to modify linked list objects

public:
    LinkedList();

    void insert(string data, int index);
    void insertEnd(string data);
    void search(string find);
    void deleteNode(int nodeNum);
    void printList();
    void edit(int index, string newString);

};

LinkedList::LinkedList(){ // Constructor for  LinkedList object which is actually a linked list
    head = NULL;
    curr = NULL;
    temp = NULL;
}

/*
 * insertEnd method attaches the string/line to a node to the end of the linked list
 * It creates a new node to be attached to the end of the linkedList
 * */
void LinkedList:: insertEnd(string data){

    nodePtr n = new node;
    n->data = data;
    n->next = NULL;
    if (head != NULL){
        curr = head;
        while (curr->next != NULL){
            curr = curr->next;
        }
        curr->next = n;
        totalNode++;
    }
    else{
        head = n;
        totalNode++;
    }

}

/*
 * insert function works to create a new node and
 * place the line within the node at the chosen
 * index
 */
void LinkedList:: insert(string data, int index){

    nodePtr n = new node;
    n->data = data;
    if(head==NULL){
        head = n;
        totalNode++;
        return;
    }
    if(index == 1){
        n->next=head;
        head = n;
        totalNode++;
        return;

    }

    int i=1;
    curr = head;

    while(i<index-1){

        curr=curr->next;
        if(curr==NULL){
            return;
        }

        i++;
    }
    nodePtr next1 =curr->next;
    curr->next=n;
    n->next=next1;
    totalNode++;
}

/*
 * deleteNode functions to delete the node at the given index/nodeNumber
 * Method frees the node from memory to avoid future fragmentation issues
 */
void LinkedList::deleteNode(int nodeNum){

    if(totalNode==0){
       cout <<  "This line does not exist" << endl;
        return;
    }
    nodePtr temp1 = head;
    if(nodeNum==1){
        head=temp1->next;
        free(temp1);
        return;
    }
    int i;
    for(i = 0; i<nodeNum-2;i++){
        temp1=temp1->next;
    }
    if(temp1==NULL){
    return;
    }
    nodePtr temp2 = temp1->next;
    if (temp2==NULL){
    return;
    }
    temp1->next=temp2->next;
    free(temp2);

}

/*
 * search Function works to look for a node by userInput
 * It looks through the string in each node in order to find a match
 * to the user input. If there is no string then the user will be prompted that the search
 * was unsuccessful
 */
void LinkedList::search(string check){
    int lineNum = 1;
    curr=head;
    bool found = false;

    while(curr!=NULL){

        if(curr->data.find(check)!=-1){

            cout << lineNum;
            cout << " "+ curr->data << endl;
            found = true;
            curr =curr->next;
            lineNum++;
    

        }
        else{
            curr=curr->next;
            lineNum++;

        }
    }
    if(found==false){
        cout << "not found" << endl;
        return;
    }
    return;
}

/*
 * Edit method works to replace the contents in the node of the given index
 * The contents will be replaced by editedString
 */
void LinkedList::edit(int index, string newString){

    nodePtr temp1 = head;
    if(index==1){
        temp1->data=newString;
        return;
    }
    int i;
    for(i = 0; i<index-1;i++){
        temp1=temp1->next;
    }
    if (temp1!=NULL){
        temp1->data = newString;
    }
    else{
    }

}

// This function prints contents of linked list from the beginning/head node
void LinkedList::printList(){

    if(totalNode==0){
        return;
    }
    
    curr = head;

    int lineNum =1;

    cout << lineNum;
    cout << " " + curr->data << endl;

    while(curr->next!=NULL){
        curr = curr->next;
        lineNum++;
        cout << lineNum;
        cout << " " + curr->data << endl;

    }
  
}

/*
 * This method works to acquire a substring between the quotes of the inputted string.
 *
*/
string extractSubstring(string lstring){

    int firstQuote = lstring.find("\"");
    int lastQuote = lstring.rfind("\"");

    int totChar = 0;
    int counter = firstQuote;

    while(counter+1<lastQuote){
        counter++;
        totChar++;
    }


    string exString = lstring.substr( firstQuote+1, totChar );

    return exString;

}


/*
 * This method is for the delete function.
 * It works to grab the index of the node that will be deleted
 * from the inputted string.
 */
int extractInt(string userString){

    string check = userString;

    int length = check.length();
    char char_array[length+1];

    strcpy(char_array, check.c_str());

    for(int i = 0;i<length; i++){
        if (isdigit(char_array[i])){
            int found = (char_array[i]-'0');
            return found;
        }
    }
}



int main() {

    LinkedList linkList; // Initializes Linked List object

    bool cont = true; // Boolean to keep the program running

    while(cont){

        //MENU STATEMENT

        //cout << "Options:\n1. insertEnd 'insert text' \n2. insert Line # 'insert text'\n3. delete Line # \n4. print \n5. search Line #\n6. quit (exits program)" << endl;

        string userInput = "";
        string data = "";
        int index = 0;

        getline(cin,userInput);

        if((userInput.find("insertEnd")!=(-1)) && (userInput.find("\"")>(userInput.find("insertEnd"))) && (userInput.find("\""))!=userInput.rfind("\"")){ // Insert line/ node at end of linked List
            string data = extractSubstring(userInput);
            if (data.length()<=80){
                linkList.insertEnd(data);
            }
        }
        else if(userInput.find("insert")!= -1 && (userInput.find("\"")>(userInput.find("insert"))) && (userInput.find("\""))!=userInput.rfind("\"")){ // insert a node at given index

            string data = extractSubstring(userInput);
            int index = extractInt(userInput);

            if (data.length()<=80){
                linkList.insert(data, index);
            }
            else{
                cout << "Line is too long" << endl;
            }

        }
        else if(userInput.find("search")!=-1 && (userInput.find("\"")>(userInput.find("search")))){ // search through each node

            string searchString = extractSubstring(userInput);
            linkList.search(searchString);

        }
        else if(userInput.find("print")!=-1){ // print the lines case

            linkList.printList();

        }
        else if(userInput.find("delete")!=-1){ // delete a line/node case

            int deleteIndex = extractInt(userInput);
            linkList.deleteNode(deleteIndex);

        }
        else if(userInput.find("edit")!=-1){ // Case where user edits the string

            string editString = extractSubstring(userInput);
            int editIndex = extractInt(userInput);

            linkList.edit(editIndex, editString);

        }
        else if(userInput.find("quit")!=-1){ // the quit case

            break;

        }
        else{
            cout << "Invalid input. Try again.\n" << endl; // The case that the user did not input any keywords
        }

    }

}
