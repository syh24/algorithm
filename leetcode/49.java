class Solution {
    public List<List<String>> groupAnagrams(String[] strs) {
        List<List<String>> list = new ArrayList<>();
        Map<String, List> m = new HashMap<>();

        for (String s : strs) {
            char[] ar = s.toCharArray();
            Arrays.sort(ar);
            String key = String.valueOf(ar);
            if (!m.containsKey(key)) {
                m.put(key, new ArrayList());
            }
            m.get(key).add(s);
        }

        for(String k : m.keySet()) {
            list.add(m.get(k));
        }

        return list;
    }
}