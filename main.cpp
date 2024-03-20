#include <iostream>
#include <fstream>
#include <set>
#include <nlohmann/json.hpp>
#include <queue>
#include <stack>

std::string path_name = R"(C:\Users\darli\CLionProjects\Discrete_HW2\package.json)";
std::ifstream path(path_name);
nlohmann::json list_of_countries = nlohmann::json::parse(path);

std::vector<std::vector<int>> adjacency_list;
std::vector<std::vector<int>> adjacency_matrix;

const int countries_amount = 49;
const int edges_amount = 93;


int GetCountryNum(int index) {
    return index;
}

std::string GetCountryName(int index) {
    std::string name = nlohmann::to_string(list_of_countries[index]["name"]);
    return name;
}

std::vector<int> GetCountryNeighbours(int index) {
    std::vector<int> neighbours;
    for (int i = 0; i < list_of_countries[index]["numbers"].size(); ++i) {
        std::string str_obj = nlohmann::to_string(list_of_countries[index]["numbers"][i]);
        str_obj = str_obj.substr(1, str_obj.size() - 2);
        int obj = std::stol(str_obj);
        neighbours.push_back(obj);
    }
    return neighbours;
}

void AddToAdjacencyList(const std::vector<int>& list_of_one_country) {
    adjacency_list.push_back(list_of_one_country);
}

void BuildAdjacencyList() {
    for (int i = 0; i <= countries_amount; ++i) {
        std::vector<int> obj = GetCountryNeighbours(i);
        AddToAdjacencyList(obj);
    }
}

void PrintAdjacencyList() {
    for (int i = 1; i <= countries_amount; ++i) {
        std::cout << i << " : ";
        for (int j = 0; j < adjacency_list[i].size(); ++j) {
            std::cout << adjacency_list[i][j] << ", ";
        }
        std::cout << '\n';
    }
}

void BuildAdjacencyMatrix() {
    adjacency_matrix.assign(50, std::vector<int>(50, 0));
    for (int i = 0; i <= countries_amount; ++i) {
        std::vector<int> obj = GetCountryNeighbours(i);
        for (int j : obj) {
            adjacency_matrix[i][j] = 1;
            adjacency_matrix[j][i] = 1;
        }
    }
}

void PrintAdjacencyMatrix() {
    std::cout << "    ";
    for (int i = 1; i <= countries_amount; ++i) {
        i < 10 ? std::cout << i << ' ' : std::cout << i % 10 << ' ';
    }
    std::cout << '\n';
    for (int i = 1; i <= countries_amount; ++i) {
        i < 10 ? std::cout << i << " : " : std::cout << i << ": ";
        for (int j = 1; j <= countries_amount; ++j) {
            std::cout << adjacency_matrix[i][j] << " ";
        }
        std::cout << '\n';
    }
}

//---------------------------Extremity---------Пункт 2------------------
int CountMinDegree() {
    std::priority_queue<int, std::vector<int>, std::greater<>> q;
    for (int i = 1; i <= countries_amount; ++i) {
        if (!adjacency_list[i].empty()) {
            q.push(adjacency_list[i].size());
        }
    }
    return q.top();
}

int CountMaxDegree() {
    std::priority_queue<int> q;
    for (int i = 1; i <= countries_amount; ++i) {
        if (!adjacency_list[i].empty()) {
            q.push(adjacency_list[i].size());
        }
    }
    return q.top();
}


//Используется алгоритм Флойда-Уоршелла
const int INF = 1000000000;

std::vector<std::vector<int>> FloydWarshall() {
    std::vector<std::vector<int>> graph = adjacency_matrix;
    for (int i = 1; i <= countries_amount; ++i) {
        for (int j = 1; j <= countries_amount; ++j) {
            if (graph[i][j] == 0 && i != j) {
                graph[i][j] = INF;
            }
        }
    }
    for (int c = 1; c <= countries_amount; ++c) {
        for (int i = 1; i <= countries_amount; ++i) {
            for (int j = 1; j <= countries_amount; ++j) {
                if (i != j) {
                    graph[i][j] = std::min(graph[i][j], graph[i][c] + graph[c][j]);
                }
            }
        }
    }
    return graph;
}

std::vector<std::vector<int>> CountExtrimity(std::vector<std::vector<int>> graph) {
    for (int i = 1; i <= countries_amount; ++i) {
        int max = 0;
        for (int j = 1; j <= countries_amount; ++j) {
            if (graph[i][j] < 100000) {
                max = std::max(max, graph[i][j]);
            }
        }
        graph[i][0] = max;
    }
    return graph;
}

int CountRadius(const std::vector<std::vector<int>>& graph) {
    int radius = graph[1][0];
    for (int i = 1; i <= countries_amount; ++i) {
        if (graph[i][0] > 1) {
            radius = std::min(radius, graph[i][0]);
        }
    }
    return radius;
}

int CountDiameter(const std::vector<std::vector<int>>& graph) {
    int diameter = graph[1][0];
    for (int i = 1; i <= countries_amount; ++i) {
        diameter = std::max(diameter, graph[i][0]);
    }
    return diameter;
}

std::vector<int> FindCenter(const std::vector<std::vector<int>>& graph) {
    int radius = CountRadius(graph);
    std::vector<int> center;
    for (int i = 1; i <= countries_amount; ++i) {
        if (graph[i][0] == radius) {
            center.push_back(i);
        }
    }
    return center;
}

void PrintExtrimityTable() {
    std::vector<std::vector<int>> table = CountExtrimity(FloydWarshall());
    for (int i = 1; i <= countries_amount; ++i) {
        std::cout << i << " : ";
        for (int j = 0; j <= countries_amount; ++j) {
            if (table[i][j] < 1000000) {
                std::cout << table[i][j] << ' ';
            } else {
                std::cout << "I" << ' ';
            }
        }
        std::cout << '\n';
    }
}

//---------------------------Chromatic---------Пункт 3------------------
//Используется алгоритм DSatur

struct NodeInfo {
    int saturation;
    int degree;
    int vertex_num;
};

struct MaxSaturation {
    bool operator()(const NodeInfo& lhs, const NodeInfo& rhs) const {
        return std::tie(lhs.saturation, lhs.degree, lhs.vertex_num) > std::tie(rhs.saturation, rhs.degree, rhs.vertex_num);
    }
};

int CountChromaticNum() {
    std::vector<int> colors(countries_amount + 1, -1);
    std::vector<int> d(countries_amount + 1);
    std::vector<std::set<int>> adj_colors(countries_amount + 1, std::set<int>());
    std::vector<bool> visited(countries_amount + 1, false);
    std::set<NodeInfo, MaxSaturation> Q;
    std::set<NodeInfo, MaxSaturation>::iterator max_ptr;

    int u = 0, i = 0;

    for (u = 1; u <= countries_amount; ++u) {
        d[u] = adjacency_list[u].size();
        Q.emplace(NodeInfo{0, d[u], u});
    }
    while (!Q.empty()) {
        max_ptr = Q.begin();
        u = (*max_ptr).vertex_num;
        Q.erase(max_ptr);

        for (auto v : adjacency_list[u]) {
            if (colors[v] != -1) {
                visited[colors[v]] = true;
            }
        }

        for (i = 1; i <= visited.size(); ++i) {
            if (!visited[i]) {
                break;
            }
        }

        for (auto v : adjacency_list[u]) {
            if (colors[v] != -1) {
                visited[colors[v]] = false;
            }
        }

        colors[u] = i;

        for (auto v : adjacency_list[u]) {
            if (colors[v] == -1) {
                Q.erase({static_cast<int>(adj_colors[v].size()), d[v], v});
                adj_colors[v].insert(i);
                --d[v];
                Q.emplace(NodeInfo {static_cast<int>(adj_colors[v].size()), d[v], v});
            }
        }
    }
    std::set<int> uniq_colors;
    for (int j = 1; j <= countries_amount; ++j) {
        uniq_colors.insert(colors[j]);
    }
    return uniq_colors.size();
}

//---------------------------Max CLique---------Пункт 4------------------
//Используется алгоритм Брона-Кербоша
std::set<std::set<int>> max_cliques;

void BronKerbosch(std::set<int> R, std::set<int> P, std::set<int> X) {
    if (P.empty() && X.empty()) {
        max_cliques.insert(R);
        return;
    }

    std::set<int> P_copy = P;
    for (int vertex : P_copy) {
        std::set<int> newR = R;
        newR.insert(vertex);

        std::set<int> newP;
        for (int v : adjacency_list[vertex]) {
            if (P.find(v) != P.end()) {
                newP.insert(v);
            }
        }

        std::set<int> newX;
        for (int v : adjacency_list[vertex]) {
            if (X.find(v) != X.end()) {
                newX.insert(v);
            }
        }

        BronKerbosch(newR, newP, newX);
        P.erase(vertex);
        X.insert(vertex);
    }
}

//---------------------------Maкс простой цикл---------Пункт 5----------------
int max_len = 0;

void PrintSet(const std::set<int>& s) {
    for (auto obj: s) {
        std::cout << obj << ' ';
    }
    std::cout << '\n';
}

void dfs(std::vector<std::vector<int>>& graph, int v, int parent, std::vector<bool>& visited, std::vector<int>& path, std::set<std::set<int>>& cycles) {
    /*if (cycles.size() > 1000) {
        return;
    }*///Типа отменяющее условие, но проще тупое ожидание
    visited[v] = true;
    path.push_back(v);
    for (int u : graph[v]) {
        if (!visited[u]) {
            dfs(graph, u, v, visited, path, cycles);
        } else if (u != parent && std::find(path.begin(), path.end(), u) != path.end()) {
            std::set<int> cycle;
            auto it = std::find(path.begin(), path.end(), u);
            for (; it != path.end(); ++it) {
                cycle.insert(*it);
            }
            if (cycle.size() > max_len) {
                max_len = cycle.size();
                PrintSet(cycle);
            }
        }
    }
    visited[v] = false;
    path.pop_back();
}

std::set<std::set<int>> FindSimpleCycles(std::vector<std::vector<int>>& graph) {
    std::set<std::set<int>> cycles;
    std::vector<bool> visited(countries_amount + 1, false);
    std::vector<int> path;

    for (int i = 1; i <= countries_amount; ++i) {
        if (cycles.size() < 1000) {
            if (!visited[i]) {
                dfs(graph, i, -1, visited, path, cycles);
            }
        }
    }

    return cycles;
}

//---------------------------Вершинная двусвязность---------Пункт 7------------------
std::vector<int> used, enter, ret, colors, paint;
std::map<std::pair<int, int>, std::vector<int>> number_of_edges;
int time_, max_color;

std::pair<int, int> GetEdge(int a, int b) {
    if (a > b) {
        std::swap(a, b);
    }
    return std::make_pair(a, b);
}

void SetColor(int v, int to, int color) {
    std::vector<int> numbers = number_of_edges[GetEdge(v, to)];
    for (int i = 0; i < numbers.size(); ++i) {
        colors[numbers[i]] = color;
    }
}

void dfs1(int v, int p = -1) {
    used[v] = 1;
    enter[v] = ret[v] = time_++;
    int c = 0;
    for (int i = 0; i < adjacency_list[v].size(); ++i) {
        int to = adjacency_list[v][i];
        if (to == p) {
            continue;
        }
        if (used[to]) {
            ret[v] = std::min(ret[v], enter[to]);
        } else {
            dfs1(to, v);
            c++;
            ret[v] = std::min(ret[v], ret[to]);
        }
    }
}

void paint1(int v, int color, int p) {
    paint[v] = 1;
    for (int i = 0; i < adjacency_list[v].size(); ++i) {
        int to = adjacency_list[v][i];
        if (!paint[to]) {
            if (ret[to] >= enter[v]) {
                int newColor = ++max_color;
                SetColor(v, to, newColor);
                paint1(to, newColor, v);
            } else {
                SetColor(v, to, color);
                paint1(to, color, v);
            }
        } else if (enter[to] < enter[v]) {
            SetColor(v, to, color);
        }
    }
}

void FindVComps() {
    time_ = 1;
    for (int i = 1; i <= countries_amount; ++i) {
        if (!used[i]) {
            dfs1(i);
        }
    }
    max_color = 0;
    for (int i = 1; i <= countries_amount; ++i) {
        if (!paint[i]) {
            paint1(i, max_color, -1);
        }
    }
}

//---------------------------Реберная двусвязность---------Пункт 8------------------
int Time, max_color_;
std::vector<int> used1, enter1, ret1, colors1, mult;
std::set<int> bridges;
std::map<std::pair<int, int>, int> edge_num;

std::pair<int, int> get_edge(int a, int b) {
    if(a > b) {
        std::swap(a, b);
    }
    return std::make_pair(a, b);
}

void dfs2(int v, int p = -1) {
    used1[v] = 1;
    enter1[v] = ret1[v] = Time++;
    for (int i = 0; i < adjacency_list[v].size(); ++i) {
        int to = adjacency_list[v][i];
        if (to == p) {
            continue;
        }
        if (used1[to]) {
            ret1[v] = std::min(ret1[v], enter1[to]);
        } else {
            dfs2(to, v);
            ret1[v] = std::min(ret1[v], ret1[to]);
            if (ret1[to] > enter1[v] && !mult[edge_num[get_edge(v, to)]]) {
                bridges.insert(edge_num[get_edge(v, to)]);
            }

        }
    }
}

void paint2(int v, int color) {
    colors1[v] = color;
    for (int i = 0; i < adjacency_list[v].size(); ++i) {
        int to = adjacency_list[v][i];
        if (colors1[to] == 0) {
            if (bridges.find(edge_num[get_edge(v, to)]) != bridges.end()) {
                max_color_++;
                paint2(to, max_color_);
            } else {
                paint2(to, color);
            }
        }
    }
}

void FindRComps() {
    Time = 1;
    for (int i = 1; i <= countries_amount; ++i) {
        colors1[i] = 0;
        if (!used1[i]) {
            dfs2(i);
        }
    }

    max_color_ = 0;
    for (int i = 1; i <= countries_amount; ++i) {
        if (colors1[i] == 0) {
            max_color_++;
            paint2(i, max_color_);
        }
    }
}

//---------------------------Веса и остовное дерево---------Пункт 9------------------

std::string w_path_name = R"(C:\Users\darli\CLionProjects\Discrete_HW2\weights.json)";
std::ifstream w_path(w_path_name);
nlohmann::json weight_list = nlohmann::json::parse(w_path);

struct Edge {
    int a, b;
    float weight;
    bool operator<(const Edge& other) {
        return weight < other.weight;
    }
    Edge(int a_, int b_, float w) : a(a_), b(b_), weight(w) {};
};


std::vector<Edge> edges;
std::vector<std::vector<float>> weight_matrix;

int GetFirst(int index) {
    std::string str_obj = nlohmann::to_string(weight_list[index]["f"]);
    //str_obj = str_obj.substr(1, str_obj.size() - 2);
    int obj = std::stol(str_obj);
    return obj;
}

int GetSecond(int index) {
    std::string str_obj = nlohmann::to_string(weight_list[index]["s"]);
    //str_obj = str_obj.substr(1, str_obj.size() - 2);
    int obj = std::stol(str_obj);
    return obj;
}

float GetWeight(int index) {
    std::string str_obj = nlohmann::to_string(weight_list[index]["w"]);
    //str_obj = str_obj.substr(1, str_obj.size() - 2);
    float obj = std::stof(str_obj);
    return obj;
}

void BuildEdges() {
    for (int i = 0; i < edges_amount - 1; ++i) {
        int from = GetFirst(i);
        int to = GetSecond(i);
        float weight = GetWeight(i);
        Edge first = Edge(from, to, weight);
        Edge second = Edge(to, from, weight);
        edges.push_back(first);
        edges.push_back(second);
    }
}

void BuildWeightMatrix() {
    weight_matrix.assign(50, std::vector<float>(50, 0));
    for (int i = 0; i < edges_amount - 1; ++i) {
        int from = GetFirst(i);
        int to = GetSecond(i);
        float weight = GetWeight(i);
        weight_matrix[from][to] = weight;
        weight_matrix[to][from] = weight;
    }
}

void PrintWeihtMatrix() {
    std::cout << "    ";
    for (int i = 1; i <= countries_amount; ++i) {
        i < 10 ? std::cout << i << ' ' : std::cout << i % 10 << ' ';
    }
    std::cout << '\n';
    for (int i = 1; i <= countries_amount; ++i) {
        i < 10 ? std::cout << i << " : " : std::cout << i << ": ";
        for (int j = 1; j <= countries_amount; ++j) {
            std::cout << weight_matrix[i][j] << " ";
        }
        std::cout << '\n';
    }
}

//Алгоритм Крускала
std::vector<int> parents(countries_amount + 1, 0);
std::vector<int> ranks(countries_amount + 1, 0);

void InitDSU() {
    for (int i = 1; i <= countries_amount; ++i) {
        parents[i] = i;
        ranks[i] = 1;
    }
}

int GetRoot(int v) {
    if (parents[v] == v) {
        return v;
    } else {
        return parents[v] = GetRoot(parents[v]);
    }
}

bool Merge(int a, int b) {
    a = GetRoot(a);
    b = GetRoot(b);
    if (a == b) {
        return false;
    } else {
        if (ranks[a] < ranks[b]) {
            std::swap(a, b);
        }
        parents[b] = a;
        ranks[a]++;
    }
    return true;
}

float mst_weigt = 0;

std::set<std::pair<int, int>> FindMst() {
    std::set<std::pair<int, int>> need_edges;
    std::sort(edges.begin(), edges.end());
    InitDSU();


    for (auto e: edges) {
        if (Merge(e.a, e.b)) {
            mst_weigt += e.weight;
            need_edges.insert(std::make_pair(e.a, e.b));
        }
    }

    return need_edges;
}

//---------------------------Кодирования---------Пункт 10------------------
//Код Прюфера
std::vector<int> PruferCode(std::set<std::pair<int, int>>& mst_edges) {
    std::map<int, std::vector<int>> adjacency_mst_list;
    for (const auto edge : mst_edges) {
        adjacency_mst_list[edge.first].push_back(edge.second);
        adjacency_mst_list[edge.second].push_back(edge.first);
    }

    std::map<int, int> vertex_degrees;
    for (const auto i : adjacency_mst_list) {
        vertex_degrees[i.first] = i.second.size();
    }

    std::vector<int> leaves;
    for (auto i: vertex_degrees) {
        if (i.second == 1) {
            leaves.push_back(i.first);
        }
    }

    std::sort(leaves.begin(), leaves.end());

    std::vector<int> prufer_code;

    while (adjacency_mst_list.size() > 2) {
        int leaf = leaves.front();
        leaves.erase(leaves.begin());

        int nei = adjacency_mst_list[leaf][0];
        prufer_code.push_back(nei);

        --vertex_degrees[nei];

        adjacency_mst_list[nei].erase(remove(adjacency_mst_list[nei].begin(), adjacency_mst_list[nei].end(), leaf), adjacency_mst_list[nei].end());

        if (vertex_degrees[nei] == 1) {
            leaves.push_back(nei);
            std::sort(leaves.begin(), leaves.end());
        }
        adjacency_mst_list.erase(leaf);
        vertex_degrees.erase(leaf);

    }

    return prufer_code;
}

//Бинарное кодирование
std::vector<int> generateBinaryCode() {
    BuildAdjacencyList(); // Построение списка смежности

    std::vector<int> binaryCode; // Результирующий бинарный код
    std::set<std::pair<int, int>> mst_edges = FindMst(); // Нахождение минимального остовного дерева
    std::vector<int> prufer_code = PruferCode(mst_edges); // Генерация кода Прюфера

    // Преобразование кода Прюфера в бинарный код
    for (int i = 0; i < prufer_code.size(); ++i) {
        int degree = adjacency_list[prufer_code[i]].size() - 1;
        for (int j = 0; j < degree; ++j) {
            binaryCode.push_back(1);
        }
        binaryCode.push_back(0);
    }

    return binaryCode;
}

int main() {

    return 0;
}
