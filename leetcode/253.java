class Solution {
    public int minMeetingRooms(int[][] intervals) {
        PriorityQueue<Integer[]> pq = new PriorityQueue<>((a, b) -> a[1] - b[1]);
        Arrays.sort(intervals, Comparator.comparing(x -> x[0]));

        for (int[] interval : intervals) {
            if (pq.isEmpty()) {
                pq.add(new Integer[]{interval[0], interval[1]});
                continue;
            }
            Integer[] cur = pq.poll();
            if (cur[1] > interval[0]) {
                pq.add(cur);
                pq.add(new Integer[]{interval[0], interval[1]});
            } else {
                pq.add(new Integer[]{interval[0], interval[1]});
            }
        }


        return pq.size();
    }
}