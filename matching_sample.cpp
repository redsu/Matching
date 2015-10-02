#include<iostream>
#include<queue>
#include<string.h>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
int V = 5;   // 圖的點數，編號為0到V-1。
bool adj[300][300];   // adjacency matrix
deque<int> p[300];   // p[x]紀錄了樹根到x點的交錯路徑。
int m[300];          // 紀錄各點所配對的點，值為-1為未匹配點。
int d[300];          // 值為-1未拜訪、0偶點、1奇點。
int q[300], *qf, *qb;    // queue，只放入偶點。
 
// 設定好由樹根至花上各個奇點的交錯路徑，並讓奇點變成偶點。
// 只處理花的其中一邊。
// 邊xy是cross edge。bi是花托的索引值。
void label_one_side(int x, int y, int bi)
{
    for (int i=bi+1; i<p[x].size(); ++i)
    {
        int z = p[x][i];
        if (d[z] == 1)
        {
            // 設定好由樹根至花上奇點的交錯路徑。
            // 會經過cross edge。
            p[z] = p[y];
            p[z].insert(p[z].end(), p[x].rbegin(), p[x].rend()-i);
 
            d[z] = 0;   // 花上的奇點變偶點
            *qb++ = z;  // 將來可以延伸出交錯路徑
        }
    }
}
 
// 給定一個未匹配點r，建立交錯樹。
bool BFS(int r)
{
    for (int i=1; i<=V; ++i) p[i].clear();
	for (int i=1; i<=V; i++) {
//			for (int j=0; j<p[i].size(); j++)
//					cout << p[i][j] << ' ';
//			cout << endl;
	}

    p[r].push_back(r);                  // 交錯樹樹根
 
    memset(d, -1, sizeof(d)+1);
    d[r] = 0;                           // 樹根是偶點
 
    qf = qb = q;
    *qb++ = r;                          // 樹根放入queue
 
    while (qf < qb)
        for (int x=*qf++, y=1; y<=V; ++y)
            if (adj[x][y] && m[y] != y) // 有鄰點，點存在。
                if (d[y] == -1)         // 沒遇過的點
                    if (m[y] == -1)     // 發現擴充路徑
                    {
                        for (int i=0; i+1<p[x].size(); i+=2)
                        {
                            m[p[x][i]] = p[x][i+1];
                            m[p[x][i+1]] = p[x][i];
                        }
                        m[x] = y; m[y] = x;
//						cout << "find" << endl;
                        return true;
                    }
                    else                // 延伸交錯樹
                    {
                        int z = m[y];
 
                        p[z] = p[x];
                        p[z].push_back(y);
                        p[z].push_back(z);
//						for(int l=0;l<p[z].size();l++)
//						cout << p[z][l] << ' ';
//						cout << endl;
 
                        d[y] = 1; d[z] = 0;
                        *qb++ = z;
                    }
                else
                    if (d[y] == 0)      // 形成花
                    {
                        // 從交錯路徑中求得LCA的索引值
                        int bi = 0;
                        while (bi < p[x].size()
                            && bi < p[y].size()
                            && p[x][bi] == p[y][bi]) bi++;
                        bi--;
 
                        // 兩條路徑分開標記
                        // 不必擔心x與y在同一朵花上
                        label_one_side(x, y, bi);
                        label_one_side(y, x, bi);
//						for(int l=0;l<p[r].size();l++)
//						                        cout << p[r][l] << ' ';
//												                        cout << endl;
                    }
                    else                // 只需留一條路徑
                        ;
    return false;
}
 
int match()
{
    memset(m, -1, sizeof(m)+1);
 
    int c = 0;
    for (int i=1; i<=V; ++i)
        if (m[i] == -1)
            if (BFS(i)){
                c++;        // 找到擴充路徑，增加匹配數
//				cout << "c " << c << endl;
			}
            else
                m[i] = i;   // 從圖上刪除此點
    return c;
}
 
int main()
{
    cin >> V;
 
    int x, y;
    while (cin >> x >> y){
	//for(int i=0; i<4; i++){
		if(cin.eof())	break;
		adj[x][y] = adj[y][x] = true;
	}
 
    cout << 2*match() << endl;
    for (int i=1; i<=V; ++i)         // 印出所有的匹配邊
        if (i < m[i])
            cout << i << ' ' << m[i] << endl;
 
    return 0;
}
