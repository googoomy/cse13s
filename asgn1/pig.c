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

    int num_Players = 0;
    printf("How many players? ");
    scanf("%d", &num_Players);
    if (num_Players < MIN_PLAYERS || num_Players > MAX_PLAYERS) {
        num_Players = MIN_PLAYERS;
        fprintf(stderr, "Invalid number of players. Using %d instead.\n", num_Players);
    }

    int user_Seed = 0;
    printf("Random seed: ");
    scanf("%d", &user_Seed);
    if (user_Seed < 0) {
        user_Seed = SEED;
        fprintf(stderr, "Invalid random seed. Using %d instead.\n", user_Seed);
    }

    int points[MAX_PLAYERS] = { 0 };
    srandom(user_Seed);
    int current_Player = 0;
    int last_Player;
    while (points[current_Player] < MAX_POINTS) {
        Position roll;
        roll = pig[random() % 7];
        if (last_Player != current_Player) {
            printf("%s rolls the pig...", names[current_Player]);
        }
        last_Player = current_Player;
        switch (roll) {
        case SIDE:
            printf(" pig lands on side");
            current_Player += 1;
            if (current_Player > num_Players - 1) {
                current_Player = 0;
            }
            printf("\n");
            break;
        case RAZORBACK:
            printf(" pig lands on back");
            points[current_Player] += 10;
            //last_Player = current_Player;
            break;
        case TROTTER:
            printf(" pig lands upright");
            points[current_Player] += 10;
            //last_Player = current_Player;
            break;
        case SNOUTER:
            printf(" pig lands on snout");
            points[current_Player] += 15;
            //last_Player = current_Player;
            break;
        case JOWLER:
            printf(" pig lands on ear");
            points[current_Player] += 5;
            //last_Player = current_Player;
            break;
        default: break;
        }
    }
    printf("\n%s wins with %d points!\n", names[current_Player], points[current_Player]);
}
