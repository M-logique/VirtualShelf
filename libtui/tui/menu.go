package tui

import "github.com/pterm/pterm"

func MenuChoice() int {
	options := []string{
		"Add a new book",
		"Show all books",
		"Add a new student",
		"Borrowing a book",
		"Search by book title or author",
		"Display a list of borrowed books and the members who have them",
	}

	selectedOption, _ := pterm.DefaultInteractiveSelect.
	WithOptions(options).
	WithFilter(false).
	Show("Please select an option")

	selectedIndex := -1

	for i, option := range options {
		if option == selectedOption {
			selectedIndex = i
			break
		}
	}

	return selectedIndex
}