import java.util.Scanner;

public class Solution {

    public static void main(String args[]) throws Exception {
        Scanner scanner = new Scanner(System.in);
        StringBuilder str = new StringBuilder();
        while (scanner.hasNextLine()) {
            str.append(scanner.nextLine()).append(" ");
        }

        scanner.close();
        throw new Exception(str.toString());
    }
}
