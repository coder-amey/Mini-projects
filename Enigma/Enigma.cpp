#include<iostream>
#include<fstream>
#include<string>
using namespace std;
char choice;
void Flow();
void exit();
void main();

class Cipher
{
private:
	char Reference[97], Key[97];
	string PT, CT;
	int EK, P;

	//Cipher key generator.
	void KeyGen(int n)
	{
		char C;
		for (int i = 0; i < 96; i++)
		{
			C = Key[i];
			Key[i] = Key[n % 96];
			Key[n % 96] = C;
			n++;
		}
	}

	//Plain text reversor.
	void reverse(int n)
	{
		char C;
		for (int i = 0; i < (n / 2); i++)
		{
			C = PT[i];
			PT[i] = PT[(n - 1) - i];
			PT[(n - 1) - i] = C;
		}
	}

	//Key formulator (overloaded).
	void formulate(int &n)
	{
		char Arr[] = { "0123456789" };
		EK = 0;
		for (int i = (n - 6); i < n; i++)
		{
			switch (CT[i])
			{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			{
				for (int j = 0; j <= 9; j++)
				{
					if (CT[i] == Arr[j])
					{
						EK = (10 * EK) + j;
					}
				}
			}
			break;
			default:
			{
				cout << "Cipher text entered is invalid. Please try again.\n\n";
				main();
			}
			}
		}
		n = n - 6;
		CT.resize(n);
	}
	void formulate()
	{
		char A[7], Arr[] = { "0123456789" };
		int x = EK;
		for (int i = 5; i >= 0; i--)
		{
			A[i] = Arr[(x % 10)];
			x = x / 10;
		}
		A[6] = '\0';
		CT.append(A);
	}

	//Convertor with periodic shifter.
	void convert(string &S, int n, string &T, char *A, char *B)
	{
		int Pass = P;
		KeyGen(Pass);
		int j = 0;
		T.resize(n);
		for (int i = 0; i < n; i++)
		{
			T[i] = translate(S[i], A, B);
			j++;
			if (j != 5)
				continue;
			else
			{
				if (Pass > 10000)
				{
					Pass--;
				}
				else
				{
					Pass++;
				}
				KeyGen(Pass);
				j = 0;
			}
		}
	}

	//Translator.
	char translate(char c, char *A, char *B)
	{
		int i = 0;
		while (i < 96)
		{
			if (c == A[i])
				break;
			else
				i++;
		}
		return (B[i]);
	}

public:
	//Constructor.
	Cipher()
	{
		strcpy_s(Reference, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ \n0123456789=+-*/,.?!;:'\"<>()[]{}\\|_&^%$#@~`");
		strcpy_s(Key, "9~eI/0k])<4_u;-tdmvNBWZCbTjq5V'U[zya1R>`+#@P2({i^of38HKF,n=s\"XGJ*c7r&|\\ALhE\n.!YS:}w$6Qp%x lgDMO?");
	}

	//Ciphering functions.
	void Encrypt(string &S, int &Pass)
	{
		PT = S;
		P = Pass;
		EK = rand();
		int n = PT.length();
		reverse(n);
		KeyGen(EK);
		convert(PT, n, CT, Reference, Key);
		formulate();
		cout << "\nCipher text:\n" << CT << "\nPassnumber: " << P << "\n\n";
		ofstream F;
		F.open("Cipher Text.txt", ios::trunc);
		F << CT;
		F.close();
	}

	void Decrypt(string &S, int &Pass)
	{
		CT = S;
		P = Pass;
		int n = CT.length();
		if (n < 6)
		{
			cout << "Cipher text entered is invalid. Please try again.\n\n";
		}
		else
		{
			formulate(n);
			KeyGen(EK);
			convert(CT, n, PT, Key, Reference);
			reverse(n);
			cout << "\nPlain text:\n" << PT << "\nPassnumber: " << P << "\n\n";
			ofstream F;
			F.open("Plain Text.txt", ios::trunc);
			F << PT;
			F.close();
		}
	}
};

//Main function.
void main()
{
	cout << "\t\t\tENIGMA!\n\n";
	Flow();
	cin.ignore();
	int Pass;
	cout << "Enter Passnumber (upto 9 digits): ";
	cin >> Pass;
	ifstream F;
	string S;
	Cipher X;
	switch (choice)
	{
	case '1':
	{
		F.open("Plain Text.txt");
		S.assign((istreambuf_iterator<char>(F)), (istreambuf_iterator<char>()));
		F.close();
		X.Encrypt(S, Pass);
	}
	break;
	case '2':
	{
		F.open("Cipher Text.txt");
		S.assign((istreambuf_iterator<char>(F)), (istreambuf_iterator<char>()));
		F.close();
		X.Decrypt(S, Pass);
	}
	break;
	}
	exit();
}

//Screen controller.
void Flow()
{
	cout << "Please make a choice. (Enter 1,2 or 3):\n1) Encrypt text.\t2) Decrypt text.\t3) Exit.\n";
	cin >> choice;
	switch (choice)
	{
	case '1':
	{
		cout << "Enter the plain text in the 'Plain Text.txt' file and press Enter to continue.\n";
		cin.ignore();
	}
	break;
	case '2':
	{
		cout << "Enter the cipher text in the 'Cipher Text.txt' file and press Enter to continue.\n";
		cin.ignore();
	}
	break;
	case '3':
	{
		exit();
	}
	break;
	default:
	{
		cout << "Invalid response. Please try again.\n\n";
		main();
	}
	}
}

//Exit
void exit()
{
	cout << "Do you want to exit the application? (Enter Y or N):\n";
	cin >> choice;
	switch (choice)
	{
	case 'Y':
	case 'y':
	{
		exit(0);
	}
	break;
	case 'N':
	case'n':
	{
		cout << "\n\n";
		main();
	}
	break;
	default:
	{
		cout << "Invalid response. Please try again.\n";
		exit();
	}
	}
}