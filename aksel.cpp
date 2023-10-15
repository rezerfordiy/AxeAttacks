
#include <bits/stdc++.h>

using namespace std;

int n, k;
vector <vector <double>> graph(n, vector<double>(n, 0));// graph s distnance
vector <vector <double>> pheromoni(n, vector<double>(n, 0.5));// graph s feromoni
vector <bool> visited;

template<typename T>
class ant
{
private:



public:
    const vector<vector<double>>* graph;



};


int main()
{
    ifstream in("input.txt");
    srand(time(NULL));
    in >> n >> k;
    graph.resize(n);
    pheromoni.resize(n);
    visited.resize(n);

    for (int i = 0; i < n; i++)
    {
        graph[i].resize(n);
        pheromoni[i].resize(n);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            graph[i][j] = -1;
        }
    }
    for (int i = 0; i < k; i++)
    {
        int from, to, val;
        in >> from >> to >> val;
        graph[from][to] = val;
        graph[to][from] = val;
        pheromoni[to][from] = 0.5;
        pheromoni[from][to] = 0.5;
    }

    for (int v = 0; v < 10; v++)
    {
        for (int t = 0; t < 10; t++)
        {
            queue <int> q;
            q.push(0);
            vector <int> way;
            for (int i = 0; i < n; i++)
            {
                visited[i] = 0;
            }
            while (!q.empty())
            {
                int et = q.front();
                way.push_back(et);
                q.pop();
                visited[et] = true;
                double sumovwill = 0;
                vector <pair<int, double>> wills;
                int counter = 0;
                for (int i = 0; i < n; i++)
                {
                    if (graph[et][i] == -1 || visited[i])
                        continue;
                    double x = pow((100.0 / graph[et][i]), 3) * pheromoni[et][i];
                    counter > 0 ? wills.push_back(make_pair(i, x + wills[counter - 1].second)) : wills.push_back(make_pair(i, x));
                    counter++;
                    sumovwill += x;

                }
                if (wills.size() == 0)
                {
                    break;
                }
                for (int i = 0; i < wills.size(); i++)
                {
                    wills[i].second /= sumovwill;
                }
                double X = ((double)rand() / (double)RAND_MAX);
                if (X < wills[0].second)
                {
                    if (!visited[wills[0].first])
                        q.push(wills[0].first);
                }
                else
                {
                    int l = 0;
                    int r = wills.size() - 1;
                    while (l < r - 1)
                    {
                        int mid = (l + r) / 2;
                        if (wills[mid].second >= X)
                        {
                            r = mid;
                        }
                        else
                        {
                            l = mid;
                        }
                    }
                    if (!visited[wills[r].first])
                        q.push(wills[r].first);
                }



            }

            double distance = 0;
            for (int i = 0; i < n - 1; i++)
            {
                distance += graph[way[i]][way[i + 1]];
            }

            for (int i = 0; i < n - 1; i++)
            {
                pheromoni[way[i]][way[i + 1]] += 10.0 / distance;
            }




            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    cout << setw(10) << pheromoni[i][j] << ' ';
                }
                cout << endl;
            }
            cout << endl;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                pheromoni[i][j] *= 0.8;
            }
        }
        cout << "???????????????????????????" << endl;
    }

}
