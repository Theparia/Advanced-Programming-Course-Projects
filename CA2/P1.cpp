#include <iostream>
#include <string>
using namespace std;

string FI(string input);
void recursiveReverse(string &str, int index); 

int main(){
string input;
getline(cin,input);
cout << FI(input) <<endl;
}


string FI(string input)
{
string first_half,second_half;
int mid_index=input.size()/2;
if(mid_index==0)
{
    return input;
}
if(input.size()%2==0)
first_half=input.substr(mid_index,mid_index);
else 
first_half=input.substr(mid_index,mid_index+1);
second_half=input.substr(0,mid_index);
recursiveReverse(first_half,0);
recursiveReverse(second_half,0);
return FI(first_half)+FI(second_half);

}


void recursiveReverse(string &str, int index) 
{ 
    int length = str.length(); 
    if (index == length / 2) 
        return; 
    swap(str[index], str[length - index - 1]); 
    recursiveReverse(str, index + 1); 
} 