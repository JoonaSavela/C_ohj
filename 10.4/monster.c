/* monster.c -- Implementation of monster actions
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dungeon.h"

// for defining some monster types below that can be used in the game
typedef struct {
    char name[20];  // Name of monster
    char sign;  // character to show it on map
    unsigned int hplow;  // lowest possible initial maxhp
    unsigned int hphigh;  // highest possible initial maxhp
} MonstType;

// Specifying three monster types to start with.
// Feel free to add more, or change the below
// Note that it is up to you to decide whether to use this array from createMonsters
// you may or may not use it
const MonstType types[] = {
    { "Goblin", 'G', 6, 10},
    { "Rat", 'R', 3, 5},
    { "Dragon", 'D', 15, 20}
};


/* One kind of attack done by monster.
 * The attack function pointer can refer to this.
 * 
 * Parameters:
 * game: the game state
 * monst: The monster performing attack
 */
void attackPunch(Game *game, Creature *monst) {
    printf("%s punches you! ", monst->name);
    int hitprob = 50;
    int maxdam = 4;
    if (rand() % 100 < hitprob) {
        printf("Hit! ");
        int dam = rand() % maxdam + 1;
        printf("Damage: %d ", dam);
        game->hp = game->hp - dam;
        if (game->hp <= 0)
            printf("You died!");
        printf("\n");
    } else {
        printf("Miss!\n");
    }
}


/*
 * Move monster 'monst' towards the player character.
 * See exercise description for more detailed rules.
 */
void moveTowards(Game *game, Creature *monst) {
	int oldx = monst->pos.x;
	int oldy = monst->pos.y;

	int px = game->position.x;
	int py = game->position.y;

	int dx = px - oldx;
	int dy = py - oldy;

	int dist = dx * dx + dy * dy;

	int d[5][2] = {{0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};

	int opt_i = 0;

	for (int i = 0; i < 5; i++) {
		int newx = oldx + d[i][0];
		int newy = oldy + d[i][1];
		dx = px - newx;
		dy = py - newy;
		int new_dist = dx * dx + dy * dy;

		if (new_dist < dist && !isBlocked(game, newx, newy) && !(dx == 0 && dy == 0)) {
			dist = new_dist;
			opt_i = i;
		}
	}

	monst->pos.x = oldx + d[opt_i][0];
	monst->pos.y = oldy + d[opt_i][1];
}

/*
 * Move monster 'monst' away from the player character.
 * See exercise description for more detailed rules.
 */
void moveAway(Game *game, Creature *monst) {
	int oldx = monst->pos.x;
	int oldy = monst->pos.y;

	int px = game->position.x;
	int py = game->position.y;

	int dx = px - oldx;
	int dy = py - oldy;

	int dist = dx * dx + dy * dy;

	int d[5][2] = {{0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};

	int opt_i = 0;

	for (int i = 0; i < 5; i++) {
		int newx = oldx + d[i][0];
		int newy = oldy + d[i][1];
		dx = px - newx;
		dy = py - newy;
		int new_dist = dx * dx + dy * dy;

		if (new_dist > dist && !isBlocked(game, newx, newy) && !(dx == 0 && dy == 0)) {
			dist = new_dist;
			opt_i = i;
		}
	}

	monst->pos.x = oldx + d[opt_i][0];
	monst->pos.y = oldy + d[opt_i][1];
}

/*
 * Take action on each monster (that is alive) in 'monsters' array.
 * Each monster either attacks or moves (or does nothing if no action is specified)
 */
void monsterAction(Game *game) {
	int px = game->position.x;
	int py = game->position.y;
	for (size_t i = 0; i < game->numMonsters; ++i) {
		Creature *m = &game->monsters[i];
		if (m->hp > 0) {
			if ((px - m->pos.x) * (px - m->pos.x) + (py - m->pos.y) * (py - m->pos.y) == 1) {
				if (m->attack != NULL) {
					m->attack(game, m);
				}
			} else {
				if (m->move != NULL) {
					m->move(game, m);
				}
			}
		}
	}
}


/*
 * Create opts.numMonsters monsters and position them on valid position
 * in the the game map. The moster data (hitpoints, name, map sign) should be
 * set appropriately (see exercise instructions) 
 */
void createMonsters(Game *game) {
    game->monsters = malloc(sizeof(Creature) * game->opts.numMonsters);
	game->numMonsters = 0;

	size_t n_types = 3;

	for (size_t i = 0; i < game->opts.numMonsters; i++) {
		size_t type_i = rand() % n_types;
		const MonstType monst = types[type_i];
		strcpy(game->monsters[i].name, monst.name);
		game->monsters[i].sign = monst.sign;
		game->monsters[i].maxhp = (rand() % (monst.hphigh + 1 - monst.hplow)) + monst.hplow;
		game->monsters[i].hp = (float)game->monsters[i].maxhp;
		game->monsters[i].attack = attackPunch;
		game->monsters[i].move = moveTowards;
		int x = rand() % game->opts.mapWidth;
		int y = rand() % game->opts.mapHeight;
		while (isBlocked(game, x, y) || (x == game->position.x && y == game->position.y)) {
			x = rand() % game->opts.mapWidth;
			y = rand() % game->opts.mapHeight;
		}
		game->monsters[i].pos.x = x;
		game->monsters[i].pos.y = y;
		game->numMonsters++;
	}

}

/* Determine whether monster moves towards or away from player character.
 */
void checkIntent(Game *game)
{
    for (unsigned int i = 0; i < game->numMonsters; i++) {
        Creature *m = &game->monsters[i];
        if (m->hp <= 2) {
            m->move = moveAway;
        } else {
            m->move = moveTowards;
        }
        if (m->hp < m->maxhp)
            m->hp = m->hp + 0.1;  // heals a bit every turn
    }
}

