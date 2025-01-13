# Library Management System
This Library Management System is a console-based application written in C. It allows users to manage books in a library through functionalities such as adding, deleting, modifying, and sorting books stored in a CSV file. The application interacts with a file named livres.csv to persist book data.

## Functionalities

1. saisirNomUtilisateur

Purpose: Prompts the user to input their name to personalize the application experience.

Description:

If the user enters sortir, the application exits.

Otherwise, the main menu is displayed.

2. afficherMenu

Purpose: Displays the main menu of the application.

Description:

Provides options to perform various operations such as adding, deleting, searching, sorting, and modifying books.

User can quit the application by selecting option 0.

3. ajouterLivre

Purpose: Adds a new book to the livres.csv file.

Description:

Prompts the user to input book details such as title, author, description, price, and category.

Checks if the book with the given ID already exists.

If not, appends the book details to the CSV file.

4. supprimerLivre

Purpose: Deletes a book by its ID from the livres.csv file.

Description:

Prompts the user for the ID of the book to delete.

Creates a temporary file temp.csv and copies all books except the one to delete.

Replaces the original file with the temporary file.

5. rechercheLivre

Purpose: Searches for a book in the livres.csv file by title and author.

Description:

Prompts the user for the book title and author.

Displays the book details if found; otherwise, informs the user that the book does not exist.

6. trier_par_titre

Purpose: Sorts all books alphabetically by their title.

Description:

Reads all books into an array of Livre structures.

Uses Bubble Sort to sort the books by title.

Writes the sorted books back to the livres.csv file.

7. modifierLivre

Purpose: Modifies details of a book by its ID.

Description:

Prompts the user for the book ID to modify.

Displays available modification options (e.g., title, author, price).

Updates the chosen field in the livres.csv file.

8. Structure "Livre"

This structure represents a book and contains the following fields:

ID: Integer, unique identifier for the book.

titre: String, title of the book.

auteur: String, author of the book.

description: String, description of the book.

nom_d_utilisateur: String, name of the user adding the book.

prix: Float, price of the book.

categorie: String, category of the book.

disponibilite: Integer, availability status (1 = available).


## File Structure

livres.csv

This file contains the library's book data in a CSV format with the following fields:

ID, Title, Author, Description, Username, Price, Category, Availability


## Dependencies

Standard Libraries:

stdio.h: For input/output operations.

string.h: For string manipulation.

stdlib.h: For memory allocation and process control.

ctype.h: For character handling.

Custom Library:

biblib.h: User-defined header file containing supporting declarations (not provided here).


## Notes

The program assumes livres.csv exists in the working directory.

Some system-specific commands, like system("cls") and sleep, are used for Windows compatibility. Modify these for cross-platform support if needed.

Proper error handling is implemented for file operations.
