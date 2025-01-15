#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <unordered_map>
#include<string.h>

/*
 * @author Dillon Geary
 * Halo Kanengiser
 * Simba Kutadzaushe
 * Pierre Minga
 * Njabulo Shabangu
 * Tony Hajdari
 * Bennett Stice
 * @date 10/13/23
 */


using namespace std;

//mapping from hexadecimal characters to their binary representation
unordered_map<char, string> base16_Binary{
	{'0', "0000"},
	{'1', "0001"},
	{'2', "0010"},
	{'3', "0011"},
	{'4', "0100"},
	{'5', "0101"},
	{'6', "0110"},
	{'7', "0111"},
	{'8', "1000"},
	{'9', "1001"},
	{'A', "1010"},
	{'B', "1011"},
	{'C', "1100"},
	{'D', "1101"},
	{'E', "1110"},
	{'F', "1111"}
};
string decimalToBinary(long int n) {
	vector<string> str;
	while (n > 0) { //loop untill the number beocmes zero
		int rem;
		rem = n % 2;
        n=n/2;
		str.push_back(to_string(rem));
	}
	string bin;
    // Loop backwards through the vector to build the binary string
	for (int i = str.size() - 1; i >-1;i--) {
		bin = bin + str[i];
	}
	return bin;
}

//convert a hexadecimal string to its binary representation
string base16ToBinary(string n) {
	char* nchr = new char[n.length()+1];
	string s;
	string binary;
	strcpy(nchr, n.c_str());
	for (int i = 0; i < n.length(); i++)
		binary = binary + base16_Binary.find(nchr[i])->second;

	return binary;
}

//convert a binary number to its decimal representation
int binaryToDecimal (long int enterNum)
{
    int expon=0;
    int digit=1;
    int sum=0;
// Convert binary number to decimal by successive divisions
    while (enterNum!=0)
    {
        digit=enterNum%10;
        sum+=(digit*pow(2,expon));
        expon++;
        enterNum=enterNum/10;
    }
    return sum;
}

void binaryToBase16(long int enterNum)
{
    int iterations=0;
    long int holdNum=enterNum;
// If the binary number is zero then increment the iteration count
    if (enterNum==0)
    {
        iterations++;
    }
    // Count the number of 4-bit sectors in the binary number
    while (enterNum!=0)
    {
        iterations++;
        enterNum=enterNum/10000;
    }

    char *array=new char[iterations];
    int sector;

 // Convert each 4-bit sector of the binary number to hexadecimal
    for (int i=0;i<iterations;i++)
    {
        sector=holdNum%10000;
        holdNum=holdNum/10000;
// Mapping each 4-bit binary value to its hexadecimal character
        if (sector==0)
        {
            array[i]='0';
        }
        if (sector==1)
        {
            array[i]='1';
        }
        if (sector==10)
        {
            array[i]='2';
        }
        if (sector==11)
        {
            array[i]='3';
        }
        if (sector==100)
        {
            array[i]='4';
        }
        if (sector==101)
        {
            array[i]='5';
        }
        if (sector==110)
        {
            array[i]='6';
        }
        if (sector==111)
        {
            array[i]='7';
        }
        if (sector==1000)
        {
            array[i]='8';
        }
        if (sector==1001)
        {
            array[i]='9';
        }
        if (sector==1010)
        {
            array[i]='A';
        }
        if (sector==1011)
        {
            array[i]='B';
        }
        if (sector==1100)
        {
            array[i]='C';
        }
        if (sector==1101)
        {
            array[i]='D';
        }
        if (sector==1110)
        {
            array[i]='E';
        }
        if (sector==1111)
        {
            array[i]='F';
        }
    }

// Printing out the hexadecimal number in reverse order
    for (int i=(iterations-1);i>-1;i--)
    {
        cout<<array[i];
    }
    cout<<endl;

    return;
}

int main (int argc, char *argv[])
{

    cout<<"Binary Buffoons Conversion Program"<<endl<<"1) Convert base 10 to binary"<<endl<<"2) Convert binary to base 10"<<endl<<"3) Convert base 16 to binary"<<endl<<"4) Convert binary to base 16"<<endl<<"5) End Program"<<endl<<endl;

    cout<<"Enter the number of the operation that you would like to perform: ";
    int choice;
    cin>>choice;

// Asking the user to input a number based on the chosen operation
    cout<<"Enter a number in the base that you picked: ";
    long int num;
    string strNum;

// If user wants to convert base 16 to binary, input is taken as a string.
// Else, input is taken as a number.
    if (choice ==3)
    {
        cin>>strNum;
    }
    else
    {
        cin>>num;
    }

// Continue looping until the user chooses 5
    while(choice!=5)
    {
// If choice is 1, convert the decimal number to binary and print the result
        if (choice==1)
        {
            cout<<decimalToBinary(num)<<endl;
        }
// If choice is 2, convert the binary number to decimal and print the result
        if (choice==2)
        {
            cout<<binaryToDecimal(num)<<endl;
        }
 // If choice is 3, convert the hexadecimal string to binary and print the result
        if (choice==3)
        {
           cout<<base16ToBinary(strNum)<<endl;
        }
// If choice is 4, convert the binary number to hexadecimal
        {
            binaryToBase16(num);
        }

 // Prompt the user for their next operation choice
        cout<<"Enter the number of the operation that you would like to perform: ";
 //int choice;
        cin>>choice;

 // If the user chooses to end the program, break out of the loop
        if (choice==5)
        {
            break;
        }

        cout<<"Enter a number in the base that you picked: ";

        if (choice ==3)
        {
        cin>>strNum; // Read hexadecimal string for choice 3
        }
        else
        {
            cin>>num; // Read a number for other choices
        }
    }

// End message after all operations are done
    cout<<"Happy Converting!!!"<<endl;



    return 0;
}
