#include <iostream>
#include <sstream>
#define show(var) cout<<var<<' ';
#define showp(l,r) cout<<l<<": "<<r<<'\n';

using namespace std;

int main()
{
    string org;
    show("Enter Original data: ")
    getline(cin, org);
    show("\n\tSender Side");
    showp("\nOriginal data",org);
   
    string flag = "flag";
    string byteStuff = flag + " ";
    stringstream input(org);
   
    string word;
    while(input>>word){
        if(word=="ESC" || word == flag)
            byteStuff+= "ESC ";
       
        byteStuff+= word;
        byteStuff+= ' ';
    }
    byteStuff+= flag;
   
    showp("Byte Stuff data", byteStuff);
   
    show("\n\tReceiver side");
    showp("\nByte Stuffed Code", byteStuff);
   
    string DeStuff = "";
    stringstream received(byteStuff);
   
    received>>word;
    while(received>>word){
        if(word==flag) break;
       
        if(word=="ESC")
            received>>word;
       
        DeStuff+= word;
        DeStuff+= ' ';
    }
   
    showp("DeStuffed Code", DeStuff);
   
    return 0;
}

/* OUTPUT:

Enter Original data:  there is no ESC from my flag today

        Sender Side
Original data: there is no ESC from my flag today
Byte Stuff data: flag there is no ESC ESC from my ESC flag today flag

        Receiver side
Byte Stuffed Code: flag there is no ESC ESC from my ESC flag today flag
DeStuffed Code: there is no ESC from my flag today
*/