# Lem-In NOTES

#### INPUT
*	Simple and easy going parsing
	*	Reading line by line with libft's GNL. Starting off by creating rooms/nodes
	and adding those to a hash table (t_hash). The name of the room will represent its ID. Every new room will be assigned a unique size_t index, which is used to reference the room/node in the adjacency list we create later. Uniqueness can be implemented by having a static counter in the function that initiates the rooms/nodes.
	*	Once input represents edges, we should not receive any new rooms. Here we start creating edges in our adjacency list (t_graph). Index references should work as mentioned in the above bullet point.
*	Error management
	*	Room/node ID should not include a '-'. Otherwise any alphanumerical character should be OK. The input will include coordinates for the room/node. These could be anything as ft_atoi will return 0 if the data is not be numerical. Optionally we could return an error and exit the program.

#### MAX FLOW
*	Edmon's Karp Max Flow Algorithm
	*	Traversing occurs in a loop which runs BFS for every iteration, increasing the flow input by one every time. When BFS cannot find new routes or we run out of input flow, we break the loop.
	*	Save the paths for every flow result. Either create an array that fits "ant" amount of space for adjacency lists. This takes quite a lot of space, and copying the graph everytime will become time consuming for bigger data sets. Alternatively save only the ID's of the room/nodes in to some list.

#### CHOOSING PATHS
*	Determine how to divide the ants into the right paths to minimize the amount of steps needed for every ant to reach the final end node. Not quite sure how to do this, but some mates had an idea, so ask around

#### OUTPUT RESULT
*	Output result efficiently. Do not use ft_printf...