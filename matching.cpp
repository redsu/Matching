#include<iostream>
#include<queue>
#include<string.h>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int n;   // 圖的點數，編號為0到n-1。
bool adj[210][210];   // adjacency matrix
deque<int> p[210];   // p[x]紀錄了樹根到x點的交錯路徑。
int m[210];          // 紀錄各點所配對的點，值為-1為未匹配點。
int d[210];          // 值為-1未拜訪、0偶點、1奇點。
int q[210], *qf, *qb;    // queue，只放入偶點。

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
    for (int i=0; i<n; ++i) p[i].clear();
	for (int i=0; i<n; i++) {
		for (int j=0; j<p[i].size(); j++)
			cout << p[i][j] << ' ';
		cout << endl;
	}
		
    p[r].push_back(r);                  // 交錯樹樹根

    memset(d, -1, sizeof(d));
    d[r] = 0;                           // 樹根是偶點

    qf = qb = q;
    *qb++ = r;                          // 樹根放入queue

    while (qf < qb)
        for (int x=*qf++, y=0; y<n; ++y)
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
                        return true;
                    }
                    else                // 延伸交錯樹
                    {
                        int z = m[y];

                        p[z] = p[x];
                        p[z].push_back(y);
                        p[z].push_back(z);

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
                    }
                    else                // 只需留一條路徑
                        ;
    return false;
}

int match()
{
    memset(m, -1, sizeof(m));

    int c = 0;
    for (int i=0; i<n; ++i)
        if (m[i] == -1)
            if (BFS(i)){

                c++;        // 找到擴充路徑，增加匹配數
            }
            else
                m[i] = i;   // 從圖上刪除此點
    return c;
}

int main(){
	int cnt,c[210],cnt2;
	long long s,a,b,r,s1;
	long long arr[210];
	double ss;
	while(1){
		cin >> n;
		cnt2 = cnt = 0;
		if(cin.eof())	break;
		for(int i=0;i<210;i++)
			for(int j=0;j<210;j++)
				adj[i][j] = 0;
		for(int i=0; i<n; i++){
			cin >> arr[i];

		}

		/*for(int i=0; i<n; i++){
			cout << ':' << arr[i] << ' ' << arr[i] << endl;
		}*/
		for(int i=0; i<n; i++){
			if(arr[i]>1){
				for(int j=n-1;j>=0;j--){
					a = arr[i], b = arr[j];

					for(;a>=1&&b>=1;a%=b,r=a,a=b,b=r);

					if(a==1||b==1){
						s = arr[i]*arr[i]+arr[j]*arr[j];
						ss = (double)s;
						ss = sqrt(ss);
						s1 = (long long)ss;

						if(s1*s1==s||(s1+1)*(s1+1)==s){
							adj[i][j] = adj[j][i] = 1;
						}
					}
				}
			}
		}
		cout << match() << "\n";

	}
	return 0;
}

