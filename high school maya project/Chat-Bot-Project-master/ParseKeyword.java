
/**
 * Write a description of class ParseKeyword here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
import java.util.*;
import java.util.Random;

public class ParseKeyword
{
    private List<String[]> keywords = new ArrayList<String[]>();
    private List<String[]> answer = new ArrayList<String[]>();
    
    //put a space before and after the keywords, so it only looks for the word itself, and not contained in another word
    private String[] whereBathroom = {"bathroom", "toilet", "restroom", "pee"};
    private String[] whereBathroomAns = {"find it yourself", "hold it together","just don't drink water"};
     
    private String[] hello = {"hi", "hello", "hey"};
    private String[] helloAns = {"hi, how's it going?", "what do you want?", "hi, how are you?"};
    
    private String[] moody = {"stop", "don't", "nay"};
    private String[] moodyAns = {"what's wrong?", "feeling moody?"};

    private String[] no = {"no"};
    private String[] noAns = {"alright my bad", "nevermind then", "alright, I'll stop then"};

    private String[] bell = {"bell", "rings"};
    private String[] bellAns = {"check it on the website", "what per?"};

    private String[] per = {"1"};
    private String[] perAns = {"8:00"};
    
    private String[] per2 = {"2"};
    private String[] per2Ans = {"8:56"};
    
    private String[] per3 = {"3"};
    private String[] per3Ans = {"9:56"};
    
    private String[] per4 = {"4"};
    private String[] per4Ans = {"10:52"};
    
    private String[] per5 = {"5"};
    private String[] per5Ans = {"12:44"};
    
    private String[] per6 = {"6"};
    private String[] per6Ans = {"13:40"};
    
    private String[] per7 = {"7"};
    private String[] per7Ans = {"14:36"};
    
    private String[] lunch = {"lunch"};
    private String[] lunchAns = {"12:09"};
    
    private String[] club = {"club", "clubs"};
    private String[] clubAns = {"2SERVE", "Fighting Game Club", "Helping Hand", "Improv Club", "HUB Club", "Internship Club", "Magic Club", "Video Production Club", "Speech & Debate Club", "Math Club", "Girls Who Code", "Engineering Club", "Enviro Tech Club", "Economics Club", "Dublin High School Art Club"};
    public ParseKeyword () {
        //add in keywords in order from most important, to least important
        //this way if you have two key words in the same sentence, one will overwrite the other
        keywords.add(moody);
        keywords.add(whereBathroom);
        keywords.add(hello);
        keywords.add(bell);
        keywords.add(per);
        keywords.add(per2);
        keywords.add(per3);
        keywords.add(per4);
        keywords.add(per5);
        keywords.add(per6);
        keywords.add(per7);
        keywords.add(lunch);
        keywords.add(club);
        //make sure the answer array matches up with the index of the keywords array
        answer.add(moodyAns);
        answer.add(whereBathroomAns);
        answer.add(helloAns);
        answer.add(bellAns);
        answer.add(perAns);
        answer.add(per2Ans);
        answer.add(per3Ans);
        answer.add(per4Ans);
        answer.add(per5Ans);
        answer.add(per6Ans);
        answer.add(per7Ans);
        answer.add(lunchAns);
        answer.add(clubAns);
    }
    
    
    public void keyToAnswer (String response) {
        boolean foundKey = false;
        //init with a negative number so it wouldn't display a result if there was no match
        int answerArrIndex = -1; 
        Random rand = new Random();
        for (int i = this.keywords.size() - 1; i >= 0; i--) {
            String[] key = this.keywords.get(i);
            for (int j = 0; j < key.length ; j++) {
                if (response.toLowerCase().contains(key[j])) {
                    foundKey = true;
                    answerArrIndex = i;
                }
            }
        }
        if (foundKey && (answerArrIndex != -1)){
            String[] ans = this.answer.get(answerArrIndex);
            int r = rand.nextInt(ans.length);
            System.out.println(ans[r]);
        }
        else {
            System.out.println("sorry, I don't understand what you mean");
        }
    }
}
