#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

typedef struct TreeNode* position;
typedef struct TreeNode {
	int el;
	position leftChild, rightChild;
}treeNode;


int menu(position root);
position find(position root, int wantedEl);
position insert(position root, int newEl);
position createNode(int newEl);
int inorderPrint(position root);
int postorderPrint(position root);
int preorderPrint(position root);
int levelorderPrint(position root);


int main() {
	//treeNode treeHead = { 0,NULL,NULL };		//mozemo bez head-a her nam je redudantan
	position root = NULL;
	int rootVal = 0;

	printf("\nUnesite vrijednost korijena: ");
	scanf("%d", &rootVal);

	root = insert(root, rootVal);

	//treeHead.leftChild = &root;

	menu(root);

	return EXIT_SUCCESS;
}

int menu(position root) {
	char pick = '\0';
	int el = 0;
	position result = NULL;

	while (1) {
		printf("\nUpisite '1' za naci odreden element u stablu, '2' za dodati novi element u stablo, '3' za ispisati stablo u inorder obliku, '4' za ispisati stablo u postorder obliku, '5' za ispisati stablo u preorder obliku,'6' za ispisati stablo u levelorder obliku a 0 za izaci iz programa\n");
		scanf(" %c", &pick);

		switch (pick) {
			case '0':

				printf("\nKraj programa!\n");

				break;

			case '1':

				printf("\nUnesite vrijednost elementa kojeg zelite pronaci u stablu: ");
				scanf("%d", &el);

				result = find(root, el);

				if (result != NULL)
					printf("\Element %d se nalazi na adresi %p\n", el, result);

				else
					printf("\nNeuspjelo pronalazanje elementa %d!\n", el);

				continue;

			case '2':

				printf("\nUnesite vrijednost elementa kojeg zelite dodati u stablo: ");
				scanf("%d", &el);

				root=insert(root, el);

				continue;

			case '3':

				inorderPrint(root);

				continue;


			case '4':

				postorderPrint(root);

				continue;

			case '5':

				preorderPrint(root);

				continue;

			case '6':

				levelorderPrint(root);

				continue;

			default:

				printf("\nKrivi unos!!\n");

				continue;
			}

		break;
	}

	return EXIT_SUCCESS;
}


position find(position root, int wantedEl) {
	if (root == NULL)
		return NULL;

	else if (wantedEl < root->el)
		return find(root->leftChild, wantedEl);

	else if (wantedEl > root->el)
		return find(root->rightChild, wantedEl);

	return root;
}

position insert(position root, int newEl) {

	if (root == NULL)
		return createNode(newEl);

	if (newEl <= root->el)
		root->leftChild = insert(root->leftChild, newEl);

	else if (newEl > root->el)
		root->rightChild = insert(root->rightChild, newEl);

	return root;
}

position createNode(int newEl) {
	position newNode = NULL;

	newNode = malloc(sizeof(treeNode));

	if (!newNode) {
		printf("\nNeuspjela alokacija memorije za newNode!\n");
		return NULL;
	}

	newNode->el = newEl;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	return newNode;
}

int inorderPrint(position root) {

	if (root != NULL) {
		inorderPrint(root->leftChild);
		printf("%d ", root->el);
		inorderPrint(root->rightChild);
	}

	return EXIT_SUCCESS;
}

int postorderPrint(position root) {

	if (root != NULL) {
		postorderPrint(root->leftChild);
		postorderPrint(root->rightChild);
		printf("%d ", root->el);

	}

	return EXIT_SUCCESS;
}

int preorderPrint(position root) {

	if (root != NULL) {
		printf("%d ", root->el);
		preorderPrint(root->leftChild);
		preorderPrint(root->rightChild);

	}

	return EXIT_SUCCESS;
}

int levelorderPrint(position root) {
	position current = NULL, queue[100] = { NULL };
	int front = 0, rear = 0;

	queue[rear] = root;

	while (front <= rear) {

		current = queue[front];

		printf("%d ", current->el);

		if (current->leftChild != NULL)
			queue[++rear] = current->leftChild;

		if (current->rightChild != NULL)
			queue[++rear] = current->rightChild;

		front++;
	}

	return EXIT_SUCCESS;