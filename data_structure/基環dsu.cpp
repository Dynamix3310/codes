//允許連通兩次的dsu，圖會是基環森林
struct dsu {
    struct node {
        int boss;
        int sz = 1;
        bool cyc = false;
    };
    vector<node> tree;
    int n;

    void init(int N) {
        n = N;
        tree.assign(n + 10, node());
        for (int i = 0; i <= n; i++) tree[i].boss = i; // 支援 0-indexed 與 1-indexed
    }

    int boss(int x) {
        if (tree[x].boss == x) return x;
        return tree[x].boss = boss(tree[x].boss);
    }

    bool merge(int u, int v) {
        int U = boss(u);
        int V = boss(v);
        if (U == V) {
            if (!tree[U].cyc) {
                tree[U].cyc = true;
                return true;
            }
            return false;
        }
        if (tree[U].cyc && tree[V].cyc) return false;

        // 啟發式合併：將小樹掛到大樹下
        if (tree[U].sz > tree[V].sz) swap(U, V);
        tree[U].boss = V;
        tree[V].sz += tree[U].sz;
        tree[V].cyc |= tree[U].cyc; // 解耦狀態轉移與樹的合併方向
        return true;
    }
};