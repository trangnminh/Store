# Store
Video Rental Store  

This project is an school assignment for course EEET2482, RMIT University Vietnam C2019  

A CLI program for managing stock and customers of a video rental store  

Features:  
	* item and customer categories  
	* add, update, delete items and customers  
	* rent and return item with restrictions  
	* display items and customers by parameters  
	* search for items or customers  
	* auto promotion for regular customers  
	* auto points and freebies for VIP customers  
	* auto items and customers text files I/O  

Details in file EEET2482_Assignment2_Sem3_2019.pdf  

Usage:  
	cmd: start store.exe customer_file_name item_file_name  
	Terminal: ./store customer_file_name item_file_name  

!!!IMPORTANT!!!  
! Text files MUST BE of format:  
	Item: Ixxx-yyyy, title, rentalType, loanType, numOfCopies, rentalFee, genre (if non-Game)  
	Customer: Cxxx, name, address, phone, numOfPastRentals, level, points (if VIP)  
		  (list of rented IDs)  

! Program validates user input but is prone to input file errors  
! Careful with text files from other operating systems due to different line separators  

Group "God saving me"  
	s3751450, s3751450@rmit.edu.vn, Trang, Nguyen Minh  
	s3750789, s3750789@rmit.edu.vn, Han, Tran Mach So  
	s3574922, s3574922@rmit.edu.vn, Dat, Tran Quoc  



