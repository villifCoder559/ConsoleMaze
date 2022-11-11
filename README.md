# ConsoleMaze
An easy implementation in C++ for fun that creates a random squared maze and it can find the solution by showing it in the console.
The maze start and end position is set before generating the maze (E-> Ending point, S-> starting point). The maze itself is generated using the back tracking method.
This method is broken down into the following steps:
<ul>
  <li>Initialise all the points in the maze to be walls. I use a matrix to save the paths of the maze
  <li>From the old node(first iteration it will be starting node) checks if there is a random valid neighbour and pick it as new node
  <li>Link old node to the new node
  <li>New node becomes old node
  <li>If there are no valid neighbours<ul>
      <li>Backtrack to the last visited point
      <li>Continue till you have find a valid neighbour
      </ul>
  <li> Repeat untill matrix is full
  </ul>
To print the maze I have to double the size to insert walls between paths.

## Snapshots
<img src="https://user-images.githubusercontent.com/1312740/201408255-6713e6a6-51f3-4920-a415-ed441b803c1a.png" alt="Maze" width="30.4%">  <img src="https://user-images.githubusercontent.com/1312740/201408262-512c6a5a-2085-423a-bf88-7b7f7e19b7ae.png" alt="Maze" width="30%">
