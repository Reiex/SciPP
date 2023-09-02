///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SciPP/Core/CoreDecl.hpp>

namespace scp
{
	template<typename TNode, typename TEdge>
	Graph<TNode, TEdge>::Graph() :
		_nextId(0),
		_nodes(),
		_edges(),
		_edgeMap()
	{
	}

	template<typename TNode, typename TEdge>
	uint64_t Graph<TNode, TEdge>::addNode(const TNode& nodeValue)
	{
		assert(_nodes.find(_nextId) == _nodes.end());

		_nodes[_nextId] = nodeValue;

		return _nextId++;
	}

	template<typename TNode, typename TEdge>
	void Graph<TNode, TEdge>::setNodeValue(uint64_t nodeId, const TNode& nodeValue)
	{
		assert(_nodes.find(nodeId) != _nodes.end());

		_nodes[nodeId] = nodeValue;
	}

	template<typename TNode, typename TEdge>
	const TNode& Graph<TNode, TEdge>::getNodeValue(uint64_t nodeId) const
	{
		assert(_nodes.find(nodeId) != _nodes.end());

		return _nodes.find(nodeId)->second;
	}

	template<typename TNode, typename TEdge>
	void Graph<TNode, TEdge>::removeNode(uint64_t nodeId)
	{
		assert(_nodes.find(nodeId) != _nodes.end());

		_nodes.erase(nodeId);

		// Remove edges going from nodeId
		auto itEdgesFromNode = _edgeMap.find(nodeId);
		if (itEdgesFromNode != _edgeMap.end())
		{
			for (const std::pair<uint64_t, std::vector<uint64_t>>& elt : itEdgesFromNode->second)
			{
				for (uint64_t edgeId : elt.second)
				{
					_edges.erase(edgeId);
				}
			}

			_edgeMap.erase(itEdgesFromNode);
		}

		// Remove edges going to nodeId
		for (std::pair<const uint64_t, std::unordered_map<uint64_t, std::vector<uint64_t>>>& edgeMapElt : _edgeMap)
		{
			auto itEdgesToNode = edgeMapElt.second.find(nodeId);
			if (itEdgesToNode != edgeMapElt.second.end())
			{
				for (uint64_t edgeId : itEdgesToNode->second)
				{
					_edges.erase(edgeId);
				}

				edgeMapElt.second.erase(itEdgesToNode);
			}
		}
	}

	template<typename TNode, typename TEdge>
	uint64_t Graph<TNode, TEdge>::addEdge(uint64_t nodeIdFrom, uint64_t nodeIdTo, const TEdge& edgeValue)
	{
		assert(_edges.find(_nextId) == _edges.end());
		assert(_nodes.find(nodeIdFrom) != _nodes.end());
		assert(_nodes.find(nodeIdTo) != _nodes.end());

		_edges[_nextId] = { nodeIdFrom, nodeIdTo, edgeValue };
		_edgeMap[nodeIdFrom][nodeIdTo].push_back(_nextId);

		return _nextId++;
	}

	template<typename TNode, typename TEdge>
	void Graph<TNode, TEdge>::setEdgeValue(uint64_t edgeId, const TEdge& edgeValue)
	{
		assert(_edges.find(edgeId) != _edges.end());

		std::get<2>(_edges[edgeId]) = edgeValue;
	}

	template<typename TNode, typename TEdge>
	uint64_t Graph<TNode, TEdge>::getEdgeTail(uint64_t edgeId) const
	{
		assert(_edges.find(edgeId) != _edges.end());

		return std::get<0>(_edges.find(edgeId)->second);
	}

	template<typename TNode, typename TEdge>
	uint64_t Graph<TNode, TEdge>::getEdgeHead(uint64_t edgeId) const
	{
		assert(_edges.find(edgeId) != _edges.end());

		return std::get<1>(_edges.find(edgeId)->second);
	}

	template<typename TNode, typename TEdge>
	const TEdge& Graph<TNode, TEdge>::getEdgeValue(uint64_t edgeId) const
	{
		assert(_edges.find(edgeId) != _edges.end());

		return std::get<2>(_edges.find(edgeId)->second);
	}

	template<typename TNode, typename TEdge>
	void Graph<TNode, TEdge>::removeEdge(uint64_t edgeId)
	{
		assert(_edges.find(edgeId) != _edges.end());

		const uint64_t nodeIdFrom = std::get<0>(_edges[edgeId]);
		const uint64_t nodeIdTo = std::get<1>(_edges[edgeId]);

		std::vector<uint64_t>& colinearEdges = _edgeMap[nodeIdFrom][nodeIdTo];
		colinearEdges.erase(std::find(colinearEdges.begin(), colinearEdges.end(), edgeId));
		if (colinearEdges.empty())
		{
			_edgeMap[nodeIdFrom].erase(_edgeMap[nodeIdFrom].find(nodeIdTo));
			if (_edgeMap[nodeIdFrom].empty())
			{
				_edgeMap.erase(_edgeMap.find(nodeIdFrom));
			}
		}

		_edges.erase(_edges.find(edgeId));
	}

	template<typename TNode, typename TEdge>
	std::vector<uint64_t> Graph<TNode, TEdge>::getNodes() const
	{
		std::vector<uint64_t> nodes;
		for (const std::pair<uint64_t, TNode>& node : _nodes)
		{
			nodes.push_back(node.first);
		}

		return nodes;
	}

	template<typename TNode, typename TEdge>
	std::vector<uint64_t> Graph<TNode, TEdge>::getEdges(uint64_t nodeIdFrom, uint64_t nodeIdTo) const
	{
		if (nodeIdFrom == -1 && nodeIdTo == -1)
		{
			std::vector<uint64_t> edges;
			for (const std::pair<uint64_t, std::tuple<uint64_t, uint64_t, TEdge>>& edge : _edges)
			{
				edges.push_back(edge.first);
			}
			return edges;
		}
		else if (nodeIdFrom == -1)
		{
			assert(_nodes.find(nodeIdTo) != _nodes.end());

			std::vector<uint64_t> edges;
			for (const std::pair<uint64_t, std::unordered_map<uint64_t, std::vector<uint64_t>>>& elt : _edgeMap)
			{
				auto itEdgesTo = elt.second.find(nodeIdTo);
				if (itEdgesTo != elt.second.end())
				{
					edges.insert(edges.end(), itEdgesTo->second.begin(), itEdgesTo->second.end());
				}
			}

			return edges;
		}
		else if (nodeIdTo == -1)
		{
			assert(_nodes.find(nodeIdFrom) != _nodes.end());

			std::vector<uint64_t> edges;
			auto itEdgesFrom = _edgeMap.find(nodeIdFrom);
			if (itEdgesFrom != _edgeMap.end())
			{
				for (const std::pair<uint64_t, std::vector<uint64_t>>& elt : itEdgesFrom->second)
				{
					edges.insert(edges.end(), elt.second.begin(), elt.second.end());
				}
			}

			return edges;
		}
		else
		{
			assert(_nodes.find(nodeIdFrom) != _nodes.end());
			assert(_nodes.find(nodeIdTo) != _nodes.end());

			auto itEdgesFrom = _edgeMap.find(nodeIdFrom);
			if (itEdgesFrom != _edgeMap.end())
			{
				auto itEdgesTo = itEdgesFrom->second.find(nodeIdTo);
				if (itEdgesTo != itEdgesFrom->second.end())
				{
					return itEdgesTo->second;
				}
			}

			return {};
		}
	}

	template<typename TNode, typename TEdge>
	const std::unordered_map<uint64_t, std::unordered_map<uint64_t, std::vector<uint64_t>>>& Graph<TNode, TEdge>::getEdgeMap() const
	{
		return _edgeMap;
	}

	template<typename TNode, typename TEdge>
	template<CTensor<TEdge> TTensor>
	void Graph<TNode, TEdge>::setFromAdjacencyMatrix(const TTensor& matrix, const std::vector<TNode>& nodeValues)
	{
		assert(matrix.getOrder() == 2);
		assert(matrix.getSize(0) == matrix.getSize(1));
		assert(matrix.getSize(0) == nodeValues.size());

		clear();

		const uint64_t m = matrix.getSize(0);
		const uint64_t n = matrix.getElementCount();

		std::vector<uint64_t> nodes(m);
		for (uint64_t i = 0; i < m; ++i)
		{
			nodes[i] = addNode(nodeValues[i]);
		}

		for (uint64_t i = 0; i < n; ++i)
		{
			const TEdge& value = matrix.get(i);
			if (value != _zeroEdge)
			{
				addEdge(nodes[i / m], nodes[i % m], value);
			}
		}
	}

	template<typename TNode, typename TEdge>
	template<CTensor<TEdge> TTensor>
	void Graph<TNode, TEdge>::getAdjacencyMatrix(TTensor& matrix, std::vector<TNode>& nodeValues) const
	{
		assert(matrix.getSize(0) == _nodes.size());
		assert(matrix.getSize(1) == _nodes.size());

		matrix.fill(_zeroEdge);
		nodeValues.resize(_nodes.size());

		std::unordered_map<uint64_t, uint64_t> nodeIndices;

		uint64_t i = 0;
		for (const std::pair<uint64_t, TNode>& node : _nodes)
		{
			nodeIndices[node.first] = i;
			nodeValues[i] = node.second;
			++i;
		}

		for (const std::pair<uint64_t, std::tuple<uint64_t, uint64_t, TEdge>>& edge : _edges)
		{
			uint64_t nodeIndexFrom = nodeIndices[std::get<0>(edge.second)];
			uint64_t nodeIndexTo = nodeIndices[std::get<1>(edge.second)];

			assert(matrix.get({ nodeIndexFrom, nodeIndexTo }) == 0);

			matrix.set({ nodeIndexFrom, nodeIndexTo }, std::get<2>(edge.second));
		}
	}

	template<typename TNode, typename TEdge>
	void Graph<TNode, TEdge>::dijkstra(PathfindingResult& result, uint64_t nodeIdFrom, uint64_t nodeIdTo) const
	{
		assert(_nodes.find(nodeIdTo) != _nodes.end());

		// Raw Dijkstra's algorithm
		std::unordered_map<uint64_t, TEdge*> distance(_nodes.bucket_count());
		std::unordered_map<uint64_t, uint64_t> parentEdge(_nodes.bucket_count());
		_dijkstra(distance, parentEdge, nodeIdFrom, nodeIdTo);

		// Extract result
		result = PathfindingResult{};
		result.pathFound = (distance[nodeIdTo] != nullptr);
		if (result.pathFound)
		{
			result.pathLength = *distance[nodeIdTo];
			uint64_t currentNode = nodeIdTo;
			while (currentNode != nodeIdFrom)
			{
				result.pathEdges.push_back(parentEdge[currentNode]);
				currentNode = std::get<0>(_edges.find(result.pathEdges.back())->second);
			}
			std::reverse(result.pathEdges.begin(), result.pathEdges.end());
		}

		// Do not forget to release distances computed by raw algorithm !
		for (const std::pair<uint64_t, TEdge*>& elt : distance)
		{
			if (elt.second)
			{
				delete elt.second;
			}
		}
	}

	template<typename TNode, typename TEdge>
	void Graph<TNode, TEdge>::dijkstra(std::unordered_map<uint64_t, PathfindingResult>& results, uint64_t nodeIdFrom) const
	{
		// Raw Dijkstra's algorithm
		std::unordered_map<uint64_t, TEdge*> distance(_nodes.bucket_count());
		std::unordered_map<uint64_t, uint64_t> parentEdge(_nodes.bucket_count());
		_dijkstra(distance, parentEdge, nodeIdFrom);

		// Extract results
		results.clear();
		results.reserve(_nodes.size());
		for (const std::pair<uint64_t, TNode>& node : _nodes)
		{
			PathfindingResult result{};
			result.pathFound = (distance[node.first] != nullptr);
			if (result.pathFound)
			{
				result.pathLength = *distance[node.first];
				uint64_t currentNode = node.first;
				while (currentNode != nodeIdFrom)
				{
					result.pathEdges.push_back(parentEdge[currentNode]);
					currentNode = std::get<0>(_edges.find(result.pathEdges.back())->second);
				}
				std::reverse(result.pathEdges.begin(), result.pathEdges.end());
			}

			results[node.first] = result;
		}

		// Do not forget to release distances computed by raw algorithm !
		for (const std::pair<uint64_t, TEdge*>& elt : distance)
		{
			if (elt.second)
			{
				delete elt.second;
			}
		}
	}

	template<typename TNode, typename TEdge>
	void Graph<TNode, TEdge>::bellmanFord(std::unordered_map<uint64_t, PathfindingResult>& results, uint64_t nodeIdFrom) const
	{
		// Raw Bellman-Ford's algorithm
		std::unordered_map<uint64_t, TEdge*> distance(_nodes.bucket_count());
		std::unordered_map<uint64_t, uint64_t> parentEdge(_nodes.bucket_count());
		bool graphHasNegativeCycle = _bellmanFord(distance, parentEdge, nodeIdFrom);

		// Extract results
		results.clear();
		results.reserve(_nodes.size());
		for (const std::pair<uint64_t, TNode>& node : _nodes)
		{
			PathfindingResult result{};
			result.graphHasNegativeCycle = graphHasNegativeCycle;
			result.pathFound = (distance[node.first] != nullptr);
			if (result.pathFound)
			{
				result.pathLength = *distance[node.first];
				uint64_t currentNode = node.first;
				while (currentNode != nodeIdFrom)
				{
					result.pathEdges.push_back(parentEdge[currentNode]);
					currentNode = std::get<0>(_edges.find(result.pathEdges.back())->second);
				}
				std::reverse(result.pathEdges.begin(), result.pathEdges.end());
			}

			results[node.first] = result;
		}

		// Do not forget to release distances computed by raw algorithm !
		for (const std::pair<uint64_t, TEdge*>& elt : distance)
		{
			if (elt.second)
			{
				delete elt.second;
			}
		}
	}
	
	template<typename TNode, typename TEdge>
	void Graph<TNode, TEdge>::floydWarshall(std::unordered_map<uint64_t, std::unordered_map<uint64_t, PathfindingResult>>& results) const
	{
		// Raw Floyd-Marshall's algorithm
		std::unordered_map<uint64_t, std::unordered_map<uint64_t, TEdge*>> distance;
		std::unordered_map<uint64_t, std::unordered_map<uint64_t, uint64_t>> midNode, midEdge;
		_floydWarshall(distance, midNode, midEdge);

		// Extract results
		results.clear();
		results.reserve(_nodes.size());
		for (const std::pair<uint64_t, TNode>& nodeA : _nodes)
		{
			results[nodeA.first].reserve(_nodes.size());
			for (const std::pair<uint64_t, TNode>& nodeB : _nodes)
			{
				PathfindingResult result{};
				result.pathFound = (distance[nodeA.first][nodeB.first] != nullptr);
				if (result.pathFound)
				{
					result.pathLength = *distance[nodeA.first][nodeB.first];

					if (nodeA.first != nodeB.first)
					{
						std::forward_list<uint64_t> nodes = { nodeA.first, nodeB.first };
						auto it = nodes.begin();
						auto itNext = ++nodes.begin();
						while (itNext != nodes.end())
						{
							if (midNode[*it][*itNext] != -1)
							{
								itNext = nodes.insert_after(it, midNode[*it][*itNext]);
							}
							else
							{
								result.pathEdges.push_back(midEdge[*it][*itNext]);
								++it;
								++itNext;
							}
						}
					}
				}

				results[nodeA.first][nodeB.first] = result;
			}
		}

		// Do not forget to release distances computed by raw algorithm !
		for (const std::pair<uint64_t, std::unordered_map<uint64_t, TEdge*>>& elt : distance)
		{
			for (const std::pair<uint64_t, TEdge*> dist : elt.second)
			if (dist.second)
			{
				delete dist.second;
			}
		}
	}

	template<typename TNode, typename TEdge>
	void Graph<TNode, TEdge>::clear()
	{
		_nextId = 0;
		_nodes.clear();
		_edges.clear();
		_edgeMap.clear();
	}

	template<typename TNode, typename TEdge>
	void Graph<TNode, TEdge>::_dijkstra(std::unordered_map<uint64_t, TEdge*>& distance, std::unordered_map<uint64_t, uint64_t>& parentEdge, uint64_t nodeIdFrom, uint64_t nodeIdTo) const
	{
		assert(_nodes.find(nodeIdFrom) != _nodes.end());
		assert(_nodes.find(nodeIdTo) != _nodes.end() || nodeIdTo == -1);
		for (const std::pair<uint64_t, std::tuple<uint64_t, uint64_t, TEdge>>& edge : _edges)
		{
			assert(std::get<2>(edge.second) >= 0);
		}

		// Initialize Dijkstra parameters

		std::unordered_map<uint64_t, bool> visited(_nodes.bucket_count());
		for (const std::pair<uint64_t, TNode>& node : _nodes)
		{
			visited[node.first] = false;
			distance[node.first] = nullptr;
			parentEdge[node.first] = -1;
		}
		distance[nodeIdFrom] = new TEdge(0);

		/* The heap contains node IDs "sorted" by their distance to nodeIdFrom. As the distance of a node to nodeIdFrom moves during the algorithm, the
		* distance at the moment of insertion must be saved (thus the std::pair<uint64_t, TEdge>). A node can furthermore be pushed multiple times in
		* the heap, thus when extracting a node from the heap, the node must be verified to not have already been visited. */
		std::vector<std::pair<uint64_t, TEdge>> nodeHeap;
		auto nodeCmp = [&](const std::pair<uint64_t, TEdge>& nodeA, const std::pair<uint64_t, TEdge>& nodeB) -> bool { return nodeA.second > nodeB.second; };

		// Main Dijkstra's algorithm loop (over all visitable nodes)

		uint64_t currentNode = nodeIdFrom;
		while (!((nodeIdTo != -1 && visited[nodeIdTo]) || visited[currentNode])) // visited[currentNode] means there are no more nodes visitable
		{
			auto it = _edgeMap.find(currentNode);
			if (it != _edgeMap.end())
			{
				// For all non-visited nodes connected to currentNode (with a direction currentNode->Node)
				for (const std::pair<uint64_t, std::vector<uint64_t>>& elt : it->second)
				{
					if (!visited[elt.first])
					{
						// Find the edge with the minimal distance
						uint64_t minEdgeId = elt.second[0];
						for (uint64_t edgeId : elt.second)
						{
							if (std::get<2>(_edges.find(edgeId)->second) < std::get<2>(_edges.find(minEdgeId)->second))
							{
								minEdgeId = edgeId;
							}
						}

						// Compute the new distance of the node and check if it is better
						TEdge newDistance = std::get<2>(_edges.find(minEdgeId)->second) + *distance[currentNode];

						TEdge*& currentDistance = distance[elt.first];
						if (!currentDistance || newDistance < *currentDistance)
						{
							// Replace the node distance and parent edge
							if (!currentDistance)
							{
								currentDistance = new TEdge();
							}

							*currentDistance = newDistance;
							parentEdge[elt.first] = minEdgeId;

							// Insert the node with its distance into the heap
							nodeHeap.push_back({ elt.first, *currentDistance });
							std::push_heap(nodeHeap.begin(), nodeHeap.end(), nodeCmp);
						}
					}
				}
			}

			// currentNode is now visited
			visited[currentNode] = true;

			// Attempt to extract an unvisited node from the heap
			while (visited[currentNode] && !nodeHeap.empty())
			{
				currentNode = nodeHeap[0].first;

				std::pop_heap(nodeHeap.begin(), nodeHeap.end(), nodeCmp);
				nodeHeap.pop_back();
			}
		}
	}

	template<typename TNode, typename TEdge>
	bool Graph<TNode, TEdge>::_bellmanFord(std::unordered_map<uint64_t, TEdge*>& distance, std::unordered_map<uint64_t, uint64_t>& parentEdge, uint64_t nodeIdFrom) const
	{
		assert(_nodes.find(nodeIdFrom) != _nodes.end());

		// Compute necessary edges

		std::vector<uint64_t> edges;
		for (const std::pair<uint64_t, std::unordered_map<uint64_t, std::vector<uint64_t>>>& elt : _edgeMap)
		{
			for (const std::pair<uint64_t, std::vector<uint64_t>>& parallelEdges : elt.second)
			{
				uint64_t minEdgeId = parallelEdges.second[0];
				for (uint64_t edgeId : parallelEdges.second)
				{
					if (std::get<2>(_edges.find(edgeId)->second) < std::get<2>(_edges.find(minEdgeId)->second))
					{
						minEdgeId = edgeId;
					}
				}

				edges.push_back(minEdgeId);
			}
		}

		// Initialize Bellman-Ford parameters

		for (const std::pair<uint64_t, TNode>& node : _nodes)
		{
			distance[node.first] = nullptr;
			parentEdge[node.first] = -1;
		}
		distance[nodeIdFrom] = new TEdge(0);

		// Main Bellman-Ford's algorithm loop (|V|-1 edges relaxations)

		uint64_t n = _nodes.size() - 1;
		bool evolved = true;
		for (uint64_t i = 0; i < n && evolved; ++i)
		{
			evolved = false;
			for (uint64_t edgeId : edges)
			{
				const std::tuple<uint64_t, uint64_t, TEdge>& edge = _edges.find(edgeId)->second;
				const TEdge* distanceFrom = distance[std::get<0>(edge)];
				if (distanceFrom)
				{
					TEdge newDistance = *distanceFrom + std::get<2>(edge);
					TEdge*& oldDistance = distance[std::get<1>(edge)];
					if (!oldDistance || newDistance < *oldDistance)
					{
						if (!oldDistance)
						{
							oldDistance = new TEdge();
						}

						*oldDistance = newDistance;
						parentEdge[std::get<1>(edge)] = edgeId;
						evolved = true;
					}
				}
			}
		}

		// Check if graph has a negative cycle

		if (!evolved)
		{
			return false;
		}

		for (uint64_t edgeId : edges)
		{
			const std::tuple<uint64_t, uint64_t, TEdge>& edge = _edges.find(edgeId)->second;
			const TEdge* distanceFrom = distance[std::get<0>(edge)];
			if (distanceFrom)
			{
				TEdge newDistance = *distanceFrom + std::get<2>(edge);
				TEdge*& oldDistance = distance[std::get<1>(edge)];
				if (!oldDistance || newDistance < *oldDistance)
				{
					return true;
				}
			}
		}

		return false;
	}

	template<typename TNode, typename TEdge>
	void Graph<TNode, TEdge>::_floydWarshall(std::unordered_map<uint64_t, std::unordered_map<uint64_t, TEdge*>>& distance, std::unordered_map<uint64_t, std::unordered_map<uint64_t, uint64_t>>& midNode, std::unordered_map<uint64_t, std::unordered_map<uint64_t, uint64_t>>& midEdge) const
	{
		// Initialize Floyd-Warshall parameters

		for (const std::pair<uint64_t, TNode>& nodeA : _nodes)
		{
			for (const std::pair<uint64_t, TNode>& nodeB : _nodes)
			{
				distance[nodeA.first][nodeB.first] = nullptr;
				midNode[nodeA.first][nodeB.first] = -1;
				midEdge[nodeA.first][nodeB.first] = -1;
			}
		}

		for (const std::pair<uint64_t, std::unordered_map<uint64_t, std::vector<uint64_t>>>& elt : _edgeMap)
		{
			for (const std::pair<uint64_t, std::vector<uint64_t>>& parallelEdges : elt.second)
			{
				uint64_t minEdgeId = parallelEdges.second[0];
				TEdge* minEdgeValue = new TEdge(std::get<2>(_edges.find(minEdgeId)->second));
				for (uint64_t edgeId : parallelEdges.second)
				{
					auto it = _edges.find(edgeId);
					if (std::get<2>(it->second) < *minEdgeValue)
					{
						minEdgeId = edgeId;
						*minEdgeValue = std::get<2>(it->second);
					}
				}

				distance[elt.first][parallelEdges.first] = minEdgeValue;
				midEdge[elt.first][parallelEdges.first] = minEdgeId;
			}
		}

		for (const std::pair<uint64_t, TNode>& node : _nodes)
		{
			assert(distance[node.first][node.first] == nullptr || *distance[node.first][node.first] > 0);
			if (distance[node.first][node.first])
			{
				*distance[node.first][node.first] = 0;
			}
			else
			{
				distance[node.first][node.first] = new TEdge(0);
			}
		}

		// Main Floyd-Warshall's algorithm loop

		for (const std::pair<uint64_t, TNode>& nodeB : _nodes)
		{
			for (const std::pair<uint64_t, TNode>& nodeA : _nodes)
			{
				for (const std::pair<uint64_t, TNode>& nodeC : _nodes)
				{
					TEdge*& dAB = distance[nodeA.first][nodeB.first];
					TEdge*& dBC = distance[nodeB.first][nodeC.first];
					TEdge*& dAC = distance[nodeA.first][nodeC.first];
					if (dAB && dBC)
					{
						TEdge newDistance = *dAB + *dBC;
						if (!dAC || newDistance < *dAC)
						{
							if (!dAC)
							{
								dAC = new TEdge();
							}

							*dAC = newDistance;
							midNode[nodeA.first][nodeC.first] = nodeB.first;
						}
					}
				}
			}
		}
	}
}
