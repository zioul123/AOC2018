import java.util.*;
import java.text.SimpleDateFormat;
import java.text.ParseException;

public class Day4 {
    // Used to parse the input
    SimpleDateFormat parser = new SimpleDateFormat("[yyyy-MM-dd HH:mm]");

    public void run() {
        ArrayList<DateStringPair> inputs = new ArrayList<>();

        // Read all input and store it
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            // e.g.: "[1518-04-09 00:01] Guard #3407 begins shift"
            String s = sc.nextLine();  
            try {
                Date date = parser.parse(s.substring(0, 18));
                inputs.add(new DateStringPair(date, s));

            } catch (ParseException e) {
                System.err.println("Failed to parse date: " + s);
                e.printStackTrace();
            }
        }
        // Sort inputs
        Collections.sort(inputs);

        // Add up all the sleeping hours per guard
        HashMap<Integer, Integer> hoursSleeping = new HashMap<>();
        int currentGuard = -1; int sleepSince = -1;
        for (DateStringPair dsp : inputs) {
            String[] s = dsp.string.split(" ");
            // <[1518-04-09>, <00:01]>, <Guard>, <#3407>, <begins>, <shift>
            String firstWord = s[2];
            switch (firstWord) {
            // Begin shift
            case "Guard":
                currentGuard = Integer.parseInt(s[3].substring(1, s[3].length()));
                break;
            case "falls":
                sleepSince = dsp.date.getMinutes();
                break;
            case "wakes":
                int sleepFor = dsp.date.getMinutes() - sleepSince;
                if (hoursSleeping.containsKey(currentGuard)) {
                    hoursSleeping.put(currentGuard, 
                                      hoursSleeping.get(currentGuard) + sleepFor);
                } else {
                    hoursSleeping.put(currentGuard,
                                      sleepFor);  
                }
                break;
            default:
                System.out.println("Error! Invalid input.");
                break;
            }
        }

        // Get the guard who slept the longest
        int longestMins = Integer.MIN_VALUE, longestGuard = -1;
        Iterator<Map.Entry<Integer, Integer>> it = hoursSleeping.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry<Integer, Integer> entry = it.next();
            if (entry.getValue() > longestMins) {
                longestMins = entry.getValue();
                longestGuard = entry.getKey();
            }
        }
        System.out.println(longestGuard + ", " + longestMins);

        // Iterate through the inputs and add up total days per minute
        currentGuard = -1; sleepSince = -1;
        int[] sleepFor = new int[60];
        for (DateStringPair dsp : inputs) {
            String[] s = dsp.string.split(" ");
            String firstWord = s[2];
            switch (firstWord) {
            // Begin shift
            case "Guard":
                currentGuard = Integer.parseInt(s[3].substring(1, s[3].length()));
                break;
            case "falls":
                if (currentGuard != longestGuard) continue;
                sleepSince = dsp.date.getMinutes();
                break;
            case "wakes":
                if (currentGuard != longestGuard) continue;
                int sleepTill = dsp.date.getMinutes();
                for (int i = sleepSince; i < sleepTill; i++) {
                    sleepFor[i]++;
                }
                break;
            default:
                System.out.println("Error! Invalid input.");
                break;
            }
        }

        // Check which minute he spent the most sleeping in
        int sleepingMin = -1; int mostSleep = Integer.MIN_VALUE;
        for (int i = 0; i < 60; i++) {
            if (sleepFor[i] > mostSleep) {
                mostSleep = sleepFor[i];
                sleepingMin = i;
            }
        }

        System.out.println("Guard: " + longestGuard + ", Sleeping Min: " + sleepingMin 
                + ", Answer: " + (longestGuard * sleepingMin));
    }
    
    public static void main(String[] args) {
        Day4 d = new Day4();
        d.run();
    }
}

// Data structure to hold a date and string
class DateStringPair implements Comparable<DateStringPair> {
    public Date date;
    public String string;
    public DateStringPair(Date date, String string) {
        this.date = date; this.string = string;
    }
    public int compareTo(DateStringPair d) {
        return date.compareTo(d.date);
    }
    public String toString() {
        return date + ", " + string;
    }
}