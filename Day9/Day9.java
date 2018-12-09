import java.util.*;

class Cll {
    public ArrayList<Integer> data;
    public int Length;
    public int Current;
    public int maxLength;

    public Cll(int n) {
        maxLength = n;
        data = new ArrayList<>(n);
        for (int i = 0; i < n; i++) 
            data.add(-1);
        Length = 0;
        Current = -1;
    }
    public void add(int val) {
        if (Length == 0) {
            data.set(0, val);
            Length++;
            Current = 0;
            return;
        }

        int location = ((Current + 1) % (Length)) + 1;
        for (int i = Length; i > location; i--) {
            data.set(i, data.get(i-1));
        }
        data.set(location, val);
        Length++;
        Current = location;
    }
    // Precondition: More than 7 things in this list
    public int pop() {
        int location = (Current - 7 < 0)
                        ? Current - 7 + Length 
                        : Current - 7;
        int res = data.get(location);
        for (int i = location; i < Length-1; i++) {
            data.set(i, data.get(i+1));
        }
        Current = location;
        Length--;
        return res;
    }
    public void setCurrent(int idx) {
        Current = idx;
    }
    public String toString() {
        StringBuilder sb = new StringBuilder(Length);
        for (int i = 0; i < Length; i++) {
            if (i == Current) sb.append("("+data.get(i)+") ");
            else sb.append(data.get(i) + " ");
        }
        sb.deleteCharAt(sb.length()-1);
        return sb.toString();
    }
}

public class Day9 {

    public void run() {
        // Get input
        Scanner sc = new Scanner(System.in);
        String[] input = sc.nextLine().split(" ");
        int p, n;
        p = Integer.parseInt(input[0]); 
        n = Integer.parseInt(input[6]);

        Cll c = new Cll(n + 1);
        int[] scoreOf = new int[p];

        for (int i = 0; i < n + 1; i++) {
            if (i % 23 != 0 || i == 0) {
                c.add(i);
            } else {
                scoreOf[i % p] += i;
                scoreOf[i % p] += c.pop();
            }
        }

        int highestScore = 0;
        for (int i = 0; i < p; i++) {
            if (scoreOf[i] > highestScore) 
                highestScore = scoreOf[i];
        }
        System.out.println(highestScore);
    }

    public static void main(String[] args) {
        Day9 d = new Day9();
        d.run();
    }
}