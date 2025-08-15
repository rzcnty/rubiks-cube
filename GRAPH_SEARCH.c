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
    enum METHODS method;

    printf("1 --> Breast-First Search\n");
    printf("2 --> Uniform-Cost Search\n");
    printf("3 --> Depth-First Search\n");
    printf("4 --> Depth-Limited Search\n");
    printf("5 --> Iterative Deepening Search\n");
    printf("6 --> Greedy Search\n");
    printf("7 --> A* Search\n");
    printf("8 --> Generalized A* Search (Not Implemented)\n");
    printf("9 --> Iterative Deepening A* (IDA*)\n");
    printf("Select a method to solve the problem: ");
    scanf("%d", (int*)&method);

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
    root_node->Number_of_Child = 0;
    root_node->state = *initial_state;

    free(initial_state);

    switch(method)
    {
        case BreastFirstSearch:
        case UniformCostSearch:
        case GreedySearch:
            goal_node = First_GoalTest_Search_TREE(method, root_node, goal_state);
                break;
        case AStarSearch:
        case DepthFirstSearch: {
            goal_node = DepthType_Search_TREE(method, root_node, goal_state, -1); // -1 = limitsiz
            break;
        }
        case DepthLimitedSearch: {
            int max_level;
            printf("Enter maximum level for depth-limited search: ");
            scanf("%d", &max_level);
            goal_node = DepthType_Search_TREE(method, root_node, goal_state, max_level);
            break;
        }
        case IterativeDeepeningSearch: {
            int level;
            for(level = 0; ; level++){
                printf("Trying with level limit: %d\n", level);
                goal_node = DepthType_Search_TREE(IterativeDeepeningSearch, root_node, goal_state, level);
                if(goal_node != FAILURE){
                    printf("Goal found at level %d.\n", level);
                    break;
                }
            }
            break;
        }

        case IterativeDeepeningAStar: {
printf("Running Iterative Deepening A*...\n");
             goal_node = IDA_Star_Search(root_node, goal_state);
             break;
        }
        default:
            printf("ERROR: Unknown or not-yet-implemented method.\n");
            goal_node = FAILURE;
            exit(-1);
    }
    Show_Solution_Path(goal_node);

    free(goal_state);

    return 0;
}
