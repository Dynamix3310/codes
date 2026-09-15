struct sparse_table {
    vector<vector<long long int>> table;
    int n;

    void init(int N, const vector<long long int> &a) {
        n = N;
        if (n <= 0) return;
        int k = __lg(n);
        table.assign(k + 1, vector<long long int>(n));
        table[0] = a;

        for (int j = 1; j <= k; j++) {
            int step = 1 << (j - 1);
            for (int i = 0; i + (1 << j) <= n; i++) {
                table[j][i] = min(table[j - 1][i], table[j - 1][i + step]);
            }
        }
    }

    // 需確保 0 <= l <= r < n
    long long int query(int l, int r) {
        int j = __lg(r - l + 1);
        return min(table[j][l], table[j][r - (1 << j) + 1]);
    }
};