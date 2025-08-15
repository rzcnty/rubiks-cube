#ifndef DATA_TYPES_H
#define DATA_TYPES_H

// ==================== WRITE YOUR OPTIONAL DATA TYPES IF YOU NEED =============
// ====== WRITE YOUR COMPULSORY (BUT SPECIFIC TO THE PROBLEM) DATA TYPES =======

enum ACTIONS // All possible actions
{
	MOVE_U,
    MOVE_D,
    MOVE_L,
    MOVE_R,
    MOVE_F,
    MOVE_B,
    MOVE_U_PRIME,
    MOVE_D_PRIME,
    MOVE_L_PRIME,
    MOVE_R_PRIME,
    MOVE_F_PRIME,
    MOVE_B_PRIME,

    NO_ACTION=-1 // This action is used to indicate no action taken
};
//Up, Down, Left, Right, Front, Back
// Prime means counterclockwise.

typedef struct State  
{
    unsigned char stickers[54]; 
} State;

// ================== YOU DO NOT NEED TO CHANGE THIS PART ======================


// This struct is used to determine a new state and action in transition model
typedef struct Transition_Model
{
    State new_state;
    float step_cost;
}Transition_Model;

typedef struct Node
{
    State state;
    float path_cost;
    enum ACTIONS action; //The action applied to the parent to generate this node
    struct Node *parent;
    float h_n;
}Node;

#endif
