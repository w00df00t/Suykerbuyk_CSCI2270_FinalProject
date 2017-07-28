PROGRAM SUMMARY:
-------------------
This program will use a combination of graphs, 2D vertices, and structs.
It involves several city locations of a branch of a kind of store, which is
navigated through the graphs. Once at the proper graph node, there will exist
a vector within containing inventory.

The user will be able to enter their own location within the network, and the
item they wish to order. The function will check the nearest store's inventory
for the item, and if available, will order it. If it is not available, this
process will continue on to the next nearest store from the home node. This
continues until the item is either found or the search has reached the end of
the store nodes, at which point it will issue a message indicating that it is
all sold out.

Therefore, the user will simply need to run the program with a supplementary
store list and inventory text file in the command line, and from there will
follow an on-screen menu to indicate their location and the item they seek.

HOW TO RUN:
-------------------
1 Download FinalProject.cpp file and supplementary datafile.txt
2 In .cpp file, if you would like to make any changes to the cities, you'll
  need to access the "buildNetwork" function (line 163); the addVertex section
  at the top is used to add a city. Below it, you must also include with
  addEdge the new city name, all other city names (with each iteration), and
  the distance in miles between the two cities.
3 In datafile.txt, you can edit or add any movies you wish; they are presented
  in the format of:
    CITYNAME,IMDB_RANK,TITLE,YEAR,INVENTORY_COUNT
  Note, the CITYNAME must be a city included in step 2.
4 Compile the program; use "g++ FinalProject.cpp -o a" from the terminal.
5 With datafile in the same folder, run the program from the command prompt as:
      ./a datafile.txt
6 Follow on screen instructions.

DEPENDENCIES:
-------------------
Requires terminal and developer tools installed to machine, and must be run
with supplementary text file.

SYSTEM REQUIREMENTS:
-------------------
Program was designed to run on Mac OS Sierra with XCode installed.

NAME:
-------------------
Savant Olen Suykerbuyk

OPEN ISSUES/BUGS:
-------------------
None, I'm awesome. 
