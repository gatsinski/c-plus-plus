#include <limits>
#include <string>


bool validateName(std::string name)
{
    if(name.length() == 0)
        return false;

    for(int i = 0; i < name.length(); i++)
        if(name[i] >= '0' && name[i] <= '9') 
            return false;

    return true;
}


bool validateGrade(double grade)
{
    if (grade < 2.0 || grade > 6.0)
        return false;
    return true;
}