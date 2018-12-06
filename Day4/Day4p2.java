import java.util.*;
import java.text.SimpleDateFormat;
import java.text.ParseException;

public class Day4p2 {
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

        // Iterate through the inputs and add up total days per minute
        HashMap<Integer, Guard> guards = new HashMap<>();
        int currentGuard = -1, sleepSince = -1;
        for (DateStringPair dsp : inputs) {
            String[] s = dsp.string.split(" ");
            String firstWord = s[2];
            switch (firstWord) {
            // Begin shift
            case "Guard":
                currentGuard = Integer.parseInt(s[3].substring(1, s[3].length()));
                if (!guards.containsKey(currentGuard)) {
                    guards.put(currentGuard, new Guard(currentGuard));
                }
                break;
            case "falls":
                sleepSince = dsp.date.getMinutes();
                break;
            case "wakes":
                int sleepTill = dsp.date.getMinutes();
                for (int i = sleepSince; i < sleepTill; i++) {
                    guards.get(currentGuard).sleepFor[i]++;
                }
                break;
            default:
                System.out.println("Error! Invalid input.");
                break;
            }
        }

        Iterator<Map.Entry<Integer, Guard>> it = guards.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry<Integer, Guard> entry = it.next();
            System.out.println(entry.getKey() + ": " + Arrays.toString(entry.getValue().sleepFor));
            System.out.println("Most: " + entry.getValue().sleptForAtMost() + ", Minute: " + entry.getValue().longestMinute());
        }

        // Check which gurad slept most minutes
        int sleepingGuard = -1; int mostSleep = Integer.MIN_VALUE;
        it = guards.entrySet().iterator();
        //Iterator<Map.Entry<Integer, Guard>> it = guards.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry<Integer, Guard> entry = it.next();
            if (entry.getValue().sleptForAtMost() > mostSleep) {
                mostSleep = entry.getValue().sleptForAtMost();
                sleepingGuard = entry.getKey();
            }
        }
        int sleepingMin = guards.get(sleepingGuard).longestMinute();

        System.out.println("Guard: " + sleepingGuard + ", Sleeping Min: " + sleepingMin 
                + ", Answer: " + (sleepingGuard * sleepingMin));
    }
    
    public static void main(String[] args) {
        Day4p2 d = new Day4p2();
        d.run();
    }
}

class Guard {
    public int id;
    public int[] sleepFor = new int[60];
    public Guard(int id) { this.id = id; }
    public int sleptForAtMost() {
        int result = -1;
        for (int i = 0; i < 60; i++) {
            if (sleepFor[i] > result) result = sleepFor[i];
        }
        return result;
    }
    public int longestMinute() {
        int result = -1, minute = -1;;
        for (int i = 0; i < 60; i++) {
            if (sleepFor[i] > result) {
                result = sleepFor[i];
                minute = i;
            }
        }
        return minute;
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