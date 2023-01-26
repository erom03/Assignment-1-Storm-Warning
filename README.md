# Storm Warning
## Objective
Give practice with dynamic memory in C.

## Story
Everyone knows that the world is not spherical. Some people know that the world is not flat either. The
world is actually a torus (donut shaped).

Our ship captains imagine the world as a flat 2D grid, where moving
off the top of the 2D grid results in reappearing at the bottom of the
grid, and moving off the bottom similarly results in reappearing at the
top of the grid. Both reappearances will result in having the same x
position. Additionally moving off the left or right side causes a
reappearance on the right or left side respectively, at the same y
position.

Your fleet continues to expand so you will need to keep track of ships
that join your fleet. Each ship that joins will start at some particular x,
y coordinate on the 2D grid and will then proceed to move at a constant speed of 1 unit per minute in a
fixed direction: either Left (negative x), Right (positive x), Up (positive y), or Down (negative y).

What’s worse is that at various points in time a small storm will appear and disrupt your ships. Luckily
you can determine in advance where storms will appear, your objective is to send your warning to the
exact ships that will be affected.

## Problem
Given a growing list of ships on a toroidal grid over time, and locations of storms, determine which ships
will need to be warned.

## (STANDARD) Input
Input will begin with a line containing 2 integers, W and H, (20 ≤ W, H ≤ 500,000), representing the
height and width of the grid respectively.  Initially you are tracking no boats.

Following this line will be a list of commands. The commands must be processed in the order they are
given.  Each command begins with a number and can be 1 of 4 types.  The types are listed below,
* 1 x y d n
  - This command informs us that a new ship is added to the fleet. The ship starts at location
    (x, y) (1 ≤ x ≤ W; 1 ≤ y ≤ H). The value d will be a single letter, either ‘L’, ‘R’,
    ‘D’, or ‘U’ (quotes for clarity) representing the direction the new ship travels in (Left,
    Right, Down, or Up respectively). The name of the ship is denoted by the string n. The
    string n will contain at least 1 and at most 20 characters. All characters in n will be
    either upper or lower case letters.  No 2 ships will have the same name.
* 2 t
  - This command informs us that time is passing by the amount of t minutes. All the ships
    will move t (1 ≤ t ≤ 525,600) units in their respective direction. Note that trying to
    update all the ships at this time will be prohibitively expensive timewise in some cases.
    The sum of the times across the whole program will be less than or equal to 1 billion
    (10<sup>9</sup>).
* 3 x y w h
  - This command informs us that a storm will appear. The “bottom left” cell affected by the
    storm will be at location (x, y) (1 ≤ x ≤ W; 1 ≤ y ≤ H), and the storm will be w units
    wide (across the x) and h units high (across the y) (1 ≤ w ≤ 10; 1 ≤ h ≤ 10). Note a ship
    location (x + w, y) will NOT be affected by the storm. Additionally, storms can also
    wrap around 2D grid.
* 4
  - This command requests that the program ends (I hope the company is still in business).

## (STANDARD) Output
For each 3 command (storm notification) you will need to first print on a line by itself a non-negative
integer (n), representing the number of boats currently in the storm. The following n lines should each
contain a name of one of the ships affected by the storm.
