#ifndef GRAPH_SEARCH_H
#define GRAPH_SEARCH_H

#include "data_types.h"

// ==================== WRITE YOUR OPTIONAL COMMANDS ===========================

// ========  YOUR COMPULSORY (BUT SPECIFIC TO THE PROBLEM) COMMANDS ============

#define NUM_ACTIONS 12
#define MAX_SEARCHED_NODE 100000000 // exit from the search process if it is exceeded

// ================== YOU DO NOT NEED TO CHANGE THIS PART ======================
#define TRUE       1
#define FALSE      0
#define FAILURE    NULL


// =========  YOUR COMPULSORY (BUT SPECIFIC TO THE PROBLEM) DECLARATIONS =======
State* Create_State();
void Print_State(const State *const state);
void Print_Action(const enum ACTIONS action);
int Result(const State *const parent_state, const enum ACTIONS action, Transition_Model *const trans_model);
float Compute_Heuristic_Function(const State *const state, const State *const goal); 
int Goal_Test(const State *const state, const State *const goal_state);
State* Create_Goal_State(const State* initial_state);

// ======= YOU DO NOT NEED TO CHANGE THIS COMPULSORY DECLARATIONS EXCEPT INSERTION OF THE GENERALIZED A* ALGORITHM==============
Node* IDA_Star_Search(Node* root, State* goal_state);
Node* Child_Node(Node *const parent, const enum ACTIONS action); 
void Show_Solution_Path(Node *const goal);
void IDA_Clear_Branch(Node *node);
void Warning_Memory_Allocation();

// ==================== WRITE YOUR OPTIONAL DECLARATIONS =======================

#endif
