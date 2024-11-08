//
//  trussquad.h
//  community
//
//  Created by lily on 2024/8/27.
//

#ifndef trussquad_h
#define trussquad_h

#include "common.h"


class Trussquad
{
public:
    int type;
    int quadNo = 0;
    vector<vector<int>> tree;
    vector<vector<int>> parent;
    unordered_map<string, int> map;//map each edge to its id
    vector<vector<int>> quadedge;
    vector<vector<int>> neighbor1;
    vector<int> minsup;
    vector<int> comsize;
    vector<int8_t> keepunchanged;

    
    
    Trussquad(int datatype){
        neighbor.resize(NODENUM);
        neighbor1.resize(NODENUM);
        type = datatype;
    }
    
    bool cmpElement(vector<int> &a, vector<int> &b, int id);
    int partitions(vector<vector<int>> &arr, int left, int right, int id);
    void quick_sort(vector<vector<int>> &arr, int left, int right, int id);
    void quick(vector<vector<int>> &arr, int length, int id);
    
    int partitions_list(vector<int> &arr, int left, int right);
    void quick_sort_list(vector<int> &arr, int left, int right);
    void quick_list(vector<int> &arr, int length);
    
    int computesupport(const char* datapath, const char* suppath, const char* neipath);
    int intersaction(vector<int> &a, vector<int> &b, int &s);
    int compute1quad(const char* datapath, const char* suppath, const char* compath);
    int connectedsubgraph(const char* compath, vector<vector<int>> &kedge, vector<int> &newlevel, int &quadid, int tlevel, int qlevel, int parentid, int minsupport);
    int computekquad(const char* compath, const char* parentpath);
    int readcommunity(const char* compath, int tlevel, int level, int id, vector<vector<int>> &edgelist);
    int copyquad(const char* compath, int oldtlevel, int oldqlevel, int oldid, int newtlevel, int newqlevel, int newid);
    int partitionCommunity(int sign, vector<vector<int>> &obtainedcom, vector<bool> &edgeexist0, vector<int16_t> &tsupport, vector<int16_t> &qsupport, int trusslevel, int quadlevel, int parentid, int quadNo0, int &taldeledgenum);

    int buildindex(const char* compath, const char* indexpath);
    int readindex(const char* indexpath, vector<vector<vector<int>>> &index);
    int readrangequery(const char* querypath, vector<vector<int>> &query);
    int readpointquery(const char* querypath, vector<int> &query);
    int pointquery(const char* indexpath, const char* querypath, const char* pointresult);
    int rangequery(const char* indexpath, const char* querypath, const char* rangeresult);
    int findCommonid(vector<vector<int>> v);
    int binarysearch(vector<int> a, int tgt);
    int find2hopneighbors(const char* datapath, const char* graphpath);
    int intersaction1(vector<int> &a, vector<int> &b);
};






#endif /* trussquad_h */
