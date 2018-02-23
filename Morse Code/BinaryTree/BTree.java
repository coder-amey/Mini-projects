package BinaryTree;

/**
 *
 * @author Amey
 */

class Node
{
    private char C;
    protected Node P, L, R;
    
    protected Node(char C, Node P)
    {
        this.C = C;
        this.P = P;
        this.L = this.R = null;
    }
    protected char value()
    {
        return (C);
    }
}

class Table
{
    private Node List[];
    private int I, N;
    private char C[];
    
    Table()
    {
        I = -1;
        N = 0;
        List = new Node[29];
        C = new char[29];
    }
    
    public void add(Node N, char c)
    {
        List[++I] = N;
        C[I] = c;
    }
    
    public Node next()
    {
        return (List[++N]);
    }
    
    public Node search(char Q)
    {
        for(int i = 0; i <= I; i++)
        {
            if(Q == C[i])
                return(List[i]);
        }
        return(null);
    }
}


public class BTree extends Node
{
    private Table T;
    public BTree()
    {
        super(' ', null);
        T = new Table();
        T.add(this, ' ');        
    }
    
    public void generate (char A[])
    {
        Node N = this;
        for(int i = 0; i < A.length; i++)
        {
            if(i%2 == 0)
            {
                N.L = new Node(A[i],N);
                T.add(N.L, A[i]);
            }
            else
            {
                N.R = new Node(A[i],N);
                T.add(N.R, A[i]);
                N = T.next();
            }
        }
    }
    
    public String trace(char C)
    {
        String t = new String();
        Node N = T.search(C);
        if(N == null)
        {
            System.out.println("Unknown symbol encountered!");
            return("$");
        }
        else
        {
            if(N.P == null)
            {;
                t = " ";
            }
            while(N.P != null)
            {
                if(N.P.L == N)
                    t = t + '.';
                else
                    t = t + '-';
                N = N.P;
            }
            String S = new String();
            int n = t.length();
            for(int i = n - 1; i >= 0; i--)
            {
                S = S + t.charAt(i);
            }    
            return(S);
        }
    }
    
    public char traverse(char[] S)
    {
        Node N = this;
        if(S[0] == ' ')
            return(' ');
        else
        {
            for(int i = 0; i < S.length; i++)
            {
                if(N == null)
                {
                    System.out.println("Unknown symbol encountered!");
                    return('$');
                }
                if(S[i] == '.')
                    N = N.L;
                else if (S[i] == '-')
                    N = N.R;
                else
                {
                    System.out.println("Unknown symbol encountered!");
                    return('$');
                }
            }
            return(N.value());
        }
    }
}