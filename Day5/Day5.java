import java.util.*;

public class Day5 {
    public void run() {
        Scanner sc = new Scanner(System.in);
        String input = sc.next();

        Deque<Character> s = new LinkedList<Character>();

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
        System.out.println(s.size());
    }

    public static void main(String[] args) {
        Day5 d = new Day5();
        d.run();
    }
}