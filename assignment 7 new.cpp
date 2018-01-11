

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int ARRAY_SIZE = 51;
//declare master arrays
string ofNames[ARRAY_SIZE];
bool isStaff[ARRAY_SIZE];

// function prototypes - work out how to convert boolean to a string

void park_current_read(ifstream & fin1);
void park_remove_read(ifstream & fin1);
void park_add_read(ifstream & fin1);
void print_function();
void park_clear(string RemoveName);
int findFreeSpace(bool addStaff);
void park_assign(string AddName, bool AddStaff);
void optimize();

int main()
{
    //open file and check
    std::ifstream fin1, fin2, fin3;
    
    fin1.open("parking_current.txt");
    fin2.open("parking_remove.txt");
    fin3.open("parking_add.txt");
    
    if (!fin1 || !fin2 || !fin3)
    {
        cout << "File not found" << endl;
        return EXIT_FAILURE;
    }
    
    // use the read fn
    park_current_read(fin1);
    
    //declare arrays for remove people
    park_remove_read(fin2);
    park_add_read(fin3);
    print_function();
    optimize();
}


void park_current_read(ifstream & fin1)
{
    int parkingNo = 0;
    string name;
    bool status = 0;
    while (fin1 >> status >> name >> parkingNo)
    {
        //store read-in info into the arrays
        ofNames[parkingNo] = name;
        isStaff[parkingNo] = status;
    }
    fin1.close();
}

void print_function()
{
    
    for (int i=1; i < 51; i++)
        
        cout << i << " " << ofNames[i] << " " << isStaff[i] << endl;
    
}

void park_remove_read(ifstream & fin2)
{
    fin2.open("parking_remove.txt");
    string RemoveName;
    bool status = 0;
    int i = 0;
    while (fin2 >> status >> RemoveName)
    {
        //store read-in info into the arrays
        park_clear(RemoveName);
        i++;
    }
    fin2.close();
}

void park_add_read(ifstream & fin3)
{
    fin3.open("parking_add.txt");
    string AddName;
    bool AddStaff;
    int i = 0;
    while (fin3 >> AddStaff >> AddName)
    {
        park_assign(AddName, AddStaff);
        i++;
    }
    fin3.close();
}

void park_clear(string RemoveName)
{
    for(int y = 0; y < ARRAY_SIZE; y++)
        if(ofNames[y] == RemoveName)
        {
                ofNames[y] = "";
                isStaff[y] = 0;
        }
}

void park_assign(string AddName, bool AddStaff)
{
    if (findFreeSpace(AddStaff) == 99)
    {
        cout << "No free space in the lot." << endl;
    }
    else
    {
        ofNames[findFreeSpace(AddStaff)] = AddName;
        isStaff[findFreeSpace(AddStaff)] = AddStaff;
    }
    
    }


int findFreeSpace(bool status)
{
    if(status==1)
    {
        for(int i=1;i<ARRAY_SIZE;i++)
        {
            
            if(ofNames[i]<" ")
            {
                cout << "First empty space: " << i<<endl;
                return i;
            }
            else if(ofNames[i]==" ")
            {
                cout<< "The parking lot if full"<<endl;
                return 99;
            }
        }
    }
    else
    {
        for(int i=26;i<ARRAY_SIZE;i++)
        {
            if(ofNames[i]<" ")
            {
                cout << "First empty space: " << i<<endl;
                return i;
            }
            else if(ofNames[i]==" ")
            {
                cout<< "The parking lot if full"<<endl;
                return 99;
            }
        }
    }
    return 99;
}

void optimize()
{
for(int i=26;i<ARRAY_SIZE;i++)
	{
		if(isStaff[i]==1)
		{
		park_clear(ofNames[i]);
		park_assign(ofNames[i], 1);
		}
	}
	
}
