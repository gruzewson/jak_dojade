#include <iostream>
#include "FifoQueue.h"
//#include "Vector.h"
#include "City.h"
#include "String.h"
using namespace std;

String findNameLeft(char** map, int h, int w, int width)
{
    String name = "";
    int tempW = w;

    if (tempW > 0)
    {
        if (map[h][tempW - 1] != '.' && map[h][tempW - 1] != '#' && map[h][tempW - 1] != '*')
        {
            tempW--;
            while (tempW > 0 && map[h][tempW - 1] != '.' && map[h][tempW - 1] != '#' && map[h][tempW - 1] != '*')
            {
                tempW--;
            }
            while (tempW < width)
            {
                if (map[h][tempW] != '.' && map[h][tempW] != '#' && map[h][tempW] != '*')
                {
                    name += map[h][tempW];
                }
                else
                {
                    return name;
                }
                tempW++;
            }
        }
    }
    return name;
}

String findNameRight(char** map, int h, int w, int width)
{
    String name = "";
    int tempW = w;

    if (tempW < width)
    {
        if (map[h][tempW] != '.' && map[h][tempW] != '#' && map[h][tempW] != '*')
        {
            name += map[h][tempW];
            tempW++;
            while (tempW < width && map[h][tempW] != '.' && map[h][tempW] != '#' && map[h][tempW] != '*')
            {
                name += map[h][tempW];
                tempW++;
            }
        }
    }
    return name;
}

String findName(Vector<City>& cities, char** map, int h, int w, int height, int width)
{
    String name = "";

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (h + i >= 0 && h + i <= height && w + j >= 0 && w + j <= width)
            {
                name = findNameLeft(map, h + i, w + j, width);
                for (int k = 0; k < cities.size(); k++)
                {
                    if (name == cities[k].name)
                    {
                        name = "";
                        break;
                    }
                }
                if (name != "")
                    return name;
                else
                {
                    name = findNameRight(map, h + i, w + j, width);
                    for (int k = 0; k < cities.size(); k++)
                    {
                        if (name == cities[k].name)
                        {
                            name = "";
                            break;
                        }
                    }

                    if (name != "")
                        return name;
                    else
                        continue;
                }
            }
        }
    }
    return name;
}

void findNeighbours(bool**& visited, Vector<City>& cities, FifoQueue& queue, City& city, char** map, int x, int y, int height, int width)
{
    int dx[] = { -1, 0, 1, 0 };
    int dy[] = { 0, 1, 0, -1 };
    for (int i = 0; i < 4; i++)
    {
        int xx = x + dx[i];
        int yy = y + dy[i];
        if (xx >= 0 && xx < height && yy >= 0 && yy < width)
        {
            if (visited[xx][yy] == false)
            {
                visited[xx][yy] = true;
                if (map[xx][yy] == '*')
                {
                    for (int k = 0; k < cities.size(); k++)
                    {
                        if (cities[k].x == xx && cities[k].y == yy)
                        {
                            city.neighbours.add({ &cities[k], queue.first()->distance + 1 });
                        }
                    }
                }
                else if (map[xx][yy] == '#')
                {
                    queue.pushback(xx, yy, queue.first()->distance + 1);
                }
                else
                    continue;
            }
        }
    }
}

void dijkstra(Vector<City>& cities, City* start, City* end, bool road)
{
    int startDist = 0;
    Vector<bool> visited;
    Vector<int> distances;
    Vector<int> previous;

    for (int i = 0; i < cities.size(); i++)
    {
        visited.add(false);
        distances.add(INT_MAX);
        previous.add(-1);
    }

    distances[start->index] = startDist;
    City* currCity = start;  

    while (currCity != end)
    {
        int minDist = INT_MAX;
        int minIndex = -1;

        for (int i = 0; i < cities.size(); i++)
        {
            if (!visited[i] && distances[i] < minDist)
            {
                minDist = distances[i];
                minIndex = i;
            }
        }

        if (minIndex == -1)  // if there is no unvisited city
        {
            break;
        }

        currCity = &cities[minIndex];  // current city -> city with shortest path
        visited[minIndex] = true;

        for (int i = 0; i < currCity->neighbours.size(); i++)
        {
            City* currNeighbour = currCity->neighbours[i].first;
            int distToNeighbour = currCity->neighbours[i].second;

            // if the path is shorter
            if (distances[currCity->index] + distToNeighbour < distances[currNeighbour->index])
            {
                distances[currNeighbour->index] = distances[currCity->index] + distToNeighbour;
                previous[currNeighbour->index] = currCity->index;
            }
        }
    }

    if (currCity == end)  // if the path is found
    {
        cout << distances[currCity->index] << " ";  // print out path size

        if (road) //print out path
        {  
            Vector<City*> path;
            int index = currCity->index;
            path.add(currCity);

            while (previous[index] != -1)
            {
                path.add(&cities[previous[index]]);
                index = previous[index];
            }

            for (int i = path.size() - 2; i > 0; i--)
            {
                cout << path[i]->name;
                cout << " ";
            }
            cout << endl;
        }
    }
}

void addingCities(char** map, int height, int width, Vector<City>&cities)
{
    char input = '0';
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            input = char(getchar());
            while (input == ' ' || input == '\n')
                input = char(getchar());
            map[i][j] = input;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map[i][j] == '*')
            {
                String name = findName(cities, map, i, j, height, width);
                cities.add(City(name, i, j, cities.size()));
            }
        }
    }
}

void addingNeighbours(char** map, int width, int height, Vector<City>&cities)
{
    bool** visited = new bool* [height];
    for (int a = 0; a < height; a++)
    {
        visited[a] = new bool[width];
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            visited[i][j] = false;
        }
    }

    FifoQueue queue;
    int cityIndex = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map[i][j] == '*')
            {
                for (int k = 0; k < cities.size(); k++)
                {
                    if (cities[k].x == i && cities[k].y == j)
                    {
                        cityIndex = k;
                    }
                }
                visited[i][j] = true;
                queue.pushback(i, j, 0);
                findNeighbours(visited, cities, queue, cities[cityIndex], map, i, j, height, width);
                do
                {
                    findNeighbours(visited, cities, queue, cities[cityIndex], map, queue.firstX(), queue.firstY(), height, width);
                    queue.popback();
                } while (queue.isEmpty() == false);

                for (int a = 0; a < height; a++)
                {
                    for (int b = 0; b < width; b++)
                    {
                        visited[a][b] = false;
                    }
                }
            }
        }
    }

    for (int a = 0; a < height; a++)
    {
        delete[] visited[a];
    }
    delete[] visited;
}

void handlingFlights(Vector<City>&cities)
{
    int howManyFlights;
    char sign = '0';
    String temp;
    String name1;
    String name2;
    cin >> howManyFlights;
    while (howManyFlights--)
    {
        temp = "";
        name1 = "";
        name2 = "";

        for (int j = 0; j < 3; j++)
        {
            sign = char(getchar());
            while (sign == ' ' || sign == '\n')
            {
                sign = char(getchar());
            }
            while (sign != ' ' && sign != '\n')
            {
                temp += sign;
                sign = char(getchar());
            }
            if (j == 0)
            {
                name1 = temp;
                temp = "";
            }
            else if (j == 1)
            {
                name2 = temp;
                temp = "";
            }
            else if (j == 2)
            {
                for (int k = 0; k < cities.size(); k++)
                {
                    if (cities[k].name == name1)
                    {
                        for (int w = 0; w < cities.size(); w++)
                        {
                            if (cities[w].name == name2)
                            {
                                cities[k].neighbours.add({ &cities[w],temp.toInt(temp) });
                            }
                        }
                    }
                }

            }
        }
    }
}

void handlingCommands(Vector<City>&cities)
{
    char sign = '0';
    int commands;
    String temp;
    String name1;
    String name2;
    cin >> commands;
    while (commands--)
    {
        temp = "";
        name1 = "";
        name2 = "";

        for (int j = 0; j < 3; j++)
        {
            sign = char(getchar());
            while (sign == ' ' || sign == '\n')
            {
                sign = char(getchar());
            }
            while (sign != ' ' && sign != '\n')
            {
                temp += sign;
                sign = char(getchar());
            }
            if (j == 0)
            {
                name1 = temp;
                temp = "";
            }
            else if (j == 1)
            {
                name2 = temp;
                temp = "";
            }
            else if (j == 2)
            {
                for (int k = 0; k < cities.size(); k++)
                {
                    if (cities[k].name == name1)
                    {
                        for (int w = 0; w < cities.size(); w++)
                        {
                            if (cities[w].name == name2)
                            {
                                dijkstra(cities, &cities[k], &cities[w], temp.toInt(temp));
                            }
                        }
                    }
                }

            }
        }
    }
}

int main()
{
    int height, width;
    Vector<City> cities;

    cin >> width >> height;
    char** map = new char* [height];
    for (int a = 0; a < height; a++)
    {
        map[a] = new char[width];
    }

    addingCities(map, height, width, cities);

    addingNeighbours(map, width, height, cities);

    handlingFlights(cities);

    handlingCommands(cities);

    for (int a = 0; a < height; a++)
    {
        delete[] map[a];
    }
    delete[] map;

    return 0;
}