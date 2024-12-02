# COP3530_Project3 (Instructions on running the code)

Step 1: When the program initially runs, the user would have to give it around 1 minute before getting any menu options. This is because the data of the .csv file we used for this project is getting transferred to a vector and then transferred into a Red-Black tree and a B-Tree. After the insertions have been made, the code will output the time it takes for each insert function of the trees to finish processing the data.

Step 2: After outputting the time it takes for each insert function, a menu option will pop up in the command window. The user can choose from one of the following options:
  (1) Find random data point in each data structure and compare
  (2) Search all trees for specific information and export
  (3) Delete random node and time operation
  (0) Exit program

Step 2a: If user picks option 1, the program will point to a random data point from the .csv file and then the search function is performed in each tree to find that data point. When found, the program will output the time it took for each search function to find that data point.

Step 2b: If user picks option 2, the program will output another menu listed below:
  (1) Search by make
  (2) Search by model
  (3) Search by year
  (4) Search by type

After one of the numbered options are chosen, the user inputs again a keyword for the data to find depending on the criteria. After this keyword is typed, the search function will find all data points that have this specific key word, output the number of data points and time for each of the trees, and export an individual .csv file with all the data points specific to that keyword.

Step 2c: If user picks option 3, the program will point to a random data point from the .csv file and use the delete functions for both trees to delete that specific data point from the tree. This will also compare the times between the two trees on which performed the function faster.

Step 3: After user is finished with the code, by going back to the menu from step 2, they can type 0 to exit the program.
