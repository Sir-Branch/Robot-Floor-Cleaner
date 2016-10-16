
/* 
 * File:   input_manage_verification.h
 * Author: r2d2
 *
 * Created on March 27, 2016, 12:07 AM
 */

#ifndef INPUT_MANAGE_VERIFICATION_H
#define INPUT_MANAGE_VERIFICATION_H



    typedef struct
    {
        unsigned long num_robots,floor_width,floor_height,mode;
        bool num_robots_f,floor_width_f,floor_height_f,mode_f;

    }user_input_t;
    


    #define NOT_VALID_INPUT -1
    #define VALID_INPUT 0

    #define MAX_FLOOR_HEIGHT 70
    #define MAX_FLOOR_WIDTH 100
    #define MAX_NUM_ROBOTS	100

    
    int validate_simulation_info(user_input_t * user_input_data);
    int get_simulation_info(char *key,char* value,void *user_data);
    void initialize_user_input(user_input_t* data);


#endif /* INPUT_MANAGE_VERIFICATION_H */

