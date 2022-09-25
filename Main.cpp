#include <iostream>
#include <windows.h>
#include <math.h>

int main()
{
    float A = 0, B = 0;

    // i = phi (화이)
    // j = theta (세타)
    float i, j;

    int k;

    // buffer size
    float z[1760];
    char b[1760];

    // Clear Screen
    std::cout << "\x1b[2J";

    // Spin
    while (true)
    {
        // void* memset(void* ptr, int value, size_t num);
        // 메모리 초기화
        memset(b, 32, 1760);
        memset(z, 0, 7040);

        // Spin Angle
        for (j = 0; j < 6.28; j += 0.07)
        {
            // Spin Angle
            for (i = 0; i < 6.28; i += 0.02)
            {
                // 휘도 계산
                float c = sin(i); // sin(phi)
                float d = cos(j); // cos(theta)
                float e = sin(A); // sin(A)
                float f = sin(j); // sin(theta)
                float g = cos(A); // cos(A)
                float h = d + 2;  // cos(theta) + 2
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i); // cos(phi)
                float m = cos(B); // cos(B)
                float n = sin(B); // sin(B)

                float t = c * h * g - f * e;

                // X축 계산
                int x = 40 + 30 * D * (l * h * m - t * n);

                // Y축 계산
                int y = 12 + 15 * D * (l * h * n + t * m);

                // ASCII 버퍼 저장 변수 (1차원 array)
                int o = x + 80 * y;

                // 휘도 공식 (N = 휘도)
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o])
                {
                    // Z 버퍼의 D
                    z[o] = D;

                    // 휘도를 기준으로 ASCII 버퍼 저장
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }
        // escape
        std::cout << "\x1b[H";

        for (k = 0; k <= 1760; k++)
        {
            putchar(k % 80 ? b[k] : 10);
            A += 0.00004;
            B += 0.00002;
        }

        // 1000 = 1초
        Sleep(10);
    }
    return 0;
}