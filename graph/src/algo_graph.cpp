#include "headers.hpp"



/***********************************************************************
     * AlgoGraph
     * constructor

***********************************************************************/
al::AlgoGraph::AlgoGraph() {
}



/***********************************************************************
     * AlgoGraph
     * destructor

***********************************************************************/
al::AlgoGraph::~AlgoGraph() {
	clear();
}



/***********************************************************************
     * AlgoGraph
     * addNode

***********************************************************************/
void al::AlgoGraph::addNode(unsigned int power) {
	nodes.push_back(new al::AlgoGraphNode(power));
}



/***********************************************************************
     * AlgoGraph
     * addEdge

***********************************************************************/
void al::AlgoGraph::addEdge(unsigned int A, unsigned int B) {
	if (A == B) return;

	nodes[A]->value--;
	nodes[B]->value--;

	nodes[A]->connected = true;
	nodes[B]->connected = true;

	edges.push_back(new al::AlgoGraphEdge(A, B));
}



/***********************************************************************
     * AlgoGraph
     * clear

***********************************************************************/
void al::AlgoGraph::clear() {
	deleteList(edges);
	deleteList(nodes);

	ends.clear();
	core.clear();
}



/***********************************************************************
     * AlgoGraph
     * init

***********************************************************************/
void al::AlgoGraph::init() {
	ends.clear();
	core.clear();

	for (unsigned int i = 0; i < nodes.size(); i++)
		if (nodes[i]->power == 1) ends.push_back(i);
		else                      core.push_back(i);
}



/***********************************************************************
     * AlgoGraph
     * generate

***********************************************************************/
void al::AlgoGraph::generate() {
	init();

	while (checkNull()) addEdge(getFreeCore(), getFreeCore());
	while (checkCore()) addEdge(getUsedCore(), getFreeCore());
	while (checkEnds()) addEdge(getUsedCore(), getFreeEnd() );
}



/***********************************************************************
     * AlgoGraph
     * checkNull

***********************************************************************/
bool al::AlgoGraph::checkNull() {
	for (unsigned int i = 0; i < nodes.size(); i++)
		if (nodes[i]->connected)
			return false;

	return true;
}



/***********************************************************************
     * AlgoGraph
     * checkCore

***********************************************************************/
bool al::AlgoGraph::checkCore() {
	for (unsigned int i = 0; i < core.size(); i++)
		if (!nodes[core[i]]->connected)
			return true;

	return false;
}



/***********************************************************************
     * AlgoGraph
     * checkEnds

***********************************************************************/
bool al::AlgoGraph::checkEnds() {
	for (unsigned int i = 0; i < ends.size(); i++)
		if (!nodes[ends[i]]->connected)
			return true;

	return false;
}



/***********************************************************************
     * AlgoGraph
     * getFreeCore

***********************************************************************/
unsigned int al::AlgoGraph::getFreeCore() {
	std::vector<unsigned int> results;

	for (unsigned int i = 0; i < core.size(); i++)
		if (nodes[core[i]]->value && !nodes[core[i]]->connected)
			results.push_back(core[i]);

	return results[rand() % results.size()];
}



/***********************************************************************
     * AlgoGraph
     * getUsedCore

***********************************************************************/
unsigned int al::AlgoGraph::getUsedCore() {
	std::vector<unsigned int> results;

	for (unsigned int i = 0; i < core.size(); i++)
		if (nodes[core[i]]->value && nodes[core[i]]->connected)
			results.push_back(core[i]);

	return results[rand() % results.size()];
}



/***********************************************************************
     * AlgoGraph
     * getFreeEnd

***********************************************************************/
unsigned int al::AlgoGraph::getFreeEnd() {
	std::vector<unsigned int> results;

	for (unsigned int i = 0; i < ends.size(); i++)
		if (nodes[ends[i]]->value && !nodes[ends[i]]->connected)
			results.push_back(ends[i]);

	return results[rand() % results.size()];
}
