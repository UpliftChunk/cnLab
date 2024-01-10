#include <bits/stdc++.h>
using namespace std;
  
#define show(var)  cout<<(var)<<' '
#define showp(i,v) cout<<(i)<<" :"<<v<<'\n'

char XOR(char a, char b){
    return (a==b)?'0':'1';
}

string generateCRC(string dividend, string divisor){
    int i=0, n=dividend.size(), k=divisor.size();
    while(i<= n-k){
        for(int c=0; c<k; c++)
            dividend[c+i]= XOR(dividend[c+i], divisor[c]);
        
        while(i<n && dividend[i]=='0') i++;
    }
    return dividend.substr(n-k+1, k-1);
}

bool isPoly(string s){
   for(char i: s) 
    if(i!='1' && i!='0') return true;
   return false;
}

string polyToBinary(string poly){
   stringstream input(poly), nums;
   char c;
   while(input>>c)
      (isdigit(c))? nums<<c: nums<<" ";
   
   int tmp, result=0;
   while(nums>>tmp) 
        result|= (1<<tmp);
   
   char binaryString[32];
   itoa(result, binaryString, 2);

   return binaryString;
}

int main() {
	string divisor, dataword;
	show("Enter divisor : "); getline(cin,divisor);
	show("Enter dataword: "); getline(cin,dataword);

   // check if input is in polynomial form
   if(isPoly(divisor))  divisor  = polyToBinary(divisor);
   if(isPoly(dataword)) dataword = polyToBinary(dataword);


//sender side	
	show("\tSender Side:");
	showp("\ndataword", dataword);
	showp(  "divisor ",  divisor);
	
	showp("Number of redundancy bits", divisor.size()-1);
	string paddedInput= dataword;
	for(int i=1; i<divisor.size(); i++)
	    paddedInput+='0';
	
	string crc = generateCRC(paddedInput, divisor);
	showp("Generated crc", crc);
	
	string codeword= dataword + crc;
	showp("codeword", codeword);
	
	
//receiver side
	show("\tReceiver Side:");
	showp("\nReceived codeword", codeword);
	
	crc = generateCRC(codeword, divisor);
	showp("Generated crc", crc);
	
	int flag=1;
	for(char c: crc) if(c=='1') flag=0; 
	
	if(flag) show("Syndrome is zero, accepted!\n");
	else show("Syndrome is not zero, not accepted!\n");
	
	return 0;
}

// OUTPUT:
/*
Enter divisor :  x^3 + x^1 + x^0
Enter dataword:  11010011101100

        Sender Side:
dataword:11010011101100
divisor:1011
Number of redundancy bits:3
Generated crc:100
codeword:11010011101100100
        Receiver Side:
Received codeword:11010011101100100
Generated crc:000
Syndrome is zero, accepted!
*/
