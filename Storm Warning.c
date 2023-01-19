#include <stdio.h>

// Test 3

typedef struct Boat Boat;
typedef struct ArrayList ArrayList;

struct Boat {
    int start_x, start_y, delta_x, delta_y, start_time;
    char name[NAME_LEN + 1];
};

struct ArrayList {
    struct Cage * cages;
    int numCages;
};

// Given a point to a list initialize the list
void initArrayList(ArrayList * list);

// Given a list and a boat tot add to it, add the boat to the end
// of the list
// Expand the list if necessary
void appendToList(ArrayList * list, Boat newBoat);

// Given
// * the x and y location of a storm,
// * the dimensions of the storm,
// * the dimensions of the world,
// * the list of ships under consideration,
// * the time change since the beginning of the program,
// * and a flag whether boats should be printed or not
// Return the number of boats in the storm and the list
// Print the names of the boats if the should_print flag is non-zero
int query(int x, int y, int storm_width, int storm_height, int world_width, int world_height, ArrayList * list, int cur_time, int should_print);

// The main function
int main() {
    

    return 0;
}

// appendToList() comments
    // Check if the list is full
        // Expand the list
    // Add the boat to the end of the list
    // Update the list’s size

// query() comments
    // Create and initialize the answer
    // Loop through all the boats in the list
        // Get the current boat
        // Get the current location of the boat (based on time)
        // Find the offset of the boat from the storm
        // Wrap the offsets around the world if necessary (modulo)
        // Check if the boat is in the storm by using the offset

// main() comments
    // Read the size of the world
    // Create the array of array lists for x and y world segments
    // Loop through and initialize all the array lists from the two arrays
    // Initialize the current time
    // Read the first command
    // Loop until the exit command is given
        // Determine the command type
            // ADD COMMAND
            // Create a static boat
            // Read in the boat values (be careful with the direction)
            // Convert the x and y to zero indexed values
            // Initialize the delta x and y based on the direction
            // Initialize the time the boat arrived
            // Check if boat is Left/Right VS Up/Down
                // Add boat to the x’s
            // Else
                // Add boat to the y’s
            // TIME COMMAND
                // Update the current time
            // STORM COMMAND
            // Read in the storm information
            // Convert the x and y to zero indexed values
            // Loop through and determine how many ships will be affected
                // Update total by querying this particular row list
                // Update total by querying this particular column list
            // Print the total number of affected ships
            // Loop through and print affected ships
                // Print the by querying this particular row list
                // Print the by querying this particular column list
        // Read in the next command
    // Clean up memory
    // Exit successfully