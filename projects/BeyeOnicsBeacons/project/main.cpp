

#include "transmissionField.h"
#include "linker.hpp"
#include <optional>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

inline constexpr int CONNECTIVITY_RADIUS_GRANULARITY = 10;
inline constexpr int DEFAULT_CONNECTIVITY_RADIUS = 100;
inline constexpr int MIN_CONNECTIVITY_RADIUS = 10;
inline constexpr int MAX_CONNECTIVITY_RADIUS = 1000;

// a struct for representing optional user input
// for a certain frame
struct UserInput
{
    std::optional<cv::Point2d> mouse_press_pos;
    std::optional<int>         mouse_wheel_delta;
};

void Run()
{ 
    UserInput lastUserInput{};
    
    const auto GREEN = cv::Scalar(0, 255, 0);
    const auto RED = cv::Scalar(0, 0, 255);
    const auto BLUE = cv::Scalar(255, 0, 0);
    const auto CANVAS_WIDTH = 1920;
    const auto CANVAS_HEIGHT = 1024;

    auto currentConnectivityRadius = DEFAULT_CONNECTIVITY_RADIUS;

    cv::namedWindow("canvas", 1);
    cv::setMouseCallback("canvas", [](int event, int x, int y, int flags, void* userdata)
    {
        
        if (event == cv::EVENT_LBUTTONDOWN)
        {
            auto userData = static_cast<UserInput*>(userdata);
            userData->mouse_press_pos = cv::Point2d{ static_cast<double>(x), static_cast<double>(y) };
        }
        //std::cout << "event" << event << std::endl;
        if (event == cv::EVENT_MOUSEWHEEL)
        {
            auto userData = static_cast<UserInput*>(userdata);

            userData->mouse_wheel_delta = cv::getMouseWheelDelta(flags);
        }
    }, &lastUserInput);

    cv::Mat canvas = cv::Mat::zeros(CANVAS_HEIGHT, CANVAS_WIDTH, CV_8UC3);

    std::optional<cv::Point2d> lastPoint{};
    TransmissionField transmissionField{};
    bool showTransmissionPath(true);

    while (true)
    {
        // clear canvas
        canvas.setTo(0);

        // TODO::YARON - local vars camel
        // TODO: handle user input
        if (lastUserInput.mouse_press_pos) // TODO::YARON - Indent
        {
            lastPoint = *lastUserInput.mouse_press_pos;
            transmissionField.ProcessAndAddNewBeacon(lastPoint, currentConnectivityRadius);
            lastUserInput.mouse_press_pos.reset();
        }
        if (lastUserInput.mouse_wheel_delta)
        {
            static constexpr int MOUSE_WHEEL_DEFAULT_GRANULARITY = 120; 
            auto radiusDelta = (*lastUserInput.mouse_wheel_delta / MOUSE_WHEEL_DEFAULT_GRANULARITY) * CONNECTIVITY_RADIUS_GRANULARITY;
            
            currentConnectivityRadius = std::clamp(
                currentConnectivityRadius + radiusDelta,
                MIN_CONNECTIVITY_RADIUS, 
                MAX_CONNECTIVITY_RADIUS
            );

            lastUserInput.mouse_wheel_delta.reset();
        }

        cv::putText(canvas, "press 'c' to clear, 't' to toggle connectivity radius, escape to exit", cv::Point(20, 50), cv::FONT_HERSHEY_SIMPLEX, 1.3, GREEN, 2);
        cv::putText(canvas, cv::format("current connectivity radius = %d", currentConnectivityRadius), cv::Point(20, 100), cv::FONT_HERSHEY_SIMPLEX, 1.3, GREEN, 2);

        // TODO draw shortest path
        
        // Draw all saved beacons
        if (!transmissionField.IsEmpty())
        {
            Beacon* currentBeacon(transmissionField.GetFirstBeacon());
            while (nullptr != currentBeacon)
            {
              std::optional<cv::Point2d>  currentCenterPoint = currentBeacon->GetCenterPoint();
              float                       currentConnectivityRadius = currentBeacon->GetConnectivityRadius();

              cv::ellipse(canvas,
                cv::Point(currentCenterPoint->x, currentCenterPoint->y),
                cv::Size((int)5, (int)5), 0.0,
                0, 360,
                GREEN, -1
              );

              cv::ellipse(canvas,
                cv::Point((int)currentCenterPoint->x, (int)currentCenterPoint->y),
                cv::Size((int)currentConnectivityRadius, (int)currentConnectivityRadius),
                0.0, 0, 360, BLUE, 3
              );

              currentBeacon = transmissionField.GetNextBeacon(currentBeacon->GetID());
            } 
        }

        // Draw last temporary beacon
        if (lastPoint) // TODO::YARON - Multiplication
        {
            cv::ellipse(canvas,
                cv::Point((int)lastPoint->x, (int)lastPoint->y),
                cv::Size((int)5, (int)5), 0.0,
                0, 360,
                GREEN, -1
            );

            cv::ellipse(canvas,
                cv::Point((int)lastPoint->x, (int)lastPoint->y),
                cv::Size((int)currentConnectivityRadius, (int)currentConnectivityRadius), 0.0,
                0, 360,
                BLUE, 3
            );
         
        }

        // Draw Transmission Path
        std::vector<unsigned int> transmissionPathIDs = transmissionField.GetTransmissionPath();
        if (transmissionPathIDs.size() > 1 && showTransmissionPath)
        {
            std::vector<unsigned int>::iterator firstBeaconID = transmissionPathIDs.begin();
            std::vector<unsigned int>::iterator secondBeaconID = std::next(firstBeaconID);
          
            for (; secondBeaconID != transmissionPathIDs.end(); ++firstBeaconID, ++secondBeaconID)
            {
                std::optional<cv::Point2d> firstBeacon2DCenter(transmissionField.GetBeacon(*firstBeaconID)->GetCenterPoint());
                std::optional<cv::Point2d> secondBeacon2DCenter(transmissionField.GetBeacon(*secondBeaconID)->GetCenterPoint());

                cv::Point firstBeaconCenter(firstBeacon2DCenter->x, firstBeacon2DCenter->y);
                cv::Point secondBeaconCenter(secondBeacon2DCenter->x, secondBeacon2DCenter->y);

                cv::line(canvas, firstBeaconCenter, secondBeaconCenter, RED, 3);
            }
        }



        cv::imshow("canvas", canvas);
        auto keyVal = cv::waitKey(1);

        if (keyVal != -1)
        {
            if (keyVal == 'c')
            {
                transmissionField.Reset();
                lastPoint.reset();
                // TODO: clear canvas
            }
            else if (keyVal == 't')
            {
                // TODO: toggle show / hide connectivity radius
              showTransmissionPath = !showTransmissionPath;
            }
            else if (keyVal == 27) // escape
            {
                break; // exit program
            }
        }

    }
}


int main()
{
    Run();
    return 0;
}
