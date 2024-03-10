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

    int direction = 0;
    float value = 0.0;
    std::string button_name;
    QTimer *timer;

public slots:
    virtual void arrowButtonPressed();
    virtual void arrowButtonReleased();
    void updateValue();
    
signals:

private:
    Ui::TocabiJoy ui_;
    QWidget* widget_;
    void joyCallback(const sensor_msgs::Joy::ConstPtr& msg);
};

}  // namespace tocabi_joy
