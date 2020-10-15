//
// Created by Jingtao Xu on 15.10.2020.
//

#ifndef ADS2WORKSHOP4_PRIORITYQ_V2W_H
#define ADS2WORKSHOP4_PRIORITYQ_V2W_H



#include "lbl_ugraph.hpp"

template <typename Vertex,typename EdgeLbl>
class PriorityQ_V2W
{
public:

    PriorityQ_V2W(){};

    void insert(const Vertex& v,const EdgeLbl& w)
    {
        _setWeightToVertex.insert({w, v});
        _vertexToWeight.insert({v, w});
    }

    void remove(const Vertex& v)
    {
        auto it = _vertexToWeight.find(v);
        if(it != _vertexToWeight.end())
        {
            _setWeightToVertex.erase({it->second, v});
            _vertexToWeight.erase(it);
        }
    }

    void set(const Vertex& v,const EdgeLbl& w)
    {
        auto it = _vertexToWeight.find(v);
        if(it != _vertexToWeight.end())
        {
            auto it2 = _setWeightToVertex.find({it->second, v});
            *it->second = w;
            *it2.first = w;
        }
    }

    int getCost(const Vertex& v)
    {
        auto it = _vertexToWeight.find(v);
        return it->second;
    }

    Vertex getMin() const
    {
        return _setWeightToVertex.begin()->second;
    }

    bool isEmpty() const
    {
        bool wIsEmtp;
        bool vIsEmpt;
        wIsEmtp = _setWeightToVertex.empty();
        vIsEmpt = _vertexToWeight.empty();
        return (vIsEmpt && wIsEmtp);
    }

private:
    std::set<std::pair<EdgeLbl,Vertex>> _setWeightToVertex;
    std::multimap<Vertex,EdgeLbl> _vertexToWeight;
};

#endif //ADS2WORKSHOP4_PRIORITYQ_V2W_H

////////////////////////////////////////////////////
//
//template<typename Vertex, typename Weight>
//class PriorityQ {
//public:
//
//    typedef std::set<Vertex> VerticesSet;
//
//    typedef std::map<Vertex, VerticesSet> queue_t;
//    typedef std::map<Vertex, Vertex> id2ValueMap_t;
//
//public:
//
//    priorityQ();
//
//public:
//
//    void insert(Vertex id, Vertex value);
//    void remove(Vertex id);
//
//    Weight getCost(Vertex id, Vertex* pValue) const;
//    bool set(Vertex id, Vertex oldValue, Vertex newValue);
//
//    bool getMin(Vertex* pId) const;
//
//    bool isEmpty() const;
//    bool contains(Vertex id) const;
//    void clear();
//
//private:
//    queue_t  _queue;
//    id2ValueMap_t _id2ValueMap;
//
//};