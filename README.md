# Suykerbuyk_CSCI2270_FinalProject
Inventory search program

This program will use a combination of graphs, binary trees, and structs.
It involves several city locations of a branch of a kind of store, which is
navigated through the graphs. Once at the proper graph node, there will exist
within a binary tree containing inventory.

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
