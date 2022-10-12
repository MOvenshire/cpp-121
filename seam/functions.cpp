#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

#define INFO(X) cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " = " << X << endl;

using std::cout;
using std::endl;
using std::string;

Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // dlete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
  cout<<"End deleteImage..."<<endl;
}

int* createSeam(int length) {
    // TODO(student): create a seam
    //INFO(length);
    //instantiate// allocate on heap 
    int *seam = new int[length];
    //set all to 0
    for (int i = 0;i<length;i++){ 
      seam[i]=0;
      //cout<<seam[i]<<" "<<&seam[i]<<endl;
    }
  return seam;
}

void deleteSeam(int* seam) {
    // TODO(student): delete a seam
    //INFO(seam);
    delete []seam;
}

bool loadImage(string filename, Pixel** image, int width, int height) {
  // TODO(student): load an image
  /*INFO(filename);
  INFO(image);
  INFO(width);
  INFO(height);
  */
  std::ifstream ifs(filename);
  if(!ifs.is_open()){
    cout<<"Error: failed to open input file - "<<filename<<endl;
   return false;
  }
  
  //error check preamble 
  char type[3];
  ifs >> type; // should be P3
  if ((toupper(type[0]) != 'P') || (type[1] != '3')) { // check that type is correct
    cout << "Error: type is " << type << " instead of P3" << endl;
    return false;
  }
  if(ifs.bad()){
    cout<<"Error: read non-integer value"<<endl;
    return false;
  }

  //make sure that height and width match input values 
  int w = 0, h = 0;
  ifs >> w >> h;
  if(ifs.fail()){
    cout<<"Error: read non-integer value"<<endl;
    return false;
  }
  if (w != width) { // check that width matches what was passed into the function
    cout << "Error: input width ("<<width<< ") does not match value in file ("<<w<<")"<< endl;
    return false;
  }
  if (h != height) { // check that height matches what was passed into the function
    cout << "Error: input height ("<<height<< ") does not match value in file ("<<h<<")"<< endl;
    return false;
  }

  int max;
  ifs>>max;
  //fill image with pixels from file 
  int red = 0;
  int blue = 0;
  int green = 0;
  //fill in column major order 
  for (int row = 0; row<height; row++){
    for (int col =0; col<width; col++){
      blue=-100000000;
      ifs>>red;
      if(red<0 ||red>255){
        cout<<"Error: invalid color value "<<red<<endl;
        return false;
      }
      ifs>>green;
      if(green<0||green>255){
        cout<<"Error: invalid color value "<<green<<endl;
        return false;
      }
      ifs>>blue;
      if((ifs.eof()&&(col==width && row==height))||(blue==-100000000)){
        cout<<"Error: not enough color values"<<endl;
        return false;
      }
      if(blue<0 ||blue>255){
        cout<<"Error: invalid color value "<<blue<<endl;
        return false;
      }
      if(ifs.fail()&& !ifs.eof()){
        cout<<"Error: read non-integer value"<<endl;
        return false;
      }
      image[col][row].r= red;
      image[col][row].g=green;
      image[col][row].b=blue;
      //cout<<col<<" "<<row<<" *"<<red<<" "<<green<<" "<<blue<<endl;
    }
  }
  //see if values remaining
  red=-100000000;
  ifs>>red;
  if(!ifs.eof()||red!=-100000000){
    cout<<"Error: too many color values"<<endl;
    return false;
  }

  ifs.close();
  return true;
}

bool outputImage(string filename, Pixel** image, int width, int height) {
    // TODO(student): output an image
    /*INFO(filename);
    INFO(image);
    INFO(width);
    INFO(height);
    */
    // TODO(student): declare/define and open output file stream
    std::ofstream outFS;
    outFS.open(filename);
    // TODO(student): check if output stream opened successfully
    if(!outFS.is_open()){
      cout<<"Error: failed to open output file - "<<filename<<endl;
      return false;
    }
    // TODO(student): output preamble
    outFS<<"P3"<<endl;
    outFS<<width<<" "<<height<<endl;
    outFS<<255<<endl;
  
    // TODO(student): output pixels
    for (int row = 0; row<height; row++){
      for (int col = 0; col<width; col++){
        outFS<<image[col][row].r<<" ";
        outFS<<image[col][row].g<<" ";
        outFS<<image[col][row].b<<" ";
      }
    }
    //close file 
    outFS.close();

  return true;
}

int energy(Pixel** image, int column, int row, int width, int height) { 
    // TODO(student): compute the energy of a pixel
    /*
    INFO(image);
    INFO(column);
    INFO(row);
    INFO(width);
    INFO(height);
    */
    int rx,ry,gx,gy,bx,by,deltax,deltay;
    int energy = 0;
    //set basic values for non border
    int c1 = column+1;
    int c2 = column-1;
    int r1 = row+1;
    int r2 = row-1;

    //handle basic edge cases
    if(row==0){// top row
      r2=height-1;    
    }if(row==height-1){//bottom row
      r1=0;
      r2=height-2;
    }
    if(column ==0){//left column
      c2= width-1;
    }
    if(column==width-1){//right column
      c1=0;
      c2=width-2;
    }
    //handle column or row only 1 component
    if(width==1){
      c1=0;
      c2=0;
    }
    if(height==1){
      r1=0;
      r2=0;
    }

    //find x and y components of each color
    rx = abs(image[column][r1].r-image[column][r2].r);
    gx = abs(image[column][r1].g-image[column][r2].g);
    bx = abs(image[column][r1].b-image[column][r2].b);

    ry = abs(image[c1][row].r-image[c2][row].r);
    gy = abs(image[c1][row].g-image[c2][row].g);
    by = abs(image[c1][row].b-image[c2][row].b);

    //square each color then add all colors for x and y 
    deltax = rx*rx + gx*gx + bx*bx;
    deltay = ry*ry + gy*gy + by*by;
    //add both energy parts
    energy = deltax + deltay;
    //cout<<energy<<" "<<column<<" "<<row<<endl;
  return energy;
}

//part 2 
int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
    // TODO(student): load a vertical seam
    //INFO(image);
    /*INFO(start_col);
    INFO(width);
    INFO(height);
    INFO(seam);
    */
    //set seam for first row to starting column
    seam[0] = start_col; 
    //initialize total energy to energy of first pixel
    int totalEnergy = energy(image,start_col,0,width,height);
    int minEnergy =totalEnergy;
    int left,forward,right;

    for(int row = 1; row<height;row++){
      //handle first column / no left 
      if(start_col==0&&start_col!=width-1){
        forward = energy(image,start_col,row,width,height);
        right = energy(image,start_col+1,row,width,height);

        //handle right is less than forward
        if(right < forward){
          minEnergy = right;
          start_col =start_col+1;
        }
        else{//handle when forward is less than or equal to right
          minEnergy = forward;
          //start col does not have to change 
        }
      }
      
      //handle last column
      else if(start_col==width-1&&start_col!=0){
        left = energy(image,start_col-1,row,width,height);
        forward = energy(image,start_col,row,width,height);

        //handle left is less than forward
        if(left < forward){
          minEnergy = left;
          start_col =start_col-1;
        }
        else{//handle when forward is less than or equal to left
          minEnergy = forward;
          //start col does not have to change 
        }
      }

      //handle only one column
      else if(width-1==0){
        forward = energy(image,start_col,row,width,height);
        minEnergy = forward;
      }
      
      //handle all others 
      else if(start_col > 0 && start_col < width-1){
        left = energy(image,start_col-1,row,width,height);
        forward = energy(image,start_col,row,width,height);
        right = energy(image,start_col+1,row,width,height);
        
        //set default to forward
        minEnergy = forward;

        //handle one is smaller
        if(left<forward && left<right){
          minEnergy = left;
          start_col = start_col-1;
        }
        if(right<forward && right<left){
          minEnergy = right;
          start_col = start_col+1;
        }
        if(left==right && right<forward){
          minEnergy = right;
          start_col+= 1;
        }
      }
      seam[row] = start_col;
      totalEnergy+=minEnergy;

    }//close row loop

  return totalEnergy;
}

//Extra Credit
int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
    // TODO(student): load a horizontal seam
    INFO(image);
    INFO(start_row);
    INFO(width);
    INFO(height);
    INFO(seam);
    
    seam[0] = start_row; 
    //initialize total energy to energy of first pixel
    int totalEnergy = energy(image,0,start_row,width,height);
    int minEnergy =totalEnergy;
    int left,forward,right;

    for(int col = 1; col<height;col++){
      //handle first column / no left 
      if(start_row==0&&start_row!=height-1){
        forward = energy(image,col,start_row,width,height);
        right = energy(image,col,start_row+1,width,height);

        //handle right is less than forward
        if(right < forward){
          minEnergy = right;
          start_row =start_row+1;
        }
        else{//handle when forward is less than or equal to right
          minEnergy = forward;
        }
      }
      
      //handle last column
      else if(start_row==height-1&&start_row!=0){
        left = energy(image,col,start_row-1,width,height);
        forward = energy(image,col,start_row,width,height);

        //handle left is less than forward
        if(left < forward){
          minEnergy = left;
          start_row =start_row-1;
        }
        else{//handle when forward is less than or equal to left
          minEnergy = forward;
          //start col does not have to change 
        }
      }

      //handle only one column
      else if(height-1==0){
        forward = energy(image,col,start_row,width,height);
        minEnergy = forward;
      }
      
      //handle all others 
      else if(start_row > 0 && start_row < height-1){
        left = energy(image,col,start_row-1,width,height);
        forward = energy(image,col,start_row,width,height);
        right = energy(image,col,start_row+1,width,height);
        
        //set default to forward
        minEnergy = forward;

        //handle one is smaller
        if(left<forward && left<right){
          minEnergy = left;
          start_row = start_row-1;
        }
        if(right<forward && right<left){
          minEnergy = right;
          start_row = start_row+1;
        }
        if(left==right && right<forward){
          minEnergy = right;
          start_row-= 1;
        }
      }
      seam[col] = start_row;
      totalEnergy+=minEnergy;

    }//close row loop

  return totalEnergy;
}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
    // TODO(student): find min vertical seam
    //INFO(image);
    //INFO(width);
    //INFO(height);

    int* verticalSeam = createSeam(width);
    int* minVSeam = createSeam(width);
    int colE;
    int minEnergy = loadVerticalSeam(image,0, width, height, verticalSeam);
    loadVerticalSeam(image,0,width,height,minVSeam);

    for (int col =1; col<width;col++){
      colE = loadVerticalSeam(image, col, width, height, verticalSeam);
      if(colE<minEnergy){
        minEnergy = colE;
        loadVerticalSeam(image,col,width,height,minVSeam);
      }
    }
    deleteSeam(verticalSeam);
  return minVSeam;
}

//Extra Credit
int* findMinHorizontalSeam(Pixel** image, int width, int height) {
    // TODO(student): find min horizontal seam
    /*INFO(image);
    INFO(width);
    INFO(height);
    */
    int* horizontalSeam = createSeam(height);
    int* minHSeam = createSeam(height);
    int rowE;
    int minEnergy = loadHorizontalSeam(image,0, width, height, horizontalSeam);
    loadHorizontalSeam(image,0,width,height,minHSeam);

    for (int row =1; row<height;row++){
      rowE = loadHorizontalSeam(image, row, width, height, horizontalSeam);
      if(rowE<minEnergy){
        minEnergy = rowE;
        loadHorizontalSeam(image,row,width,height,minHSeam);
      }
    }
    deleteSeam(horizontalSeam);
  return minHSeam; 
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
    // TODO(student): remove a vertical seam
    /*INFO(image);
    INFO(width);
    INFO(height);
    INFO(verticalSeam);
  */
    int col;
    for (int row = 0; row<height;row++){
      col = verticalSeam[row];
      for(int c = 0; c<width-1;c++){
        if(c>=col){
          image[c][row] = image[c+1][row];
        }
      }
    }
}

//Extra Credit
void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
    // TODO(student): remove a horizontal seam
    INFO(image);
    INFO(width);
    INFO(height);
    INFO(horizontalSeam);

    int row;
    for (int col = 0; col<width;col++){
      row = horizontalSeam[col];
      //cout<<col;
      for(int r = 0; r<height-1;r++){
        if(r>=row){
          image[col][r] = image[col][r+1];
        }
      }
    }
}
