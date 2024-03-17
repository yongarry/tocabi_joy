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
    ui_.qButton->setShortcut(QKeySequence(Qt::Key_Q));
    ui_.eButton->setShortcut(QKeySequence(Qt::Key_E));

    ui_.wButton->setIcon(QIcon::fromTheme("go-up"));
    ui_.aButton->setIcon(QIcon::fromTheme("go-previous"));
    ui_.sButton->setIcon(QIcon::fromTheme("go-down"));
    ui_.dButton->setIcon(QIcon::fromTheme("go-next"));

    // connect(ui_.wButton, SIGNAL(pressed()), this, SLOT(arrowButtonPressed()));
    // connect(ui_.aButton, SIGNAL(pressed()), this, SLOT(arrowButtonPressed()));
    // connect(ui_.sButton, SIGNAL(pressed()), this, SLOT(arrowButtonPressed()));
    // connect(ui_.dButton, SIGNAL(pressed()), this, SLOT(arrowButtonPressed()));

    // connect(ui_.wButton, SIGNAL(released()), this, SLOT(arrowButtonReleased()));
    // connect(ui_.aButton, SIGNAL(released()), this, SLOT(arrowButtonReleased()));
    // connect(ui_.sButton, SIGNAL(released()), this, SLOT(arrowButtonReleased()));
    // connect(ui_.dButton, SIGNAL(released()), this, SLOT(arrowButtonReleased()));

    connect(ui_.wButton, SIGNAL(pressed()), this, SLOT(arrowButtonPressed1()));
    connect(ui_.sButton, SIGNAL(pressed()), this, SLOT(arrowButtonPressed1()));
    connect(ui_.aButton, SIGNAL(pressed()), this, SLOT(arrowButtonPressed2()));
    connect(ui_.dButton, SIGNAL(pressed()), this, SLOT(arrowButtonPressed2()));
    connect(ui_.qButton, SIGNAL(pressed()), this, SLOT(arrowButtonPressed3()));
    connect(ui_.eButton, SIGNAL(pressed()), this, SLOT(arrowButtonPressed3()));

    connect(ui_.wButton, SIGNAL(released()), this, SLOT(arrowButtonReleased1()));
    connect(ui_.sButton, SIGNAL(released()), this, SLOT(arrowButtonReleased1()));
    connect(ui_.aButton, SIGNAL(released()), this, SLOT(arrowButtonReleased2()));
    connect(ui_.dButton, SIGNAL(released()), this, SLOT(arrowButtonReleased2()));
    connect(ui_.qButton, SIGNAL(released()), this, SLOT(arrowButtonReleased3()));
    connect(ui_.eButton, SIGNAL(released()), this, SLOT(arrowButtonReleased3()));

    timer = new QTimer(this);
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    timer3 = new QTimer(this);
    connect(timer1, &QTimer::timeout, this, &TocabiJoy::updateValue1);
    connect(timer2, &QTimer::timeout, this, &TocabiJoy::updateValue2);
    connect(timer3, &QTimer::timeout, this, &TocabiJoy::updateValue3);

    connect(timer, &QTimer::timeout, this, &TocabiJoy::updateValue);
    timer->start(10); // Adjust time interval as needed
}

// void TocabiJoy::arrowButtonPressed() {
//     direction = 1;
//     button_name = sender()->objectName().toStdString();
//     timer->start(100); // Adjust time interval as needed
// }

// void TocabiJoy::arrowButtonReleased() {
//     direction = -1;
//     button_name = sender()->objectName().toStdString();
//     timer->start(100); // Adjust time interval as needed
// }

// void TocabiJoy::updateValue() {
//     value += direction * 0.1; // Adjust step size as needed
//     if (value < 0) {
//         value = 0;
//         timer->stop();
//     }
//     if (value > 1) {
//         value = 1;
//         timer->stop();
//     }
//     sensor_msgs::Joy msg;
//     msg.axes.resize(2);
//     if (button_name == "wButton") {
//         msg.axes[0] = value;
//     } else if (button_name == "aButton") {
//         msg.axes[1] = value;
//     } else if (button_name == "sButton") {
//         msg.axes[0] = -value;
//     } else if (button_name == "dButton") {
//         msg.axes[1] = -value;
//     }
//     joy_pub_.publish(msg);
// }

void TocabiJoy::arrowButtonPressed1() {
    direction_x = 1;
    button_name_1 = sender()->objectName().toStdString();
    timer1->start(100); // Adjust time interval as needed
}

void TocabiJoy::arrowButtonReleased1() {
    direction_x = -1;
    button_name_1 = sender()->objectName().toStdString();
    timer1->start(100); // Adjust time interval as needed
}

void TocabiJoy::arrowButtonPressed2() {
    direction_y = 1;
    button_name_2 = sender()->objectName().toStdString();
    timer2->start(100); // Adjust time interval as needed
}

void TocabiJoy::arrowButtonReleased2() {
    direction_y = -1;
    button_name_2 = sender()->objectName().toStdString();
    timer2->start(100); // Adjust time interval as needed
}

void TocabiJoy::arrowButtonPressed3() {
    direction_t = 1;
    button_name_3 = sender()->objectName().toStdString();
    timer3->start(100); // Adjust time interval as needed
}

void TocabiJoy::arrowButtonReleased3() {
    direction_t = -1;
    button_name_3 = sender()->objectName().toStdString();
    timer3->start(100); // Adjust time interval as needed
}

void TocabiJoy::updateValue1() {
    valuex += direction_x * 0.1; // Adjust step size as needed
    if (valuex < 0) {
        valuex = 0;
        timer1->stop();
    }
    if (valuex > 1) {
        valuex = 1;
        timer1->stop();
    }
    if (button_name_1 == "sButton")
        valuex_ = -valuex;
    else
        valuex_ = valuex;
}

void TocabiJoy::updateValue2() {
    valuey += direction_y * 0.1; // Adjust step size as needed
    if (valuey < 0) {
        valuey = 0;
        timer2->stop();
    }
    if (valuey > 1) {
        valuey = 1;
        timer2->stop();
    }
    if (button_name_2 == "dButton")
        valuey_ = -valuey;
    else
        valuey_ = valuey;
}

void TocabiJoy::updateValue3() {
    valuet += direction_t * 0.1; // Adjust step size as needed
    if (valuet < 0) {
        valuet = 0;
        timer3->stop();
    }
    if (valuet > 1) {
        valuet = 1;
        timer3->stop();
    }
    if (button_name_3 == "eButton")
        valuet_ = -valuet;
    else
        valuet_ = valuet;
    
}

void TocabiJoy::updateValue() {
    sensor_msgs::Joy msg;
    msg.axes.resize(3);
    msg.axes[0] = valuex_;
    msg.axes[1] = valuey_;
    msg.axes[2] = valuet_;
    joy_pub_.publish(msg);
}

void TocabiJoy::joyCallback(const sensor_msgs::Joy::ConstPtr& msg) {
    joy_msg_ = *msg;
    ui_.axis0->setText(QString::number(joy_msg_.axes[0]));
    ui_.axis1->setText(QString::number(joy_msg_.axes[1]));
    ui_.axis2->setText(QString::number(joy_msg_.axes[2]));
}

void TocabiJoy::shutdownPlugin() {
}

void TocabiJoy::saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const {
}

void TocabiJoy::restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings) {
}

}  // namespace tocabi_joy
PLUGINLIB_EXPORT_CLASS(tocabi_joy::TocabiJoy, rqt_gui_cpp::Plugin)