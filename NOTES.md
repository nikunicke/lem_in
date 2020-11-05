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
	*	Traversing occurs in a loop which runs BFS for every iteration, increasing the flow input by one every time. When BFS cannot find new routes or we run out of input flow, we break the loop. Note that this graph also includes capacities inside the verticies, meaning the algorithm must be reduced to this particular case. The correct way to do this, would be to separate each node into two parts. The first, which incoming paths point to, and the second, from which outgoing paths point from. Between the 'in' and 'out' node, we have an edge with a capacity which represents the capacity of the actual node. This implementation does not include such split nodes, but instead, the algorithm recognized wether we use an incoming or outgoing (residual) edge to reach a node. This allows us to define what edges are available from that particular node. Keep in mind that this might only work when the capacity == 1 for the whole graph. Visited tokens will become problematic with this solution, as the 'in' and 'out' node should have different tokens. However, as we already recognize what kind of an edge we are coming from, we can quite easily work around this issue by including another token for the node, which then would simulate the node being split...
	*	Save the paths for every flow result. Either create an array that fits "ant" amount of space for adjacency lists. This takes quite a lot of space, and copying the graph everytime will become time consuming for bigger data sets. Alternatively save only the ID's of the room/nodes in to some list.
	*	Everytime the flow increases, save the open set of paths and add it to a collection, which eventually will include all path sets for every flow value. The index of a sets represents its flow value + 1.
	
	>i.e if we end up having a total flow of 3, our collection will include 3 sets. The first set has one path,, the next 2 and the final set has 3 paths.

	*	Finally return the collection

#### CHOOSING PATHS
*	Determine which set to use
	>*path_length + ants - 1 = steps*
	*	The above calculation will determine the amount of steps it takes for some amount of ants to reach the end of the path. This can be reduced to calculate a cost (steps) for each set in the collection. The set with the lowest cost will then be used to send ants trough the graph.

	>*cost = (SUM(path_lengths_in_set) + ants - 1) / flow*

#### OUTPUT RESULT
*	Divide ants to paths
	*	Once we know which set to use, divide the ants to their respective paths. This is also determined by using the using the calculation which calculates how many steps the ants are going to take. We only change it to calculate the ants, and not steps. For steps we use the cost we calculated for the whole set. If a path would be longer than the cost, we would assign 0 ants to it, and decrease the flow value.
	>*ants = cost - path_length + 1*
	*	Every path will now have the max amount of ants that can be sent trough the graph within 'cost' steps. This means we sometimes end up with more ants than what we actually have. This is solved by reducing one ant from each path, starting from the longest, until we have the right amounts of ants. If a path would have all its ants removed, decrement the flow value.
*	Output steps
	*	Create an array where each index represents an ant. The index will store the current edge the ant is going to travel trough. Only print the step for the amount of ants that are currently moving, so starting with flow amount of ants, and then increasing by flow. Not that the flow needs to be updated in a similar way as when we removed ants from paths earlier, so if one path does not have anymore ants to send trough, flow will decrease, changing the amount of ants we add to the next step. This will then run in a loop, until the last ant has reached the end of its path.
