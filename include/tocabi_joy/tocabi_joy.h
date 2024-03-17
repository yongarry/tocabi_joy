#include <rqt_gui_cpp/plugin.h>
#include <tocabi_joy/ui_tocabi_joy.h>
#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <std_msgs/Float32.h>
#include <sensor_msgs/Joy.h>
#include <iostream>

#include <ros/ros.h>

namespace tocabi_joy {

class TocabiJoy : public rqt_gui_cpp::Plugin {
    Q_OBJECT
public:
    TocabiJoy();
    virtual void initPlugin(qt_gui_cpp::PluginContext& context);
    virtual void shutdownPlugin();
    virtual void saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const;
    virtual void restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings);
    
    ros::Publisher joy_pub_;
    ros::Subscriber joy_sub_;

    sensor_msgs::Joy joy_msg_;

    int direction_x = 0;
    int direction_y = 0;
    int direction_t = 0;
    // float value = 0.0;
    float valuex = 0.0;
    float valuey = 0.0;
    float valuet = 0.0;
    float valuex_ = 0.0;
    float valuey_ = 0.0;
    float valuet_ = 0.0;

    // std::string button_name;
    std::string button_name_1;
    std::string button_name_2;
    std::string button_name_3;

    QTimer *timer;
    QTimer *timer1;
    QTimer *timer2;
    QTimer *timer3;


public slots:
    // virtual void arrowButtonPressed();
    // virtual void arrowButtonReleased();
    virtual void arrowButtonPressed1();
    virtual void arrowButtonReleased1();
    virtual void arrowButtonPressed2();
    virtual void arrowButtonReleased2();
    virtual void arrowButtonPressed3();
    virtual void arrowButtonReleased3();

    void updateValue();
    void updateValue1();
    void updateValue2();
    void updateValue3();
    
signals:

private:
    Ui::TocabiJoy ui_;
    QWidget* widget_;
    void joyCallback(const sensor_msgs::Joy::ConstPtr& msg);
};

}  // namespace tocabi_joy
