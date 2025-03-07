package main

import "C"

import (
	"fmt"
	"libtui/tui"
	"time"

	"github.com/pterm/pterm"
)

//export PrintLogo
func PrintLogo() {
	tui.PrintLogo()
}

//export GetMenuChoice
func GetMenuChoice() int {
	return tui.MenuChoice()
}

//export TypeText
func TypeText(text *C.char) {
	goText := C.GoString(text)

	tui.TypeText(
		goText,
		time.Millisecond * 3,
		pterm.NewRGB(0, 255, 255),
		pterm.NewRGB(80, 80, 80),
	)
}

//export PressEnter
func PressEnter() {
	fmt.Println()
	tui.TypeText(
		"Press enter to continue...", 
		time.Millisecond * 10, 
		pterm.NewRGB(0, 255, 255),
		pterm.NewRGB(80, 80, 80),
	)
	fmt.Scanln()
}


func main() {}