#ifndef __ALGO_GRAPH
#define __ALGO_GRAPH


namespace al {
	struct AlgoGraphNode {
		unsigned int power;
		unsigned int value;
		bool         connected;


		AlgoGraphNode(unsigned int _power) {power = _power; value = _power; connected = false;};
	};


	struct AlgoGraphEdge {
		unsigned int A;
		unsigned int B;

		AlgoGraphEdge(unsigned int _A, unsigned int _B) {A = _A; B = _B;};
	};


	struct AlgoGraph {
		std::vector<al::AlgoGraphNode*> nodes;
		std::vector<al::AlgoGraphEdge*> edges;

		std::vector<unsigned int> ends;
		std::vector<unsigned int> core;


		 AlgoGraph();
		~AlgoGraph();

		void addNode(unsigned int power);
		void addEdge(unsigned int A, unsigned int B);

		bool checkNull();
		bool checkCore();
		bool checkEnds();

		unsigned int getFreeCore();
		unsigned int getUsedCore();
		unsigned int getFreeEnd();

		void clear();
		void init();
		void generate();
	};
}

#endif
