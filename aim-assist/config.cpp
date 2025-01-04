#include "config.h"
#include <string>
#include <chrono>
#include <thread>

bool render_menu = false;
bool login_state = false;
bool aimbot_state = false;
int a1mb0tKey = 0x01;  // VK_LBUTTON
std::string color = "red";
double aimbot_fov_x = 30.0;
double aimbot_fov_y = 30.0;
float last_target_time = 0.0f;
int aim_mode = 1;
double aimbot_speed = 50.0;
double sticky_strength = 0.5;
double sensx = 1.0;
double sensy = 1.0;
double recoil_offset = 0.0;
double head_offset = 0.0;
bool linear_constant_speed = true;
double linear_speed = 1.0;
bool humanization_enabled = true;
int micro_adjust_min = 100;
int micro_adjust_max = 200;
double micro_adjust_strength = 0.5;
bool enable_curve = true;
double curve_strength = 0.3;
bool enable_speed_randomization = true;
double speed_random_strength = 0.2;
bool magnet_enabled = false;
int magnet_key = 0x05;  // VK_XBUTTON1
double magnet_fov = 15.0;
double magnet_smooth = 50.0;
bool magnet_auto_shoot = false;
double magnet_delay_between_shots = 200.0;
bool flick_state = false;
int flickKey = 0x06;  // VK_XBUTTON2
double flick_delay = 200.0;
double flick_fov_x = 30.0;
double flick_fov_y = 30.0;
int flick_mode = 0;
bool flick_double_click = false;
int flick_smoothing = 1;
bool silent_state = false;
int silentKey = 0x04;  // VK_MBUTTON
double silent_delay = 200.0;
double silent_fov_x = 30.0;
double silent_fov_y = 30.0;
bool trigger_state = false;
int triggerKey = 0x12;  // VK_MENU
int first_shoot_delay = 100;
double trigger_fov = 5.0;
int fps_target = 240;
