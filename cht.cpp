/*
- Сразу чекает случай когда слоупы равны
- Функция get() отвечает бинпоиском
- Функция get_ptr() отвечает указателем
- Можно передать компаратор, если нужен минимум less<ll>(), если максимум greater<ll>()
- Если ищем минимум нужно добавлять линии по возрастанию слоуп, а запросы для двух указателей по возрастанию x
- Если ищем максимум нужно добавлять линии по убыванию слоуп, а запросы для двух указателей по убыванию x
- Можно поменять функцию good() если точности double не хватает
- Можно вызвать reserve(n) чтобы ускорить вектор
*/

struct Line {
    ll k, b;
    Line() : k(0), b(0) {}
    Line(ll _k, ll _b) : k(_k), b(_b) {}

    ll get(ll x) {
        return k * x + b;
    }

    double inter(Line &o) {
        return (double)(b - o.b) / (o.k - k);
    }
};

bool good(Line a, Line b, Line c) {
    return a.inter(b) < b.inter(c);
}

struct CHT : public vector<Line> {
    int ptr;
    function<bool(ll, ll)> cmp;
    CHT() : ptr(0), cmp(greater<ll>()) {}
    CHT(function<bool(ll, ll)> _cmp) : ptr(0), cmp(_cmp) {}

    void add(Line l) {
        if (!empty() && l.k == back().k) {
            if (cmp(l.b, back().b)) {
                pop_back();
            }
            else {
                return;
            }
        }

        while (size() >= 2 && !good(end()[-2], end()[-1], l)) {
            pop_back();
        }

        pb(l);
    }     

    ll get_ptr(ll x) {
        while (ptr + 1 < (int)size() && cmp(at(ptr + 1).get(x), at(ptr).get(x))) {
            ptr++;
        }

        ptr = min(ptr, (int)size() - 1);
        return at(ptr).get(x);
    }

    ll get(ll x) {
        int l = 0, r = (int)size() - 1;

        while (l != r) {
            int m = (l + r) >> 1;

            if (cmp(at(m).get(x), at(m + 1).get(x))) {
                r = m;
            }
            else {
                l = m + 1;
            }
        }

        return at(l).get(x);
    }
};

struct CHT_dynamic : public vector<CHT> {
    function<bool(ll, ll)> cmp;
    CHT_dynamic() : cmp(greater<ll>()) {}
    CHT_dynamic(function<bool(ll, ll)> _cmp) : cmp(_cmp) {} 

    CHT merge(CHT a, CHT b) {
        CHT res(cmp);
        int j = 0;

        for (int i = 0; i < sz(a); i++) {
            while (j < sz(b) && cmp(a[i].k, b[j].k)) {
                res.add(b[j++]);
            }

            res.add(a[i]);
        }

        while (j < sz(b)) {
            res.add(b[j++]);
        }

        return res;
    }

    void add(Line l) {
        CHT cur(cmp);
        cur.add(l);

        for (CHT &ex : *this) {
            if (ex.empty()) {
                ex.swap(cur);
                break;
            }

            cur = merge(cur, ex);
            ex.clear();
        }

        if (!cur.empty()) {
            push_back(cur);
        }  
    }

    ll get(ll x) {
        ll ret = (cmp(0, 1) ? LLONG_MAX : LLONG_MIN);

        for (CHT &cur : *this) {
            if (!cur.empty()) {
                ret = min(ret, cur.get(x), cmp);
            }
        }

        return ret;
    }
};
