#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <graphics.h>

const unsigned short MAX_RADIUS = 5;
const unsigned short POINTS_MAX = 100;
const unsigned int offset = 3;

const unsigned int duration = 400;
const unsigned int delay_for_speed = 20;

unsigned int max_x = 0;
unsigned int max_y = 0;
unsigned int mid_x = 0;
unsigned int mid_y = 0;
unsigned int max_circle = 0;
float diag_angle = 0.0f;

struct Star {
    float cos;
    float sin;
    unsigned int r;
    unsigned int rad;
    int sign_x;
    int sign_y;
};

int max(int x, int y) {
    return x > y ? x : y;
}

int min(int x, int y) {
    return x > y ? y : x;
}

unsigned int CalculateMaxR(struct Star *star) {
    unsigned int max_r;
    float angle = star->sin / star->cos;
    if (angle <= diag_angle) {
        unsigned int my = star->r * star->sin;
        max_r = sqrt(mid_x * mid_x + my * my);
    } else {
        unsigned int mx = star->r * star->cos;
        max_r = sqrt(mx * mx + mid_y * mid_y);
    }
    return max_r;
}

void GenerateCorrectR(struct Star *star, unsigned int max) {
    if (max != 0) {
        unsigned int max_r = CalculateMaxR(star);
        max = max_r <= MAX_RADIUS ? max_r + MAX_RADIUS : max_r - MAX_RADIUS;
        star->r = rand() % max;
    } else {
        star->r = rand() % min(mid_x, mid_y);
    }
}

int GenerateSign() {
    int sign = 0;
    while (sign == 0) {
        sign = (rand() % 3) - 1;
    }
    return sign;
}

void GenerateAngle(struct Star *star) {
    float alf = (float)rand() / RAND_MAX;
    star->cos = alf;
    star->sin = sqrt(1 - alf * alf);
    star->sign_x = GenerateSign();
    star->sign_y = GenerateSign();
}

void GenerateCorrectRad(struct Star *star) {
    unsigned int max_r = CalculateMaxR(star);
    float remote_coeff = (float) star->r / max_r;
    int remoteness_idx = remote_coeff * (float) MAX_RADIUS;
    star->rad = remoteness_idx;
}

void GenerateCorrectStar(struct Star *star) {
    GenerateAngle(star);
    GenerateCorrectR(star, 0);
    GenerateCorrectRad(star);
}

void fillNet(struct Star* net) {
    int i = 0;
    srand(time(NULL));
    for (i = 0; i < POINTS_MAX; ++i) {
        GenerateCorrectStar(&net[i]);
    }
}

void CalculateNewStar(struct Star *star) {
    star->r += offset;
    unsigned int max_r = CalculateMaxR(star);
    if (star->r >= max_r - MAX_RADIUS) {
        GenerateCorrectR(star, max_circle);
        GenerateCorrectRad(star);
    } else {
        GenerateCorrectRad(star);
    }
}

void printStars(struct Star *net) {
    cleardevice();
    int i = 0;
    for (i = 0; i < POINTS_MAX; ++i) {
        CalculateNewStar(&net[i]);
        unsigned int x = net[i].r * net[i].cos * net[i].sign_x;
        unsigned int y = net[i].r * net[i].sin * net[i].sign_y;
        fillellipse(mid_x + x, mid_y + y, net[i].rad, net[i].rad);
    }
    delay(delay_for_speed);
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm,NULL);
    max_x = getmaxx();
    max_y = getmaxy();
    mid_x = max_x / 2;
    mid_y = max_y / 2;
    max_circle = min(max_x, max_y) / 12;
    diag_angle = (float) (max_y - mid_y) / (max_x - mid_x);

    int i = 0;
    struct Star *net = (struct Star *)malloc(POINTS_MAX * sizeof(struct Star));
    fillNet(net);
    for (i = 0 ; i < duration; ++i) {
        printStars(net);
    }
    delay(500);
    free(net);
    getch();
    closegraph();

    return 0;
}
