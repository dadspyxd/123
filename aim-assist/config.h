#pragma once
#include <string>
#include <array>
#include <chrono>
#include <thread>

// Windows-specific function stubs for compilation testing
#define WINAPI
typedef void* HWND;
typedef unsigned long DWORD;

// Forward declarations of Windows functions
DWORD GetTickCount64();
short GetAsyncKeyState(int);
void Sleep(DWORD);

// Class declarations
class enemy_scanner {
public:
    void update();
    std::array<double, 2> find_closest_enemy_head(double, double, const char*);
    bool is_enemy_in_crosshair();
};

class driver {
public:
    void move_mouse(double x, double y, int flags);
    static driver& get_instance();
private:
    driver() {} // Private constructor for singleton
};

class stopwatch {
public:
    void update();
    double get_elapsed();
};

// Configuration variables
extern bool render_menu;
extern bool login_state;
extern bool aimbot_state;
extern int a1mb0tKey;
extern std::string color;
extern double aimbot_fov_x;
extern double aimbot_fov_y;
extern float last_target_time;
extern int aim_mode;
extern double aimbot_speed;
extern double sticky_strength;
extern double sensx;
extern double sensy;
extern double recoil_offset;
extern double head_offset;
extern bool linear_constant_speed;
extern double linear_speed;
extern bool humanization_enabled;
extern int micro_adjust_min;
extern int micro_adjust_max;
extern double micro_adjust_strength;
extern bool enable_curve;
extern double curve_strength;
extern bool enable_speed_randomization;
extern double speed_random_strength;
extern bool magnet_enabled;
extern int magnet_key;
extern double magnet_fov;
extern double magnet_smooth;
extern bool magnet_auto_shoot;
extern double magnet_delay_between_shots;
extern bool flick_state;
extern int flickKey;
extern double flick_delay;
extern double flick_fov_x;
extern double flick_fov_y;
extern int flick_mode;
extern bool flick_double_click;
extern int flick_smoothing;
extern bool silent_state;
extern int silentKey;
extern double silent_delay;
extern double silent_fov_x;
extern double silent_fov_y;
extern bool trigger_state;
extern int triggerKey;
extern int first_shoot_delay;
extern double trigger_fov;
extern int fps_target;

// Function declarations
void meain();
