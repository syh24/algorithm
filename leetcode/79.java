import java.util.*;

class Solution {
    int[] g_nums;
    boolean[] visited = new boolean[11];
    List<List<Integer>> answer = new ArrayList<>();
    List<Integer> g_list = new ArrayList<>();
    public List<List<Integer>> subsets(int[] nums) {
        g_nums = nums;
        answer.add(new ArrayList<>());
        dfs(0);

        return answer;
    }

    public void dfs(int idx) {
        List<Integer> tt = new ArrayList<>();
        for (int i = idx; i < g_nums.length; i++) {
            if (visited[i]) continue;
            g_list.add(g_nums[i]);
            answer.add(new ArrayList<>(g_list));
            visited[i] = true;
            dfs(i + 1);
            visited[i] = false;
            g_list.remove(g_list.indexOf(g_nums[i]));
        }
    }
}