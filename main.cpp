#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ranges>
#include <unordered_map>
#include <map>
#include <sstream>
#include <set>
#include <stack>
#include <variant>
#include <array>
#include <numeric>
#include <sstream>
#include <iomanip>

std::vector<std::string> split (const std::string& s, const std::string& delimiter) {
    std::size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

int day1_1()
{
    int result = 0;
    int acc = 0;

    std::ifstream input("day1.txt");
    std::string line;

    while(std::getline(input, line))
    {
        if(line.empty())
        {
            result = std::max(result, acc);
            acc = 0;
            continue;
        }
        acc += std::stoi(line);
    }

    return result;
}

int day1_2()
{
    int acc = 0;
    std::vector<int> elves;

    std::ifstream input("day1.txt");
    std::string line;

    while(std::getline(input, line))
    {
        if(line.empty())
        {
            elves.push_back(acc);
            acc = 0;
            continue;
        }
        acc += std::stoi(line);
    }

    std::ranges::sort(elves, [](int l, int r){return l>r;});
    return elves[0] + elves[1] + elves[2];
}


int day2_1()
{
    int result = 0;

    std::ifstream input("day2.txt");
    std::string line;

    while(std::getline(input, line))
    {
        int l = line.at(0) - 'A';
        int r = line.at(2) - 'X';

        result += (l == r ? 3 : (l+1)%3 == r ? 6 : 0) + r + 1;
    }

    return result;
}

int day2_won(int l, int r)
{
    if(r == 0) return l == 0 ? 3 : l;
    if(r == 1) return 3 + l + 1;
    if(r == 2) return 6 + ((l+1)%3) + 1;

    return 0;
}

int day2_2()
{
    int result = 0;

    std::ifstream input("day2.txt");
    std::string line;

    while(std::getline(input, line))
    {
        int l = line.at(0) - 'A';
        int r = line.at(2) - 'X';

        result += day2_won(l,r);
    }

    return result;
}


int day3_1()
{
    int result = 0;
    std::map<char, bool> values;

    std::ifstream input("day3.txt");
    std::string line;

    while(std::getline(input, line))
    {
        for(int i = 0; i < line.size() / 2; i++)
        {
            values[line[i]] = true;
        }

        for(int i = line.size() / 2; i < line.size(); i++)
        {
            if(values.contains(line[i]))
            {
                const int prio = line[i] > 96 ? line[i] - 'a' + 1 : line[i] - 'A' + 27;
                result += prio;
                break;
            }
        }
        values.clear();
    }
    return result;
}


int day3_2()
{
    int result = 0;
    std::unordered_map<char, int> values{};
    std::unordered_map<char, bool> exists{};

    std::ifstream input("day3.txt");
    std::string line;

    int elfCounter = 0;
    
    while(std::getline(input, line))
    {
        for(int i = 0; i < line.size(); i++)
        {
            exists[line[i]] = true;
        }

        for(const auto i : exists | std::views::keys)
        {
            values[i]++;
        }
        exists.clear();

        if(elfCounter == 2)
        {
            for(const auto [k, v] : values)
            {
                if(v == 3)
                {
                    result += k > 96 ? k - 'a' + 1 : k - 'A' + 27;
                    break;
                }
            }
            values.clear();
            elfCounter = 0;
        }else{
            elfCounter++;
        }

        
    }
    return result;
}


int day4_1()
{
    int result = 0;
    std::ifstream input("day4.txt");
    std::string line;

    while(std::getline(input, line))
    {
        const auto pairs = split(line, ",");
        int a,b,c,d;
        const auto p1 = split(pairs[0], "-");
        const auto p2 = split(pairs[1], "-");
        a = std::stoi(p1[0]);
        b = std::stoi(p1[1]);
        c = std::stoi(p2[0]);
        d = std::stoi(p2[1]);

        result += ((a <= c && b >= d) || (a >= c && d >= b)) ? 1 : 0;
        //std::cout << "\n" << a << "-" << b << ":" << c << "-" << d << "\n";

    }

    return result;
}


int day4_2()
{
    int result = 0;
    std::ifstream input("day4.txt");
    std::string line;

    while(std::getline(input, line))
    {
        const auto pairs = split(line, ",");
        const auto p1 = split(pairs[0], "-");
        const auto p2 = split(pairs[1], "-");
        const int a = std::stoi(p1[0]);
        const int b = std::stoi(p1[1]);
        const int c = std::stoi(p2[0]);
        const int d = std::stoi(p2[1]);

        if((a >= c && a <= d) || (b >= c && b <= d) || ((c >= a && c <= b) || (d >= a && d <= b)))
        {
            result += 1; 
        }
    }

    return result;
}


std::string day5_1()
{
    std::ifstream input("day5.txt");
    std::string line;
    std::vector<std::string> lines;
    std::vector<std::stack<char>> stacks;
    stacks.resize(9);
    bool header = false;

    while(std::getline(input, line))
    {
        if(!header)
        {
            if(line.empty())
            {
                header = true;

                for(int i = lines.size() - 2; i >= 0; i--)
                {
                    for(int x = 0; x < 9; x++)
                    {
                        char c = lines[i].at(x*4+1);
                        if(c == ' ') continue;
                        stacks[x].push(c);
                    }
                }

                lines.clear();
                continue;
            }
            lines.push_back(line);
        }
        else
        {
            const auto splitStr = split(line, " ");
            const int amount = std::stoi(splitStr[1]);
            const int src = std::stoi(splitStr[3]) - 1;
            const int dst = std::stoi(splitStr[5]) - 1;

            for(int i = 0; i < amount; i++)
            {
                stacks[dst].push(stacks[src].top());
                stacks[src].pop();
            }

        }
    }

    std::string result{};
    for(int i = 0; i < stacks.size(); i++)
    {
        result += stacks[i].top();
    }

    return result;
}

std::string day5_2()
{
    std::ifstream input("day5.txt");
    std::string line;
    std::vector<std::string> lines;
    std::vector<std::stack<char>> stacks;
    stacks.resize(9);
    bool header = false;

    while(std::getline(input, line))
    {
        if(!header)
        {
            if(line.empty())
            {
                header = true;

                for(int i = lines.size() - 2; i >= 0; i--)
                {
                    for(int x = 0; x < 9; x++)
                    {
                        char c = lines[i].at(x*4+1);
                        if(c == ' ') continue;
                        stacks[x].push(c);
                    }
                }

                lines.clear();
                continue;
            }
            lines.push_back(line);
        }
        else
        {
            const auto splitStr = split(line, " ");
            const int amount = std::stoi(splitStr[1]);
            const int src = std::stoi(splitStr[3]) - 1;
            const int dst = std::stoi(splitStr[5]) - 1;

            std::stack<char> temp{};

            for(int i = 0; i < amount; i++)
            {
                temp.push(stacks[src].top());
                stacks[src].pop();
            }

            do
            {
                stacks[dst].push(temp.top());
                temp.pop();
            }while(!temp.empty());

        }
    }

    std::string result{};
    for(int i = 0; i < stacks.size(); i++)
    {
        result += stacks[i].top();
    }

    return result;
}


int day6_1()
{
    std::ifstream input("day6.txt");
    std::string line;

    std::getline(input, line);

    for(int i = 3; i < line.size(); i++)
    {
        std::set<char> set;

        for(int j = 0; j < 4; j++)
        {
            set.insert(line[i-j]);
        }
        
        if(set.size() == 4)
        {
            return i+1;
        }

    }

    return 0;
}


int day6_2()
{
    std::ifstream input("day6.txt");
    std::string line;

    std::getline(input, line);

    for(int i = 13; i < line.size(); i++)
    {
        std::set<char> set;

        for(int j = 0; j < 14; j++)
        {
            set.insert(line[i-j]);
        }
        
        if(set.size() == 14)
        {
            return i+1;
        }

    }

    return 0;
}


struct FileSystemEntry
{
    FileSystemEntry(const std::string& name, int size, FileSystemEntry* parent) : name(name), type(size>0), size(size), parent(parent){}
    std::string name{};
    bool type = false;
    int size = 0;
    FileSystemEntry* parent = nullptr;
    std::vector<FileSystemEntry> children{};
};

void printFileSystem(FileSystemEntry* ptr, const int depth = 0)
{
    std::cout << std::string(depth, '\t') << "- " << ptr->name << (!ptr->type ? " (dir), " + std::to_string(ptr->size) + ")" : " (file, " + std::to_string(ptr->size) + ")") << "\n";

    for(auto& elem : ptr->children)
    {
        printFileSystem(&elem, depth + 1);
    }
}

void calculateFileSizes(FileSystemEntry* ptr)
{
    if(ptr->type)
    {
        FileSystemEntry* temp = ptr->parent;
        while(temp != nullptr)
        {
            temp->size += ptr->size;
            temp = temp->parent;
        }
    }

    for(auto& elem : ptr->children)
    {
        calculateFileSizes(&elem);
    }
}

int findBigDirectories(FileSystemEntry* ptr)
{
    int result = 0;

    if(ptr->size < 100000 && !ptr->type)
    {
        result += ptr->size;
    }

    for(auto& elem : ptr->children)
    {
        result += findBigDirectories(&elem);
    }

    return result;
}

int day7_1()
{
    std::ifstream input("day7.txt");
    std::string line;

    FileSystemEntry root{"/", 0, nullptr};
    FileSystemEntry* cwd = nullptr;

    while(std::getline(input, line))
    {
        if(line.at(0) == '$')
        {
            const auto cmd = split(line, " ");
            if(cmd.at(1) == "cd")
            {
                if(cmd.at(2) == "/")
                {
                    cwd = &root;
                }
                else if(cmd.at(2) == "..")
                {
                    cwd = cwd->parent;
                }
                else
                {
                    for(auto& children : cwd->children)
                    {
                        if(children.name == cmd.at(2))
                        {
                            cwd = &children;
                            break;
                        }
                    }
                }
            }
        }
        else //ls output
        {
            const auto output = split(line, " ");

            if(output.at(0) == "dir")
            {
                cwd->children.emplace_back(output.at(1), 0, cwd);
            }
            else
            {
                cwd->children.emplace_back(output.at(1), std::stoi(output.at(0)), cwd);
            }
        }
    }
    
    calculateFileSizes(&root);

    //std::cout <<"\n";
    //printFileSystem(&root);



    return findBigDirectories(&root);
}

int findToDelete(FileSystemEntry* ptr, const int required, const int smallest = INT_MAX)
{
    int result = -1;

    if(!ptr->type && ptr->size >= required && ptr->size <= smallest)
    {
        result = ptr->size;
    }

    for(auto& elem : ptr->children)
    {
        if(elem.type) continue;
        const int r = findToDelete(&elem, required, smallest);
        if(r != -1){
            result = std::min(result, r);
        }
        
    }

    return result;
}

int day7_2()
{
    std::ifstream input("day7.txt");
    std::string line;

    FileSystemEntry root{"/", 0, nullptr};
    FileSystemEntry* cwd = nullptr;
    constexpr int fileSystemSize = 70000000;
    constexpr int requiredSize = 30000000;

    while(std::getline(input, line))
    {
        if(line.at(0) == '$')
        {
            const auto cmd = split(line, " ");
            if(cmd.at(1) == "cd")
            {
                if(cmd.at(2) == "/")
                {
                    cwd = &root;
                }
                else if(cmd.at(2) == "..")
                {
                    cwd = cwd->parent;
                }
                else
                {
                    for(auto& children : cwd->children)
                    {
                        if(children.name == cmd.at(2))
                        {
                            cwd = &children;
                            break;
                        }
                    }
                }
            }
        }
        else //ls output
        {
            const auto output = split(line, " ");

            if(output.at(0) == "dir")
            {
                cwd->children.emplace_back(output.at(1), 0, cwd);
            }
            else
            {
                cwd->children.emplace_back(output.at(1), std::stoi(output.at(0)), cwd);
            }
        }
    }
    
    calculateFileSizes(&root);

    //std::cout <<"\n";
    //printFileSystem(&root);

    const int required = requiredSize - (fileSystemSize - root.size);
    return findToDelete(&root, required);
}

int day8_1()
{
    int result = 0;
    std::ifstream input("day8.txt");
    std::string line;
    std::vector<int> trees;
    int width{};
    int height{};

    while(std::getline(input, line))
    {
        for(const auto c : line)
        {
            trees.push_back(c - '0');
        }
        width = line.size();
        height++;
    }

    for(int y = 1; y < height - 1; y++)
    {
        for(int x = 1; x < width - 1; x++)
        {
            const int current = trees.at(y*width + x);

            bool left = true;
            for(int i = 0; i < x; i++)
            {
                if(trees.at(y*width+i) >= current)
                {
                    left = false;
                }
            }

            if(left){result++; continue;}

            bool right = true;
            for(int i = x + 1; i < width; i++)
            {
                if(trees.at(y*width+i) >= current)
                {
                    right = false;
                }
            }

            if(right){result++; continue;}

            bool top = true;
            for(int i = 0; i < y; i++)
            {
                if(trees.at(i*width+x) >= current)
                {
                    top = false;
                }
            }

            if(top){result++; continue;}

            bool bot = true;
            for(int i = y+1; i < height; i++)
            {
                if(trees.at(i*width+x) >= current)
                {
                    bot = false;
                }
            }

            if(bot){result++; continue;}

        }
      
    }

    result += 2 * width + (2*height) - 4;

    return result;
}


int day8_2()
{
    int result = 0;
    std::ifstream input("day8.txt");
    std::string line;
    std::vector<int> trees;
    int width{};
    int height{};

    while(std::getline(input, line))
    {
        for(const auto c : line)
        {
            trees.push_back(c - '0');
        }
        width = line.size();
        height++;
    }

    for(int y = 1; y < height - 1; y++)
    {
        for(int x = 1; x < width - 1; x++)
        {
            const int current = trees.at(y*width + x);
            int scenic_r = 0;
            int scenic_l = 0;
            int scenic_b = 0;
            int scenic_t = 0;

            for(int i = x+1; i < width; i++)
            {
                scenic_r++;

                if(trees.at(y*width + i) >= current)
                    break;
            }

            for(int i = x-1; i >= 0; i--)
            {
                scenic_l++;

                if(trees.at(y*width + i) >= current)
                    break;
            }

            for(int i = y+1; i < height; i++)
            {
                scenic_b++;
                if(trees.at(i*width + x) >= current)
                    break;
            }

            for(int i = y-1; i >= 0; i--)
            {
                scenic_t++;
                if(trees.at(i*width + x) >= current)
                    break;
            }

            result = std::max(result, scenic_r * scenic_b * scenic_l * scenic_t);
        }
    }

    return result;
}


template<typename T>
struct Vector
{
    Vector() = default;
    Vector(const T _x, const T _y) : x(_x), y(_y) {}
    T x{};
    T y{};

    float mag(){return std::sqrt(x*x+y*y);}
    Vector<T> abs(){return {std::abs(x), std::abs(y)};}
    Vector<T> dir(const Vector<T>& v) const
    {
        auto diff = Vector<T>{x - v.x, y - v.y};
        if(diff.x != 0) diff.x /= std::abs(diff.x);
        if(diff.y != 0) diff.y /= std::abs(diff.y);
        return diff;
    }

    int manhattan(const Vector<T>& other) const
    {
        return std::abs(x - other.x) + std::abs(y - other.y);
    }
    friend bool operator< (const auto& lhs, const auto& rhs){ return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y); } 
    bool operator== (const auto& other) const{ return x == other.x && y == other.y; }
    bool operator!= (const auto& other){ return !operator==(other); }
    Vector<T> operator+ (const auto& other) { return {x + other.x, y + other.y}; }
    Vector<T> operator- (const auto& other) { return {x - other.x, y - other.y}; }
    Vector<T>& operator-= (const auto& other) { x -= other.x; y -= other.y; return *this; }
    Vector<T>& operator+= (const auto& other) { x += other.x; y += other.y; return *this; }
    friend std::ostream& operator<< (std::ostream& os, const auto& value){os << value.x << " | " << value.y; return os;}
};

using Vec2i = Vector<int>;

int day9_1()
{
    std::ifstream input("day9.txt");
    std::string line;
    std::vector<Vec2i> moves;
    std::set<Vec2i> visited;
    Vec2i head{};
    Vec2i tail{};

    while(std::getline(input, line))
    {
        const auto splitStr = split(line, " ");
        Vec2i dir{};
        if(splitStr.at(0) == "R")
        {
            dir = {1,0};
        }
        if(splitStr.at(0) == "D")
        {
            dir = {0,1};
        }
        if(splitStr.at(0) == "L")
        {
            dir = {-1,0};
        }
        if(splitStr.at(0) == "U")
        {
            dir = {0,-1};
        }

        for(int i = 0; i < std::stoi(splitStr.at(1)); i++)
        {
            moves.push_back(dir);
        }
    }

    //std::cout << "\n";
    for(const auto& m : moves)
    {
        head += m;

        //std::cout << "Head: " << head << "\n";
        if((head - tail).mag() > 1.5f)
        {
            if(head.x == tail.x || head.y == tail.y)
            {
                tail += m;
            }else{
                auto diff = head - tail;
                diff.x /= std::abs(diff.x);
                diff.y /= std::abs(diff.y);
                tail += diff;
            }
        }
        //std::cout << "Tail: " << tail << "\n\n";

        visited.insert(tail);

        // for(int y = -4; y < 1; y++)
        // {
        //     for(int x = 0; x < 6; x++)
        //     {
        //         if(Vec2i{x, y} == head)
        //         {
        //             std::cout<<"H";
        //         }
        //         else if(Vec2i{x,y} == tail)
        //         {
        //             std::cout<<"T";
        //         }
        //         else if(visited.contains(Vec2i{x,y}))
        //         {
        //             std::cout<<"#";
        //         }
        //         else{
        //             std::cout<<".";
        //         }
        //     }
        //     std::cout << "\n";
        // }
        // std::cout << "\n";
    }

    return visited.size();
}


int day9_2()
{
    std::ifstream input("day9.txt");
    std::string line;
    std::vector<Vec2i> moves;
    std::set<Vec2i> visited;
    std::array<Vec2i, 10> rope{};

    while(std::getline(input, line))
    {
        const auto splitStr = split(line, " ");
        Vec2i dir{};
        if(splitStr.at(0) == "R")
        {
            dir = {1,0};
        }
        if(splitStr.at(0) == "D")
        {
            dir = {0,1};
        }
        if(splitStr.at(0) == "L")
        {
            dir = {-1,0};
        }
        if(splitStr.at(0) == "U")
        {
            dir = {0,-1};
        }

        for(int i = 0; i < std::stoi(splitStr.at(1)); i++)
        {
            moves.push_back(dir);
        }
    }

    for(const auto& m : moves)
    {
        rope[0] += m;

        for(int i = 0; i < rope.size()-1; i++)
        {
            auto& head = rope[i];
            auto& tail = rope[i+1];

            if((head - tail).mag() > 1.5f)
            {
                auto diff = head - tail;
                if(diff.x != 0) diff.x /= std::abs(diff.x);
                if(diff.y != 0) diff.y /= std::abs(diff.y);
                tail += diff;
            }
        }

        visited.insert(rope[9]);
   
        // for(int y = -20; y < 21; y++)
        // {
        //     for(int x = -20; x < 21; x++)
        //     {
        //         int c = 0;
        //         bool w = false;
        //         for(const auto& r : rope)
        //         {
        //             if(r == Vec2i{x,y})
        //             {
        //                 if(c == 0)
        //                 {
        //                     std::cout << "H";
        //                 }
        //                 else{
        //                     std::cout << c;
        //                 }
                        
        //                 w = true;
        //                 continue;
        //             }
        //             c++;
        //         }

        //         if(w) continue;
        //         if(visited.contains(Vec2i{x,y}))
        //         {
        //             std::cout<<"#";
        //         }
        //         else{
        //             std::cout<<".";
        //         }
        //     }
        //     std::cout << "\n";
        // }
        // std::cout << "\n";
    }

    return visited.size();

    return 0;
}

int day10_1()
{
    int result = 0;
    std::vector<int> values{};
    int reg = 1;
    std::ifstream input("day10.txt");
    std::string line;

    while(std::getline(input, line))
    {
        const auto cmd = split(line, " ");
        const int regP = reg;
        if(cmd.at(0) == "noop")
        {
            values.push_back(reg);
        }
        else if(cmd.at(0) == "addx")
        {
            const int p = std::stoi(cmd.at(1));
            values.push_back(reg);
            values.push_back(reg);
            reg = reg + p;
        }
    }

    // std::cout << "\n";
    // int c = 1;
    // for(const auto i : values)
    // {
    //     std::cout << "cycle " << c++ << ": " << i << "\n";
    // }
    return values[19]*20+values[59]*60+values[99]*100+values[139]*140+values[179]*180+values[219]*220;
}

void day10_2()
{
    int result = 0;
    std::vector<int> values{};
    int reg = 1;
    std::ifstream input("day10.txt");
    std::string line;

    const auto printPixel = [&](int cycle, int spritePos)
    {
        if(cycle % 40 == 0){std::cout << "\n";}

        const int pos = cycle % 40;
        if(pos > spritePos - 2 && pos < spritePos + 2)
        {
            std::cout << "#";
        }
        else{
            std::cout << " ";
        }
    
    };


    while(std::getline(input, line))
    {
        const auto cmd = split(line, " ");
        const int regP = reg;
        if(cmd.at(0) == "noop")
        {
            values.push_back(reg);
        }
        else if(cmd.at(0) == "addx")
        {
            const int p = std::stoi(cmd.at(1));
            values.push_back(reg);
            values.push_back(reg);
            reg = reg + p;
        }
    }
    
    for(int i = 0; i < values.size(); i++)
    {
        printPixel(i, values[i]);
    }

}

struct Monkey
{
    std::vector<std::uint64_t> items{};
    std::string operation{};
    int test{};
    int trueTo{};
    int falseTo{};
    int inspections{};

    friend std::ostream& operator<< (std::ostream& os, const Monkey& m)
    {
        os << "Monkey holds the items: ";
        for(const auto i : m.items)
        {
            os << i << " ";
        }
        os << "\nIt inspected " << m.inspections << " times.";
        return os;
    }
};


int day11_1()
{
    std::ifstream input("day11.txt");
    std::string line;
    std::vector<std::string> lines;
    std::vector<Monkey> monkeys;
    constexpr int rounds = 20;

    while(std::getline(input, line))
    {
        if(!line.empty())
        {
            lines.push_back(line);
        }
    }

    for(int i = 0; i < lines.size() / 6; i++)
    {
        Monkey monkey;
        const auto items = split(lines[i*6+1].substr(18), ", ");
        for(const auto i : items)
        {
            monkey.items.push_back(std::stoi(i));
        }
        monkey.operation = lines[i*6+2].substr(19);
        monkey.test = std::stoi(lines[i*6+3].substr(21));
        monkey.trueTo = std::stoi(lines[i*6+4].substr(29));
        monkey.falseTo = std::stoi(lines[i*6+5].substr(30));

        monkeys.push_back(monkey);
    }

    const auto worry = [](int value, const std::string& op)->int
    {
        const auto cmd = split(op, " ");
        const int right = cmd.at(2) == "old" ? value : std::stoi(cmd.at(2));
        if(cmd.at(1) == "+")
        {
            return value + right;
        }
        else if(cmd.at(1) == "*")
        {
            return value * right;
        }
        return 0;
    };

    for(int i = 0; i < rounds; i++)
    {
        for(int k = 0; k < monkeys.size(); k++)
        {
            auto& m = monkeys[k];
            for(int j = 0; j < m.items.size(); j++)
            {
                m.items[j] = worry(m.items[j], m.operation) / 3;
                m.inspections++;

                if(m.items[j] % m.test == 0)
                {
                    monkeys[m.trueTo].items.push_back(m.items[j]);
                    //std::cout << "Monkey " << k << " throws item with value " << m.items[j] << " to monkey " << m.trueTo << ".\n";
                }
                else{
                    monkeys[m.falseTo].items.push_back(m.items[j]);
                    //std::cout << "Monkey " << k << " throws item with value " << m.items[j] << " to monkey " << m.falseTo << ".\n";
                }
            }
            
            m.items.clear();
        }
    }

    std::vector<int> active;
    for(const auto& m : monkeys)
    {
        active.push_back(m.inspections);
        //std::cout << m << "\n";
    }
    std::ranges::sort(active);
    std::ranges::reverse(active);

    return active[0] * active[1];
}


std::uint64_t day11_2()
{
    std::ifstream input("day11.txt");
    std::string line;
    std::vector<std::string> lines;
    std::vector<Monkey> monkeys;
    constexpr int rounds = 10000;

    while(std::getline(input, line))
    {
        if(!line.empty())
        {
            lines.push_back(line);
        }
    }

    for(int i = 0; i < lines.size() / 6; i++)
    {
        Monkey monkey;
        const auto items = split(lines[i*6+1].substr(18), ", ");
        for(const auto i : items)
        {
            monkey.items.push_back(std::stoi(i));
        }
        monkey.operation = lines[i*6+2].substr(19);
        monkey.test = std::stoi(lines[i*6+3].substr(21));
        monkey.trueTo = std::stoi(lines[i*6+4].substr(29));
        monkey.falseTo = std::stoi(lines[i*6+5].substr(30));

        monkeys.push_back(monkey);
    }

    const auto worry = [](int value, const std::string& op)->std::uint64_t
    {
        const auto cmd = split(op, " ");
        const std::uint64_t right = cmd.at(2) == "old" ? value : std::stoi(cmd.at(2));
        if(cmd.at(1) == "+")
        {
            return value + right;
        }
        else if(cmd.at(1) == "*")
        {
            return value * right;
        }
        return 0;
    };

    int smod = 1;
    for(auto &m : monkeys){smod *= m.test;}

    for(int i = 0; i < rounds; i++)
    {
        for(int k = 0; k < monkeys.size(); k++)
        {
            auto& m = monkeys[k];
            for(int j = 0; j < m.items.size(); j++)
            {
                m.items[j] = worry(m.items[j], m.operation) % smod;
                m.inspections++;

                if(m.items[j] % m.test == 0)
                {
                    monkeys[m.trueTo].items.push_back(m.items[j]);
                    //std::cout << "Monkey " << k << " throws item with value " << m.items[j] << " to monkey " << m.trueTo << ".\n";
                }
                else{
                    monkeys[m.falseTo].items.push_back(m.items[j]);
                    //std::cout << "Monkey " << k << " throws item with value " << m.items[j] << " to monkey " << m.falseTo << ".\n";
                }
            }
            
            m.items.clear();
        }
    }

    std::vector<std::int64_t> active;
    for(const auto& m : monkeys)
    {
        active.push_back(m.inspections);
        //std::cout << m << "\n";
    }
    std::ranges::sort(active);
    std::ranges::reverse(active);

    return active[0] * active[1];
}


int day12_1()
{
    std::ifstream input("day12.txt");
    std::string line;
    std::vector<char> map;
    int start{};
    int end{};
    int result{};

    int x = 0;
    int y = 0;
    int w = 0;
    while(std::getline(input, line))
    {
        w = line.size();
        for(const char c : line)
        {
            if(c == 'S')
            {
                map.push_back('a');
                start = w * y + x;
            }else if(c == 'E')
            {
                map.push_back('z');
                end = w * y + x;
            }
            else
            {
                map.push_back(c);
            }
            ++x;
        }
        x = 0;
        ++y;
    }

    std::vector<bool> visited(map.size());
    std::deque<Vec2i> queue;
    queue.push_back({0, end});

    while(true)
    {
        const auto pair = queue.front();
        queue.pop_front();

        if(visited[pair.y])
        {
            continue;
        }

        visited[pair.y] = true;
        if(map[pair.y] == 'a')
        {
            if(pair.y == start)
            {
                result = pair.x;
                break;
            }
        }

        for(auto d : {1, -1, -w, w}) //right, left, up, down
        {
            const int n = pair.y + d;
            if(n < 0 || n > static_cast<int>(map.size()) || visited[n] || (map[pair.y] - map[n]) > 1)
            {
                continue;
            }
            queue.push_back({pair.x+1, n});
        }
    }

    return result;
}


int day12_2()
{
    std::ifstream input("day12.txt");
    std::string line;
    std::vector<char> map;
    int start{};
    int end{};
    int result{};

    int x = 0;
    int y = 0;
    int w = 0;
    while(std::getline(input, line))
    {
        w = line.size();
        for(const char c : line)
        {
            if(c == 'S')
            {
                map.push_back('a');
                start = w * y + x;
            }else if(c == 'E')
            {
                map.push_back('z');
                end = w * y + x;
            }
            else
            {
                map.push_back(c);
            }
            ++x;
        }
        x = 0;
        ++y;
    }

    const auto pathFind = [&](int s){
        std::vector<bool> visited(map.size());
        std::deque<Vec2i> queue;
        queue.push_back({0, end});

        while(true)
        {
            if(queue.empty()) return INT_MAX; //no possible way
            const auto pair = queue.front();
            queue.pop_front();

            if(visited[pair.y])
            {
                continue;
            }

            visited[pair.y] = true;
            if(map[pair.y] == 'a')
            {
                if(pair.y == s)
                {
                    return pair.x;
                }
            }

            for(auto d : {1, -1, -w, w}) //right, left, up, down
            {
                const int n = pair.y + d;
                if(n < 0 || n > static_cast<int>(map.size()) || visited[n] || (map[pair.y] - map[n]) > 1)
                {
                    continue;
                }
                queue.push_back({pair.x+1, n});
            }
        }

    };

    std::vector<std::size_t> startIndices{};
    for(std::size_t i = 0; i < map.size(); i++)
    {
        if(map[i] == 'a')
        {
            startIndices.push_back(i);
        }
    }

    int min = INT_MAX;
    for(const auto i : startIndices) //brute force all start points
    {
        min = std::min(min, pathFind(i));
    }

    return min;
}



int day13_1()
{
    std::ifstream input("day13.txt");

    std::string line1;
    std::string line2;
    std::vector<int> right;
    int list = 0;

    while(getline(input,line1))
    {
        if(line1.empty())
        {
            continue;
        }

        list++;

        getline(input, line2);
        int i = 0, j = 0;

        while(i < line1.size() && j < line2.size())
        {
            if(std::isdigit(line1[i]) && std::isdigit(line2[j]))
            {
                std::string x1{};
                std::string x2{};

                while(i < line1.size() && std::isdigit(line1[i]))
                {
                    x1 += line1[i];
                    i++;
                }

                while(j < line2.size() && std::isdigit(line2[j]))
                {
                    x2 += line2[j];
                    j++;
                }

                if(stoi(x1) == stoi(x2)) 
                {
                    continue;
                }
                if(stoi(x1) < stoi(x2))
                {
                    right.push_back(list);
                }
                break;
            }
            if(line1[i] == line2[j])
            {
                i++;
                j++;
                continue;
            }
            else
            {
                if(line1[i] == ']'){
                    right.push_back(list);
                    break;
                }
                else if(line2[j] == ']') break;
                else if(line1[i] == '[' || line1[i] == ',')
                { 
                    i++;
                    continue;
                }
                else if(line2[j] == '[' || line2[j] == ',')
                {
                    j++;
                    continue;
                }
            }
        }
        
        if(i == line1.size()) right.push_back(list);
    }

    int ans = 0;
    ans = std::accumulate(right.begin(), right.end(), ans);
    return ans;
}


int day13_2()
{
    std::fstream input("day13.txt");
    std::string line1;
    std::string line2;

    int list = 0;
    std::vector<std::string> signals{"[[2]]", "[[6]]"};
    int cnt[2] = {0};

    while(getline(input,line2))
    {
        if(line2.empty())
        {
            continue;
        }

        list++;

        for(int x = 0; x < 2; x++){
            line1 = signals[x];
            int i = 0, j = 0;
            while(i < line1.length() && j < line2.length()){
                if(std::isdigit(line1[i]) && std::isdigit(line2[j]))
                {
                    std::string x1 = "", x2 = "";

                    while(i < line1.size() && std::isdigit(line1[i]))
                    {
                        x1 += line1[i];
                        i++;
                    }

                    while(j < line2.size() && std::isdigit(line2[j]))
                    {
                        x2 += line2[j];
                        j++;
                    }

                    if(stoi(x1) == stoi(x2))
                    {
                        continue;
                    } 

                    if(stoi(x1) < stoi(x2))
                    {
                    cnt[x]++;
                    }
                    break;
                }

                if(line1[i] == line2[j]){
                    i++;
                    j++;
                    continue;
                }
                else
                {
                    if(line1[i] == ']'){
                    cnt[x]++;
                    break;
                    }
                    else if(line2[j] == ']') break;
                    else if(line1[i] == '[' || line1[i] == ','){ 
                    i++;
                    continue;
                    }
                    else if(line2[j] == '[' || line2[j] == ','){
                    j++;
                    continue;
                    }
                }
            }
            if(i == line1.length())
            {
                cnt[x]++;
            }
        }
    }

    return (list - cnt[0] + 1)*(list - cnt[1] + 2);
}


// int day14_1()
// {
//     std::ifstream input("day14.txt");
//     std::string line;
//     std::set<Vec2i> inputVecs;

//     const auto toVec = [](const std::string& str) -> Vec2i
//     {
//         const auto spl = split(str, ",");
//         return {std::stoi(spl.at(0)), std::stoi(spl.at(1))};
//     };

//     Vec2i topLeft{INT_MAX, 0};
//     Vec2i bottomRight{-INT_MAX, -INT_MAX};

//     while(std::getline(input, line))
//     {
        
//         const auto coordList = split(line, " -> ");
        
//         for(int i = 0; i < coordList.size() - 1; i++)
//         {
//             auto src = toVec(coordList[i]);
//             const auto dst = toVec(coordList[i+1]);
//             const auto dir = dst.dir(src);

//             bool br = false;
//             while(true)
//             {
//                 if(src.x < topLeft.x) topLeft.x = src.x;
//                 if(src.y < topLeft.y) topLeft.y = src.y;
//                 if(src.x > bottomRight.x) bottomRight.x = src.x;
//                 if(src.y > bottomRight.y) bottomRight.y = src.y;
//                 inputVecs.insert(src);
//                 src += dir;

//                 if(br) break;
//                 if(src == dst){
//                     br = true;
//                 }
//             }
//         }
//     }

//     enum class GroundType
//     {
//         Air,
//         Stone,
//         Sand,
//         Source
//     };

//     std::vector<GroundType> cave;
//     const int width = (bottomRight.x - topLeft.x + 1);
//     const int height = (bottomRight.y - topLeft.y + 1);
//     cave.resize(width * height);

//     for(const auto& e : inputVecs)
//     {
//         cave[(e.y - topLeft.y) * width + (e.x - topLeft.x)] = GroundType::Stone;
//     }
//     const auto origin = Vec2i{500 - topLeft.x, 0};
//     cave[origin.x] = GroundType::Source;

//     const auto printCave = [&](){
//         std::cout << "\n";
//         for(int y = 0; y < height; y++)
//         {
//             for(int x = 0; x < width; x++)
//             {
//                 const auto t = cave[y * width + x];
//                 if(t == GroundType::Air)
//                 {
//                     std::cout << ".";
//                 }
//                 else if(t == GroundType::Stone)
//                 {
//                     std::cout << "#";
//                 }
//                 else if(t == GroundType::Sand)
//                 {
//                     std::cout << "O";
//                 }
//                 else
//                 {
//                     std::cout << "+";
//                 }
//             }
//             std::cout << "\n";
//         }
//     };

//     //printCave();

//     int sandRested = 0;

//     const auto notInBounds = [height, width](const Vec2i& v)->bool
//     {
//         return v.x < 0 || v.x > width || v.y < 0 || v.y > height;
//     };

//     //pour sand
//     while(true)
//     {
//         Vec2i newSand = origin;

//         while(true)
//         {
//             const auto down = newSand + Vec2i{0,1};
//             const auto left = newSand + Vec2i{-1,1};
//             const auto right = newSand + Vec2i{1,1};

//             if(!notInBounds(right) && cave[down.y * width + down.x] == GroundType::Air)
//             {
//                 newSand = down;
//             }
//             else if(!notInBounds(right) && cave[left.y * width + left.x] == GroundType::Air)
//             {
//                 newSand = left;
//             }
//             else if(!notInBounds(right) && cave[right.y * width + right.x] == GroundType::Air)
//             {
//                 newSand = right;
//             }
//             else
//             {
//                 if(newSand.y >= height)
//                 {
//                     //printCave();
//                     return sandRested;
//                 }else{
//                     sandRested++;
//                     cave[newSand.y * width + newSand.x] = GroundType::Sand;
//                     break;
//                 }
//             }
//         }
//     }


//     return 0;
// }

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;  
    }
};

struct vec2_hash
{
    template<typename T>
    std::size_t operator() (const Vector<T>& v) const
    {
        return std::hash<T>{}(v.x) ^ std::hash<T>{}(v.y);
    }
};

int day14_1() //redone because map > vector for part 2
{
    std::ifstream input("day14.txt");
    std::string line;
    enum class GroundType
    {
        Stone,
        Sand
    };
    
    std::unordered_map<std::pair<int, int>, GroundType, pair_hash> cave;

    const auto toVec = [](const std::string& str) -> std::pair<int, int>
    {
        const auto spl = split(str, ",");
        return {std::stoi(spl.at(0)), std::stoi(spl.at(1))};
    };

    std::pair<int, int> topLeft{INT_MAX, 0};
    std::pair<int, int> bottomRight{-INT_MAX, -INT_MAX};

    while(std::getline(input, line))
    {
        const auto coordList = split(line, " -> ");
        
        for(int i = 0; i < coordList.size() - 1; i++)
        {
            auto src = toVec(coordList[i]);
            const auto dst = toVec(coordList[i+1]);

            auto dir = std::pair<int, int>{dst.first - src.first, dst.second - src.second};
            if(dir.first != 0) dir.first /= std::abs(dir.first);
            if(dir.second != 0) dir.second /= std::abs(dir.second);
            
            bool br = false;
            while(true)
            {
                if(src.first < topLeft.first) topLeft.first = src.first;
                if(src.second < topLeft.second) topLeft.second = src.second;
                if(src.first > bottomRight.first) bottomRight.first = src.first;
                if(src.second > bottomRight.second) bottomRight.second = src.second;
                cave[src] = GroundType::Stone;
                src.first += dir.first;
                src.second += dir.second;

                if(br) break;
                if(src == dst){
                    br = true;
                }
            }
        }
    }

    const int width = (bottomRight.first - topLeft.first + 1);
    const int height = (bottomRight.second - topLeft.second + 1);
    const auto origin = std::pair<int, int>{500 , 0};
    int sandRested = 0;

    //pour sand
    while(true)
    {
        auto newSand = origin;

        while(true)
        {
            const auto down = std::pair<int, int>{newSand.first, newSand.second + 1};
            const auto left = std::pair<int, int>{newSand.first - 1, newSand.second + 1};
            const auto right = std::pair<int, int>{newSand.first + 1, newSand.second + 1};

            if(newSand.second >= height)
            {
                return sandRested;
            }

            if(!cave.contains(down))
            {
                newSand = down;
            }
            else if(!cave.contains(left))
            {
                newSand = left;
            }
            else if(!cave.contains(right))
            {
                newSand = right;
            }
            else
            {
                sandRested++;
                cave[newSand] = GroundType::Sand;
                break;
            }
        }
    }


    return 0;
}


int day14_2()
{
    std::ifstream input("day14.txt");
    std::string line;
    enum class GroundType
    {
        Stone,
        Sand
    };
    
    std::unordered_map<std::pair<int, int>, GroundType, pair_hash> cave;

    const auto toVec = [](const std::string& str) -> std::pair<int, int>
    {
        const auto spl = split(str, ",");
        return {std::stoi(spl.at(0)), std::stoi(spl.at(1))};
    };

    std::pair<int, int> topLeft{INT_MAX, 0};
    std::pair<int, int> bottomRight{-INT_MAX, -INT_MAX};

    while(std::getline(input, line))
    {
        const auto coordList = split(line, " -> ");
        
        for(int i = 0; i < coordList.size() - 1; i++)
        {
            auto src = toVec(coordList[i]);
            const auto dst = toVec(coordList[i+1]);

            auto dir = std::pair<int, int>{dst.first - src.first, dst.second - src.second};
            if(dir.first != 0) dir.first /= std::abs(dir.first);
            if(dir.second != 0) dir.second /= std::abs(dir.second);
            
            bool br = false;
            while(true)
            {
                if(src.first < topLeft.first) topLeft.first = src.first;
                if(src.second < topLeft.second) topLeft.second = src.second;
                if(src.first > bottomRight.first) bottomRight.first = src.first;
                if(src.second > bottomRight.second) bottomRight.second = src.second;
                cave[src] = GroundType::Stone;
                src.first += dir.first;
                src.second += dir.second;

                if(br) break;
                if(src == dst){
                    br = true;
                }
            }
        }
    }

    const int width = (bottomRight.first - topLeft.first + 1);
    const int height = (bottomRight.second - topLeft.second + 1) + 2;
    const auto origin = std::pair<int, int>{500 , 0};
    int sandRested = 0;

    const auto printCave = [&]()
    {
        std::cout << "\n";
        for(int i = 0; i < height; i++)
        {
            for(int j = -width; j < width; j++)
            {
                if(i == height - 1)
                {
                    std::cout << "=";
                    continue;
                }
                if(cave.contains({j+500, i}))
                {
                    std::cout << (cave[{j+500, i}] == GroundType::Sand ? 'O' : '#');
                }else{
                    std::cout << "-";
                }
            }
            std::cout << "\n";
        }
    };

    //pour sand
    while(true)
    {
        auto newSand = origin;

        while(true)
        {
            const auto down = std::pair<int, int>{newSand.first, newSand.second + 1};
            const auto left = std::pair<int, int>{newSand.first - 1, newSand.second + 1};
            const auto right = std::pair<int, int>{newSand.first + 1, newSand.second + 1};

            if(newSand.second == height - 1)
            {
               // sandRested++;
                cave[newSand] = GroundType::Sand;
                break;
            }

            if(!cave.contains(down))
            {
                newSand = down;
            }
            else if(!cave.contains(left))
            {
                newSand = left;
            }
            else if(!cave.contains(right))
            {
                newSand = right;
            }
            else
            {
                sandRested++;
                cave[newSand] = GroundType::Sand;
                //printCave();
                if(newSand == origin)
                {
                    //printCave();
                    return sandRested;
                }
                break;
            }
        }
    }


    return 0;
}

struct Sensor
{
    Sensor(int px, int py, int bx, int by) : position(px, py), nextBeacon(bx, by) {}
    void calculateDistance()
    {
        distance = position.manhattan(nextBeacon);
    }
    Vec2i position{};
    Vec2i nextBeacon{};
    int distance{};
};

std::vector<int> extractInts(const std::string& str)
{
    std::vector<int> result{};
    std::string temp;

    int i = 0; 
    while(i < str.size())
    {
        char c = str[i];
        if(std::isdigit(c) || c == '-')
        {
            do
            {
                temp = temp + c;
                c = str[++i];
            } while (std::isdigit(c));
            
            result.push_back(std::stoi(temp));
            temp.clear();
        }
        i++;
    }
    
    return result;
}

int day15_1()
{
    std::ifstream input("day15.txt");
    std::string line;
    std::vector<Sensor> sensors{};
    std::set<Vec2i> beacons{};

    while(std::getline(input, line))
    {
        const auto numbers = extractInts(line);
        sensors.emplace_back(numbers[0], numbers[1], numbers[2], numbers[3]);
        sensors.back().calculateDistance();
        beacons.insert(sensors.back().nextBeacon);
    }

    constexpr int checkRow = 2000000;
    std::set<Vec2i> row;

    for(const auto& s : sensors)
    {
        if(s.position.y < checkRow && s.position.y + s.distance < checkRow)
        {
            continue;
        }
        if(s.position.y > checkRow && s.position.y - s.distance > checkRow)
        {
            continue;
        }

        for(int x = -s.distance; x < s.distance; x++)
        {
            const auto pos = Vec2i{s.position.x + x, checkRow};
            if(s.position.manhattan(pos) <= s.distance)
            {
                if(!beacons.contains(pos))
                {
                    row.insert(pos);
                }
            }
        }
    }


    return row.size();
}


std::uint64_t day15_2() //warning: this is giga slow
{
    std::ifstream input("day15.txt");
    std::string line;
    std::vector<Sensor> sensors{};
    std::set<Vec2i> beacons{};

    while(std::getline(input, line))
    {
        const auto numbers = extractInts(line);
        sensors.emplace_back(numbers[0], numbers[1], numbers[2], numbers[3]);
        sensors.back().calculateDistance();
        beacons.insert(sensors.back().nextBeacon);
    }

    std::set<Vec2i> row;
    constexpr int searchArea = 4000000;

    //std::cout << "\n";
    for(int y = 0; y < searchArea; y++)
    {
        for(int x = 0; x < searchArea; x++)
        {
            int found = true;
            for(const auto& s : sensors)
            {
                if(s.position.manhattan(Vec2i{x,y}) <= s.distance)
                {
                    found = false;
                    break;
                }
            }
            if(found)
            {
                return std::uint64_t(x) * 4000000 + y;
            }
        }
        //std::cout << "\r" << std::setw(7) << y << "/" << searchArea;
    }
    //std::cout << std::endl;

    return row.size();

}

struct Vec3
{
    Vec3(int x, int y, int z) : x(x), y(y), z(z) {}
    int x{};
    int y{};
    int z{};

    friend bool operator< (const Vec3& lhs, const Vec3& rhs){ return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y) || (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z < rhs.z); } 
    bool operator== (const auto& other){ return x == other.x && y == other.y && z == other.z; }
    bool operator!= (const auto& other){ return !operator==(other); }
    Vec3 operator+ (const Vec3& r) const { return {x + r.x, y + r.y, z + r.z};} 
};

int day18_1()
{
    std::ifstream input("day18.txt");
    std::string line;
    std::set<Vec3> lava;
    int result = 0;

    while(std::getline(input, line))
    {
        const auto spl = split(line, ",");
        lava.insert(Vec3(std::stoi(spl.at(0)), std::stoi(spl.at(1)), std::stoi(spl.at(2))));
    }

    const std::vector<Vec3> sides = {{1,0,0},{-1,0,0},{0,1,0}, {0,-1,0},{0,0,1},{0,0,-1}};

    for(const auto& v : lava)
    {
        for(const auto& s : sides)
        {
            if(!lava.contains(v + s))
            {
                ++result;
            }
        }
    }

    return result;
}


int day18_2()
{


    return 0;
}

template<typename T>
struct Node
{
    T value{};
    std::size_t startPos{};
    std::shared_ptr<Node<T>> left = nullptr;
    std::shared_ptr<Node<T>> right = nullptr;
};

int day20_1()
{
    std::ifstream input("day20.txt");
    std::string line;
    auto root = std::make_shared<Node<int>>();
    std::shared_ptr<Node<int>> current = nullptr;
    std::vector<int> ops{};
    int c = 0;

    while(std::getline(input, line))
    {
        if(!current)
        {
            root->value = std::stoi(line);
            root->startPos = c++;
            ops.push_back(root->value);
            current = root;
        }
        else
        {
            auto node = std::make_shared<Node<int>>();
            node->value = std::stoi(line);
            ops.push_back(node->value);
            node->startPos = c++;
            node->left = current;
            current->right = node;
            current = node;
        }
    }
    root->left = current;
    current->right = root;

    const auto swapNode = [](std::shared_ptr<Node<int>> n1, std::shared_ptr<Node<int>> n2)
    {
        int tVal = n1->value;
        std::size_t tPos = n1->startPos;

        n1->value = n2->value;
        n1->startPos = n2->startPos;

        n2->value = tVal;
        n2->startPos = tPos;
    };

    const auto printLine = [&]()
    {
        std::cout<<"\n";
        auto t = root;
        do
        {
            std::cout << t->value << " ";
            t = t->right;
        } while (t != root);
    };
    //printLine();

    for(int i = 0; i < ops.size(); i++)
    {
        auto s = root;
        while(s->startPos != i){ s = s->right; }
        for(int j = 0; j < std::abs(s->value) % (ops.size() - 1); j++)
        {
            if(s->value < 0)
            {
                swapNode(s, s->left);
                s = s->left;
            }
            if(s->value > 0)
            {
                swapNode(s, s->right);
                s = s->right;
            }
        }
        //printLine();
    }

    //find start again
    auto s = root;
    while(s->value != 0){ s = s->right; }
    root = s;

   // printLine();

    int sum = 0;
    auto l = root;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 1000; j++)
        {
            l = l->right;
        }
        sum += l->value;
    }

    return sum;
}


std::int64_t day20_2()
{
    std::ifstream input("day20.txt");
    std::string line;
    auto root = std::make_shared<Node<std::int64_t>>();
    std::shared_ptr<Node<std::int64_t>> current = nullptr;
    std::vector<int> ops{};
    int c = 0;

    while(std::getline(input, line))
    {
        if(!current)
        {
            root->value = (std::int64_t)(std::stoi(line)) * 811589153;
            root->startPos = c++;
            ops.push_back(root->value);
            current = root;
        }
        else
        {
            auto node = std::make_shared<Node<std::int64_t>>();
            node->value = (std::int64_t)(std::stoi(line)) * 811589153;
            ops.push_back(node->value);
            node->startPos = c++;
            node->left = current;
            current->right = node;
            current = node;
        }
    }
    root->left = current;
    current->right = root;

    const auto swapNode = [](std::shared_ptr<Node<std::int64_t>> n1, std::shared_ptr<Node<std::int64_t>> n2)
    {
        std::int64_t tVal = n1->value;
        std::size_t tPos = n1->startPos;

        n1->value = n2->value;
        n1->startPos = n2->startPos;

        n2->value = tVal;
        n2->startPos = tPos;
    };

    const auto printLine = [&]()
    {
        std::cout<<"\n";
        auto t = root;
        do
        {
            std::cout << t->value << " ";
            t = t->right;
        } while (t != root);
    };

    //printLine();

    for(int x = 0; x < 10; x++)
    for(int i = 0; i < ops.size(); i++)
    {
        auto s = root;
        while(s->startPos != i){ s = s->right; }
        for(int j = 0; j < std::abs(s->value) % (ops.size() - 1); j++)
        {
            if(s->value < 0)
            {
                swapNode(s, s->left);
                s = s->left;
            }
            if(s->value > 0)
            {
                swapNode(s, s->right);
                s = s->right;
            }
        }
        //printLine();
    }

    //find start again
    auto s = root;
    while(s->value != 0){ s = s->right; }
    root = s;

    //printLine();

    std::int64_t sum = 0;
    auto l = root;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 1000; j++)
        {
            l = l->right;
        }
        sum += l->value;
    }

    return sum;
}

bool isNumber(std::string_view str)
{
    for(const auto c : str)
    {
        if(!std::isdigit(c))
        {
            return false;
        }
    }
    return true;
}

 std::int64_t day21_1()
{
    std::ifstream input("day21.txt");
    std::string line;
    std::unordered_map<std::string, std::variant<std::string, std::int64_t>> monkeys;

    while(std::getline(input, line))
    {
        const auto spl = split(line, ": ");
        if(isNumber(spl.at(1)))
        {
            monkeys[spl.at(0)] = std::stoi(spl.at(1));
        }
        else
        {
            monkeys[spl.at(0)] = spl.at(1);
        }
    }
    
                                                //recursive lambda trick
    const auto solve = [&](const std::string& m, auto&& solve)-> std::int64_t
    {
        if(monkeys[m].index() == 1)
        {
            return std::get<std::int64_t>(monkeys[m]);
        }else{
            const auto instr = split(std::get<std::string>(monkeys[m]), " ");
            if(instr.at(1) == "+")
            {
                return solve(instr[0], solve) + solve(instr[2], solve);
            }
            else if(instr.at(1) == "-")
            {
                return solve(instr[0], solve) - solve(instr[2], solve);
            }
            else if(instr.at(1) == "*")
            {
                return solve(instr[0], solve) * solve(instr[2], solve);
            }
            else
            {
                return solve(instr[0], solve) / solve(instr[2], solve);
            }
        }
        return 0;
    };

    return solve("root", solve);
}


int day21_2()
{

    return 0;
}


int day22_1()
{
    std::ifstream input("day22.txt");
    std::string line;
    std::unordered_map<Vec2i, bool, vec2_hash> map;
    std::vector<std::variant<int, std::string>> instr;
    Vec2i pos{};
    const std::vector<Vec2i> directions{{1,0},{0,1},{-1,0},{0,-1}};
    int dirIdx = 0;
    Vec2i mapDim{};

    int l = 0;
    while(std::getline(input, line))
    {
        if(line.empty())
        {
            std::getline(input, line);
            std::size_t startIdx = 0;
            for(std::size_t i = 0; i < line.size(); i++)
            {
                if(!std::isdigit(line[i]))
                {
                    instr.push_back(std::stoi(line.substr(startIdx, i - startIdx)));
                    instr.push_back(std::string{line[i]});
                    startIdx = i+1;
                }
            }
            instr.push_back(std::stoi(line.substr(startIdx, line.size() - startIdx)));
            break;
        }

        for(int x = 0; x < line.size(); x++)
        {
            const auto c = line.at(x);
            if(c != ' ')
            {
                static bool f = false;
                if(!f){pos = {x,l}; f = true;}
                mapDim = Vec2i{std::max(mapDim.x, x), std::max(mapDim.y, l)};
                map[Vec2i{x, l}] = c == '#';
            }
        }

        l++;
    }

    for(const auto c : instr)
    {
        if(c.index() == 1)
        {
            const auto d = std::get<std::string>(c);
            if(d == "R")
            {
                dirIdx = (dirIdx + 1) % directions.size();
            }
            else
            {
                dirIdx = dirIdx - 1;
                if(dirIdx < 0) dirIdx = directions.size();
            }
        }
        else
        {
            for(int i = 0; i < std::get<int>(c); i++)
            {
                //next tile
                Vec2i npos = pos;
                do
                {
                    npos = npos + directions[dirIdx];
                    npos.x = npos.x % mapDim.x;
                    npos.y = npos.y % mapDim.y;
                    if(npos.x < 0) npos.x = mapDim.x - 1;
                    if(npos.y < 0) npos.y = mapDim.y - 1;
                } while(!map.contains(npos));
                if(!map[npos])
                {
                    pos = npos;
                    //std::cout << "--> " << pos << "\n";
                }
            }
        }
    }

    return 1000 * (pos.y+1) + 4 * (pos.x+1) + dirIdx;
}

int main()
{
    std::ios_base::sync_with_stdio(false); 
    // std::cout << "Day 1_1: " << day1_1() << "\n";
    // std::cout << "Day 1_2: " << day1_2() << "\n";
    // std::cout << "Day 2_1: " << day2_1() << "\n";
    // std::cout << "Day 2_2: " << day2_2() << "\n";
    // std::cout << "Day 3_1: " << day3_1() << "\n";
    // std::cout << "Day 3_2: " << day3_2() << "\n";
    // std::cout << "Day 4_1: " << day4_1() << "\n";
    // std::cout << "Day 4_2: " << day4_2() << "\n";
    // std::cout << "Day 5_1: " << day5_1() << "\n";
    // std::cout << "Day 5_2: " << day5_2() << "\n";
    // std::cout << "Day 6_1: " << day6_1() << "\n";
    // std::cout << "Day 6_2: " << day6_2() << "\n";
    // std::cout << "Day 7_1: " << day7_1() << "\n";
    // std::cout << "Day 7_2: " << day7_2() << "\n";
    // std::cout << "Day 8_1: " << day8_1() << "\n";
    // std::cout << "Day 8_2: " << day8_2() << "\n";
    // std::cout << "Day 9_1: " << day9_1() << "\n";
    // std::cout << "Day 9_2: " << day9_2() << "\n";
    // std::cout << "Day 10_1: " << day10_1() << "\n";
    // std::cout << "Day 10_2: "; day10_2(); std::cout << "\n";
    // std::cout << "Day 11_1: " << day11_1() << "\n";
    // std::cout << "Day 11_2: " << day11_2() << "\n";
    // std::cout << "Day 12_1: " << day12_1() << "\n";
    // std::cout << "Day 12_2: " << day12_2() << "\n";
    // std::cout << "Day 13_1: " << day13_1() << "\n";
    // std::cout << "Day 13_2: " << day13_2() << "\n";
    // std::cout << "Day 14_1: " << day14_1() << "\n";
    // std::cout << "Day 14_2: " << day14_2() << "\n";
    // std::cout << "Day 15_1: " << day15_1() << "\n";
    // std::cout << "Day 15_2: " << day15_2() << "\n"; //extremely slow
    // std::cout << "Day 18_1: " << day18_1() << "\n";
    // std::cout << "Day 18_2: " << day18_2() << "\n"; 
    // std::cout << "Day 20_1: " << day20_1() << "\n";
    // std::cout << "Day 20_2: " << day20_2() << "\n"; 
    std::cout << "Day 21_1: " << day21_1() << "\n";
    std::cout << "Day 21_2: " << day21_2() << "\n"; 
    std::cout << "Day 22_1: " << day22_1() << "\n"; 
}