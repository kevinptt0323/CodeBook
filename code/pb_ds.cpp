#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#include <ext/pb_ds/priority_queue.hpp>
typedef __gnu_pbds::priority_queue<T, greater<T>, pairing_heap_tag> Heap;
/*
 * method: push, pop, modify(iter, val), erase, join
 * point_iterator push(const_reference r_val)
 * pop
 * void modify(point_iterator it,const_reference r_new_val)
 * size_type erase_if(Pred prd) - return earsed number
 * void join(priority_queue &other)
 * void split(Pred prd, priority_queue &other) - move v into other if prd(v)
 *
 * tags: pairing_heap_tag, binary_heap_tag, binomial_heap_tag, rc_binomial_heap_tag, thin_heap_tag
 */

#include <ext/pb_ds/tree_policy.hpp>
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> RBTree;
typedef tree<int, null_type, less<int>, splay_tree_tag, tree_order_statistics_node_update> Splay;
/*
 * point_iterator find_by_order(size_type order) [0, size)
 * size_type order_of_key(const_key_reference r_key) - number of elements < r_key
 * void split(const_key_reference r_key, tree &other) - move elements > r_key
 */

#include<ext/pb_ds/trie_policy.hpp>
#include<ext/pb_ds/tag_and_trait.hpp>
typedef trie<string, null_type, trie_string_access_traits<>, pat_trie_tag, trie_prefix_search_node_update> Trie;
typedef trie<string, null_type, string_trie_e_access_traits, pat_trie_tag, trie_prefix_search_node_update> Trie;
/*
 * pair<Trie::iterator, bool> insert(string s) - iterator and is new string
 * pair<Trie::iterator, Trie::iterator> prefix_range(string pre)
 */

#include <ext/pb_ds/hash_policy.hpp>
typedef cc_hash_table<string, int> Hash;
typedef gp_hash_table<string, int> Hash;
