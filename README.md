# Video Rental Store

A simple CLI app for managing the stock and customers of a video rental store.

----- RMIT University Vietnam -----<br>
**Course:** EEET2482 - Software Engineering Design<br>
**Semester:** 2019C<br>
**Assessment:** Assignment 2<br>
**Student Name:** Nguyen Minh Trang<br>
**Student ID:** 3751450<br>

## 1. Introduction
- This CLI program provides CRUD functions to manage stock and customer lists

## 2. Features
- Item and customer categories  
- Add, update, delete items and customers  
- Rent and return item with restrictions  
- Display items and customers by parameters  
- Search for items or customers  
- Auto promotion for regular customers  
- Auto points and freebies for VIP customers  
- Auto items and customers text files I/O  

More details in file EEET2482_Assignment2_Sem3_2019.pdf (folder assignment).

## 3. Usage
1. Build the execution file and put it in the same folder as input text files
2. Run this command in Command Prompt:
```start store.exe customer_file_name item_file_name```
Terminal version:
```./store customer_file_name item_file_name```


### Notes 
Text files MUST BE of format:  
- Item: Ixxx-yyyy, title, rentalType, loanType, numOfCopies, rentalFee, genre (if non-Game)  
- Customer: Cxxx, name, address, phone, numOfPastRentals, level, points (if VIP)  
		  (list of rented IDs)  
