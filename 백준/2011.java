package spring.test;

import java.util.*;
import java.io.*;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String n = br.readLine();

        int[] dp = new int[n.length() + 1];
        dp[0] = 1;

        if (n.charAt(0) == '0') {
            System.out.println(0);
            return;
        }

        for (int i = 1; i < n.length(); i++) {

            if (n.charAt(i - 1) - '0' == 2) {
                if (n.charAt(i) - '0' > 0 && n.charAt(i) - '0' <= 6) {
                    if (i == 1) {
                        dp[i] = 2;
                    } else {
                        dp[i] = (dp[i-2] + dp[i-1]) % 1000000;
                    }
                } else if (n.charAt(i) - '0' == 0) {
                    if (i == 1) {
                        dp[i] = 1;
                    } else {
                        dp[i] = dp[i-2];
                    }
                } else {
                    dp[i] = (dp[i-1]);
                }
            } else if (n.charAt(i - 1) - '0' == 1){
                if (n.charAt(i) - '0' == 0) {
                    if (i == 1) {
                        dp[i] = 1;
                    } else {
                        dp[i] = dp[i-2];
                    }
                } else {
                    if (i == 1) {
                        dp[i] = 2;
                    } else {
                        dp[i] = (dp[i-2] + dp[i-1]) % 1000000;
                    }
                }
            } else {
                if (n.charAt(i) - '0' == 0) {
                    System.out.println(0);
                    return;
                }
                dp[i] = (dp[i-1]);
            }
        }

        System.out.println(dp[n.length()-1]);
    }
}
