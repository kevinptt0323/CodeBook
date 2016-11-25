// SWERC 2015 - Text Processor
// Approach: Suffix Tree + Sliding Window. O(|S| + Q)
// Author: Miguel Oliveira
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct SuffixTree {
  struct Node {
    int l, r, par, link = -1, num_children = 0, next[26];

    Node(int l=0, int r=0, int par=-1) : l(l), r(r), par(par) {
      memset(next, -1, sizeof next); 
    }
    int Length()     { return r - l;       }
    int& get(char c) { return next[c-'a']; }

    void SetEdge(char c, int node_index) {
      if (next[c-'a'] != -1 && node_index == -1)
        --num_children;
      else if (next[c-'a'] == -1 && node_index != -1)
        ++num_children;
      next[c-'a'] = node_index;
    }
  };
  struct State {
    int v, pos;
    State(int v, int pos) : v(v), pos(pos)  {}
  };
  
  string text;
  queue<int> qleaves;
  vector<Node> tree;
  State ptr = State(0, 0);
  long long num_substrings = 0;

  SuffixTree(char* str) {
    text = string(str);
    tree.reserve(2 * text.size() + 1);
    tree.push_back(Node(0));
  }

  State Go(State st, int l, int r) {
    while (l < r) {
      if (st.pos == tree[st.v].Length()) {
        st = State(tree[st.v].get(text[l]), 0);
        if (st.v == -1)  
          return st;
      } else {
        if (text[ tree[st.v].l + st.pos ] != text[l])
          return State(-1, -1);
        if (r-l < tree[st.v].Length() - st.pos)
          return State(st.v, st.pos + r-l);
        l += tree[st.v].Length() - st.pos;
        st.pos = tree[st.v].Length();
      }
    }
    return st;
  }

  int Split(const State& st) {
    if (st.pos == tree[st.v].Length())
      return st.v;
    if (st.pos == 0)
      return tree[st.v].par;
    const Node& v = tree[st.v];
    int id = tree.size();
    tree.push_back(Node(v.l, v.l + st.pos, v.par));
    tree[v.par].SetEdge(text[v.l], id);
    tree[id].SetEdge(text[v.l + st.pos], st.v);
    tree[st.v].par = id;
    tree[st.v].l += st.pos;
    return id;
  }

  int GetLink(int v) {
    if (tree[v].link != -1) return tree[v].link;
    if (tree[v].par == -1)  return 0;
    int to = GetLink(tree[v].par);
    return tree[v].link = Split(Go(State(to,tree[to].Length()), tree[v].l + (tree[v].par==0), tree[v].r));
  }

  void TreeExtend(int pos) {
    int mid;
    num_substrings += qleaves.size();
    do {
      State nptr = Go(ptr, pos, pos+1);
      if (nptr.v != -1) {
        ptr = nptr;
        return;
      }
      mid = Split(ptr);
      int leaf = tree.size();
      num_substrings++;         // new leaf.
      qleaves.push(leaf);
      tree.push_back(Node(pos, text.size(), mid));
      tree[mid].SetEdge(text[pos], leaf);
      ptr.v = GetLink(mid);
      ptr.pos = tree[ptr.v].Length();
    } while (mid != 0);
  }

  void TreeDelete(int pos) {
    int leaf = qleaves.front();
    qleaves.pop();
    int par = tree[leaf].par;
    while (tree[leaf].num_children == 0) {
      if (ptr.v != leaf) {
        tree[par].SetEdge(text[tree[leaf].l], -1);
        num_substrings -= min(tree[leaf].r, pos) - tree[leaf].l;
        leaf = par;
        par = tree[leaf].par;
      } else {
        if (ptr.pos == min(tree[leaf].r,pos) - tree[leaf].l)
          break;
        int mid = Split(ptr);
        ptr.v = mid;
        num_substrings -= min(tree[leaf].r, pos) - tree[leaf].l;
        tree[mid].SetEdge(text[tree[leaf].l], -1);
        tree[leaf] = tree[mid];
        tree[tree[mid].par].SetEdge(text[tree[mid].l], leaf);
        tree.pop_back();
        break;
      }
    }
    if (leaf != 0 && tree[leaf].num_children == 0) { 
      qleaves.push(leaf);
      int to = (tree[leaf].par == 0) ? 0 : tree[tree[leaf].par].link;
      ptr = Go(State(to, tree[to].Length()), tree[leaf].l + (tree[leaf].par==0), tree[leaf].r);
      tree[leaf].l = pos - tree[leaf].Length();
      tree[leaf].r = text.size();
    }
  }
};

int main() {
  const int MAXN = 100100;
  long long ans_window[MAXN];
  char text[MAXN];
  int w, n, q;
  scanf("%s %d %d", text, &n, &w); 
  SuffixTree suffix_tree(text);
  for (int i = 1; i <= (int)suffix_tree.text.size(); ++i) {
    suffix_tree.TreeExtend(i-1);
    if (i >= w) {
      ans_window[i-w] = suffix_tree.num_substrings;
      suffix_tree.TreeDelete(i);
    }
  } 
  for (int i = 0; i < n; ++i) {
    scanf("%d", &q);
    printf("%lld\n", ans_window[q-1]);
  }
  return 0;
}
