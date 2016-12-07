#include <vector>

///////////////////////////////////////
// ------------- GRAPH ---------------
///////////////////////////////////////
struct Edge {
	int v;
	int w;
	Edge(int vIn = -1, int wIn = -1) 
	: v(vIn) 
	, w(wIn) 
	{}
};

class GRAPH {
private:
public:
	GRAPH(int, bool);
	~GRAPH();
	int V() const;
	int E() const;
	bool directed() const;
	int insert(Edge);
	int remove(Edge);
	bool edge(int, int);

	class adjIteartor {
	public:
		adjIteartor(const GRAPH&, int);
		int beg();
		int nxt();
		bool end();
	};
};

template <class Graph> 
std::vector<Edge> edges(Graph& G) {
	int E = 0;
	vector<Edge> a(G.E());
	for (int v = 0; v < G.V(); v++) {
		typename Graph::adjIterator A(G, v);
		for (int w = A.beg(); w != A.end(); w = A.nxt()) {
			if (G.directed() || v < w) {
				a[E++] = Edge(v, w);
			}
		}
	}
	return a;
}

template <class Graph>
class IO {
public:
	static void show(Graph&);
	static void scanEZ(Graph&);
	static void scan(Graph&);
};

template <class Graph> 
void IO<Graph>::show(Graph& G) {
	for (int s = 0; s < G.V(); s++) {
		std::cout << s << " : ";
		typename Graph::adjIterator(G, s);
		for (int t = A.beg(); t != A.end(); t = A.nxt()) {
			std::cout << t << " ";
		}
		std::cout << std::endl;
	}
}

template <class Graph> 
class CC {
private:
public:
	CC(const Graph&);
	int count();
	bool connect(int, int);
};

//////////////////////////////////////////////////////////
/////////////// Graph based on adjscency matrix //////////
//////////////////////////////////////////////////////////
class DenseGraph {
private:
	int Vcnt;
	int Ecnt;
	bool digraph;
	std::vector<std::vector<bool>> adj;
public:
	DenseGraph(int V, bool digraphIn = false)
		: adj(V)
		, Vcnt(V)
		, Ecnt(0)
		, digraph(digraphIn) {
		for (int i = 0; i < V; i++) {
			adj[i].assign(V, false);
		}
	}
	int V() const { return Vcnt; }
	int E() const { return Ecnt; }
	int directed() const { return digraph; }
	
	void insert(Edge e) {
		int v = e.v;
		int w = e.w;
		if (adj[v][w] == false) Ecnt++;
		adj[v][w] = true;
		if (!digraph) adj[w][v] = true;
	}

	void remove(Edge e) {
		int v = e.v;
		int w = e.w;
		if (adj[v][w] == true) Ecnt--;
		adj[v][w] = false;
		if (!digraph) adj[w][v] = false;
	}

	bool edge(int v, int w) const {
		return adj[v][w];
	}

	class adjIterator;
	friend class adjIterator;
};

class DenseGraph::adjIterator {
private:
	const DenseGraph& G;
	int i;
	int v;
public:
	adjIterator(const DenseGraph& GiN, int vIn) 
		: G(GiN)
		, v(vIn)
		, i(-1) {}

	int beg() { 
		i = -1;
		return nxt();
	}

	int nxt() {
		for (i++; i < G.V(); i++) {
			if (G.adj[v][i] == true) return i;
			else return -1;
		}
	}

	bool end() {
		return i >= G.V();
	}
};


//////////////////////////////////////////////////////////
/////////////// Graph based on adjacency list //////////
//////////////////////////////////////////////////////////
class SparseMultiGRAPH{
private:
	int Vcnt;
	int Ecnt;
	bool digraph;
	struct node {
		int v;
		node* next;
		
		node(int inV, node* inNext)
			: v(inV)
			, next(inNext) {}
	};
	typedef node* link;
	std::vector <link> adj;
public:
	SparseMultiGRAPH(int V, bool digraphIn = false)
		: adj(V)
		, Vcnt(V)
		, Ecnt(0)
		, digraph(digraphIn) {
		adj.assign(V, 0);
	}

	int V() const { return Vcnt; }
	int E() const { return Ecnt; }
	int directed() const { return digraph; }

	void insert(Edge e) {
		int v = e.v;
		int w = e.w;
		adj[v] = new node(w, adj[v]);
		if (!digraph) adj[w] =new node(v, adj[w]);
		Ecnt++;
	}

	void remove(Edge e);
	bool edge(int v, int w);

	class adjIterator;
	friend class adjIterator;
};

class SparseMultiGRAPH::adjIterator {
private:
	const SparseMultiGRAPH& G;
	int v;
	link t;
public:
	adjIterator(const SparseMultiGRAPH& GiN, int vIn)
		: G(GiN)
		, v(vIn)
		, t(0) {}

	int beg() {
		t = G.adj[v];
		return t ? t->v : -1;
	}

	int nxt() {
		if (t) t = t->next;
		return t ? t->v : -1;
	}

	bool end() {
		return t == 0;
	}
};