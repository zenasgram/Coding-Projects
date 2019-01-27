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
  std::cout << "please enter name of file containing the range of numbers" << std::endl;
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
  std::cout << "please enter name of file containing bi and ei" << std::endl;
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


while(current<=ei){


    //hunt for the nearest NONZERO term
    if(in[current]==0 && current<=ei){
      do{
            current++;
            zero++; //track number of zeroes found in vector
      }while(in[current]==0 && current<ei);
    }

//SPECIAL CASE IN CASE CURRENT COUNTER OVER RUNS
    if(current>=ei && in[ei]==0){
      zero--;
      cmp = 0;
    }

    //only updates ref if this condition is met
    if(in[current]!=0){
      cmp = in[current]; //cmp is SET to NONZERO

        current++;

    }
    //CMP is now a NONZERO

//SPECIAL CASE IN CASE CURRENT COUNTER OVER RUNS
    if(current>ei && in[ei]==0){
      zero--;
      cmp = 0;
    }


  //hunt for the nearest NONZERO term for Current
  if(in[current]==0){
    do{
          current++;
          if(current<=ei){
            zero++; //track number of zeroes found in vector
          }
    }while(in[current]==0 && current<=ei);
  }


      if(cmp==in[current] && current<=ei){ //merge if equal
        sum = cmp*2; //cpm+in[current]
        zero++; //add one more zero to replace merged element
        out.push_back(sum);
        current++;
      }
      else if(in[current]!=0 && current<=ei){  //store if cmp reference if not equal
        out.push_back(cmp);
      }
      else if(current>ei && in[ei]!=0){   //SPECIAL CASE 1: current pointer is out of range and last value in range is a NONZERO
        out.push_back(in[ei]);
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
for(int y=ei+1; y<in.size(); y++){
  out.push_back(in[y]);
}

//print elements in output vector
printvector(out);



  for(int i=bi; i<=ei; i++){

    if(in[i]!=out[i]){
      //clear out vector for the next iteration
      out.clear();
      return true;
    }

  }
//clear out vector for the next iteration
out.clear();
return false;

}

void printvector (const std::vector<int> v){
  for (int i = 0; i<v.size(); i++){
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
}
