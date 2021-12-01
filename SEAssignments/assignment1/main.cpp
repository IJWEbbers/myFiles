#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

int main()
{
   //----------------------------------------------------
   //part a
   //----------------------------------------------------

   //initialise strings
   string str1= "hello";
   string str2="world";

   //show values
   cout << "initial values" << endl;
   cout << "str1 = " << str1 << endl;
   cout << "str2 = " << str2 << endl;

   //copy
   cout << "copy str1 into str2" << endl;
   str2 = str1;
   cout << "str2 = " << str2 << endl;

   //insert
   cout << "insert letter 'a' into str1 at position 2" << endl;
   str1.insert(2, "a");
   cout << "str1 = " << str1 << endl;

   //erase
   cout << "remove character at position 2" << endl;
   str1.erase(2,1);
   cout << "str1 = " << str1 << endl;

   //compare
   if(str1 == str2){
      cout << "str1 is the same as str2" << endl;
   }
   else{
      cout << "str1 is not the same as str2" << endl;
   }

   cout << endl << endl;
   //----------------------------------------------------
   //part b
   //----------------------------------------------------

   //initialise vectors
   vector<int> vect1 (3, 100);
   vector<int> vect2 (3, 300);

   //show values
   cout << "initial values" << endl;
   cout << "vect1 = {";
   for(vector<int>::iterator i = vect1.begin(); i != vect1.end(); i++){
      cout << *i << " " ;
   }
   cout << "}" << endl;
   cout << "vect2 = {";
   for(vector<int>::iterator i = vect2.begin(); i != vect2.end(); i++){
      cout << *i << " " ;
   }
   cout << "}" << endl;

   //copy
   cout << "copy vect1 into vect2" << endl;
   vect2 = vect1;

   cout << "vect2 = {";
   for(vector<int>::iterator i = vect2.begin(); i != vect2.end(); i++){
      cout << *i << " " ;
   }
   cout << "}" << endl;

   //insert
   cout << "insert 200 into vect 1 at position 2" << endl;
   vect1.insert(vect1.begin() + 2, 1, 200);
   cout << "vect1 = {";
   for(vector<int>::iterator i = vect1.begin(); i != vect1.end(); i++){
      cout << *i << " " ;
   }
   cout << "}" << endl;

   //erase
   cout << "erase number at position 0" << endl;
   vect1.erase(vect1.begin());
   cout << "vect1 = {";
   for(vector<int>::iterator i = vect1.begin(); i != vect1.end(); i++){
      cout << *i << " " ;
   }
   cout << "}" << endl;

   //compare
   if(vect1 == vect2){
      cout << "vect1 is the same as vect2" << endl;
   }
   else{
      cout << "vect1 is not the same as vect2" << endl;
   }

   cout << endl << endl;
   //----------------------------------------------------
   //part c
   //----------------------------------------------------
   list<double> list1 (3, 1.5);
   list<double> list2 (5, 2.7);

   //show values
   cout << "initial values" << endl;
   cout << "list1 = {";
   for(list<double>::iterator i = list1.begin(); i != list1.end(); i++){
      cout << *i << " ";
   }
   cout << "}" << endl;
   cout << "list1 = {";
   for(list<double>::iterator i = list2.begin(); i != list2.end(); i++){
      cout << *i << " ";
   }
   cout << "}" << endl;

   //copy
   cout << "copy list1 into list2" << endl;
   list2 = list1;

   cout << "list2 = {";
   for(list<double>::iterator i = list2.begin(); i != list2.end(); i++){
      cout << *i << " " ;
   }
   cout << "}" << endl;

   //insert
   cout << "insert 200.0 into list1 at position 0" << endl;
   list1.insert(list1.begin(), 1, 200.0);
   cout << "list1 = {";
   for(list<double>::iterator i = list1.begin(); i != list1.end(); i++){
      cout << *i << " " ;
   }
   cout << "}" << endl;

   //erase
   cout << "erase number at position 0" << endl;
   list1.erase(list1.begin());
   cout << "list1 = {";
   for(list<double>::iterator i = list1.begin(); i != list1.end(); i++){
      cout << *i << " " ;
   }
   cout << "}" << endl;

   //compare
   if(list1 == list2){
      cout << "list1 is the same as list2" << endl;
   }
   else{
      cout << "list1 is not the same as list2" << endl;
   }

   cout << endl << endl;

   //----------------------------------------------------
   //part d
   //----------------------------------------------------
   vector<string> vdata1;
   vector<string> vdata2{"start", "setspeed 2", "stop"};

   //show values
   cout << "initial values" << endl;
   cout << "vdata1 = {";
   for(vector<string>::iterator i = vdata1.begin(); i != vdata1.end(); i++){
      cout << *i << " " ;
   }
   cout << "}" << endl;
   cout << "vdata2 = {";
   for(vector<string>::iterator i = vdata2.begin(); i != vdata2.end(); i++){
      cout << *i << " " ;
   }
   cout << "}" << endl;



   //copy
   cout << "copy vdata2 into vdata1" << endl;
         vdata1 = vdata2;

   cout << "vdata2 = {";
   for(vector<string>::iterator i = vdata2.begin(); i != vdata2.end(); i++){
      cout << *i << " " ;
   }
   cout << "}" << endl;

   //insert
   cout << "insert 'reverse' into vdata1 at position 2" << endl;
   vdata1.insert(vdata1.begin() + 2, 1, "reverse");
   cout << "vect1 = {";
   for(vector<string>::iterator i = vdata1.begin(); i != vdata1.end(); i++){
      cout << *i << " " ;
   }
   cout << "}" << endl;

   //erase
   cout << "erase string at position 0" << endl;
   vdata1.erase(vdata1.begin());
   cout << "vdata1 = {";
   for(vector<string>::iterator i = vdata1.begin(); i != vdata1.end(); i++){
      cout << *i << " " ;
   }
   cout << "}" << endl;

   //compare
   if(vdata1 == vdata2){
      cout << "vdata1 is the same as vdata2" << endl;
   }
   else{
      cout << "vdata1 is not the same as vdata2" << endl;
   }


   cout << "size of vdata1 is "<< vdata1.size() << endl;
   cout << "content of vdata[1] is "<<vdata1[1] << endl;

   cout << endl << endl;


   //----------------------------------------------------
   //part e
   //----------------------------------------------------
   queue<int> bob;
   int jimmy = -1;
   cout << "please enter some integers (enter 0 to end)" << endl;
   //pushes entered integer at bob
   while(jimmy != 0) {
      cin >> jimmy;
      bob.push(jimmy);
   };

   cout << "bob contains: ";
   //pops all integers in bob
   while(!bob.empty()){
      cout << ' ' << bob.front();
      bob.pop();
   }
   cout << endl;
   return 0;
}
