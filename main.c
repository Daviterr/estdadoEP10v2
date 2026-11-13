#include "team.h"
#include "teamlist.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    TeamList *tl = tl_create();
    if (tl == NULL) {
        return 1;
    }

    FILE *fp = fopen("teams.csv", "r");
    if (fp == NULL) {
        perror("Erro ao abrir teams.csv");
        tl_free(tl);
        return 1;
    }

    char line[256];
    int id;
    char name[128];

    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\r\n")] = '\0';
        if (sscanf(line, "%d,%127[^\n]", &id, name) == 2) {
            Team *t = team_create(id, name);
            if (t != NULL) {
                tl_append(tl, t);
            }
        }
    }
    fclose(fp);

    printf("%-4s %-22s %3s %3s %3s %3s %3s %4s %4s\n",
           "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");

    int n = tl_size(tl);
    for (int i = 0; i < n; i++) {
        Team *t = tl_get(tl, i);
        int wins = team_wins(t);
        int draws = team_draws(t);
        int losses = team_losses(t);
        int gs = team_goals_scored(t);
        int gc = team_goals_conceded(t);
        int gd = gs - gc;
        int pts = 3 * wins + draws;

        printf("%-4d %-22s %3d %3d %3d %3d %3d %4d %4d\n",
               team_id(t), team_name(t), wins, draws, losses, gs, gc, gd, pts);
    }

    tl_free(tl);
    return 0;
}
