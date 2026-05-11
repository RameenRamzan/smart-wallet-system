# SmarWallet — Smart Banking Wallet System

> A console-based banking simulation built in C++ that demonstrates core Data Structures (Arrays, Linked Lists, Stacks, and Queues) in a real-world fin-tech context.

**Course:** Data Structures and Algorithms — Fall 2025  
**Institution:** FAST-NUCES, Karachi Campus  
**Team:**
- Rameen Ramzan — Roll# 24K-0557
- Umama Zubair — Roll# 24K-0621

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Data Structures Used](#data-structures-used)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Build Instructions](#build-instructions)
  - [Running the Pre-built Executable](#running-the-pre-built-executable)
- [Usage](#usage)
  - [Admin Login](#admin-login)
  - [User Operations](#user-operations)
  - [Reports](#reports)
- [Module Overview](#module-overview)
- [Algorithmic Workflow](#algorithmic-workflow)

---

## Overview

SmarWallet is an interactive, console-based banking wallet system that simulates real-world digital finance operations. Users can create accounts, perform transactions, undo mistakes, schedule recurring payments, and view detailed reports — all through a colour-coded terminal GUI with ASCII art.

The project was built as part of a DSA course to showcase how fundamental data structures power everyday financial applications.

---

## Features

| Feature | Description |
|---|---|
| **Account Management** | Create, update, and delete user accounts |
| **Deposits & Withdrawals** | Instantly update account balances |
| **Fund Transfers** | Move funds between any two accounts |
| **Undo Transactions** | Roll back the last transaction using a Stack |
| **Transaction History** | View a full per-account history via a Linked List |
| **Scheduled Payments** | Queue recurring or future payments for automated processing |
| **Admin Dashboard** | Privileged view of all accounts and system statistics |
| **Report Generation** | User reports, transaction logs, financial summaries, and activity reports |
| **Colour Console UI** | ANSI/Windows colour-coded menus with ASCII art |

---

## Data Structures Used

| Feature | Primary Data Structure |
|---|---|
| User Accounts and Profile Management | Array (`User users[MAX_USERS]`) |
| Deposits, Withdrawals, and Transfers | Array / Linked List |
| Undo Recent Transactions | **Stack** (`Stack undoStack`) |
| Per-Account Transaction History | **Linked List** (`Transaction* transactionHistory`) |
| Scheduled / Recurring Payments | **Queue** (`Queue paymentQueue`) |

---

## Project Structure

```
SmarWallet/
├── main.cpp              # Entry point — launches SimpleGUI
├── SimpleGUI.h/.cpp      # Console UI: menus, screens, ASCII art, colour output
├── BankingSystem.h/.cpp  # Core logic: accounts, transactions, scheduling, reports
├── User.h/.cpp           # User model with linked-list transaction history
├── Transaction.h/.cpp    # Transaction node (linked list element)
├── Stack.h/.cpp          # Stack for undo functionality
├── Queue.h/.cpp          # Queue for scheduled/recurring payments
├── Report.h/.cpp         # Static report-generation utilities
├── Admin.h/.cpp          # Admin credentials and authentication
├── colors.h/.cpp         # ANSI/Windows terminal colour helpers
└── SmarWallet.exe        # Pre-built Windows executable
```

---

## Getting Started

### Prerequisites

- A C++17-compatible compiler (e.g., `g++ 11+`, MSVC, or Clang)
- Windows (for the pre-built `.exe` and Windows Console colour support) or any ANSI-capable terminal on Linux/macOS

### Build Instructions

Clone or unzip the project, then compile all `.cpp` files together:

```bash
g++ -std=c++17 -o SmarWallet \
    main.cpp \
    SimpleGUI.cpp \
    BankingSystem.cpp \
    User.cpp \
    Transaction.cpp \
    Stack.cpp \
    Queue.cpp \
    Report.cpp \
    Admin.cpp \
    colors.cpp
```

On Windows (MinGW):
```bash
g++ -std=c++17 -o SmarWallet.exe main.cpp SimpleGUI.cpp BankingSystem.cpp User.cpp Transaction.cpp Stack.cpp Queue.cpp Report.cpp Admin.cpp colors.cpp
```

### Running the Pre-built Executable

A pre-built Windows binary is included:

```
SmarWallet.exe
```

Simply double-click it or run it from a terminal:

```cmd
SmarWallet.exe
```

---

## Usage

### Admin Login

The system starts with a welcome screen and login prompt.

| Credential | Value |
|---|---|
| Username | `admin` |
| Password | `admin123` |

After logging in, the admin can manage all user accounts, view system-wide reports, and process scheduled payments.

### User Operations

Once an account is selected, the following operations are available:

- **Deposit** — Add funds to an account
- **Withdraw** — Deduct funds (balance-checked)
- **Transfer** — Move funds to another account
- **Undo** — Reverse the most recent transaction via the undo stack
- **View History** — Browse the full transaction linked list for that account
- **Schedule Payment** — Enqueue a future payment with a date and description

### Reports

Accessible from the Admin Dashboard:

- **User Report** — Lists all registered accounts and their balances
- **Transaction Report** — Full transaction log, optionally filtered by date range
- **Financial Summary** — System-wide totals: total balance, active users, transaction volume
- **User Activity Report** — Last activity date and transaction count per user

---

## Module Overview

### `BankingSystem`
The central controller. Holds the `User` array (up to 100 users), the `Stack` for undo, the `Queue` for scheduled payments, and the `Admin` object. All business logic (deposit, withdraw, transfer, scheduling, reports) lives here.

### `User`
Stores account ID, name, email, phone, balance, join date, and a pointer to a singly linked list of `Transaction` nodes representing that account's history.

### `Transaction`
A linked-list node storing transaction ID, type (`DEPOSIT`, `WITHDRAWAL`, `TRANSFER`), amount, date, description, and the account it belongs to.

### `Stack`
A custom singly-linked stack. Each push records the account ID, transaction type, amount, and (for transfers) the target account. `undoLastTransaction()` pops from this stack and reverses the operation.

### `Queue`
A singly-linked FIFO queue for scheduled payments. Each node holds source/destination account IDs, amount, scheduled date, and a description. `processScheduledPayments()` dequeues and executes them in order.

### `Report`
A stateless utility class with static methods that iterate over the `User` array to generate formatted console reports.

### `SimpleGUI`
Drives the full console interface: clears the screen, renders colour-coded headers and menus, reads user input, and dispatches to the appropriate `BankingSystem` methods.

### `Admin`
Stores admin credentials and exposes an `authenticate()` method. Default credentials are `admin` / `admin123`.

---

## Algorithmic Workflow

```
Start
  └── SimpleGUI::run()
        ├── handleLoginScreen()        → Admin::authenticate()
        └── handleMainMenu()
              ├── handleUserOperations()
              │     ├── deposit()      → update balance, push to Stack, append to Transaction linked list
              │     ├── withdraw()     → update balance, push to Stack, append to Transaction linked list
              │     ├── transfer()     → update both balances, push to Stack
              │     ├── undoLastTransaction() → Stack::pop() → reverse last operation
              │     ├── displayTransactionHistory() → traverse Transaction linked list
              │     └── schedulePayment() → Queue::enqueue()
              ├── handleAdminDashboard()
              │     ├── displayAllAccounts()
              │     ├── processScheduledPayments() → Queue::dequeue() in FIFO order
              │     └── handleReportsMenu() → Report static methods
              └── Exit
```
