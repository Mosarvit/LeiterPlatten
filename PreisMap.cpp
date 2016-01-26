#include "PreisMap.h"
#include "PreisAngebot.h"

void PreisMap::addPreisAngebot(Node & rSchritt1, Node & rSchritt2, double angebot)
{
	addEdge(new PreisAngebot(rSchritt1, rSchritt2, angebot));
}

Node* PreisMap::getNodeById(const string& rNodeId)
{
	for (list<Node*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++) {
		if ((*it)->getID() == rNodeId)
			return *it;
	}
	return NULL;
}