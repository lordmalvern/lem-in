# lem-in
Ant-farm simulation where ants try to reach one end of the farm to the other in as few moves as possible.

## How to Run
Compile using the included Makefile then in the terminal type:
```bash
./lem-in < mapfile
```
where mapfile is the path to the input file containing the map of the ant farm and the number of ants.

## Example Input
```
20
a 22 0
b 15 4
##start
c 11 7
d 9 3
e 1 5
##end
f 4 8
a-b
a-c
c-d
c-e
c-b
e-f
d-f
```

## Example Output
```
a 22 0
b 15 4
##start
c 11 7
d 9 3
e 1 5
##end
f 4 8
a-b
a-c
c-d
c-e
c-b
e-f
d-f
L1-d L2-e
L1-f L2-f L3-d L4-e
L3-f L4-f L5-d L6-e
L5-f L6-f L7-d L8-e
L7-f L8-f L9-d L10-e
L9-f L10-f L11-d L12-e
L11-f L12-f L13-d L14-e
L13-f L14-f L15-d L16-e
L15-f L16-f L17-d L18-e
L17-f L18-f L19-d L20-e
L19-f L20-f
```

## How It Works
### Input files
Input files start with the number of ants in the farm, then the names and locations of the rooms, and finally the connections between the rooms.

There are two forms of comments: comments and commands. Comments are ignored when parsing the input file, commands add a property to the room described in the line following the command.
Comments start with `#` and commands start with `##`.
Currently the only commands available are `##start` and `##end` denoting the start room and the end room.

Rooms are defined using the following format:
```
(Room name) (X coordinate) (Y coordinate)
```
Room names are invalid if they start with the characters `L` or `#`, otherwise they may contain any printable character.
X and Y coordinates represent the location of the room within the map and are only applicable if a visualizer is used.

Connections between rooms are defined with the following format:
```
(Room 1)-(Room 2)
```
Connections are two-way so the order of the connected rooms does not matter. 
A room can have as many or as few connections as needed however a valid input file must have at least one path from the start room to the end room.

### Ants
Ants must follow the following rules:
* No two ants may occupy the same room, except for the start and end rooms.
* Ants can only move one room a turn.
* If an ant cannot make a valid move on their turn, then the ant will wait in their current room for its turn.
* If an ant is waiting then its turn is not recorded in the returned output.

An ant's turn is represented in the following format:
```
L(ant number)-(destination)
```
