#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <libmormegil/dice.h>

uint32_t keybuf[8];
uint32_t nonce[2];

int main()
{
    int fd;
    fd = open("/dev/urandom", O_RDONLY, 0);
    if (fd < 0)
    {
        perror("S20prng-test: can't open /dev/urandom");
        return 1;
    }

    int i = 0;
    int testroll;
    uint64_t counter = 0;
    int rolls[11];

    read(fd, keybuf, sizeof keybuf);
    read(fd, nonce, sizeof nonce);
    dice_setstate(keybuf, nonce, &counter, &i);
    for (i = 0; i < 11; ++i)
    {
        rolls[i] = 0;
    }
    for (i = 0; i < 1000000; ++i)
    {
        testroll = dice(2, 6);
        if ((testroll < 2) || (testroll > 12))
        {
            fprintf(stderr, "S20prng-test: FAIL: 2d6 roll came up %d\n", testroll);
            return 2;
        }
        rolls[testroll - 2]++;
    }
    for (i = 0; i < 11; ++i)
    {
        printf("%d: %d times\n", i + 2, rolls[i]);
    }
    return 0;
}

