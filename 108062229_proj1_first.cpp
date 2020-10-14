#include <iostream>
#include <climits>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>

#define pii pair<int, int>
#define mk make_pair

using namespace std;

class block {
    public:
        vector<vector<int>> col_row;
        int n_row[4];
        int b_col_size;

        block(pii* arr) {
            int ord = 0;
            vector<int> v;
            for(int i = 0; i < 4; i++) {
                while(arr[ord].first == i && ord < 4) {
                    v.push_back(arr[ord].second);
                    n_row[arr[ord].second] = i;
                    ord++;
                }
                col_row.push_back(v);
                v.clear();
                if(ord == 4) break;
            }
            b_col_size = col_row.size();
        };
        ~block(){};
};

class game {
    public:
        list<int> puzzle[40];
        int highest[40] = {0};
        int n_row[15] = {0};
        int row = 0, col = 0;

        game(int m, int n): row(m), col(n) {
            for(int i = 0; i < n; ++i) {
                list<int> a;
                puzzle[i] = a;
            }
        };
        ~game(){};
        int first_fall(block* b, int b_col) {
            int mn = INT_MAX;
            for(auto v: b->col_row) {
                mn = min(mn, (v[0] + row - highest[b_col++]));
                //cout<<"mn: "<<mn<<endl;
            }
            return row - mn;
        };
        int final_fall(block* b, int b_row, int b_col) {
            int n = b->b_col_size, mn = INT_MAX;
            for(int i = 0; i < n; ++i) {
                int tetris_col = i + b_col; 
                vector<int> v = b->col_row[i];
                list<int>::iterator it = puzzle[tetris_col].begin();
                if(it == puzzle[tetris_col].end()) mn = min(v[0] + b_row, mn); 
                else {
                    while(*it < b_row && it != puzzle[tetris_col].end()) it++;
                    it--;
                    mn = min(v[0] + b_row - 1 - (*it), mn);
                }    
            }
            return b_row - mn;
        };
        void place(block* b, int b_row, int b_col) {
            int n = b->b_col_size;
            //cout<<"n: "<<n<<endl;
            for(int i = 0; i < n; ++i) {
                int tetris_col = i + b_col; 
                vector<int> v = b->col_row[i];
                list<int>::iterator it = puzzle[tetris_col].begin();
            
                while(it != puzzle[tetris_col].end() && *it < b_row + v[0]) it++;
                if(it == puzzle[tetris_col].end()) highest[tetris_col] = v.back() + 1 + b_row;
                for(auto r: v) {
                    puzzle[tetris_col].insert(it, r + b_row);
                    n_row[r + b_row]++;
                    //cout<<"r: "<<r + b_row<<" col: "<<n_row[r + b_row]<<endl;
                }
            }
        };
        void del() {
            for(int i = 0; i < row; ++i) {
                if(n_row[i] == col) {
                    //cout<<"i: "<<i<<endl;
                    
                    for(int j = i; j < row - 1; ++j) n_row[j] = n_row[j + 1];
                    n_row[row - 1] = 0;
                    for(int i = 0; i < col; ++i) highest[i]--;
                    
                    for(int j = 0; j < col; ++j) {
                        list<int>::iterator it = find(puzzle[j].begin(), puzzle[j].end(), i);
                        it = puzzle[j].erase(it);
                        for(auto it_b = it; it_b != puzzle[j].end(); it_b++) (*it_b)--;
                    }
                    i--;
                    
                }
            }
        }
        bool gameover() {
            for(int i = 0; i < col; i++) {
                if(*puzzle[i].end() >= row) return 1;
            }
            return 0;
        }
};

pii t1[4] = {{0, 1}, {1, 0}, {1, 1}, {2, 1}};
pii t2[4] = {{0, 1}, {1, 0}, {1, 1}, {1, 2}};
pii t3[4] = {{0, 0}, {1, 0}, {1, 1}, {2, 0}};
pii t4[4] = {{0, 0}, {0, 1}, {0, 2}, {1, 1}};
pii l1[4] = {{0, 0}, {0, 1}, {0, 2}, {1, 0}};
pii l2[4] = {{0, 0}, {0, 1}, {1, 1}, {2, 1}};
pii l3[4] = {{0, 2}, {1, 0}, {1, 1}, {1, 2}};
pii l4[4] = {{0, 0}, {1, 0}, {2, 0}, {2, 1}};
pii j1[4] = {{0, 0}, {1, 0}, {1, 1}, {1, 2}};
pii j2[4] = {{0, 0}, {0, 1}, {1, 0}, {2, 0}};
pii j3[4] = {{0, 0}, {0, 1}, {0, 2}, {1, 2}};
pii j4[4] = {{0, 1}, {1, 1}, {2, 0}, {2, 1}};
pii s1[4] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
pii s2[4] = {{0, 1}, {0, 2}, {1, 0}, {1, 1}};
pii z1[4] = {{0, 1}, {1, 0}, {1, 1}, {2, 0}};
pii z2[4] = {{0, 0}, {0, 1}, {1, 1}, {1, 2}};
pii i1[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}};
pii i2[4] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
pii o[4] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};

block T1(t1);
block T2(t2);
block T3(t3);
block T4(t4);
block L1(l1);
block L2(l2);
block L3(l3);
block L4(l4);
block J1(j1);
block J2(j2);
block J3(j3);
block J4(j4);
block S1(s1);
block S2(s2);
block Z1(z1);
block Z2(z2);
block I1(i1);
block I2(i2);
block O(o);

int main (int argc, char* argv[]) {
    ifstream input;
    input.open(argv[1], ios::in);
    if(!input) {
        cout<<"There's no input file\n";
        return 1;
    }
    int m, n, col, shift;
    string op;
    input>>m>>n;
    if(m <= 0 || n <= 0 || m > 15 || n > 40) {
        cout<<"out of the limit of edge\n";
        return 1;
    }
    game tetris(m, n);
    input>>op;
    while(op != "End") {
        input>>col>>shift;\
        col--;
        block* target;
        switch (op[0])
        {
        case 'T':
            switch (op[1])
            {
            case '1':
                target = &T1;
                break;
            case '2':
                target = &T2;
                break;
            case '3':
                target = &T3;
                break;
            case '4':
                target = &T4;
                break;
            }
            break;
        case 'L':
            switch (op[1])
            {
            case '1':
                target = &L1;
                break;
            case '2':
                target = &L2;
                break;
            case '3':
                target = &L3;
                break;
            case '4':
                target = &L4;
                break;
            }
            break;
        case 'J':
            switch (op[1])
            {
            case '1':
                target = &J1;
                break;
            case '2':
                target = &J2;
                break;
            case '3':
                target = &J3;
                break;
            case '4':
                target = &J4;
                break;
            }
            break;
        case 'S':
            switch (op[1])
            {
            case '1':
                target = &S1;
                break;
            case '2':
                target = &S2;
                break;
            }
            break;
        case 'Z':
            switch (op[1])
            {
            case '1':
                target = &Z1;
                break;
            case '2':
                target = &Z2;
                break;
            }
            break;
        case 'I':
            switch (op[1])
            {
            case '1':
                target = &I1;
                break;
            case '2':
                target = &I2;
                break;
            }
            break;
        case 'O':
            target = &O;
            break;
        default:
            cout<<"Wrong input!!\n";
            return 1;
        }
        if(col + target->b_col_size - 1 >= tetris.col || col < 0) {
            cout<<"col: "<<col<<" Initial col out of edge!!\n";
            return 1;
        }
        int r_firstf = tetris.first_fall(target, col);
        //cout<<"r_firf: "<<r_firstf<<"\n";
        int r_finalf;
        if(!shift) r_finalf = r_firstf;   
        else {
            col += shift;
            if(col + target->b_col_size - 1 >= tetris.col || col < 0) {
                cout<<"Out of side limit!!\n";
                return 1;
            }
            r_finalf = tetris.final_fall(target, r_firstf, col);
        }
        tetris.place(target, r_finalf, col);
        //cout<<"Y\n";
        tetris.del();
        int f = tetris.gameover();
        if(f) {
            cout<<"Out of upper edge!!\n";
            return 1;
        }

        input>>op;
    }
    int final_puz[40][15];
    for(int i = 0; i < tetris.col; ++i) {
        int cnt = 0;
        for(auto r: tetris.puzzle[i]) {
            while(cnt < r) final_puz[i][cnt++] = 0;
            final_puz[i][cnt++] = 1;
        }
        while(cnt < tetris.row) final_puz[i][cnt++] = 0;
    }
    ofstream output;
    output.open("108062229_proj1.final");
    for(int j = tetris.row - 1; j >= 0; --j) {
        for(int i = 0; i < tetris.col; ++i) {
            output<<final_puz[i][j]<<" \n"[i == tetris.col - 1];
        }
    }

    input.close();
    output.close();



    return 0;
}