
# 💰 Personal Finance Manager

<p align="center">
  <img src="https://img.shields.io/badge/C++-17-blue?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++ 17">
  <img src="https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey?style=for-the-badge" alt="Multi-Platform">
  <img src="https://img.shields.io/badge/Status-Completed-brightgreen?style=for-the-badge" alt="Completed">
</p>


> A personal finance management application written in pure C++ - Final project for Introduction to Computer Science

## 👥 Contributors - Group 04

- **Trần Hồng Vy** (ID: 25125049)
- **Nguyễn Sơn Lâm** (ID: 25125058)

## 💻 Development Environment

- **Operating System:** Windows 11, MacOS Monterey 12.7.6
- **Compiler:** g++ (via Visual Studio Code, Xcode)
- **IDE:** Visual Studio Code, XCode

## 📖 Table of Contents

- Introduction
- Key features
- Installation
- Usage
- Architecture
- Project Structure
- Demo Video
- Technical Details

## 🎯 Introduction

**Personal Finance Manager** is a console-based financial tracking application developed in pure C++. This tool helps users manage their daily income and expenses, track multiple wallets, and analyze financial health through comprehensive reports and statistics.

**Academic Objectives:**

- Implement Object-Oriented Programming concepts in C++
- Practice manual memory management with dynamic arrays
- Work with binary file I/O for data persistence
- Develop a complete console application from scratch

## ✨ Key Features

- **Dynamic Data Handling:** Implemented a custom `DynamicArray` template to manage memory on the Heap without `std::vector`.
- **Transaction Management:** Supports detailed recording of Income and Expenses.
- **Master Data System:** Manage Wallets, Expense Categories, and Income Sources with unique ID mapping.
- **Binary Persistence:** Data is preserved across multiple executions using binary file handling in the `/data` folder.
- **Advanced Storage:** Optimized string storage using a Name Pool strategy (offsets and lengths).

## 🚀 Installation

### Prerequisites

- **Compiler**: GCC/G++ 9+ or Clang 10+ or MSVC 2019+
- **Operating System**: Windows, Linux, or macOS
- **Memory**: Minimum 4MB RAM

### Build Instructions

```bash
# 1. Clone the repository
git clone https://github.com/Slampanda/Final-Project-Group-4-Personal-Finance-Manager-.git

# 2. Create build directory
mkdir build && cd build

# 3. Compile the application
# Linux/macOS:
g++ -std=c++17 -o pfm ../src/*.cpp -I../include

# Windows (MinGW):
g++ -std=c++17 -o pfm.exe ../src/*.cpp -I../include

# 4. Run the application
./pfm  # or pfm.exe on Windows
```

### Quick Start

1. Run the executable
2. Sample data will be created automatically on first run
3. Navigate using numeric menu options

## 🎮 Usage

### Main Menu

```tex
=========== PERSONAL FINANCE MANAGER ===========
1. Dashboard
2. Add Income Transaction
3. Add Expense Transaction
4. Add Recurring Transaction
5. View All Transactions
6. Statistics & Reports
7. Manage Wallets
8. Manage Income Sources
9. Manage Expense Categories
10. Process Recurring Transactions
0. Exit
================================================
```

### Key Functions

#### 1. Dashboard

Displays:

- Total balance across all wallets
- Individual wallet balances
- Current month's income/expense/net

#### 2. Add Income

```tex
==== ADD INCOME TRANSACTION ====
Enter date (dd mm yyyy): 01 12 2024
Enter amount: 5000000
============= WALLET LIST =============
1 - Cash - Balance: 0
2 - Bank - Balance: 0
3 - Momo - Balance: 0

Select wallet ID (or 0 to add new): 2
============= SOURCES LIST ============
1 - Salary
2 - Bonus
3 - Investment

Select source ID (or 0 to add new): 1
Description (optional): Monthly salary
Income added. Wallet 2 increased by 5,000,000
✓ Updated wallet 2 balance: 5,000,000
Income added successfully!
```

#### 3. Add Expense

```tex
==== ADD EXPENSE TRANSACTION ====
Enter date (dd mm yyyy): 05 12 2024
Enter amount: 200000
============= WALLET LIST =============
1 - Cash - Balance: 0
2 - Bank - Balance: 5,000,000
3 - Momo - Balance: 0

Select wallet ID (or 0 to add new): 2
============= CATEGORIES LIST ============
1 - Food
2 - Transportation
3 - Shopping
4 - Entertainment

Select category ID (or 0 to add new): 1
Description (optional): Dinner at restaurant
Expense added. Wallet 2 decreased by 200,000
✓ Updated wallet 2 balance: 4,800,000
Expense added successfully!
```

#### 4. Add Recurring Transaction

```tex
==== ADD RECURRING TRANSACTION ====
Is this income? (1 = Yes, 0 = No): 1
Enter amount: 3000000
Select wallet ID: 2
Select source ID: 1
Description (optional): Monthly salary
Start date (dd mm yyyy): 01 01 2024
Has end date? (y/n): n
Recurring transaction added successfully! ID: 1
```

#### 6. Statistics & Reports

Submenu options:

```tex
1. Time-based Statistics (Custom Date Range)
2. Wallet-based Statistics
3. Yearly Overview
4. Income Breakdown by Source
5. Expense Breakdown by Category
6. Net Balance Report
```

## 🏗️ Architecture

### Core Class Diagram

```tex
┌───────────────────┐     ┌──────────────────┐
│ FinanceManager    │────▶│ Transaction      │
├───────────────────┤     ├──────────────────┤
│ - Main controller │     │ - Base class     │
│ - Menu handling   │     │ - Date, Amount   │
│ - Data persistence│     │ - Wallet ID      │
└───────────────────┘     │ - Source/Category│
           │              └──────────────────┘
           │                       △
           │             ┌─────────┴─────────┐
           ▼             │                   │
┌─────────────────┐    ┌─▼───────┐       ┌───▼───────┐
│   Managers      │    │Income   │       │Expense    │
├─────────────────┤    ├─────────┤       ├───────────┤
│ WalletManager   │    │+SourceID│       │+CategoryID│
│ SourceManager   │    └─────────┘       └───────────┘
│ CategoryManager │
└─────────────────┘
```

### Key Design Decisions

- **Custom DynamicArray**: Manual memory management without STL containers
- **Binary Serialization**: Efficient file storage for all data types
- **Name Pool Optimization**: Separate storage for string data to reduce file size
- **Transaction Inheritance**: Income and Expense derived from base Transaction class

## 📁 Project Structure

```tex
PersonalFinanceManager/
├── src/                         # Source files
│   ├── main.cpp                 # Program entry point
│   ├── financeManager.cpp       # Main controller
│   ├── transactionManager.cpp   # Transaction operations
│   ├── walletManager.cpp        # Wallet management
│   ├── sourceManager.cpp        # Income source management
│   ├── categoryManager.cpp      # Expense category management
│   ├── transaction.cpp          # Base transaction class
│   ├── income.cpp               # Income transactions
│   ├── expense.cpp              # Expense transactions
│   ├── date.cpp                 # Date handling utilities
│   ├── dynamicArray.cpp  # Custom dynamic array implementation
│   ├── recurringTransaction.cpp # Recurring transactions
│   └── numberUtils.cpp          # Number formatting utilities
│   └── common.h          # Include some useful libraries
├── include/                     # Header files
│   ├── financeManager.h
│   ├── transactionManager.h
│   ├── walletManager.h
│   ├── dynamicArray.h    # Template dynamic array
│   ├── transaction.h
│   ├── income.h
│   ├── expense.h
│   ├── date.h
│   ├── recurringTransaction.h
│   ├── incomeSource.h
│   ├── expenseCategory.h
│   ├── sourceManager.h
│   ├── categoryManager.h
│   └── numberUtils.h
├── data/                 # Data storage (auto-created)
│   ├── wallets.bin       # Wallet data
│   ├── sources.bin       # Income sources
│   ├── categories.bin    # Expense categories
│   ├── transactions.bin  # Transaction records
│   ├── recurring.bin     # Recurring transactions
│   ├── walletNames.bin   # Wallet name pool
│   ├── sourceNames.bin   # Source name pool
│   └── categoryNames.bin # Category name pool
├── docs/                 # Documentation
├── README.md             # This file
└── .gitignore            # Git ignore rules
```

## 🙏 Acknowledgments

- **Course Instructor**: Dinh Ba Tien, Truong Phuoc Loc, Ho Tuan Thanh.
- **Course**: Introduction to Computer Science - FIT HCMUS, VNU-HCM.
- **References**: [cplusplus.com](https://cplusplus.com/), GitHub repositories
- **Tools**: Visual Studio Code, XCode, Git, Typora, Overleaf.

------

*Project completed December 2025*
