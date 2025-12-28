# PERSONAL FINANCE MANAGER (Introduction to Computer Science Final Project)

A professional C++ console-based application designed to help users track their financial health by recording income and expense transactions. This project emphasizes manual memory management, object-oriented programming (OOP), and binary data persistence without relying on the C++ Standard Template Library (STL).

## 👥 Contributors - Group 04
- **Trần Hồng Vy** (ID: 25125049)
- **Nguyễn Sơn Lâm** (ID: 25125058)

## 💻 Development Environment
- **Operating System:** Windows 11
- **Compiler:** g++ (via Visual Studio Code)
- **IDE:** Visual Studio Code

## 🚀 Key Features
- **Dynamic Data Handling:** Implemented a custom `DynamicArray` template to manage memory on the Heap without `std::vector`.
- **Transaction Management:** Supports detailed recording of Income and Expenses.
- **Master Data System:** Manage Wallets, Expense Categories, and Income Sources with unique ID mapping.
- **Binary Persistence:** Data is preserved across multiple executions using binary file handling in the `/data` folder.
- **Advanced Storage:** Optimized string storage using a Name Pool strategy (offsets and lengths).

## 📂 Project Structure
- `include/`: Header files (.h) defining class interfaces.
- `src/`: Implementation files (.cpp) containing the core business logic.
- `data/`: Binary storage files for data persistence.

## 🛠 Build and Run Instructions

### 1. Compile and Run the Application
Open your terminal in the project root directory and run:

```bash
g++ src/*.cpp -I include -o finance_manager
.\finance_manager.exe