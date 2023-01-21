#include <stdio.h>
#include <stdlib.h>

#define NAME_LEN 20

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
    // gather width and height from user
    int width;
    int height;

    scanf("%d", &width);
    scanf("%d", &height);
    
    // Initialize array of array list
    struct ArrayList ** lists = (struct ArrayList **)malloc(width * sizeof(struct ArrayList *));
    
    for(int i = 0; i < width; ++i) {
        lists[i] = (struct ArrayList *)malloc(height * sizeof(struct ArrayList));
    }

    // Initialize time
    int currTime = 0;
    int newTime;
    int currCommand;

    scanf("%d", &currCommand);

    while(currCommand != 4) {
        switch (currCommand) {
            case 1:
                // ADD command
                break;
            case 2:
                // TIME command
                break;
            case 3:
                // STORM command
                break;
            case 4:
                // Exit
                break;
            default:
                printf("Something went wrong, pick a valid command\n");
        }

        scanf("%d", &currCommand);
    }

    free(lists);

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
    // TODO: left off here
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