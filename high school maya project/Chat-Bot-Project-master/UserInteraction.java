
/**
 * Write a description of class UserInput here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
import java.util.Scanner;

public class UserInteraction
{
    private static String response;
    public static void main() {
        response = "";
        while (response.equals("stop") == false){
            ParseKeyword p = new ParseKeyword();
            Scanner s = new Scanner(System.in);
            response = s.nextLine();
            p.keyToAnswer(response);
            //System.out.println("you said " + response);
        }
        System.out.println("ok, I'll shut up now");
    }
}
