package HuffmanCode;

import BinaryTree.*;

public class Morse
{
    private BTree M;
    public Morse()
    {
        M = new BTree();
        char A[] = {'E', 'T', 'I', 'A', 'N', 'M', 'S', 'U', 'R', 'W', 'D', 'K', 'G', 'O', 'H', 'V', 'F', '$', 'L', '$', 'P', 'J', 'B', 'X', 'C', 'Y', 'Z', 'Q'};
        M.generate(A);
    }
    
    public String encode(String S) throws InputException
    {
        char P[] = S.toUpperCase().toCharArray();
        for(int i = 0; i < P.length; i++)
        {
            if((P[i] < 'A') || (P[i] > 'Z'))
            {
                if((P[i] != ' ') && (P[i] != '\n'))
                {
                    throw new InputException("Error: Invalid character(s) in the English input.");
                }
            }
        }
        S = new String();
        for(int i = 0; i < P.length; i++)
        {
            if(P[i] == '\n')
            {
                S = S + P[i];
                continue;
            }
            
            S = S + M.trace(P[i]);
            if((i != (P.length - 1)) && (P[i] != ' '))
                S = S + " ";
        }
        return(S);
    }
    
    public String decode (String S) throws InputException
    {
        char P[] = S.toCharArray();
        int i;
        for(i = 0; i < P.length; i++)
        {
            if((P[i] != ' ') && (P[i] != '.') && (P[i] != '-') && (P[i] != '\n'))
            {
                throw new InputException("Error: Invalid character(s) in the Morse Code input.");
            }
        }
        S = new String();
        i = 0;
        while(i < P.length)
        {
            boolean flag = false;
            String T = new String();
            while((i < P.length) && (P[i] != ' '))
            {
                if(P[i] == '\n')
                {
                    flag = true;
                    break;
                }
                T = T + P[i++];
            }
            i++;
            if(T.isEmpty())
                T = " ";
            S = S + M.traverse(T.toCharArray());
            if(flag)
                S = S +"\n";
        }
        return(S);
    }
}