package main

/*
#cgo CXXFLAGS: -std=c++14
#cgo CFLAGS: -I./../include
#cgo LDFLAGS: -L./libtui -lstdc++
#include "shared.h"
*/
import "C"

import (
	"fmt"
	"libtui/tui"
	"time"
	"unsafe"

	"github.com/pterm/pterm"
)

//export GoPrintLogo
func GoPrintLogo() {
	tui.PrintLogo()
}

//export GoGetMenuChoice
func GoGetMenuChoice() int {
	return tui.MenuChoice()
}

//export GoTypeText
func GoTypeText(text *C.char) {
	goText := C.GoString(text)

	tui.TypeText(
		goText,
		time.Millisecond * 5,
		pterm.NewRGB(0, 255, 255),
		pterm.NewRGB(80, 80, 80),
	)
}

//export GoPressEnter
func GoPressEnter() {
	fmt.Println()
	tui.TypeText(
		"Press enter to continue...", 
		time.Millisecond * 10, 
		pterm.NewRGB(0, 255, 255),
		pterm.NewRGB(80, 80, 80),
	)
	fmt.Scanln()
}

//export GoUpdateRGBState
func GoUpdateRGBState() {
	tui.RgbEnabled = int(C.is_rgb_enabled())
}

//export GoBetterPrint
func GoBetterPrint(text *C.char) {
	goText := C.GoString(text)
	tui.BetterPrint(goText)
}

//export GoDisplayBookSelector
func GoDisplayBookSelector() int {

	var size C.int
	valuesPtr := C.get_book_values(&size)

	if valuesPtr == nil || size == 0 {
		tui.BetterPrint("{{.Red}}[!]{{.Yellow}} There is no book in the shelf!\n{{.Reset}}")
		GoPressEnter()
		return -1
	}

	values := unsafe.Slice((**C.char)(unsafe.Pointer(valuesPtr)), size)

	var options []string
	for _, value := range values {
		options = append(options, C.GoString(value))
	}

	C.free_values(valuesPtr, size)

	selector := pterm.DefaultInteractiveSelect.
		WithOptions(options).
		WithFilter(true).
		WithMaxHeight(10)

	selector.SelectorStyle = pterm.NewStyle(pterm.FgDarkGray)

	selectedOption, _ := selector.Show("Please select a book")

	var bookID int
	_, err := fmt.Sscanf(selectedOption, "ID: %d", &bookID)
	if err != nil {
		fmt.Println("Error extracting book ID:", err)
		return -1
	}

	return bookID
}

//export GoDisplayStudentSelector
func GoDisplayStudentSelector() int {

	var size C.int
	valuesPtr := C.get_student_values(&size)

	if valuesPtr == nil || size == 0 {
		tui.BetterPrint("{{.Red}}[!]{{.Yellow}} You don't have any students yet!\n{{.Reset}}")
		GoPressEnter()
		return -1
	}

	values := unsafe.Slice((**C.char)(unsafe.Pointer(valuesPtr)), size)

	var options []string
	for _, value := range values {
		options = append(options, C.GoString(value))
	}

	C.free_values(valuesPtr, size)

	selector := pterm.DefaultInteractiveSelect.
		WithOptions(options).
		WithFilter(true).
		WithMaxHeight(10)

	selector.SelectorStyle = pterm.NewStyle(pterm.FgDarkGray)

	selectedOption, _ := selector.Show("Please select a student")

	var studentID int
	_, err := fmt.Sscanf(selectedOption, "ID: %d", &studentID)
	if err != nil {
		fmt.Println("Error extracting book ID:", err)
		return -1
	}

	return studentID
}


func main() {}