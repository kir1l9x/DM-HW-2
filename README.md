Данная работа является домашним заданием по дискретной математике. Я использовал различные алгоритмы для работы с графами для ее выполнения.

# Инструкция по проверке/выполнению

Для проверки задания достаточно сбилдить проект на устройстве, затем вставить код для каждого пункта в функцию 'int main()'. Результат будет предоставлен в консоли. Если возникают какие-либо несоответствия или возникают другие вопросы, обращайтесь к @killmefasterdear. Мои выводы записаны в отдельный PDF файл в этом же репозитории.

## Пункт 2
```c++
int main() {
    BuildAdjacencyMatrix();
    BuildAdjacencyList();
    int min_degree = CountMinDegree();
    int max_degree = CountMaxDegree();
    std::cout << "Min Degree : " << min_degree << '\n';
    std::cout << "Max Degree : " << max_degree << '\n' << '\n';
    PrintExtrimityTable();
    std::vector<std::vector<int>> table = CountExtrimity(FloydWarshall());
    int radius = CountRadius(table);
    std::cout << "Radius : " << radius << '\n';
    int diameter = CountDiameter(table);
    std::cout << "Diameter : " << diameter << '\n';
    std::vector<int> center = FindCenter(table);
    std::cout << "Center : ";
    for (int i = 0; i < center.size(); ++i) {
        std::cout << center[i] << ' ';
    }
    return 0;
}
```

## пункт 3
```c++
int main() {
    BuildAdjacencyList();
    int chromatic_num = CountChromaticNum();
    std::cout << chromatic_num;
    return 0;
}
```

## пункт 4
```c++
int main() {
    BuildAdjacencyMatrix();
    BuildAdjacencyList();
    std::set<int> R, P, X;
    for (int i = 1; i <= countries_amount; ++i) {
        P.insert(i);
    }
    BronKerbosch(R, P, X);
    size_t max_size = 0;
    for (auto b : max_cliques) {
        max_size = std::max(max_size, b.size());
    }
    for (auto b : max_cliques) {
        if (b.size() == max_size) {
            for (auto a : b) {
                std::cout << a << ' ';
            }
            std::cout << '\n';
        }
    }
    return 0;
}
```
## пункт 5
```c++
int main() {
    BuildAdjacencyList();
    std::set<std::set<int>> cycle = FindSimpleCycles(adjacency_list);//в функцию можно добавить добавление циклов в множество и получить их множество
    return 0;
}
```

## пункт 7
```c++
int main() {
    BuildAdjacencyList();
    used.resize(countries_amount + 1);
    paint.resize(countries_amount + 1);
    enter.resize(countries_amount + 1);
    ret.resize(countries_amount + 1);
    colors.resize(edges_amount + 1);
    for (int i = 1; i <= countries_amount; ++i) {
        for (int j = 0; j < adjacency_list[i].size(); ++j) {
            int neighbor = adjacency_list[i][j];
            number_of_edges[GetEdge(i, neighbor)].push_back(i);
        }
    }

    FindVComps();

    std::cout << max_color << '\n';
    for (const auto& entry : number_of_edges) {
        const std::pair<int, int>& edge = entry.first;
        const std::vector<int>& vertices = entry.second;
        int edge_color = colors[edge.first];
        for (int vertex : vertices) {
            std::cout << edge.first << "->" << edge.second << ' ' << vertex << " : " << edge_color << '\n';
        }
    }
    return 0;
}
```

## пункт 8
```c++
int main() {
    BuildAdjacencyList();
    used1.resize(countries_amount + 1);
    enter1.resize(countries_amount + 1);
    ret1.resize(countries_amount + 1);
    colors1.resize(countries_amount + 1);
    mult.resize(edges_amount + 1);

    int edge_number = 1;
    for (int i = 1; i <= countries_amount; ++i) {
        for (int j = 0; j < adjacency_list[i].size(); ++j) {
            int neighbor = adjacency_list[i][j];
            std::pair<int, int> edge = get_edge(i, neighbor);
            if (edge_num.find(edge) == edge_num.end()) {
                edge_num[edge] = edge_number++;
            }
        }
    }
    FindRComps();
    std::cout << max_color_ << '\n';
    for (int i = 1; i <= countries_amount; ++i) {
        std::cout << i << " : " << colors1[i] << '\n';
    }

    return 0;
}
```
## пункт 9
```c++
int main() {
    BuildEdges();
    std::set<std::pair<int, int>> mst = FindMst();
    std::cout << "Amount : " << mst.size() << '\n';
    for (auto pair: mst) {
        std::cout << pair.first << ' ' << pair.second << '\n';
    }
    std::cout << "Weight : " << mst_weigt;
    return 0;
}
```

## пункт 10
1) код Прюфера
```c++
int main() {
    BuildEdges();
    BuildAdjacencyList();
    std::set<std::pair<int, int>> mst = FindMst();
    std::vector<int> prufer_code = PruferCode(mst);
    for (auto a: prufer_code) {
        std::cout << a << ' ';
    }
    return 0;
}
```
2) бинарный код 
```c++
int main() {
    BuildEdges();
    std::vector<int> binaryCode = generateBinaryCode();
    std::cout << "Binary Code: ";
    for (int code : binaryCode) {
        std::cout << code;
    }
    std::cout << std::endl;

    return 0;
}

```

сам по себе код максимально не ООП и не красив, но прост для проверки)
