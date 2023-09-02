///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SciPP/Core/CoreTypes.hpp>

namespace scp
{
	template<typename TNode, typename TEdge>
	class Graph
	{
		public:

			Graph();
			Graph(const Graph& graph) = default;
			Graph(Graph&& graph) = default;

			Graph& operator=(const Graph& graph) = default;
			Graph& operator=(Graph && graph) = default;

			uint64_t addNode(const TNode& nodeValue);
			void setNodeValue(uint64_t nodeId, const TNode& nodeValue);
			const TNode& getNodeValue(uint64_t nodeId) const;
			void removeNode(uint64_t nodeId);

			uint64_t addEdge(uint64_t nodeIdFrom, uint64_t nodeIdTo, const TEdge& edgeValue);
			void setEdgeValue(uint64_t edgeId, const TEdge& edgeValue);
			uint64_t getEdgeTail(uint64_t edgeId) const;
			uint64_t getEdgeHead(uint64_t edgeId) const;
			const TEdge& getEdgeValue(uint64_t edgeId) const;
			void removeEdge(uint64_t edgeId);

			std::vector<uint64_t> getNodes() const;
			std::vector<uint64_t> getEdges(uint64_t nodeIdFrom = -1, uint64_t nodeIdTo = -1) const;
			const std::unordered_map<uint64_t, std::unordered_map<uint64_t, std::vector<uint64_t>>>& getEdgeMap() const;

			template<CTensor<TEdge> TTensor> void setFromAdjacencyMatrix(const TTensor& matrix, const std::vector<TNode>& nodeValues);
			template<CTensor<TEdge> TTensor> void getAdjacencyMatrix(TTensor& matrix, std::vector<TNode>& nodeValues) const;

			struct PathfindingResult
			{
				bool pathFound = false;
				std::vector<uint64_t> pathEdges = {};
				TEdge pathLength = 0;
				bool graphHasNegativeCycle = false;
			};
			
			void dijkstra(PathfindingResult& result, uint64_t nodeIdFrom, uint64_t nodeIdTo) const;									// A->B, O((E+V)log(V)), d >= 0, no neg-cycle
			void dijkstra(std::unordered_map<uint64_t, PathfindingResult>& results, uint64_t nodeIdFrom) const;						// A->, O((E+V)log(V)), d >= 0, no neg-cycle
			void bellmanFord(std::unordered_map<uint64_t, PathfindingResult>& results, uint64_t nodeIdFrom) const;					// A->, O(EV), d < 0, neg-cycle
			void floydWarshall(std::unordered_map<uint64_t, std::unordered_map<uint64_t, PathfindingResult>>& results) const;		// ->, O(V^3), d < 0, no neg-cycle

			void clear();

			~Graph() = default;

		private:

			static constexpr TEdge _zeroEdge = 0;

			void _dijkstra(std::unordered_map<uint64_t, TEdge*>& distance, std::unordered_map<uint64_t, uint64_t>& parentEdge, uint64_t nodeIdFrom, uint64_t nodeIdTo = -1) const;
			bool _bellmanFord(std::unordered_map<uint64_t, TEdge*>& distance, std::unordered_map<uint64_t, uint64_t>& parentEdge, uint64_t nodeIdFrom) const;
			void _floydWarshall(std::unordered_map<uint64_t, std::unordered_map<uint64_t, TEdge*>>& distance, std::unordered_map<uint64_t, std::unordered_map<uint64_t, uint64_t>>& midNode, std::unordered_map<uint64_t, std::unordered_map<uint64_t, uint64_t>>& midEdge) const;
			
			uint64_t _nextId;
			std::unordered_map<uint64_t, TNode> _nodes;
			std::unordered_map<uint64_t, std::tuple<uint64_t, uint64_t, TEdge>> _edges;
			std::unordered_map<uint64_t, std::unordered_map<uint64_t, std::vector<uint64_t>>> _edgeMap;
	};
}
