// Name: Sean Perez
// CS 344: HW 1
// Date: 1/13/22
// Source: Sample code provided for hw 1 - additional sources commented in the code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------------------------------------------------------------------------------------------------------------------------- -

// Citation for the following function(s): struct movie, struct movie* createMovie, struct movie *processFile, 
// and all the print functions
// Date: 1/16/2022
// Copied from /OR/ Adapted from /OR/ Base on:
// https://www.geeksforgeeks.org/basics-file-handling-c/
// https://www.geeksforgeeks.org/size_t-data-type-c-language/
// https://jameshfisher.com/2017/02/22/ssize_t/
// https://www.programiz.com/c-programming/c-dynamic-memory-allocation
// https://stackoverflow.com/questions/25489260/copying-integer-to-integer-with-allocated-memory
// https://www.tutorialspoint.com/c_standard_library/c_function_strtod.htm

/* Struct for movie information */
struct movie
{
    char* title;
    int year;
    char* language;
    double rating;
    struct movie* next;
};

/* Parse the current line which is space delimited and create a
*  movies struct with the data in this line
*/
struct movie* createMovie(char* currLine)
{
    // For use with strtok_r
    char* saveptr;
    struct movie* currMovie = malloc(sizeof(struct movie));

    // The first token is the title
    char* token = strtok_r(currLine, ",", &saveptr);
    currMovie->title = (char*)calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->title, token);

    // The next token is the year

    token = strtok_r(NULL, ",", &saveptr);
    int stringYear = atoi(token);
    currMovie->year = stringYear;
    
    // The next token is the language
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->language = (char*)calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->language, token);

    // The last token is the rating
    token = strtok_r(NULL, "\n", &saveptr);
    double stringRating;
    char* ptrRate;
    stringRating = strtod(token, &ptrRate);
    currMovie->rating = stringRating;
    
    // Set the next node to NULL in the newly created movie entry
    currMovie->next = NULL;

    return currMovie;
}

/*
* Return a linked list of movies by parsing data from
* each line of the specified file.
*/
struct movie *processFile(char* filePath)
{
    // Open the specified file for reading only
    FILE *csvFile = fopen(filePath, "r");

    char* currLine = NULL;
    size_t len = 0;
    ssize_t nread;
    int initCounter = 0;

    // The head of the linked list
    struct movie* head = NULL;
    // The tail of the linked list
    struct movie* tail = NULL;

    // Read the file line by line
    while ((nread = getline(&currLine, &len, csvFile)) != -1)
    {
        // Prevents first line (column titles) from being saved
        if (initCounter == 0) {
            initCounter++;
            continue;
        }

        // Get a new movie node corresponding to the current line
        struct movie* newNode = createMovie(currLine);

        // Is this the first node in the linked list?
        if (head == NULL)
        {
            // This is the first node in the linked link
            // Set the head and the tail to this node
            head = newNode;
            tail = newNode;
        }
        else
        {
            // This is not the first node.
            // Add this node to the list and advance the tail
            tail->next = newNode;
            tail = newNode;
        }
    }
    free(currLine);
    fclose(csvFile);
    return head;
}

/*
* Print data for the given movie
*/
void printMovieByLanguage(struct movie* movieNode) {
    printf("%d %s\n",
        movieNode->year,
        movieNode->title
    );
}

/*
* Print title for the given movie
*/
void printTitle(struct movie* movieNode) {
    printf("%s\n", movieNode->title);
}

/*
* Print the linked list of movies
*/
void printMovieRating(struct movie* movieNode)
{
    printf("%d %.1f %s\n",
        movieNode->year,
        movieNode->rating,
        movieNode->title
    );
}

// -------------------------------------------------------------------------------------------------------------------------------- -

// Citation for the following function(s): countMovieList, moviesByYears
// Date: 1/16/2022
// Copied from /OR/ Adapted from /OR/ Base on:
// OSU CS 344 Explorations Week 2

/*
* Counts number of nodes (movies) created
*/
int countMovieList(struct movie* movieNode)
{
    struct movie* tempHead = movieNode;
    int counter = 0;

    if (tempHead == NULL)
    {
        printf("No values");
        return 0;
    }

    while (tempHead != NULL)
    {
        counter++;
        tempHead = tempHead->next;
    }

    return counter;
}

/*
* Returns movies in a given year
*/
int moviesByYears(struct movie* movieNode, int *yearValue)
{
    struct movie* tempHead = movieNode;
    
    int counter = 0;

    if (tempHead == NULL)
    {
        printf("No values");
        return 0;
    }

    while (tempHead != NULL)
    {
        if (*yearValue == (tempHead->year))
        {
            printTitle(tempHead);
            counter++;
            tempHead = (tempHead->next);
        }
        else
        {
            tempHead = (tempHead->next);
        }

    }

    if (counter == 0)
    {
        printf("No data about movies released in the year %d \n", *yearValue);
    }

    return 0;
}


// -------------------------------------------------------------------------------------------------------------------------------- -

// Citation for the following function(s): ratingByYear and  highestRatings
// Date: 1/17/2022
// Copied from /OR/ Adapted from /OR/ Base on:
// https://stackoverflow.com/questions/2589749/how-to-initialize-array-to-0-in-c/2589751
// https://www.tutorialspoint.com/cprogramming/c_arrays.htm
// https://www.geeksforgeeks.org/memset-c-example/
// https://beginnersbook.com/2014/01/c-passing-array-to-function-example/
// https://stackoverflow.com/questions/2589749/how-to-initialize-array-to-0-in-c/2589751


/*
* Receives year, finds highest rated movie and calls print funct
*/ 
int ratingByYear(struct movie* movieNode, int *yearSearched)
{
    struct movie* tempHead = movieNode;
    struct movie* max = NULL;

    // Loop Through the array
    while (tempHead != NULL)
    {   
        // If current Node year is same as year being searched from array memory of all the years
        if (tempHead->year == *yearSearched)
        {
            // Sets max Node and continues the loop
            if (max == NULL)
            {
                max = tempHead;
                continue;
            }

            // Compares rating values and updates if current node is higher than "max"
            if (max->rating < tempHead->rating)
            {
                max = tempHead;
            }
        }
        // Move to next Node
        tempHead = tempHead->next;
    }
    printMovieRating(max);

    return 0;
}


/*
* Returns highest rated movies by year
*/ 
int highestRatings(struct movie* movieNode, int *total)
{
    struct movie* tempHead = movieNode;
    int yearsCompleted[*total];
    memset(yearsCompleted, 0, *total * sizeof(int));

    // While loop sends year to function
    if (tempHead == NULL)
    {
        printf("No values");
        return 0;
    }

    // Keeps track of current movie year that is being checked against
    int tempYear;

    // Goes through the linked list, updating the tempYear and passing to for loop
    while (tempHead != NULL)
    {
        tempYear = tempHead->year; 
        
        for (int i=0; i < *total ; i++)
        {
            // Breaks loop if year is already found in the array memory
            if (yearsCompleted[i] == tempYear)
            {
                break;
            }

            if (yearsCompleted[i] == 0)
            {
                // Update array memory to value of tempYear
                yearsCompleted[i] = tempYear;
                break;
            }
        }
        // Move to next Node
        tempHead = tempHead->next;
    }

    // Call function to find highest rated by year using filled array.
    for (int j = 0; j < *total; j++)
    {
        // If it reaches a point where the value is 0, it will end the loop and then the function
        if (yearsCompleted[j] == 0)
        {
            break;
        }
        ratingByYear(movieNode, &yearsCompleted[j]);
    }

    return 0;
}

// ---------------------------------------------------------------------------------------------------------------------------------
// Citation for the following function(s): tokenLanguage and moviesByLanguage
// Date: 1/16/2022
// Copied from /OR/ Adapted from /OR/ Base on:
// https://stackoverflow.com/questions/43585922/malloc-memory-corruption
// OSU CS 344 Explorations Week 2
// https://stackoverflow.com/questions/23456374/why-do-we-use-null-in-strtok
// https://www.geeksforgeeks.org/core-dump-segmentation-fault-c-cpp/
// Domenic Hanson: https://edstem.org/us/courses/16718/discussion/1005925
// Artem Kuryachy: https://edstem.org/us/courses/16718/discussion/992386


/*
* Returns int value of strncmp, calls printMovieByLanguage() if logic allows
*/
int tokenLanguage(struct movie* movieNode, char* languageValue)
{
    // For use with strtok_r
    struct movie* tempHead = movieNode;
    char* saveptr;
    int valueReturned;

    // Sets up a dynamic mem string and copies the value of the pointer at language
    char* newString = (char*)calloc( strlen(movieNode->language) + 1, sizeof(char));
    strcpy(newString, tempHead->language);
     
    // Initiates the toekn and starts the pointer
    char* token = strtok_r(newString, "[;", &saveptr);

    // Compares token up to length of provided language string
    valueReturned = (strncmp(languageValue, token, strlen(languageValue)));
    if (valueReturned == 0)
    {
        printMovieByLanguage(tempHead);
        return valueReturned;
    }

    // Will run until token is null
    while (1)
    {
        token = strtok_r(NULL, ";", &saveptr);
        if (token == NULL)
        {
            // free(newString);
            return valueReturned;
        }

        // Compares token up to length of provided language string
        valueReturned = (strncmp(languageValue, token, strlen(languageValue)));
        if (valueReturned == 0)
        {
            printMovieByLanguage(tempHead);
            break;
        }
    } 
    
    return valueReturned; 
}

/*
* Returns a list of all movies by given languague; calls tokenLanguage()
*/
int moviesByLanguage(struct movie* movieNode, char *languageValue)
{
    struct movie* tempHead = movieNode;
    int counter = 0;

    if (tempHead == NULL)
    {
        printf("No values");
        return 0;
    }

    while (tempHead != NULL)
    {
        // Calls tokenLanguage, which compares the string value
        int langVer = tokenLanguage(tempHead, languageValue);
        if (langVer == 0)
        {
            counter++;
        }
      
        // Move on to the next node
        tempHead = tempHead->next;
    }

    // If movies were with with provided language, prints below.
    if (counter == 0)
    {
        print("\n")
        printf("No data about movies released in %s \n", languageValue);
    }

    return 0;
}

// -------------------------------------------------------------------------------------------------------------------------------- -

// Citation for the following function(s): main
// Date: 1/16/2022
// Copied from /OR/ Adapted from /OR/ Base on:
// https://stackoverflow.com/questions/43585922/malloc-memory-corruption
// OSU CS 344 Explorations Week 2
// https://stackoverflow.com/questions/1863094/pass-strings-by-reference-in-c
// https://stackoverflow.com/questions/5189461/passing-an-array-of-strings-to-a-c-function-by-reference
// Jonathan Nichols: https://edstem.org/us/courses/16718/discussion/984861


/*
* Main func provides menu for user and takes input. Uses input to pass relevant values to relevant functions
*/
int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movie_info1.txt\n");
        return EXIT_FAILURE;
    }
    struct movie* movies = processFile(argv[1]);
    int total;
    struct movie* tempHead = movies;
    total = countMovieList(tempHead);

    printf("\n");
    printf("Processed file %s and parsed data for %d movies \n", argv[1], total);

    int userInput;
    int yearValue;
    char languageValue[20]; 

    while (1)
    {
        //print the menu choices
        printf("\n");
        printf("1. Show movies released in the specified year\n");
        printf("2. Show highest rated movie for each year\n");
        printf("3. Show the title and year of release of all movies in a specific language\n");
        printf("4. Exit from the program\n");
        printf("\n");
        printf("Enter a choice from 1 to 4: ");

        //get user input
        scanf("%d", &userInput);

        //check if input correct
        if (userInput < 1 || userInput >4)
        {
            printf("You entered an incorrect choice. Try again.\n");
        }

        //switch for different prompts and functions to be activated.
        switch (userInput)
        {
            //1. Show movies released in the specified year
        case 1:
            printf("Enter the year for which you want to see movies: ");
            scanf("%d", &yearValue);
            moviesByYears(tempHead, &yearValue);
            break;

            //2. Show highest rated movie for each year
        case 2:
            highestRatings(tempHead, &total);
            break;
            //3. Show the title and year of release of all movies in a specific language
        case 3:
            printf("Enter the language for which you want to see movies: ");
            scanf("%s", languageValue); 
            moviesByLanguage(tempHead, languageValue);
            break;

            //4. Exit from the program
        case 4:
            // Free up all memory!
            free(movies);
            exit(0);
            break;
        }
    }
    return 0;
}