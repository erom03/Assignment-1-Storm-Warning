#include <stdio.h>
#include <stdlib.h>

#define NAME_LEN 20
#define DEFAULT_CAPACITY 5

typedef struct Boat Boat;
typedef struct ArrayList ArrayList;

struct Boat {
    int start_x, start_y, delta_x, delta_y, start_time;
    char name[NAME_LEN + 1];
};

struct ArrayList {
    Boat * array;
    int size, capacity;
};

// Prototypes
ArrayList * initArrayList();
void appendToList(ArrayList * list, Boat newBoat);
int query(int x, int y, int storm_width, int storm_height, int world_width, int world_height, ArrayList * list, int cur_time, int should_print);
void freeMemory(ArrayList * list);

// The main function
int main() {
    // gather width and height from user
    int width;
    int height;

    scanf("%d", &width);
    scanf("%d", &height);
    
    // Initialize array of array list
    ArrayList * columns = initArrayList();
    ArrayList * rows = initArrayList();

    // Initialize time
    int currTime = 0;
    int newTime;
    int currCommand;

    scanf("%d", &currCommand);

    while(currCommand != 4) {
        // I tried using a switch here but it didn't like me
        // declaring a new struct in it so if statements it is

        //ADD COMMAND
        if(currCommand == 1) {
            // Create a static boat and read in values
            Boat newBoat;
            char direction;

            scanf("%d", &newBoat.start_x);
            scanf("%d", &newBoat.start_y);
            getchar();
            scanf("%c", &direction);
            scanf("%s", newBoat.name);

            // Zero index my values
            newBoat.start_x -= 1;
            newBoat.start_y -= 1;

            // Set start time
            newBoat.start_time = currTime;

            // Check direction the ships move and assign
            // its change in x and y accordingly
            // then append the new boat to the list
            switch (direction) {
                case 'L':
                    newBoat.delta_x = -1;
                    newBoat.delta_y = 0;

                    appendToList(rows, newBoat);
                    break;
                case 'R':
                    newBoat.delta_x = 1;
                    newBoat.delta_y = 0;

                    appendToList(rows, newBoat);
                    break;
                case 'D':
                    newBoat.delta_x = 0;
                    newBoat.delta_y = -1;

                    appendToList(columns, newBoat);
                    break;
                case 'U':
                    newBoat.delta_x = 0;
                    newBoat.delta_y = 1;

                    appendToList(columns, newBoat);
                    break;
            }
        }

        // TIME COMMAND
        if(currCommand == 2) {
            int addTime;
            
            // get time to be added from user
            scanf("%d", &addTime);
            currTime += addTime;
        }

        // STORM COMMAND
        if(currCommand == 3) {
            // read in storm values
            int stormX;
            int stormY;
            int stormWidth;
            int stormHeight;

            scanf("%d", &stormX);
            scanf("%d", &stormY);
            scanf("%d", &stormWidth);
            scanf("%d", &stormHeight);

            // zero index the values
            stormX -= 1;
            stormY -= 1;

            int should_print = 0;    // 0 = no, 1 = yes

            // gather how many ships will be affected from query command
            int totalAffected = 0;
            totalAffected += query(stormX, stormY, stormWidth, 
                                    stormHeight, width, 
                                    height, columns, 
                                    currTime, should_print);

            totalAffected += query(stormX, stormY, stormWidth, 
                                    stormHeight, width, 
                                    height, rows, 
                                    currTime, should_print);

            printf("%d\n", totalAffected);

            // set query function to print
            should_print = 1;

            // print affected ships
            query(stormX, stormY, stormWidth, 
                    stormHeight, width, 
                    height, columns, 
                    currTime, should_print);

            query(stormX, stormY, stormWidth, 
                    stormHeight, width, 
                    height, rows, 
                    currTime, should_print);
        }        

        // read next command
        scanf("%d", &currCommand);
    }

    // free memory
    free(columns);
    free(rows);

    return 0;
}

// Given a point to a list initialize the list
ArrayList * initArrayList() {
    ArrayList * list = (ArrayList *)malloc(sizeof(ArrayList));
    
    // set default values for the array list
    list->size = 0;
    list->capacity = DEFAULT_CAPACITY;
    list->array = (Boat *)malloc(sizeof(Boat) * list->capacity);

    return list;
}

// Given a list and a boat to add to it, add the boat to the end
// of the list
// Expand the list if necessary
void appendToList(ArrayList * list, Boat newBoat) {
    // Check if list should be expanded
    if(list->size == list->capacity) {
        list->capacity *= 2;
        list->array = (Boat *)realloc(list->array, list->capacity * sizeof(Boat));
    }

    // Add value to end
    list->array[list->size] = newBoat;
    list->size++;
}

// Given
// * the x and y location of a storm,
// * the dimensions of the storm,
// * the dimensions of the world,
// * the list of ships under consideration,
// * the time change since the beginning of the program,
// * and a flag whether boats should be printed or not
// Return the number of boats in the storm and the list
// Print the names of the boats if the should_print flag is non-zero
int query(int x, int y, int storm_width, int storm_height, int world_width, int world_height, ArrayList * list, int cur_time, int should_print) {
    int affectedShips = 0;          // Tracks affected ships
    int shift, newPos, stormPos;    // Tracks ship and storm positions
    int stormWrap = -1;             // Tracks if storm wraps

    for(int i = 0; i < list->size; i++) {
        if(list->array[i].start_time <= cur_time) {       
            // Row check
            if(list->array[i].delta_x != 0) {
                // Checks the rows of the storm
                for(int j = 0; j < storm_height; j++) {
                    // Check if storm wraps and adjust accordingly
                    stormPos = y + j;
                    if(stormPos >= world_height) {
                        stormPos -= world_height;
                    }

                    // Checks if boat is in same row as array
                    if(list->array[i].start_y == stormPos) {
                        // Get boats current location
                        shift = (cur_time - list->array[i].start_time) * list->array[i].delta_x;
                        newPos = (shift + list->array[i].start_x);
                        
                        // Wrap ship if needed
                        if(newPos > world_width || newPos < 0)
                             newPos %= world_width;

                        // Get storm's furthest position
                        stormPos = x + storm_width - 1;

                        // Check if storm wraps
                        stormWrap = stormPos - world_width;

                        if(stormPos >= world_width) {
                            stormPos = world_width - 1;
                        }

                        // Check if boat is in storm
                        if((newPos >= x && newPos <= stormPos) || newPos <= stormWrap) {
                            affectedShips++;
                            
                            // print ship if needed
                            if(should_print == 1)
                                printf("%s\n", list->array[i].name);

                        }
                    }
                }
            }

            // Column check
            if(list->array[i].delta_y != 0) {
                // Checks the columns of the storm
                for(int j = 0; j < storm_width; j++) {
                    // Check if storm wraps and adjust accordingly
                    stormPos = x + j;
                    if(stormPos >= world_width) {
                        stormPos -= world_width;
                    }

                    // Checks if boat is in same column as array
                    if(list->array[i].start_x == stormPos) {
                        // Get boats current location
                        shift = (cur_time - list->array[i].start_time) * list->array[i].delta_y;
                        newPos = (shift + list->array[i].start_y);
                        
                        // Wrap ship if needed
                        if(newPos > world_height || newPos < 0)
                             newPos %= world_height;

                        // Get storm's furthest position
                        stormPos = y + storm_height - 1;

                        // Check if storm wraps
                        stormWrap = stormPos - world_height;

                        if(stormPos >= world_height) {
                            stormPos = world_height - 1;
                        }

                        // Check if boat is in storm
                        if((newPos >= y && newPos <= stormPos) || newPos <= stormWrap) {
                            affectedShips++;
                            
                            // print ship if needed
                            if(should_print == 1)
                                printf("%s\n", list->array[i].name);

                        }
                    }
                }
            }

        }
    }

    return affectedShips;
}

void freeMemory(ArrayList * list) {
    // first free the memory of the array within the array list
    // then free the list itself
    free(list->array);
    free(list);
}