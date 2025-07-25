#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GRAPH_SEARCH.h"
#include "data_types.h"

State* Create_Goal_State()
{
    State *goal = (State*)malloc(sizeof(State));
    if(goal == NULL) {
        Warning_Memory_Allocation();
    }
    int i;
    for (i = 0; i < 9; i++)  goal->stickers[i] = 0; // Up: White
    for (i = 9; i < 18; i++) goal->stickers[i] = 1; // Left: Orange
    for (i = 18; i < 27; i++) goal->stickers[i] = 2; // Front: Green
    for (i = 27; i < 35; i++) goal->stickers[i] = 3; // Right: Red
    for (i = 35; i < 45; i++) goal->stickers[i] = 4; // Back: Blue
    for (i = 45; i < 54; i++) goal->stickers[i] = 5; // Down: Yellow

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
    scanf("%d", &method);

    printf("\n======== ENTER INITIAL STATE =============== \n");
    initial_state = Create_State();

    goal_state = Create_Goal_State();
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
        case AStarSearch:
            goal_node = First_GoalTest_Search_TREE(method, root_node, goal_state);
            break;
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
        case IterativeDeepeningA*: {

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
