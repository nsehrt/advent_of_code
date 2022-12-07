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



int main()
{
    std::cout << "Day 1_1: " << day1_1() << "\n";
    std::cout << "Day 1_2: " << day1_2() << "\n";
    std::cout << "Day 2_1: " << day2_1() << "\n";
    std::cout << "Day 2_2: " << day2_2() << "\n";
    std::cout << "Day 3_1: " << day3_1() << "\n";
    std::cout << "Day 3_2: " << day3_2() << "\n";
    std::cout << "Day 4_1: " << day4_1() << "\n";
    std::cout << "Day 4_2: " << day4_2() << "\n";
    std::cout << "Day 5_1: " << day5_1() << "\n";
    std::cout << "Day 5_2: " << day5_2() << "\n";
    std::cout << "Day 6_1: " << day6_1() << "\n";
    std::cout << "Day 6_2: " << day6_2() << "\n";
    std::cout << "Day 7_1: " << day7_1() << "\n";
    std::cout << "Day 7_2: " << day7_2() << "\n";
}