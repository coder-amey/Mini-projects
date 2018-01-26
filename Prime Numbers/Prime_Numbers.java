import java.io.IOException;
import java.util.Scanner;
import java.util.ArrayList;
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Amey
 */
public class Prime_Numbers
{
    public static Scanner jin = new Scanner(System.in);
    /**
     * @param A the command line arguments
     * @throws java.io.IOException
     */
    public static void main(String[] A)throws IOException
    {
        System.out.println (  "Enter limit for evaluation of prime numbers: " );
        long limit = jin.nextLong();
	Prime P = new Prime();
	P.evaluate(limit);
	quit();
    }

    static void quit() throws IOException
    {
	System.out.println (  "Do you want to quit the application? (Enter Y or N):" );
	char C = jin.next().charAt(0);
	switch (C)
	{
	case 'Y':
	case 'y':
	{
		System.exit(0);
	}
	break;
	case 'N':
	case'n':
	{
		String[] P = new String[] {""};
                main(P);
	}
	break;
	default:
	{
		System.out.println (  "Invalid response. Please try again." );
		quit();
	}
	}
    }    
};

class Prime
{
    private long n, i;
    private ArrayList <Long> P;
    
    Prime()
    {
    	n = 3;
	i = 0;
	P = new ArrayList<>();
        P.add(n-1);
    }

    public void evaluate(long limit)
    {
	int t = 1;
	for (int k = 0; k < (limit / 10000); k++)
	{
            for (int j = 3; j <= 10000; j += 2)
            {
		check(n);
		n += 2;
            }
            System.out.println (  "Pass " + t + ": " + t * 10000 + "." );
            t++;
	}
	for (; n <= limit - 3; n += 2)
        {
            check(n);
	}
	for (; n <= limit; n++)
	{
            check(n);
	}
	n--;
	display();
    }
    
    private void check(long n)
    {
	int x = 0;
	int  j = 0;
	while (j <= i)
	{
            if (n % P.get(j) == 0)
            {
                x = 0;
		break;
            }
            else
            {
                j++;
		x = 1;
            }
	}
	if (x == 1)
	{
            i++;
            P.add(n);
	}
    }

    private void display()
    {
    	System.out.println (  "List of prime numbers between 1 and " + n + ":" );
	for (int j = 0; j <= i; j++)
	{
		System.out.print (P.get(j) + "\t" );
	}
	System.out.println (  "\nTotal prime numbers found: " + (i + 1) );
    }
};