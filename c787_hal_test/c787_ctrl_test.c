#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "inc/header.h"

extern void init();
extern int __set_wpkey_h_ang(float h);
extern int __set_wpkey_v_ang(float v);
extern float __get_wpkey_h_ang();
extern float __get_wpkey_v_ang();
extern void four_corner_keystone(int corner, int x, int y);

extern struct wpkey_param my_wpkey_param;
extern struct wpkey_param my_wpkey_param_old;

int g_spi_fd = -1;
int g_firmware_fd = -1;

void dump()
{
    printf("############################\n");
    printf("H-ang %f\n", my_wpkey_param.wpkey_ang_h);
    printf("V-ang %f\n", my_wpkey_param.wpkey_ang_v);
    printf("----------------------------\n");
    printf("Top Left\t: x = %d, y = %d\n", my_wpkey_param.wp_pos4c.tl_x, my_wpkey_param.wp_pos4c.tl_y);
    printf("Top Right\t: x = %d, y = %d\n", my_wpkey_param.wp_pos4c.tr_x, my_wpkey_param.wp_pos4c.tr_y);
    printf("Bottom Left\t: x = %d, y = %d\n", my_wpkey_param.wp_pos4c.bl_x, my_wpkey_param.wp_pos4c.bl_y);
    printf("Bottom Right\t: x = %d, y = %d\n", my_wpkey_param.wp_pos4c.br_x, my_wpkey_param.wp_pos4c.br_y);
    printf("############################\n\n");

}

int main(int argc, char *argv[])
{
#define FOURCORNER  0
#define HVKEYSTON   1
    int mode = 0;

    int corner = 0, x = 0, y = 0;
    float h = 0, v = 0;
    clock_t start, finish;
    double duration;

    if (argc != 2) {
        printf("usage: c787_ctrl_test mode\n" \
            "\tmode %d for four corner keystone\n" \
            "\tmode %d for HV keystone\n", FOURCORNER, HVKEYSTON);
        exit(-1);
    }

    g_spi_fd = open(DEVICE_NAME, O_RDWR);
    if (g_spi_fd < 0) {
        perror("open");
        exit(-1);
    }
    
    init();
    
    sscanf(argv[1], "%d", &mode);
    if (mode == FOURCORNER) {
        printf("mode : four corner keystone\n\n");
       
        while (1) {
            printf("input >");
            scanf("%d %d %d", &corner, &x, &y);
            //printf("corner = %d, x = %d, y = %d\n", corner, x, y);
            start = clock(); 
            four_corner_keystone(corner, x, y);
            finish = clock();

            duration = (double)(finish - start) * 1000 / CLOCKS_PER_SEC;
            printf("time: %f ms\n", duration);
            dump();
        }
    } else if (mode == HVKEYSTON) {
        printf("mode : HV keystone\n\n");

        while (1) {
            printf("input >");            
            scanf("%f %f", &h, &v);

            start = clock(); 
            __set_wpkey_h_ang(h);
            __set_wpkey_v_ang(v);
            finish = clock();

            duration = (double)(finish - start) * 1000 / CLOCKS_PER_SEC;
            printf("time: %f ms\n", duration);
            dump();
        }
    } else {
        printf("unkonwn mode\n");
        exit(-1);
    }
        
    return 0;
}

