import java.util.*;

public class Day5p2 {
    public void run() {
        Scanner sc = new Scanner(System.in);
        String preinput = sc.next();

        Deque<Character> s = new LinkedList<Character>();
        int[] charScores = new int[26];
        char[] chars = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r',
        's','t','u','v','w','x','y','z' };

        for (int cha = 0; cha < 26; cha++) {
            char selectedChar = chars[cha];
            String input = filter(preinput, selectedChar);
            for (int i = 0; i < input.length(); i++) {
                char c = input.charAt(i);
                // Empty stack
                if (s.size() == 0) {
                    s.offerLast(c);
                // same as last
                } else if (Character.toLowerCase(s.peekLast()) == Character.toLowerCase(c)) {
                    char c2 = s.peekLast();
                    // Same case
                    if ((Character.isLowerCase(c2) && Character.isLowerCase(c)) 
                        || (!Character.isLowerCase(c2) && !Character.isLowerCase(c))) {
                        s.offerLast(c);
                    // Different case
                    } else {
                        s.pollLast();
                    }
                // Different from last
                } else {
                    s.offerLast(c);
                }
            }
            System.out.println("Char: " + chars[cha] + ", " + s.size());
            charScores[cha] = s.size();
            s.clear();
        }
        int min = 50000000; char cha = '!';
        for (int i = 0 ; i < 26; i++) {
            if (charScores[i] < min) {
                min = charScores[i];
                cha = chars[i];
            }
        }
        System.out.println(cha);
    }

    // c is lowercase
    String filter(String s, char c) {
        StringBuilder sb = new StringBuilder();
        for (int i=0; i < s.length(); i++) {
            if (Character.toLowerCase(s.charAt(i)) != c) {
                sb.append("" + s.charAt(i));
            }
        }
        return sb.toString();
    }
    public static void main(String[] args) {
        Day5p2 d = new Day5p2();
        d.run();
    }
}