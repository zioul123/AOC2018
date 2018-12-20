import java.util.*;

public class Day2p2 {
    /** Driver class */
    public void run() {
        // Gather input
        Scanner sc = new Scanner(System.in);
        ArrayList<String> input = new ArrayList<>();
        while (sc.hasNext()) {
            input.add(sc.next());
        }

        // n^2 loop to find solution
        for (int i = 0; i < input.size(); i++) {
            for (int j = i+1; j < input.size(); j++) {
                if (isSimilar(input.get(i), input.get(j))) {
                    System.out.println(similarity(input.get(i), input.get(j)));
                    return;
                }
            }
        }
        System.out.println("Failed!");
    }

    /** Returns true if the two strings differ by 1 letter */
    private boolean isSimilar(String s1, String s2) {
        int differences = 0;
        for (int i = 0; i < s1.length(); i++) {
            if (s1.charAt(i) != s2.charAt(i)) {
                differences++;
            }
            if (differences > 1) return false;
        }
        return true;
    }

    /** Returns the common letters in the string */
    private String similarity(String s1, String s2) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < s1.length(); i++) {
            if (s1.charAt(i) == s2.charAt(i)) {
                sb.append("" + s1.charAt(i));
            }
        }
        return sb.toString();
    }

    public static void main(String[] args) {
        Day2p2 d = new Day2p2();
        d.run();
    }

}