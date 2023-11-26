// --------------------1.引入头文件--------------------
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/SetPen.h>
#include <turtlesim/Spawn.h>
#include <turtlesim/Pose.h>
#include <Eigen/Dense> //使用Eigen库来处理二维向量

// --------------------2.全局变量定义--------------------
ros::Publisher turtle1_cmd_pub_, turtle2_cmd_pub_;
ros::Subscriber trigger_sub_, turtle1_pos_sub_, turtle2_pos_sub_;
ros::ServiceClient pen_service_, spawn_service_;
ros::Timer state_Timer_;

ros::Time spawn_time_;

bool if_start_ = false;
bool if_spawn_ = false;
bool if_finished_ = false;
double inverse_ = 1.0; //用于改变圆形运动的方向

Eigen::Vector2d turtle1Pose_, turtle2Pose_, loop_start_pos_;

// --------------------3.枚举类型定义--------------------
//使用枚举state定义了三种状态：LINE（直线运动）、CIRCLE（圆形运动）、FINISH（完成），stateCallback中的逻辑决定何时改变状态
enum state{LINE, CIRCLE, FINISH};

state State_ = state::LINE; 

// --------------------4.函数定义--------------------
void line_motion(){
    geometry_msgs::Twist cmd;
    cmd.linear.x = 1.0;
    turtle2_cmd_pub_.publish(cmd);
}

void circle_motion(){
    geometry_msgs::Twist cmd1;
    geometry_msgs::Twist cmd2;

    cmd1.linear.x = 1.0 * inverse_;
    cmd1.angular.z = 0.5 * inverse_;

    cmd2.linear.x = 1.5;
    cmd2.angular.z = 0.5;

    turtle1_cmd_pub_.publish(cmd1);
    turtle2_cmd_pub_.publish(cmd2);
}

void pose1Callback(turtlesim::Pose::ConstPtr msg){
    turtle1Pose_.x() = msg->x;
    turtle1Pose_.y() = msg->y;
}

void pose2Callback(turtlesim::Pose::ConstPtr msg){
    turtle2Pose_.x() = msg->x;
    turtle2Pose_.y() = msg->y;
}

void triggerCallback(geometry_msgs::Twist::ConstPtr msg){
    if(!if_spawn_){
        turtlesim::Spawn spawn_srv;
        spawn_srv.request.name = "turtle2";
        spawn_srv.request.x = 1.0;
        spawn_srv.request.y = 1.0;
        spawn_srv.request.theta = 0;
        spawn_service_.call(spawn_srv); //call成功会返回True
        ros::Duration(0.05).sleep();
        if(spawn_srv.response.name.c_str() != NULL){
            if_spawn_ = true;
        }    
    }
    if_start_ = true;
    spawn_time_ = ros::Time::now();
}

// --------------------5.主要回调函数--------------------
void stateCallback(const ros::TimerEvent& event){
    ros::Time tnow = ros::Time::now();
    if(!if_start_ || ! if_spawn_ || if_finished_ ) return;
    if((tnow - spawn_time_).toSec() < 3.0) return;

    static int loop_cnt = 0;
    if((turtle1Pose_[0] - turtle2Pose_[0]) < 0.01 && loop_cnt == 0){
        State_ = state::CIRCLE;
        loop_start_pos_ = turtle2Pose_;
        loop_cnt ++;
    }
    
    
    static turtlesim::SetPen pen_srv;
    pen_srv.request.width = 6.0;
    pen_srv.request.r = 255.0;
    pen_srv.request.g = 0.0;
    pen_srv.request.b = 0.0;


    switch(State_){
        case state::LINE:
        {
            line_motion();
            break;
        }
        case state::CIRCLE:
        {
            static ros::Time start_t = ros::Time::now();
            static double accumulate_t = 0;
            static int color_cnt = 1;
            
            circle_motion();

            if((tnow - start_t).toSec() - accumulate_t > 1.0){
                pen_srv.request.r = color_cnt % 3 == 1 ? 255.0 : 0.0;
                pen_srv.request.g = color_cnt % 3 == 2 ? 255.0 : 0.0;
                pen_srv.request.b = color_cnt % 3 == 0 ? 255.0 : 0.0;
                pen_service_.call(pen_srv);
                color_cnt ++;
                accumulate_t += 1.0;
            }

            static int loop_state = 1;
            if((turtle2Pose_[0] < loop_start_pos_[0]) && loop_state == 1) loop_state = 2;
            if((turtle2Pose_[0] > loop_start_pos_[0]) && loop_state == 2){
                loop_cnt++;
                inverse_ *= -1.0;
                loop_state = 1;
                ROS_WARN("direction inverse!");
            }

            if(loop_cnt > 3.0) State_ = state::FINISH;

            break;
        }
        case state::FINISH:{
            ROS_WARN("loop finished!");
            if_finished_ = true;
        }
    }

}


// --------------------6.主函数-------------------
int main(int argc, char **argv) {
    //初始化ROS节点和句柄
    ros::init(argc, argv, "ros_turtle");
    ros::NodeHandle n;
    ROS_WARN("turtle node initialized!");

    //设置发布、订阅和服务器客户端
    turtle1_cmd_pub_ = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    turtle2_cmd_pub_ = n.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 10);

    turtle1_pos_sub_ = n.subscribe("/turtle1/pose", 10, pose1Callback);
    turtle2_pos_sub_ = n.subscribe("/turtle2/pose", 10, pose2Callback);

    trigger_sub_ = n.subscribe("/trigger", 10, triggerCallback);

    //在圆形运动状态中，使用SetPen服务来改变乌龟绘制的颜色
    pen_service_ = n.serviceClient<turtlesim::SetPen>("/turtle2/set_pen");
    spawn_service_ = n.serviceClient<turtlesim::Spawn>("/spawn");
   
    //创建并启动计时器，该计时器会定期调用stateCallback函数
    state_Timer_ = n.createTimer(ros::Duration(0.05), stateCallback);

    //调用ros::spin()使程序保持运行，直到收到关闭信号
    ros::spin();

    return 0;
}