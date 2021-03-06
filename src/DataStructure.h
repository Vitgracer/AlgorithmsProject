template<class Item> 
void exch(Item& A, Item&B) {
	Item t = A;
	A = B;
	B = t;
}
/////////////////////////
// ---- LINKED-LIST -----
/////////////////////////
struct node {
	int item;
	node* next;

	node(int i, node* n);
};
typedef node* link;
typedef link Node;

namespace li {
	void deleteNode(Node n);
	void insert(Node src, Node ins);
	link reverse(link x);
	Node next(Node n);
	int item(Node n);
	void show(Node n);
}

/////////////////////////
// ------ STACK --------
/////////////////////////
template <class Item>
class Stack {
private:
	Item* data;
	int N;
public:
	Stack(int maxSize) : data(new Item[maxSize]), N(0) {};
	int empty() const { return N == 0; }
	void push(Item item) { data[N++] = item; }
	Item pop() { return data[--N]; }
	int getSize() { return N; }
};

////////////////////////////////////////////
// ------ STACK based on linked list--------
////////////////////////////////////////////
template <class Item>
class llStack {
private:
	link head;
public:
	llStack() : head(0) {}
	int empty() const { return head == 0; }
	void push(Item item) { head = new node(item, head); }
	Item pop() {
		using namespace li;
		Item v = item(head);
		link t = next(head);
		delete head;
		head = t;
		return v;
	}
};

/////////////////////////
// ------ QUEUE --------
/////////////////////////
template<class Item> 
class Queue {
private:
	link head, tail;
public:
	Queue() : head(0) {}
	int empty() const { return head == 0; }
	void put(Item item) { 
		link t = tail;
		tail = new node(item, 0);
		if (head == 0) {
			head = tail;
		}
		else {
			t->next = tail;
		}
	}
	
	Item get() {
		using namespace li;
		Item v = head->item;
		link t = next(head);
		delete head;
		head = t;
		return v;
	}
};

///////////////////////////////////////
// ------ QUEUE based on array --------
///////////////////////////////////////
template <class Item>
class QueueArray {
private:
	Item* data;
	int tail;
	int head;
	int N;
public:
	QueueArray(int maxN) 
		: data(new Item[maxN])
		, N(maxN + 1)
		, head(N)
		, tail(0) {}

	int empty() const { return head % N == tail; }
	void put(Item item) {
		data[tail++] = item;
		tail = tail % N;
	}
	Item get() {
		head = head % N;
		return data[head++];
	}
};

///////////////////////////////////////
// ------ PRIORITY-QUEUE --------------
///////////////////////////////////////
template <class Item>
class PriorityQueue {
private:
	Item* pq;
	int N;
public:
	PriorityQueue(int maxN) : pq(new Item[maxN]), N(0) {}
	int empty() const { return N == 0; }
	void insert(Item item) { pq[N++] = item; }
	Item getMax() {
		int maxInd = 0;
		for (int i = 1; i < N; i++) {
			if (pq[maxInd] < pq[i]) maxInd = i;
		}
		exch(pq[maxInd], pq[N - 1]);
		return pq[--N];
	}
};
///////////////////////////////////////
// ------ BINARY-TREE ----------------
///////////////////////////////////////
struct BinaryTree {
	int item;
	BinaryTree* l;
	BinaryTree* r;

	BinaryTree(int in, BinaryTree* nodeL, BinaryTree* nodeR);
};
typedef BinaryTree* BinaryTreeLink;

namespace biTree {
	void traverse(BinaryTreeLink h);
	void traverseStack(BinaryTreeLink h);
	void levelTraverseQueue(BinaryTreeLink h);
	void visit(BinaryTreeLink h);
	int count(BinaryTreeLink h);
	int height(BinaryTreeLink h);
}