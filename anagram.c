#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * A digest function for anagram letter counts
 * Uses 26*2 bits of a 64 bit long for a 2 bit state count of each letter in 'a'-'z'
 *
 *   z  y  x ... a
 *  00 00 00 ... 00  => long  (52 bits of the 64 used)
 *        
 * Walks the characters of a lower case string and changes 2 bits of
 * the digest to an observed count for that character (up to 3)
 */
long
digest(char *word) {
    static unsigned char table[] = { 1, 3, 1, 0, 0, 0, 0, 0 };
    long d = 0;

    for (char *p = word; *p; p++) {
        // a-z converted to 0-25, multiplied by 2
        // This is the 2-bit posititon representing the letter count.
        // Counts only go up to 3, the 4th state represents "empty / not seen"
        //   00 - empty (never observed)
        //   01 - seen once
        //   10 - seen twice
        //   11 - seen three
        int shift = (*p - 'a') << 1;

        // grab the value from the 2 bits representing the current state (count).
        int state = (d >> shift) & 3;

        // add 1 to the state with an XOR from the lookup table
        //  00 ^ table[0] == 1
        //  01 ^ table[1] == 2
        //  10 ^ table[2] == 3
        //  11 ^ table[3] == 3
        int nextState = table[state] ^ state;

        // mask to clear the 2 bits in "digest" representing the current state
        //long unsigned mask = 0xffffffffffffffff ^ 3 << shift;
        long unsigned mask = ~0 ^ 3 << shift;

        // replace the 2 bits in "digest" with the new state
        // d = (d &  (~0 ^ 3 << shift))  |  (table[(d >> shift) & 3] ^ ((d >> shift) & 3)) << shift;
        d = (d & mask) | (nextState << shift);
    }
    return d;
}


int
main(int argc, char *argv[]) {
    char word[64];
    FILE *fp;

    if (sizeof(long) != 8) {
        fprintf(stderr, "Usage: %s sorry, need an 8 byte long for this digest\n", *argv);
        exit(0);
    }

    if (argc != 2) {
        fprintf(stderr, "Usage: %s wordfile\n", *argv);
        exit(0);
    }

    if (!(fp = fopen(*++argv, "r"))) {
        fprintf(stderr, "Can't read file \"%s\"\n", *argv);
        exit(0);
    }

    while (fgets(word, sizeof word, fp)) {
        word[strlen(word) -1] = '\0';
        printf("digest: %ld for [%s]\n", digest(word), word);
    }
}
