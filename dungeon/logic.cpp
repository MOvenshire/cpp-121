#include "logic.h"

/**
 * This function is provided; do not change
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  2D dynamic array representation of dungeon map with player's location.
 */
char** loadLevel(const string fileName, int& maxRow, int& maxCol, Player& player) {
    ifstream ifs(fileName);
    if (!ifs.is_open()) {
        cout << "ERROR: Unable to open: " << fileName << endl;
        return nullptr;
    }
    ifs >> maxRow >> maxCol;
    ifs >> player.row >> player.col;

    char** dungeon = createMap(maxRow,maxCol);
    if (dungeon == nullptr) {
        cout << "ERROR: Map did not load." << endl;
        return nullptr;
    }

    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {
            ifs >> dungeon[i][j];
            if (i == player.row && j == player.col) {
                dungeon[i][j] = TILE_PLAYER;
            }
        }
    }

    return dungeon;
}

/**
 * This function is provided; do not change
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 */
void getDirection(char input, int& nextRow, int& nextCol) {
    switch(input) {
        case MOVE_UP:
            nextRow--;
            break;
        case MOVE_DOWN:
            nextRow++;
            break;
        case MOVE_LEFT:
            nextCol--;
            break;
        case MOVE_RIGHT:
            nextCol++;
            break;
    }
}

/**
 * TODO: Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    //create dynamic array of char pointers for columns
    char** map = new char*[maxRow];
    
    //use a loop to set each char pointer to a row
    for(int i = 0; i<maxRow;i++){
        map[i] = new char [maxCol];
    }

    //initialize all to TILE_OPEN in row major order
    for(int r = 0; r<maxRow; r++){
        for(int c = 0; c<maxCol; c++){
            map[r][c] = TILE_OPEN;
        }
    }
    return map;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 */
void deleteMap(char** map, int maxRow) {
    //avoid memory leak by deleting the array
    for(int i = 0; i<maxRow; i++){
        delete[]map[i];
    }
    delete []map;
    map = nullptr;
}

/* 
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can call your createMap and deleteMap functions to help with this one!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  An updated 2D map that has twice as many columns and rows in size.
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {
    //create a new map twice the size
    maxRow*=2;
    maxCol*=2;
    char** mapSized = createMap(maxRow,maxCol);
    //copy the original map into the new one A (top left)
    for(int r = 0; r<maxRow/2; r++){
        for(int c = 0; c<maxCol/2;c++){
            mapSized[r][c] = map[r][c];
        }
    }

    //remove adventurer from the original map to copy
    for (int r = 0; r<maxRow/2;r++){
        for(int c = 0; c<maxCol/2; c++){
            if(map[r][c]=='o'){
                map[r][c]=TILE_OPEN;
            }
        }
    }
    
    //copy original into resized translations
    for(int r = 0; r<maxRow/2; r++){
        for(int c = 0; c<maxCol/2;c++){
            //copy into B (top right)
            mapSized[r][c+maxCol/2] = map[r][c];
            //copy into C (bottom left)
            mapSized[r+maxRow/2][c] = map[r][c];
            //copy into D (bottom right)
            mapSized[r+maxRow/2][c+maxCol/2] = map[r][c];
        }
    }
    
    deleteMap(map,maxRow/2);
    return mapSized;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int& nextRow, int& nextCol) {
    //check if player can move
	int currRow = player.row;
	int currCol = player.col;
	int currT = player.treasure;
	int status = STATUS_MOVE;

	//check out of bounds
	if(nextCol>=maxCol || nextRow>=maxRow||nextRow<0||nextCol<0){
		nextRow = currRow;
		nextCol = currCol;
		return STATUS_STAY;
	}
	
	char m = map[nextRow][nextCol];
	//check pillar/ monster
	if(m==TILE_MONSTER||m==TILE_PILLAR){
		nextRow = currRow;
		nextCol = currCol;
		return STATUS_STAY;
	}

	//check treasure
	if(m==TILE_TREASURE){
		player.treasure = currT+1;
		status = STATUS_TREASURE;
	}

	//check amulet
	if(m==TILE_AMULET){
		status = STATUS_AMULET;
	}

	//check door
	if(m==TILE_DOOR){
		status = STATUS_LEAVE;
	}

	//check exit 
	if(m==TILE_EXIT){
		if(currT>=1){
			status = STATUS_ESCAPE;
		}else{//treat as pillar
			nextRow = currRow;
			nextCol = currCol;
			status = STATUS_STAY;
		}
	}

	//update map
	map[currRow][currCol] = TILE_OPEN;
	map[nextRow][nextCol] = TILE_PLAYER;

	player.row = nextRow;
	player.col = nextCol;
    return status; // update to use STATUS consts from logic.h!
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, Player& player) {
    int currRow = player.row;
    int currCol = player.col;
    bool noPillar = true;
    // check up
    if(currRow > 0){//make sure there are vals above
    	for (int r = currRow-1; r>=0;r--){//start on tile above and move up
    		if(map[r][currCol]==TILE_MONSTER && noPillar){
    			map[r][currCol]=TILE_OPEN;
    			map[r+1][currCol]=TILE_MONSTER;
    		}
    		if(map[r][currCol]==TILE_PILLAR){
    			noPillar=false;
    		}
    	}
    }

    // check down
    //Reset no pillar 
    noPillar = true;
    if(currRow < maxRow-1){//make sure there are vals below
    	for (int r = currRow+1; r<maxRow;r++){//start on tile below and move down/ toward edge
    		if(map[r][currCol]==TILE_MONSTER && noPillar){
    			map[r][currCol]=TILE_OPEN;
    			map[r-1][currCol]=TILE_MONSTER;
    		}
    		if(map[r][currCol]==TILE_PILLAR){
    			noPillar=false;
    		}
    	}
    }

    // check left
    //Reset no pillar 
    noPillar = true;
	if(currCol > 0){//make sure there are vals above
    	for (int c = currCol-1; c>=0;c--){//start on tile above and move up
    		if(map[currRow][c]==TILE_MONSTER && noPillar){
    			map[currRow][c]=TILE_OPEN;
    			map[currRow][c+1]=TILE_MONSTER;
    		}
    		if(map[currRow][c]==TILE_PILLAR){
    			noPillar=false;
    		}
    	}
    }

    // check right
	if(currCol < maxCol-1){//make sure there are vals below
    	for (int c = currCol+1; c<maxCol;c++){//start on tile below and move down/ toward edge
    		if(map[currRow][c]==TILE_MONSTER && noPillar){
    			map[currRow][c]=TILE_OPEN;
    			map[currRow][c-1]=TILE_MONSTER;
    		}
    		if(map[currRow][c]==TILE_PILLAR){
    			noPillar=false;
    		}
    	}
    }

    // check if any monster is on player
    if(map[currRow][currCol]==TILE_MONSTER){
    	return true;//adventurer killed game over
    }else{
    	return false;//game continues
    }
}
