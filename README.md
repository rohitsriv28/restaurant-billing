# Spice Symphony - Invoice Management System

Spice Symphony is a simple, interactive console-based invoice management system developed in C. It allows you to create, save, and retrieve customer invoices for a restaurant-like business setup. The system supports invoice creation with itemized billing, tax/discount calculations, colored terminal output, and persistent storage using binary files.

---

## 🚀 Features

- 📦 Create new invoices with multiple items
- 💾 Save invoices to a binary file (`SpiceSymphony.dat`)
- 🔍 Search invoices by customer name
- 📜 View all saved invoices
- 💰 Automatic discount and VAT calculations
- 🎨 Colorful and formatted bill output

---

## 🛠️ Technologies Used

- **Language:** C (Standard Library)
- **File Handling:** Binary files for persistent storage
- **Terminal Styling:** ANSI color codes for colorful output

---

## 🧾 Invoice Structure

Each invoice (order) includes:

- Customer Name
- Date and Time
- List of Items:
  - Item Name
  - Quantity
  - Unit Price
- Subtotal
- Discount @10%
- VAT @13%
- Grand Total

---

## 📂 File Details

- **FILENAME:** `SpiceSymphony.dat`
- Stored in binary format using `fwrite()` and `fread()`

---

## 📋 How to Use

1. **Compile the Code:**
   ```bash
   gcc -o spice_symphony spice_symphony.c
   ```

2. **Run the Program:**
   ```bash
   ./spice_symphony
   ```

3. **Menu Options:**
   - `1`: Create a new invoice
   - `2`: View all saved invoices
   - `3`: Search invoice by customer name
   - `4`: Exit the system

4. **Continue Operations:**
   - After each action, you can choose to continue or exit.

---

## 🧠 Key Functions

- `createNewOrder()` - Handles invoice creation and input
- `saveOrder()` - Saves the invoice to file
- `displayAllOrders()` - Displays all invoices from file
- `searchOrderByCustomer()` - Searches and displays invoices by customer name
- `printBillHeader()` / `printBillBody()` / `printBillFooter()` - Formatted invoice printing

---

## 📌 Notes

- Max 50 items per invoice
- Uses `struct` for data modeling (`Item`, `Order`)
- ANSI escape codes used for terminal color output (works best on Linux/macOS)
- Input buffer is cleared to avoid newline issues

---

## 🧽 To Do / Future Improvements

- Add deletion and editing of invoices
- Export invoices to `.txt` or `.pdf`
- GUI-based version using C++ or Python
- Enhanced validation and user authentication

---

## 🙌 Credits

Developed in VS Code as a C programming project.

---
