#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>

int rowcoltoi(int x, int y, int rowlen);

bool merge_num(std::vector<int>& v, int bi, int ei);
void rotate_anti_clock(std::vector<int>& v);
bool game_over(const std::vector<int>& v);
void print_grid(const std::vector<int>& v);
void randgenerate (std::vector<int>& v);

int main (){

std::ifstream infile;
std::string filename;

std::vector<int> v;

std::cout << "enter initial configuration file name:" << std::endl;
std::cin >> filename;

infile.open(filename.c_str());

if(!infile.is_open()){
    std::cout << "file not found, using default start configuration" << std::endl;
    //configure default grid
    for(int i=0; i<15; i++){
      v.push_back(0);
    }
    v.push_back(2);

}

//configure infile
int n;
while(infile >> n){
    v.push_back(n);
}

//main script there
int rowlen = std::sqrt(v.size());
bool gameover, mergecheck;
std::string arrow;
int bi, ei, execute=0;

gameover = game_over(v);

//print initial grid
print_grid(v);

while(gameover==false){

std::cin >> arrow;

if (arrow=="a"){  //LEFT

  //merge for elements along each row, bounded by row lenght
  for (int i=0; i<rowlen; i++){
    bi= i*rowlen;
    ei= bi+rowlen-1;
    mergecheck = merge_num(v, bi, ei);

      if(mergecheck==true){
        execute++; //something has changed! Prep to print grid again
      }
  }
}
else if (arrow=="d"){   //RIGHT

rotate_anti_clock(v);
rotate_anti_clock(v);

//merge for elements along each row, bounded by row lenght
for (int i=0; i<rowlen; i++){
  bi= i*rowlen;
  ei= bi+rowlen-1;
  mergecheck = merge_num(v, bi, ei);

    if(mergecheck==true){
      execute++;
    }
}
rotate_anti_clock(v);
rotate_anti_clock(v);
}
else if (arrow=="s"){   //DOWN

  rotate_anti_clock(v);
  rotate_anti_clock(v);
  rotate_anti_clock(v);

  //merge for elements along each row, bounded by row lenght
  for (int i=0; i<rowlen; i++){
    bi= i*rowlen;
    ei= bi+rowlen-1;
    mergecheck = merge_num(v, bi, ei);

      if(mergecheck==true){
        execute++;
      }
  }
  rotate_anti_clock(v);
}
else if (arrow=="w"){   //UP

  rotate_anti_clock(v);

  //merge for elements along each row, bounded by row lenght
  for (int i=0; i<rowlen; i++){
    bi= i*rowlen;
    ei= bi+rowlen-1;
    mergecheck = merge_num(v, bi, ei);

      if(mergecheck==true){
        execute++;
      }
  }
  rotate_anti_clock(v);
  rotate_anti_clock(v);
  rotate_anti_clock(v);
}

if(execute!=0){
  //generate random 2
  randgenerate(v);

  print_grid(v);
  execute = 0; //reset
}

//check to see if gameover condition is met
gameover = game_over(v);

}

std::cout << "game over" << std::endl;


return 0;

}




// function rowcoltoi maps two-dimensional indices to a one-dimensional one
// it takes in input:
// - the two indices x and y of a two dimensional data structure
// - the length of the row, rowlen
// it returns:
// - the corresponding one-dimensional index

int rowcoltoi(int x, int y, int rowlen){
    return x*rowlen+y;
}



/*this is almost the same as the function described in the preparatory exercise
except for the fact that there are no separate input and output vectors:
v is at the same time an input and output parameter. Note that ei is not the
index of the last element involved in the transformation, it's 1 + the index of
the last element involved in the transformation. You can notice that this is the
case if you observe carefully examples 2 and 3. (It is quite common,
when ranges are expressed in C++, that the left endpoint is included in the
interval while the right one isn't.)*/
bool merge_num(std::vector<int>& v, int bi, int ei){

  int current=bi, sum=0, zero=0, cmp=0;
  std::vector<int> out;


  //copy elements before bi
  for(int x=0; x<bi; x++){
    out.push_back(v[x]);
  }


  while(current<=ei){


    //hunt for the nearest NONZERO term
    if(v[current]==0 && current<=ei){
      do{
            current++;
            zero++; //track number of zeroes found in vector
      }while(v[current]==0 && current<ei);
    }

  //SPECIAL CASE IN CASE CURRENT COUNTER OVER RUNS
    if(current>=ei && v[ei]==0){
      zero--;
      cmp = 0;
    }

    //only updates ref if this condition is met
    if(v[current]!=0){
      cmp = v[current]; //cmp is SET to NONZERO

        current++;

    }
    //CMP is now a NONZERO

  //SPECIAL CASE IN CASE CURRENT COUNTER OVER RUNS
    if(current>ei && v[ei]==0){
      zero--;
      cmp = 0;
    }

        //hunt for the nearest NONZERO term for Current
        if(v[current]==0){
          do{
                current++;
                if(current<=ei){
                  zero++; //track number of zeroes found in vector
                }
          }while(v[current]==0 && current<=ei);
        }


            if(cmp==v[current] && current<=ei){ //merge if equal
              sum = cmp*2; //cpm+in[current]
              zero++; //add one more zero to replace merged element
              out.push_back(sum);
              current++;
            }
            else if(v[current]!=0 && current<=ei){  //store if cmp reference if not equal
              out.push_back(cmp);
            }
            else if(current>ei && v[ei]!=0){   //SPECIAL CASE 1: current pointer is out of range and last value in range is a NONZERO
              out.push_back(v[ei]);
            }
            else{
              if(zero!=(ei-bi+1)){
               out.push_back(cmp);  //incase only zeros are detected, DONT print cmp
                                   //SPECIAL CASE 2: current pointer is out of range and cmp still holds an unprinted value
              zero++;
              }
            }


  }


  //print zeroes to fill gap
  for(int z=0; z<zero; z++){
    out.push_back(0);
  }


  //copy elements after ei
  for(int y=ei+1; y<v.size(); y++){
    out.push_back(v[y]);
  }

  for(int i=bi; i<=ei; i++){

    if(v[i]!=out[i]){
        //clear out vector for the next iteration
        v.clear();
        for(int i=0; i<out.size(); i++){
          v.push_back(out[i]);
        }
      return true;
    }

  }

  //clear out vector for the next iteration
    v.clear();
    for(int i=0; i<out.size(); i++){
      v.push_back(out[i]);
    }
  return false;

}


/*this function performs an “anti-clockwise rotation” of the grid contained in
vector v (again this is both an input and output parameter). For example if v
is passed to the function containing 1 2 3 4 5 6 7 8 10 11 12 13 14 15 16, after
the function call v should contain 4 8 12 16 3 7 11 15 2 6 10 14 1 5 9 13.
Note that this is a typical example in which xytoi/rowcoltoi as mentioned above
should be used for the sake of good design and readability*/
void rotate_anti_clock(std::vector<int>& v){

int n, rowlen = std::sqrt(v.size());
std::vector<int> out;

  for (int i=rowlen-1; i>=0; i--){

    for(int j=0; j<rowlen; j++){
        n = v[rowcoltoi(j,i, rowlen)];

        //rotate anticlockwise
        out.push_back(n);
    }
  }

  //map back to input vector v
  v.clear();
  for(int i=0; i<out.size(); i++){
    v.push_back(out[i]);
  }

}


/*this should return true if it's true that the content of v represents a game
over situation and false otherwise. (An input file may well contain a grid already
in a game over situation, in which case the program should just print game over
as in the screenshot above.)*/
bool game_over(const std::vector<int>& v){

  int n, rowlen = std::sqrt(v.size());
  std::vector<int> tmp;

  //copy into new vector for manipulation
  tmp = v;

  for (int i=0; i<rowlen; i++){
    for(int j=0; j<rowlen; j++){
      n = tmp[rowcoltoi(i,j, rowlen)];
        if(n==0){
          return false; //game still has zeroes, game can continue.
        }
    }
  }

//if two elements side by side have the same value, game is NOT over

for (int i=0; i<rowlen; i++){
  for(int j=0; j<rowlen-1; j++){
    if(tmp[rowcoltoi(i,j, rowlen)]==tmp[rowcoltoi(i,j+1, rowlen)]){
      return false;
    }
}
}

//check for vertical direction
  rotate_anti_clock(tmp);

  for (int i=0; i<rowlen; i++){
    for(int j=0; j<rowlen-1; j++){
      if(tmp[rowcoltoi(i,j, rowlen)]==tmp[rowcoltoi(i,j+1, rowlen)]){
        return false;
      }
  }
}
  //all the empty spaces in the game have been filled up. Game Over.
  return true;

}


/*This should print the content of v as an nxn grid as shown in the screenshots.
Functions other than the main and print_grid should not contain user or file
input or output (cin, cout, ifstream etc) in their implementation.*/
void print_grid(const std::vector<int>& v){

  int n, rowlen = std::sqrt(v.size());

  for (int i=0; i<rowlen; i++){
    for(int j=0; j<rowlen; j++){
        n = v[rowcoltoi(i,j, rowlen)];
        std::cout << n << "\t" ;
    }
  std::cout << std::endl;
  }
//space prints apart
std::cout << std::endl;
}

void randgenerate (std::vector<int>& v){

  int r;
  bool randgen = false; //setup
  std::vector<int> tmp;

  r = (rand() % v.size()); //r is a random index

  //Insert random 2 iteration
      do{
//IF A NULL SPACE IS FOUND, INSERT 2
          if(v[r]==0){
              for(int i=0; i<r; i++){
                tmp.push_back(v[i]);
              }

              tmp.push_back(2); //insert 2

              for(int i=r+1; i<v.size(); i++){
                tmp.push_back(v[i]);
              }

              //paste back into output vector
              v.clear();
              for(int i=0; i<tmp.size(); i++){
                v.push_back(tmp[i]);
              }
              randgen=true;
          }

          //run through index and ensures no repeated value generated by rand function
          if(r<v.size()){
            r++;
          }
          else{
            r=0;
          }

      }while(randgen==false);
}
