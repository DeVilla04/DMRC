// Team name: - Kasauli Tigers

// node_value_new.txt contains the node details like which node is connected with which node and at what distance
// stationcode.txt contains the names of 248 stations
// stationcolorcodes.txt contains the color of line on which the station is situated

#include <iostream>
#include <limits.h>
#include <string>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <time.h>
#include <windows.h>
using namespace std;
const int V = 248;

// this class will be used to store the details of a particular station
// i.e. it's name , index(code), line color(color)
class station_code
{
public:
    string name;
    int code;
    string color;
};

struct node1
{
    vector<float> p;
} P[V];

float graph[V][V];
station_code station[V];
COORD coord;

// all these function to be used in this code: -
void drawbox(int, int, int, int, int);
void secondWindow();
void clrscreen();
void delay(unsigned int ms);
void gotoxy(int x, int y);
int timetaken(float dist);
int money(float dist);
void Path(float dist, int e, int st, int inter);
int minDistance(float dist[], bool visited[]);
void dijkstra(float graph[V][V], int src, int targ);
void take_input();
void logo(int x, int y);
void printing_UI();
string makecapital(string str);

void delay(unsigned int ms)
{
    // this is for the box printing with time delay
    clock_t goal = ms + clock();
    while (goal > clock())
    {
    }
}

void clrscreen()
{
    system("cls");
    drawbox(1, 0, 117, 29, 0);
}

void gotoxy(int x, int y)
{
    // this function for setting the cursor position
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawbox(int x1, int y1, int x2, int y2, int d)
{
    // the coloured box is printed
    gotoxy(x1, y1);
    printf("+");
    delay(d);
    gotoxy(x2, y2);
    printf("+");
    delay(d);
    int i;
    for (i = 1; i < x2 - x1; i++)
    {
        gotoxy(x1 + i, y1);
        printf("-");
        printf("\a");
        delay(d);
        gotoxy(x2 - i, y2);
        printf("-");
        delay(d);
    }
    gotoxy(x1, y2);
    printf("+");
    gotoxy(x2, y1);
    printf("+");
    int j;
    for (j = 1; j < y2 - y1; j++)
    {
        gotoxy(x2, y1 + j);
        printf("|");
        delay(d);
        gotoxy(x1, y2 - j);
        printf("|");
        delay(d);
    }
}

int lcs(string X, string Y)
{
    int m = X.length();
    int n = Y.length();
    int L[m + 1][n + 1];

    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
                L[i][j] = 0;

            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;

            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }
    return L[m][n];
}

int timetaken(float dist)
{
    // this is for finding the time to reach the destination
    float speed = 0.55;
    return ceil(dist / speed);
}

int money(float dist)
{

    // for calculating the tickect cost
    if (dist <= 2)
        return 20;
    else if (dist > 2 && dist <= 5)
        return 30;
    else if (dist > 5 && dist <= 12)
        return 40;
    else if (dist > 12 && dist <= 21)
        return 50;
    else if (dist > 21 && dist <= 32)
        return 60;
    else
        return 70;
}

void Path(float d, int end_station, int st, int inter)
{

    int size;
    static float dist = 0;
    dist += d;

    gotoxy(16, 11);
    cout << "THE SHORTEST PATH IS : ";

    static int pos_x = 12;
    static int pos_y = 15;
    vector<int> path;
    path.push_back(end_station);
    while (end_station != st)
    {
        size = P[end_station].p.size();
        end_station = P[end_station].p[size - 1];
        path.push_back(end_station);
    }
    vector<int>::iterator i = path.end();
    string str;
    string color;
    if (!inter)
    {
        gotoxy(44, 13);
        cout << "****** LOADING ******";
        delay(2000);
        gotoxy(42, 13);
        cout << "****** ROUTE FOUND ******";
    }
    vector<int>::iterator i2 = path.end();
    i2--;
    int n_of_stations = 0;
    while (i != path.begin())
    {
        i--;
        color = station[*i].color;
        if (color == "BLUE")
            system("color 09");
        else if (color == "YELLOW")
            system("color 06");
        else if (color == "PINK")
            system("color 0D");
        else if (color == "RED")
            system("color 04");
        else if (color == "MAGENTA")
            system("color 05");
        else if (color == "VOILET")
            system("color 01");
        else if (color == "GREEN")
            system("color 02");
        else if (color == "AQUA")
            system("color 03");
        else if (color == "ORANGE")
            system("color 0C");

        if (i != i2)
        {
            if (station[*(i2)].color != station[*(i)].color)
            {
                pos_x = 8;
                pos_y++;
                gotoxy(pos_x, pos_y);
                cout << "{change from " << station[*i2].color << " to " << station[*i].color << "}";
                pos_x = 12;
                pos_y++;
                gotoxy(pos_x, pos_y);
            }
            i2--;
        }
        str = station[*i].name;
        // as the text can go out form the box so that we put pos_x + 5 + str.size() < 106
        // here we are printing the station name and the
        if (pos_x + 5 + str.size() < 106)
        {
            gotoxy(pos_x, pos_y);
            cout << " --> " << str;
            pos_x = pos_x + str.size() + 5;
        }
        else
        {
            pos_x = 12;
            pos_y++;
            gotoxy(pos_x, pos_y);
            cout << " --> " << str;
            pos_x = pos_x + str.size() + 5;
        }
        n_of_stations++;
        delay(700);
    }
    if (!inter)
    {
        gotoxy(12, ++pos_y);
        cout << "INTERMEDIATE STATION";
        pos_y++;
        pos_x = 12;
    }

    if (inter)
    {
        delay(1000);
        gotoxy(72, 11);
        cout << "PATH LENGTH IS :";
        gotoxy(97, 11);
        cout << d << " KM";
        delay(1000);
        gotoxy(16, 10);
        cout << "AVERAGE TIME : ";
        gotoxy(39, 10);
        cout << timetaken(d) << " MIN";
        delay(1000);
        gotoxy(72, 10);
        cout << "AVERAGE FARE : ";
        gotoxy(94, 10);
        cout << " Rs. " << money(d);
        delay(1000);
        gotoxy(72, 12);
        cout << "NO OF STATIONS : ";
        gotoxy(92, 12);
        cout << n_of_stations - 1;
    }
    else
    {
        delay(1000);
        gotoxy(72, 11);
        cout << "PATH LENGTH IS :";
        gotoxy(89, 11);
        cout << d << " KM,";
        delay(1000);
        gotoxy(16, 10);
        cout << "AVERAGE TIME : ";
        gotoxy(32, 10);
        cout << timetaken(d) << " MIN,";
        delay(1000);
        gotoxy(72, 10);
        cout << "AVERAGE FARE : Rs. ";
        gotoxy(91, 10);
        cout << money(d) << ",";
        delay(1000);
        gotoxy(72, 12);
        cout << "NO OF STATIONS : ";
        gotoxy(89, 12);
        cout << n_of_stations - 1 << ",";
    }

    if (inter)
    {
        delay(2500);
        gotoxy(44, 9);
        cout << "PRESS ENTER TO SEARCH AGAIN";
        string choice;
        pos_x = 12;
        pos_y = 15;

        char ch;
        scanf("%c", &ch);
        secondWindow();
    }
    return;
}

int minDistance(float dist[], bool visited[])
{
    float min = INT_MAX;
    int min_index;

    for (int v = 0; v < V; v++)
        // once the if condition is executed and min value changes form INT_MAX to any other then this for will
        if (visited[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}
// (the adjacent_matrix, the starting_station index, the end_station index, do we have an intermidiate station)
void dijkstra(float graph[V][V], int src, int targ, int inter)
{
    float dist[V];
    bool visited[V];
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, visited[i] = false;
    dist[src] = 0;
    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, visited);
        visited[u] = true;
        for (int v = 0; v < V; v++)
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                P[v].p.push_back(u);
            }
    }
 
    Path(dist[targ], targ, src, inter);
}

int sameMatch(string s)
{
    int max = 0, maxi = -1;
    for (int i = 0; i < V; i++)
    {
        int val = lcs(s, station[i].name);
        if (val > max)
        {
            maxi = station[i].code;
            max = val;
        }
    }

    if (max < station[maxi].name.length() / 2)
        return -1;

    // this will return the index of perfect match
    return maxi;
}

string makecapital(string str)
{
    // these are the ascii values
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] > 96 && str[i] < 123)
            str[i] = str[i] - 32;
    }
    return str;
}

void take_input()
{
    char ch;

    // the variables for the strat station, end station and intermidiate station
    string start_s, end_s, inter_s, line, col;
    gotoxy(16, 3);
    cout << "ENTER THE STARTING STATION:";
    gotoxy(20, 5);

    getline(cin, start_s);
    gotoxy(72, 3);
    cout << "ENTER THE DESTINATION STATION:";
    gotoxy(76, 5);
    getline(cin, end_s);
    gotoxy(42, 6);
    cout << "ENTER THE INTERMEDIATE STATION:";
    gotoxy(46, 8);
    getline(cin, inter_s);

    // if checking the station name in data we have to make it either capital case or smaller case
    start_s = makecapital(start_s);
    end_s = makecapital(end_s);
    inter_s = makecapital(inter_s);

    int startcode, endcode, intercode = -1;
    int startflag = 0, endflag = 0, interflag1 = 0, interflag2 = 0;

    if (!(inter_s == "NO" || inter_s == "N"))
        interflag1 = 1;

    startcode = sameMatch(start_s);
    endcode = sameMatch(end_s);
    intercode = sameMatch(inter_s);

    if (startcode == -1)
        startflag = 1;
    if (endcode == -1)
        endflag = 1;
    if (intercode == -1)
        interflag2 = 1;

    int fault = 0;
    if (startflag == 1)
    {
        gotoxy(30, 10);
        cout << "WRONG STARTING STATION NAME ENTERED PRESS ENTER TO RESTART";
        fault = 1;
    }
    if (endflag == 1)
    {
        gotoxy(30, 11);
        cout << "WRONG DESTINATION STATION NAME ENTERED PRESS ENTER TO RESTART";
        fault = 1;
    }
    if (interflag1 && interflag2 == 1)
    {
        gotoxy(30, 12);
        cout << "WRONG INTERMEDIATE STATION NAME ENTERED PRESS ENTER TO RESTART";
        fault = 1;
    }
    if (fault)
    {

        scanf("%c", &ch);
        secondWindow();
        return;
    }
    if (interflag1)
    {
        // here the function for finding the sortest path
        dijkstra(graph, startcode, intercode, 0);
        dijkstra(graph, intercode, endcode, 1);
    }
    else
        dijkstra(graph, startcode, endcode, 1);
}

void logo(int x, int y)
{
    gotoxy(x, y);
    printf("   ___                     ___       ____");
    gotoxy(x, y + 1);
    printf(" ||   \\\\   ||\\\\    //||  ||   \\\\   //    \\\\");
    gotoxy(x, y + 2);
    printf(" ||    ||  || \\\\  // ||  ||    || ||");
    gotoxy(x, y + 3);
    printf(" ||    ||  ||  \\\\//  ||  ||___//  ||");
    gotoxy(x, y + 4);
    printf(" ||    ||  ||        ||  ||  \\\\   ||");
    gotoxy(x, y + 5);
    printf(" ||___//   ||        ||  ||   \\\\   \\\\____//");
}

void secondWindow()
{
    // clear the screen for next UI
    clrscreen();
    gotoxy(48, 19);
    system("color 0C");
    delay(90);

    take_input();
}

void printing_UI()
{

    // here we will print out the logo and some basic instructions and then we will move the secondWindow() function
    system("color 0A");
    drawbox(1, 0, 117, 29, 4);
    system("color 0C");
    delay(90);
    system("color 0A");
    delay(90);
    // logo i.e. DMRC
    logo(37, 4);
    system("color 0C");
    delay(90);
    drawbox(30, 3, 87, 11, 4);
    drawbox(28, 2, 89, 12, 4);
    system("color 0C");
    delay(90);
    system("color 0A");
    delay(90);
    gotoxy(42, 14);
    cout << "WELCOME TO DELHI METRO DESKTOP APP";
    system("color 0C");
    delay(90);
    system("color 0D");
    delay(90);
    gotoxy(47, 18);
    printf("PRESS ENTER TO CONTINUE");
    char ch;
    scanf("%c", &ch);
    secondWindow();
}

int main()
{

    system("cls");

    // the storage sequence in the node_values_new.txt file is : -
    // number of stations connected, current station, connected station, distance form current station to connected station, and so on .......

    // this variable is for number of connected stations to a particular station
    int num_connected_stations;

    // this variable is for which station we are talking about right now
    int which_station;

    // this variable is for the connected stations to that particular station
    int connected_station;

    // this is for the distance of that station from that particular station
    float distance;

    // Opens the file identified by argument filename
    ifstream node_file;
    node_file.open("node_values_new.txt");

    // adding the nodes to the graph
    // V is the constant whose value is equal to 248 as we have 248 stations
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
            graph[i][j] = 0;
    }

    for (int i = 1; i <= V; i++)
    {
        node_file >> num_connected_stations;
        node_file >> which_station;
        for (int j = 0; j < num_connected_stations; j++)
        {
            node_file >> connected_station;
            node_file >> distance;

            // we subtract one because in the node_values_new.txt file we have start the indexing from 1 instead of 0
            graph[which_station - 1][connected_station - 1] = distance;
        }
    }

    // this is to show the graph into the txt file
    ofstream matrix;
    matrix.open("matrix.txt");
    matrix << "  ";
    for (int i = 0; i < V; i++)
        matrix << i << " ";
    matrix << endl;
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (j == 0)
                matrix << i << " ";
            matrix << graph[i][j] << " ";
        }
        matrix << endl;
    }

    // these two variables help to get the color and name form the txt files
    string name_line, color_line;

    // Opens the file identified by argument filename
    ifstream station_name;
    ifstream station_color;
    station_name.open("stationcodes.txt");
    station_color.open("stationcolorcodes.txt");

    for (int i = 0; i < V; i++)
    {

        // getline function will help to store the string in name_line variable form station_name ifstream object which open the txt file
        getline(station_name, name_line);
        station[i].name = name_line;
        station[i].code = i;
        getline(station_color, color_line);
        station[i].color = color_line;
    }

    printing_UI();

    return 0;
}