#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>


bool merge_num(const std::vector<int>& in, int bi, int ei, std::vector<int>& out);
void printvector (const std::vector<int> v, int ref);

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
      printvector(in, 0);

      //run the merge function
      test = merge_num(in, bi, ei, out);

      //print output
      printvector(out, ref);
        ref = ref + in.size();

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

int current=bi, next, sum=0, zero=0, cmp=0;

//copy elements before bi
for(int x=0; x<bi; x++){
  out.push_back(in[x]);
}


//merge within range
while(current<=ei){

  //v[k] is the nearest NONZERO term
  while(in[current]==0 && current<ei){
        current++;
        zero++; //track number of zeroes found in vector
  }


  //ENSURE bi and ei markers do not exceed the range
  if (current == ei){
    next = current;
  }
  else{
    next=current+1;
  }


  //find the NEXT nonzero term
  while(in[next]==0 && next<ei){
        next++;
        zero++; //track number of zeroes found in vector
  }

                          //ONLY for first case cmp variable
                          if(cmp==0){
                            cmp = in[current];
                          }

    //merge if current and next are equal
    if(cmp==in[next]){
      sum = cmp + in[next];
      out.push_back(sum);
      cmp = sum;
        zero++; //merging results in one less digit

    //jump to next NEXT since the 2 digits have merged
        next++;

      while(in[next]==0 && next<=ei){
            next++;
            zero++;
      }

    }
    else{
        //print current
        out.push_back(in[current]);
        cmp = in[current];
    }

  current=next; //loop for next comparison
}


//print zeroes to fill gap
for(int z=0; z<zero; z++){
  out.push_back(0);
}


//copy elements after ei
for(int y=ei+1; y<in.size(); y++){
  out.push_back(in[y]);
}


    if(sum==0){
      return false;
    }
    return true;
}


void printvector (const std::vector<int> v, int ref){
  for (int i = ref; i<v.size(); i++){
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
}
