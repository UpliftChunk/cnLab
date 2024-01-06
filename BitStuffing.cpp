#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define show(var) cout<<var<<'\n'
#define showp(l,r) cout<<l<<": "<<r<<'\n'

// make sure to replace "flag" with "01111110", i've mentioned it as "flag" for readability.
string flag = "flag";

void display(vector<string> arr) {
   for(int i=0; i<arr.size(); i++)
      cout<<"frame."<<i<<" :"<<arr[i]<<'\n';
}

string stuff (string frame){
   string bitStuff = flag;
   int n= frame.size(), c1=0;

   for(int i=0; i<n; i++){
      bitStuff+= frame[i];
      (frame[i]=='1')? c1++: c1=0;
      if(c1==5) bitStuff+= '0', c1=0;
   }
   return bitStuff+flag;
}

string deStuff(string stuffedframe){
   string DeStuff = "";
   int n=stuffedframe.size(), c1=0;

   for(int i=flag.size(); i<n-flag.size(); i++){
      DeStuff+= stuffedframe[i];
      (stuffedframe[i]=='1')? c1++: c1=0;
      if(c1==5) i++, c1=0;
   }
   return DeStuff;
}

int main(){
   fstream newfile;
   newfile.open("inputForBitStuffing.txt",ios::in);

   int frameSize;
   cout<<"Enter Frame Size: "; cin>>frameSize;

   if (newfile.is_open()){
      string s;
      while(getline(newfile, s)){
   // sender side
         show("\n\tSender Side");
         showp(" Original data",s);
         int n= s.size();

         // divide into frames
         vector<string> frames;
         for(int i=0; i<n; i+=frameSize){
            int len= min(frameSize, n-i);
            frames.push_back(s.substr(i, len));
         }
         
         // padding zeros to last frame
         int lastFrameIndex= frames.size()-1, paddedBits=0;
         while(frames[lastFrameIndex].size() < frameSize)
            frames[lastFrameIndex]+='0', paddedBits++;
         
         // display frames
         display(frames);
         
         // stuff each frame
         vector<string> StuffedFrames;
         for(string i: frames) 
            StuffedFrames.push_back(stuff(i));

         // display StuffedFrames
         show(" BitStuffed Frames:"), display(StuffedFrames);

   // receiver Side
         show("\n\tReceiver Side");
         showp("Number of padded bits", paddedBits);

         // display received bitStuffed Codes
         show(" Received BitStuffed Codes:"), display(StuffedFrames);
         
         vector<string> DeStuffedFrames;
         for(string i: StuffedFrames) 
            DeStuffedFrames.push_back(deStuff(i));

         // remove padding bits from last deStuff frame
         DeStuffedFrames[lastFrameIndex]= DeStuffedFrames[lastFrameIndex].substr(0, frameSize- paddedBits);

         // display deStuffed Frames
         show(" DeStuffed Frames:"), display(DeStuffedFrames);

      }
      newfile.close(); //close the file object.
   }
   else show("Error in opening file");
   return 0;
}

/*OUTPUT

Enter Frame Size: 8

        Sender Side
 Original data: 0100100111111010111
frame.0 :01001001
frame.1 :11111010
frame.2 :11100000
 BitStuffed Frames:
frame.0 :flag01001001flag
frame.1 :flag111110010flag
frame.2 :flag11100000flag

        Receiver Side
Number of padded bits: 5
 Received BitStuffed Codes:
frame.0 :flag01001001flag
frame.1 :flag111110010flag
frame.2 :flag11100000flag
 DeStuffed Frames:
frame.0 :01001001
frame.1 :11111010
frame.2 :111
*/