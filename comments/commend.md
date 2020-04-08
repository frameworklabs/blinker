Your demo is perfectly fine.

2 things to mention.

1. I like to seperate concerns in separate activities in order reduced the indentation level and to simplify testing of different concerns.

2. There is an additional way to access the environment via external memory or external functions. This allows to encapsulate environment where it is needed and reduces the amount of parameters to be handed down form the entrypoint activity to the various subactivities.

I showed both aspects in my [fork of your repository in branch comments](https://github.com/schorg/blinker/tree/comments).

I created a test program, that allows to interactively test the blinker lever.

