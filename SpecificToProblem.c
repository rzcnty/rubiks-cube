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
    State new_state;
	const int PATH_COSTS[CITY_NUMBER][ACTIONS_NUMBER] = 
        {   {  0,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 140, 118,  -1,  -1,  75},  // Arad
            { -1,   0,  -1,  -1,  -1, 211,  90,  -1,  -1,  -1,  -1,  -1,  -1, 101,  -1,  -1,  -1,  85,  -1,  -1},  // Bucharest
			{ -1,  -1,   0, 120,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 138, 146,  -1,  -1,  -1,  -1,  -1},  // Craiova
			{ -1,  -1, 120,   0,  -1,  -1,  -1,  -1,  -1,  -1,  75,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1},  // Drobeta
			{ -1,  -1,  -1,  -1,   0,  -1,  -1,  86,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1},  // Eforie
			{ -1, 211,  -1,  -1,  -1,   0,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  99,  -1,  -1,  -1,  -1},  // F 
			{ -1,  90,  -1,  -1,  -1,  -1,   0,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1},  // G
			{ -1,  -1,  -1,  -1,  86,  -1,  -1,   0,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  98,  -1,  -1},  // H
			{ -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,   0,  -1,  -1,  87,  -1,  -1,  -1,  -1,  -1,  -1,  92,  -1},  // I
			{ -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,   0,  70,  -1,  -1,  -1,  -1,  -1, 111,  -1,  -1,  -1},  // L 
			{ -1,  -1,  -1,  75,  -1,  -1,  -1,  -1,  -1,  70,   0,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1},  // M
			{ -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  87,  -1,  -1,   0,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1},  // N
			{ -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,   0,  -1,  -1, 151,  -1,  -1,  -1,  71},  // O
			{ -1, 101, 138,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,   0,  97,  -1,  -1,  -1,  -1,  -1},  // P
			{ -1,  -1, 146,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  97,   0,  80,  -1,  -1,  -1,  -1},  // R
			{140,  -1,  -1,  -1,  -1,  99,  -1,  -1,  -1,  -1,  -1,  -1, 151,  -1,  80,   0,  -1,  -1,  -1,  -1},  // S
			{118,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 111,  -1,  -1,  -1,  -1,  -1,  -1,   0,  -1,  -1,  -1},  // T
			{ -1,  85,  -1,  -1,  -1,  -1,  -1,  98,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,   0, 142,  -1},  // U
			{ -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  92,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 142,   0,  -1},  // V
			{ 75,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  71,  -1,  -1,  -1,  -1,  -1,  -1,   0}   // Z
		};
	     //    A    B    C    D    E    F    G    H    I    L    M    N    O    P    R    S    T    U    V    Z       
	 
         if(PATH_COSTS[parent_state->city][action]<=0) 
              return FALSE;
         else{
              new_state.city = action;
              trans_model->new_state = new_state;
              trans_model->step_cost = PATH_COSTS[parent_state->city][action]; 
         }     
         return TRUE;                                               
}

//______________________________________________________________________________
float Compute_Heuristic_Function(const State *const state, const State *const goal)
{
      const float SLD[CITY_NUMBER][CITY_NUMBER] =   // CALCULATED ROUGHLY!!!
        {   {  0, 366, 300, 220, 590, 235, 430, 535, 420, 168, 225, 355, 110, 290, 185, 130, 105, 435, 470,  67},  // Arad
            {366,   0, 160, 242, 161, 176,  77, 151, 226, 244, 241, 234, 380, 100, 193, 253, 329,  80, 199, 374},  // Bucharest
			{300, 160,   0, 102, 325, 210, 142, 325, 368, 145, 110, 388, 355, 133, 138, 190, 220, 220, 385, 330},  // Craiova
			{220, 242, 102,   0, 390, 245, 240, 380, 400, 100,  70, 460, 310, 190, 155, 205, 150, 302, 410, 265},  // Drobeta
			{590, 161, 325, 390,   0, 325, 205,  80, 245, 400, 375, 350, 595, 265, 340, 395, 555, 130, 260, 593},  // Eforie
			{235, 176, 210, 245, 325,   0, 200, 251, 180, 175, 185, 135, 220, 102,  85,  95, 255, 195, 200, 227},  // F 
			{430,  77, 142, 240, 205, 200,   0, 213, 297, 245, 280, 285, 410, 125, 225, 285, 330, 120, 230, 520},  // G
			{535, 151, 325, 380,  80, 251, 213,   0, 205, 370, 370, 260, 535, 220, 345, 365, 495,  92, 130, 535},  // H
			{440, 226, 368, 400, 245, 180, 297, 205,   0, 330, 350,  80, 365, 250, 260, 280, 450, 190,  85, 390},  // I
			{168, 244, 145, 100, 400, 175, 245, 370, 330,   0,  66, 290, 240, 140,  95, 135, 100, 285, 360, 205},  // L 
			{225, 241, 110,  70, 375, 185, 280, 370, 350,  66,   0, 305, 300, 140, 120, 175, 130, 280, 370, 260},  // M
			{355, 234, 388, 460, 350, 135, 285, 260,  80, 290, 305,   0, 273, 220, 260, 250, 330, 235, 155, 310},  // N
			{110, 380, 355, 310, 595, 220, 410, 535, 365, 240, 300, 273,   0, 305, 200, 140, 213, 415, 435,  66},  // O
			{290, 100, 133, 190, 265, 102, 125, 220, 250, 140, 140, 220, 305,   0, 115, 150, 230, 140, 185, 297},  // P
			{185, 193, 138, 155, 340,  85, 225, 345, 260,  95, 120, 260, 200, 115,   0,  75, 150, 230, 290, 193},  // R
			{130, 253, 190, 205, 395,  95, 285, 365, 280, 135, 175, 250, 140, 150,  75,   0, 137, 300, 330, 135},  // S
			{105, 329, 220, 150, 555, 255, 330, 495, 450, 100, 130, 330, 213, 230, 150, 137,   0, 380, 455, 155},  // T
			{435,  80, 220, 302, 130, 195, 120,  92, 190, 285, 280, 235, 415, 140, 230, 300, 380,   0, 132, 425},  // U
			{470, 199, 385, 410, 260, 200, 230, 130,  85, 360, 370, 155, 435, 185, 290, 330, 455, 132,   0, 452},  // V
			{ 67, 374, 330, 265, 593, 227, 520, 535, 390, 205, 260, 310,  66, 297, 193, 135, 155, 425, 452,   0}   // Z
		};
	     //    A    B    C    D    E    F    G    H    I    L    M    N    O    P    R    S    T    U    V    Z   
         
        return SLD[state->city][goal->city];   
}

//_______________ Update if your goal state is not determined initially ___________________________________
int Goal_Test(const State *const state, const State *const goal_state)
{
	if(PREDETERMINED_GOAL_STATE)	
		return Compare_States(state, goal_state); 
	else
		return 1;
}

// ==================== WRITE YOUR OPTIONAL FUNCTIONS (IF REQUIRED) ==========================
