#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>


bool merge_num(std::vector<int>& in, int bi, int ei, std::vector<int>& out);
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





bool merge_num(std::vector<int>& in, int bi, int ei, std::vector<int>& out){

int zero, sum;
std::vector<int> check;

sum = 0;
zero = 0;

//copy elements to check for final return value
for(int i=bi; i<=ei; i++){
  check.push_back(in[i]);
}


//copy elements after ei in reverse order (SAVES A COPY OF ORIGINAL IN FIRST FEW ELEMENTS OF OUT VECTOR)
for(int i=in.size()-1; i>=ei; i--){
  out.push_back(in[i]);
}


for (int i=bi; i<=ei; i++){

  if (in[i]==0) //if zero, keep track
  {
      out.push_back(0); //push all zeroes into out
  }
}
for (int i=ei; i>=bi; i--){ //reverse order to setup for popback

  if (in[i]!=0) //if nonzero, keep track
  {
      out.push_back(in[i]); //push all zeroes into out
  }
}

//out vector is arranged from all zero terms to nonzero terms

//prep in vector
//erase all elements till bi
for(int x=in.size()-1; x>=bi; x--){
  in.pop_back();
}

//begin to pop into out vector
for(int i=out.size()-1; i>=0; i--){

  if(out[i]==0){ //sees zero term
    in.push_back(out[i]);
  }
  else if (out[i]==out[i-1]){

    //merge
    sum = out[i]*2; //double the value
    in.push_back(sum);
        if((i-2)!=0){ //condition to check for i at second last nonzero term.
          i--; //jump the next index as it has merged
          zero++; //take into account additional zero to replace merged term
        }
        else{ //i is at second last position, and the last term has been mered. Start printing zeroes.
          //print additional zeroes to fill gap if any
            for(int z=0; z<zero; z++){
            in.push_back(0);
            }
          }
    }
    else{
        in.push_back(out[i]);
    }

}



//print elements in output vector
out.clear();
for(int i=0; i<in.size(); i++){
  out.push_back(in[i]);
}
printvector(out);


int c=0; //index for check
  for(int i=bi; i<=ei; i++){

    if(check[c]!=out[i]){
      //clear out vector for the next iteration
      out.clear();
      return true;
    }
    c++;
  }
//clear out vector for the next iteration
out.clear();
return false;


}
/*
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
      }while(in[current]==0 && current<=ei);
    }
    //only updates ref if this condition is met
    if(in[current]!=0){
      cmp = in[current]; //cmp is SET to NONZERO

        current++;

    }
    //CMP is now a NONZERO



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

*/

void printvector (const std::vector<int> v){
  for (int i = 0; i<v.size(); i++){
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
}
