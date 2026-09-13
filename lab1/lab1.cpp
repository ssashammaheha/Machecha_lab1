
#include <iostream>
#include <string>

struct Pipe
{
    std::string name;
    double length;
    int diameter;
    bool inRepair;
};

struct CompressorStation
{
    std::string name;
    int workshopCount;
    int workingWorkshops;
    int stationClass;
};

void showPipe(Pipe pipe)
{
    std::cout << "name: " << pipe.name << std::endl;

    std::cout << "lenght: "
        << pipe.length
        << " km"
        << std::endl;

    std::cout << "diametr: "
        << pipe.diameter
        << " mm"
        << std::endl;

    std::cout << "is repair: ";

    if (pipe.inRepair)
    {
        std::cout << "Да";
    }
    else
    {
        std::cout << "Нет";
    }
}


int main()
{
    Pipe pipe1;
    pipe1.name = "truba 1";
    pipe1.length = 15.5;
    pipe1.diameter = 520;
    pipe1.inRepair = false;


    showPipe(pipe1);
    
}
