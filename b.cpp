template <typename T> 
struct Fenwick {
    int kMaxBit;
    vector < T > value;
    Fenwick (int n) : value(n+1, 0) {
        kMaxBit = 0;
        while((1<< (kMaxBit + 1)) < n) ++kMaxBit;
    }

    T getSum(int r) {
        T res = 0;
        for (; r > 0; r -= r & -r)
            res += value[r];
        
        return res;
    }

    void add(int pos, T val) {
        for (; pos < (int)value.size(); pos += pos & -pos)
            value[pos] += val;
    }

    int kthElement(int k) {
        int res = 0;
        for (int p = kMaxBit; p >= 0; --p) {
            if (res < (int)value.size() - (1<<p)) {
                if(value[(1<<p) + res] < k) {
                    res += (1<<p);
                    k -= value[res];
                }
            }
        }

        return ++res;
    }
};

//для создание Fenwick<data_type> d(sizeOfFenwick) 