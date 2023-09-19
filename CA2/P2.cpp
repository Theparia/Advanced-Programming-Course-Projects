#include <iostream>
#include <vector>

using namespace std;

int multipy_elements(vector <int> list,int index,int count,int size);
void put_elements(vector <int> &list,int index,int size);
void remove_extra_elements(vector <int> &list,int index,int size);
void reverse_Vector(vector <int> &list,int start,int end);


int main()
{
vector <int> list;
int temp;
while(cin>>temp)
list.push_back(temp);
int size=list.size();
put_elements(list,0,size);
reverse_Vector(list,0,2*size-1);
remove_extra_elements(list,0,size);
reverse_Vector(list,0,size-1);
for(int index=0;index<list.size();index++)
cout<<list[index]<<" ";
cout<<endl;
}

int multipy_elements(vector <int> list,int index,int count,int size)
{
    if(count==size)
    return 1;
    return list[(index+1)%size]*multipy_elements(list,index+1,count+1,size);

}
void put_elements(vector <int> &list,int index,int size)
{
    if(index==size)
    return;
    list.push_back(multipy_elements(list,index,1,size));
    put_elements(list,index+1,size);
}
void remove_extra_elements(vector <int> &list,int index,int size)
{
    if(index==size)
    return;
    list.pop_back();
    remove_extra_elements(list,index+1,size);
}

void reverse_Vector(vector <int> &list,int start,int end)
{
     int temp;
     if(start >= end)
     return;
  
    temp = list[start];
    list[start] = list[end];
    list[end]   = temp;
    reverse_Vector(list, start+1, end-1);
}