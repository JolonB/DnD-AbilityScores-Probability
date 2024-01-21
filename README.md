# Dungeons and Dragons Ability Scores Probability

When creating a character in D&D, you can roll dice for stats.
[One of the ways to do it](https://en.wikibooks.org/wiki/Dungeons_%26_Dragons/Learning_the_game/Ability_Scores) is to roll 4d6 and discard the lowest scoring dice.
This is repeated for each stat.

I was wondering what sort of scores you can expected to get, particularly how it differs from simply rolling 3d6 and discarding none of them.

The script does just that (and more!).
The results are below.

## Results

These results were calculated over 1 million dice roll combinations.

### 4d6, discarding 1

```
Mean: 12.2445
Median: 12.0000
Mode: 13
```

### 3d6, discarding 0

```
Mean: 10.5001
Median: 11.0000
Mode: 10
```

## Running

If you want to run the code yourself and play around with any different combinations of dice, you can do so by first compiling the code:

```
gcc calculate.c
```

You can run the code with:

```
./a.out
```

If you want to play with different settings, you can also apply some of the command line arguments.
You can see these by running `./a.out -h`.
