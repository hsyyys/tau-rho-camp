#ifndef common_h
#define common_h

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <set>
#include <unordered_map>
#include <filesystem>
#include <ctime>
#include <climits>


using namespace std;

#define SPACE_CHAR ' '
#define TAB_CHAR '\t'
extern int NODENUM;
extern int NODE;
extern int USERNUM;
extern int USER;

typedef struct anedge{
    int from;
    int to;
    anedge(int from, int to) : from(from), to(to){}
}anedge;


extern vector<vector<int>> neighbor;
extern vector<vector<int>> edge;
extern vector<int16_t> support;
extern vector<int16_t> tsupport;
extern int edgenum;


#endif /* common_h */
