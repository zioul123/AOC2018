import java.util.*;

public class Day2 {
    public void run() {
        Scanner sc = new Scanner(System.in);
        ArrayList<String> input = new ArrayList<>();
        while (sc.hasNext()) {
            input.add(sc.next());
        }

        int hasTwo = count(input, 2);
        int hasThree = count(input, 3);

        System.out.println("Result: " + hasTwo * hasThree);
    }

    private int count(ArrayList<String> in, int total) {
        int totalRes = 0;
        for (String s : in) {
            int res = 0;
            HashMap<Character, Integer> count = new HashMap<>();
            for (int i = 0; i < s.length(); i++) {
                char c = s.charAt(i);
                if (!count.containsKey(c)) {
                    count.put(c, 1);
                    continue;
                }

                if (count.get(c) == total-1) {
                    res++;
                } else if (count.get(c) == total) {
                    res--;
                } 
                count.put(c, count.get(c) + 1);

            }
            
            if (res > 0) totalRes++;
        }
        return totalRes;
    }

    public static void main(String[] args) {
        Day2 d = new Day2();
        d.run();
    }
}