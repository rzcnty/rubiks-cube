/* 
    These functions are standard for graph search algorithms and you do not need to
    change them for different search problems.
    
    However, if you insert the generalized A* algorithm, 
	        you should update First_InsertFrontier_Search_TREE()
			              and Insert_Priority_Queue_GENERALIZED_A_Star(),  which is similar to Insert_Priority_Queue_A_Star()    
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GRAPH_SEARCH.h"
#include "data_types.h"
#include "HashTable.h"

//______________________________________________________________________________
Node* IDA_Star_Recursive_Search(Node* node, State* goal_state, float threshold, float* next_threshold)
{
    float f_n = node->path_cost + node->h_n;

    if (f_n > threshold) {
        if (f_n < *next_threshold) {
            *next_threshold = f_n;
        }
        return FAILURE;
    }

    if (Goal_Test(&node->state, goal_state)) {
        return node;
    }

    enum ACTIONS action;
    for (action = 0; action < NUM_ACTIONS; action++) {
        Node* child = Child_Node(node, action);

        if (child != NULL) {
            child->h_n = Compute_Heuristic_Function(&child->state, goal_state);

            Node* result = IDA_Star_Recursive_Search(child, goal_state, threshold, next_threshold);
            if (result != FAILURE) {
                return result;
            }
            free(child);
        }
    }
    return FAILURE;
}

Node* IDA_Star_Search(Node* root, State* goal_state)
{
    if (Goal_Test(&root->state, goal_state)) {
        printf("\nTotal nodes searched: 1\n");
        return root;
    }

    root->h_n = Compute_Heuristic_Function(&root->state, goal_state);
    float threshold = root->h_n;

    int total_searched_nodes = 0;

    while (1) {
        printf("Searching with threshold: %.2f\n", threshold);

        float next_threshold = 1e9;

        Node* root_copy = (Node*)malloc(sizeof(Node));
        memcpy(root_copy, root, sizeof(Node));

        Node* result = IDA_Star_Recursive_Search(root_copy, goal_state, threshold, &next_threshold);

        if (result == FAILURE) {
            free(root_copy);
        }

        if (result != FAILURE) {
            printf("\nTotal nodes searched: %d\n", total_searched_nodes);
            return result;
        }

        if (next_threshold == 1e9) {
            return FAILURE;
        }

        threshold = next_threshold;
    }
}
//______________________________________________________________________________
Node* Child_Node(Node *const parent, const enum ACTIONS action)
{
      Node *child = NULL;
      Transition_Model trans_model;

      if (parent->action != NO_ACTION) {
          if (action == parent->action + 6 || action == parent->action - 6) {
              return NULL;
          }
      }

      if( Result(&(parent->state), action, &trans_model) ){
          child = (Node*)malloc(sizeof(Node));
          if(child==NULL)
               Warning_Memory_Allocation(); 
           
          child->state     = trans_model.new_state;
          child->path_cost = parent->path_cost + trans_model.step_cost;
          child->parent    = parent;
          child->action    = action;
          child->h_n       = 0;
      }
      return child;
}

//______________________________________________________________________________
void Show_Solution_Path(Node *const goal)
{   
    Node *temp;
	if(goal==FAILURE)
		printf("THE SOLUTION CAN NOT BE FOUND.\n");
	else{
		printf("\nTHE COST PATH IS %.2f.\n", goal->path_cost);
		printf("\nTHE SOLUTION PATH IS:\n");
		for(temp = goal; temp!= NULL; temp = temp->parent)
		{
			Print_State(&(temp->state));
			if(temp->parent!= NULL){
				printf("\n\taction(");
                Print_Action(temp->action);
                printf(")\n");
            }			
		}
	}		
}


//______________________________________________________________________________
void Warning_Memory_Allocation()
{
    printf("The memory Error in alloacation process! Press a key to exit.\n");
    exit(-1);
}

