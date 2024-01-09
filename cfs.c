#include <stdio.h>
#include "utility.h"
#include "cfs.h"

struct node* minimal(struct node* root) {
	struct node* iterator = root;
	while (iterator->left != NULL) {
		iterator = iterator->left;
	}
	return iterator;
}
void decay(struct node* n){
	n->data->runTime -= n->data->decay;
}
struct node* cfs(struct process* processes, int time) {
	struct process* iterator = processes;
	struct node* root = NULL;
	struct node *newN = NULL;
	while (iterator != NULL) {
		iterator->runTime = iterator->PID;
		newN = newNode(iterator->PID);
		newN->data = iterator;
		root = insertRB(root,newN ); // die beginnende Knoten sind mit PID als val
		iterator = iterator->next;
	}
	for (int i = 0; i < time; i++) {
		struct node *min = minimal(root);
		printf("Time: %d PID: %d\n",min->val,min->data->PID);
		min->data->runTime += 10;
		iterate_post_order(root, decay);
		iterate_post_order(root, free_node);
		root = NULL;
		iterator = processes;
		while (iterator != NULL) {
			newN = newNode(iterator->runTime);
			newN->data = iterator;
			root = insertRB(root,newN );
			iterator = iterator->next;
		}
	}

	return root;
}


