// vim: ts=4 sw=4 et
#include<iostream>
#include<cstring>
#include<deque>

using namespace std;
int _map[300][300];
int match[300];
int visit[300];
int queue[300], *qf, *qb;
int n;
deque<int> p[300];


void label_one_side(int x, int y, int bi){
	for(int i=bi+1; i<p[x].size(); ++i){
		int z = p[x][i];
		if(visit[z]==1){
			p[z] = p[y];
/*			cout << "before\n";
            for(int k=0; k<p[z].size(); k++)
				cout << p[z][k] << ' ';
			cout << endl;
            cout << "after\n";*/
			p[z].insert(p[z].end(), p[x].rbegin(), p[x].rend()-i);
/*			for(int k=0; k<p[z].size(); k++)
				cout << p[z][k] << ' ';
			cout << endl;*/
			visit[z] = 0;
			*qb++ = z;
		}
	}
}

bool BFS(int r){
	for(int i=1; i<=n ;i++)
		p[i].clear();
	p[r].push_back(r);

	memset(visit, -1, sizeof(visit)+1);
	visit[r] = 0;

	//queue[0] = r;
	qf = qb = queue;
	*qb++ = r;
//	cout << "--- r --- = " << r << endl;
	while(qf < qb)
		for(int x=*qf++, y=1; y<=n; ++y){
//            cout << "--- X --- = " << x << endl;
			if(_map[x][y]&&match[y]!=y){
				if(visit[y] == -1){
                    if(match[y] == -1){
//                        cout << "case 1\n";
                        for(int i=0; i+1<p[x].size(); i+=2){
				    		match[p[x][i]] = p[x][i+1];
				    		match[p[x][i+1]] = p[x][i];
				    	}
					    match[x] = y, match[y] = x;
					    return true;
                    }
				
    				else{
	    				int z = match[y];
		    			
//                        cout << "case 2\n";
			    		p[z] = p[x];
				    	p[z].push_back(y);
					    p[z].push_back(z);
                        
 /*                       for(int k=0; k<p[z].size(); k++)
                            cout << p[z][k] << ' ';
                        cout << '*' << endl;
*/
    					visit[y] = 1, visit[z] = 0;
	    				*qb++ = z;
                   }
				}

    			else
	    			if(visit[y]==0){
		    			//even to even
//                        cout << "case 3\n";
				    	int bi = 0;
					
    					while(bi<p[x].size()&&
	    					  bi<p[y].size()&&
		    				  p[x][bi]==p[y][bi])	bi++;
			    		bi--;
				    	label_one_side(x, y, bi);
					    label_one_side(y, x, bi);
    				}
    			    else
				        ;
			
		}
	}
    return false;
}

int Match(){
	int c = 0;
	memset(match, -1, sizeof(match)+1);
	for(int i=1; i<=n; i++){
		if(match[i]==-1)
			if(BFS(i))
				c++;
			else
				match[i] = i;
	}
	return c;
}
int main(){
	int x, y;
	cin >> n;
	for(int i=0; i<=n; i++)
		for(int j=0; j<=n; j++)
		    _map[i][j] = 0;
	while(cin>>x>>y){
		if(cin.eof())
			break;
		_map[x][y] = _map[y][x] = 1;
	}
	
	cout << Match()*2 << endl;
    for(int i=1; i<=n; i++)
        if(i<match[i])
            cout << i << ' ' << match[i] << endl;
	return 0;
}
