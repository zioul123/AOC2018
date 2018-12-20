import java.util.*;

public class Day7p2 {
    boolean testing = false;
    public int charToInt(char c) {
        return c - 'A';
    }
    public char intToChar(int c) {
        return (char) ('A' + c);
    }

    public void run() {
        // Create edgelist
        ArrayList<LinkedList<Character>> fromTo = new ArrayList<>();
        for (int i = 0; i < (testing ? 6 :26); i++) {
            fromTo.add(new LinkedList<>());
        }

        // Get all input edges
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            // Step C must be finished before step A can begin.
            String[] input = sc.nextLine().split(" ");
            char from = input[1].charAt(0);
            char to = input[7].charAt(0);
            fromTo.get(charToInt(from)).add(to);
        }
        // Preview
        if (testing) for (LinkedList c : fromTo) System.out.println(c);
        for (LinkedList c : fromTo) System.out.println(c);

        // Create indegree
        int[] inDegree = new int[(testing ? 6 :26)];
        for (int from=0; from<(testing ? 6 :26); from++) {
            LinkedList<Character> to = fromTo.get(from);
            for (Character c : to) {
                inDegree[charToInt(c)]++;
            }
        }
        if (testing) System.out.println(Arrays.toString(inDegree));
        System.out.println(Arrays.toString(inDegree));
        // Initialize PQ
        PriorityQueue<Character> pq = new PriorityQueue<>();
        boolean[] visited = new boolean[(testing ? 6 :26)];
        String result = "";
        for (int i = 0; i < (testing ? 6 :26); i++) {
            if (inDegree[i] == 0) {
                pq.add(intToChar(i));
                visited[i] = true;
            }
        }

        int timeLeft[] = new int[(testing ? 2 : 5)];
        char lookingAt[] = new char[(testing ? 2 : 5)];
        for (int i = 0; i < timeLeft.length; i++) {
            timeLeft[i] = 0;
            lookingAt[i] = '.';
        }

        int currTime = 0;
        int lettersDeleted = 0;
        // Topo sort
        while (pq.size() != 0 || 
               lettersDeleted < (testing ? 6 : 26)) {
            System.out.println(currTime + ": " + pq);
            // Clear all the clocks first
            for (int i = 0; i < (testing ? 2 : 5); i++) {
                // This guy is free
                if (timeLeft[i] == 0) {
                    // Clear his last char if possible
                    if (lookingAt[i] != '.') {
                        char c = lookingAt[i];
                        result = result + c;
                        System.out.println(result);
                        lettersDeleted++;
                        // Add to the to
                        LinkedList<Character> to = fromTo.get(charToInt(c));
                        for (Character charTo : to) {
                            if (!visited[charToInt(charTo)]) {
                                inDegree[charToInt(charTo)]--;
                                if (inDegree[charToInt(charTo)] == 0) {
                                    visited[charToInt(charTo)] = true;
                                    pq.add(charTo);
                                }
                            }
                        }
                    }
                }
            }

            // Add jobs if possible
            for (int i = 0; i < (testing ? 2 : 5); i++) {
                System.out.println("Worker " + i +
                    ": " + lookingAt[i] + ": " + timeLeft[i]);
                // This guy is free
                if (timeLeft[i] == 0) {
                    // Give him a new thing if possible
                    if (pq.size() != 0) {
                        char c = pq.poll();
                        lookingAt[i] = c;   
                        timeLeft[i] = charToInt(c) + (testing ? 0 : 60);    
                        System.out.println("Worker " + i + " looks at " + c);
                    } else {
                        lookingAt[i] = '.';
                    }
                // Otherwise just tick the clock
                } else {
                    timeLeft[i]--;
                }
            }
            currTime++;
        }   
        System.out.println(result);
    }

    public static void main(String[] args) {
        Day7p2 d = new Day7p2();
        d.run();
    }
}