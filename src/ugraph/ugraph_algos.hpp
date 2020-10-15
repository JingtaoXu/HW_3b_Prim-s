////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief      Contains implementations of some algorithms for undirected graph.
/// \author     Sergey Shershakov
/// \version    0.1.0
/// \date       21.09.2020
/// \copyright  © Sergey Shershakov 2020.
///             This code is for educational purposes of the course "Algorithms
///             and Data Structures" provided by the Faculty of Computer Science
///             at the Higher School of Economics.
///
/// When altering code, a copyright line must be preserved.
/// \copyright  © Jingtao Xu 2020.
////////////////////////////////////////////////////////////////////////////////


#ifndef UGRAPH_ALGOS_HPP
#define UGRAPH_ALGOS_HPP

#include <set>
#include <queue>
#include <climits>

#include "lbl_ugraph.hpp"
#include "priorityQ_V2W.h"

/// Finds a MST for the given graph \a g using Prim's algorithm.
template<typename Vertex, typename EdgeLbl>
std::set<typename EdgeLblUGraph<Vertex, EdgeLbl>::Edge>
findMSTPrim(const EdgeLblUGraph<Vertex, EdgeLbl>& g)
{
    // Aliases
    typedef EdgeLblUGraph<Vertex,EdgeLbl> LblUGraph;
    typedef std::map<Vertex,Vertex> MapV2V;

    // containers
    std::set<typename LblUGraph::Edge> result_mst;
    MapV2V mst_temp; // use its .find() in line 86
    std::map<Vertex,EdgeLbl> totalWeightToV;
    std::set<Vertex> markedVertex; // O(log n) for searching
    PriorityQ_V2W<Vertex,EdgeLbl> pq;

    // construct a table which shows the distance from srcVertex
    typename LblUGraph::EdgeIterPair edge_range = g.getEdges();
    typename LblUGraph::EdgeIter it_edge = edge_range.first;
    typename std::map<Vertex,EdgeLbl>::iterator it_vToW = totalWeightToV.begin();
    typename LblUGraph::VertexIterPair vt_range = g.getVertices();

    for(typename LblUGraph::VertexIter it_vertex = vt_range.first;
        it_vertex != vt_range.second;
        ++it_vertex)
    {
        totalWeightToV.insert({*it_vertex, INT_MAX}); // INT_MAX - INF
    }

    // put the the Shortest
    it_vToW = totalWeightToV.find(it_edge->first);
    it_vToW->second = 0;
    pq.insert(it_edge->first, 0);

    while(!pq.isEmpty())
    {
        // Select the edge with minimum weight, remove the vertex from pq
        Vertex cur_src = pq.getMin();
        markedVertex.insert(cur_src);
        pq.remove(cur_src);

        // Go through the adjacent vertices to cur_src
        typename LblUGraph::AdjListCIterPair range_adjToSrc = g.getAdjEdges(cur_src);
        for(typename LblUGraph::AdjListCIter it_adjToSrc = range_adjToSrc.first;
            it_adjToSrc != range_adjToSrc.second;
            ++it_adjToSrc)
        {
            Vertex v_adjToSrc = it_adjToSrc->second;

            EdgeLbl wAdj;
//            wAdj = g.getLabelValue(cur_src, v_adjToSrc);
            g.getLabel(cur_src, v_adjToSrc, wAdj); // to assign wAdj with weight of cur_src and v_adjToSrc

            // continue if the adjacent vertex is in the set of marked vertices
            if(markedVertex.find(v_adjToSrc) != markedVertex.end()
               || totalWeightToV.find(v_adjToSrc)->second <= wAdj)
                continue;
            else
            {
                totalWeightToV.find(v_adjToSrc)->second = wAdj;
                pq.insert(v_adjToSrc, totalWeightToV.find(v_adjToSrc)->second); // insert every adjacent vertices with its weight

                // if find in mst_temp update the new lower cost, else insert a new edge
                typename MapV2V::iterator mstIt = mst_temp.find(v_adjToSrc);
                if(mstIt != mst_temp.end())
                    mstIt->second = cur_src;
                else
                    mst_temp.insert({v_adjToSrc, cur_src});
            }
        }
    }

    // put mst_temp to result_mst
    for(typename MapV2V::iterator mstIt = mst_temp.begin();
        mstIt != mst_temp.end();
        ++mstIt)
    {
        result_mst.insert({mstIt->first, mstIt->second});
    }

    return result_mst;
}

/// Finds a MST for the given graph \a g using Kruskal's algorithm.
template<typename Vertex, typename EdgeLbl>
std::set<typename EdgeLblUGraph<Vertex, EdgeLbl>::Edge>
findMSTKruskal(const EdgeLblUGraph<Vertex, EdgeLbl>& g)
{
    // TODO: implement this!

    std::set<typename EdgeLblUGraph<Vertex, EdgeLbl>::Edge> res;
    return res;
}


/*
   struct HeapNode // 定义堆中的节点
    {
        int distance2U;
        Vertex index; // 到MST中的距离以及顶点的索引

        bool operator <(HeapNode node)
        {
            return distance2U > node.distance2U; // 即本节点到MST的距离大于node到MST的距离, 则本节点的优先级就比node小
        }
    };

    struct Cmp
    {
        bool operator()(const HeapNode& a,const HeapNode &b) // 注意, 为了效率, 入参是引用, 为了鲁棒性, 这里加了const限制，该运算符就是重载 < , a<b 表示a的优先级低于b, 即本运算符返回true的话, 表示a的优先级低于b, 而优先队列pop出来的都是当前队列中优先级最高的
        {
            if (a.distance2U > b.distance2U) return true;
            else if(a.distance2U == b.distance2U && a.index > b.index) return true; // 在距离相等的情况下,索引大的, 优先级低, 要排后面去
            else return false;
        }
    };


    std::priority_queue<HeapNode, std::vector<HeapNode>(), Cmp> () ;


 */


#endif // UGRAPH_ALGOS_HPP
