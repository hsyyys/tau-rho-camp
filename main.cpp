//
//  main.cpp
//  community
//
//  Created by lily on 2024/7/3.
//

#include "common.h"
#include "trussquad.h"

int NODENUM;
int NODE;
int USERNUM;
int USER;
vector<vector<int>> neighbor;
vector<vector<int>> edge;
vector<int16_t> support;
vector<int16_t> tsupport;
int edgenum;

int main(int argc, const char * argv[]) {
    if (argc != 6 && argc != 8 && argc != 9) {
        std::cerr << "Usage1-onlyMakeIndex: " << argv[0] << " <datapath> <indexfolder> <maxuser> <maxnode> <datatype>" << std::endl;
        std::cerr << "Usage2-onlyQuery: " << argv[0] << " <indexfolder> <querypath> <queryresult> <is_onePoint> <maxuser> <maxnode> <datatype>" << std::endl;
        std::cerr << "Usage3-MakeIndex+Query: " << argv[0] << " <datapath> <indexfolder> <querypath> <queryresult> <is_onePoint> <maxuser> <maxnode> <datatype>" << std::endl;
        return 1;
    }
    else if (argc == 6) {
            std::cout << "Usage1-onlyMakeIndex:" << argv[1] << " " << argv[2] << " "  << argv[3]<< " "  << argv[4] << " " << argv[5] <<endl;
            USER = std::atoi(argv[3]);
            USERNUM = USER + 1;
            NODE = std::atoi(argv[4]);
            NODENUM = NODE + 1;
            const int datatype = std::atoi(argv[5]);
            const string datapath = argv[1];
            const char* dataPath = datapath.c_str();
            const string indexfolder = argv[2];
            string suppath = indexfolder + "/support.txt";
            const char* supPath = suppath.c_str();
            string neipath = indexfolder + "/neighbor.txt";
            const char* neiPath = neipath.c_str();
            string compath = indexfolder + "/community/";
            const char* comPath = compath.c_str();
            string parentpath = indexfolder + "/parent.txt";
            const char* parentPath = parentpath.c_str();
            string indexpath = indexfolder + "/index.txt";
            const char* indexPath = indexpath.c_str();

            Trussquad* tq = new Trussquad(datatype);
            auto Index_start = chrono::high_resolution_clock::now(); // 记录开始时间

            tq->computesupport(dataPath, supPath, neiPath);
            tq->compute1quad(dataPath, supPath, comPath);
            tq->computekquad(comPath, parentPath);
            tq->buildindex(comPath, indexPath);
            auto Index_end = chrono::high_resolution_clock::now(); // 记录结束时间
            auto Index_duration = chrono::duration_cast<chrono::milliseconds>(Index_end - Index_start); // 计算运行时间
            cout << "Index_Duration: " << Index_duration.count() << " milliseconds" << endl;
    }
    else if (argc == 8) {
            std::cout << "Usage2-onlyQuery:" << argv[1] << " " << argv[2] << " "  << argv[3]<< " "  << argv[4] << " " << argv[5] << " " << argv[6] << " " << argv[7] <<endl;
            const int datatype = std::atoi(argv[7]);
            USER = std::atoi(argv[5]);
            USERNUM = USER + 1;
            NODE = std::atoi(argv[6]);
            NODENUM = NODE + 1;

            const string indexfolder = argv[1];
            string indexpath = indexfolder + "/index.txt";
            const char* indexPath = indexpath.c_str();
            const string querypath = argv[2];
            const char* queryPath = querypath.c_str();
            string queryresult =  argv[3];
            const char* queryResult = queryresult.c_str();
            const bool is_onePoint = (std::string(argv[4]) == "true");
            Trussquad* tq = new Trussquad(datatype);
            if (is_onePoint) tq->pointquery(indexPath, queryPath, queryResult);
            else tq->rangequery(indexPath, queryPath, queryResult);
    }
    else {
            std::cout << "Usage3-MakeIndex+Query:" << argv[1] << " " << argv[2] << " "  << argv[3]<< " "  << argv[4] << " " << argv[5] << " " << argv[6] << " " << argv[7] << " " << argv[8] <<endl;
            USER = std::atoi(argv[6]);
            USERNUM = USER + 1;
            NODE = std::atoi(argv[7]);
            NODENUM = NODE + 1;
            const int datatype = std::atoi(argv[8]);
            const string datapath = argv[1];
            const char* dataPath = datapath.c_str();
            const string indexfolder = argv[2];
            string suppath = indexfolder + "/support.txt";
            const char* supPath = suppath.c_str();
            string neipath = indexfolder + "/neighbor.txt";
            const char* neiPath = neipath.c_str();
            string compath = indexfolder + "/community/";
            const char* comPath = compath.c_str();
            string parentpath = indexfolder + "/parent.txt";
            const char* parentPath = parentpath.c_str();
            string indexpath = indexfolder + "/index.txt";
            const char* indexPath = indexpath.c_str();
            const string querypath = argv[3];
            const char* queryPath = querypath.c_str();
            string queryresult =  argv[4];
            const char* queryResult = queryresult.c_str();
            const bool is_onePoint = (std::string(argv[5]) == "true");

            Trussquad* tq = new Trussquad(datatype);
            auto Index_start = chrono::high_resolution_clock::now(); // 记录开始时间
            tq->computesupport(dataPath, supPath, neiPath);
            tq->compute1quad(dataPath, supPath, comPath);
            tq->computekquad(comPath, parentPath);
            tq->buildindex(comPath, indexPath);

            auto Index_end = chrono::high_resolution_clock::now(); // 记录结束时间
            auto Index_duration = chrono::duration_cast<chrono::milliseconds>(Index_end - Index_start); // 计算运行时间
            cout << "Index_Duration: " << Index_duration.count() << " milliseconds" << endl;

            if (is_onePoint) tq->pointquery(indexPath, queryPath, queryResult);
            else tq->rangequery(indexPath, queryPath, queryResult);
    }
    return 0;
}
