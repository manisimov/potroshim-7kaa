#include "rand.h"

#define MULTIPLIER 0x015a4e35L
#define INCREMENT  1
#define RANDOM_MAX 0x7FFFU

Rand::Rand()
{
    random_seed = 1;
}

int Rand::get_rand()
{
    random_seed = MULTIPLIER * random_seed + INCREMENT;

    return ((random_seed >> 16) & RANDOM_MAX);
}
