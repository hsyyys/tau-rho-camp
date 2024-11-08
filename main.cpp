//
//  main.cpp
//  community
//
//  Created by lily on 2024/7/3.
//

#include "common.h"
#include "kquad.hpp"
#include "trussquad.h"

vector<vector<int>> neighbor;
vector<vector<int>> edge;
vector<int16_t> support;
vector<int16_t> tsupport;
int edgenum;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    string dataf = "/Users/lily/Desktop/c++/test/community/adata/bilibili/";//   ./data/
    //const char* dataFolder = dataf.c_str();
    string datapath = dataf + "data.txt";//bilibili  newbilibili
    string datapath0 = dataf + "edges.txt";//bilibili  newbilibili
    const char* dataPath = datapath.c_str();
    string neipath = dataf + "neighbor.txt";
    const char* neiPath = neipath.c_str();
    string suppath = dataf + "support.txt";
    const char* supPath = suppath.c_str();
    string compath = dataf + "community/";
    const char* comPath = compath.c_str();
    string parentpath = dataf + "parent.txt";
    const char* parentPath = parentpath.c_str();
    string indexpath = dataf + "index.txt";
    const char* indexPath = indexpath.c_str();
    
    string pquerypath = dataf + "query/pquery.txt";
    const char* pqueryPath = pquerypath.c_str();
    string rquerypath = dataf + "query/rquery.txt";
    const char* rqueryPath = rquerypath.c_str();
    string pqueryresult = dataf + "query/pqueryresult.txt";
    const char* pqueryResult = pqueryresult.c_str();
    string rqueryresult = dataf + "query/rqueryresult.txt";
    const char* rqueryResult = rqueryresult.c_str();
    
    string rpath = dataf + "ratio/";
    const char* rPath = rpath.c_str();
    string cpath = dataf + "imdb_distinct/"; //"weibo_queryresult/";
    const char* cPath = cpath.c_str();
    
    string dblppath = dataf + "imdb_distinct/";
    const char* dblpPath = dblppath.c_str();
    string dblppath1 = dataf + "imdb_distinct/";
    const char* dblpPath1 = dblppath1.c_str();
    string graphpath = dataf + "graph.txt";
    const char* graphPath = graphpath.c_str();
    
    int datatype = 1;
    Trussquad* tq = new Trussquad(datatype);
    tq->computesupport(dataPath, supPath, neiPath);
    
//    string line;
//    ifstream fin(supPath);
//    if (fin)
//    {
//        while (getline(fin, line))
//        {
//            istringstream iss(line);
//            string temp;
//            vector<int> tup;
//            while (getline(iss, temp, ' ')) {
//                tup.push_back(stoi(temp));
//            }
//            vector<int> e;
//            e.push_back(tup[0]);
//            e.push_back(tup[1]);
//            edge.push_back(e);
//            tsupport.push_back(tup[2]);
//            support.push_back(tup[3]);
//            neighbor[tup[0]].push_back(tup[1]);
//            neighbor[tup[1]].push_back(tup[0]);
//        }
//    }
//    cout<<edge.size()<<endl;
//    cout<<support.size()<<endl;
//    fin.clear();
//    fin.close();
//    for(int i = 0; i < neighbor.size(); i++){
//        tq->quick_list(neighbor[i], neighbor[i].size());
//    }
    
    tq->compute1quad(dataPath, supPath, comPath);
    tq->computekquad(comPath, parentPath);
    
    //tq->buildindex(comPath, indexPath);
    //tq->pointquery(indexPath, pqueryPath, pqueryResult);
    //tq->rangequery(indexPath, rqueryPath, rqueryResult);
    
 
    
    
    
    
    
    
    
    
    
    
    
// preprocess data, user1 < user2
//    int i, j, g;
//    string line;
//    vector<vector<int>> tuples;
//    ofstream fout(dataPath, ios::out);
//    ifstream fin(datapath0);
//    int num1 = 0;
//    if (fin)
//    {
//        while (getline(fin, line))
//        {
//            istringstream iss(line);
//            string temp;
//            vector<int> tup;
//            while (getline(iss, temp, ' ')) {
//                tup.push_back(stoi(temp));
//            }
////            if(tup[0] <= tup[1]) fout<<tup[0]<<" "<<tup[1]<<endl;
////            else fout<<tup[1]<<" "<<tup[0]<<endl;
//            if(tup[0] == tup[1]) {num1++; continue;}
//            if(tup[0] > tup[1]) {int a = tup[0];  tup[0] = tup[1]; tup[1] = a;}
//            tuples.push_back(tup);
//        }
//    }
//    fin.clear();
//    fin.close();
//    Kquad* q = new Kquad();
//    q->quick(tuples, tuples.size());
//    vector<int> t = tuples[0];
//    int num = 0;
//    for(i = 1; i < tuples.size(); i++){
//        if(tuples[i][0] == t[0] && tuples[i][1] == t[1]) {num++; continue;}
//        fout<<tuples[i][0]<<" "<<tuples[i][1]<<endl;
//        t = tuples[i];
//    }
//    fout.clear();
//    fout.close();
//    cout<<"same: "<<num1<<", duplicate: "<<num<<endl;
    
    
    
    
    
    
    
    
    
    
    
    
    
    //Kquad* q = new Kquad();
    //q->quadratio(dataf, cpath, rpath, 3);
    //q->quadratio(dataf, cpath, rpath, 4);//compute matrics
    
    //q->addContents(neiPath, dblpPath, dblpPath1);
    
    //q->computesupport(dataPath, supPath, neiPath);
    
//    string line;
//    ifstream fin(supPath);
//    if (fin)
//    {
//        while (getline(fin, line))
//        {
//            istringstream iss(line);
//            string temp;
//            vector<int> tup;
//            while (getline(iss, temp, ' ')) {
//                tup.push_back(stoi(temp));
//            }
//            vector<int> e;
//            e.push_back(tup[0]);
//            e.push_back(tup[1]);
//            edge.push_back(e);
//            support.push_back(tup[2]);
//            neighbor[tup[0]].push_back(tup[1]);
//            neighbor[tup[1]].push_back(tup[0]);
//        }
//    }
//    cout<<edge.size()<<endl;
//    cout<<support.size()<<endl;
//    fin.clear();
//    fin.close();
//    for(int i = 0; i < neighbor.size(); i++){
//        q->quick_list(neighbor[i], neighbor[i].size());
//    }
    
    
    //q->compute1quad(dataPath, supPath, comPath);
    //q->computekquad(comPath, parentPath);
    
//    q->buildindex(comPath, indexPath);
    
    
    //q->pointquery(indexPath, pqueryPath, pqueryResult);
    //q->rangequery(indexPath, rqueryPath, rqueryResult);
    
    
    
    
    return 0;
}
