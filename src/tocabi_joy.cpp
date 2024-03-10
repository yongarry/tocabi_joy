#include "tocabi_joy/tocabi_joy.h"
#include <pluginlib/class_list_macros.h>
#include <QStringList>

namespace tocabi_joy {

TocabiJoy::TocabiJoy()
    : rqt_gui_cpp::Plugin(), widget_(0) {
    setObjectName("TocabiJoy");
}

void TocabiJoy::initPlugin(qt_gui_cpp::PluginContext& context) {
    QStringList argv = context.argv();
    widget_ = new QWidget();
    ui_.setupUi(widget_);
    context.addWidget(widget_);

    joy_pub_ = getNodeHandle().advertise<sensor_msgs::Joy>("/joy", 1);
    joy_sub_ = getNodeHandle().subscribe("/joy", 1, &TocabiJoy::joyCallback, this);

    ui_.wButton->setShortcut(QKeySequence(Qt::Key_W));
    ui_.aButton->setShortcut(QKeySequence(Qt::Key_A));
    ui_.sButton->setShortcut(QKeySequence(Qt::Key_S));
    ui_.dButton->setShortcut(QKeySequence(Qt::Key_D));

    ui_.wButton->setIcon(QIcon::fromTheme("go-up"));
    ui_.aButton->setIcon(QIcon::fromTheme("go-previous"));
    ui_.sButton->setIcon(QIcon::fromTheme("go-down"));
    ui_.dButton->setIcon(QIcon::fromTheme("go-next"));

    connect(ui_.wButton, SIGNAL(pressed()), this, SLOT(arrowButtonPressed()));
    connect(ui_.aButton, SIGNAL(pressed()), this, SLOT(arrowButtonPressed()));
    connect(ui_.sButton, SIGNAL(pressed()), this, SLOT(arrowButtonPressed()));
    connect(ui_.dButton, SIGNAL(pressed()), this, SLOT(arrowButtonPressed()));

    connect(ui_.wButton, SIGNAL(released()), this, SLOT(arrowButtonReleased()));
    connect(ui_.aButton, SIGNAL(released()), this, SLOT(arrowButtonReleased()));
    connect(ui_.sButton, SIGNAL(released()), this, SLOT(arrowButtonReleased()));
    connect(ui_.dButton, SIGNAL(released()), this, SLOT(arrowButtonReleased()));

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TocabiJoy::updateValue);

    joy_msg_.axes.resize(2);
}

void TocabiJoy::arrowButtonPressed() {
    direction = 1;
    button_name = sender()->objectName().toStdString();
    timer->start(100); // Adjust time interval as needed
}

void TocabiJoy::arrowButtonReleased() {
    direction = -1;
    button_name = sender()->objectName().toStdString();
    timer->start(100); // Adjust time interval as needed
}

void TocabiJoy::updateValue() {
    value += direction * 0.1; // Adjust step size as needed
    if (value < 0) {
        value = 0;
        timer->stop();
    }
    if (value > 1) {
        value = 1;
        timer->stop();
    }
    sensor_msgs::Joy msg;
    msg.axes.resize(2);
    if (button_name == "wButton") {
        msg.axes[0] = value;
    } else if (button_name == "aButton") {
        msg.axes[1] = value;
    } else if (button_name == "sButton") {
        msg.axes[0] = -value;
    } else if (button_name == "dButton") {
        msg.axes[1] = -value;
    }
    joy_pub_.publish(msg);
}

void TocabiJoy::joyCallback(const sensor_msgs::Joy::ConstPtr& msg) {
    joy_msg_ = *msg;
    ui_.axis0->setText(QString::number(joy_msg_.axes[0]));
    ui_.axis1->setText(QString::number(joy_msg_.axes[1]));
}

void TocabiJoy::shutdownPlugin() {
}

void TocabiJoy::saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const {
}

void TocabiJoy::restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings) {
}

}  // namespace tocabi_joy
PLUGINLIB_EXPORT_CLASS(tocabi_joy::TocabiJoy, rqt_gui_cpp::Plugin)