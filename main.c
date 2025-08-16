#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solver.h"
#include "data_types.h"

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
