#include <string>
#include <vector>
#include <iostream>

using namespace std;

const int MAX_INT = 2147483647;
const char FILE_CHAR = '#';

vector<int> solution(vector<string> wallpaper) {
    int lx = MAX_INT, ly = MAX_INT, rx = -1, ry = -1;
    int w = wallpaper[0].size(), h = wallpaper.size();

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (wallpaper[i][j] == FILE_CHAR) {
                lx = min(lx, j);
                rx = max(rx, j);
                ly = min(ly, i);
                ry = max(ry, i);
            }
        }
    }

    return { ly, lx, ry + 1, rx + 1 };
}