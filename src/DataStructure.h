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