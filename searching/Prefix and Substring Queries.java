import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Collection;
import java.io.IOException;
import java.util.Comparator;
import java.util.NoSuchElementException;
import java.io.InputStream;
/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class Main {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        PrefixAndSubstringQueries solver = new PrefixAndSubstringQueries();
        solver.solve(1, in, out);
        out.close();
    }
    static class PrefixAndSubstringQueries {
        int MAXN = 200005;
        int lgN = 21;
        PrintWriter out;
        InputReader in;
        int sqrt;
        EzIntArrayList[] tree = new EzIntArrayList[MAXN];
        int[][] anc = new int[lgN][MAXN];
        int[] dist = new int[MAXN];
        EzIntArrayList dfs_order = new EzIntArrayList();
        int[] lps;
        int timer = 0;
        int[] in_t = new int[MAXN];
        int[] out_t = new int[MAXN];
        int[] segtree = new int[2 * MAXN];
        final Comparator<Tuple> com = new Comparator<Tuple>() {
            public int compare(Tuple t1, Tuple t2) {
                int x = t1.l / sqrt, y = t2.l / sqrt;
                if (x != y)
                    return Integer.compare(x, y);
                if (t1.r == t2.r)
                    return Integer.compare(t1.l, t2.l);
                if (x % 2 == 1)
                    return Integer.compare(t2.r, t1.r);
                else
                    return Integer.compare(t1.r, t2.r);
            }
        };
        int[] computeLPSArray(char[] pat, int M) {
            int[] lps = new int[M];
            int len = 0;
            lps[0] = 0;
            int i = 1;
            while (i < M) {
                if (pat[i] == pat[len]) {
                    len++;
                    lps[i] = len;
                    i++;
                } else {
                    if (len != 0) {
                        len = lps[len - 1];
                    } else {
                        lps[i] = 0;
                        i++;
                    }
                }
            }
            return lps;
        }
        int lca_of(int u, int v) {
            if (dist[u] < dist[v]) {
                int t = u;
                u = v;
                v = t;
            }
            int diff = dist[u] - dist[v];
            for (int i = lgN - 1; i >= 0; i--) {
                if (((1 << i) & diff) != 0) {
                    u = anc[i][u];
                }
            }
            if (u == v)
                return u;
            for (int i = lgN - 1; i >= 0; i--) {
                if (anc[i][u] > 0 && anc[i][u] != anc[i][v]) {
                    u = anc[i][u];
                    v = anc[i][v];
                }
            }
            return anc[0][u];
        }
        void dfs(int v) {
            dfs_order.add(v);
            in_t[v] = timer++;
            for (int i = 0; i < tree[v].size; i++) {
                int u = tree[v].get(i);
                dfs(u);
            }
            out_t[v] = timer - 1;
        }
        void segtree_update(int ind, int val, int n) {
            segtree[ind += n] += val;
            for (; ind > 1; ind >>= 1)
                segtree[ind >> 1] = (segtree[ind] + segtree[ind ^ 1]);
        }
        int segtree_query(int l, int r, int n) {
            int res = 0;
            for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
                if ((l & 1) == 1)
                    res += segtree[l++];
                if ((r & 1) == 1)
                    res += segtree[--r];
            }
            return res;
        }
        void add(int idx, int n) {
            segtree_update(dfs_order.get(idx), 1, n);
        }
        void remove(int idx, int n) {
            segtree_update(dfs_order.get(idx), -1, n);
        }
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            this.out = out;
            this.in = in;
            int n = ni(), q = ni();
            sqrt = (int) (Math.sqrt(n + q));
            String st = n();
            StringBuilder str = new StringBuilder(st);
            int[][] query = new int[q][];
            int cnt = 0;
            int i = 0;
            for (i = 0; i < MAXN; i++)
                tree[i] = new EzIntArrayList();
            for (i = 0; i < q; i++) {
                int type = ni();
                if (type == 1) {
                    query[i] = new int[1];
                    query[i][0] = type;
                    str.append(n());
                } else if (type == 2) {
                    query[i] = new int[3];
                    query[i][0] = type;
                    query[i][1] = ni();
                    query[i][2] = ni();
                } else if (type == 3) {
                    query[i] = new int[4];
                    query[i][0] = type;
                    query[i][1] = ni();
                    query[i][2] = ni();
                    query[i][3] = ni();
                    cnt++;
                }
            }
            st = str.toString();
            n = st.length();
            lps = computeLPSArray(st.toCharArray(), st.length());
            for (i = 0; i < n; i++) {
                tree[lps[i]].add(i + 1);
                anc[0][i + 1] = lps[i];
                dist[i + 1] = dist[lps[i]] + 1;
                for (int j = 1; j < lgN; j++)
                    anc[j][i + 1] = anc[j - 1][anc[j - 1][i + 1]];
            }
            dfs(0);
            Tuple[] type_3_query = new Tuple[cnt];
            int c = 0;
            int[] ans = new int[q];
            for (i = 0; i < q; i++) {
                if (query[i][0] == 3)
                    type_3_query[c++] = new Tuple(in_t[query[i][1]], out_t[query[i][1]], query[i][2] + query[i][1] - 1, query[i][3], i);
                else if (query[i][0] == 2)
                    ans[i] = lca_of(query[i][1], query[i][2]);
            }
            Arrays.sort(type_3_query, com);
            int cur_l = 0, cur_r = -1;
            for (Tuple curr : type_3_query) {
                //pn(curr.l +" "+curr.r +" "+curr.x +" "+curr.y +" "+curr.id);
                while (cur_l > curr.l) {
                    cur_l--;
                    add(cur_l, MAXN);
                }
                while (cur_r < curr.r) {
                    cur_r++;
                    add(cur_r, MAXN);
                }
                while (cur_l < curr.l) {
                    remove(cur_l, MAXN);
                    cur_l++;
                }
                while (cur_r > curr.r) {
                    remove(cur_r, MAXN);
                    cur_r--;
                }
                ans[curr.id] = segtree_query(curr.x, curr.y + 1, MAXN);
            }
            for (i = 0; i < q; i++) {
                if (query[i][0] != 1)
                    pn(ans[i]);
            }
        }
        String n() {
            return in.next();
        }
        int ni() {
            return in.nextInt();
        }
        void pn(long zx) {
            out.println(zx);
        }
        class EzIntArrayList implements EzIntList, PrefixAndSubstringQueries.EzIntStack {
            private static final int DEFAULT_CAPACITY = 10;
            private static final double ENLARGE_SCALE = 2.0;
            private static final int HASHCODE_INITIAL_VALUE = 0x811c9dc5;
            private static final int HASHCODE_MULTIPLIER = 0x01000193;
            private int[] array;
            private int size;
            public EzIntArrayList() {
                this(DEFAULT_CAPACITY);
            }
            public EzIntArrayList(int capacity) {
                if (capacity < 0) {
                    throw new IllegalArgumentException("Capacity must be non-negative");
                }
                array = new int[capacity];
                size = 0;
            }
            public EzIntArrayList(PrefixAndSubstringQueries.EzIntCollection collection) {
                size = collection.size();
                array = new int[size];
                int i = 0;
                for (PrefixAndSubstringQueries.EzIntIterator iterator = collection.iterator(); iterator.hasNext(); ) {
                    array[i++] = iterator.next();
                }
            }
            public EzIntArrayList(int[] srcArray) {
                size = srcArray.length;
                array = new int[size];
                System.arraycopy(srcArray, 0, array, 0, size);
            }
            public EzIntArrayList(Collection<Integer> javaCollection) {
                size = javaCollection.size();
                array = new int[size];
                int i = 0;
                for (int element : javaCollection) {
                    array[i++] = element;
                }
            }
            public int size() {
                return size;
            }
            public PrefixAndSubstringQueries.EzIntIterator iterator() {
                return new EzIntArrayListIterator();
            }
            public boolean add(int element) {
                if (size == array.length) {
                    enlarge();
                }
                array[size++] = element;
                return true;
            }
            public int get(int index) {
                if (index < 0 || index >= size) {
                    throw new IndexOutOfBoundsException("Index " + index + " is out of range, size = " + size);
                }
                return array[index];
            }
            private void enlarge() {
                int newSize = Math.max(size + 1, (int) (size * ENLARGE_SCALE));
                int[] newArray = new int[newSize];
                System.arraycopy(array, 0, newArray, 0, size);
                array = newArray;
            }
            public boolean equals(Object o) {
                if (this == o) return true;
                if (o == null || getClass() != o.getClass()) return false;
                EzIntArrayList that = (EzIntArrayList) o;
                if (size != that.size) {
                    return false;
                }
                for (int i = 0; i < size; i++) {
                    if (array[i] != that.array[i]) {
                        return false;
                    }
                }
                return true;
            }
            public int hashCode() {
                int hash = HASHCODE_INITIAL_VALUE;
                for (int i = 0; i < size; i++) {
                    hash = (hash ^ PrefixAndSubstringQueries.PrimitiveHashCalculator.getHash(array[i])) * HASHCODE_MULTIPLIER;
                }
                return hash;
            }
            public String toString() {
                StringBuilder sb = new StringBuilder();
                sb.append('[');
                for (int i = 0; i < size; i++) {
                    sb.append(array[i]);
                    if (i < size - 1) {
                        sb.append(", ");
                    }
                }
                sb.append(']');
                return sb.toString();
            }
            private class EzIntArrayListIterator implements PrefixAndSubstringQueries.EzIntIterator {
                private int curIndex = 0;
                public boolean hasNext() {
                    return curIndex < size;
                }
                public int next() {
                    if (curIndex == size) {
                        throw new NoSuchElementException("Iterator doesn't have more elements");
                    }
                    return array[curIndex++];
                }
            }
        }
        interface EzIntCollection {
            int size();
            PrefixAndSubstringQueries.EzIntIterator iterator();
            boolean equals(Object object);
            int hashCode();
            String toString();
        }
        interface EzIntIterator {
            boolean hasNext();
            int next();
        }
        interface EzIntStack extends PrefixAndSubstringQueries.EzIntCollection {
            int size();
            PrefixAndSubstringQueries.EzIntIterator iterator();
            boolean equals(Object object);
            int hashCode();
            String toString();
        }
        static class PrimitiveHashCalculator {
            private PrimitiveHashCalculator() {
            }
            public static int getHash(int x) {
                return x;
            }
        }
        class Tuple {
            int x;
            int y;
            int id;
            int l;
            int r;
            Tuple(int a, int b, int c, int d, int e) {
                l = a;
                r = b;
                x = c;
                y = d;
                id = e;
            }
        }
    }
    static class InputReader {
        private InputStream stream;
        private byte[] buf = new byte[1024];
        private int curChar;
        private int numChars;
        public InputReader(InputStream stream) {
            this.stream = stream;
        }
        public int read() {
            if (numChars == -1)
                throw new UnknownError();
            if (curChar >= numChars) {
                curChar = 0;
                try {
                    numChars = stream.read(buf);
                } catch (IOException e) {
                    throw new UnknownError();
                }
                if (numChars <= 0)
                    return -1;
            }
            return buf[curChar++];
        }
        public int nextInt() {
            return Integer.parseInt(next());
        }
        public String next() {
            int c = read();
            while (isSpaceChar(c))
                c = read();
            StringBuffer res = new StringBuffer();
            do {
                res.appendCodePoint(c);
                c = read();
            } while (!isSpaceChar(c));
            return res.toString();
        }
        private boolean isSpaceChar(int c) {
            return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
        }
    }
    static interface EzIntList {
    }
}
