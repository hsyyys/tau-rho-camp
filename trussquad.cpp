//
//  trussquad.cpp
//  community
//
//  Created by lily on 2024/8/27.
//

#include "trussquad.h"

///---------------------------------------------------------------------------------------------------
bool Trussquad::cmpElement(vector<int> &a, vector<int> &b, int id) {///b大于等于a，返回true
    int i;
    bool sign = true;//0表示a大，1表示b大
    if(id == -1) {
        for (i = 0; i < a.size(); i++) {
            //cout << dim1[dimOrder[i]] << "  " << dim2[dimOrder[i]] << endl;
            if (a[i] < b[i]) {
                sign = true;
                break;
            }
            if (a[i] > b[i]) {
                sign = false;
                break;
            }
        }
    }
    else{
        if(a[id] > b[id]) sign = false;
    }
    return sign;
}
///----------------------------------------------------------------------------------------------------
int Trussquad::partitions(vector<vector<int>> &arr, int left, int right, int id) {
    swap(arr[left], arr[(left + right) / 2]);
    //cout << "left = " << left << " , right = " << right << endl;
    vector<int> pivot = arr[left];
    int tmp;
    while (left < right) {
        while (left < right && cmpElement(pivot, arr[right], id))//arr[right] > pivot
            right--;
        if (left < right) {
            arr[left++] = arr[right];
        }
        while (left < right && cmpElement(arr[left], pivot, id))//arr[left] < pivot
            left++;
        if (left < right) {
            arr[right--] = arr[left];
        }
    }
    arr[left] = pivot;
    return left;
}
///-----------------------------------------------------------------------------------------------------
void Trussquad::quick_sort(vector<vector<int>> &arr, int left, int right, int id) {
    if (right - left <= 0) {
        return;
    }
    int pivot;
    pivot = partitions(arr, left, right, id);
    // leave the pivot where it was
    quick_sort(arr, left, pivot - 1, id);
    quick_sort(arr, pivot + 1, right, id);
    return;
}
///-----------------------------------------------------------------------------------------------------
void Trussquad::quick(vector<vector<int>> &arr, int length, int id) {
    quick_sort(arr, 0, length - 1, id);
}
///-----------------------------------------------------------------------------------------------------
int Trussquad::partitions_list(vector<int> &arr, int left, int right) {
    swap(arr[left], arr[(left + right) / 2]);
    int pivot = arr[left];
    int tmp;
    while (left < right) {
        while (left < right && pivot < arr[right])//arr[right] > pivot
            right--;
        if (left < right) {
            arr[left++] = arr[right];
        }
        while (left < right && arr[left] < pivot)//arr[left] < pivot
            left++;
        if (left < right) {
            arr[right--] = arr[left];
        }
    }
    arr[left] = pivot;
    return left;
}
///---------------------------------------------------------------------------------------
void Trussquad::quick_sort_list(vector<int> &arr, int left, int right) {
    if (right - left <= 0) {
        return;
    }
    int pivot;
    pivot = partitions_list(arr, left, right);
    // leave the pivot where it was
    quick_sort_list(arr, left, pivot - 1);
    quick_sort_list(arr, pivot + 1, right);
    return;
}
///---------------------------------------------------------------------------------------
void Trussquad::quick_list(vector<int> &arr, int length) {
    quick_sort_list(arr, 0, length - 1);
}
///---------------------------------------------------------------------------------------
int Trussquad::intersaction(vector<int> &a, vector<int> &b, int &s) {
    int i = 0, j = 0;
    if(a.size()==0 || b.size()==0) return s;
    while(true){
        if(a[i]==b[j]) {
            s++; i++; j++;
        }
        else{
            if(a[i] < b[j]) i++;
            else j++;
        }
        if(i>=a.size() || j>=b.size()) break;
    }
    s--;
    return s;
}
///---------------------------------------------------------------------------------------
int Trussquad::computesupport(const char* datapath, const char* suppath, const char* neipath) {
    int i, j, g;
    string line;
    ifstream fin(datapath);
    if (fin)
    {
        while (getline(fin, line))
        {
            istringstream iss(line);
            string temp;
            vector<int> tup;
            while (getline(iss, temp, ' ')) {
                tup.push_back(stoi(temp));
            }
            if(tup.size()>2) {cout<<"abnormal"<<endl; return 0;}
            if(tup.size()==1) break;
            neighbor[tup[0]].push_back(tup[1]);
            neighbor[tup[1]].push_back(tup[0]);
            edge.push_back(tup);
        }
    }
    fin.clear();
    fin.close();
    edgenum = edge.size();
    
    //sort the neighgbors
    ofstream fout(neipath, ios::out);
    for(i = 0; i < neighbor.size(); i++){
        quick_list(neighbor[i], neighbor[i].size());
        string out = "";// = to_string(i) + ' ';
        int former = -1;
        for(j = 0; j < neighbor[i].size(); j++){
            if(neighbor[i][j] != former){
                out = out + to_string(neighbor[i][j]) + ' ' ;
                former = neighbor[i][j];
            }
        }
        fout<<out<<endl;
    }
    fout.clear();
    fout.close();
    cout<<"sort completes!"<<endl;
    
    //support
    support.resize(edgenum,0);
    tsupport.resize(edgenum,0);
    ofstream fout1(suppath, ios::out);
    for(i = 0; i < edge.size(); i++){
        if(i%100000==0) cout<<"line "<<i<<endl;
        int sup = 0, tsup = 0;
        intersaction(neighbor[edge[i][0]], neighbor[edge[i][1]], tsup);
        tsup++;
        for(j = 0; j < neighbor[edge[i][0]].size(); j++){//user's neighbors
            int video = neighbor[edge[i][0]][j];
            if(video==edge[i][1]) continue;
            intersaction(neighbor[edge[i][1]], neighbor[video], sup);
        }
        support[i] = sup;
        tsupport[i] = tsup;
        string ss = to_string(edge[i][0]) + " " + to_string(edge[i][1]) + " " + to_string(tsupport[i]) + " " + to_string(support[i]);
        fout1<< ss <<endl;
    }
    fout1.clear();
    fout1.close();
    cout<<"support complete"<<endl;
    return 0;
}
///---------------------------------------------------------------------------------------
int Trussquad::compute1quad(const char* datapath, const char* suppath, const char* compath) {
    int i;
    vector<vector<int>> newedge;//all the edges whose support is at least 1
    for(i = 0; i < edge.size(); i++){
        if(support[i] + tsupport[i] >= 1)
            newedge.push_back(edge[i]);
    }
    vector<int> rootlevel;
    tree.push_back(rootlevel);

    //get connected subgraphs
    int tlevel = 1, qlevel = 1, parentid = -1;
    vector<int> onelevelquad;
    connectedsubgraph(compath, newedge, onelevelquad, quadNo, tlevel, qlevel, parentid, 1);
    tree.push_back(onelevelquad);
    cout<<"1T1Q end!"<<endl;
    return 0;
}
///---------------------------------------------------------------------------------------
int Trussquad::connectedsubgraph(const char* compath, vector<vector<int>> &kedge, vector<int> &newlevel, int &quadid, int tlevel, int qlevel, int parentid, int minsupport) {
    int i, j;
    //1) find the neighbors
    vector<vector<int>> neighbor1(NODENUM);
    for(i = 0; i < kedge.size(); i++){
        neighbor1[kedge[i][0]].push_back(kedge[i][1]);
        neighbor1[kedge[i][1]].push_back(kedge[i][0]);
    }
    //2) union the neighbors to get the connected nodes
    queue<int> que;// the node list to find the neighbors
    vector<bool> nodebitmap(NODENUM, false);
    vector<bool> edgebitmap(kedge.size(), false);
    int enum_edgenum = 0;
    vector<int> nodeset;
    vector<int> edgeset;
    while(true){
        vector <int>().swap(nodeset);
        vector <int>().swap(edgeset);
        bool sign = true;
        //select a start edge to find the connected subgraph
        for(i = 0; i < kedge.size(); i++){
            if(edgebitmap[i]==false) {
                sign = false;
                que.push(kedge[i][0]); que.push(kedge[i][1]);
                nodebitmap[kedge[i][0]] = true;
                nodebitmap[kedge[i][1]] = true;
                nodeset.push_back(kedge[i][0]);
                nodeset.push_back(kedge[i][1]);
                edgebitmap[i] = true;
                enum_edgenum++;
                break;
            }
        }
        if(sign==true || nodeset.size()==0) break;
        
        //find the node set of the connected subgraph
        while(que.size()>0){
            int v = que.front();
            for(i = 0; i < neighbor1[v].size(); i++){
                if(nodebitmap[neighbor1[v][i]]==false) {
                    nodeset.push_back(neighbor1[v][i]);
                    que.push(neighbor1[v][i]);
                    nodebitmap[neighbor1[v][i]] = true;
                }
            }
            que.pop();
        }
        int max = (tlevel/2 > 3) ? tlevel/2 : 3;
        if(nodeset.size() < max) continue;
        max = (qlevel/2 > 4) ? qlevel/2 : 4;
        if(nodeset.size() < max) continue;
        
        //find the edge set of the connected subgraph
        quick_list(nodeset, nodeset.size());
//        for(i = 0; i < nodeset.size(); i++){
//            if(nodeset[i] >= USERNUM) continue;
//            for(j = 0; j < neighbor1[nodeset[i]].size(); j++){
//                if(nodeset[i] > neighbor1[nodeset[i]][j]) continue;
//                edgeset.push_back(nodeset[i]);
//                edgeset.push_back(neighbor1[nodeset[i]][j]);
//            }
//        }
        for(i = 0; i < nodeset.size(); i++){
            for(j = 0; j < neighbor1[nodeset[i]].size(); j++){
                if(type==0){//dblp
                     if(nodeset[i] < USERNUM){
                        edgeset.push_back(nodeset[i]);
                        edgeset.push_back(neighbor1[nodeset[i]][j]);
                    }
                    else{
                        if(neighbor1[nodeset[i]][j] >= USERNUM) {
                            if(nodeset[i] > neighbor1[nodeset[i]][j]) continue;
                            edgeset.push_back(nodeset[i]);
                            edgeset.push_back(neighbor1[nodeset[i]][j]);
                        }
                    }
                }
                else{
                    if(type==1){//bilibili, weibo
                        if(nodeset[i] >= USERNUM) continue;
                        if(nodeset[i] > neighbor1[nodeset[i]][j]) continue;
                        edgeset.push_back(nodeset[i]);
                        edgeset.push_back(neighbor1[nodeset[i]][j]);
                    }
                    else{//youtube
                        if(nodeset[i] > neighbor1[nodeset[i]][j]) continue;
                        edgeset.push_back(nodeset[i]);
                        edgeset.push_back(neighbor1[nodeset[i]][j]);
                    }
                }
            }
        }
        for(i = 0; i < kedge.size(); i++){
            if(nodebitmap[kedge[i][0]]==true) {//***add edge[i][0] is true for other k
                if(edgebitmap[i]==false) {
                    edgebitmap[i] = true;
                    enum_edgenum++;
                }
            }
        }
        cout<<"community "<<quadid<<": node "<<nodeset.size()<<", edge "<<edgeset.size()/2<<endl;
        //output
        string comfolder = compath;
        string communitypath = comfolder + to_string(tlevel)+ "_" + to_string(qlevel)+ "-" +to_string(quadid) + ".txt";
        const char* communityPath = communitypath.c_str();
        ofstream fout(communityPath, ios::out);
        string out = to_string(tlevel) + " " + to_string(qlevel) + " " + to_string(quadid) + " " + to_string(parentid) + " " + to_string(edgeset.size()/2) + " " + to_string(nodeset.size());
        fout<< out <<endl;
        vector<int> v ;
        v.push_back(tlevel); v.push_back(qlevel); v.push_back(quadid); v.push_back(parentid);
        parent.push_back(v);
        out = "";
        for(i = 0; i < edgeset.size()/2; i++){
            out = to_string(edgeset[2*i]) + " " + to_string(edgeset[2*i+1]);
            fout<<out<<endl;
        }
        out = "";
        quick_list(nodeset, nodeset.size());
        for(i = 0; i < nodeset.size(); i++){
            out = to_string(nodeset[i]);
            fout<<out<<endl;
        }
        fout.clear();
        fout.close();
        newlevel.push_back(quadid);
        minsup.push_back(minsupport);
        comsize.push_back(edgeset.size()/2);
        if(quadid==0) keepunchanged.push_back(0);
        else {
            if(comsize[parentid] == comsize[quadid])
                keepunchanged.push_back(keepunchanged[parentid]+1);
            else keepunchanged.push_back(0);
        }
        quadid++;
        if(enum_edgenum>=kedge.size()) break;
    }
    vector <int>().swap(nodeset);
    vector <int>().swap(edgeset);
    vector <vector<int>>().swap(neighbor1);
    return 0;
}
///---------------------------------------------------------------------------------------
int Trussquad::computekquad(const char* compath, const char* parentpath) {
    int i;
    ofstream fout(parentpath, ios::app);
    string out;
    int totaldeledgenum = 0;
    vector<bool> edgeexist(edge.size(), true);//if an edge is still in k-quad (undeleted)
    for(i = 0; i < edge.size(); i++){
        if (support[i]==0 && tsupport[i]==0){
            edgeexist[i] = false;
            totaldeledgenum++;
        }
    }
    //unordered_map<string, int> map;//map each edge to its id
    for(i = 0; i < edge.size(); i++){
        out = to_string(edge[i][0]) + " " + to_string(edge[i][1]);
        map.insert(make_pair(out, i));
    }
    queue<vector<int>> splitquad;//store the k-quad to be decomposed to (k+1)-quad, vector<int> stores the truss level and quad level and the quad id
    for(i = 0; i < tree[1].size(); i++){//1T1Q
        vector<int> v = {1,1,tree[1][i]};
        splitquad.push(v);
    }
    vector<int> newlevelquad;//store the obtained new (k+1)-quads -> (k1+1)Tk2Q or k1T(k2+1)Q
    //decompose the quads in splitqaud to get the nested communities
    int trusslevel, quadlevel, quadid;
    while(true){//pop splitquad
        if(splitquad.size()==0) break;
        trusslevel = splitquad.front()[0];//truss level
        quadlevel = splitquad.front()[1];//quad level
        quadid = splitquad.front()[2];//the current kquad that should be splited, ancestor quad id
        //the edges of the current kquad
        vector<vector<int>>().swap(quadedge);
        neighbor1.clear();
        neighbor1.resize(NODENUM);
        
        readcommunity(compath, trusslevel, quadlevel, quadid, quadedge);
        if(quadedge.size()==0) {
            if(splitquad.size()==0) break;
            else{splitquad.pop(); continue;}
        }
        //find the neighbors
        for(i = 0; i < quadedge.size(); i++){
            neighbor1[quadedge[i][0]].push_back(quadedge[i][1]);
            neighbor1[quadedge[i][1]].push_back(quadedge[i][0]);
        }
        for(i = 0; i < neighbor1.size(); i++){
            quick_list(neighbor1[i], neighbor1[i].size());
        }
        vector<int16_t> tsupport1 = tsupport;//truss support
        vector<int16_t> qsupport1 = support;//quad support
        vector<int16_t> tsupport2 = tsupport;//truss support
        vector<int16_t> qsupport2 = support;//quad support
        vector<bool> edgeexist1 = edgeexist;
        vector<bool> edgeexist2 = edgeexist;
        int quadNo1 = quadNo;//child quad id
        int quadNo2 = quadNo;
        int totaldeledgenum1 = totaldeledgenum;
        int totaldeledgenum2 = totaldeledgenum;

        //partition
        vector<vector<int>> newquadedge1;
        vector<vector<int>> newquadedge2;
        partitionCommunity(0, newquadedge1, edgeexist1, tsupport1, qsupport1,
                           trusslevel, quadlevel, quadid, quadNo1, totaldeledgenum1);
        partitionCommunity(1, newquadedge2, edgeexist2, tsupport2, qsupport2,
                           trusslevel, quadlevel, quadid, quadNo2, totaldeledgenum2);
        //compute and compare metric
        int min1 = INT_MAX, min2 = INT_MAX;
        for(i = 0; i < newquadedge1.size(); i++){
            int eid = map.at(to_string(newquadedge1[i][0])+" "+to_string(newquadedge1[i][1]));
            if(tsupport1[eid] + qsupport1[eid] < min1)
                min1 = tsupport1[eid] + qsupport1[eid];
        }
        for(i = 0; i < newquadedge2.size(); i++){
            int eid = map.at(to_string(newquadedge2[i][0])+" "+to_string(newquadedge2[i][1]));
            if(tsupport2[eid] + qsupport2[eid] < min2)
                min2 = tsupport2[eid] + qsupport2[eid];
        }
//        if((min1 == minsup[quadid] && min2 <= minsup[quadid]) || (min1 <= minsup[quadid] && min2 == minsup[quadid])) {
//            if(++keepunchanged[quadid] >= 20) {
//                splitquad.pop();
//                continue;
//            }
//        }
        
        if(keepunchanged[quadid] >= 50) {
            splitquad.pop();
            continue;
        }
            
        if(min1 > min2){
            tsupport = tsupport1;
            support = qsupport1;
            edgeexist = edgeexist1;
            totaldeledgenum = totaldeledgenum1;
            vector<int> newcommunity;
            connectedsubgraph(compath, newquadedge1, newcommunity, quadNo,trusslevel+1, quadlevel, quadid, min1);
            for(i = 0; i < newcommunity.size(); i++){
                vector<int> vec = {trusslevel+1, quadlevel, newcommunity[i]};
                splitquad.push(vec);
            }
        }
        else{
            tsupport = tsupport2;
            support = qsupport2;
            edgeexist = edgeexist2;
            totaldeledgenum = totaldeledgenum2;
            vector<int> newcommunity;
            connectedsubgraph(compath, newquadedge2, newcommunity, quadNo,trusslevel, quadlevel+1, quadid, min2);
            for(i = 0; i < newcommunity.size(); i++){
                vector<int> vec = {trusslevel, quadlevel+1, newcommunity[i]};
                splitquad.push(vec);
            }
        }
        //break the loop
        if(totaldeledgenum>=edge.size()) {
            cout<<totaldeledgenum<<" "<<edge.size()<<endl;
            break;
        }
        splitquad.pop();
        if(splitquad.size()==0) {
            break;
        }
        vector<vector<int>>().swap(quadedge);
        vector<vector<int>>().swap(neighbor1);
    }
    
    for(i = 0; i < parent.size()-1; i++)
        fout<< to_string(parent[i][0]) + " " + to_string(parent[i][1]) + " " + to_string(parent[i][2]) + " " + to_string(parent[i][3]) <<endl;
    fout.clear();
    fout.close();
    return 0;
}
//-----------------------------------------------------------------------------------------
int Trussquad::partitionCommunity(int sign, vector<vector<int>> &newquadedge, vector<bool> &edgeexist0, vector<int16_t> &tsupport, vector<int16_t> &qsupport, int trusslevel, int quadlevel, int parentid, int quadNo0, int &taldeledgenum){
    int i, j, k, g;
    //for the community with 'quadedge', find edge whose support is less than k and delete
    queue<anedge> deleteedge;
    int eid;
    for(i = 0; i < quadedge.size(); i++){
        eid = map.at(to_string(quadedge[i][0])+" "+to_string(quadedge[i][1]));
        if(sign==0){//truss level increase
            if(tsupport[eid] < trusslevel+1 && qsupport[eid] < quadlevel && edgeexist0[eid]==true){
                deleteedge.push(anedge(edge[eid][0], edge[eid][1]));
                edgeexist0[eid] = false;
                taldeledgenum++;
            }
        }
        else{//quad level increase
            if(qsupport[eid] < quadlevel+1 && tsupport[eid] < trusslevel && edgeexist0[eid]==true) {
                //delete the edge
                deleteedge.push(anedge(edge[eid][0], edge[eid][1]));
                edgeexist0[eid] = false;
                taldeledgenum++;
            }
        }
    }
    if(deleteedge.size()==0) {//k+1-quad is complete k-quad
        newquadedge = quadedge;
        return 0;
    }

    //when minus support, each rectangle must be minus once
    int rectangleid = 0, triangleid = 0;
    unordered_map<string, int> rectangle;
    unordered_map<string, int> triangle;
    //delete edges whose support is less than k+1
    while(true){//per delete edge
        //delete the edges and change the support of its neighboring edges
        if(deleteedge.size()==0) break;
        anedge a = deleteedge.front();
        int eid0 = map.at(to_string(a.from)+" "+to_string(a.to));
        if(qsupport[eid0]==0 && tsupport[eid0]==0) {//the edge is already deleted
            deleteedge.pop();
            continue;
        }
        //minus the truss support of the edges that compose triangle with the current edge
        tsupport[eid0] = 0; qsupport[eid0] = 0;
        i = 0; g = 0;
        while(i < neighbor1[a.to].size() && g < neighbor1[a.from].size()){//find common neighbors
            if(neighbor1[a.to][i]==neighbor1[a.from][g]) {
                int commonuser = neighbor1[a.to][i];
                vector<int> v = {a.from, commonuser, a.to};
                quick_list(v, v.size());
                string s = "";
                for(k = 0; k < v.size(); k++)
                    s = s + to_string(v[k]) + " ";
                if(triangle.find(s)!=triangle.end()) {i++;g++;continue;}//already minus
                triangle.insert(make_pair(s, triangleid++));
                int eid1 = a.from<commonuser ? map.at(to_string(a.from)+" "+to_string(commonuser)) : map.at(to_string(commonuser)+" "+to_string(a.from));
                int eid2 = a.to<commonuser ? map.at(to_string(a.to)+" "+to_string(commonuser)) : map.at(to_string(commonuser)+" "+to_string(a.to));
                if(--tsupport[eid1] < trusslevel+1 && qsupport[eid1] < quadlevel && edgeexist0[eid1]==true) {
                    deleteedge.push(anedge(edge[eid1][0], edge[eid1][1]));
                    edgeexist0[eid1] = false;
                    taldeledgenum++;
                }
                if(--tsupport[eid2] < trusslevel+1 && qsupport[eid2] < quadlevel && edgeexist0[eid2]==true) {
                    deleteedge.push(anedge(edge[eid2][0], edge[eid2][1]));
                    edgeexist0[eid2] = false;
                    taldeledgenum++;
                }
                i++; g++;
            }
            else{
                if(neighbor1[a.to][i] < neighbor1[a.from][g]) i++;
                else g++;
            }
        }
        //minus the quad support of the edges that compose rectangle with the current edge
        for(j = 0; j < neighbor1[a.from].size(); j++){//user's video neighbors
            int video = neighbor1[a.from][j];//a video neighbor
            if(video==a.to) continue;
            i = 0, g = 0;
            while(i < neighbor1[a.to].size() && g < neighbor1[video].size()){//find common user neighbors
                if(neighbor1[a.to][i]==neighbor1[video][g]) {
                    int commonuser = neighbor1[a.to][i];
                    if(commonuser==a.from) {
                        i++;g++;
                        continue;
                    }
                    vector<int> v = {a.from, commonuser, a.to, video};
                    quick_list(v, v.size());
                    string s = "";
                    for(k = 0; k < v.size(); k++)
                        s = s + to_string(v[k]) + " ";
                    if(rectangle.find(s)!=rectangle.end()) {i++;g++;continue;}//already minus
                    rectangle.insert(make_pair(s, rectangleid++));
                    //int eid0 = map.at(to_string(a.from)+" "+to_string(a.to));
                    int eid1 = a.from<video ? map.at(to_string(a.from)+" "+to_string(video)) : map.at(to_string(video)+" "+to_string(a.from));
                    int eid2 = video<commonuser ? map.at(to_string(video)+" "+to_string(commonuser)) : map.at(to_string(commonuser)+" "+to_string(video));
                    int eid3 = a.to<commonuser ? map.at(to_string(a.to)+" "+to_string(commonuser)) : map.at(to_string(commonuser)+" "+to_string(a.to));
                    //qsupport[eid0] = 0;
                    if(--qsupport[eid1] < quadlevel+1 && tsupport[eid1] < trusslevel && edgeexist0[eid1]==true) {
                        deleteedge.push(anedge(edge[eid1][0], edge[eid1][1]));
                        edgeexist0[eid1] = false;
                        taldeledgenum++;
                    }
                    if(--qsupport[eid2] < quadlevel+1 && tsupport[eid2] < trusslevel && edgeexist0[eid2]==true) {
                        deleteedge.push(anedge(edge[eid2][0], edge[eid2][1]));
                        edgeexist0[eid2] = false;
                        taldeledgenum++;
                    }
                    if(--qsupport[eid3] < quadlevel+1 && tsupport[eid3] < trusslevel && edgeexist0[eid3]==true) {
                        deleteedge.push(anedge(edge[eid3][0], edge[eid3][1]));
                        edgeexist0[eid3] = false;
                        taldeledgenum++;
                    }
                    i++; g++;
                }
                else{
                    if(neighbor1[a.to][i] < neighbor1[video][g]) i++;
                    else g++;
                }
            }
        }
        deleteedge.pop();
    }
    
    //find connected graphs
    for(i = 0; i < quadedge.size(); i++){
        int eid1 = map.at(to_string(quadedge[i][0])+" "+to_string(quadedge[i][1]));
        if(edgeexist0[eid1] == true) newquadedge.push_back(quadedge[i]);
    }
    return 0;
}
///---------------------------------------------------------------------------------------
int Trussquad::readcommunity(const char* compath, int tlevel, int level, int id, vector<vector<int>> &edgelist) {
    string comfolder = compath;
    string communitypath = comfolder + to_string(tlevel)+ "_" + to_string(level)+ "-" +to_string(id) + ".txt";
    const char* communityPath = communitypath.c_str();
    string line;
    int lineno = 0, edgenumber = 0;
    ifstream fin(communityPath);
    if (fin)
    {
        while (getline(fin, line))
        {
            istringstream iss(line);
            string temp;
            vector<int> tup;
            while (getline(iss, temp, ' ')) {
                tup.push_back(stoi(temp));
            }
            if(lineno==0) edgenumber = tup[4];
            else{
                edgelist.push_back(tup);
            }
            if(lineno++ == edgenumber) break;
        }
    }
    fin.clear();
    fin.close();
    
    return 0;
}
///---------------------------------------------------------------------------------------
int Trussquad::copyquad(const char* compath, int oldtlevel, int oldqlevel, int oldid, int newtlevel, int newqlevel, int newid) {
    string comfolder = compath;
    string oldpath = comfolder + to_string(oldtlevel)+ "_" + to_string(oldqlevel)+ "-" +to_string(oldid) + ".txt";
    const char* oldPath = oldpath.c_str();
    string newpath = comfolder + to_string(newtlevel)+ "_" + to_string(newqlevel)+ "-" +to_string(newid) + ".txt";
    const char* newPath = newpath.c_str();
    ofstream fout(newPath, ios::out);
    string out;
    ifstream fin(oldPath);
    string line;
    int lnum = 0;
    int edgesetsize, nodesetsize;
    if (fin)
    {
        while (getline(fin, line))
        {
            if(lnum++==0) {
                istringstream iss(line);
                string temp;
                vector<int> tup;
                while (getline(iss, temp, ' ')) {
                    tup.push_back(stoi(temp));
                }
                out = to_string(newtlevel) + " " + to_string(newqlevel) + " " + to_string(newid) + " " + to_string(oldid) + " " + to_string(tup[4]) + " " + to_string(tup[5]);
                fout<<out<<endl;
            }
            else
                fout<<line<<endl;
        }
    }
    fin.clear();
    fin.close();
    fout.clear();
    fout.close();
    return 0;
}
///---------------------------------------------------------------------------------------
int Trussquad::buildindex(const char* compath, const char* indexpath) {
    int i, j, k;
    string line;
    filesystem::path folderPath(compath);
    string folder = compath;
    vector<string> filename;
    vector<vector<int>> commu;
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            filename.push_back(entry.path().filename().string());
            k = filename[filename.size()-1].find("_");
            i = filename[filename.size()-1].find("-");
            j = filename[filename.size()-1].find(".");
            string str2 = filename[filename.size()-1].substr(i+1, j-i-1);
            string str1 = filename[filename.size()-1].substr(k+1, i-k-1);
            string str = filename[filename.size()-1].substr(0,k);
            vector<int> v = {stoi(str), stoi(str1), stoi(str2)};//level, community ID
            commu.push_back(v);
        }
    }
    quick(commu, commu.size(), 2);//sort communities by their community id
    vector<vector<int>> index(NODENUM);
    for(i = commu.size()-1; i >= 0; i--){
        string path = folder + to_string(commu[i][0]) + "_" + to_string(commu[i][1]) + "-" + to_string(commu[i][2]) + ".txt";
        const char* Path = path.c_str();
        ifstream fin(Path);
        if (fin)
        {
            while (getline(fin, line))
            {
                istringstream iss(line);
                string temp;
                vector<int> tup;
                while (getline(iss, temp, ' ')) {
                    tup.push_back(stoi(temp));
                }
                if(tup.size()>1) continue;
                index[tup[0]].push_back(commu[i][0]);//tlevel
                index[tup[0]].push_back(commu[i][1]);//qlevel
                index[tup[0]].push_back(commu[i][2]);//com ID
            }
        }
        fin.clear();
        fin.close();
        cout<<i<<endl;
    }
    ofstream fout(indexpath, ios::out);
    for(i = 0; i < NODENUM; i++){
        line = to_string(i) + " " ;
        for(j = 0; j < index[i].size()/3; j++){
            line = line + to_string(index[i][3*j]) + " " + to_string(index[i][3*j+1]) + " " + to_string(index[i][3*j+2]) + " ";
        }
        fout<< line <<endl;
    }
    fout.clear();
    fout.close();
    
    return 0;
}
///---------------------------------------------------------------------------------------
int Trussquad::readindex(const char* indexpath, vector<vector<vector<int>>> &index) {
    int i;
    string line;
    index.resize(NODENUM);
    for(i = 0; i < NODENUM; i++)
        index[i].resize(3);
    ifstream fin(indexpath);
    if (fin)
    {
        while (getline(fin, line))
        {
            istringstream iss(line);
            string temp;
            vector<int> tup;
            while (getline(iss, temp, ' ')) {
                tup.push_back(stoi(temp));
            }
            for(i = 0; i < tup.size()/3; i++){
                index[tup[0]][0].push_back(tup[3*i+1]);
                index[tup[0]][1].push_back(tup[3*i+2]);
                index[tup[0]][2].push_back(tup[3*i+3]);
            }
        }
    }
    fin.clear();
    fin.close();
    
    return 0;
}
///---------------------------------------------------------------------------------------
int Trussquad::readrangequery(const char* querypath, vector<vector<int>> &query) {
    string line;
    ifstream fin(querypath);
    if (fin)
    {
        while (getline(fin, line))
        {
            istringstream iss(line);
            string temp;
            vector<int> tup;
            while (getline(iss, temp, ' ')) {
                tup.push_back(stoi(temp));
            }
            query.push_back(tup);
        }
    }
    fin.clear();
    fin.close();
    
    return 0;
}
///---------------------------------------------------------------------------------------
int Trussquad::readpointquery(const char* querypath, vector<int> &query) {
    string line;
    ifstream fin(querypath);
    if (fin)
    {
        while (getline(fin, line))
        {
            istringstream iss(line);
            query.push_back(stoi(line));
        }
    }
    fin.clear();
    fin.close();
    
    return 0;
}
///---------------------------------------------------------------------------------------
int Trussquad::pointquery(const char* indexpath, const char* querypath, const char* pointresult) {
    int i,j;
    vector<vector<vector<int>>> index;
    vector<int> query;
    vector<vector<int>> result;
    readindex(indexpath, index);
    readpointquery(querypath, query);
    ofstream fout(pointresult, ios::out);
    //************
    for(i = 0; i < query.size(); i++){
        if(index[query[i]][0].size() >= 1){
            //tlevel, qlevel, com ID
            result.push_back({index[query[i]][0][0], index[query[i]][1][0], index[query[i]][2][0]});
        }
        else result.push_back({-1, -1, -1});
    }
    //***********
    for(i = 0; i < result.size(); i++)
        fout<<to_string(result[i][0])<<" "<<to_string(result[i][1])<<" "<<to_string(result[i][2])<<" "<<endl;
    fout.clear();
    fout.close();
    return 0;
}
///---------------------------------------------------------------------------------------
int Trussquad::rangequery(const char* indexpath, const char* querypath, const char* rangeresult) {
    int i,j,k;
    vector<vector<vector<int>>> index;
    vector<vector<int>> query;
    readindex(indexpath, index);
    readrangequery(querypath, query);
    ofstream fout(rangeresult, ios::out);
    vector<vector<int>> result;
    //**********
    for(i = 0; i < query.size(); i++){
        vector<vector<int>> v;
        for(j = 0; j < query[i].size(); j++){
            v.push_back(index[query[i][j]][2]);
        }
        int id = findCommonid(v);
        if(id==-1) result.push_back({-1, -1, -1});
        else result.push_back({index[query[i][0]][0][id], index[query[i][0]][1][id], index[query[i][0]][2][id]});
    }
    //*********
    for(i = 0; i < query.size(); i++){
        fout << to_string(result[i][0]) + " " + to_string(result[i][1]) + " " + to_string(result[i][2])<<endl;
    }
    fout.clear();
    fout.close();
    return 0;
}
///---------------------------------------------------------------------------------------
int Trussquad::findCommonid(vector<vector<int>> v) {
    int i, j;
    vector<int> vec;
//    int min = v[0][0], place = 0;
//    vector<int> pos(v.size(), 0);
//    for(i = 1; i < v.size(); i++)
//        if(v[i][0] < min) {min = v[i][0]; place = i;}
//    for(i = 0; i < v.size(); i++){
//        if(i == place) continue;
//        pos[i] = binarysearch(v[i], min);
//    }
//    while(true){
//    }
    
    for(i = 0; i < v.size(); i++)
        vec.insert(vec.end(), v[i].begin(), v[i].end());
    quick_list(vec, vec.size());
    int former = -1, num = 1;
    for(i = vec.size()-1; i >= 0; i--){
        if(vec[i] != former){
            former = vec[i];
            num = 1;
        }
        else {
            if(++num == v.size()) break;
        }
    }
    if(num < v.size()) return -1;
    return binarysearch(v[0], former);
}
///---------------------------------------------------------------------------------------
int Trussquad::binarysearch(vector<int> a, int tgt){//a是倒序
    int low = 0;
    int high = a.size() - 1;
    int middle;
    while (low <= high) {
        if (high - low <= 1) {
            return high;
        }
        middle = (low + high) / 2;
        if (a[middle] < tgt) {
            //比关键字小则关键字在左区域
            high = middle - 1;
        }
        else if (a[middle] > tgt) {
            //比关键字大则关键字在右区域
            low = middle + 1;
        }
        else {
            return middle;
        }
    }
    return -1;
}
///---------------------------------------------------------------------------------------
int Trussquad::find2hopneighbors(const char* datapath, const char* graphpath){
    int i;
    vector<vector<int>> neighbor(NODENUM);
    string line;
    ifstream fin(datapath);
    if (fin)
    {
        while (getline(fin, line))
        {
            istringstream iss(line);
            string temp;
            vector<int> tup;
            while (getline(iss, temp, ' ')) {
                tup.push_back(stoi(temp));
            }
            neighbor[tup[0]].push_back(tup[1]);
            neighbor[tup[1]].push_back(tup[0]);
        }
    }
    fin.clear();
    fin.close();
    
    ofstream fout1(graphpath, ios::out);
    for(i = 0; i < USERNUM; i++){
        int n = 0;
        unordered_map<int, int> maps;
        if(i%100000==0) cout<<"line "<<i<<endl;
        for(int a: neighbor[i]){//user's neighbors
            if(a < USERNUM) continue;
            for(int b : neighbor[a]){
                if(b <= i || maps.find(b)!=maps.end() || intersaction1(neighbor[i], neighbor[b])<0) continue;
                maps.insert(make_pair(b, n++));
            }
        }
        for(auto g : maps){
            fout1 << i << " "<< g.first << endl;
        }
    }
    
    fout1.clear();
    fout1.close();
    
    return 0;
}
///---------------------------------------------------------------------------------------
int Trussquad::intersaction1(vector<int> &a, vector<int> &b) {
    int i = 0, j = 0;
    if(a.size()==0 || b.size()==0) return -1;
    while(true){
        if(a[i]>=USERNUM || b[j]>=USERNUM) return -1;
        if(a[i]==b[j]) {
           return 1;
        }
        else{
            if(a[i] < b[j]) i++;
            else j++;
        }
        if(i>=a.size() || j>=b.size()) break;
    }
    return -1;
}
