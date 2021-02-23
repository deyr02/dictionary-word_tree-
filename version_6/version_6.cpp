// Version_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
//construction for node
//each node has 27 pointer, because 26 pointers will refer to 26 different letter and one node for end of word
// variable letter will hold a character
//counter will refer to how many pointer is  pointing  to other node.
typedef struct Node {
	int counter = 0;
	char letter;
	Node * next[27];
}NODE;

//construction  for root
// root does not have charcter it will refer only 26 pointer
// counter helps to measure how many pointer is  pointing to other node
typedef struct {
	int counter = 0;
	NODE* root[26];
}Head; //Header of the tree

//create the tree
// intialize counter 
//making all the pointer null;
Head * createHead() {
	Head * Dictionay = new Head; //creating head
	Dictionay->counter = 0;
	for (int i = 0; i < 27; i++) { //making all the pointer null
		Dictionay->root[i] = NULL;
	}
	return Dictionay; //return  head
}
// this function will check in head that wheher it is pointing to particular letter or not
// if the root pointing to particular letter then it will return true, otherwise it will return false.
//
bool check_letter_in_Head(Head * Current, char letter) {
	bool check = false; // intialize the variable that will check
	for (int i = 0; i < Current->counter; i++) { // looping through pointing array
		if (Current->root[i] != NULL) { 
			if (Current->root[i]->letter == letter) { // if the letter found, it will return true  and break the loop
				check = true;
				break;
			}
			else {
				check = false; 
			}
		}

	}
	return check; //return boolean value
}
//this function will check wheather this node is pointing to specific leteter or not
// this function will loop through the array of pointers.
//if the current noode pointing to specific letter it will return true else return false
bool check_letter_in_Nodes(NODE * Current, char letter) {
	bool check = false; //initialize variable as false

	for (int i = 0; i <Current->counter; i++) { //loop through array of pointers
		if (Current->next[i] != NULL) {
			if (Current->next[i]->letter == letter) {
				check = true;
				break;
			}
			else {
				check = false;
			}
		}

	}
	return check;
}

//this function will check in the root that the root is pointing to specific letter or not 
// if the root pointing to the letter the function will break the loop and retrun the index number else it will return an negetive integer.
//
int position_in_Head(Head * Current, char letter) {
	int check = -1;

	for (int i = 0; i < Current->counter; i++) {  //looping through the array of pointers
		check++;
		if (Current->root[i] != NULL) {
			if (Current->root[i]->letter == letter) { // check for particular word
				return check; 
				break; // break the loop
			}

		}


	}
	return -1;
}

//this will check the node that it is pointing to specfic word or not, if it is then it will return index number of the array of pointers else it will return neget integer.

int position_in_Node(NODE * Current, char letter) {
	int check = -1;

	for (int i = 0; i < Current->counter; i++) {// looping through array of pointers

		if (Current->next[i] != NULL) {
			if (Current->next[i]->letter == letter) { // matiching word
				return i;
				break;
			}

		}


	}
	return -1;
}
// this function will search for a word in the dictionary, if the word exist there it will return 1 else 0

int Search_Word(Head * head, char word[]) {
	bool checker = false; // this variable will help to identify the end of word '\0'
	int check = 0; // this variable will help to retun the search result if the workd found it will return 1 else 0
	int count = 0; //this variable will help to count how many number has found in the  dictionry
	if (strlen(word) != 0) { //checking that the length of the search word  is not 0
		NODE * pNext = NULL; //this variable will be used to travese the treee.

		for (int i = 0; i < strlen(word); i++) { // loop through word
			
			if (i == 0) {// the root always pointing the first letter of the word, this statement will check first letter of the word;
				bool check = check_letter_in_Head(head, word[i]); // checking for first letter int root that the first letter is pointing by the root or not
				if (check == false) { // if the letter is not pointing  by the root, it will break the loop and return 0
					break;
				}
				else { // if the first letter is pointing by root
					int Postion = position_in_Head(head, word[i]);// this statement will identify the which pointer in the root, pointing to that letter.
					pNext = head->root[Postion]; //the above statement will identify the index number, this statement will direct to next noode.
					count++; // this pointer will help to identify the the first letter found in the dictionary

				}
			}
			else { // this statement will justify that the current letter is not the first letter.
				bool check_NODE = check_letter_in_Nodes(pNext, word[i]); //the current node is pointing to the next lettet or not
				if (check_NODE == false) {// if thecurrent node is not pointing to the next letter 
					break; //this satement will break the loop.

				}
				else { // if the current node is pointing to the next letter
					int Position = position_in_Node(pNext, word[i]); // this statement will identify, which pointer is pointing the next letter.
					pNext = pNext->next[Position]; // directing to the next node
					count++; // count that the word is found
				}
			}

		}
		
		if (pNext != NULL) { // this statement will check the last leete of the word pointing to the end of line 
			for (int i = 0; i < pNext->counter; i++) {//loop through array of pointer
				if (pNext->next[i]->letter == '\0') { // checking for end of line 
					checker = true; // if end line characater is counting the current node it break the loop and return true;
					break;

				}
				checker = false;
			}
		}

		// this statement compare the length of word to how many word found in the dictionary and checking the last letter of the word pointing to end of line character in the next node
		// if codition is true variable check  will retun 1 
		if ((count == strlen(word)) && (checker == true)) {
			check = 1; // return that the word is found 
		}
		else {
			check = 0; // the statment represent that the workd is not  found
		}
		
	
	}
	return check; // retun that whether the word found or not
}
int Add_Word(Head * head, char word[]) { //this function will add word to the dictionary
	int avilavlity = 0;// this variable intialize to retun that the word is added or the word is  in the dictionary
	int checker = Search_Word(head, word); // this statement will check that the word is already there or not
	if (checker == 0) { // if the word is not in the dictionary
		avilavlity = 1; //return that the word is  added successfully
		NODE * LAST = new NODE; //intialize  a node that will will be pointing by the last letter of the word 
		LAST->letter = '\0'; //intialize end of the character
		if (strlen(word) != 0) { //checking that the length of the character is not o
			NODE * pNext = NULL; // intialize a variable which will direct the tree

			for (int i = 0; i <= strlen(word); i++) { //looping throgh length of characters
				NODE * pNew = new NODE;//hold the letter and add in the tree
				pNew->letter = word[i]; //adding letter in the node
				if (i == 0) { // checking that current letter is first letter or not
					bool check = check_letter_in_Head(head, word[i]); // checking the first letter in the root or not
					if (check == false) { // if the first letter is not pointing  by the root then add the word in the root
						head->root[head->counter] = pNew;//add new node in the root
						pNext = pNew; // refering to next node
						head->counter++; // the counter in the root will increase, to help to identify that how many node is pointing by the root
					}
					else { // if the first letter is already pointing by the root 
						int Postion = position_in_Head(head, word[i]); // if the word in the root, the statement will identify wich pointer is pointing to this word
						pNext = head->root[Postion]; // sirecing to next node.
					}
				}
				else {
					bool check_NODE = check_letter_in_Nodes(pNext, word[i]); //checking that next node  pointing to next leter or not
					if (check_NODE == false) { // if not 
						pNext->next[pNext->counter] = pNew; // this statment will add the letter
						pNext->counter++; // increaseing the counter
						pNext = pNew; //directing to the next node

					}
					else {
						int Position = position_in_Node(pNext, word[i]); // if the letter is in the tree it will redircting to the next node
						pNext = pNext->next[Position]; // dircting to next node
					}
				}
			}

			pNext->next[pNext->counter] = LAST; // adding end of line pointer at the end of the last letter node
			pNext->counter++;

		}

	}
	return avilavlity; // return that the the word is added succeses

}

void populate_dictionary(Head * Dictionary, const char fileName[]) {

	char word[100]; // 

	FILE * file; // initialize FILE Variable

	if (fopen_s(&file, fileName, "r") == 0) { // open the MOCK_DATA file in reading mode and validating that file exists
		char buffer[100]; // setting up size for each line from the file
		size_t i; // intialize  numbers of lines in the file;
		for (i = 0; i<10000; ++i) {

			if (fgets(buffer, sizeof buffer, file) != NULL) {
				size_t len = strlen(buffer); 
				if (len > 0 && buffer[len - 1] == '\n') { //cutting of end of line character from the word which is read you 
					buffer[--len] = '\0'; // 
					int n = Add_Word(Dictionary, buffer); // adding vaules to the list
					if (n == 1) {
						printf("\nThe Word '%s' has been added successfully\n", buffer);
					}
					else {
						printf("\nThe Word '%s' is in the Dictionary\n", buffer);
					}
				}
			}

		}
		fclose(file);//closing file;
	}
	else {
		printf("File not found\n");
	}
}

int main()
{
	Head * Dictionary = NULL; // initialize dictionary
	int selection = ' '; // this variable will help to input select form the menu
	printf("\n\n");
	printf("---------------WELCOME------------------\n");
	printf("\n\n");
	printf("-------------ASSIGNMENT------------------\n\n");
	printf("   THIS ASSIGNMENT IS COMPLETED BY\n");
	printf("\n\n");
	printf("            RAJIB DEY\n");
	printf("        STUDENT ID : 1446112\n");
	printf("\n\n");
	printf("\n\n");
	printf(" PLEASE PRESS ENTER TO RUN THE PROGRAM\n");



	while (selection) {

		if (selection == '1') // create new dictionay
		{
			system("cls"); // clear console field
			printf("\n");
			printf("\n");
			;
			if (Dictionary == NULL) {
				Dictionary = createHead(); //creating the list


				printf(" THE DICTIONARY  HAS BEEN CREATED SUCCESSFULLY\n");
			}
			else
			{

				printf(" THE DICTIONARY IS ALREADY CREATED\n");
			}
		}
		else if (selection == '2') { // add new word
			system("cls");//clear the console
			printf("\n");

			printf("\n");
			printf("---------------ADD WORD--------------------");

			if (Dictionary == NULL) {
				printf("\n");
				
				printf(" PLEASE CREATE THE DICTIONARY FIRST\n");

			}
			else {
				getchar();
				char WORD[100]; //intialize variable for 
				
				printf("\n"); 
				printf("PLEASE ENTER YOUR WORD:  ");
				fgets(WORD, 100, stdin); //getword from the user input


				size_t len = strlen(WORD); // lenght of the word
				if (len > 0 && WORD[len - 1] == '\n') { //cutting of end of line
					WORD[--len] = '\0';

					for (int i = 0; i < strlen(WORD); i++) { //converting user input to lower case
						char w = WORD[i];
						WORD[i] = towlower(w);
					}
					int n = Add_Word(Dictionary, WORD); // adding vaules to the list
					if (n == 1) {
						printf("\n");
						printf("\nThe Word '%s' has been added successfully\n", WORD);
					}
					else {
						printf("\n");
						printf("\nThe Word '%s' is in the Dictionary\n", WORD);
					}
				}
			}


		}
		else if (selection == '3') {
			system("cls");
			printf("\n");

			printf("\n");
			printf("---------------SEARCH WORD--------------------");

			if (Dictionary == NULL) {
				printf("\n");
				printf(" PLEASE CREATE THE DICTIONARY FIRST\n");
			}
			else {
				getchar();
				char WORD[100]; //intialize variable to get user input
				char p[100];
				printf("\n");
				printf("PLEASE ENTER THE WORD YOUR WANT TO SEARCH:  ");
				fgets(WORD, 100, stdin); // user input 
				size_t len = strlen(WORD); // length of the word
				if (len > 0 && WORD[len - 1] == '\n') { // cutting the end of line
					WORD[--len] = '\0'; //cutting end of line
					for (int i = 0; i < strlen(WORD); i++) { // converting  user input to lower case
						char w = WORD[i];
						char C = towlower(w);
						WORD[i] = C;
					}
					int n = Search_Word(Dictionary, WORD); // Search for the word
					if (n == 1) {
						printf("\n");
						printf("FOUND\n");
						printf("\nTHE WORD '%s' IS IN THE DICTIONARY\n", WORD);
					}
					else {
						printf("\n");
						printf("NOT FOUND\n");
						printf("\nTHE WORD '%s' IS NOT IN THE DICTIONARY\n", WORD);
					}
				}
			}


		}
		else if (selection == '4') {
			system("cls"); // clear the console
			printf("\n");
			printf("\n");
			if (Dictionary == NULL) {
				printf(" PLEASE CREATE THE DICTIONARY FIRST\n");
			}
			else {
				populate_dictionary(Dictionary, "word.txt"); // populate the dictionary
			}
		}

		else if (selection == '0') { //close progtm

			return 0; //close application
		}

		// Menu
		selection = getchar();

		printf("\n.................MENU.........................\n");
		printf("Press-1: TO CREATE THE DICTIONARY\n");
		printf("Press-2: TO ADD NEW WORD\n");
		printf("Press-3: TO SEARCH WORD\n");
		printf("Press-4: TO POPULATE DICTIONARY FROM FILE\n");
		printf("Press-0: TO EXIT THE PROGRAM\n");

		printf("\n SELECT OPTION:");


	}


	
}

