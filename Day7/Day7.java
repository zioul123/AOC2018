import java.util.*;



public class Day7 {
    boolean testing = true;
    public int charToInt(char c) {
        return c - 'A';
    }
    public char intToChar(int c) {
        return (char) ('A' + c);
    }

    public void run() {
        // Create edgelist
        ArrayList<LinkedList<Character>> fromTo = new ArrayList<>();
        for (int i = 0; i < 26; i++) {
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

        // Create indegree
        int[] inDegree = new int[26];
        for (int from=0; from<26; from++) {
            LinkedList<Character> to = fromTo.get(from);
            for (Character c : to) {
                inDegree[charToInt(c)]++;
            }
        }
        if (testing) System.out.println(Arrays.toString(inDegree));

        // Initialize PQ
        PriorityQueue<Character> pq = new PriorityQueue<>();
        boolean[] visited = new boolean[26];
        String result = "";
        for (int i = 0; i < 26; i++) {
            if (inDegree[i] == 0) {
                pq.add(intToChar(i));
                visited[i] = true;
            }
        }
        
        // Topo sort
        while (pq.size() != 0) {
            char c = pq.poll();
            result = result + c;
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
            
        System.out.println(result);
    }

    public static void main(String[] args) {
        Day7 d = new Day7();
        d.run();
    }
}