# Student Hall Management System

A modular **Student Hall Management System** written in C.
This project manages student data, authentication, meals, and billing using a structured multi-file architecture.

---

## 📌 Features

* 📋 Student record management
* 🔐 Authentication system
* 🍽️ Meal tracking
* 💳 Billing management
* 💾 File-based storage system
* 🧩 Modular code design

---

## 🛠️ Technologies Used

* Language: C
* Core Concepts:

  * Modular Programming (.c / .h separation)
  * File Handling
  * Structures
  * Functions

---

## 📂 Project Structure

```id="plk9za"
.
├── main.c
├── student.c
├── student.h
├── auth.c
├── auth.h
├── meal.c
├── meal.h
├── billing.c
├── billing.h
├── file_handler.c
├── file_handler.h
├── Makefile
└── README.md
```

---

## ⚙️ Build & Run

### Compile the project

```bash id="d6hv3r"
gcc main.c student.c auth.c meal.c billing.c file_handler.c -o elvaris
```

*or using Makefile:*

```bash id="u2u1l2"
make
```

### Run the program

```bash id="3xxgq6"
./elvaris
```

---

## 🧹 Clean Build

```bash id="akb9f3"
make clean
```

---

## 🧠 Module Overview

* **student** → Handles student data and operations
* **auth** → Manages login/authentication
* **meal** → Tracks meal plans and usage
* **billing** → Calculates and manages payments
* **file_handler** → Handles file I/O operations

---

## 🚀 Future Improvements

* Add database support (SQLite/MySQL)
* GUI-based interface
* Role-based authentication (Admin/User)
* Reporting system (monthly bills, meal stats)
* Error handling & validation improvements

---

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Open a Pull Request

---


## 👨‍💻 Author

0x7byte
