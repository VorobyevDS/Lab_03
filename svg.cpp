#include <iostream>
#include <vector>
#include <string.h>
#include "svg.h"
#include <sstream>
#include <windows.h>
#include <cstdio>


void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}
void
svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='"<< baseline<< "'>"<<text<<"</text>";
}
void svg_rect(double x, double y, double width, double height, string stroke, string fill){
    cout<< "<rect x= '" << x <<"' y='"<< y << "' width='"<<width<<"' height='" << height << "' stroke='"<< stroke<<"' fill='"<<fill<<"' />\n ";
}

void
svg_end() {
    cout << "</svg>\n";
}

string make_info_text() {
    stringstream buffer;

    DWORD infover = GetVersion();
    //printf("\ninfo_10= %u, info_16= %x", infover, infover);
    DWORD mask = 0x0000ffff;
    DWORD version = infover & mask;
    DWORD version_major = version & 0b00000000'00000000'00000000'11111111;
    DWORD version_minor = version >> 8;
    //printf("\nWindows v%lu.%lu", version_major, version_minor);// Windows v6.2 должны получить
    DWORD platform;
    if ((infover & 0x80000000 ) == 0) {
            platform = infover >> 16;
    } else {
            platform = ( infover >> 24 ) & 0x7f;
    }
    //printf(" build(%lu)\n", platform);

    buffer << "Windows v" << " " << version_major << "." << version_minor << " " << "(build" << " " << platform << ")" << '\n';
    TCHAR storage[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD  bufCharCount = MAX_COMPUTERNAME_LENGTH + 1;
    GetComputerNameA(LPSTR(storage), &bufCharCount);
    buffer << "\nComputer name:" << " " << storage;
    return buffer.str();
}

void
show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 700;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    size_t bin_count=0;
    size_t IMAGE_HEIGHT=0;
    const auto bin_height = 30;
    const auto BLOCK_WIDTH = 10;
    double MAX_WIDTH = (IMAGE_WIDTH - TEXT_WIDTH);
    size_t max_bin = bins[0];
    for (size_t bin : bins)
    {
        if (bin > max_bin)
        {
            max_bin = bin;
        }
    }
    double top = 0;
    for (size_t bin : bins){
        bin_count+=1;
    }
    IMAGE_HEIGHT=(bin_height*bin_count)+20;
    svg_begin(700, 300);

    for (size_t bin : bins) {
        double bin_width = BLOCK_WIDTH * bin;
        if (max_bin > (MAX_WIDTH/BLOCK_WIDTH))
        {
            bin_width = MAX_WIDTH * (static_cast<double>(bin) / max_bin);
        }
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, bin_height, "red", "red");
        top += bin_height;
}
    svg_text(TEXT_LEFT, IMAGE_HEIGHT - TEXT_BASELINE + 30, make_info_text());
    svg_end();
}

