#include <bits/stdc++.h>
using namespace std;

enum DATA_TYPE
{
    INT,
    STRING,
    FLOAT,
    CHAR
};

class Employee
{
    int empid;
    string name = "";
    double salary;
    string dept = "";
    int age;

public:
    static int counter;
    static unordered_map<int, DATA_TYPE> DATA_MEMBERS;
    Employee() {}
    Employee(int id, string name, double salary, string dept, int age)
    {
        // vector<void *> fields = {&id, &name, &salary, &dept};
        this->empid = id;
        this->name = name;
        this->salary = ceil(salary*100.0)/100.0;
        this->dept = dept;
        this->age = age;
    }
    Employee(string &s)
    {
        stringstream ss(s);
        vector<string> vec;
        while (ss.good())
        {
            string sub;
            getline(ss, sub, ',');
            vec.push_back(sub);
        }
        this->empid = stoi(vec[0]);
        this->name = vec[1];
        this->salary = ceil(stod(vec[2])*100.0)/100.0;
        this->dept = vec[3];
        this->age = stoi(vec[4]);
    }
    void setEmpl()
    {
        this->empid = counter++;
        cout << "Enter emp name: ";
        getline(cin, this->name);
        cout << "Enter salary: ";
        cin >> this->salary;
        cout << "Enter dept: ";
        cin.ignore();
        getline(cin, this->dept);
        cout << "Enter age: ";
        cin >> this->age;
    }
    int getEmpId()
    {
        return this->empid;
    }
    string getEmpName()
    {
        return this->name;
    }
    double getSalary()
    {
        return this->salary;
    }
    string getEmpDept()
    {
        return this->dept;
    }
    int getEmpAge()
    {
        return this->age;
    }
    void getRows()
    {
        cout << "\t| "
            <<left <<setw(5) << this->empid <<" | "
            << left << setw(16) <<this->name <<" | "
            << left << setw(16) << fixed << setprecision(2)<<this->salary<<" | "
            << left << setw(20) << this->dept << " | "
            << left << setw(5) << this->age << " |\n";
        // cout << "\t| " << this->empid << "\t| " << this->name << "  \t| ";cout << std::fixed << std::setprecision(2)<<(this->salary) << "  \t| " << this->dept << "  \t| "<<this->age<<"  \t|\n";
    }
    string saveUtil()
    {
        return to_string(empid) + "," + name + "," + to_string(salary) + "," + dept + "," + to_string(age)+"\n";
    }
    int getIntField(int field_id)
    {
        switch (field_id)
        {
        case 1:
            return this->getEmpId();
        case 5:
            return this->getEmpAge();
        default:
            throw invalid_argument("Invalid syntax.");
        }
    }
    string getStringField(int field_id)
    {
        switch (field_id)
        {
        case 2:
            return this->getEmpName();
        case 4:
            return this->getEmpDept();
        
        default:
            throw invalid_argument("Invalid syntax.");
        }
    }
    double getFloatField(int field_id)
    {
        switch (field_id)
        {
        case 3:
            return this->getSalary();
        default:
            throw invalid_argument("Invalid syntax.");
        }
    }
};
int Employee::counter = 1;
unordered_map<int, DATA_TYPE> Employee::DATA_MEMBERS =
    {{1, INT},
     {2, STRING},
     {3, FLOAT},
     {4, STRING},
     {5, INT}};

class SearchHandler
{
    map<int, Employee> orig_map;
    map<int, Employee> output_map;

public:
    SearchHandler(map<int, Employee> &mp)
    {
        map<int, Employee>::iterator it;
        for (it = mp.begin(); it != mp.end(); it++)
        {
            orig_map[it->first] = (it->second);
        }
    }
    map<int, Employee> int_field_filter(int field_index)
    {
        output_map.clear();
        cout << "\toptions:\n";
        cout << "\t1. < \n";
        cout << "\t2. > \n";
        cout << "\t3. == \n";
        cout << "\t4. <= \n";
        cout << "\t5. >= \n";
        int compOpt;
        cin >> compOpt;

        cout << "Enter number to search: ";
        int number;
        cin >> number;
        for (auto it : orig_map)
        {
            switch (compOpt)
            {
            case 1:
                if (it.second.getIntField(field_index) < number)
                    output_map[it.first] = it.second;
                break;
            case 2:
                if (it.second.getIntField(field_index) > number)
                    output_map[it.first] = it.second;
                break;
            case 3:
                if (it.second.getIntField(field_index) == number)
                    output_map[it.first] = it.second;
                break;
            case 4:
                if (it.second.getIntField(field_index) <= number)
                    output_map[it.first] = it.second;
                break;
            case 5:
                if (it.second.getIntField(field_index) >= number)
                    output_map[it.first] = it.second;
                break;
            default:
                break;
            }
        }
        return output_map;
    }
    map<int, Employee> string_field_filter(int field_index)
    {
        output_map.clear();
        cout << "\tOptions: \n";
        cout << "\t1. Starts with: \n";
        cout << "\t2. Ends with: \n";
        cout << "\t3. Contains: \n";
        int option;
        cin >> option;
        cout << "\n Enter the string to search: ";
        string s;
        cin >> s;
        int l = s.length();

        for (auto it : orig_map)
        {
            string sn = it.second.getStringField(field_index);
            int ln = sn.length();

            switch (option)
            {
            case 1:
                if (sn.substr(0, l) == s)
                    output_map[it.first] = it.second;
                break;

            case 2:
                if (sn.substr(ln - l, l) == s)
                    output_map[it.first] = it.second;
                break;

            case 3:
                for (int i = 0; i <= ln - l && ln >= l; i++)
                {
                    if (sn.substr(i, l) == s)
                    {
                        output_map[it.first] = it.second;
                        break;
                    }
                }
                break;
            default:
                break;
            }
        }

        return output_map;
    }
    map<int, Employee> float_field_filter(int field_index)
    {
        output_map.clear();
        cout << "\toptions:\n";
        cout << "\t1. < \n";
        cout << "\t2. > \n";
        cout << "\t3. == \n";
        cout << "\t4. <= \n";
        cout << "\t5. >= \n";
        int compOpt;
        cin >> compOpt;

        cout << "Enter float number to search: ";
        double floatNumber;
        cin >> floatNumber;
        for (auto it : orig_map)
        {
            switch (compOpt)
            {
            case 1:
                if (it.second.getFloatField(field_index) < floatNumber)
                    output_map[it.first] = it.second;
                break;
            case 2:
                if (it.second.getFloatField(field_index) > floatNumber)
                    output_map[it.first] = it.second;
                break;
            case 3:
                if (it.second.getFloatField(field_index) == floatNumber)
                    output_map[it.first] = it.second;
                break;
            case 4:
                if (it.second.getFloatField(field_index) <= floatNumber)
                    output_map[it.first] = it.second;
                break;
            case 5:
                if (it.second.getFloatField(field_index) >= floatNumber)
                    output_map[it.first] = it.second;
                break;
            default:
                break;
            }
        }

        return output_map;
    }
    map<int, Employee> union_operation(map<int, Employee> mp1, map<int, Employee> mp2)
    {
        output_map.clear();
        for(auto it: mp1)
        {
            output_map[it.first] = it.second;
        }
        for(auto it: mp2)
        {
            output_map[it.first] = it.second;
        }

        return output_map;
    }
    map<int, Employee> intersection_operation(map<int, Employee> mp1, map<int, Employee> mp2)
    {
        output_map.clear();

        for (auto it : mp2)
        {
            if (mp1.find(it.first) != mp1.end()) // if exists in both
                output_map[it.first] = it.second;
        }
        return output_map;
    }
    map<int, Employee> not_operation(map<int, Employee> mp2)
    {
        map<int, Employee> mp1(orig_map);
        for (auto it : mp2)
        {
            if (mp1.find(it.first) != mp1.end())
                mp1.erase(it.first);
        }
        return mp1;
    }
};

void save(map<int, Employee> &mp)
{
    ofstream myfile("myfile.dat");
    map<int, Employee>::iterator it;
    for (it = mp.begin(); it != mp.end(); it++)
    {
        Employee e = it->second;

        myfile << e.saveUtil();
    }
    cout << "saved..\n";
}

map<int,Employee> searchEmp(map<int, Employee> &mp)
{
    SearchHandler searchObj(mp);
    map<int, Employee> return_map;
    int inp = 0, opt = 0;

    cout << "\tSearch by which field: \n";
    cout << "\t1. By empid\n";
    cout << "\t2. By name\n";
    cout << "\t3. By salary\n";
    cout << "\t4. By Department\n";
    cout << "\t5. By age\n";
    cin >> inp;
    DATA_TYPE field_type = Employee::DATA_MEMBERS[inp];     // returns int for inp=1 or 5, float for inp=2

    if (field_type == INT)
        return_map = searchObj.int_field_filter(inp);

    else if (field_type == STRING)
        return_map = searchObj.string_field_filter(inp);

    else if (field_type == FLOAT)
        return_map = searchObj.float_field_filter(inp);

    return return_map ;
}

void displayEmp(map<int, Employee> &mp)
{
    if(mp.size()==0)
        cout<<"\n\t-------------No records-------------\n";
    else
    {
        cout <<"\t______________________________________________________________________________\n";
        cout << "\t| "
            <<left <<setw(5) << "EMPID" <<" | "
            << left << setw(16) << "NAME" <<" | "
            << left << setw(16) << "SALARY" << " | "
            << left << setw(20) << "DEPT" << " | "
            << left << setw(5) << "AGE" << " |\n";
        cout<<"\t``````````````````````````````````````````````````````````````````````````````\n";
        for(auto it: mp)
            it.second.getRows();
        cout<<"\t``````````````````````````````````````````````````````````````````````````````\n";
    }
}
int main()
{
    Employee::counter = 1;
    bool isChange = 0;
    char input = '0';
    map<int, Employee> mp;
    cout << "Loading db-dat myfile..." << endl;
    ifstream myfile("myfile.dat");
    if (myfile.is_open())
    {
        string s;
        while (getline(myfile, s))
        {
            Employee e(s);
            mp[e.getEmpId()] = e;
            Employee::counter++;
        }
        cout << "Loaded.";
    }
    else
        cout << "No file exists.";

    myfile.close();

    while (input != '6')
    {
        cout << "\nEmployee system\n";
        cout << "Choose:\n";
        cout << "1. Add employee" << endl;
        cout << "2. Remove employee" << endl;
        cout << "3. Dislay records from memory" << endl;
        cout << "4. Search an employee" << endl;
        cout << "5. Save changes ? " << endl;
        cout << "6. Exit" << endl;
        cin >> input;
        cin.ignore();
        if (input == '1')
        {
            isChange = 1;
            Employee e;
            e.setEmpl();
            mp[e.getEmpId()] = e;
            cout << "Employee inserted\n";

            displayEmp(mp);
        }
        else if (input == '2')
        {
            isChange = 1;
            int id;
            cout << "Enter the emp no. to delete record: ";
            cin >> id;
            cout << "entered: " << id << endl;
            if (mp.find(id) != mp.end())
            {
                mp.erase(id);
                cout << "\trecord deleted\n";
            }
            else
                cout << "\trecord not found\n";

            displayEmp(mp);
        }
        else if (input == '3')
        {
            displayEmp(mp);
        }
        else if (input == '4')
        {
            SearchHandler searchHandlerObj(mp);
            map<int, Employee> result_map;
            result_map = searchEmp(mp);
            int combineOpt=0;
            do
            {
                cout<<"\tEnter further query: \n\n";
                cout<<"\t1. &&\t";
                cout<<"\t2. ||\t";
                cout<<"\t3. !\t";
                cout<<"\t4. End Query\t\n\n";
                cout<<"\tenter option:   ";
                cin>>combineOpt;
                cout<<"\n";
                
                if(combineOpt==2)
                    result_map = searchHandlerObj.union_operation(result_map, searchEmp(mp));
                else if(combineOpt==1)
                    result_map = searchHandlerObj.intersection_operation(result_map, searchEmp(mp));
                else if(combineOpt==3)
                    result_map = searchHandlerObj.not_operation(result_map);
                else if(combineOpt==4)
                    break;
                else
                    cout<<"\n---Enter valid input----\n";

            } while (combineOpt!=4);

            // show final
            displayEmp(result_map);
        }

        else if (input == '5')
            save(mp);

        else if (input == '6')
        {
            // check if map is in sync with db
            if (isChange)
            {
                cout << "Do you want to save changes ? (y/n)";
                char c;
                cin >> c;
                if (c == 'y' || c == 'Y')
                    save(mp);
            }
            break;
        }
        else
            cout << "\tInvalid Choice !!, Enter again";
    }

    return 0;
}
/*
eirnvirnv

uibwvupug[uwge
*/