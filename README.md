# network-programming-labs
# 💻 Systems and Network Programming Labs & Final Project

## 👨‍🎓 Student: Etape Benida  
## 🧾 Course: Systems and Network Programming  
## 🎯 Institution: University of Buea   
## 📅 Semester: 3rd year/ 2nd semester

---

## 📁 Overview

This repository contains the completed lab exercises and final project for the *Systems and Network Programming* course. The projects demonstrate interprocess communication (IPC), socket programming, distributed systems, and real-time communication using both TCP and UDP.

---

## 🧪 Labs Summary

### 🔹 **Lab 2: Unnamed Pipe – IPC Between Parent and Child**
- Used `pipe()` and `fork()` to create a pipe between a parent and child process.
- Parent writes a message; child reads it and prints the result.
- Demonstrates one-way communication within related processes.

### 🔹 **Lab 3: Named Pipe (FIFO) – IPC Between Independent Processes**
- Used `mkfifo()` to create a FIFO file.
- Implemented separate `server` and `client` programs for communication.
- Demonstrated one-way and two-way sync using either one or two FIFOs.

### 🔹 **Lab 4: Socket Programming – TCP & UDP**
- Implemented basic TCP server-client connection and message exchange.
- Created a UDP version for lightweight, connectionless communication.
- Compared TCP (reliable) and UDP (faster, suitable for real-time).

### 🔹 **Lab 5: Distributed Systems – Multi-Client Communication**
- Developed a TCP server using threads to handle multiple clients.
- Clients send and receive messages in real-time through the server.
- Built a broadcast system for full real-time synchronization between clients.

---

## 📡 Final Project – Real-Time Temperature Monitoring System (UDP-Based)

### 🧩 Description:
- Simulates 3 temperature sensor clients sending periodic temperature data via UDP to a central server.
- Server logs data and optionally broadcasts to other clients for real-time updates.
- Demonstrates real-world IoT concepts: fast, stateless, multi-client UDP communication.

---

## ⚙️ How to Compile and Run

### 🔨 Compile C Files
```bash
gcc filename.c -o program
