#include <bits/stdc++.h>
#define random rand()%4
using namespace std;
int dx[4]={-1,0,1,0},dy[4]={0,-1,0,1},wall[65][65][4];
bool check[65][65],pass[4];
string text_input[65];
vector<pair<int,int> > connect[65][65];
bool in(int a,int b){return 1<=a && a<=64 && 1<=b && b<=64;}
vector<int> create_rand(){
    vector<int> ret;
    memset(pass,false,sizeof(pass));
    while(ret.size() < 4){
        int _push = random;
        if(pass[_push]) continue;
        ret.push_back(_push);
        pass[_push] = true;
    }
    return ret;
}
/*  wall
    status1 : save
    status0 : die
    idx : 0 left - 1 up - 2 right - 3 down
*/
void clear(){
    for(int i=1; i<=64; i++){
        check[i][1] = check[1][i] = check[i][64] = check[64][i] = 1;
        for(int j=1; j<=64; j++) wall[i][j][0] = wall[i][j][1] = wall[i][j][2] = wall[i][j][3] = 1;
    }
}
void create_maze(int y,int x){
    check[y][x]=true;
    vector<int> next = create_rand();
    for(int go : next){
        int next_x = x+dx[go];
        int next_y = y+dy[go];
        if(!in(next_y,next_x)) continue;
        if(check[next_y][next_x]) continue;
        if(go == 0){
            wall[y][x][0] = 0;
            wall[next_y][next_x][2] = 0;
            create_maze(next_y,next_x);
        }
        if(go == 1){
            wall[y][x][1] = 0;
            wall[next_y][next_x][3] = 0;
            create_maze(next_y,next_x);
        }
        if(go == 2){
            wall[y][x][2] = 0;
            wall[next_y][next_x][0] = 0;
            create_maze(next_y,next_x);
        }
        if(go == 3){
            wall[y][x][3] = 0;
            wall[next_y][next_x][1] = 0;
            create_maze(next_y,next_x);
        }
    }
}
void draw(){
    for(int i=64; i>=1; i--){
        for(int j=2; j<=64; j++){
            if(i == 1 || i == 64){
                int k = 62;
                if(i == 1){
                    cout<<"|s|";
                    text_input[i]+="|s|";
                    k-=2;
                    while(k--){
                        cout<<"__";
                        text_input[i]+="__";
                    }
                    text_input[i]+="_|";
                    cout<<"_|";
                    break;
                }
                while(k--){
                    cout<<"__";
                    text_input[i]+="__";
                }
                if(i == 64){
                    cout<<"_";
                    text_input[i]+="_";
                }
                if(i == 1){
                    cout<<"|";
                    text_input[i]+="|";
                }
                break;
            }
            if(wall[i][j][0]){
                cout<<"| ";
                text_input[i]+="| ";
            }
            else if(wall[i][j][0] && wall[i][j][3]){
                cout<<"|_";
                text_input[i]+="|_";
            }
            else if(wall[i][j][3] || wall[i][j][1]){
                cout<<"__";
                text_input[i]+="__";
            }
            else{
                cout<<"  ";
                text_input[i]+="  ";
            }
        }
        cout<<'\n';
    }
}
void solved_maze(){
    
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    srand((unsigned int)time(0));
    clear();
    create_maze(2,2);
    draw();
    string file_name = "",_time = __TIMESTAMP__;
    ofstream fout;
    fout.open("/Users/erolf0123/Desktop/c++/Maze/Maze/Maze_data/"+_time+".out");
    for(int i=64; i>=1; i--) fout<<text_input[i]<<'\n';
    fout.close();
}
