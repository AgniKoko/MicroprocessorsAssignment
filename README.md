# Microprocessors Assignment

## **Introduction**
This repository contains the implementation of a microprocessor-based ATM simulator as described in the exercise statement. The purpose of this project is to demonstrate concepts related to microprocessor programming, memory management, and hardware interaction using ARM assembly language.

![vlcsnap-2025-01-09-11h24m32s669](https://github.com/user-attachments/assets/3403923a-97ab-421e-81ed-41d63f8ae5fa)

---

## **Assignment Description**
The task involves the simulation of an ATM that processes banknotes and verifies user PINs. Below is the full description of the exercise extracted from the assignment statement:

### **Statements**
1. The microprocessor is responsible for:
   - Reading a user PIN entered by the user and comparing it with the PIN stored on the ATM card.
   - Each PIN is stored in hexadecimal format for simplicity.
   - The ATM card PIN is transferred to the accessible memory address `0x0200H`.

2. The system will:
   - Check if the user PIN matches the card PIN.
   - If the PINs match, the ATM will handle the banknotes.
   - If the PINs do not match, an error signal will be activated.

3. **Banknotes Handling Logic**:
   - Each banknote type is represented by a switch, located at specific memory addresses:
     - `0x1FFFF010` for 200€ banknotes.
     - `0x1FFFF014` for 100€ banknotes.
     - `0x1FFFF018` for 50€ banknotes.
     - `0x1FFFF020` for 20€ banknotes.
     - `0x1FFFF024` for 10€ banknotes.
     - `0x1FFFF028` for 5€ banknotes.

   - Each switch should be activated and deactivated in a loop according to the count of each banknote requested.
   - For every banknote, the switch must turn ON (value `1`), wait briefly, and then turn OFF (value `0`).

4. **Error Handling**:
   - If the PINs do not match, an error signal (`30H`) will be activated, and the program will terminate.

5. **Requirements**:
   - Use ARM assembly language.
   - Store and handle the PINs and switches correctly using the appropriate memory addresses.
   - Ensure proper memory management, including handling banknote operations in a loop.
   - The digital board used for this project is the property of the course's professor and is required for hardware testing.

---

## **Structure of the Repository**
- `main.c`: The main C file for setting up variables and calling the assembly function. Also contains MyFunc, an ARM assembly code implementing the PIN verification, error handling, and banknote switching logic.
- `README.md`: This file, explaining the assignment and its implementation.

---

## **Execution**
1. Open Keil μVision.
2. Load the `main.c` and `MyFunc.asm` files into the project.
3. Build the project to ensure there are no syntax or logic errors.
4. Run the project in Debug mode to simulate the execution and verify the memory addresses, PIN comparison, and banknote handling.

---

## **License**
This project is based on an assignment from the "Microprocessors and Applications" course at Democritus University of Thrace (DUTH). The original task description is intellectual property of the course instructor.

