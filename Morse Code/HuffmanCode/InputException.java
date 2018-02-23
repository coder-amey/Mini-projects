package HuffmanCode;

/**
 *
 * @author Amey
 */
public class InputException extends Exception
{
    public String Message;
    public InputException(String S)
    {
        Message = S;
    }
}
