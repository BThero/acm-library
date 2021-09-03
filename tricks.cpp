#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T, typename P> using ordered_map = tree<T, P, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// мощная хэш функция
struct chash {
    const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
    static unsigned long long hash_f(unsigned long long x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    static unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
    int operator()(int x) const { return hash_f(x)^RANDOM; }
};

// unordered_map но быстрее
gp_hash_table<int, int> table;
gp_hash_table<int, int, chash> table2;

/*
   rnd.seed(x); 
   cout << rnd64() << endl;
   cout << urd(rnd) << endl;
 */

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
mt19937_64 rnd64(chrono::system_clock::now().time_since_epoch().count());
uniform_real_distribution<> urd(0.0, 1.0);
uniform_int_distribution<> uid(1, 6);

// вправо, вниз, влево, вверх
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

// ход конем
int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
