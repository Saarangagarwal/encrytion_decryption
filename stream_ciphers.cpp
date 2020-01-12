#include<iostream>
#include<string>
#include<cctype>
#include<cassert>
#include<cmath>

#ifndef MARMOSET_TESTING
int main();
#endif
char *encode(char *plaintext, unsigned long key);
char *decode(char *ciphertext, unsigned long key);
//bool is_valid_ciphertext(char *str);
//bool is_valid_plaintext(char *str);


#ifndef MARMOSET_TESTING
int main()
{
	char str[]="Hello World!";
	char str1[]="K-;tL\"/CL2`s8@i`6Eb*,eSt]";
	encode(str, 51323);
	decode(str1, 150);
	return 0;
}
#endif

char *encode(char *plaintext, unsigned long key)
{
	//std::cout<<"HI";
	unsigned char S[256];
	//std::cout<<"Hello World!";
	for(std::size_t length{}; length<256; length++)
	{
		S[length]=length;
	}

	unsigned int i{}, j{}, k{};

	//std::cout<<"HI";

	//scrambling the entries of S
	for(std::size_t length{}; length<256; length++)
	{
		k=i%64;
		j=(j+S[i]+ ((key>>k)&1L))%256 ;
		unsigned int temp;
		temp=S[i];
		S[i]=S[j];
		S[j]=temp;
		i++;
		i=(i%256);
	}

	//std::cout<<"HI";
	//testing loop
	/*for(std::size_t cnt=0; cnt<256; cnt++)
	{
		std::cout<<int(S[cnt])<<std::endl;
	}*/

	//finding the length of the plain text
	unsigned int length=0;
	while(plaintext[length]!='\0')
	{
		length++;
	}
	//std::cout<<length;
	unsigned int div{}, integer=length, remaining{};

	if(length%4!=0)
	{
		div=length/4;
		integer=(4*div)+4;
		remaining=integer-length;
	}//put these at the top maybe as discussed in class
	//std::cout<<integer;

	//std::cout<<length<<std::endl;

	char cpy_plaintext[integer];

	for(int count=0; count<length; count++)
	{
		cpy_plaintext[count]=plaintext[count];
	}

	for(int count=length; count <integer; count++)
	{
		cpy_plaintext[count]='\0';
	}



	//testing loop

//std::cout<<cpy_plaintext<<std::endl;
	for(int count=0; count<integer; count ++)
	{
		//finding the value of R
		unsigned char temp{}, r{},R{};
		i++;
		i=(i%256);
		j=(j+S[i])%256;
		temp=S[i];
		S[i]=S[j];
		S[j]=temp;
		r=(S[i]+S[j])%256;
		R=S[r];

		//XORing each element with a different value of R
		cpy_plaintext[count]^=R;

	}
	//std::cout<<cpy_plaintext<<std::endl;

	unsigned int number{};
	char *cipher_arr=new char[(5*(integer/4))+1];

	int n=1, cipher_count{};

	//finding ascii armour of cpy_plaintext
	for(int count=0; count<integer; count+=4)
	{
		number=( (static_cast<unsigned char> (cpy_plaintext[count])<<24) +
				(static_cast<unsigned char> (cpy_plaintext[count+1])<<16)+
				(static_cast<unsigned char> (cpy_plaintext[count+2])<<8)+
				static_cast<unsigned char> (cpy_plaintext[count+3]));
		//std::cout<<number<<std::endl;
		cipher_count=(5*n)-1;
		for(int a =0 ; a<5;a++)
		{
			cipher_arr[cipher_count]='!'+(number%85);
			//std::cout<<cipher_arr[cipher_count];
			number/=85;
			//std::cout<<cipher_count<<std::endl;
			cipher_count--;
		}

		n++;
	}
	cipher_arr[(5*(integer/4))]='\0';

	//testing loop
		std::cout<<cipher_arr<<std::endl;




	return cipher_arr;
}

char *decode(char *ciphertext, unsigned long key)
{
	//std::cout<<std::endl;
	int count=0;
	//std::cout<<count<<std::endl;
	while(ciphertext[count]!='\0')
	{
		count++;
	}
	//std::cout<<count<<std::endl;//for debugging
	int no_elements=4*((count)/5);
	std::cout<<no_elements<<std::endl;//for debugging
	int no_blocks=no_elements/4;
	//std::cout<<no_blocks<<std::endl;//for debugging
	unsigned int n{};
	char *cipher=new char[no_elements+1]{};
	int cnt1{}, cnt2{}, cnt3{};

	for(std::size_t i{}; i<no_blocks;i++)
	{

		for(std::size_t i{}; i<5; i++)
		{
			ciphertext[cnt1]-='!';
			cnt1++;
			//std::cout<<cnt1<<std::endl;//for debugging
		}

		for(std::size_t i{}; i<5; i++)
		{
			n+=std::pow(85, 4-i)*ciphertext[cnt2];
			cnt2++;
			//std::cout<<cnt2<<std::endl;//for debugging
		}

		//std::cout<<n<<std::endl;//for debugging

		int shift=24;
				char temp{};
		for(std::size_t i=0; i<4;i++)
		{
			temp=int(n>>shift);
			shift-=8;
			temp=int(temp)&255;
			cipher[cnt3]=temp;
			cnt3++;
		}
		n=0;



	}
	//std::cout<<cipher;//for debugging

	//#####################################################################
	//std::cout<<"HI";
		unsigned char S[256];
		//std::cout<<"Hello World!";
		for(std::size_t length{}; length<256; length++)
		{
			S[length]=length;
		}

		unsigned int i{}, j{}, k{};

		//std::cout<<"HI";

		//scrambling the entries of S
		for(std::size_t length{}; length<256; length++)
		{
			k=i%64;
			j=(j+S[i]+ ((key>>k)&1L))%256 ;
			unsigned int temp;
			temp=S[i];
			S[i]=S[j];
			S[j]=temp;
			i++;
			i=(i%256);
		}
		for(int count=0; count<no_elements ; count ++)
		{
			//finding the value of R
			unsigned char temp{}, r{},R{};
			i++;
			i=(i%256);
			j=(j+S[i])%256;
			temp=S[i];
			S[i]=S[j];
			S[j]=temp;
			r=(S[i]+S[j])%256;
			R=S[r];

			//XORing each element with a different value of R
			cipher[count]^=R;
		}
		cipher[no_elements]='\0';
		std::cout<<cipher;

	     return cipher;
}

