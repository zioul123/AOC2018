import java.util.*;

class LinkedList {
    int val;
    LinkedList prev;
    LinkedList next;
    public LinkedList(LinkedList p, int x, LinkedList n) {
        prev = p;
        val = x;
        next = n;
    }
    public LinkedList(int x, LinkedList n) {
        prev = null;
        val = x;
        next = n;
    }
    public LinkedList(int x) {
        val = x;
        prev = (next = null);
    }
}

class Cll {
    LinkedList Current;

    public int Length;

    public Cll() {
        Length = 0;
        Current = null;
    }
    public void add(int val) {
        if (Length == 0) {
            Current = new LinkedList(val);
            Current.next = Current.prev = Current;
            Length++;
            return;
        }
        if (Length == 1) {
            LinkedList nL = new LinkedList(Current, val, Current);
            Current.next = Current.prev = nL;
            Current = nL;
            Length++;
            return;
        }
        
        LinkedList newList = new LinkedList(Current.next,
                                            val,
                                            Current.next.next);
        Current.next.next.prev = newList;
        Current.next.next = newList;
        Current = newList;
        Length++;
    }
    // Precondition: More than 7 things in this list
    public int pop() {
        for (int i = 0; i < 7; i++) {
            Current = Current.prev;
        }
        int res = Current.val;
        Current.prev.next = Current.next;
        Current.next.prev = Current.prev;
        Current = Current.next;
        Length--;
        return res;
    }
    public String toString() {
        StringBuilder sb = new StringBuilder(Length);
        LinkedList curr = Current;

        do {
            if (curr == Current) {
                sb.append("(" + curr.val + ") ");
            } else {
                sb.append(curr.val + " ");
            }
            curr = curr.next;
        } while (curr != Current);

        sb.deleteCharAt(sb.length()-1);
        return sb.toString();
    }
}

public class Day9p2 {

    public void run() {
        // Get input
        Scanner sc = new Scanner(System.in);
        String[] input = sc.nextLine().split(" ");
        int p, n;
        p = Integer.parseInt(input[0]); 
        n = Integer.parseInt(input[6]);

        Cll c = new Cll();
        long[] scoreOf = new long[p];

        for (int i = 0; i < n + 1; i++) {
            if (i % 23 != 0 || i == 0) {
                c.add(i);
            } else {
                scoreOf[i % p] += i;
                scoreOf[i % p] += c.pop();
            }
        }

        long highestScore = 0;
        for (int i = 0; i < p; i++) {
            System.out.println(Arrays.toString(scoreOf));
            if (scoreOf[i] > highestScore) 
                highestScore = scoreOf[i];
        }
        System.out.println(highestScore);
    }

    public static void main(String[] args) {
        Day9p2 d = new Day9p2();
        d.run();
    }
}