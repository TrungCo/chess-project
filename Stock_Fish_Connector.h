#ifndef STOCK_FISH_CONNECTOR_H_INCLUDED
#define STOCK_FISH_CONNECTOR_H_INCLUDED

#include "Start_prog.h"


class Stock_fish_engine{
private:
    HANDLE hChildStd_IN_Rd; // Pipe để đọc từ tiến trình con
    HANDLE hChildStd_IN_Wr; // Pipe để ghi vào tiến trình con
    HANDLE hChildStd_OUT_Rd; // Pipe để đọc từ tiến trình con
    HANDLE hChildStd_OUT_Wr; // Pipe để ghi vào tiến trình con

public:
    // Hàm khởi tạo
    Stock_fish_engine(const std::string& enginePath) {
        SECURITY_ATTRIBUTES saAttr;
        saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
        saAttr.bInheritHandle = TRUE; // Cho phép các handle được kế thừa
        saAttr.lpSecurityDescriptor = nullptr;

        // Tạo pipe cho stdin (đầu vào của tiến trình con)
        if (!CreatePipe(&hChildStd_IN_Rd, &hChildStd_IN_Wr, &saAttr, 0)) {
            std::cerr << "Lỗi: Không thể tạo pipe cho stdin." << std::endl;
            exit(1);
        }

        // Tạo pipe cho stdout (đầu ra của tiến trình con)
        if (!CreatePipe(&hChildStd_OUT_Rd, &hChildStd_OUT_Wr, &saAttr, 0)) {
            std::cerr << "Lỗi: Không thể tạo pipe cho stdout." << std::endl;
            exit(1);
        }

        // Cấu hình thông tin tiến trình
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        // Thiết lập các handle cho stdin, stdout, và stderr của tiến trình con
        si.hStdError = hChildStd_OUT_Wr;
        si.hStdOutput = hChildStd_OUT_Wr;
        si.hStdInput = hChildStd_IN_Rd;
        si.dwFlags |= STARTF_USESTDHANDLES;

        // Tạo tiến trình con (Stockfish)
        if (!CreateProcess(
                nullptr, // Tên ứng dụng (nullptr để sử dụng command line)
                const_cast<LPSTR>(enginePath.c_str()), // Command line
                nullptr, // Security attributes (tiến trình)
                nullptr, // Security attributes (thread)
                TRUE, // Các handle có thể được kế thừa
                0, // Cờ tạo tiến trình
                nullptr, // Môi trường
                nullptr, // Thư mục làm việc
                &si, // STARTUPINFO
                &pi)) { // PROCESS_INFORMATION
            std::cerr << "Lỗi: Không thể tạo tiến trình Stockfish." << std::endl;
            exit(1);
        }

        // Đóng các handle không cần thiết
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    // Hàm hủy
    ~Stock_fish_engine() {
        CloseHandle(hChildStd_IN_Rd);
        CloseHandle(hChildStd_IN_Wr);
        CloseHandle(hChildStd_OUT_Rd);
        CloseHandle(hChildStd_OUT_Wr);
    }

    // Gửi lệnh đến Stockfish và nhận phản hồi
    void sendCommand(const std::string& command) {
        DWORD written;
        // Ghi lệnh vào pipe đầu vào của tiến trình con
        WriteFile(hChildStd_IN_Wr, command.c_str(), command.size(), &written, nullptr);
        WriteFile(hChildStd_IN_Wr, "\n", 1, &written, nullptr); // Thêm ký tự xuống dòng
    }

    // Đọc phản hồi từ Stockfish
    std::string readResponse() {
        char buffer[1024];
    std::string response;
    DWORD read;
    while (true) {
        if (!ReadFile(hChildStd_OUT_Rd, buffer, sizeof(buffer), &read, nullptr) || read == 0) break;
        response.append(buffer, read);
        // Dừng lại nếu nhận được phản hồi mong muốn
        if (response.find("bestmove") != std::string::npos) {
            break;
        }
    }

    // Trích xuất nước đi từ phản hồi
    if (response.find("Checkers:")!= std::string::npos){
        return "chieu";
    }
    size_t bestmovePos = response.find("bestmove");
    if (bestmovePos != std::string::npos) {
        size_t moveStart = bestmovePos + 9; // Vị trí bắt đầu của nước đi
        size_t moveEnd = response.find(' ', moveStart); // Vị trí kết thúc của nước đi
        if (moveEnd != std::string::npos) {
            return response.substr(moveStart, moveEnd - moveStart);
        }
        else {
            return response.substr(moveStart);
        }
    }

    return "none"; // Trả về chuỗi rỗng nếu không tìm thấy nước đi
    }
};



#endif // STOCK_FISH_CONNECTOR_H_INCLUDED
