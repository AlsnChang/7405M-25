#include "autonSelector.h"
#include "intake.h"
#include "pros/distance.hpp"
#include "pros/motors.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "lemlib/api.hpp"
#include <sys/_intsup.h>

pros::Distance frontD{2}, backD{8}, leftD{15}, rightD{10};

pros::Distance* getSensor(int val)
{
    if (val == 0) return &frontD;
    if (val == 1) return &backD;
    if (val == 2) return &leftD;
    if (val == 3) return &rightD;
    return nullptr;
}

 
std::array<pros::Distance*, 2> sortDistances() {
    std::array<std::pair<int, pros::Distance*>, 4> sensors = {{
        {frontD.get(), &frontD},
        {backD.get(),  &backD},
        {leftD.get(),  &leftD},
        {rightD.get(), &rightD}
    }};

    std::sort(sensors.begin(), sensors.end(),
        [](auto& a, auto& b) {
            return a.first < b.first;
        });

    return {sensors[0].second, sensors[1].second};
}


// std::array<pros::Distance*, 2> sortDistances()
// {
//     //values of distance sensors (yes there probably is a better way but whateverrrr)
//     std::array<int, 4> compare = {frontD.get(), backD.get(), leftD.get(), rightD.get()};
//     std::array<int, 4> distances = {frontD.get(), backD.get(), leftD.get(), rightD.get()};

//     //sort the values of the distance sensors greatest -> least
//     std::array<pros::Distance*, 2> closest = {nullptr, nullptr};
//     int n = distances.size();
//     std::sort(distances.begin(), distances.begin() + n);

//     //get the distance sensors with the lowest values (yes yes I probably could have done this better too)
//     for (int i = 0; i < n; i++)
//     {
//         int counter = 0;
//         if (compare[i] == distances[3] || compare[i] == distances[2])
//         {
//             closest[counter] = getSensor(i);
//             counter++;
//         }
//     }

//     return closest;
// }

//expected values in mm
//1 foot = around 300 mm
void distanceReset(double front, double side)
{
    //there's this cool thingamajingie that java should totally have too!! I love auto!
    auto sensors = sortDistances();
    //we're gonna assume that we always put front value first which probably isn't true but oh welll.
    //but like lowkey think about it, it's always gonna be front sensor right cuz we do it in the corners and that's where match loaders are
    if (!sensors[0] || !sensors[1]) {
        return; // safety check
    }

    double firstSensor  = sensors[0]->get();
    double secondSensor = sensors[1]->get(); //always a side sensor

    //if for some reason first sensor isn't front sensor, swap em using unicorn slaves ✨
    if ((std::abs(secondSensor-front)) < std::abs(firstSensor-front)) 
    {
        double store = secondSensor;
        secondSensor = firstSensor;
        firstSensor = store;
    }
    //ok so basically now front = first sensor and side = second sensor
    double frontError = front - firstSensor;
    double sideError = side - secondSensor;
    //I honestly have no clue what I'm doing rn btw so this is probably wrong :)
    chassis.resetLocalPosition();
    frontError /= 25.4; //converting from mm to inches
    sideError /= 25.4;

    //this seems way too simple to be right but uhhh later me problem?
    chassis.setPose({(float)frontError, (float)sideError, (float)imu.get_heading()});
}