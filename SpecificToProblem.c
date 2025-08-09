/* 
    These functions are compulsory for search algorithms but they are specific
    to problems. More clearly, you must must update their blocks but do not change
    their input and output parameters.
    
    Also, you can add new functions at the end of file by declaring them in GRAPH_SEARCH.h
*/

#include "GRAPH_SEARCH.h"
#include "data_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//______________________________________________________________________________
State* Create_State()
{
	State *state = (State*)malloc(sizeof(State));
    if(state==NULL)
    	Warning_Memory_Allocation(); 
   
   	 printf("========================================================================\n");
    printf("Rubik's cube solver\n");
    printf("========================================================================\n");
    printf("Enter the cube's state as a 54-character string.\n\n");
    printf("Color codes:\n");
    printf("  0: White   1: Orange   2: Green\n");
    printf("  3: Red    4: Blue        5: Yellow\n\n");
    printf("Input Order:\n");
    printf("1. FIRST UPPER FACE (UP), then LEFT (LEFT), then FRONT (FRONT), then RIGHT (RIGHT),\n");
    printf("   then BACK (BACK) and finally LOWER (DOWN) face colors.\n\n");
    printf("2. For each face, enter 9 colors, ROW BY ROW and from left to right:\n");
    printf("   Example input order for the UPPER face:\n");
    printf("      +---+---+---+\n");
    printf("      | 1 | 2 | 3 |  <-- First this row (left, middle, right)\n");
    printf("      +---+---+---+\n");
    printf("      | 4 | 5 | 6 |  <-- Then this row (left, middle, right)\n");
    printf("      +---+---+---+\n");
    printf("      | 7 | 8 | 9 |  <-- Finally this row (left, middle, right)\n");
    printf("      +---+---+---+\n\n");
    printf("Example (for a completely solved cube):\n");
    printf("000000000111111111222222222333333333444444444555555555\n\n");
    printf("Enter your cube's state: ");

	       char input_string[100];
    scanf("%99s", input_string);

    if (strlen(input_string) != 54) {
        printf("ERROR: The entered string must be exactly 54 characters long!\n");
        printf("Terminating the program.\n");
        free(state);
        exit(1);
    }

    int i;
    for (i = 0; i < 54; i++) {
        char c = input_string[i];
        if (c >= '0' && c <= '5') {
            state->stickers[i] = c - '0';
        } else {
            printf("ERROR: Invalid character '%c' found. Only digits 0-5 are allowed.\n", c);
            printf("Terminating the program.\n");
            free(state);
            exit(1);
        }
    }

    printf("\nInitial state created successfully.\n");
    Print_State(state);
    printf("\n");
    return state;    
}

//______________________________________________________________________________
void Print_State(const State *const state)
{
    int i;
    printf("Cube State: ");
    for(i = 0; i < 54; i++) {
        printf("%d", state->stickers[i]);
    }
    printf("\n");
}

//______________________________________________________________________________
void Print_Action(const enum ACTIONS action)
{
   switch(action){
        case NO_ACTION:     printf("NO ACTION"); break;
        case MOVE_U:        printf("U"); break;
        case MOVE_D:        printf("D"); break;
        case MOVE_L:        printf("L"); break;
        case MOVE_R:        printf("R"); break;
        case MOVE_F:        printf("F"); break;
        case MOVE_B:        printf("B"); break;
        case MOVE_U_PRIME:  printf("U'"); break;
        case MOVE_D_PRIME:  printf("D'"); break;
        case MOVE_L_PRIME:  printf("L'"); break;
        case MOVE_R_PRIME:  printf("R'"); break;
        case MOVE_F_PRIME:  printf("F'"); break;
        case MOVE_B_PRIME:  printf("B'"); break;
    }        
}

//______________________________________________________________________________
int Result(const State *const parent_state, const enum ACTIONS action, Transition_Model *const trans_model)
{
   State next_state;
    next_state=*parent_state;
State* s = &next_state;

        switch (action)
    {
        case MOVE_U: {

    unsigned char temp_corner = s->stickers[0];
    s->stickers[0] = s->stickers[6];
    s->stickers[6] = s->stickers[8];
    s->stickers[8] = s->stickers[2];
    s->stickers[2] = temp_corner;

    unsigned char temp_edge = s->stickers[1];
    s->stickers[1] = s->stickers[3];
    s->stickers[3] = s->stickers[7];
    s->stickers[7] = s->stickers[5];
    s->stickers[5] = temp_edge;

    unsigned char temp_side[3];
    temp_side[0] = s->stickers[9];
    temp_side[1] = s->stickers[10];
    temp_side[2] = s->stickers[11];

    s->stickers[9] = s->stickers[18];
    s->stickers[10] = s->stickers[19];
    s->stickers[11] = s->stickers[20];

    s->stickers[18] = s->stickers[27];
    s->stickers[19] = s->stickers[28];
    s->stickers[20] = s->stickers[29];

    s->stickers[27] = s->stickers[36];
    s->stickers[28] = s->stickers[37];
    s->stickers[29] = s->stickers[38];

    s->stickers[36] = temp_side[0];
    s->stickers[37] = temp_side[1];
    s->stickers[38] = temp_side[2];
               break; }

        case MOVE_U_PRIME: {

    unsigned char temp_corner = s->stickers[0];
    s->stickers[0] = s->stickers[2];
    s->stickers[2] = s->stickers[8];
    s->stickers[8] = s->stickers[6];
    s->stickers[6] = temp_corner;

    unsigned char temp_edge = s->stickers[1];
    s->stickers[1] = s->stickers[5];
    s->stickers[5] = s->stickers[7];
    s->stickers[7] = s->stickers[3];
    s->stickers[3] = temp_edge;

    unsigned char temp_side[3];
    temp_side[0] = s->stickers[9];
    temp_side[1] = s->stickers[10];
    temp_side[2] = s->stickers[11];

    s->stickers[9] = s->stickers[36];
    s->stickers[10] = s->stickers[37];
    s->stickers[11] = s->stickers[38];

    s->stickers[36] = s->stickers[27];
    s->stickers[37] = s->stickers[28];
    s->stickers[38] = s->stickers[29];

    s->stickers[27] = s->stickers[18];
    s->stickers[28] = s->stickers[19];
    s->stickers[29] = s->stickers[20];

    s->stickers[18] = temp_side[0];
    s->stickers[19] = temp_side[1];
    s->stickers[20] = temp_side[2];
            break; }

            case MOVE_D: {

    unsigned char temp_corner = s->stickers[45];
    s->stickers[45] = s->stickers[47];
    s->stickers[47] = s->stickers[53];
    s->stickers[53] = s->stickers[51];
    s->stickers[51] = temp_corner;

    unsigned char temp_edge = s->stickers[46];
    s->stickers[46] = s->stickers[50];
    s->stickers[50] = s->stickers[52];
    s->stickers[52] = s->stickers[48];
    s->stickers[48] = temp_edge;

    unsigned char temp_side[3];
    temp_side[0] = s->stickers[15];
    temp_side[1] = s->stickers[16];
    temp_side[2] = s->stickers[17];

    s->stickers[15] = s->stickers[24];
    s->stickers[16] = s->stickers[25];
    s->stickers[17] = s->stickers[26];

    s->stickers[24] = s->stickers[33];
    s->stickers[25] = s->stickers[34];
    s->stickers[26] = s->stickers[35];

    s->stickers[33] = s->stickers[42];
    s->stickers[34] = s->stickers[43];
    s->stickers[35] = s->stickers[44];

    s->stickers[42] = temp_side[0];
    s->stickers[43] = temp_side[1];
    s->stickers[44] = temp_side[2];
            break; }

            case MOVE_D_PRIME: {
    unsigned char temp_corner = s->stickers[45];
    s->stickers[45] = s->stickers[51];
    s->stickers[51] = s->stickers[53];
    s->stickers[53] = s->stickers[47];
    s->stickers[47] = temp_corner;

    unsigned char temp_edge = s->stickers[46];
    s->stickers[46] = s->stickers[48];
    s->stickers[48] = s->stickers[52];
    s->stickers[52] = s->stickers[50];
    s->stickers[50] = temp_edge;

    unsigned char temp_side[3];
    temp_side[0] = s->stickers[15];
    temp_side[1] = s->stickers[16];
    temp_side[2] = s->stickers[17];

    s->stickers[15] = s->stickers[42];
    s->stickers[16] = s->stickers[43];
    s->stickers[17] = s->stickers[44];

    s->stickers[42] = s->stickers[33];
    s->stickers[43] = s->stickers[34];
    s->stickers[44] = s->stickers[35];

    s->stickers[33] = s->stickers[24];
    s->stickers[34] = s->stickers[25];
    s->stickers[35] = s->stickers[26];

    s->stickers[24] = temp_side[0];
    s->stickers[25] = temp_side[1];
    s->stickers[26] = temp_side[2];

                break; }
case MOVE_L: {
unsigned char temp_corner = s->stickers[9];
    s->stickers[9] = s->stickers[15];
    s->stickers[15] = s->stickers[17];
    s->stickers[17] = s->stickers[11];
    s->stickers[11] = temp_corner;

    unsigned char temp_edge = s->stickers[10];
    s->stickers[10] = s->stickers[12];
    s->stickers[12] = s->stickers[16];
    s->stickers[16] = s->stickers[14];
    s->stickers[14] = temp_edge;

    unsigned char temp_side[3];
    temp_side[0] = s->stickers[0];
    temp_side[1] = s->stickers[3];
    temp_side[2] = s->stickers[6];

    s->stickers[0] = s->stickers[44];
    s->stickers[3] = s->stickers[41];
    s->stickers[6] = s->stickers[38];

    s->stickers[44] = s->stickers[45];
    s->stickers[41] = s->stickers[48];
    s->stickers[38] = s->stickers[51];

    s->stickers[45] = s->stickers[18];
    s->stickers[48] = s->stickers[21];
    s->stickers[51] = s->stickers[24];

    s->stickers[18] = temp_side[0];
    s->stickers[21] = temp_side[1];
    s->stickers[24] = temp_side[2];

                break; }
 case MOVE_L_PRIME: {
unsigned char temp_corner = s->stickers[9];
    s->stickers[9] = s->stickers[11];
    s->stickers[11] = s->stickers[17];
    s->stickers[17] = s->stickers[15];
    s->stickers[15] = temp_corner;

    unsigned char temp_edge = s->stickers[10];
    s->stickers[10] = s->stickers[14];
    s->stickers[14] = s->stickers[16];
    s->stickers[16] = s->stickers[12];
    s->stickers[12] = temp_edge;

    unsigned char temp_side[3];
    temp_side[0] = s->stickers[0];
    temp_side[1] = s->stickers[3];
    temp_side[2] = s->stickers[6];

    s->stickers[0] = s->stickers[18];
    s->stickers[3] = s->stickers[21];
    s->stickers[6] = s->stickers[24];

    s->stickers[18] = s->stickers[45];
    s->stickers[21] = s->stickers[48];
    s->stickers[24] = s->stickers[51];

    s->stickers[45] = s->stickers[44];
    s->stickers[48] = s->stickers[41];
    s->stickers[51] = s->stickers[38];

    s->stickers[44] = temp_side[0];
    s->stickers[41] = temp_side[1];
    s->stickers[38] = temp_side[2];

                break; }
 case MOVE_R: {
unsigned char temp_corner = s->stickers[27];
    s->stickers[27] = s->stickers[33];
    s->stickers[33] = s->stickers[35];
    s->stickers[35] = s->stickers[29];
    s->stickers[29] = temp_corner;

    unsigned char temp_edge = s->stickers[28];
    s->stickers[28] = s->stickers[30];
    s->stickers[30] = s->stickers[34];
    s->stickers[34] = s->stickers[32];
    s->stickers[32] = temp_edge;

    unsigned char temp_side[3];
    temp_side[0] = s->stickers[2];
    temp_side[1] = s->stickers[5];
    temp_side[2] = s->stickers[8];

    s->stickers[2] = s->stickers[20];
    s->stickers[5] = s->stickers[23];
    s->stickers[8] = s->stickers[26];

    s->stickers[20] = s->stickers[47];
    s->stickers[23] = s->stickers[50];
    s->stickers[26] = s->stickers[53];

    s->stickers[47] = s->stickers[42];
    s->stickers[50] = s->stickers[39];
    s->stickers[53] = s->stickers[36];

    s->stickers[42] = temp_side[0];
    s->stickers[39] = temp_side[1];
    s->stickers[36] = temp_side[2];

                break; }
 case MOVE_R_PRIME: {
unsigned char temp_corner = s->stickers[27];
    s->stickers[27] = s->stickers[29];
    s->stickers[29] = s->stickers[35];
    s->stickers[35] = s->stickers[33];
    s->stickers[33] = temp_corner;

    unsigned char temp_edge = s->stickers[28];
    s->stickers[28] = s->stickers[32];
    s->stickers[32] = s->stickers[34];
    s->stickers[34] = s->stickers[30];
    s->stickers[30] = temp_edge;

    unsigned char temp_side[3];
    temp_side[0] = s->stickers[2];
    temp_side[1] = s->stickers[5];
    temp_side[2] = s->stickers[8];

    s->stickers[2] = s->stickers[42];
    s->stickers[5] = s->stickers[39];
    s->stickers[8] = s->stickers[36];

    s->stickers[42] = s->stickers[47];
    s->stickers[39] = s->stickers[50];
    s->stickers[36] = s->stickers[53];

    s->stickers[47] = s->stickers[20];
    s->stickers[50] = s->stickers[23];
    s->stickers[53] = s->stickers[26];

    s->stickers[20] = temp_side[0];
    s->stickers[23] = temp_side[1];
    s->stickers[26] = temp_side[2];
                break; }
case MOVE_F: {
unsigned char temp_corner = s->stickers[18];
    s->stickers[18] = s->stickers[24];
    s->stickers[24] = s->stickers[26];
    s->stickers[26] = s->stickers[20];
    s->stickers[20] = temp_corner;

    unsigned char temp_edge = s->stickers[19];
    s->stickers[19] = s->stickers[21];
    s->stickers[21] = s->stickers[25];
    s->stickers[25] = s->stickers[23];
    s->stickers[23] = temp_edge;

    unsigned char temp_side[3];
    temp_side[0] = s->stickers[6];
    temp_side[1] = s->stickers[7];
    temp_side[2] = s->stickers[8];

    s->stickers[6] = s->stickers[17];
    s->stickers[7] = s->stickers[14];
    s->stickers[8] = s->stickers[11];

    s->stickers[17] = s->stickers[47];
    s->stickers[14] = s->stickers[46];
    s->stickers[11] = s->stickers[45];

    s->stickers[47] = s->stickers[27];
    s->stickers[46] = s->stickers[30];
    s->stickers[45] = s->stickers[33];

    s->stickers[27] = temp_side[0];
    s->stickers[30] = temp_side[1];
    s->stickers[33] = temp_side[2];

                break; }
case MOVE_F_PRIME: {
unsigned char temp_corner = s->stickers[18];
    s->stickers[18] = s->stickers[20];
    s->stickers[20] = s->stickers[26];
    s->stickers[26] = s->stickers[24];
    s->stickers[24] = temp_corner;

    unsigned char temp_edge = s->stickers[19];
    s->stickers[19] = s->stickers[23];
    s->stickers[23] = s->stickers[25];
    s->stickers[25] = s->stickers[21];
    s->stickers[21] = temp_edge;

    unsigned char temp_side[3];
    temp_side[0] = s->stickers[6];
    temp_side[1] = s->stickers[7];
    temp_side[2] = s->stickers[8];

    s->stickers[6] = s->stickers[27];
    s->stickers[7] = s->stickers[30];
    s->stickers[8] = s->stickers[33];

    s->stickers[27] = s->stickers[47];
    s->stickers[30] = s->stickers[46];
    s->stickers[33] = s->stickers[45];

    s->stickers[47] = s->stickers[17];
    s->stickers[46] = s->stickers[14];
    s->stickers[45] = s->stickers[11];

    s->stickers[17] = temp_side[0];
    s->stickers[14] = temp_side[1];
    s->stickers[11] = temp_side[2];

                break; }
case MOVE_B: {
unsigned char temp_corner = s->stickers[36];
    s->stickers[36] = s->stickers[38];
    s->stickers[38] = s->stickers[44];
    s->stickers[44] = s->stickers[42];
    s->stickers[42] = temp_corner;

    unsigned char temp_edge = s->stickers[37];
    s->stickers[37] = s->stickers[41];
    s->stickers[41] = s->stickers[43];
    s->stickers[43] = s->stickers[39];
    s->stickers[39] = temp_edge;

    unsigned char temp_side[3];
    temp_side[0] = s->stickers[0];
    temp_side[1] = s->stickers[1];
    temp_side[2] = s->stickers[2];

    s->stickers[0] = s->stickers[15];
    s->stickers[1] = s->stickers[12];
    s->stickers[2] = s->stickers[9];

    s->stickers[15] = s->stickers[53];
    s->stickers[12] = s->stickers[52];
    s->stickers[9] = s->stickers[51];

    s->stickers[53] = s->stickers[29];
    s->stickers[52] = s->stickers[32];
    s->stickers[51] = s->stickers[35];

    s->stickers[29] = temp_side[0];
    s->stickers[32] = temp_side[1];
    s->stickers[35] = temp_side[2];

                break; }
case MOVE_B_PRIME: {
unsigned char temp_corner = s->stickers[36];
    s->stickers[36] = s->stickers[42];
    s->stickers[42] = s->stickers[44];
    s->stickers[44] = s->stickers[38];
    s->stickers[38] = temp_corner;

    unsigned char temp_edge = s->stickers[37];
    s->stickers[37] = s->stickers[39];
    s->stickers[39] = s->stickers[43];
    s->stickers[43] = s->stickers[41];
    s->stickers[41] = temp_edge;

    unsigned char temp_side[3];
    temp_side[0] = s->stickers[0];
    temp_side[1] = s->stickers[1];
    temp_side[2] = s->stickers[2];

    s->stickers[0] = s->stickers[29];
    s->stickers[1] = s->stickers[32];
    s->stickers[2] = s->stickers[35];

    s->stickers[29] = s->stickers[53];
    s->stickers[32] = s->stickers[52];
    s->stickers[35] = s->stickers[51];

    s->stickers[53] = s->stickers[15];
    s->stickers[52] = s->stickers[12];
    s->stickers[51] = s->stickers[9];

    s->stickers[15] = temp_side[0];
    s->stickers[12] = temp_side[1];
    s->stickers[9] = temp_side[2];

                break; }

    default:
        break;

    }
         trans_model->new_state=next_state;
    trans_model->step_cost = 1.0f;
    return 1;
}

//______________________________________________________________________________
float Compute_Heuristic_Function(const State *const state, const State *const goal)
{
    int misplaced_count = 0;
    int i;

    for (i = 0; i < 54; i++) {
        if (state->stickers[i] != goal->stickers[i]) {
            misplaced_count++;
        }
    }

    float h = (float)misplaced_count / 8.0f;
    return h * 2.0f;
}
//_______________ Update if your goal state is not determined initially ___________________________________
int Goal_Test(const State *const state, const State *const goal_state)
{
    int i;
    for(i = 0; i < 54; i++){
        if(state->stickers[i] != goal_state->stickers[i]){
            return 0;
        }
    }
    return 1;}

// ==================== WRITE YOUR OPTIONAL FUNCTIONS (IF REQUIRED) ==========================
