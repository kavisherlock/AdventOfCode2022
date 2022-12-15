What's advent of code without a bit of trial and error, where sometimes your solution only works for the given input (or a very similar one)

That's what I did for this problem. But honestly, when you're given input coordinates that are around 500, that's what you get. To make the cave 2d array, I estimated its size just by looking at the input and seeing what the smallest and largest values I could find. Yes I can do this through code, but effort. Anyway, after making the 2d array, I did exactly what the author did in the problem. I simulated the sand falling down one by one. It was fairly simple to implement

For part 1, I kept the simulation going until the sand reached a point beyond the lowest rock

For part 2, I added the rock layer at the bottom and ran the simulation until the sand stayed at 500,0. I had to play around with the cave widths a bit to make sure the sand didn't hit the cave "walls" (since there are no walls)
