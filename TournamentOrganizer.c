#include <stdio.h>
#include <string.h>

#define MAX_PLAYERS 16
#define NAME_LEN 50

void printRound(char players[][NAME_LEN], int count) {
    printf("\n--- Round with %d players ---\n", count);
    for (int i = 0; i < count; i += 2) {
        printf("Match %d: %s vs %s\n", (i/2) + 1, players[i], players[i+1]);
    }
}

int main() {
    int n;
    char players[MAX_PLAYERS][NAME_LEN];
    char winners[MAX_PLAYERS][NAME_LEN];

    printf("Enter number of players (must be a power of 2, max %d): ", MAX_PLAYERS);
    scanf("%d", &n);
    getchar(); // clear newline

    if (n < 2 || n > MAX_PLAYERS || (n & (n - 1)) != 0) {
        printf("Invalid number of players! Must be a power of 2.\n");
        return 1;
    }

    printf("\nEnter player names:\n");
    for (int i = 0; i < n; i++) {
        printf("Player %d: ", i + 1);
        fgets(players[i], NAME_LEN, stdin);
        players[i][strcspn(players[i], "\n")] = 0; // remove newline
    }

    int round = 1;
    while (n > 1) {
        printf("\n===== Round %d =====\n", round);
        printRound(players, n);

        int winCount = 0;
        for (int i = 0; i < n; i += 2) {
            int choice;
            printf("Winner of match %d (1 for %s, 2 for %s): ", 
                   (i/2)+1, players[i], players[i+1]);
            scanf("%d", &choice);
            getchar();
            if (choice == 1)
                strcpy(winners[winCount], players[i]);
            else
                strcpy(winners[winCount], players[i+1]);
            winCount++;
        }

        memcpy(players, winners, sizeof(winners));
        n = winCount;
        round++;
    }

    printf("\n🏆 The Champion is: %s 🏆\n", players[0]);

    return 0;
}
