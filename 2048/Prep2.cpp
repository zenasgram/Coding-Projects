#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>


bool merge_num(const std::vector<int>& in, int bi, int ei, std::vector<int>& out);
void printvector (const std::vector<int> v);

int main(){

  std::vector<int> in, out;
  bool test;
  int bi, ei, ref=0;


  // begin of block of code reading the sudoku from the text file
  std::string filename1, filename2;

//open numbers file
  std::cout << "plese enter name of file containing the range of numbers" << std::endl;
  std::cin >> filename1;

  std::ifstream numbersfile;
  numbersfile.open(filename1.c_str());

  if(!numbersfile.is_open()){
      std::cout << "error, can't open input file" << std::endl;
      exit(EXIT_FAILURE);
  }

  int tmp1;
  while(numbersfile >> tmp1){
      in.push_back(tmp1);
  }


//open be file
  std::cout << "plese enter name of file containing bi and ei" << std::endl;
  std::cin >> filename2;

  std::ifstream befile;
  befile.open(filename2.c_str());

  if(!befile.is_open()){
      std::cout << "error, can't open input file" << std::endl;
      exit(EXIT_FAILURE);
  }


  int tmp2;
  while(befile >> tmp2){
      bi = tmp2;
      befile >> tmp2;
      ei = tmp2;
      std::cout << bi << " " << ei << std::endl;


      //print input
      printvector(in);

      //run the merge function
      test = merge_num(in, bi, ei, out);

      //print results if merge occurred
      if(test==true){
        std::cout << "1" << std::endl;
      }
      else{
          std::cout << "0" << std::endl;
      }

  std::cout << std::endl; //next paragraph
  }


    return 0;

}





bool merge_num(const std::vector<int>& in, int bi, int ei, std::vector<int>& out){

int current=bi, sum=0, zero=0, cmp=0;

//copy elements before bi
for(int x=0; x<bi; x++){
  out.push_back(in[x]);
}

//INITAL SETUP (Stores valoue of first NONZERO to CMP)
    //in[current] is the nearest NONZERO term
    while(in[current]==0 && current<ei){
          current++;
          zero++; //track number of zeroes found in vector
    }
    if(current<=ei){
      cmp = in[current];
      current++;
    }



//merge within range
while(current<=ei){


  if(in[current]==0 && current==ei){ //account for the case when current = ei but it is zero, and does not enter loop.
    zero++;
   }


  //in[current] is the nearest NONZERO term
  while(in[current]==0 && current<ei){
        current++;
        zero++; //track number of zeroes found in vector
  }

  //in[current] at this point is a NONZERO unless range exceeded

          //merge if current and next are equal
          if(cmp==in[current]){
            sum = 2*in[current];
            out.push_back(sum); //sum is used as a tracker. if sum=0 at the end of the function, nothing has changed.
            zero++; //merging results in one less digit

            //hunt for next term to use as cmp reference
            while(in[current]==0 && current<ei){
                  current++;
                  zero++; //track number of zeroes found in vector
            }
            cmp = in[current]; //setup after the merge

          }
          /*else if(current==ei && in[ei]==0){ //special case (when current has reached end of range without finding any other value to compare with)
            //range has hit limit. If this is zero and sum was not activated, then..
            out.push_back(cmp);  //print cmp, which equals to the original in[current]
            zero++; //account for ei being zero
          }*/
          //if cmp and current are not equal
          else{
              //print current
              out.push_back(cmp);
              cmp = in[current]; //set cmp for next iteration
          }



  //set current to hunt for next NONZERP
  current++;
}


//print zeroes to fill gap
for(int z=0; z<zero; z++){
  out.push_back(0);
}


//copy elements after ei
for(int y=ei+1; y<in.size(); y++){
  out.push_back(in[y]);
}

//print elements in output vector
printvector(out);

//clear out vector for the next iteration
out.clear();

    if(sum==0){
      return false;
    }
    return true;
}


void printvector (const std::vector<int> v){
  for (int i = 0; i<v.size(); i++){
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
}
