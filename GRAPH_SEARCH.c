#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GRAPH_SEARCH.h"
#include "data_types.h"

State* Create_Goal_State(const State* initial_state)
{
    State *goal = (State*)malloc(sizeof(State));
    if(goal == NULL) {
        Warning_Memory_Allocation();
    }
   unsigned char up_center    = initial_state->stickers[4];
    unsigned char left_center  = initial_state->stickers[13];
    unsigned char front_center = initial_state->stickers[22];
    unsigned char right_center = initial_state->stickers[31];
    unsigned char back_center  = initial_state->stickers[40];
    unsigned char down_center  = initial_state->stickers[49];

for (int i = 0;  i < 9;  i++) goal->stickers[i] = up_center;
    for (int i = 9;  i < 18; i++) goal->stickers[i] = left_center;
    for (int i = 18; i < 27; i++) goal->stickers[i] = front_center;
    for (int i = 27; i < 36; i++) goal->stickers[i] = right_center;
    for (int i = 36; i < 45; i++) goal->stickers[i] = back_center;
    for (int i = 45; i < 54; i++) goal->stickers[i] = down_center;

    return goal;
}


int main()
{
    Node *root_node;
    Node *goal_node;
    State *initial_state;
    State *goal_state;

    printf("\n======== ENTER INITIAL STATE =============== \n");
    initial_state = Create_State();

    goal_state = Create_Goal_State(initial_state);
    printf("\nGoal state is the solved cube.\n");
    Print_State(goal_state);
    printf("============================================\n\n");

    root_node = (Node*)malloc(sizeof(Node));
    if(root_node == NULL) {
        Warning_Memory_Allocation();
    }
    root_node->parent = NULL;
    root_node->path_cost = 0;
    root_node->action = NO_ACTION;
    root_node->state = *initial_state;

    free(initial_state);

    printf("Running Iterative Deepening A*...\n");
    goal_node = IDA_Star_Search(root_node, goal_state);

    Show_Solution_Path(goal_node);
    free(goal_state);

    return 0;
}
