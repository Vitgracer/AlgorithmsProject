#include <stdlib.h>
#include <iostream>

static int maxKey = 1000;
typedef int Key;

class Item {
private:
	Key keyval;
	float info;
public:
	Item() : keyval(maxKey), info(0) {}
	Key key() const { return keyval; }
	int null() const { return keyval == maxKey; }
	void rand() { 
		keyval = 100 * ::rand() / RAND_MAX; 
		info = 1.0 * ::rand() / RAND_MAX; 
	}
};

class ItemHash {
private:
	char keyval;
	float info;
public:
	ItemHash() : keyval(0), info(0) {}
	char key() const { return keyval; }
	int null() const { return keyval == 0; }
	void rand() {
		keyval = 100 * ::rand() / RAND_MAX;
		info = 1.0 * ::rand() / RAND_MAX;
	}
};


/////////////////////////////////////////////////
//--- SYMBOL-TABLE (based on array) (S 448)-----
//------------ distributed search --------------
/////////////////////////////////////////////////
template <class Item, class Key>
class STdistributed {
private:
	Item nullItem;
	Item* st;
	int M;
	int size;
public:
	STdistributed(int maxN) 
		: M(nullItem.key())
		, size(maxN)
		, st(new Item[size]) { 
		for (int i = 0; i < size; i++) {
			st[i] = Item();
		}
	}
	
	int count() const {
		int n = 0; 
		for (int i = 0; i < size; i++) {
			if (!st[i].null()) n++;
		}
		return n;
	}
	void insert(Item x) { st[x.key()] = x; }
	Item search(Key v) const { return st[v]; }
	void remove(Item x) { st[x.key()] = nullItem; }
	Item select(int k) {
		for (int i = 0; i < size; i++) {
			if (!st[i].null())
				if (k-- == 0) return st[i];
		}
		return nullItem;
	}
};

/////////////////////////////////////////////////
//--- SYMBOL-TABLE (based on array) (S 450)-----
//--------sequental search, ordered array-------
/////////////////////////////////////////////////
template <class Item, class Key>
class STsequental {
private:
	Item nullItem;
	Item* st;
	int N;
	Item binarySearch(int l, int r, Key v) {
		if (l > r) return nullItem;
		int m = (l + r) / 2;
		if (v == st[m].key()) return st[m];
		if (l == r) return nullItem;
		if (v < st[m].key())
			return binarySearch(0, m - 1, v);
		else
			return binarySearch(m + 1, r, v);

	}
public:
	STsequental(int maxN)
		: N(0)
		, st(new Item[maxN + 1]) {
		for (int i = 0; i < N; i++) {
			st[i] = Item();
		}
	}

	int count() const { return N; }
	void insert(Item x) { 
		int i = N++;
		Key v = x.key();
		while (i > 0 && v < st[i - 1].key()) {
			st[i] = st[i - 1];
			i--;
		}
		st[i] = x;
	}

	Item search(Key v) const { 
		for (int i = 0; i < N; i++) 
			if (v == st[i].key()) return st[i];
		return nullItem;
	}

	Item Bsearch(Key v) {
		return binarySearch(0, N - 1, v);
	}
};

///////////////////////////////////////////////////////
//--- SYMBOL-TABLE (based on linked list) (S 452)-----
//------------------unordered array-------------------
///////////////////////////////////////////////////////
template <class Item, class Key>
class STll {
private:
	Item nullItem;
	struct node {
		Item item;
		node* next;

		node (Item inItem, node* inNext) 
			: item(inItem)
			, next(inNext) {}
	};
	typedef node* link;

	int N;
	link head;

	Item searchR(link t, Key v) {
		if (t == 0) return nullItem;
		if (t->item.key() == v) return t->item;
		return searchR(t->next, v);
	}
public:
	STll(int maxN)
		: N(0)
		, head(0) { }

	int count() const { return N; }
	void insert(Item x) {
		head = new node(x, head);
		N++;
	}

	Item search(Key v) {
		return searchR(head, v);
	}
};

/////////////////////////////////////////////////
//--- BINARY-SEARCH-TREE (BST) (S 462) ---------
/////////////////////////////////////////////////
template <class Item, class Key> 
class BST {
private:
	struct node {
		Item item;
		node* l;
		node* r;

		node(Item inItem)
			: item(inItem)
			, l(0)
			, r(0) {}
	};
	typedef node* link;
	link head;
	Item nullitem;
	Item searchR(link treeNode, Key inputKey) {
		if (treeNode == 0) return nullitem;
		Key currentKey = treeNode->item.key();
		if (currentKey == inputKey) return treeNode->item;
		if (inputKey < currentKey)
			return searchR(treeNode->l, inputKey);
		else
			return searchR(treeNode->r, inputKey);
	}
	void insertR(link& treeNode, Item inputItem) {
		if (treeNode == 0) {
			treeNode = new node(inputItem);
			return;
		}
		Key currentKey = treeNode->item.key();
		if (inputItem.key() < currentKey)
			return insertR(treeNode->l, inputItem);
		else
			return insertR(treeNode->r, inputItem);
	}

	void showR(link treenode) {
		if (treenode == 0) return;
		showR(treenode->l);
		std::cout << treenode->item.key() << "\t";
		showR(treenode->r);
	}
	void rotR(link& treeNode) {
		link x = treeNode->l;
		treeNode->l = x->r;
		x->r = treeNode;
		treeNode = x;
	}

	void rotL(link& treeNode) {
		link x = treeNode->r;
		treeNode->r = x->l;
		x->l = treeNode;
		treeNode = x;
	}

	void insertToVertex(link& treeNode, Item inputItem) {
		if (treeNode == 0) {
			treeNode = new node(inputItem);
			return;
		}
		Key currentKey = treeNode->item.key();
		if (inputItem.key() < currentKey) {
			insertToVertex(treeNode->l, inputItem);
			rotR(treeNode);
		}
		else {
			insertToVertex(treeNode->r, inputItem);
			rotL(treeNode);
		}
	}

	link joinR(link a, link b) {
		if (b == 0) return a;
		if (a == 0) return b;
		insertToVertex(b, a->item);
		b->l = joinR(a->l, b->l);
		b->r = joinR(a->r, b->r);
		delete a;
		return b;
	}
public:
	BST() : head(0) {}
	Item search(Key inputKey) { return searchR(head, inputKey); }
	void insert(Item inputItem) { insertR(head, inputItem); }
	void insertV(Item inputItem) { insertToVertex(head, inputItem); }
	void show() { showR(head); }
	void join(BST<Item, Key>& b) { head = joinR(head, b.head); }
};

/////////////////////////////////////////////////
//------------- SKIP-LIST (S 521) ---------------
/////////////////////////////////////////////////
template <class Item> 
class SkipList {
private:
	struct node {
		Item item;
		node** next;
		int sz;

		node(Item inItem, int inSz)
			: item(inItem)
			, sz(inSz)
			, next(new node*[inSz]) {
			for (int i = 0; i < inSz; i++) {
				next[i] = 0;
			}
		}
	};
	typedef node* link;
	link head;
	Item nullitem;
	int lgN;
	
	Item searchR(link linkNode, Key v, int k) {
		if (linkNode == 0) return nullitem;
		if (v == linkNode->item.key()) return linkNode->item;
		link levelLink = linkNode->next[k];
		if ((levelLink == 0) || (v < levelLink.key())) {
			if (k == 0) return nullitem;
			return searchR(linkNode, v, k - 1);
		}
		return searchR(levelLink, v, k - 1);
	}
public:
	SkipList(int lgnMax) 
		: head(new node(nullitem, lgnMax))
		, lgN(0) {}
	Item search(Key v) { return searchR(head, v, lgN); }
};

///////////////////////////////////////////////////////////
//--------------------- HASH-FUNCTION ---------------------
///////////////////////////////////////////////////////////
int hash(char* v, int M) {
	int h = 0; 
	int a = 127;
	for (; *v != 0; v++) {
		h = (a * h + *v) % M;
	}
	return h;
}

///////////////////////////////////////////////////////////
//------------- HASH-TABLE (LINEAR PROBING) ---------------
///////////////////////////////////////////////////////////
template <class Item, class Key>
class HashTable {
private:
	Item* st;
	int N, M;
	Item nullitem;
public:
	HashTable(int maxN) 
		: N(0)
		, M(2 * maxN)
		, st(new Item[M]) {
		for (int i = 0; i < M; i++) st[i] = nullitem;
	}
	
	int count() const { return N; }
	void insert(Item item) {
		char tempVal = item.key();
		int i = hash(&tempVal, M);
		while (!st[i].null()) i = (i + 1) % M;
		st[i] = item;
		N++;
	}

	Item search(Key v) {
		int i = hash(&v, M);
		while (!st[i].null()) {
			if (v == st[i].key()) return st[i];
			else i = (i + 1) % M;
		}
		return nullitem;
	}
};