#ifndef AALTO_GAMEOFLIFE_H
#define AALTO_GAMEOFLIFE_H

typedef enum {
    DEAD,
    ALIVE
} Status;

typedef struct {
    unsigned int xsize, ysize;
    Status **cells;
} Area;

Area *createArea(unsigned int xsize, unsigned int ysize);

void releaseArea(Area *a);

void initArea(Area *a, unsigned int n);

void printArea(const Area *a);

void tick(Area *a);

#endif  /* AALTO_GAMEOFLIFE_H */
