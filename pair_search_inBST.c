#include <stdio.h>
#include <stdlib.h>
#define maxSize 100

typedef struct node {
	int value;
	node *left, *right;
} node;

typedef struct {
	int size, top;
	node **v;
} Stack;

node *newNode(int x) {
	node *aux = (node*)malloc(sizeof(node));
	aux->value = x;
	aux->left = aux->right = NULL;
	return aux;
}

node *insert(node *root, int x) {
	if (root == NULL) return newNode(x);

	if (x < root->value)
		root->left = insert(root->left, x);
	else if (x > root->value)
		root->right = insert(root->right, x);
}

Stack *createStack(int size) {
	Stack *stack = (Stack *)malloc(sizeof(Stack));
	stack->size = size;
	stack->top = -1;
	stack->v = (node **)malloc(stack->size * sizeof(node));
	return stack;
}

int isFull(Stack *stack) {
	return stack->top == stack->size - 1;
}

int isEmpty(Stack *stack) {
	return stack->top == -1;
}

void push(Stack *stack, node *x) {
	if (isFull(stack))
		return;
	stack->v[++stack->top] = x;
}

node *pop(Stack *stack) {
	if (isEmpty(stack))
		return NULL;
	return stack->v[stack->top--];
}

bool isPairPresent(node *root, int target) {
	Stack *s1 = createStack(maxSize);
	Stack *s2 = createStack(maxSize);

	bool done1 = false, done2 = false;
	int val1 = 0, val2 = 0;
	node *curr1 = root, *curr2 = root;

	while (true) {
		while (done1 == false)
		{
			if (curr1 != NULL) {
				push(s1,curr1);
				curr1 = curr1->left;
			}
			else {
				if (isEmpty(s1))
					done1 = true;
				else {
					curr1 = pop(s1);
					val1 = curr1->value;
					curr1 = curr1->right;
					done1 = true;
				}
			}
		}
		while (done2 == false) 
		{
			if (curr2 != NULL) {
				push(s2, curr2);
				curr2 = curr2->right;
			}
			else {
				if (isEmpty(s2))
					done2 = true;
				else {
					curr2 = pop(s2);
					val2 = curr2->value;
					curr2 = curr2->left;
					done2 = true;
				}
			}
		}
		if (val1 != val2 && val1 + val2 == target) {
			printf("Pair found: %d + %d = %d", val1, val2, target);
			return true;
		}
		else if (val1 + val2 < target)
			done1 = false;
		else if (val1 + val2 > target)
			done2 = false;
		if (val1 >= val2)
			return false;
	}
}

void printSortedBST(node *root) {
	if (root != NULL) {
		printSortedBST(root->left);
		printf("%d ", root->value);
		printSortedBST(root->right);
	}
}

int main()
{
	int n, val;
	node *root = NULL;
	scanf("%d %d", &n, &val);
	for (int x, i = 0 ; i < n ; ++i)
	{
		scanf("%d", &x);
		if (!i) root = insert(root, x);
		else insert(root,x);
	}
	//printSortedBST(root);
	if (isPairPresent(root,val) == false)
		printf("The pair can't be found!");
	printf("\n");
	return 0;
}