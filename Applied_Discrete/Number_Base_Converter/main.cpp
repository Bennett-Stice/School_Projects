#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <unordered_map>
#include<string.h>


using namespace std;

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
/*
string decimalToBinary(long long int n) {
	vector<string> str;
	while (n > 0) {
		int rem;
		rem = n % 2;

		if (rem == 0)
			n = n / 2;
		else {
			n = n - 1;
			n = n / 2;
		}
		str.push_back(to_string(rem));
	}
	string bin;
	for (int i = str.size() - 1; i >-1;i--) {
		bin = bin + str[i];
	}
	return bin;
}
*/

int decimalToBinary(long long int n)
{
    int expon =0;
    int sum=0;
    while (n>0)
    {
        sum+=(n%2)*pow(10,expon);
        n=n/2;
        expon++;
    }

    return sum;
}

string base16ToBinary(string n) {
	char* nchr = new char[n.length()+1];
	string s;
	string binary;
	strcpy(nchr, n.c_str());
	for (long unsigned int i = 0; i < n.length(); i++)
		binary = binary + base16_Binary.find(nchr[i])->second;

	return binary;
}


long long int binaryToDecimal (long long int enterNum)
{
    int expon=0;
    int digit=1;
    int sum=0;
    while (enterNum!=0)
    {
        digit=enterNum%10;
        sum+=(digit*pow(2,expon));
        expon++;
        enterNum=enterNum/10;
    }
    return sum;
}
/*
void binaryToBase16(long long int enterNum)
{
    int iterations=0;
    long int holdNum=enterNum;
    if (enterNum==0)
    {
        iterations++;
    }
    while (enterNum!=0)
    {
        iterations++;
        enterNum=enterNum/10000;
    }

    char *array=new char[iterations];
    int sector;


    for (int i=0;i<iterations;i++)
    {
        sector=holdNum%10000;
        holdNum=holdNum/10000;

        case (sector==0):
            array[i]='0';
        case (sector==1):
            array[i]='1';
        case (sector==10):
            array[i]='2';
        case (sector==11):
            array[i]='3';
        case (sector==100):
            array[i]='4';
        case (sector==101):
            array[i]='5';
        case (sector==110):
            array[i]='6';
        case (sector==111):
            array[i]='7';
        case (sector==1000):
            array[i]='8';
        case (sector==1001):
            array[i]='9';
        case (sector==1010):
            array[i]='A';
        case (sector==1011):
            array[i]='B';
        case (sector==1100):
            array[i]='C';
        case (sector==1101):
            array[i]='D';
        case (sector==1110):
            array[i]='E';
        case (sector==1111):
            array[i]='F';
    }

    for (int i=(iterations-1);i>-1;i--)
    {
        cout<<array[i];
    }
    cout<<endl;

    return;
}*/

int main (int argc, char *argv[])
{

    cout<<"Binary Buffoons Conversion Program"<<endl<<"1) Convert base 10 to binary"<<endl<<"2) Convert binary to base 10"<<endl<<"3) Convert base 16 to binary"<<endl<<"4) Convert binary to base 16"<<endl<<"5) End Program"<<endl<<endl;

    cout<<"Enter the number of the operation that you would like to perform: ";
    int choice;
    cin>>choice;

    cout<<"Enter a number in the base that you picked: ";
    long long int num;
    string strNum;

    if (choice ==3)
    {
        cin>>strNum;
    }
    else
    {
        cin>>num;
    }

    while(choice!=5)
    {
        if (choice==1)
        {
            cout<<decimalToBinary(num)<<endl;
        }

        if (choice==2)
        {
            cout<<binaryToDecimal(num)<<endl;
        }

        if (choice==3)
        {
           cout<<base16ToBinary(strNum)<<endl;
        }
/*
        if (choice==4)
        {
            binaryToBase16(num);
        }
*/
        cout<<"Enter the number of the operation that you would like to perform: ";
        //int choice;
        cin>>choice;

        if (choice==5)
        {
            break;
        }

        cout<<"Enter a number in the base that you picked: ";

        if (choice ==3)
        {
        cin>>strNum;
        }
        else
        {
            cin>>num;
        }
    }

    cout<<"Happy Converting!!!"<<endl;



    return 0;
}
