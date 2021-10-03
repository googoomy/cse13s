#include "names.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN_PLAYERS 2
#define MAX_PLAYERS 10
#define MAX_POINTS  100
#define SEED        2021

int main(void) {
    typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;
    const Position pig[7] = { SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER };
    //Ask the user for how many players in the game. If the number is not allowed the default number of players is 2
    int num_Players = 0;
    printf("How many players? ");
    scanf("%d", &num_Players);
    if (num_Players < MIN_PLAYERS || num_Players > MAX_PLAYERS) {
        num_Players = MIN_PLAYERS;
        fprintf(stderr, "Invalid number of players. Using %d instead.\n", num_Players);
    }
    //Ask the user the seed the game will be played under. If the number is a negative integer the default seed is 2021
    int user_Seed = 0;
    printf("Random seed: ");
    scanf("%d", &user_Seed);
    if (user_Seed < 0) {
        user_Seed = SEED;
        fprintf(stderr, "Invalid random seed. Using %d instead.\n", user_Seed);
    }
    //This is where the main implementation of the game is
    //points are stored in an array so the players' scores are mapped to the same position in both arrays
    int points[MAX_PLAYERS] = { 0 };
    srandom(user_Seed);
    int current_Player = 0; //this variable keeps track of the current player
    int last_Player; //this variable keeps track of the last player so the rolls the pig line doesn't repeat every loop
    //the game ends when a player reaches 100 points or more
    while (points[current_Player] < MAX_POINTS) {
        Position roll;
        roll = pig[random() % 7];
        if (last_Player != current_Player) {
            printf("%s rolls the pig...", names[current_Player]);
        }
        last_Player = current_Player;
        switch (roll) {
        //if the player rolls SIDE the turn is passed over to the next player
        case SIDE:
            printf(" pig lands on side");
            current_Player += 1;
            //if the last player rolls side the next player will be the first player. It loops around.
            if (current_Player > num_Players - 1) {
                current_Player = 0;
            }
            printf("\n");
            break;
        //if the player rolls RAZORBACK they gain 10 points
        case RAZORBACK:
            printf(" pig lands on back");
            points[current_Player] += 10;
            break;
        //if the player rolls TROTTER they gain 10 points
        case TROTTER:
            printf(" pig lands upright");
            points[current_Player] += 10;
            break;
        //if the player rolls SNOUTER they gain 15 points
        case SNOUTER:
            printf(" pig lands on snout");
            points[current_Player] += 15;
            break;
        //if the player rolls JOWLER they gain 5 points
        case JOWLER:
            printf(" pig lands on ear");
            points[current_Player] += 5;
            break;
        default: break;
        }
    }
    //print who won the game
    printf("\n%s wins with %d points!\n", names[current_Player], points[current_Player]);
}
