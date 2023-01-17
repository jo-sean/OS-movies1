Movies
Name: Sean Perez
Date: 1/13/22


To compile, run: gcc --std=gnu99 -o movies main.c

To open executable, run: ./movies movies_sample_1.csv



Description:

Reads a CSV file with movie data that is provided to the program as an argument
Processes the data in the file to create structs to hold data for each movie
Creates a linked list of all these structs
Gives user choices to ask questions about the movies in the data
Prints out the data about the movies per user choice
Format of the CSV File


Here is a sample file whose format corresponds to the format of the CSV file your program will be tested with.

The first line in the input file will always be the header line containing the column headers (i.e., it will not have data for a movie).
All the other lines will have the data for a movie in valid format and no columns will be missing.
The file will not have any empty lines.
The file will contain data for at least one movie.
Commas appear as delimiters between columns, but will not appear in the values of any columns.
The name of the input file will be less than 50 characters and will not contain any spaces.
This file has the following columns:

Title
This is a string with the movie title. 
E.g., Iron Man 2
You cannot assume a maximum length of the movie title.
Year
This is a 4 digit integer value for the year the movie was released
It's value will be between 1900 and 2021 (inclusive of these years).
E.g., 2010
Languages
The language or languages in which the movie was released.
One or more string values that are always enclosed within []
Multiple values are separated by semi-colons.
E.g,
[English;Portuguese;Spanish]
[English;French]
[English]
You can assume that the maximum number of languages any movie can be released in is 5.
You can assume that the maximum length of a language string is 20 characters.
You cannot assume any particular case for the letters in the language.
E.g., don't assume that the first letter is upper case, or that all letters are lowercase.
Rating Value
A number between 1 and 10 (inclusive of both 1 and 10)
It can be an integer or a double with one digit after the decimal point
E.g.,
5
8.7
Program Functionality
Process the input file
When your program starts it must read all data from the file and process it. After processing the file, the program must print the following message to stdout

"Processed file XYZ and parsed data for M movies"

where XYZ is the name of the file that has been process and M is the number of movies whose data has been processed (this will be 1 less than than the number of lines in the file because the first line has the column headers).

E.g., Processed file movies_sample_1.csv and parsed data for 24 movies
